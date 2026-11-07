"""The opt-in -frac2-wide-saves-below: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("wide_saves_below",
    ROOT / "tools/compiler/transformers/wide_saves_below.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-wide-saves-below"
CASES = {"PLAIN": ("plain",), "ONE": ("wide_one",), "STICKY": ("wide_one", "plain_after"),
         "ARGS": ("wide_args",), "TWO": ("wide_two",)}
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION],
            "quad": ["-mastra-quad-saves"], "quad_enabled": ["-mastra-quad-saves", "-f" + OPTION],
            "quad_narrow": ["-mastra-quad-saves", "-frac2-narrow-saves-below"],
            "quad_narrow_enabled": ["-mastra-quad-saves", "-frac2-narrow-saves-below", "-f" + OPTION]}
WIDTH = {"sq": 16, "sd": 8, "s.d": 8, "s.s": 4}
ACCESS = re.compile(r"\t(sq|sd|lq|ld|s\.s|l\.s|s\.d|l\.d)\s+(\$f?\d+),(\d+)\(\$sp\)")


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def frame(body: str) -> int:
    return int(re.search(r"\tsubu\t\$sp,\$sp,(\d+)", body).group(1))


def accesses(body: str) -> list:
    """Every $sp-relative save, restore and load as (op, register, offset), in order."""
    return [(op, reg, int(off)) for op, reg, off in ACCESS.findall(body)]


def saves(body: str) -> list:
    return sorted(a for a in accesses(body) if a[0] in WIDTH)


def restores(body: str) -> list:
    """The epilogue's loads from the save area, in emission order."""
    size = frame(body)
    return [a for a in accesses(body) if a[0] in ("lq", "ld", "l.s", "l.d") and a[2] < size
            and a[1] != "$2"]


