"""-frac2-sticky-volatile-sets, on by default: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("sticky_volatile_sets",
    ROOT / "tools/compiler/transformers/sticky_volatile_sets.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-sticky-volatile-sets"
FUNCTIONS = ("store_then_volatile", "plain_stores", "volatile_first", "volatile_load")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-fno-" + OPTION],
            "reenabled": ["-fno-" + OPTION, "-f" + OPTION],
            "refs": ["-fno-" + OPTION, "-frac2-sticky-volatile-refs"]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^(" + name + r"):.*?\.end\s+\1\b", asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def instructions(body: str) -> list:
    return [line.strip() for line in body.splitlines()
            if line.strip() and not line.strip().startswith((".", "#")) and not line.strip().endswith(":")]


def first_slot(body: str):
    """The instruction reorg put in the delay slot of the call to one(), or None if it is empty.

    cc1 writes a filled slot inside `.set noreorder` right after the jal; an empty one is left
    to the assembler, so the jal is not inside such a block."""
    lines = [line.strip() for line in body.splitlines() if line.strip() and not line.strip().startswith("#")]
    at = lines.index("jal\tone")
    if lines[at - 1] != ".set\tnomacro":
        return None
    return next(line for line in lines[at + 1:] if not line.startswith("."))


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"resource.c": "a\n    case MEM:\n" + transformer.SET_OLD + "b\n",
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
            resource = (root / "resource.c").read_text()
            # Both fields of the MEM set, and only they, keep their earlier value.
            self.assertEqual(resource.count("flag_rac2_sticky_volatile_sets ?"), 2)
            self.assertIn("(flag_rac2_sticky_volatile_sets ? res->volatil : 0)\n\t\t\t | MEM_VOLATILE_P (x);",
                          resource)
            self.assertIn("(flag_rac2_sticky_volatile_sets ? res->unch_memory : 0)\n\t\t\t     | "
                          "RTX_UNCHANGING_P (x);", resource)
            self.assertNotIn("res->volatil = MEM_VOLATILE_P (x);", resource)
            top = (root / "toplev.c").read_text()
            # On by default; the option table gives -fno-rac2-sticky-volatile-sets.
            self.assertIn("int flag_rac2_sticky_volatile_sets = 1;", top)
            self.assertNotIn("int flag_rac2_sticky_volatile_sets = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_sticky_volatile_sets, 1,', top)
            # The new entry follows its anchor, the -frac2-no-static-chain-base entry.
            self.assertIn(transformer.OPTION_OLD + '  {"' + OPTION + '"', top)
            self.assertIn("extern int flag_rac2_sticky_volatile_sets;", (root / "flags.h").read_text())
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        # The option-table anchor is checked on its own: toplev.c keeps its definition anchor.
        cases = (("resource.c", "unexpected text", "MEM set"),
                 ("resource.c", transformer.SET_OLD.replace("res->volatil = ", "res->volatil |= "), "MEM set"),
                 ("toplev.c", "unexpected text", "option definition"),
                 ("toplev.c", transformer.DEFINITION_OLD + "unexpected option table\n", "option table"),
                 ("flags.h", "unexpected text", "option declaration"))
        for name, text, label in cases:
            with self.subTest(label=label, text=text[:30]), tempfile.TemporaryDirectory() as d:
                root = Path(d)
                files = self.sources(root, **{name: text})
                with self.assertRaisesRegex(ValueError, label):
                    transformer.patch(root)
                self.assertEqual({n: (root / n).read_text() for n in files}, files)

    def test_a_second_mem_set_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            files = self.sources(root, **{"resource.c": transformer.SET_OLD + transformer.SET_OLD})
            with self.assertRaisesRegex(ValueError, "MEM set: expected one insertion point, found 2"):
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
            source.write_bytes((ROOT / "tests/fixtures/sticky_volatile_sets.c").read_bytes())
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
                cls.outputs[label] = {name: function_text(text, name) for name in FUNCTIONS}

    def test_the_rule_is_the_default(self):
        self.assertEqual(self.outputs["default"], self.outputs["enabled"])
        self.assertEqual(self.outputs["default"], self.outputs["reenabled"])

    def test_default_leaves_the_slot_empty(self):
        self.assertIsNone(first_slot(self.outputs["default"]["store_then_volatile"]))

    def test_opt_out_takes_the_multiply_from_before_both_stores(self):
        self.assertEqual(first_slot(self.outputs["disabled"]["store_then_volatile"]), "mult\t$16,$5,$6")

    def test_exact_output_of_both_rules(self):
        # By default the volatile store's flag survives the plain store, so the search stops
        # there and the multiply stays ahead of both stores. Only the schedule changes.
        expected = {
            "disabled": ["subu\t$sp,$sp,16", "lui\t$2,%hi(status) # high", "sd\t$16,0($sp)",
                         "sd\t$31,8($sp)", "sw\t$7,0($4)", "sw\t$0,%lo(status)($2)", "jal\tone",
                         "mult\t$16,$5,$6", "jal\ttwo", "move\t$4,$16", "ld\t$16,0($sp)",
                         "ld\t$31,8($sp)", "j\t$31", "addu\t$sp,$sp,16"],
            "default": ["subu\t$sp,$sp,16", "lui\t$2,%hi(status) # high", "sd\t$16,0($sp)",
                        "sd\t$31,8($sp)", "mult\t$16,$5,$6", "sw\t$7,0($4)", "sw\t$0,%lo(status)($2)",
                        "jal\tone", "jal\ttwo", "move\t$4,$16", "ld\t$16,0($sp)", "ld\t$31,8($sp)",
                        "j\t$31", "addu\t$sp,$sp,16"],
        }
        for label, lines in expected.items():
            with self.subTest(label):
                self.assertEqual(instructions(self.outputs[label]["store_then_volatile"]), lines)

    def test_the_referenced_half_alone_does_not_stop_the_search(self):
        # -frac2-sticky-volatile-refs changes mark_referenced_resources only; the stores are sets.
        self.assertEqual(self.outputs["refs"]["store_then_volatile"],
                         self.outputs["disabled"]["store_then_volatile"])

    def test_controls_are_unchanged(self):
        self.assertEqual(first_slot(self.outputs["default"]["plain_stores"]), "sw\t$0,%lo(extra)($2)")
        self.assertEqual(first_slot(self.outputs["default"]["volatile_first"]), "sw\t$7,0($4)")
        self.assertEqual(first_slot(self.outputs["default"]["volatile_load"]), "sw\t$2,0($4)")
        for name in ("plain_stores", "volatile_first", "volatile_load"):
            with self.subTest(name):
                self.assertEqual(self.outputs["default"][name], self.outputs["disabled"][name])


if __name__ == "__main__":
    unittest.main()
