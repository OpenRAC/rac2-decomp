"""The opt-in -frac2-narrow-saves-below: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("narrow_saves_below",
    ROOT / "tools/compiler/transformers/narrow_saves_below.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-narrow-saves-below"
FUNCTIONS = ("same_width", "narrow_ra")
PROFILES = {"plain": [], "plain_enabled": ["-f" + OPTION],
            "default": ["-mastra-quad-saves"], "enabled": ["-mastra-quad-saves", "-f" + OPTION],
            "disabled": ["-mastra-quad-saves", "-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def saves(body: str) -> list:
    """The $16/$31 stack saves and restores as (op, register, offset), sorted."""
    return sorted(re.findall(r"\t(sq|sd|lq|ld)\s+(\$16|\$31),(\d+)\(\$sp\)", body))


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"config/mips/mips.c": "a\n" + transformer.SCOPE_OLD + "b\n" + transformer.LOOP_OLD,
                 "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
                 "flags.h": transformer.DECLARATION_OLD}
        files.update(override)
        (root / "config/mips").mkdir(parents=True, exist_ok=True)
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            mips = (root / "config/mips/mips.c").read_text()
            self.assertEqual(mips.count("rac2_width_pass < (rac2_by_width ? 2 : 1)"), 1)
            self.assertIn("flag_rac2_narrow_saves_below && mips_astra_quad_saves", mips)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_narrow_saves_below = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_narrow_saves_below, 1,', top)
            self.assertIn("extern int flag_rac2_narrow_saves_below;", (root / "flags.h").read_text())
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
            source.write_bytes((ROOT / "tests/fixtures/narrow_saves_below.c").read_bytes())
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

    def test_option_has_no_effect_without_quad_saves(self):
        self.assertEqual(self.outputs["plain"], self.outputs["plain_enabled"])

    def test_default_keeps_ra_in_the_top_slot(self):
        self.assertEqual(saves(self.outputs["default"]["narrow_ra"]),
                         sorted([("sd", "$31", "16"), ("sq", "$16", "0"), ("ld", "$31", "16"), ("lq", "$16", "0")]))

    def test_option_puts_the_narrower_ra_save_below(self):
        self.assertEqual(saves(self.outputs["enabled"]["narrow_ra"]),
                         sorted([("sq", "$16", "16"), ("sd", "$31", "0"), ("lq", "$16", "16"), ("ld", "$31", "0")]))

    def test_control_keeps_ra_on_top(self):
        self.assertEqual(self.outputs["default"]["same_width"], self.outputs["enabled"]["same_width"])
        self.assertEqual(saves(self.outputs["enabled"]["same_width"]),
                         sorted([("sq", "$31", "16"), ("sq", "$16", "0"), ("lq", "$31", "16"), ("lq", "$16", "0")]))


if __name__ == "__main__":
    unittest.main()
