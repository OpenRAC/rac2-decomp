"""Tests for tools/fcheck.py's placement, splicing and return types: no game data, no toolchain."""
import struct
import sys
import unittest
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf  # noqa: E402
import fcheck  # noqa: E402

GP = fcheck.GP


def words(*ws):
    return b"".join(struct.pack("<I", w & 0xFFFFFFFF) for w in ws)


def word(blob, at):
    return struct.unpack_from("<I", blob, at)[0]


def section(name, data=b"", kind=elf.SHT_PROGBITS, flags=2, align=4, size=None):
    return {"name": name, "type": kind, "flags": flags, "align": align,
            "size": len(data) if size is None else size, "data": data}


def sym(name, sec, value=0, kind=fcheck.STT_FUNC, size=0):
    return {"name": name, "section": sec, "value": value, "type": kind, "size": size, "bind": 1}


def placer(obj, name="func_00200000", named=None, function=None, writable=None, literal=None):
    p = fcheck.Placer(obj, name, named or (lambda n: None), function or (lambda n: None),
                      writable or (lambda s: None), literal or (lambda d, s, o: None))
    p.relocate()
    return p, bytes(p.image)


LUI_V0 = 0x3C020000          # lui $v0, 0
ADDIU_V0 = 0x24420000        # addiu $v0, $v0, 0
LW_V0 = 0x8C420000           # lw $v0, 0($v0)
LWC1_GP = 0xC7800000         # lwc1 $f0, 0($gp)
LW_GP = 0x8F820000           # lw $v0, 0($gp)
JAL = 0x0C000000
JR_RA = 0x03E00008


class PlacerTests(unittest.TestCase):
    def test_jump_table_entries_go_to_the_placed_code(self):
        # .text.f: lui/lw of the table (.rodata), the table holds two case offsets into .text.f.
        text = words(LUI_V0, LW_V0, JR_RA, 0, 0, 0)
        rodata = words(0x10, 0x14)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6), section(".rodata", rodata)],
               "symbols": [sym("", 0), sym("", 1, kind=fcheck.STT_SECTION), sym("", 2, kind=fcheck.STT_SECTION),
                           sym("func_00200000", 1)],
               "relocations": {1: [(0, elf.R_MIPS_HI16, 2), (4, elf.R_MIPS_LO16, 2)],
                               2: [(0, elf.R_MIPS_32, 1), (4, elf.R_MIPS_32, 1)]}}
        p, image = placer(obj)
        self.assertEqual(p.entry, fcheck.BASE)
        table = p.where[2]
        self.assertGreaterEqual(table, fcheck.BASE + len(text))
        self.assertEqual(word(image, table - fcheck.BASE), fcheck.BASE + 0x10)
        self.assertEqual(word(image, table - fcheck.BASE + 4), fcheck.BASE + 0x14)
        hi, lo = word(image, 0) & 0xFFFF, word(image, 4) & 0xFFFF
        self.assertEqual((hi << 16) + (lo - 0x10000 if lo & 0x8000 else lo), table)

    def test_writable_data_stays_at_retail_and_unplaced_data_is_noted(self):
        text = words(LUI_V0, ADDIU_V0, LUI_V0, ADDIU_V0, JR_RA, 0)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6),
                            section(".data", words(1, 2), flags=3), section(".bss", kind=elf.SHT_NOBITS, flags=3, size=16)],
               "symbols": [sym("", 0), sym("", 2, kind=fcheck.STT_SECTION), sym("", 3, kind=fcheck.STT_SECTION),
                           sym("func_00200000", 1)],
               "relocations": {1: [(0, elf.R_MIPS_HI16, 1), (4, elf.R_MIPS_LO16, 1),
                                   (8, elf.R_MIPS_HI16, 2), (12, elf.R_MIPS_LO16, 2)]}}
        p, image = placer(obj, writable=lambda s: 0x00238C80 if s == ".data" else None)
        self.assertEqual(p.where[2], 0x00238C80)
        self.assertEqual(word(image, 0) & 0xFFFF, 0x0024)
        self.assertEqual(word(image, 4) & 0xFFFF, 0x8C80)
        self.assertTrue(fcheck.BASE < p.where[3] < fcheck.LIMIT)
        self.assertTrue(any(".bss" in n for n in p.notes))

    def test_named_symbols_calls_and_helpers(self):
        text = words(JAL, 0, JAL, 0, JR_RA, 0)
        helper = words(JR_RA, 0)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6),
                            section(".text.helper", helper, flags=6)],
               "symbols": [sym("", 0), sym("", 2, kind=fcheck.STT_SECTION), sym("func_00200000", 1),
                           sym("func_00123450", 0, kind=0), sym("helper", 2)],
               "relocations": {1: [(0, elf.R_MIPS_26, 3), (8, elf.R_MIPS_26, 1)]}}
        p, image = placer(obj, named=lambda n: 0x00123450 if n == "func_00123450" else None)
        self.assertEqual((word(image, 0) & 0x3FFFFFF) << 2, 0x00123450)
        self.assertEqual((word(image, 8) & 0x3FFFFFF) << 2, p.where[2])
        self.assertTrue(any("helper" in n for n in p.notes))

    def test_gp_relative(self):
        text = words(LW_GP, LWC1_GP, JR_RA, 0)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6),
                            section(".lit4", words(0x3F800000))],
               "symbols": [sym("", 0), sym("", 2, kind=fcheck.STT_SECTION), sym("func_00200000", 1),
                           sym("D_001AF000", 0, kind=1)],
               "relocations": {1: [(0, elf.R_MIPS_GPREL16, 3), (4, 8, 1)]}}
        found = []
        p, image = placer(obj, named=lambda n: 0x001AF000 if n == "D_001AF000" else None,
                          literal=lambda d, s, o: found.append((d, s, o)) or GP - 0x10)
        self.assertEqual(word(image, 0) & 0xFFFF, 0x001AF000 - GP)
        self.assertEqual(word(image, 4) & 0xFFFF, (-0x10) & 0xFFFF)
        self.assertEqual(found, [(words(0x3F800000), ".lit4", 0)])
        far = dict(obj, symbols=obj["symbols"][:3] + [sym("D_00300000", 0, kind=1)])
        with self.assertRaises(fcheck.Link):
            placer(far, named=lambda n: 0x00300000)
        with self.assertRaises(fcheck.Link):
            placer(obj, named=lambda n: 0x001AF000, literal=lambda d, s, o: None)

    def test_hi_pairs_with_the_next_lo_in_object_order(self):
        # %hi at +8 pairs with the %lo at +0 listed after it (a loop's last delay slot).
        text = words(ADDIU_V0 | 0x10, 0, LUI_V0, JR_RA, 0, 0)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6)],
               "symbols": [sym("", 0), sym("func_00200000", 1), sym("D_00238000", 0, kind=1)],
               "relocations": {1: [(8, elf.R_MIPS_HI16, 2), (0, elf.R_MIPS_LO16, 2)]}}
        p, image = placer(obj, named=lambda n: 0x0023FFF8)
        self.assertEqual(word(image, 8) & 0xFFFF, 0x0024)
        self.assertEqual(word(image, 0) & 0xFFFF, 0x0008)
        bad = dict(obj, relocations={1: [(8, elf.R_MIPS_HI16, 2)]})
        with self.assertRaises(fcheck.Link):
            placer(bad, named=lambda n: 0x0023FFF8)

    def test_missing_function(self):
        obj = {"sections": [section("")], "symbols": [sym("", 0)], "relocations": {}}
        with self.assertRaises(fcheck.Link):
            placer(obj)


