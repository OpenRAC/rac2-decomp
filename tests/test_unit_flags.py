"""Unit flag rows are read from case lines and stay addresses plus flags only."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import unit_flags  # noqa: E402

ROOT = Path(__file__).resolve().parents[1]


class FlagTests(unittest.TestCase):
    def test_case_line_is_parsed(self):
        m = unit_flags.CASE.match('  usa/text/1A8180) GFLAG="-G8"; CC1EXTRA="-fno-gcse -fno-strict-aliasing"; S136EXTRA="";')
        self.assertEqual((m.group(1), m.group(2), m.group(3)), ("1A8180", "-G8", "-fno-gcse -fno-strict-aliasing"))
        self.assertIsNone(unit_flags.CASE.match('  eu/text/16E7B8) GFLAG="-G8";'))

    def test_committed_rows(self):
        rows = [l.split("\t") for l in (ROOT / "config/segments/ntsc-u-unit-flags.tsv").read_text(encoding="utf-8").splitlines()
                if not l.startswith("#")]
        self.assertTrue(rows)
        for v1, v2, unit, g, extra in rows:
            self.assertTrue(v1.startswith("0x") and v2.startswith("0x"))
            self.assertRegex(g, r"^-G\d+$")
            self.assertTrue(all(f.startswith("-f") for f in extra.split()))


if __name__ == "__main__":
    unittest.main()
