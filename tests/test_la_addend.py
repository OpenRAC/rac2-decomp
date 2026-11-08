"""Authored, asset-free controls for the opt-in `--r5900-la-addend=sn` profile.

SN's assembler builds `la sym+addend` as the absolute lui/addiu pair even for a
gp-relative symbol; the bare symbol keeps the single $gp addiu, and loads and
stores keep $gp at any addend. The default and explicit `gnu` profiles keep the
GNU $gp form. The cases are authored here; no game bytes are used.

Ordinary CI skips when the assembler is absent. Compiler qualification must run
with RAC2_COMPILER_ROOT set to the new tools; then a missing assembler is an error.
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
import elf

GPREL, HI16, LO16 = 7, 5, 6
SOURCE = """\
\t.extern\tS, 32
\t.sdata
\t.globl\tD
D:\t.word\t1, 2, 3, 4
\t.text
\t.globl\tf
\t.ent\tf
f:
\tla\t$2,S
\tla\t$3,S+8
\tla\t$4,S-4
\tlw\t$5,S+8
\tsw\t$5,S+28
\tla\t$6,D
\tla\t$7,D+4
\tlw\t$8,D+4
\tla\t$9,S+0
\tj\t$31
\t.end\tf
"""
# (opcode/rs/rt field of each word, relocation type) for the macros above.
ADDIU, LW, SW, LUI = 0x09, 0x23, 0x2B, 0x0F
GNU = [(ADDIU, 28, 2, GPREL), (ADDIU, 28, 3, GPREL), (LUI, 0, 4, HI16), (ADDIU, 4, 4, LO16),
       (LW, 28, 5, GPREL), (SW, 28, 5, GPREL), (ADDIU, 28, 6, GPREL), (ADDIU, 28, 7, GPREL),
       (LW, 28, 8, GPREL), (ADDIU, 28, 9, GPREL)]
SN = [(ADDIU, 28, 2, GPREL), (LUI, 0, 3, HI16), (ADDIU, 3, 3, LO16), (LUI, 0, 4, HI16),
      (ADDIU, 4, 4, LO16), (LW, 28, 5, GPREL), (SW, 28, 5, GPREL), (ADDIU, 28, 6, GPREL),
      (LUI, 0, 7, HI16), (ADDIU, 7, 7, LO16), (LW, 28, 8, GPREL), (ADDIU, 28, 9, GPREL)]


class LaAddendProfile(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")).resolve()
        cls.assembler = compiler / "as"
        if not cls.assembler.is_file():
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built as")
            raise unittest.SkipTest("EE assembler absent; compiler build must run with RAC2_COMPILER_ROOT")

    def assemble(self, *options):
        with tempfile.TemporaryDirectory() as directory:
            source, output = Path(directory) / "t.s", Path(directory) / "t.o"
            source.write_text(SOURCE)
            subprocess.run([str(self.assembler), "-G64", *options, "-o", str(output), str(source)],
                           check=True, capture_output=True)
            obj = elf.read_object(output)
        index = next(i for i, s in enumerate(obj["sections"]) if s["name"] == ".text")
        data = obj["sections"][index]["data"]
        relocs = {o: t for o, t, _ in obj["relocations"].get(index, [])}
        words = [struct.unpack_from("<I", data, at)[0] for at in range(0, len(data), 4)]
        # drop the trailing jr $ra and its delay slot
        return [(w >> 26, (w >> 21) & 31, (w >> 16) & 31, relocs.get(4 * k))
                for k, w in enumerate(words[:-2])]

    def test_default_and_gnu_keep_the_gp_form(self):
        self.assertEqual(self.assemble(), GNU)
        self.assertEqual(self.assemble("--r5900-la-addend=gnu"), GNU)

    def test_sn_uses_the_absolute_pair_only_for_la_with_an_addend(self):
        self.assertEqual(self.assemble("--r5900-la-addend=sn"), SN)

    def test_bad_or_missing_profile_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            source, output = Path(directory) / "t.s", Path(directory) / "t.o"
            source.write_text(".text\nnop\n")
            for option in ("--r5900-la-addend=typo", "--r5900-la-addend=", "--r5900-la-addend"):
                with self.subTest(option=option):
                    result = subprocess.run([str(self.assembler), "-o", str(output), str(source), option],
                                            capture_output=True, text=True)
                    self.assertNotEqual(result.returncode, 0)


if __name__ == "__main__":
    unittest.main()
