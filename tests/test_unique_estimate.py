"""The destructive structural estimate must never supply matching credit."""
import sys
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import unique_estimate as ue  # noqa: E402

LUI_T0 = 0x3C080000 | 0x0012
ADDIU_T0 = 0x25080000 | 0x3456  # addiu t0,t0,imm
LW_T1_T0 = 0x8D090000 | 0x0010  # lw t1,0x10(t0)
LI_T1 = 0x24090000 | 0x0005  # addiu t1,zero,5


class NormaliseTests(unittest.TestCase):
    def test_address_pair_and_offset_are_masked(self):
        a = ue.normalise([LUI_T0, ADDIU_T0, LW_T1_T0])
        b = ue.normalise([LUI_T0 + 1, ADDIU_T0 + 2, LW_T1_T0 + 4])
        self.assertEqual(a, b)

    def test_plain_constants_stay_distinct(self):
        self.assertNotEqual(ue.normalise([LI_T1]), ue.normalise([LI_T1 + 1]))

    def test_non_address_offsets_stay_distinct(self):
        lw_sp = 0x8FA90000 | 0x10
        self.assertNotEqual(ue.normalise([lw_sp]), ue.normalise([lw_sp + 4]))

    def test_jump_targets_are_masked(self):
        self.assertEqual(ue.normalise([0x0C000123]), ue.normalise([0x0C000456]))

    def test_float_constants_demonstrate_destructive_mask(self):
        # lui t0,0x3f80 / 0x4000; mtc1 t0,f12 loads 1.0 / 2.0, not an address.
        self.assertEqual(ue.digest([0x3C083F80, 0x44886000]),
                         ue.digest([0x3C084000, 0x44886000]))

    def test_legacy_credit_flags_are_ignored_everywhere(self):
        catalog = ue.json.loads(ue.ESTIMATE.read_text(encoding="utf-8"))
        for rows in [catalog["functions"]["boot"],
                     *catalog["functions"]["shared"].values(),
                     *catalog["functions"]["specific"].values()]:
            for row in rows:
                row[2] = 1  # A stale or candidate-only snapshot must never become accepted credit.
        report = ue.build_report(catalog)
        for item in [report, *report["units"], *report["categories"]]:
            self.assertEqual(int(item["measures"]["matchedCode"]), 0)
            self.assertEqual(int(item["measures"]["completeCode"]), 0)
            self.assertEqual(item["measures"]["matchedFunctions"], 0)
            self.assertEqual(item["measures"]["completeUnits"], 0)
        self.assertEqual(report["metadata"]["matchingCredit"], "none")
        self.assertTrue(all(not u["metadata"]["complete"] for u in report["units"]))
        self.assertTrue(all(f["fuzzyMatchPercent"] == 0 for u in report["units"] for f in u["functions"]))

    def test_catalog_never_reads_candidate_or_integration_credit(self):
        data = b"synthetic reference"
        pinned = ue.hashlib.sha256(data).hexdigest()
        region = SimpleNamespace(serial="SCUS_972.68", target={"boot": {"sha256": pinned}},
                                 overlays={"levels": []})
        with patch.object(ue.regions, "load", return_value=region), \
                patch.object(Path, "read_bytes", return_value=data), \
                patch.object(Path, "read_text", side_effect=AssertionError("proof input read")), \
                patch.object(ue, "code_words", return_value={0x100: [0x03E00008, 0]}), \
                patch.object(ue, "extents", return_value=[(0x100, 8)]):
            catalog = ue.build_catalog(Path("synthetic"), Path("boot.elf"))
        self.assertEqual(catalog["functions"]["boot"], [[0x100, 8, 0]])
        self.assertEqual(catalog["matching_credit"], "none")

    def test_catalog_rejects_wrong_overlay_reference(self):
        data = b"synthetic boot"
        pinned = ue.hashlib.sha256(data).hexdigest()
        region = SimpleNamespace(serial="SCUS_972.68", target={"boot": {"sha256": pinned}},
                                 overlays={"levels": [{"level": "1_test", "sha256": "0" * 64}]})
        with patch.object(ue.regions, "load", return_value=region), \
                patch.object(Path, "read_bytes", return_value=data), \
                patch.object(ue, "code_words", return_value={}):
            with self.assertRaisesRegex(SystemExit, "Overlay 1_test is not the pinned"):
                ue.build_catalog(Path("synthetic"), Path("boot.elf"))

    def test_committed_estimate_is_heuristic_and_builds(self):
        catalog = ue.json.loads(ue.ESTIMATE.read_text(encoding="utf-8"))
        self.assertTrue(catalog["heuristic"])
        report = ue.build_report(catalog)
        total = int(report["measures"]["totalCode"])
        self.assertLess(total, sum(catalog["physical_code_bytes"].values()))
        self.assertEqual({c["id"] for c in report["categories"]} >= {"executable", "core", "game", "level_code", "common", "levels"}, True)
        self.assertTrue(any(u["name"].startswith("core/") for u in report["units"]))
        self.assertEqual(int(report["measures"]["matchedCode"]), 0)
        self.assertEqual(catalog["matching_credit"], "none")
        self.assertTrue(all(row[2] == 0 for rows in [catalog["functions"]["boot"],
                             *catalog["functions"]["shared"].values(), *catalog["functions"]["specific"].values()]
                            for row in rows))


if __name__ == "__main__":
    unittest.main()
