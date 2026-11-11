"""The opt-in -frac2-gcse-hash-111: transformer drift and insertion points."""
import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("gcse_hash_111",
    ROOT / "tools/compiler/transformers/gcse_hash_111.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {
            root / "gcse.c": "a\n" + transformer.HASH_OLD + "\nb\n",
            root / "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
            root / "flags.h": transformer.DECLARATION_OLD,
        }
        files.update(override)
        for path, contents in files.items():
            path.write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            self.assertIn("flag_rac2_gcse_hash_111", (root / "gcse.c").read_text())
            self.assertIn("flag_rac2_gcse_hash_111", (root / "toplev.c").read_text())
            self.assertIn("flag_rac2_gcse_hash_111", (root / "flags.h").read_text())

    def test_already_applied_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            with self.assertRaises(ValueError):
                transformer.patch(root)


if __name__ == "__main__":
    unittest.main()
