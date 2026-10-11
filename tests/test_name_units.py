"""rac1 name matches are unique on both sides and never name a unit from a single function."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import name_units_from_rac1 as nu  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]


class NameTests(unittest.TestCase):
    def test_unique_digests_drop_duplicates(self):
        rows = [(0x100, 8, "a"), (0x200, 8, "b"), (0x300, 8, "b")]
        self.assertEqual(nu.unique_digests(rows), {"a": 0x100})

    def test_committed_rows_are_sorted_and_address_only(self):
        lines = (ROOT / "config/segments/ntsc-u-rac1-matches.tsv").read_text(encoding="utf-8").splitlines()
        rows = [l.split("\t") for l in lines if not l.startswith("#")]
        self.assertTrue(rows)
        self.assertTrue(all(len(r) == 3 and r[0].startswith("0x") and r[2].startswith("0x") for r in rows))
        self.assertEqual([r[0] for r in rows], sorted(r[0] for r in rows))


if __name__ == "__main__":
    unittest.main()
