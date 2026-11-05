"""Short loops count only the measured unannounced external SI macro class."""
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf
import sdata_aliases
from test_count_asm_words import backward_spans


class SymbolicLoopTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")).resolve()
        if not all((compiler / n).is_file() for n in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built compiler")
            raise unittest.SkipTest("EE compiler absent")
        cls.objects = {}
        with tempfile.TemporaryDirectory() as d:
            work = Path(d)
            source = work / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/symbolic_loop_words.c").read_bytes())
            with (work / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), "-I" + str(ROOT / "include"), str(source)],
                                   stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host")
            for g in (0, 8):
                assembly = work / f"g{g}.s"
                subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", f"-G{g}",
                                "-ffunction-sections", str(work / "input.i"), "-o", str(assembly)], check=True)
                # Exercise the same explicit-GP metadata pass as production.
                assembly.write_text(sdata_aliases.transform(assembly.read_text()))
                obj = work / f"g{g}.o"
                subprocess.run([str(compiler / "as"), "-o", str(obj), str(assembly)], check=True)
                cls.objects[g] = elf.read_object(obj)

    def span(self, name, g=8):
        return backward_spans(self.objects[g], name)

    def test_unknown_load_counts_its_absolute_pair(self):
        self.assertEqual(self.span("unknown_limit_loop"), [[7]])

    def test_unknown_address_with_offset_counts_two_words(self):
        self.assertEqual(self.span("unknown_address_loop", 0), [[7]])

    def test_early_sda_declaration_keeps_gp_padding(self):
        self.assertEqual(self.span("known_gp_limit_loop"), [[7]])

    def test_incomplete_explicit_gp_alias_keeps_gp_padding(self):
        self.assertEqual(self.span("explicit_gp_limit_loop"), [[7]])

    def test_raw_alias_recognizes_the_ordinary_announcement(self):
        self.assertEqual(self.span("alias_of_known_limit_loop"), [[7]])

    def test_ordinary_name_recognizes_the_raw_alias_announcement(self):
        self.assertEqual(self.span("ordinary_spelling_loop"), [[7]])

    def test_g0_external_then_definition_changes_only_the_known_form(self):
        self.assertEqual(self.span("before_definition_loop", 0), [[7]])
        self.assertEqual(self.span("after_definition_loop", 0), [[7]])


if __name__ == "__main__":
    unittest.main()
