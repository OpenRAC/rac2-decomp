"""16-byte-aligned block moves use lq/sq: transformer drift and EE output."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("block_move_quad",
    ROOT / "tools/compiler/transformers/block_move_quad.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

FUNCTIONS = ("copy_packet", "copy_short", "copy_words")


def function_text(asm: str, name: str) -> str:
    return re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()


def opcodes(text: str) -> list:
    return re.findall(r"(?m)^\s+(lq|sq|ld|sd)\s", text)


class TransformerTests(unittest.TestCase):
    def test_each_edit_applies_once(self):
        with tempfile.TemporaryDirectory() as d:
            mips = Path(d) / "mips.c"
            original = transformer.CAP_OLD + transformer.PIECES_OLD + transformer.OUTPUT_OLD
            mips.write_text(original)
            transformer.patch(mips)
            self.assertIn("lq", mips.read_text())
            with self.assertRaisesRegex(ValueError, "found 0"):
                transformer.patch(mips)

    def test_source_drift_is_rejected_without_writing(self):
        with tempfile.TemporaryDirectory() as d:
            mips = Path(d) / "mips.c"
            mips.write_text(transformer.CAP_OLD)
            with self.assertRaisesRegex(ValueError, "found 0"):
                transformer.patch(mips)
            self.assertEqual(mips.read_text(), transformer.CAP_OLD)


class CompilerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools"))
        if not all((compiler / name).is_file() for name in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built cpp, cc1 and as")
            raise unittest.SkipTest("EE compiler absent; tools/compiler/build.sh runs these checks after building it")
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            source = root / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/block_move_quad.c").read_bytes())
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            asm = root / "input.s"
            subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G8", "-ffunction-sections",
                            str(root / "input.i"), "-o", str(asm)], check=True)
            text = asm.read_text()
            cls.outputs = {name: opcodes(function_text(text, name)) for name in FUNCTIONS}

    def test_aligned_loop_moves_quadwords(self):
        # Retail, e.g. func_L12_00418418: two lq and two sq a round, one of each for the leftover.
        self.assertEqual(self.outputs["copy_packet"], ["lq", "lq", "sq", "sq", "lq", "sq"])

    def test_short_copy_stays_in_pieces(self):
        self.assertNotIn("lq", self.outputs["copy_short"])

    def test_word_aligned_loop_keeps_doublewords(self):
        self.assertNotIn("lq", self.outputs["copy_words"])
        self.assertIn("ld", self.outputs["copy_words"])


if __name__ == "__main__":
    unittest.main()