class SourceTests(unittest.TestCase):
    UNIT = ('#include "common.h"\n\nINCLUDE_ASM("asm/x", func_00200000);\n\n'
            "static int\nfunc_00200010(int a)\n{\n    return a + 1;\n}\n\nint func_00200020(void) { return 0; }\n")

    def test_splice_stub(self):
        t = fcheck.splice(self.UNIT, "func_00200000", "int func_00200000(void) {\n    return 2;\n}\n")
        self.assertNotIn("INCLUDE_ASM", t)
        self.assertIn("return 2;", t)
        self.assertIn("func_00200010(int a)", t)

    def test_splice_definition_with_type_line(self):
        t = fcheck.splice(self.UNIT, "func_00200010", "int func_00200010(int a)\n{\n    return a - 1;\n}\n")
        self.assertNotIn("return a + 1", t)
        self.assertNotIn("static int\n", t)
        self.assertIn("int func_00200020(void)", t)
        with self.assertRaises(fcheck.Link):
            fcheck.splice(self.UNIT, "func_00300000", "")

    def test_one_line_definitions(self):
        unit = ('void func_00200000(int *a) { *a = 1; }\n\n/* } */\nvoid func_00200008(int *a) { *a = 2; }\n'
                'int func_00200010(void)\n{\n    char *s = "}";\n    return s[0];\n}\n')
        a, b = fcheck.find_definition(unit, "func_00200000")
        self.assertEqual(unit[a:b], "void func_00200000(int *a) { *a = 1; }\n")
        a, b = fcheck.find_definition(unit, "func_00200010")
        self.assertTrue(unit[a:b].startswith("int func_00200010(void)") and unit[a:b].endswith("}\n"))
        t = fcheck.splice(unit, "func_00200000", "void func_00200000(int *a) { *a = 3; }")
        self.assertIn("*a = 2;", t)
        self.assertNotIn("*a = 1;", t)

    def test_returns(self):
        self.assertEqual(fcheck.returns("func_1", "void func_1(int a) {\n}"), "void")
        self.assertEqual(fcheck.returns("func_1", "static int\nfunc_1(int a)\n{\n}"), "int")
        self.assertEqual(fcheck.returns("func_1", "char *func_1(void) {\n}"), "int")
        self.assertEqual(fcheck.returns("func_1", "f32 func_1(void) {\n}"), "float")
        self.assertEqual(fcheck.returns("func_1", "unsigned long func_1(void) {\n}"), "long")
        self.assertEqual(fcheck.returns("func_1", "u64 func_1(void) {\n}"), "long")
        self.assertEqual(fcheck.returns("func_1", "struct S func_1(void) {\n}"), "void")
        self.assertEqual(fcheck.returns("func_1", "extern int func_2(void);\nu16 func_1(void) {\n}"), "int")

    def test_scripts_stop_before_a_level_runs(self):
        self.assertLessEqual(fcheck.SCRIPTS["newgame"]["frames"], 1650)
        for s in fcheck.SCRIPTS.values():
            self.assertEqual(s["phases"], sorted(s["phases"]))
            self.assertTrue(all(int(p.split(":")[0]) < s["frames"] for p in s["presses"]))


if __name__ == "__main__":
    unittest.main()
