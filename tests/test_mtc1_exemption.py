"""The assembler's transfer-delay exemption (tools/compiler/transformers/restrict_mtc1_exemption.py).

Retail drops the mtc1 hazard nop for `mtc1 a0,f0; cvt.s.w f0,f0' and `mtc1 zero,f0;
c.lt.s f12,f0' only when the mtc1 starts a function (empty history); behind a branch
delay slot the assembler fills with a nop, the nop stays. The test needs the newly built
assembler: it skips without it, and RAC2_COMPILER_ROOT naming a directory without it is an error.
"""
import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf  # noqa: E402

NOP = 0
MTC1 = 0x224                # word >> 21 of mtc1


def functions(path):
    obj = elf.read_object(path)
    return {s["name"][len(".text."):]: [w for (w,) in struct.iter_unpack("<I", s["data"])]
            for s in obj["sections"] if s["name"].startswith(".text.")}


class ExemptionTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools"))
        if not (compiler / "as").is_file():
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built as")
            raise unittest.SkipTest("EE assembler absent; tools/compiler/build.sh builds it")
        with tempfile.TemporaryDirectory() as d:
            obj = Path(d) / "out.o"
            subprocess.run([str(compiler / "as"), "-o", str(obj),
                            str(ROOT / "tests/fixtures/mtc1_exemption.s")], check=True)
            cls.text = functions(obj)

    def word_after_mtc1(self, name):
        words = self.text[name]
        index = next(i for i, w in enumerate(words) if w >> 21 == MTC1)
        return words[index + 1]

    def test_function_start_drops_the_nop(self):
        for name in ("convert_entry", "compare_entry"):
            with self.subTest(case=name):
                self.assertNotEqual(self.word_after_mtc1(name), NOP)
                self.assertEqual(self.text[name][0] >> 21, MTC1)

    def test_after_a_filled_branch_slot_the_nop_stays(self):
        for name in ("convert_after_branch", "compare_after_branch"):
            with self.subTest(case=name):
                words = self.text[name]
                self.assertEqual(words[3], NOP)            # the branch slot gas filled
                self.assertEqual(words[4] >> 21, MTC1)
                self.assertEqual(words[5], NOP)            # the hazard nop

    def test_other_registers_keep_the_nop(self):
        self.assertEqual(self.word_after_mtc1("other_register"), NOP)


if __name__ == "__main__":
    unittest.main()
