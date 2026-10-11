"""Symbol imports preserve release identity and maintained maps."""
import json
import sys
import tempfile
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
import import_going_native_symbols as upstream
import import_symbol_addrs as candidates


class SymbolImportTests(unittest.TestCase):
    def test_upstream_requires_immutable_revision_and_explicit_release(self):
        sha = "a" * 40
        self.assertIn(f"/{sha}/going-decompiled/symbol_addrs/usa/", upstream.source_url(sha, "usa-v2"))
        self.assertIn("/symbol_addrs/eu/", upstream.source_url(sha, "eu"))
        for revision, region in (("main", "usa-v2"), (sha, "usa"), (sha, "ntsc-u")):
            with self.assertRaises(ValueError):
                upstream.source_url(revision, region)

    def test_only_names_and_addresses_are_retained(self):
        self.assertEqual(upstream.parse_symbols("f = 0x1234; // upstream code/comment\n# comment"),
                         {"f": 0x1234})
        with self.assertRaisesRegex(ValueError, "Conflicting"):
            upstream.parse_symbols("f = 0x1234;\nf = 0x5678;")

    def test_candidate_metadata_must_identify_pinned_v101(self):
        target = json.loads((ROOT / "config/target.json").read_bytes())
        data = {"target": target["serial"], "reference_sha256": target["boot"]["sha256"],
                "functions": [{"symbol": "f", "address": 0x1234}]}
        self.assertEqual(candidates.candidate_symbols(data, target), {"f": 0x1234})
        for field, value in (("reference_sha256", "v2"), ("target", "SCES_516.07")):
            with self.assertRaisesRegex(ValueError, "pinned USA v1.01"):
                candidates.candidate_symbols(dict(data, **{field: value}), target)

    def test_review_output_never_overwrites_a_file(self):
        with tempfile.TemporaryDirectory() as tmp:
            output = Path(tmp) / "review.txt"
            candidates.write_review(output, {"f": 0x1234}, "region=ntsc-u")
            original = output.read_bytes()
            with self.assertRaisesRegex(ValueError, "overwrite"):
                candidates.write_review(output, {"g": 0x5678}, "region=eu")
            self.assertEqual(output.read_bytes(), original)

    def test_maintained_and_unignored_destinations_are_refused(self):
        for rel in ("symbol_addrs/usa/not-created.txt", "src/not-created.txt"):
            with self.assertRaises(ValueError):
                candidates.review_output(ROOT / rel)
        self.assertEqual(candidates.review_output(ROOT / "build/private-symbol-review-not-created.txt"),
                         ROOT / "build/private-symbol-review-not-created.txt")


if __name__ == "__main__":
    unittest.main()
