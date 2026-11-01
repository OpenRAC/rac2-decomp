"""reorg's redundant-insn search stops at a division guard or volatile asm: transformer drift and EE compiler output."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("trap_redundant_barrier",
    ROOT / "tools/compiler/transformers/trap_redundant_barrier.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

FUNCTIONS = ("guarded", "plain", "copied", "stored")


def function_text(asm: str, name: str) -> str:
    return re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()


def last_jump_lands_on_restore(text: str) -> bool:
    """Whether the function's last `b` goes to a label directly above the restore of $16."""
    lines = [l.strip() for l in text.splitlines()]
    label = [l for l in lines if l.startswith("b\t$L")][-1].split()[1]
    at = lines.index(label + ":")
    following = next(l for l in lines[at + 1:] if not l.endswith(":"))
    return following.startswith("ld\t$16,")


def first_branch_slot(text: str) -> str:
    """The instruction in the delay slot of the function's first conditional `bne`."""
    lines = [l.strip() for l in text.splitlines()]
    i = next(k for k, l in enumerate(lines) if l.startswith("bne\t"))
    return lines[i + 1].split("#")[0].strip()


class TransformerTests(unittest.TestCase):
    def test_the_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            reorg = Path(d) / "reorg.c"
            reorg.write_text("before\n" + transformer.SCAN_OLD + "\nafter\n")
            transformer.patch(reorg)
            text = reorg.read_text()
            self.assertIn("      if (GET_CODE (trial) == INSN\n"
                          "\t  && (GET_CODE (pat) == TRAP_IF\n"
                          "\t      || (GET_CODE (pat) != SEQUENCE && volatile_insn_p (pat))))\n"
                          "\treturn 0;\n", text)
            self.assertNotIn("flag_rac2", text)
            with self.assertRaisesRegex(ValueError, "redundant_insn"):
                transformer.patch(reorg)

    def test_source_drift_is_rejected_without_writing(self):
        with tempfile.TemporaryDirectory() as d:
            reorg = Path(d) / "reorg.c"
            reorg.write_text("unexpected source\n")
            with self.assertRaisesRegex(ValueError, "found 0"):
                transformer.patch(reorg)
            self.assertEqual(reorg.read_text(), "unexpected source\n")


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
            source.write_bytes((ROOT / "tests/fixtures/trap_redundant_barrier.c").read_bytes())
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            asm = root / "input.s"
            subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G8", "-ffunction-sections",
                            str(root / "input.i"), "-o", str(asm)], check=True)
            subprocess.run([str(compiler / "as"), "-o", str(root / "input.o"), str(asm)], check=True)
            text = asm.read_text()
            cls.outputs = {name: function_text(text, name) for name in FUNCTIONS}

    def test_the_reload_across_a_guard_fills_the_slot(self):
        # This tree's search found the load above the `% 3' guard, dropped the target's
        # reload as redundant and stole the `li $2,5' after it.
        self.assertIn("break\t7", self.outputs["guarded"])
        self.assertRegex(first_branch_slot(self.outputs["guarded"]), r"^lw\t\$\d+,ticks$")

    def test_a_restore_is_not_redundant_across_a_volatile_asm(self):
        self.assertTrue(last_jump_lands_on_restore(self.outputs["copied"]), self.outputs["copied"])

    def test_without_an_asm_the_restore_is_skipped(self):
        self.assertFalse(last_jump_lands_on_restore(self.outputs["stored"]), self.outputs["stored"])

    def test_without_a_guard_the_reload_is_dropped(self):
        self.assertNotIn("break\t7", self.outputs["plain"])
        self.assertEqual(first_branch_slot(self.outputs["plain"]), "li\t$2,5")


if __name__ == "__main__":
    unittest.main()
