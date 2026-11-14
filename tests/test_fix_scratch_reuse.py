"""The opt-in -frac2-fix-scratch-reuse: transformer drift and EE compiler-output controls.

The integer scratch of fix_truncsfsi2 is never emitted on the R5900, so the controls read it
from the post-reload RTL dump (-dg) and check that the assembly does not change in the fixture.
"""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("fix_scratch_reuse",
    ROOT / "tools/compiler/transformers/fix_scratch_reuse.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "-frac2-fix-scratch-reuse"
PROFILES = {"default": [], "enabled": [OPTION], "disabled": [OPTION, "-fno-rac2-fix-scratch-reuse"]}
SCRATCH = re.compile(r"\(fix:SI[^\n]*\n\s+\(clobber \(reg:SI (\d+)")


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path) -> dict:
        files = {
            "reload1.c": "a\n" + transformer.HELPER_OLD + "b\n" + transformer.ORDER_OLD + "c\n",
            "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
            "flags.h": transformer.DECLARATION_OLD,
        }
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            reload1 = (root / "reload1.c").read_text()
            self.assertIn("rac2_fix_scratch_p (insn)", reload1)
            self.assertIn("if (flag_rac2_fix_scratch_reuse && rac2_fix_scratch_p (chain->insn))", reload1)
            self.assertLess(reload1.index("flag_rac2_fix_scratch_reuse"), reload1.index("qsort (hard_reg_n_uses"))
            self.assertIn('"rac2-fix-scratch-reuse"', (root / "toplev.c").read_text())
            self.assertIn("extern int flag_rac2_fix_scratch_reuse;", (root / "flags.h").read_text())

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
            (root / "reload1.c").write_text("no anchor\n")
            files["reload1.c"] = "no anchor\n"
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
        cls.asm, cls.scratches = {}, {}
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            source = root / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/fix_scratch_reuse.c").read_bytes())
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
                                "-dg", *options, str(root / "input.i"), "-o", str(asm)], check=True, cwd=root)
                subprocess.run([str(compiler / "as"), "-o", str(root / (label + ".o")), str(asm)], check=True)
                cls.asm[label] = asm.read_text()
                cls.scratches[label] = SCRATCH.findall((root / "input.i.greg").read_text())

    def test_disabled_option_restores_default(self):
        self.assertEqual(self.scratches["default"], self.scratches["disabled"])
        self.assertEqual(self.asm["default"], self.asm["disabled"])

    def test_second_truncation_reuses_the_first_scratch(self):
        self.assertEqual(len(self.scratches["default"]), 2)
        first, second = self.scratches["default"]
        self.assertNotEqual(first, second)
        self.assertEqual(self.scratches["enabled"], [first, first])

    def test_unemitted_scratch_leaves_this_fixture_unchanged(self):
        self.assertEqual(self.asm["default"], self.asm["enabled"])


if __name__ == "__main__":
    unittest.main()
