"""The opt-in -frac2-mult-add-no-flatten: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("mult_add_no_flatten",
    ROOT / "tools/compiler/transformers/mult_add_no_flatten.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-mult-add-no-flatten"
FUNCTIONS = ("shift_row", "clear_row")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def offset_partner(body: str) -> str:
    """What the base-minus-16 register is first added to: "product" (the row's i*400 from
    mult) or "sum" (anything else, such as the flattened slot*16 + i*400)."""
    kind = {}  # register -> what its latest definition computed
    for op, dest, args in re.findall(r"(?m)^\t(\w+)\t(\$\d+),(\S+)$", body):
        args = args.split(",")
        if op == "addu" and len(args) == 2 and "base16" in (kind.get(args[0]), kind.get(args[1])):
            other = args[1] if kind.get(args[0]) == "base16" else args[0]
            return "product" if kind.get(other) == "product" else "sum"
        if op == "mult":
            kind[dest] = "product"
        elif op == "addu" and args[-1] == "-16" and "base16" not in kind.values():
            kind[dest] = "base16"
        else:
            kind[dest] = op
    raise AssertionError("base-minus-16 register is never added")


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"expmed.c": "a\n" + transformer.EXPAND_OLD + "b\n",
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
            expmed = (root / "expmed.c").read_text()
            self.assertEqual(expmed.count("if (flag_rac2_mult_add_no_flatten)"), 1)
            self.assertEqual(expmed.count("flag_schedule_insns = rac2_saved_schedule_insns;"), 1)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_mult_add_no_flatten = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_mult_add_no_flatten, 1,', top)
            self.assertIn("extern int flag_rac2_mult_add_no_flatten;", (root / "flags.h").read_text())
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
            source.write_bytes((ROOT / "tests/fixtures/mult_add_no_flatten.c").read_bytes())
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

    def test_default_flattens_the_source_cursor(self):
        self.assertEqual(offset_partner(self.outputs["default"]["shift_row"]), "sum")

    def test_option_keeps_row_plus_offset_base(self):
        self.assertEqual(offset_partner(self.outputs["enabled"]["shift_row"]), "product")

    def test_control_without_an_offset_is_unchanged(self):
        self.assertEqual(self.outputs["default"]["clear_row"], self.outputs["enabled"]["clear_row"])


if __name__ == "__main__":
    unittest.main()
