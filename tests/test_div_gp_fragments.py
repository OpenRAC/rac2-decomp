"""Division padding counts a chosen GP expansion once, not both alternatives."""
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


class GPFragmentTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")).resolve()
        assembler = compiler / "as"
        if not assembler.is_file():
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built as")
            raise unittest.SkipTest("EE assembler absent")
        cls.bodies = {}
        with tempfile.TemporaryDirectory() as d:
            output = Path(d) / "authored.o"
            try:
                r = subprocess.run([str(assembler), "-G8", "-o", str(output),
                                    str(ROOT / "tests/fixtures/div_gp_fragments.s")],
                                   capture_output=True, text=True)
            except OSError:
                if "RAC2_COMPILER_ROOT" in os.environ:
                    raise
                raise unittest.SkipTest("EE assembler not runnable on this host")
            if r.returncode:
                raise RuntimeError(r.stderr)
            obj = elf.read_object(output)
            for symbol in obj["symbols"]:
                if symbol["size"] and 0 < symbol["section"] < len(obj["sections"]):
                    data = obj["sections"][symbol["section"]]["data"]
                    cls.bodies[symbol["name"]] = [w[0] for w in struct.iter_unpack(
                        "<I", data[symbol["value"]:symbol["value"] + symbol["size"]])]

    def shape(self, name):
        result = []
        for w in self.bodies[name]:
            if w == 0:
                result.append("nop")
            elif w >> 26 == 0x31:
                result.append("gp-load" if (w >> 21) & 31 == 28 else "load")
            elif w >> 26 == 0x0f:
                result.append("lui")
            elif w & 0xFFE0003F == 0x46000003:
                result.append("div.s")
            else:
                result.append(hex(w))
        return result

    def test_explicit_gp_has_one_padding_slot(self):
        self.assertEqual(self.shape("direct_gp"), ["gp-load", "nop", "div.s"])

    def test_sized_gp_macro_has_the_same_padding(self):
        self.assertEqual(self.shape("small_gp"), ["gp-load", "nop", "div.s"])

    def test_absolute_pair_already_spans_two_slots(self):
        self.assertEqual(self.shape("large_absolute"), ["lui", "load", "div.s"])

    def test_two_gp_macros_do_not_add_padding(self):
        self.assertEqual(self.shape("two_gp"), ["gp-load", "gp-load", "div.s"])

    def test_word_after_gp_contributes_one_slot(self):
        self.assertEqual(self.shape("gp_word"), ["gp-load", "nop", "div.s"])

    def test_unknown_symbol_is_not_assumed_short(self):
        self.assertEqual(self.shape("forward_absolute"), ["lui", "load", "div.s"])


if __name__ == "__main__":
    unittest.main()
