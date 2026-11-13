"""The opt-in -frac2-keep-user-copies: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("keep_user_copies",
    ROOT / "tools/compiler/transformers/keep_user_copies.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-keep-user-copies"
CASES = ("counter_float", "counter_limit")
CONTROLS = ("control_float", "control_limit", "control_sum")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^(" + name + r"):.*?\.end\s+\1\b", asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def instructions(body: str) -> list:
    return [line.split("#")[0].strip() for line in body.splitlines()
            if line.strip() and not line.strip().startswith((".", "#")) and not line.strip().endswith(":")]


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"cse.c": "a\n" + transformer.CSE_OLD + "\nb\n",
                 "combine.c": "a\n" + transformer.COMBINE_OLD + "\nb\n",
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
            for name in ("cse.c", "combine.c", "toplev.c", "flags.h"):
                self.assertIn("flag_rac2_keep_user_copies", (root / name).read_text())
            self.assertIn('{"' + OPTION + '", &flag_rac2_keep_user_copies, 1,', (root / "toplev.c").read_text())
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_rules_key_on_the_registers_alone(self):
        # A user variable and pseudo registers: nothing about a function, an address or a mode.
        for text in (transformer.CSE_NEW, transformer.COMBINE_NEW):
            self.assertIn("REG_USERVAR_P", text)
            self.assertIn("FIRST_PSEUDO_REGISTER", text)
            self.assertNotIn("current_function", text)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        cases = (("cse.c", "unexpected text", "cse canonical register"),
                 ("combine.c", "unexpected text", "combine copy"),
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
            source.write_bytes((ROOT / "tests/fixtures/keep_user_copies.c").read_bytes())
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

    def test_default_drops_the_copy(self):
        # By default the copy is folded away: each case compiles as its control.
        for case, control in (("counter_float", "control_float"), ("counter_limit", "control_limit")):
            with self.subTest(case):
                self.assertEqual(self.lines("default", case), self.lines("default", control))

    def test_the_kept_copy_costs_no_instruction(self):
        for name in CASES:
            with self.subTest(name):
                self.assertEqual(len(self.lines("enabled", name)), len(self.lines("default", name)))
                moves = {label: sum(bool(re.fullmatch(r"move\t\$\d+,\$\d+", line))
                                    for line in self.lines(label, name)) for label in ("default", "enabled")}
                self.assertEqual(moves["enabled"], moves["default"])

    def test_option_gives_the_counter_the_first_register(self):
        # The copy is tied to the counter, whose quantity outranks counter + 1 (and the divisor).
        lines = self.lines("enabled", "counter_float")
        self.assertIn("lhu\t$2,150($4)", lines)
        self.assertIn("addu\t$3,$2,1", lines)
        self.assertIn("mtc1\t$2,$f3", lines)
        self.assertIn("li.s\t$f4,2.00000000000000000000e0", lines)
        lines = self.lines("enabled", "counter_limit")
        self.assertIn("lhu\t$3,150($7)", lines)
        self.assertIn("addu\t$4,$3,1", lines)
        self.assertIn("li\t$6,6", lines)
        self.assertIn("slt\t$2,$2,$3", lines)


if __name__ == "__main__":
    unittest.main()
