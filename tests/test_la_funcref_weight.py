"""The opt-in -frac2-la-funcref-weight: transformer drift and EE compiler-output controls."""
import importlib.util
import os
from pathlib import Path
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
spec = importlib.util.spec_from_file_location("la_funcref_weight",
    ROOT / "tools/compiler/transformers/la_funcref_weight.py")
transformer = importlib.util.module_from_spec(spec)
spec.loader.exec_module(transformer)

OPTION = "-frac2-la-funcref-weight"
PROFILES = {"default": [], "enabled": [OPTION], "disabled": [OPTION, "-fno-rac2-la-funcref-weight"]}


class TransformerTests(unittest.TestCase):
    def sources(self, root: Path) -> dict:
        files = {
            "local-alloc.c": "a\n" + transformer.PROTO_OLD + "b\n" + transformer.ORDER_OLD + "c\n",
            "c-decl.c": "void\ncopy_lang_decl (node)\n{\n}\n",
            "toplev.c": transformer.DEFINITION_OLD + transformer.OPTION_OLD,
            "flags.h": transformer.DECLARATION_OLD,
        }
        for name, contents in files.items():
            (root / name).write_text(contents)
        return files

    def test_each_insertion_point_is_used_once(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            local = (root / "local-alloc.c").read_text()
            self.assertIn("if (flag_rac2_la_funcref_weight)", local)
            self.assertIn("rac2_symbol_is_function PROTO((char *))", local)
            self.assertLess(local.index("flag_rac2_la_funcref_weight"), local.index("qty_order = (int *)"))
            self.assertIn("rac2_symbol_is_function (name)", (root / "c-decl.c").read_text())
            self.assertIn('"rac2-la-funcref-weight"', (root / "toplev.c").read_text())
            self.assertIn("extern int flag_rac2_la_funcref_weight;", (root / "flags.h").read_text())

    def test_already_applied_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.sources(root)
            transformer.patch(root)
            with self.assertRaises(ValueError):
                transformer.patch(root)

    def test_missing_insertion_point_changes_nothing(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            files = self.sources(root)
            (root / "local-alloc.c").write_text("no anchor\n")
            files["local-alloc.c"] = "no anchor\n"
            with self.assertRaises(ValueError):
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
            for fixture in ("la_funcref_weight", "la_funcref_weight_data"):
                source = root / (fixture + ".c")
                source.write_bytes((ROOT / "tests/fixtures" / (fixture + ".c")).read_bytes())
                with (root / (fixture + ".i")).open("w") as out:
                    try:
                        subprocess.run([str(compiler / "cpp"), str(source)], stdout=out, check=True)
                    except OSError:
                        if "RAC2_COMPILER_ROOT" in os.environ:
                            raise
                        raise unittest.SkipTest("EE compiler not runnable on this host; tools/compiler/build.sh "
                                                "runs these checks in its build environment")
                for label, options in PROFILES.items():
                    asm = root / f"{fixture}-{label}.s"
                    subprocess.run([str(compiler / "cc1"), "-quiet", "-O2", "-G0", "-ffunction-sections",
                                    *options, str(root / (fixture + ".i")), "-o", str(asm)], check=True)
                    subprocess.run([str(compiler / "as"), "-o", str(asm.with_suffix(".o")), str(asm)],
                                   check=True)
                    cls.outputs[fixture, label] = asm.read_text()

    def register_of(self, fixture: str, label: str, symbol: str) -> str:
        for line in self.outputs[fixture, label].splitlines():
            parts = line.split()
            if parts and parts[0] == "addiu" and f"%lo({symbol})" in line:
                return parts[1].split(",")[0]
        self.fail(f"no %lo({symbol}) in {fixture} {label}")

    def test_disabled_option_restores_default(self):
        for fixture in ("la_funcref_weight", "la_funcref_weight_data"):
            self.assertEqual(self.outputs[fixture, "default"], self.outputs[fixture, "disabled"])

    def test_function_address_quantity_is_allocated_earlier(self):
        fixture = "la_funcref_weight"
        default = [self.register_of(fixture, "default", s) for s in ("page", "table", "upd_fn")]
        enabled = [self.register_of(fixture, "enabled", s) for s in ("page", "table", "upd_fn")]
        self.assertEqual(default, ["$7", "$8", "$9"])
        self.assertEqual(enabled, ["$8", "$9", "$7"])

    def test_data_addresses_are_unchanged(self):
        self.assertEqual(self.outputs["la_funcref_weight_data", "default"],
                         self.outputs["la_funcref_weight_data", "enabled"])


if __name__ == "__main__":
    unittest.main()
