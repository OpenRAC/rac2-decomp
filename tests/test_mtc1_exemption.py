"""The assembler's transfer-delay exemption (tools/compiler/transformers/restrict_mtc1_exemption.py).

Retail drops the mtc1 hazard nop for `mtc1 a0,f0; cvt.s.w f0,f0' and `mtc1 zero,f0;
c.lt.s f12,f0' only where gas has forgotten its history (prev_insn_valid clear: a section
start, and with -ffunction-sections in practice a function start). Behind a branch delay
slot the assembler fills with a nop, the nop stays, and so it does behind an unconditional
branch (b, j, jal, jr), after which gas empties both history slots without forgetting it.
Two known limits stay exempt: `b; .align 3; L: mtc1' and `b; .set noreorder; .set reorder;
L: mtc1', which cc1 never emits. The test needs the newly built assembler: it skips without
it, and RAC2_COMPILER_ROOT naming a directory without it is an error.
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
            subprocess.run([str(compiler / "as"), "--r5900-swap-branch-slots", "-o", str(obj),
                            str(ROOT / "tests/fixtures/mtc1_exemption.s")], check=True)
            cls.swapped = functions(obj)

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

    def test_after_an_unconditional_branch_the_nop_stays(self):
        names = ("compare_after_b", "compare_after_swapped_b", "compare_after_j",
                 "compare_after_jal", "convert_after_jr", "compare_after_aligned_label")
        for text, profile in ((self.text, "default"), (self.swapped, "swapped slots")):
            for name in names:
                with self.subTest(case=name, profile=profile):
                    words = text[name]
                    index = next(i for i, w in enumerate(words) if w >> 21 == MTC1)
                    self.assertGreater(index, 0)
                    self.assertEqual(words[index + 1], NOP)     # the hazard nop
                    self.assertNotEqual(words[index + 2], NOP)  # then the reader

    def test_the_unconditional_branch_slots(self):
        b = 0x10000000                                    # beq $0,$0 (b), offset masked
        words = self.text["compare_after_b"]              # lw; bne; nop; b; nop; mtc1
        self.assertEqual(words[3] & 0xFFFF0000, b)
        self.assertEqual(words[4], NOP)
        self.assertEqual(words[5] >> 21, MTC1)
        words = self.text["compare_after_swapped_b"]      # this profile never swaps
        self.assertEqual(words[1] & 0xFFFF0000, b)
        self.assertEqual(words[2], NOP)
        self.assertEqual(words[3] >> 21, MTC1)
        words = self.swapped["compare_after_swapped_b"]   # b; addiu (the slot); mtc1
        self.assertEqual(words[0] & 0xFFFF0000, b)
        self.assertEqual(words[1] >> 26, 9)
        self.assertEqual(words[2] >> 21, MTC1)
        for name in ("compare_after_j", "compare_after_jal", "convert_after_jr"):
            with self.subTest(case=name):
                self.assertEqual(self.text[name][1], NOP)    # the branch slot
                self.assertEqual(self.text[name][2] >> 21, MTC1)
        words = self.text["compare_after_aligned_label"]  # addiu; b; nop; .p2align nop; mtc1
        self.assertEqual(words[3], NOP)
        self.assertEqual(words[4] >> 21, MTC1)

    def test_function_start_is_exempt_in_both_profiles(self):
        for name in ("convert_entry", "compare_entry"):
            with self.subTest(case=name):
                self.assertEqual(self.swapped[name][0] >> 21, MTC1)
                self.assertNotEqual(self.swapped[name][1], NOP)

    def test_known_limits_stay_exempt(self):
        # .align and .set reorder call mips_no_prev_insn, which forgets the history; cc1 gives
        # code labels .p2align (compare_after_aligned_label) and never writes these forms.
        b = 0x10000000
        for text, profile, start in ((self.text, "default", 1), (self.swapped, "swapped slots", 0)):
            for name in ("limit_after_align", "limit_after_set_reorder"):
                with self.subTest(case=name, profile=profile):
                    words = text[name]
                    self.assertEqual(words[start] & 0xFFFF0000, b)
                    if start:                                  # addiu; b; nop (the slot)
                        self.assertEqual(words[2], NOP)
                    else:                                      # b; addiu (the slot)
                        self.assertEqual(words[1] >> 26, 9)
                    index = next(i for i, w in enumerate(words) if w >> 21 == MTC1)
                    self.assertEqual(words[index + 1], 0x46006034)  # c.lt.s $f12,$f0: no nop

    def test_other_registers_keep_the_nop(self):
        self.assertEqual(self.word_after_mtc1("other_register"), NOP)


if __name__ == "__main__":
    unittest.main()
