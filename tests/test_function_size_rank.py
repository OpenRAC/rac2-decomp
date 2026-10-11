"""Boundary discovery in the size ranking tool, on synthetic code only."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import function_size_rank as rank  # noqa: E402

BASE = 0x00100000
ADDIU_SP = 0x27BDFFE0
JR_RA = 0x03E00008


class DiscoverTests(unittest.TestCase):
    def test_functions_split_after_delay_slot_and_padding_is_trimmed(self):
        words = [ADDIU_SP, 0x1, JR_RA, 0, 0, 0, ADDIU_SP, JR_RA, 0x2, 0]
        starts = rank.discover_starts([(BASE, words)], {})
        self.assertEqual(starts, [BASE, BASE + 6 * 4])
        self.assertEqual(rank.trim_size(words, BASE, BASE, BASE + 24), 16)
        self.assertEqual(rank.trim_size(words, BASE, BASE + 24, BASE + 40), 12)

    def test_jal_targets_and_function_symbols_are_starts_data_symbols_are_not(self):
        jal = (3 << 26) | ((BASE + 8) >> 2)
        words = [jal, 0, 0x1, JR_RA, 0]
        syms = {BASE + 4: ("g_table", None)}
        self.assertTrue(rank.is_function("f", "type:func size:0x8"))
        self.assertFalse(rank.is_function("g_table", ""))
        self.assertIn(BASE + 8, rank.discover_starts([(BASE, words)], syms))

    def test_categories(self):
        f = lambda n: rank.Function(0, n, "x", "todo").category
        self.assertEqual((f(100), f(101), f(500), f(501)), ("small", "medium", "medium", "big"))


if __name__ == "__main__":
    unittest.main()
