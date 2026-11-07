"""The opt-in -frac2-no-extra-increment-givs: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("no_extra_increment_givs",
    ROOT / "tools/compiler/transformers/no_extra_increment_givs.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-no-extra-increment-givs"
FUNCTIONS = ("fill", "fill_index", "fill_once", "fill_volatile", "fill_some", "clear16", "pairs")
CONTROLS = ("fill_once", "fill_volatile", "fill_some", "clear16")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^(" + name + r"):.*?\.end\s+\1\b", asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def instructions(body: str) -> list:
    return [line.strip() for line in body.splitlines()
            if line.strip() and not line.strip().startswith((".", "#")) and not line.strip().endswith(":")]


def stores(body: str) -> list:
    """(offset, base register) of every doubleword store."""
    return [(int(m.group(1)), m.group(2)) for line in instructions(body)
            for m in [re.match(r"sd\t\$\d+,(-?\d+)\((\$\d+)\)$", line)] if m]


def increments(body: str, register: str) -> list:
    """The constant steps of `addu reg,reg,C` for one register."""
    r = re.escape(register)
    return [int(m.group(1)) for line in instructions(body)
            for m in [re.match(r"addu\t" + r + "," + r + r",(-?\d+)$", line)] if m]


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"loop.c": "a\n" + transformer.GUARD_OLD + "    {\nb\n",
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
            loop = (root / "loop.c").read_text()
            self.assertIn("  if (! flag_rac2_no_extra_increment_givs\n"
                          "      && n_extra_increment && ! loop_has_volatile)\n    {\n", loop)
            self.assertNotIn("  if (n_extra_increment && ! loop_has_volatile)\n", loop)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_no_extra_increment_givs = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_no_extra_increment_givs, 1,', top)
            # The new entry follows its anchor, the -frac2-no-static-chain-base entry.
            self.assertLess(top.index(transformer.OPTION_OLD), top.index('{"' + OPTION + '"'))
            flags = (root / "flags.h").read_text()
            self.assertIn("extern int flag_rac2_no_extra_increment_givs;", flags)
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        # The option-table anchor is checked on its own: toplev.c keeps its definition anchor.
        cases = (("loop.c", "unexpected text", "strength_reduce guard"),
                 ("loop.c", transformer.GUARD_OLD * 2, "strength_reduce guard"),
                 ("toplev.c", "unexpected text", "option definition"),
                 ("toplev.c", transformer.DEFINITION_OLD + "unexpected option table\n", "option table"),
                 ("flags.h", "unexpected text", "option declaration"))
        for name, text, label in cases:
            with self.subTest(label=label, text=text[:20]), tempfile.TemporaryDirectory() as d:
                root = Path(d)
                files = self.sources(root, **{name: text})
                with self.assertRaisesRegex(ValueError, label):
                    transformer.patch(root)
                self.assertEqual({n: (root / n).read_text() for n in files}, files)

    def test_check_dbra_loop_is_not_edited(self):
        # The guard text names loop_has_volatile once; check_dbra_loop's own test is elsewhere.
        self.assertEqual(transformer.GUARD_NEW.count("loop_has_volatile"), 1)
        self.assertNotIn("check_dbra_loop", transformer.GUARD_NEW)


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
            source.write_bytes((ROOT / "tests/fixtures/no_extra_increment_givs.c").read_bytes())
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

    def test_disabled_option_restores_default_for_every_function(self):
        self.assertEqual(self.outputs["default"], self.outputs["disabled"])

    def test_default_splits_the_cursor_into_givs(self):
        for name in ("fill", "fill_index"):
            with self.subTest(name):
                found = stores(self.outputs["default"][name])
                self.assertEqual(len(found), 4)
                # Several reduced pointers (fill shares one between its first and last store,
                # -24 and 0), each stepped once by the whole iteration's 32 bytes.
                self.assertGreater(len({base for _, base in found}), 2)
                for base in {base for _, base in found}:
                    # (a pointer's start, before the loop, can be an addu of the cursor too)
                    self.assertEqual(increments(self.outputs["default"][name], base).count(32), 1)
                    self.assertNotIn(8, increments(self.outputs["default"][name], base))

    def test_option_keeps_every_increment_of_the_cursor(self):
        for name in ("fill", "fill_index"):
            with self.subTest(name):
                found = stores(self.outputs["enabled"][name])
                self.assertEqual(len(found), 4)
                # One cursor, every store at offset 0, stepped by 8 after each store.
                self.assertEqual({offset for offset, _ in found}, {0})
                (cursor,) = {base for _, base in found}
                self.assertEqual(increments(self.outputs["enabled"][name], cursor), [8, 8, 8, 8])

    def test_controls_are_unchanged(self):
        for name in CONTROLS:
            with self.subTest(name):
                self.assertEqual(self.outputs["default"][name], self.outputs["enabled"][name])

    def test_a_volatile_read_already_keeps_the_increments(self):
        # loop_has_volatile skips the conversion in the default too: the cursor in $4 keeps both.
        self.assertEqual(increments(self.outputs["default"]["fill_volatile"], "$4"), [8, 8])

    def test_check_dbra_loop_still_reverses_a_single_increment_counter(self):
        for label in ("default", "enabled"):
            with self.subTest(label):
                lines = instructions(self.outputs[label]["clear16"])
                self.assertIn("li\t$2,15\t\t\t# 0xf", lines)
                self.assertTrue(any(line.startswith("bgez\t") for line in lines))

    def test_a_twice_incremented_counter_counts_up_with_the_option(self):
        default = instructions(self.outputs["default"]["pairs"])
        enabled = instructions(self.outputs["enabled"]["pairs"])
        # Default: one increment became a giv, so check_dbra_loop reversed the count (30 down by 2).
        self.assertIn("li\t$3,30\t\t\t# 0x1e", default)
        self.assertTrue(any(line.startswith("bgez\t") for line in default))
        # Option: the counter keeps both increments, as written, and the loop counts up to 32.
        self.assertIn("slt\t$2,$3,32", enabled)
        self.assertFalse(any(line.startswith("bgez\t") for line in enabled))
        self.assertEqual(increments(self.outputs["enabled"]["pairs"], "$4"), [8, 8])


if __name__ == "__main__":
    unittest.main()
