"""The opt-in -frac2-sched-store-offset: transformer drift and insertion points."""
import importlib.util
from pathlib import Path
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("sched_store_offset",
    ROOT / "tools/compiler/transformers/sched_store_offset.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {
            root / "haifa-sched.c": "a\n" + transformer.RANK_OLD + "\n" + transformer.TIE_OLD + "\nb\n",
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
            self.assertIn("flag_rac2_sched_store_offset", (root / "haifa-sched.c").read_text())
            self.assertIn("flag_rac2_sched_store_offset", (root / "toplev.c").read_text())
            self.assertIn("flag_rac2_sched_store_offset", (root / "flags.h").read_text())

    def test_already_applied_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            with self.assertRaises(ValueError):
                transformer.patch(root)


if __name__ == "__main__":
    unittest.main()
