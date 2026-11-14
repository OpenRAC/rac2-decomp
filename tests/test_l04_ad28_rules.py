"""The opt-in switches for func_L04_0040AD28: transformer drift and EE output controls.

The positive control is a matched unit the switch is known to change (src/levels/shared/L04_00402D90-results-g8.c); it is
compiled in place, never copied. The disabled form must give the default bytes.
"""
import importlib.util
import os
from pathlib import Path
import shlex
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("l04_ad28_rules",
    ROOT / "tools/compiler/transformers/l04_ad28_rules.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTIONS = ['-frac2-ga-no-lo-sum-pref', '-frac2-ga-divisor-first', '-frac2-sched2-call-copy-fp-wait', '-frac2-sched2-const-low-reg-first']
UNIT = ROOT / "src/levels/shared/L04_00402D90-results-g8.c"
FLAGS = shlex.split("-O2 -G8 -ffunction-sections -g")
PROFILES = {"default": [], "enabled": OPTIONS,
            "disabled": OPTIONS + ["-fno-" + o[2:] for o in OPTIONS]}


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path) -> dict:
        files = {
            name: "a\n" + "\nb\n".join(old for old, _ in hunks) + "c\n"
            for name, hunks in transformer.HUNKS.items()
        }
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            self.assertIn("flag_rac2_ga_divisor_first", (root / "global.c").read_text())
            self.assertIn('"rac2-ga-divisor-first"', (root / "toplev.c").read_text())
            self.assertIn("extern int flag_rac2_ga_divisor_first;", (root / "flags.h").read_text())

    def test_already_applied_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            with self.assertRaises(ValueError):
                transformer.patch(root)

    def test_missing_insertion_point_changes_nothing(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            files = self.sources(root)
            (root / "global.c").write_text("no anchor\n")
            files["global.c"] = "no anchor\n"
            with self.assertRaises(ValueError):
                transformer.patch(root)
            self.assertEqual({n: (root / n).read_text() for n in files}, files)


class CompilerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")).resolve()
        if not all((compiler / name).is_file() for name in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built cpp, cc1 and as")
            raise unittest.SkipTest("EE compiler absent; tools/compiler/build.sh runs these checks after building it")
        cls.asm = {}
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), "-I" + str(compiler / "include"),
                                    "-I" + str(ROOT / "include"), "-I" + str(UNIT.parent), str(UNIT)],
                                   stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            for label, options in PROFILES.items():
                asm = root / (label + ".s")
                subprocess.run([str(compiler / "cc1"), "-quiet", *FLAGS, *options,
                                str(root / "input.i"), "-o", str(asm)], check=True)
                cls.asm[label] = asm.read_text()

    def test_disabled_option_restores_default(self):
        self.assertEqual(self.asm["default"], self.asm["disabled"])

    def test_control_unit_changes_when_enabled(self):
        self.assertNotEqual(self.asm["default"], self.asm["enabled"])


if __name__ == "__main__":
    unittest.main()