def overlapping(body: str) -> list:
    """Pairs of save slots that share bytes, taking sq's 16-byte alignment into account."""
    spans = []
    for op, reg, off in saves(body):
        start = off & ~15 if op == "sq" else off
        spans.append((start, start + WIDTH[op], reg))
    return [(a[2], b[2]) for i, a in enumerate(spans) for b in spans[i + 1:]
            if a[0] < b[1] and b[0] < a[1]]


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"config/mips/mips.c": ("a\n" + transformer.HELPERS_OLD + "b\n" + transformer.SIZE_OLD
                                        + "c\n" + transformer.SCOPE_OLD + "d\n" + transformer.START_OLD
                                        + "e\n" + transformer.SLOT_OLD),
                 "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
                 "flags.h": transformer.DECLARATION_OLD}
        files.update(override)
        (root / "config/mips").mkdir(parents=True, exist_ok=True)
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            mips = (root / "config/mips/mips.c").read_text()
            self.assertEqual(mips.count("\nrac2_wide_saves (mask)\n"), 1)
            self.assertEqual(mips.count("long rac2_wide = rac2_wide_saves (mask);"), 1)
            self.assertEqual(mips.count("int rac2_wide_on = rac2_wide_saves_p ();"), 1)
            self.assertEqual(mips.count("rac2_wide_offset = rac2_narrow_offset = end_offset;"), 1)
            self.assertEqual(mips.count("gp_offset = rac2_wide_offset,"), 1)
            self.assertIn("regno = reg_renumber != 0 ? reg_renumber[regno] : -1;", mips)
            self.assertIn("&& ! mips_astra_quad_saves", mips)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_wide_saves_below = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_wide_saves_below, 1,', top)
            self.assertIn("extern int flag_rac2_wide_saves_below;", (root / "flags.h").read_text())
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            files = self.sources(root, **{"flags.h": "unexpected declaration"})
            with self.assertRaisesRegex(ValueError, "option declaration"):
                transformer.patch(root)
            self.assertEqual({name: (root / name).read_text() for name in files}, files)

    def test_a_missing_slot_anchor_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            mips = ("a\n" + transformer.HELPERS_OLD + transformer.SIZE_OLD + transformer.SCOPE_OLD
                    + transformer.START_OLD)
            files = self.sources(root, **{"config/mips/mips.c": mips})
            with self.assertRaisesRegex(ValueError, "GP slot per register"):
                transformer.patch(root)
            self.assertEqual({name: (root / name).read_text() for name in files}, files)


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
            source.write_bytes((ROOT / "tests/fixtures/wide_saves_below.c").read_bytes())
            for case, functions in CASES.items():
                pre = root / (case + ".i")
                with pre.open("w") as out:
                    try:
                        subprocess.run([str(compiler / "cpp"), "-DCASE_" + case, str(source)],
                                       stdout=out, check=True)
                    except OSError:
                        if "RAC2_COMPILER_ROOT" in os.environ:
                            raise
                        raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                                "runs these checks in its build environment")
                for label, options in PROFILES.items():
                    asm = root / f"{case}-{label}.s"
                    subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                                    *options, str(pre), "-o", str(asm)], check=True)
                    subprocess.run([str(compiler / "as"), "-o", str(asm.with_suffix(".o")), str(asm)],
                                   check=True)
                    text = asm.read_text()
                    for name in functions:
                        cls.outputs[label, case, name] = function_text(text, name)

    def each(self, label: str):
        for case, functions in CASES.items():
            for name in functions:
                yield (case, name), self.outputs[label, case, name]

    def test_disabled_option_restores_default_for_every_function(self):
        self.assertEqual(dict(self.each("default")), dict(self.each("disabled")))

    def test_option_has_no_effect_with_quad_saves(self):
        self.assertEqual(dict(self.each("quad")), dict(self.each("quad_enabled")))
        self.assertEqual(dict(self.each("quad_narrow")), dict(self.each("quad_narrow_enabled")))

    def test_control_without_timode_is_unchanged(self):
        self.assertEqual(self.outputs["default", "PLAIN", "plain"], self.outputs["enabled", "PLAIN", "plain"])
        self.assertEqual(overlapping(self.outputs["default", "PLAIN", "plain"]), [])

    def test_default_overlaps_the_wide_save_with_its_neighbour(self):
        # The stock layout this option corrects: sq $17,8($sp) writes 0..15 over $16's slot.
        body = self.outputs["default", "ONE", "wide_one"]
        self.assertIn(("sq", "$17", 8), saves(body))
        self.assertEqual(overlapping(body), [("$16", "$17")])

    def test_wide_save_takes_the_bottom_slot(self):
        body = self.outputs["enabled", "ONE", "wide_one"]
        self.assertEqual(saves(body), sorted([("sq", "$17", 0), ("sd", "$16", 16), ("sd", "$18", 24),
                                              ("sd", "$31", 32), ("s.s", "$f20", 48)]))
        self.assertEqual(frame(body), 64)
        self.assertEqual([r for _, r, _ in restores(body)], ["$16", "$17", "$18", "$31", "$f20"])

    def test_every_enabled_frame_is_sound(self):
        for key, body in self.each("enabled"):
            with self.subTest(key):
                self.assertEqual(overlapping(body), [])
                self.assertTrue(all(off % 16 == 0 for op, _, off in saves(body) if op == "sq"))
                self.assertTrue(all(off < frame(body) for _, _, off in saves(body)))

    def test_stack_arguments_follow_the_larger_frame(self):
        default, enabled = self.outputs["default", "ARGS", "wide_args"], self.outputs["enabled", "ARGS", "wide_args"]
        self.assertEqual((frame(default), frame(enabled)), (32, 48))
        for body in (default, enabled):
            loads = sorted(off for op, _, off in accesses(body) if op == "ld" and off >= frame(body))
            self.assertEqual(loads, [frame(body), frame(body) + 8])
        self.assertEqual(saves(enabled), sorted([("sq", "$16", 0), ("sd", "$17", 16), ("sd", "$18", 24),
                                                 ("sd", "$31", 32)]))

    def test_two_wide_saves_ascend_from_the_bottom(self):
        body = self.outputs["enabled", "TWO", "wide_two"]
        self.assertEqual(saves(body), sorted([("sq", "$17", 0), ("sq", "$18", 16), ("sd", "$16", 32),
                                              ("sd", "$19", 40), ("sd", "$31", 48)]))
        self.assertEqual([r for _, r, _ in restores(body)], ["$16", "$17", "$18", "$19", "$31"])

    def test_a_widened_mode_carries_into_later_functions_of_the_unit(self):
        # mips_reg_mode stays TImode for $17 after wide_one; with the option the later save
        # gets a slot of its width instead of overlapping, which is why a witness has a unit
        # of its own.
        default = self.outputs["default", "STICKY", "plain_after"]
        enabled = self.outputs["enabled", "STICKY", "plain_after"]
        self.assertIn(("sq", "$17", 8), saves(default))
        self.assertNotEqual(overlapping(default), [])
        self.assertIn(("sq", "$17", 0), saves(enabled))
        self.assertEqual(overlapping(enabled), [])
        self.assertEqual(self.outputs["enabled", "STICKY", "wide_one"], self.outputs["enabled", "ONE", "wide_one"])


if __name__ == "__main__":
    unittest.main()
