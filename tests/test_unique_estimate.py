"""The v1.01 deduplicated estimate masks address fields only and never adds credit by itself."""
import sys
import unittest
from pathlib import Path

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

    def test_committed_estimate_is_heuristic_and_builds(self):
        catalog = ue.json.loads(ue.ESTIMATE.read_text(encoding="utf-8"))
        self.assertTrue(catalog["heuristic"])
        report = ue.build_report(catalog)
        total = int(report["measures"]["totalCode"])
        self.assertLess(total, sum(r["physical_code_bytes"] for r in catalog["images"].values()))
        self.assertLessEqual(int(report["measures"]["matchedCode"]), total)


if __name__ == "__main__":
    unittest.main()
