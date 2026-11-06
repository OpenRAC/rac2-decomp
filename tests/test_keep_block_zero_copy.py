"""The opt-in -frac2-keep-block-zero-copy: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("keep_block_zero_copy",
    ROOT / "tools/compiler/transformers/keep_block_zero_copy.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-keep-block-zero-copy"
FUNCTIONS = ("same_block", "other_block")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def moves(body: str) -> list:
    """The register moves, as (destination, source)."""
    return re.findall(r"\tmove\t(\$\d+),(\$\d+)", body)


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"cse.c": "a\n" + transformer.HELPER_OLD + "\nb\n" + transformer.CHOICE_OLD,
                 "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
                 "flags.h": transformer.DECLARATION_OLD}
        files.update(override)
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            cse = (root / "cse.c").read_text()
            self.assertEqual(cse.count("rac2_set_in_block_p (insn, reg)"), 1)
            self.assertIn("if (flag_rac2_keep_block_zero_copy", cse)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_keep_block_zero_copy = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_keep_block_zero_copy, 1,', top)
            self.assertIn("extern int flag_rac2_keep_block_zero_copy;", (root / "flags.h").read_text())
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            files = self.sources(root, **{"flags.h": "unexpected declaration"})
            with self.assertRaisesRegex(ValueError, "option declaration"):
                transformer.patch(root)
            self.assertEqual({name: (root / name).read_text() for name in files}, files)


class CompilerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools"))
        if not all((compiler / name).is_file() for name in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built cpp, cc1 and as")
            raise unittest.SkipTest("EE compiler absent; tools/compiler/build.sh runs these checks after building it")
        cls.outputs = {}
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            source = root / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/keep_block_zero_copy.c").read_bytes())
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            for label, options in PROFILES.items():
                asm = root / (label + ".s")
                subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                                *options, str(root / "input.i"), "-o", str(asm)], check=True)
                subprocess.run([str(compiler / "as"), "-o", str(root / (label + ".o")), str(asm)], check=True)
                text = asm.read_text()
                cls.outputs[label] = {name: function_text(text, name) for name in FUNCTIONS}

    def test_disabled_option_restores_default_for_every_function(self):
        self.assertEqual(self.outputs["default"], self.outputs["disabled"])

    def test_default_folds_the_copy_to_zero(self):
        self.assertEqual(sum(source == "$0" for _, source in moves(self.outputs["default"]["same_block"])), 2)

    def test_option_keeps_the_same_block_copy(self):
        enabled = moves(self.outputs["enabled"]["same_block"])
        self.assertEqual(sum(source == "$0" for _, source in enabled), 1)
        zero = next(dest for dest, source in enabled if source == "$0")
        self.assertIn(zero, [source for _, source in enabled])

    def test_control_across_a_call_is_unchanged(self):
        self.assertEqual(self.outputs["default"]["other_block"], self.outputs["enabled"]["other_block"])


if __name__ == "__main__":
    unittest.main()
