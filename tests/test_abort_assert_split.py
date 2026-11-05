"""Authored catalogue controls: adjacent noreturn bodies need independent entries."""
import hashlib
import struct
import sys
import unittest
from pathlib import Path
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "tools"))
import levels


class AbortAssertSplit(unittest.TestCase):
    def setUp(self):
        self.base = 0x120000
        self.first, self.second = "func_00115E28", "func_00115E38"
        self.rows = [(self.first, self.base, 64), ("func_00131CA8", 0x130000, 16),
                     ("func_00115CF0", 0x140000, 16)]
        # Authored instructions, not a retail dump. Relocations still need named
        # callee checks because cross_identity deliberately masks their targets.
        words = [0x24020007] * 16
        words[2] = 0x0C000000 | (0x130000 >> 2)
        words[12] = 0x0C000000 | (0x140000 >> 2)
        words[14] = 0x0C000000 | (self.base >> 2)
        self.body = struct.pack("<16I", *words)
        self.identity = hashlib.sha256(levels.cross_identity(self.body)).hexdigest()
        self.memory = {self.base: self.body}
        for i, (name, offset) in enumerate((("func_003358A0", 0x2C),
                                           ("func_00336DB8", 0x40),
                                           ("func_00336E40", 0x74),
                                           ("func_0034EE78", 0x68))):
            address = 0x150000 + i * 0x100
            self.rows.append((name, address, 0x80))
            self.memory[address + offset] = struct.pack("<I", 0x0C000000 | ((self.base + 16) >> 2))

    def run_split(self, rows=None):
        def read(address, size):
            return self.memory[address][:size]
        with patch.object(levels, "boot_bytes", side_effect=read), \
             patch.object(levels, "ABORT_ASSERT_IDENTITY", self.identity):
            return levels.split_boot_rows(self.rows if rows is None else rows)

    def test_preserves_end_unrelated_rows_and_replay(self):
        fixed = self.run_split()
        self.assertEqual(fixed[:2], [(self.first, self.base, 16),
                                    (self.second, self.base + 16, 48)])
        self.assertEqual(fixed[2:], self.rows[1:])
        self.assertEqual(sum(n for _, _, n in fixed), sum(n for _, _, n in self.rows))
        self.assertEqual(self.run_split(fixed), fixed)

    def test_changed_or_truncated_complete_body(self):
        for body in (self.body[:-4], bytes([self.body[0] ^ 1]) + self.body[1:]):
            with self.subTest(length=len(body)):
                self.memory[self.base] = body
                with self.assertRaisesRegex(ValueError, "body differs"):
                    self.run_split()

    def test_relocated_call_still_needs_the_named_callee(self):
        for offset in (8, 48, 56):
            with self.subTest(offset=offset):
                body = bytearray(self.body)
                struct.pack_into("<I", body, offset, 0x0C000000 | (0x160000 >> 2))
                self.memory[self.base] = bytes(body)
                with self.assertRaisesRegex(ValueError, "callee differs"):
                    self.run_split()

    def test_each_incoming_entry_witness_is_required(self):
        for address in list(self.memory)[1:]:
            with self.subTest(address=address):
                saved = self.memory[address]
                self.memory[address] = struct.pack("<I", 0x0C000000 | (self.base >> 2))
                with self.assertRaisesRegex(ValueError, "witness differs"):
                    self.run_split()
                self.memory[address] = saved

    def test_malformed_or_overlapping_catalogue_is_rejected(self):
        cases = [self.rows + [self.rows[0]],
                 [(self.first, self.base, 60)] + self.rows[1:],
                 [(self.first, self.base, 16)] + self.rows[1:],
                 self.rows + [(self.second, self.base + 16, 48)],
                 self.rows + [("other", self.base + 20, 4)],
                 [(self.second, self.base + 16, 48)]]
        for rows in cases:
            with self.subTest(rows=rows), self.assertRaises(ValueError):
                self.run_split(rows)

    def test_short_or_missing_caller_is_rejected(self):
        for rows in (self.rows[:-1], self.rows[:-1] + [(self.rows[-1][0], self.rows[-1][1], 4)]):
            with self.subTest(rows=rows), self.assertRaisesRegex(ValueError, "caller extent"):
                self.run_split(rows)

    def test_unrelated_catalogue_is_untouched(self):
        rows = [("other", 0x170000, 8)]
        self.assertEqual(self.run_split(rows), rows)


if __name__ == "__main__":
    unittest.main()
