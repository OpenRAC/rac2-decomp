"""Carried names and Ghidra file anchors are structure-only rows."""
import re
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import transfer_names  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]


class CommittedRowTests(unittest.TestCase):
    def test_carried_names_follow_the_marker_and_are_unique(self):
        text = (ROOT / "symbol_addrs/usa/symbol_addrs.txt").read_text(encoding="utf-8").splitlines()
        rows = text[text.index(transfer_names.MARKER) + 1:]
        parsed = [transfer_names.SYM.match(r) for r in rows if r.strip()]
        self.assertTrue(parsed and all(parsed))
        names = [m.group(1) for m in parsed]
        addresses = [int(m.group(2), 16) for m in parsed]
        self.assertEqual(len(names), len(set(names)))
        self.assertEqual(len(addresses), len(set(addresses)))
        self.assertFalse(any(re.match(r"(func|FUN)_", n) for n in names))

    def test_anchor_rows_are_addresses_and_file_names(self):
        rows = [l.split("\t") for l in (ROOT / "config/segments/ntsc-u-file-anchors.tsv").read_text(encoding="utf-8").splitlines()
                if not l.startswith("#")]
        self.assertTrue(rows)
        for function, name, string in rows:
            self.assertTrue(function.startswith("0x") and string.startswith("0x"))
            self.assertRegex(name, r"^[A-Za-z0-9_/]+\.(c|cpp)$")


if __name__ == "__main__":
    unittest.main()


class HintRowTests(unittest.TestCase):
    def test_ghidra_hint_rows_hold_names_not_messages(self):
        rows = [l.split("\t") for l in (ROOT / "config/datamine/ntsc-u-name-hints-ghidra.tsv").read_text(encoding="utf-8").splitlines()
                if not l.startswith("#")]
        self.assertTrue(rows)
        for program, function, token, string, form in rows:
            self.assertTrue(function.startswith("0x") and string.startswith("0x"))
            self.assertRegex(token, r"^[A-Za-z0-9_]+$")
            self.assertIn(form, ("named", "mention"))


class DataNameTests(unittest.TestCase):
    def test_addresses_follow_lui_pairs_and_gp(self):
        import transfer_data_names as td
        lui_t0 = 0x3C080012  # lui t0,0x12
        addiu_t0 = 0x25080010  # addiu t0,t0,0x10
        lw_gp = 0x8F890020  # lw t1,0x20(gp)
        self.assertEqual(td.addresses([lui_t0, addiu_t0, lw_gp]), [0x120010, td.GP + 0x20])

    def test_carried_data_rows_are_unique(self):
        import transfer_data_names as td
        lines = (ROOT / "symbol_addrs/usa/symbol_addrs.txt").read_text(encoding="utf-8").splitlines()
        rows = [transfer_names.SYM.match(l) for l in lines[lines.index(td.MARKER) + 1:] if l.strip()]
        self.assertTrue(rows and all(rows))
        self.assertEqual(len({m.group(1) for m in rows}), len(rows))
        self.assertEqual(len({m.group(2).lower() for m in rows}), len(rows))
