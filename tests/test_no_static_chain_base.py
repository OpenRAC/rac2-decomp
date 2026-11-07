"""The opt-in -frac2-no-static-chain-base: transformer drift and EE compiler-output regressions."""
import importlib.util
import os
from pathlib import Path
import re
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("no_static_chain_base",
    ROOT / "tools/compiler/transformers/no_static_chain_base.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "rac2-no-static-chain-base"
FUNCTIONS = ("fill_table", "fill_short", "fill_returned", "count_calls", r"bump\.\d+",
             "chain_store", r"store_twice\.\d+", "chain_local", r"store_and_local\.\d+")
PROFILES = {"default": [], "enabled": ["-f" + OPTION], "disabled": ["-f" + OPTION, "-fno-" + OPTION]}


def function_text(asm: str, name: str) -> str:
    """The function's assembly, its local labels renumbered in order of appearance."""
    body = re.search(r"(?ms)^(" + name + r"):.*?\.end\s+\1\b", asm).group()
    labels = {}
    return re.sub(r"\$L\d+", lambda m: labels.setdefault(m.group(), f"$L{len(labels)}"), body)


def instructions(body: str) -> list:
    return [line.strip() for line in body.splitlines()
            if line.strip() and not line.strip().startswith((".", "#")) and not line.strip().endswith(":")]


def save_positions(body: str) -> tuple:
    """Indexes of the callee saves (sd to $sp) and of the stores through $v0 ($2)."""
    lines = instructions(body)
    saves = [i for i, line in enumerate(lines) if re.match(r"sd\t\$\w+,\d+\(\$sp\)", line)]
    stores = [i for i, line in enumerate(lines) if re.match(r"sw\t\$\w+,\d+\(\$2\)", line)]
    return saves, stores


def chain_and_pointer_stores(body: str) -> list:
    """The order of the nested function's two stores: through the chain ($2) and through p ($4)."""
    return ["chain" if line.endswith("($2)") else "p" for line in instructions(body)
            if re.match(r"sw\t\$\d+,0\(\$[24]\)$", line)]


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path, **override) -> dict:
        files = {"alias.c": "a\n" + transformer.SEEDS_OLD + "b\n",
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
            alias = (root / "alias.c").read_text()
            # Both seeds, and only they, are guarded.
            self.assertEqual(alias.count("! flag_rac2_no_static_chain_base"), 2)
            self.assertEqual(alias.count("gen_rtx_ADDRESS (Pmode, static_chain_rtx)"), 1)
            self.assertEqual(alias.count("gen_rtx_ADDRESS (Pmode, struct_value_incoming_rtx)"), 1)
            top = (root / "toplev.c").read_text()
            self.assertIn("int flag_rac2_no_static_chain_base = 0;", top)
            self.assertIn('{"' + OPTION + '", &flag_rac2_no_static_chain_base, 1,', top)
            flags = (root / "flags.h").read_text()
            self.assertIn("extern int flag_rac2_no_static_chain_base;", flags)
            with self.assertRaisesRegex(ValueError, "already present"):
                transformer.patch(root)

    def test_source_drift_is_rejected_before_any_file_is_written(self):
        # The option-table anchor is checked on its own: toplev.c keeps its definition anchor.
        cases = (("alias.c", "unexpected text", "init_alias_analysis"),
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

    def test_nested_functions_mark_the_chain_seen(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            alias = (root / "alias.c").read_text()
            self.assertIn("else if (flag_rac2_no_static_chain_base\n\t       && current_function_needs_context", alias)
            self.assertIn("\treg_seen[REGNO (static_chain_rtx)] = 1;\n", alias)


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
            source.write_bytes((ROOT / "tests/fixtures/no_static_chain_base.c").read_bytes())
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

    def test_default_issues_every_save_before_the_table_stores(self):
        saves, stores = save_positions(self.outputs["default"]["fill_table"])
        self.assertEqual(len(saves), 9)
        self.assertEqual(len(stores), 31)
        self.assertLess(max(saves), min(stores))

    def test_option_lets_table_stores_pass_the_saves(self):
        saves, stores = save_positions(self.outputs["enabled"]["fill_table"])
        self.assertEqual(len(saves), 9)
        self.assertEqual(len(stores), 31)
        self.assertGreater(sum(save > min(stores) for save in saves), 0)
        # Only the schedule changes: the same instructions, in another order.
        self.assertEqual(sorted(instructions(self.outputs["default"]["fill_table"])),
                         sorted(instructions(self.outputs["enabled"]["fill_table"])))

    def test_controls_are_unchanged(self):
        self.assertNotIn("\tsd\t", self.outputs["default"]["fill_short"])
        for name in ("fill_short", "fill_returned", "count_calls", "chain_store", "chain_local"):
            with self.subTest(name):
                self.assertEqual(self.outputs["default"][name], self.outputs["enabled"][name])

    def test_nested_function_reads_and_writes_through_its_chain(self):
        # bump: both loads through the chain come before both stores, and `calls` is stored
        # before *out. The default copies the chain to $3; with the option it stays in $2.
        expected = {
            "default": ["subu\t$sp,$sp,16", "move\t$3,$2", "sw\t$2,0($sp)", "lw\t$2,0($3)",
                        "lw\t$5,4($3)", "addu\t$2,$2,$4", "sw\t$2,0($3)", "sw\t$2,0($5)", "j\t$31",
                        "addu\t$sp,$sp,16"],
            "enabled": ["subu\t$sp,$sp,16", "sw\t$2,0($sp)", "lw\t$3,0($2)", "lw\t$5,4($2)",
                        "addu\t$3,$3,$4", "sw\t$3,0($2)", "sw\t$3,0($5)", "j\t$31", "addu\t$sp,$sp,16"],
        }
        for label, lines in expected.items():
            with self.subTest(label):
                self.assertEqual(instructions(self.outputs[label][r"bump\.\d+"]), lines)

    def test_option_keeps_nested_stores_through_the_chain_in_order(self):
        # p == &x in both: the store to x through the chain must stay before the *p store.
        for name in (r"store_twice\.\d+", r"store_and_local\.\d+"):
            with self.subTest(name):
                self.assertEqual(chain_and_pointer_stores(self.outputs["enabled"][name]), ["chain", "p"])

    def test_default_keeps_the_2_95_seed(self):
        # The default stays stock: the seeded chain is a stack reference, which base_alias_check
        # says cannot alias an argument, so the *p store goes first in store_twice. (Without the
        # seed but without the reg_seen mark, as in 2.95.3, store_and_local's later
        # `$v0 = $sp + 16` gives the chain a stack base and swaps its stores the same way.)
        self.assertEqual(chain_and_pointer_stores(self.outputs["default"][r"store_twice\.\d+"]), ["p", "chain"])
        self.assertEqual(chain_and_pointer_stores(self.outputs["default"][r"store_and_local\.\d+"]),
                         ["chain", "p"])


if __name__ == "__main__":
    unittest.main()
