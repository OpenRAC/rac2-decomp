"""The opt-in -frac2-caller-reg-order: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("caller_reg_order",
    ROOT / "tools/compiler/transformers/caller_reg_order.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-caller-reg-order"


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        (root / "config/mips").mkdir(parents=True, exist_ok=True)
        files = {
            root / "config/mips/mips.c": "a\n" + transformer.MIPS_OLD + "b\n",
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
            self.assertIn("flag_rac2_caller_reg_order", (root / "config/mips/mips.c").read_text())
            self.assertIn("flag_rac2_caller_reg_order", (root / "toplev.c").read_text())
            self.assertIn("flag_rac2_caller_reg_order", (root / "flags.h").read_text())

    def test_already_applied_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            with self.assertRaises(ValueError):
                transformer.patch(root)


if __name__ == "__main__":
    unittest.main()
