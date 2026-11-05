"""Loop padding counts an asm statement and the grouped qcopy by their words."""
import os
import importlib.util
import struct
import sys
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf
FUNCTIONS = ("asm_copy_rows", "pattern_copy_rows", "scalar_rows")

spec = importlib.util.spec_from_file_location(
    "count_asm_words", ROOT / "tools/compiler/transformers/count_asm_words.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)


class TransformerTests(unittest.TestCase):
    def object_definition(self):
        return ("\nmips_declare_object (stream, name, init_string, final_string, size)\n{\n"
                + transformer.declaration_old + "\n}\n")

    def test_padding_updates_the_counter_and_reapplication_is_rejected(self):
        source = ("void\nmips_r5900_pad_loops (first)\n{\n" + transformer.old
                  + "\n" + transformer.padding_old * 2 + "\n}\n/* ASTRA P25:"
                  + self.object_definition())
        patched = transformer.patch(source)
        self.assertIn(transformer.padding_new, patched)
        with self.assertRaises(AssertionError):
            transformer.patch(patched)

    def test_insertion_drift_fails_before_a_result_is_returned(self):
        for insertion in ("", transformer.padding_old, transformer.padding_old * 3):
            source = ("void\nmips_r5900_pad_loops (first)\n{\n" + transformer.old
                      + "\n" + insertion + "\n}\n/* ASTRA P25:" + self.object_definition())
            with self.subTest(insertion=insertion), self.assertRaises(AssertionError):
                transformer.patch(source)


def loop_words(asm: str, name: str) -> tuple[int, int]:
    """(words from the loop label through the branch's delay slot, NOPs among them)."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    lines = [l.split("#")[0].strip() for l in body.splitlines()]
    start = next(k for k, l in enumerate(lines) if re.match(r"\$L\d+:", l))
    words = nops = 0
    for k in range(start + 1, len(lines)):
        line = lines[k]
        if not line or line.startswith(".") or line.endswith(":"):
            continue
        words += 1
        nops += line == "nop"
        if re.match(r"b\w*\s", line):
            return words + 1, nops   # the delay slot follows
    raise AssertionError("no loop branch in " + name)


def backward_spans(obj: dict, name: str) -> list[list[int]]:
    """Actual object-word spans include assembler-generated empty delay slots."""
    symbol = next(s for s in obj["symbols"] if s["name"] == name and s["type"] == 2)
    raw = obj["sections"][symbol["section"]]["data"]
    body = raw[symbol["value"]:symbol["value"] + symbol["size"]]
    edges = {}
    for position, (word,) in enumerate(struct.iter_unpack("<I", body)):
        if word >> 26 not in (1, 4, 5, 6, 7, 20, 21, 22, 23):
            continue
        displacement = word & 0xFFFF
        if displacement >= 0x8000:
            displacement -= 0x10000
        target = position + 1 + displacement
        if 0 <= target <= position:
            edges.setdefault(target, []).append(position - target + 2)
    return [edges[target] for target in sorted(edges)]


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
            source.write_bytes((ROOT / "tests/fixtures/count_asm_words.c").read_bytes())
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            asm = root / "input.s"
            subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                            "-frac2-qcopy", str(root / "input.i"), "-o", str(asm)], check=True)
            subprocess.run([str(compiler / "as"), "-o", str(root / "input.o"), str(asm)], check=True)
            text = asm.read_text()
            cls.loops = {name: loop_words(text, name) for name in FUNCTIONS}
            obj = elf.read_object(root / "input.o")
            cls.multiple = {name: backward_spans(obj, name)
                            for name in ("skip_pair", "skip_two_pairs", "poll_pair")}

    def test_the_asm_copy_counts_two_words(self):
        # Counted as one insn, the seven-word retail loop got an eighth word.
        words, nops = self.loops["asm_copy_rows"]
        self.assertEqual((words, nops), (7, 0))

    def test_the_grouped_copy_counts_two_words(self):
        words, nops = self.loops["pattern_copy_rows"]
        self.assertEqual(words, 7)
        self.assertLessEqual(nops, 1)

    def test_a_short_scalar_loop_is_still_padded(self):
        words, nops = self.loops["scalar_rows"]
        self.assertGreaterEqual(words, 7)

    def test_second_back_edge_counts_the_padding_already_inserted(self):
        self.assertEqual(self.multiple["skip_pair"], [[7, 9]])

    def test_independent_loops_each_keep_their_own_minimum(self):
        self.assertEqual(self.multiple["skip_two_pairs"], [[7, 9], [7, 9]])

    def test_unfilled_delay_slots_also_count_prior_padding(self):
        self.assertEqual(self.multiple["poll_pair"], [[7, 10]])


if __name__ == "__main__":
    unittest.main()
