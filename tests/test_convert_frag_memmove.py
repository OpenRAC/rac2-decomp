"""md_convert_frag moves an overlapping variant: transformer drift and assembler output."""
import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
TRANSFORMER = ROOT / "tools/compiler/transformers/convert_frag_memmove.py"
OLD = "\tmemcpy (fixptr - old, fixptr, new);\n"
NEW = "\tmemmove (fixptr - old, fixptr, new);\n"


def run(path: Path) -> subprocess.CompletedProcess:
    return subprocess.run([sys.executable, str(TRANSFORMER), str(path)], capture_output=True, text=True)


class TransformerTests(unittest.TestCase):
    def test_the_copy_becomes_a_move_once(self):
        with tempfile.TemporaryDirectory() as d:
            source = Path(d) / "tc-mips.c"
            source.write_text("  if (new > 0)\n" + OLD)
            self.assertEqual(run(source).returncode, 0)
            self.assertEqual(source.read_text(), "  if (new > 0)\n" + NEW)
            self.assertNotEqual(run(source).returncode, 0)

    def test_source_drift_is_rejected_without_writing(self):
        with tempfile.TemporaryDirectory() as d:
            source = Path(d) / "tc-mips.c"
            source.write_text(OLD + OLD)
            self.assertNotEqual(run(source).returncode, 0)
            self.assertEqual(source.read_text(), OLD + OLD)


class AssemblerOutputTests(unittest.TestCase):
    """A load with a base register and an unknown symbol keeps its lui (8-byte $gp form, 12-byte
    absolute form: the overlapping case)."""

    def test_base_register_load_keeps_its_lui(self):
        assembler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")) / "as"
        if not assembler.is_file():
            raise unittest.SkipTest("EE assembler absent; tools/compiler/build.sh builds it")
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / "t.s").write_text("\t.text\n\tlbu\t$2,sym+1($18)\n\tlw\t$3,sym+4($18)\n")
            subprocess.run([str(assembler), "-EL", "-G2", "-o", "t.o", "t.s"], cwd=root, check=True)
            data = (root / "t.o").read_bytes()
        shoff, = struct.unpack_from("<I", data, 0x20)
        entsize, count = struct.unpack_from("<HH", data, 0x2E)
        words = []
        for index in range(count):
            _, kind, flags, _, offset, size = struct.unpack_from("<IIIIII", data, shoff + index * entsize)
            if kind == 1 and flags & 4:
                words = list(struct.unpack_from("<%dI" % (size // 4), data, offset))
        # lui $2,%hi ; addu $2,$2,$18 ; lbu $2,%lo+1($2) ; lui $3,%hi ; addu $3,$3,$18 ; lw $3,%lo+4($3)
        self.assertEqual(words[:6], [0x3C020000, 0x00521021, 0x90420001,
                                     0x3C030000, 0x00721821, 0x8C630004])


if __name__ == "__main__":
    unittest.main()
