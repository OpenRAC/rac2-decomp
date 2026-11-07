"""The opt-in -frac2-keep-float-pun-source: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("keep_float_pun_source",
    ROOT / "tools/compiler/transformers/keep_float_pun_source.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-keep-float-pun-source"
CASES = ("two_reads", "two_helpers", "three_reads", "older_register", "reads_in_loop",
         "reads_across_branches")
# Where the default compiler loses the ori: three reads, two in a loop, reads across a branch.
LOW_HALF_LOST = ("three_reads", "reads_in_loop", "reads_across_branches")
CONTROLS = ("one_read", "one_read_in_loop", "read_side", "plain_float", "small_constant",
            "double_word", "pun_argument")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^(" + name + r"):.*?\.end\s+\1\b", asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def instructions(body: str) -> list:
    return [line.split("#")[0].strip() for line in body.splitlines()
            if line.strip() and not line.strip().startswith((".", "#")) and not line.strip().endswith(":")]


def index_of(lines: list, pattern: str) -> int:
    return next(i for i, line in enumerate(lines) if re.fullmatch(pattern, line))


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"cse.c": "a\n" + transformer.CANON_OLD + "b\n" + transformer.TRIAL_OLD,
                 "combine.c": "a\n" + transformer.I3_OLD + "b\n",
                 "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
                 "flags.h": transformer.DECLARATION_OLD}
        files.update(override)
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            cse = (root / "cse.c").read_text()
            self.assertEqual(cse.count("RAC2_FLOAT_PUN_SET_P (sets[i].rtl)"), 2)
            self.assertIn("? src : canon_reg (src, insn);", cse)
            combine = (root / "combine.c").read_text()
            self.assertEqual(combine.count("RAC2_FLOAT_PUN_SET_P (x)"), 1)
            self.assertLess(combine.index("find_single_use"), combine.index("expand_field_assignment"))
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_keep_float_pun_source = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_keep_float_pun_source, 1,', top)
            flags = (root / "flags.h").read_text()
            self.assertIn("extern int flag_rac2_keep_float_pun_source;", flags)
            self.assertIn("#define RAC2_FLOAT_PUN_SET_P(SET)", flags)
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_macro_keys_on_the_insn_alone(self):
        # The shape of the SET and the option, nothing about a function or an address.
        macro = transformer.DECLARATION_NEW[transformer.DECLARATION_NEW.index("#define"):]
        for test in ("GET_MODE (SET_DEST (SET)) == SImode", "GET_MODE (SUBREG_REG (SET_DEST (SET))) == SFmode",
                     "REGNO (SUBREG_REG (SET_DEST (SET))) >= FIRST_PSEUDO_REGISTER",
                     "GET_CODE (SET_SRC (SET)) == REG"):
            self.assertIn(test, macro)
        self.assertNotIn("NAME", macro)
        self.assertNotIn("current_function", macro)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        # Each anchor on its own: the other anchor of the same file stays in place.
        cases = (("cse.c", "a\n" + transformer.TRIAL_OLD, "cse_insn canon_reg"),
                 ("cse.c", transformer.CANON_OLD + "unexpected trial loop\n", "cse_insn trial loop"),
                 ("combine.c", "unexpected text", "combinable_i3pat"),
                 ("toplev.c", "unexpected text", "option definition"),
                 ("toplev.c", transformer.DEFINITION_OLD + "unexpected option table\n", "option table"),
                 ("flags.h", "unexpected text", "option declaration"))
        for name, text, label in cases:
            with self.subTest(label), tempfile.TemporaryDirectory() as d:
                root = Path(d)
                files = self.sources(root, **{name: text})
                with self.assertRaisesRegex(ValueError, label):
                    transformer.patch(root)
                self.assertEqual({n: (root / n).read_text() for n in files}, files)


class CompilerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools"))
        if not all((compiler / name).is_file() for name in ("cpp", "cc1", "as")):
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built cpp, cc1 and as")
            raise unittest.SkipTest("EE compiler absent; tools/compiler/build.sh runs these checks after building it")
        cls.outputs = {}
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            source = root / "input.c"
            source.write_bytes((ROOT / "tests/fixtures/keep_float_pun_source.c").read_bytes())
            with (root / "input.i").open("w") as out:
                try:
                    subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                except OSError:
                    if "RAC2_COMPILER_ROOT" in os.environ:
                        raise
                    raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                            "runs these checks in its build environment")
            for label, options in PROFILES.items():
                asm = root / (label + ".s")
                subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                                *options, str(root / "input.i"), "-o", str(asm)], check=True)
                subprocess.run([str(compiler / "as"), "-o", str(root / (label + ".o")), str(asm)], check=True)
                text = asm.read_text()
                cls.outputs[label] = {name: function_text(text, name) for name in CASES + CONTROLS}

    def lines(self, label: str, name: str) -> list:
        return instructions(self.outputs[label][name])

    def test_disabled_option_restores_default_for_every_function(self):
        self.assertEqual(self.outputs["default"], self.outputs["disabled"])

    def test_controls_are_unchanged(self):
        for name in CONTROLS:
            with self.subTest(name):
                self.assertEqual(self.outputs["default"][name], self.outputs["enabled"][name])

    def test_one_read_still_folds(self):
        for label in PROFILES:
            for name in ("one_read", "one_read_in_loop"):
                with self.subTest(label=label, name=name):
                    self.assertTrue(any(re.fullmatch(r"li\.s\t\$f13,1\.98\S*", line)
                                        for line in self.lines(label, name)))
                    self.assertFalse(any(line.startswith("mtc1\t$2") for line in self.lines(label, name)))

    def test_default_keeps_the_word_in_a_saved_register(self):
        for name in ("two_reads", "two_helpers", "older_register"):
            with self.subTest(name):
                lines = self.lines("default", name)
                self.assertEqual(sum(line == "mtc1\t$17,$f13" for line in lines), 2)
                self.assertTrue(any(line.startswith("li\t$17,") for line in lines))

    def test_option_moves_the_word_once_into_a_saved_fpr(self):
        for name in ("two_reads", "two_helpers", "older_register"):
            with self.subTest(name):
                lines = self.lines("enabled", name)
                self.assertEqual([line for line in lines if line.startswith("mtc1\t$2")], ["mtc1\t$2,$f21"])
                self.assertEqual(sum(line == "mov.s\t$f13,$f21" for line in lines), 2)
                self.assertFalse(any(line.startswith(("li\t$17", "li.s\t$f21", "li.s\t$f13")) for line in lines))

    def test_option_sets_the_word_after_the_previous_call_in_order(self):
        for name in ("two_reads", "two_helpers", "older_register"):
            with self.subTest(name):
                lines = self.lines("enabled", name)
                call = index_of(lines, r"jal\twork")
                high = index_of(lines, r"li\t\$2,\d+")
                low = index_of(lines, r"ori\t\$2,\$2,0x\w+")
                move = index_of(lines, r"mtc1\t\$2,\$f21")
                read = index_of(lines, r"mov\.s\t\$f13,\$f21")
                first = index_of(lines, r"jal\tkey")
                self.assertLess(call, high)
                self.assertLess(high, low)
                self.assertLess(low, move)
                self.assertLess(move, read)  # the copy waits out the transfer
                self.assertLess(read, first)

    def test_option_does_not_reuse_an_older_register(self):
        # older_register has the word in $4 for store_word: the store builds it again.
        lines = self.lines("enabled", "older_register")
        self.assertEqual(sum(line.startswith("li\t") and "1615069184" in line for line in lines), 2)

    def test_default_loses_the_low_half(self):
        # The wrong code this tree gives by default: sched1 splits the store, the reads win
        # FP_REGS, and reload drops the ior's output reload. It must stay stock here
        # (docs/COMPILER-NOTES.md, known issue).
        for name in LOW_HALF_LOST:
            with self.subTest(name):
                lines = self.lines("default", name)
                self.assertTrue(any(re.fullmatch(r"li\t\$2,\d+.*", line) for line in lines))
                self.assertFalse(any(line.startswith("ori") for line in lines))

    def test_option_keeps_the_low_half(self):
        # call < lui < ori < mtc1: the whole word reaches the FPR, after the previous call.
        low_half = {"three_reads": "0x2d00", "reads_in_loop": "0x2d00", "reads_across_branches": "0xc070"}
        for name in LOW_HALF_LOST:
            with self.subTest(name):
                lines = self.lines("enabled", name)
                call = index_of(lines, r"jal\twork")
                high = index_of(lines, r"li\t\$2,\d+")
                low = index_of(lines, r"ori\t\$2,\$2," + low_half[name])
                move = index_of(lines, r"mtc1\t\$2,\$f2[01]")
                self.assertLess(call, high)
                self.assertLess(high, low)
                self.assertLess(low, move)
                self.assertEqual(sum(line.startswith("mtc1\t$2") for line in lines), 1)


if __name__ == "__main__":
    unittest.main()
