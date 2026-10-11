"""Adversarial checks for exploratory whole-function comparisons, never credit."""
import contextlib
import gzip
import hashlib
import io
import json
import struct
import sys
import tempfile
import types
import unittest
from pathlib import Path
from unittest import mock

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import try_function as trial  # noqa: E402


def sha(data):
    return hashlib.sha256(data).hexdigest()


def object_fixture(symbol="f", start=8, size=8, relocation=8):
    """Two functions share .text; the requested one need not start at zero."""
    strings = b"\0other\0" + symbol.encode() + b"\0"
    symbols = bytes(16) + struct.pack("<IIIBBH", 1, 0, 8, 0x12, 0, 1)
    symbols += struct.pack("<IIIBBH", 7, start, size, 0x12, 0, 1)
    blocks = [(0, 0, b"", 0, 0, 0), (1, 6, struct.pack("<4I", 1, 2, 3, 4), 0, 0, 0),
              (3, 0, strings, 0, 0, 0), (2, 0, symbols, 2, 1, 16),
              (9, 0, struct.pack("<II", relocation, 4), 3, 1, 8),
              (3, 0, b"\0.text\0.strtab\0.symtab\0.rel.text\0.shstrtab\0", 0, 0, 0)]
    names = [0, 1, 7, 15, 23, 33]
    data = bytearray(52)
    data[:6] = b"\x7fELF\x01\x01"
    struct.pack_into("<H", data, 16, 1)
    headers = []
    for name, (kind, flags, blob, link, info, stride) in zip(names, blocks):
        offset = len(data)
        data.extend(blob)
        headers.append(struct.pack("<10I", name, kind, flags, 0, offset, len(blob), link, info, 4, stride))
    struct.pack_into("<I", data, 32, len(data))
    struct.pack_into("<HHH", data, 46, 40, len(headers), 5)
    data.extend(b"".join(headers))
    return bytes(data)


