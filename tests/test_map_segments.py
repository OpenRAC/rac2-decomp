"""Segment boundaries are read from a splat config as addresses and names only."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import map_segments  # noqa: E402

YAML = """segments:
  - name: cod
    type: code
    subsegments:
      - [0x000000, textbin, cod/000000]
      - [0x015180, c, cod/015180h] # head
      - [0x0152C0, lib, libgcc, r5900_memcmp_strcmp] # libc
  - name: data
    subsegments:
      - [0x138B80, c, data/x]
"""


class BoundaryTests(unittest.TestCase):
    def test_code_subsegments_become_v2_addresses(self):
        with tempfile.TemporaryDirectory() as tmp:
            path = Path(tmp) / "c.yaml"
            path.write_text(YAML, encoding="utf-8")
            rows = map_segments.boundaries(path)
        self.assertEqual(rows, [(0x115200, "c", "015180h"), (0x115340, "lib", "r5900_memcmp_strcmp")])


if __name__ == "__main__":
    unittest.main()
