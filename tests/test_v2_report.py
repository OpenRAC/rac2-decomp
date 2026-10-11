"""The v2.00 decomp.dev report counts matched functions once and level code de-duplicated."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import v2_report  # noqa: E402


class ReportTests(unittest.TestCase):
    catalog = {"functions": [[0x100, 16, "a"], [0x110, 32, "b"]], "boot_data_sections": {".data": 64},
               "levels": {"1_x": {"text_bytes": 1000, "new_unique_bytes": 200}}}

    def test_totals_and_units(self):
        report = v2_report.build_report(self.catalog, [])
        m = report["measures"]
        self.assertEqual((m["totalCode"], m["totalData"], m["matchedCode"], m["totalUnits"]), ("248", "64", "0", 4))
        self.assertEqual([c["id"] for c in report["categories"]], ["boot", "levels"])

    def test_match_must_agree_with_catalogue(self):
        bad = {"symbol": "a", "address": 0x100, "size": 8, "source": "x.c", "source_sha256": "0" * 64}
        with self.assertRaises(SystemExit):
            v2_report.build_report(self.catalog, [bad])

    def test_committed_catalogue_and_matches_build(self):
        catalog = v2_report.json.loads(v2_report.CATALOG.read_text(encoding="utf-8"))
        matches = v2_report.json.loads(v2_report.MATCHES.read_text(encoding="utf-8"))["matches"]
        report = v2_report.build_report(catalog, matches)
        self.assertEqual(report["measures"]["matchedCode"], "0")  # candidates never earn credit
        self.assertLess(int(report["measures"]["totalCode"]), 6_000_000)


if __name__ == "__main__":
    unittest.main()
