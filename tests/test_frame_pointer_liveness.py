"""The opt-in -frac2-frame-pointer-liveness: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("frame_pointer_liveness",
    ROOT / "tools/compiler/transformers/frame_pointer_liveness.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-frame-pointer-liveness"
FUNCTIONS = ("dead_after_loop", "live_after_loop", "no_fp", "with_frame_pointer")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^" + name + r":.*?\.end\s+" + name, asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def loop_branch(body: str) -> tuple:
    """The branch on $2 that closes the loop, and the instruction in its delay slot."""
    lines = [line.strip() for line in body.splitlines()
             if line.strip() and not line.strip().startswith((".", "#"))]
    index = max(i for i, line in enumerate(lines) if re.match(r"bnel?\t\$2,\$0,", line))
    return lines[index].split("\t")[0], lines[index + 1]


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"flow.c": "\n".join(("a", transformer.LIVE_AT_END_OLD, transformer.DEAD_OLD,
                                      transformer.SET_OLD, transformer.USE_OLD,
                                      transformer.SET_USE_OLD, "b")),
                 "haifa-sched.c": "c\n" + transformer.DEATHS_OLD + "d\n",
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
            flow = (root / "flow.c").read_text()
            # live at end: one test; insn_dead_p, mark_set_1, both mark_used_regs cases: two each.
            self.assertEqual(flow.count(transformer.SPECIAL), 9)
            self.assertNotIn("regno != FRAME_POINTER_REGNUM", flow)
            self.assertNotIn("regno != HARD_FRAME_POINTER_REGNUM", flow)
            sched = (root / "haifa-sched.c").read_text()
            self.assertEqual(sched.count(transformer.SPECIAL), 2)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_frame_pointer_liveness = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_frame_pointer_liveness, 1,', top)
            flags = (root / "flags.h").read_text()
            self.assertIn("extern int flag_rac2_frame_pointer_liveness;", flags)
            # GCC 2.95's condition, and always true without the option.
            self.assertIn("(! flag_rac2_frame_pointer_liveness || ! reload_completed \\\n"
                          "   || frame_pointer_needed)", flags)
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        for name, label in (("haifa-sched.c", "attach_deaths"), ("flags.h", "option declaration")):
            with self.subTest(name), tempfile.TemporaryDirectory() as d:
                root = Path(d)
                files = self.sources(root, **{name: "unexpected text"})
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
            source.write_bytes((ROOT / "tests/fixtures/frame_pointer_liveness.c").read_bytes())
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

    def test_default_annuls_the_slot_that_sets_fp(self):
        self.assertEqual(loop_branch(self.outputs["default"]["dead_after_loop"]),
                         ("bnel", "addu\t$fp,$16,16"))

    def test_option_fills_the_same_slot_without_annulling(self):
        self.assertEqual(loop_branch(self.outputs["enabled"]["dead_after_loop"]),
                         ("bne", "addu\t$fp,$16,16"))
        default = self.outputs["default"]["dead_after_loop"].replace("bnel\t$2,$0,", "bne\t$2,$0,")
        self.assertEqual(default, self.outputs["enabled"]["dead_after_loop"])

    def test_fp_live_at_the_exit_stays_annulled(self):
        for label in ("default", "enabled"):
            self.assertEqual(loop_branch(self.outputs[label]["live_after_loop"]),
                             ("bnel", "addu\t$fp,$16,16"))

    def test_controls_are_unchanged(self):
        self.assertIn(".frame\t$fp,", self.outputs["default"]["with_frame_pointer"])
        self.assertNotIn("$fp,$16,16", self.outputs["default"]["no_fp"])
        for name in ("live_after_loop", "no_fp", "with_frame_pointer"):
            with self.subTest(name):
                self.assertEqual(self.outputs["default"][name], self.outputs["enabled"][name])


if __name__ == "__main__":
    unittest.main()
