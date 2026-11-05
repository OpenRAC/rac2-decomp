"""reload_reg_used_guard.py: the transformer's anchor, and an inheritance reload refuses a non-spill register."""
import importlib.util
import os
from pathlib import Path
import re
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent

spec = importlib.util.spec_from_file_location(
    "reload_reg_used_guard", ROOT / "tools/compiler/transformers/reload_reg_used_guard.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

NAMES = ("refused", "inherited")


class TransformerTests(unittest.TestCase):
    SOURCE = (transformer.DECLARATION_OLD
              + "static int\nreload_reg_free_for_value_p ()\n{\n"
              + transformer.OLD + "    }\n}\n"
              + "void choose_reload_regs(void) {\n" + transformer.INITIAL_OLD + "}\n")

    def test_patch_tests_reload_reg_used_first_and_applies_once(self):
        patched = transformer.patch(self.SOURCE)
        body = patched.split("int copy = 0;\n", 1)[1]
        self.assertRegex(body, r"(?s)^\n  /\* RAC2: .*?\*/\n  if \(TEST_HARD_REG_BIT \(rac2_reload_unavailable, regno\)\)\n"
                               r"    return 0;\n\n  if \(out == const0_rtx\)")
        self.assertIn(transformer.DECLARATION_NEW, patched)
        self.assertTrue(patched.endswith(transformer.INITIAL_NEW + "}\n"))
        with self.assertRaisesRegex(ValueError, "already patched"):
            transformer.patch(patched)

    def test_source_drift_is_rejected(self):
        with self.assertRaisesRegex(ValueError, "expected one anchor, found 0"):
            transformer.patch(self.SOURCE.replace("int copy = 0;", "int copy;"))
        with self.assertRaisesRegex(ValueError, "found 2"):
            transformer.patch(self.SOURCE + transformer.OLD)

    def test_missing_or_duplicate_snapshot_anchor_is_rejected(self):
        for anchor in (transformer.DECLARATION_OLD, transformer.INITIAL_OLD):
            for source in (self.SOURCE.replace(anchor, ""), self.SOURCE + anchor):
                with self.subTest(anchor=anchor), self.assertRaises(ValueError):
                    transformer.patch(source)


class ReloadLifetimeTests(unittest.TestCase):
    def test_real_predicate_keeps_conflicts_but_ignores_its_own_reload(self):
        source_path = os.environ.get("RAC2_GCC_SOURCE")
        if not source_path:
            self.skipTest("compiler recipe supplies its freshly patched reload1.c")
        compiler = shutil.which("cc") or shutil.which("gcc")
        if not compiler:
            self.fail("native C compiler required by the compiler recipe")
        text = Path(source_path).read_text()
        start = text.index("static int\nreload_reg_free_for_value_p (regno")
        end = text.index("\n}\n", start) + 3
        predicate = text[start:end]
        self.assertIn("i != reloadnum", predicate)
        self.assertIn("TEST_HARD_REG_BIT (rac2_reload_unavailable, regno)", predicate)
        harness = (ROOT / "tests/fixtures/reload_lifetime_control.c").read_text()
        declaration, cases = harness.split("/* INSERT_ACTUAL_PREDICATE */")
        variants = {
            "current": (predicate, 0),
            "mutable_set": (predicate.replace("(rac2_reload_unavailable, regno)",
                                               "(reload_reg_used, regno)"), 40),
            "no_exclusion": (predicate.replace("TEST_HARD_REG_BIT (rac2_reload_unavailable, regno)",
                                                "0"), 41),
        }
        with tempfile.TemporaryDirectory() as directory:
            root = Path(directory)
            for name, (body, expected) in variants.items():
                with self.subTest(name=name):
                    source, exe = root / (name + ".c"), root / name
                    source.write_text(declaration + body + cases)
                    subprocess.run([compiler, "-std=gnu89", str(source), "-o", str(exe)],
                                   capture_output=True, text=True, check=True)
                    self.assertEqual(subprocess.run([str(exe)]).returncode, expected)


def instructions(body: str) -> list[str]:
    lines = (line.split("#")[0].strip() for line in body.splitlines())
    return [line for line in lines if line and not line.startswith(".") and not line.endswith(":")]


class CompilerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools"))
        if not all((compiler / name).is_file() for name in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built cpp, cc1 and as")
            raise unittest.SkipTest("EE compiler absent; tools/compiler/build.sh runs these checks after building it")
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            source = root / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/reload_reg_used_guard.c").read_bytes())
            with (root / "input.i").open("w") as out:
                subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
            asm = root / "input.s"
            subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                            str(root / "input.i"), "-o", str(asm)], check=True)
            subprocess.run([str(compiler / "as"), "-o", str(root / "input.o"), str(asm)], check=True)
            text = asm.read_text()
        cls.code = {name: instructions(re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, text).group())
                    for name in NAMES}

    def before_slt(self, name):
        code = self.code[name]
        k = next(k for k, line in enumerate(code) if line.startswith("slt\t$2,") and line.endswith(",128"))
        return code[k - 4:k + 1]

    def test_the_count_is_reloaded_after_its_output_reload(self):
        # Without the test reload inherits $2 from the increment: addu $2,$2,1; sw $2; slt $2,$2,128.
        self.assertEqual(self.before_slt("refused"),
                         ["addu\t$2,$2,1", "sw\t$2,520($sp)", "sw\t$0,152($4)", "lw\t$3,520($sp)",
                          "slt\t$2,$3,128"])

    def test_a_spill_register_of_the_insn_is_still_inherited(self):
        self.assertEqual(self.before_slt("inherited")[-3:],
                         ["addu\t$3,$sp,$2", "sw\t$5,520($sp)", "slt\t$2,$5,128"])


if __name__ == "__main__":
    unittest.main()
