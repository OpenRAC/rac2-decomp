"""tests/check_return_types.py: return type classes and name grouping (no clang needed)."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import check_return_types as crt  # noqa: E402


class ReturnTypes(unittest.TestCase):
    def test_return_part(self):
        self.assertEqual(crt.return_part("float (char *, char *)"), "float")
        self.assertEqual(crt.return_part("int ()"), "int")
        self.assertEqual(crt.return_part("void **(int)"), "void **")
        self.assertEqual(crt.return_part("void (int) __attribute__((noreturn))"), "void")
        self.assertEqual(crt.classify(crt.return_part("void (*(int))(void)"), {}), "pointer")

    def test_classes(self):
        typedefs = {"s32": "int", "f32": "float", "u64": "unsigned long long", "Vec": "struct Vec",
                    "ps2_u128": "unsigned int __attribute__((mode(TI)))", "T": "s32"}
        cases = {"void": "void", "int": "int32", "unsigned": "int32", "unsigned char": "int32",
                 "enum Mode": "int32", "s32": "int32", "T": "int32", "f32": "float",
                 "double": "double", "long": "int64", "unsigned long long": "int64", "u64": "int64",
                 "char *": "pointer", "const struct X *": "pointer", "Vec": "aggregate",
                 "struct Vec": "aggregate"}
        for text, expected in cases.items():
            self.assertEqual(crt.classify(text, typedefs), expected, text)

    def test_alias_joins_address(self):
        names = {"func_002E45C8", "F391de845_FUN_002E45C8", "X_FUN_00401000", "func_L04_00401000",
                 "func_00283B98_10"}
        key = crt.canonical(names)
        self.assertEqual(key["F391de845_FUN_002E45C8"], "func_002E45C8")
        self.assertEqual(key["X_FUN_00401000"], "func_L04_00401000")
        self.assertEqual(key["func_002E45C8"], "func_002E45C8")
        self.assertEqual(key["func_00283B98_10"], "func_00283B98")

    def test_conflict_needs_two_classes(self):
        def decl(name, cls, defined, file="a.c"):
            return {"name": name, "class": cls, "ret": cls, "defined": defined, "implicit": False,
                    "file": file, "line": 1, "col": 1, "len": len(name)}
        same = [{"path": "a.c", "decls": [decl("f", "int32", True)], "errors": []},
                {"path": "b.c", "decls": [decl("f", "int32", False, "b.c")], "errors": []}]
        self.assertEqual(crt.conflicts(same), {})
        other = [{"path": "a.c", "decls": [decl("f", "float", True)], "errors": []},
                 {"path": "b.c", "decls": [decl("f", "int32", False, "b.c")], "errors": []}]
        self.assertEqual(list(crt.conflicts(other)), ["f"])

    def test_exception_tolerates_only_listed_classes(self):
        def decl(cls, defined):
            return {"class": cls, "defined": defined}
        group = [decl("int32", True), decl("int32", False), decl("void", False)]
        self.assertTrue(crt.excepted(group, {"void"}))
        self.assertFalse(crt.excepted(group + [decl("float", False)], {"void"}))
        self.assertFalse(crt.excepted([decl("void", True), decl("int32", False)], {"void"}))


if __name__ == "__main__":
    unittest.main()