class ExtentTests(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        self.root = Path(self.tmp.name)
        self.pin = "a" * 64
        self.body = struct.pack("<4I", 1, 2, 3, 4)
        folder = self.root / "config/function-catalog"
        folder.mkdir(parents=True)
        (self.root / "input.json").write_bytes(b"current")
        row = [0x100, 16, sha(self.body), "flow_supported_inferred", None, [], [], [], None]
        expanded = (json.dumps(row) + "\n").encode()
        compressed = gzip.compress(expanded)
        (folder / "boot.ndjson.gz").write_bytes(compressed)
        self.doc = {"schema": 1, "target": "SCUS_972.68", "normalizer": {"sha256": "b" * 64},
                    "input_pins": [{"path": "input.json", "sha256": sha(b"current")}],
                    "programs": [{"program": "boot", "reference_sha256": self.pin}],
                    "function_chunks": [{"program": "boot", "path": "boot.ndjson.gz", "compression": "gzip",
                                         "format": "compact-ndjson-v1", "sha256": sha(compressed),
                                         "expanded_sha256": sha(expanded), "max_expanded_bytes": len(expanded) + 1}]}
        self.save()
        v2 = self.root / "config/regions/ntsc-u-v2"
        v2.mkdir(parents=True)
        self.v2 = {"schema": 1, "target": "SCUS_972.68", "version": "2.00", "boot_sha256": self.pin,
                   "functions": [[0x100, 16, "f"]]}
        self.save_v2()

    def save(self):
        (self.root / "config/function-catalog/catalog.json").write_text(json.dumps(self.doc))

    def save_v2(self):
        (self.root / "config/regions/ntsc-u-v2/catalog.json").write_text(json.dumps(self.v2))

    def extent(self, address=0x100, size=16, region="ntsc-u"):
        return trial.catalog_extent(region, address, size, self.pin, self.root)

    def test_whole_v1_body_uses_pinned_extent_and_hash(self):
        self.assertEqual(self.extent(), ("flow_supported_inferred", sha(self.body)))

    def test_prefix_interior_and_unaligned_slices_are_refused(self):
        for region in ("ntsc-u", "ntsc-u-v2"):
            for address, size in ((0x100, 8), (0x104, 12), (0x101, 16), (0x100, 20)):
                with self.subTest(region=region, address=address, size=size), self.assertRaises(ValueError):
                    self.extent(address, size, region)

    def test_stale_inputs_are_refused(self):
        (self.root / "input.json").write_bytes(b"changed")
        with self.assertRaisesRegex(ValueError, "Stale input pin"):
            self.extent()

    def test_stale_boot_identity_is_refused(self):
        self.doc["programs"][0]["reference_sha256"] = "c" * 64
        self.save()
        with self.assertRaisesRegex(ValueError, "identity"):
            self.extent()

    def test_stale_compressed_and_expanded_payloads_are_refused(self):
        path = self.root / "config/function-catalog/boot.ndjson.gz"
        path.write_bytes(path.read_bytes() + b"changed")
        with self.assertRaisesRegex(ValueError, "compressed"):
            self.extent()
        self.doc["function_chunks"][0]["sha256"] = sha(path.read_bytes())
        self.save()
        with self.assertRaises((ValueError, OSError, EOFError)):
            self.extent()

    def test_expanded_hash_drift_is_refused(self):
        self.doc["function_chunks"][0]["expanded_sha256"] = "f" * 64
        self.save()
        with self.assertRaisesRegex(ValueError, "expanded"):
            self.extent()

    def test_fragment_boundary_is_refused(self):
        path = self.root / "config/function-catalog/boot.ndjson.gz"
        row = json.loads(gzip.decompress(path.read_bytes()))
        row[3] = "ambiguous_fragment"
        expanded = (json.dumps(row) + "\n").encode()
        payload = gzip.compress(expanded)
        path.write_bytes(payload)
        self.doc["function_chunks"][0].update(sha256=sha(payload), expanded_sha256=sha(expanded),
                                            max_expanded_bytes=len(expanded) + 1)
        self.save()
        with self.assertRaisesRegex(ValueError, "not a supported whole body"):
            self.extent()

    def test_wrong_v2_identity_and_duplicate_extents_are_refused(self):
        self.v2["boot_sha256"] = "d" * 64
        self.save_v2()
        with self.assertRaisesRegex(ValueError, "Stale"):
            self.extent(region="ntsc-u-v2")
        self.v2["boot_sha256"] = self.pin
        self.v2["functions"].append([0x100, 16, "alias"])
        self.save_v2()
        with self.assertRaisesRegex(ValueError, "Overlapping"):
            self.extent(region="ntsc-u-v2")


class ObjectTests(unittest.TestCase):
    def read(self, data, symbol="f"):
        with mock.patch.object(Path, "read_bytes", return_value=data):
            return trial.object_text(Path("fixture.o"), symbol)

    def test_exact_symbol_body_and_relative_relocation(self):
        self.assertEqual(self.read(object_fixture()), (struct.pack("<2I", 3, 4), {0: 4}))

    def test_missing_symbol_never_falls_back_to_text(self):
        with self.assertRaisesRegex(ValueError, "STT_FUNC"):
            self.read(object_fixture(), "missing")

    def test_incomplete_or_unaligned_symbol_is_refused(self):
        for start, size in ((8, 12), (9, 4), (8, 0)):
            with self.subTest(start=start, size=size), self.assertRaises(ValueError):
                self.read(object_fixture(start=start, size=size))

    def test_bad_relocation_is_refused(self):
        with self.assertRaisesRegex(ValueError, "Relocation"):
            self.read(object_fixture(relocation=9))


class CliTests(unittest.TestCase):
    def compare(self, mask=False, reference_hash=None, record=False, region="ntsc-u-v2"):
        with tempfile.TemporaryDirectory() as folder:
            root = Path(folder)
            elf = root / "reference.elf"
            elf.write_bytes(b"synthetic pinned ELF")
            source = root / "f.c"
            source.write_text("int f(void) { return 3; }\n")
            argv = ["try_function.py", str(source), "--elf", str(elf), "--address", "0x100", "--size", "8",
                    "--region", region]
            if mask:
                argv.append("--mask-relocs")
            if record:
                argv.append("--record")
            original_temp = tempfile.TemporaryDirectory
            def compile_fixture(_source, _flags, obj, asm, _log):
                obj.write_bytes(object_fixture())
                asm.write_text("synthetic assembly\n")
            output = io.StringIO()
            with mock.patch.object(sys, "argv", argv), \
                    mock.patch.object(trial.regions, "load", return_value=types.SimpleNamespace(
                        target={"boot": {"sha256": sha(elf.read_bytes())}})), \
                    mock.patch.object(trial, "catalog_extent", return_value=("flow_supported_inferred", reference_hash)), \
                    mock.patch.object(trial.rank, "load_code_ranges", return_value=[(0x100, [3, 4])]), \
                    mock.patch.object(trial.tempfile, "TemporaryDirectory", side_effect=lambda **kw: original_temp(dir=root)), \
                    mock.patch.object(trial.wsl_chain, "compile_c", side_effect=compile_fixture), \
                    contextlib.redirect_stdout(output):
                result = trial.main()
            return result, output.getvalue()

    def test_raw_equality_is_explicitly_uncredited(self):
        code, output = self.compare()
        self.assertEqual(code, 0)
        self.assertIn("RAW_EQUAL_CANDIDATE", output)
        self.assertIn("no matching credit", output)
        self.assertNotIn("\nMATCH\n", output)

    def test_masked_equality_is_diagnostic(self):
        code, output = self.compare(mask=True)
        self.assertEqual(code, 0)
        self.assertIn("MASKED_EQUAL_DIAGNOSTIC", output)
        self.assertNotIn("RAW_EQUAL_CANDIDATE", output)

    def test_stale_body_hash_is_refused_before_compilation(self):
        with self.assertRaisesRegex(ValueError, "body hash"):
            self.compare(reference_hash="e" * 64)

    def test_v1_record_is_refused_before_comparison(self):
        with self.assertRaisesRegex(SystemExit, "only for the experimental"):
            self.compare(record=True, region="ntsc-u")


if __name__ == "__main__":
    unittest.main()
