"""Private working data may live outside the repository or in its git-ignored extracted/ folder only."""
import sys
import tempfile
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import private_dir  # noqa: E402


class PrivateDirTests(unittest.TestCase):
    def test_outside_repository_is_allowed(self):
        with tempfile.TemporaryDirectory() as tmp:
            self.assertTrue(private_dir.allowed(Path(tmp)))

    def test_ignored_extracted_folder_is_allowed(self):
        self.assertTrue(private_dir.allowed(private_dir.EXTRACTED / "v101"))

    def test_other_repository_paths_are_rejected(self):
        for name in ("progress", "src", "build", "extracted-not"):
            self.assertFalse(private_dir.allowed(private_dir.ROOT / name))
        self.assertFalse(private_dir.allowed(private_dir.ROOT))


if __name__ == "__main__":
    unittest.main()
