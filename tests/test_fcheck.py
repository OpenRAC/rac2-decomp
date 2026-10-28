"""Tests for tools/fcheck.py's placement, splicing and return types: no game data, no toolchain."""
import struct
import sys
import unittest
from unittest import mock
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

    def test_named_variables_in_writable_sections_go_to_their_address(self):
        # An initialised sda global or a static is reached through its section's symbol, its
        # $gp-relative offset less the object's gp0 (.reginfo): still its named address.
        gp0 = 0x4000
        text = words(LW_GP | ((0 - gp0) & 0xFFFF), LW_GP | ((4 - gp0) & 0xFFFF), LUI_V0, ADDIU_V0 | 4, JR_RA, 0)
        reginfo = words(0, 0, 0, 0, 0, gp0)
        obj = {"sections": [section(""), section(".text.func_00200000", text, flags=6),
                            section(".sdata", words(0, 0), flags=3), section(".reginfo", reginfo, flags=2)],
               "symbols": [sym("", 0), sym("", 2, kind=fcheck.STT_SECTION), sym("func_00200000", 1),
                           sym("D_001A748C", 2, 0, kind=1, size=4), sym("D_001A7498", 2, 4, kind=1, size=4)],
               "relocations": {1: [(0, elf.R_MIPS_GPREL16, 1), (4, elf.R_MIPS_GPREL16, 1),
                                   (8, elf.R_MIPS_HI16, 1), (12, elf.R_MIPS_LO16, 1)]}}
        names = {"D_001A748C": 0x001A748C, "D_001A7498": 0x001A7498}
        p, image = placer(obj, named=names.get, writable=lambda s: 0x00238C80)
        self.assertEqual(word(image, 0) & 0xFFFF, (0x001A748C - GP) & 0xFFFF)
        self.assertEqual(word(image, 4) & 0xFFFF, (0x001A7498 - GP) & 0xFFFF)
        self.assertEqual(word(image, 8) & 0xFFFF, 0x001A)
        self.assertEqual(word(image, 12) & 0xFFFF, 0x7498)
        self.assertNotIn(2, p.where)          # the section itself was never needed
        self.assertEqual(fcheck.sda_alias("D_001A7C04_sda"), "D_001A7C04")
        self.assertEqual(fcheck.sda_alias("D_001A748C__gp"), "D_001A748C")
        self.assertIsNone(fcheck.sda_alias("D_001A748C"))

    def test_ref_values_read_from_retail_by_alignment(self):
        # The near miss has an extra instruction; its %hi/%lo of ref_..._00 (plus 0x3FFF) and
        # its call of ref_..._01 line up with retail's, which give the values.
        ADDIU_SP, OR_V0 = 0x27BDFFF0, 0x00431025
        mine = words(ADDIU_SP, LUI_V0, OR_V0, ADDIU_V0 | 0x3FFF, JAL, 0, JR_RA, 0)
        retail = words(ADDIU_SP, LUI_V0 | 0x0035, ADDIU_V0 | 0x5FBF, JAL | (0x00123450 >> 2), 0, JR_RA, 0)
        obj = {"sections": [section(""), section(".text.func_00200000", mine, flags=6)],
               "symbols": [sym("", 0), sym("func_00200000", 1, size=len(mine)),
                           sym("ref_L00_00200000_00", 0, kind=0), sym("ref_L00_00200000_01", 0, kind=0)],
               "relocations": {1: [(4, elf.R_MIPS_HI16, 2), (12, elf.R_MIPS_LO16, 2), (16, elf.R_MIPS_26, 3)]}}
        with mock.patch.object(fcheck, "boot_functions", lambda: {"func_00200000": (0x00200000, len(retail))}), \
                mock.patch.object(fcheck, "retail_bytes", lambda a, n: retail[:n]):
            values = fcheck.aligned_values(obj, "func_00200000")
        self.assertEqual(values, {"ref_L00_00200000_00": 0x00351FC0, "ref_L00_00200000_01": 0x00123450})

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
        # The boot's scripts end before level 00 runs; a level's script says which level it plays.
        self.assertLessEqual(fcheck.SCRIPTS["newgame"]["frames"], 1650)
        self.assertNotIn("level", fcheck.SCRIPTS["menu"])
        self.assertNotIn("level", fcheck.SCRIPTS["newgame"])
        for s in fcheck.SCRIPTS.values():
            self.assertEqual(s["phases"], sorted(s["phases"]))
            self.assertTrue(all(int(p.split(":")[0]) < s["frames"] for p in s["presses"]))


class LevelTests(unittest.TestCase):
    """Level placement: a function's place in level 00's program, resident boot functions below
    LEVEL_BASE, the boot build's values in a level, and which program a state is of."""
    BOOT_FUNCS = {"func_00150000": (0x00150000, 64),       # resident: below LEVEL_BASE
                  "func_00200000": (0x00200000, 32),       # replaced by the level; copy at 0x2A0100
                  "func_00210000": (0x00210000, 16)}       # replaced, no copy in level 00
    CATALOGUE = {"func_00200000": {0: 0x002A0100, 3: 0x002B0100, -1: 32},
                 "func_L00_002A0200": {0: 0x002A0200, -1: 8},
                 "func_L03_002B0300": {3: 0x002B0300, -1: 8}}

    def setUp(self):
        self.BOOT_FUNCS, self.CATALOGUE = dict(self.BOOT_FUNCS), dict(self.CATALOGUE)   # a test may add to its own
        fcheck.level_functions.cache_clear()
        self.patches = [mock.patch.object(fcheck, "boot_functions", lambda: self.BOOT_FUNCS),
                        mock.patch.object(fcheck, "catalogue", lambda: self.CATALOGUE)]
        for p in self.patches:
            p.start()

    def tearDown(self):
        for p in self.patches:
            p.stop()
        fcheck.level_functions.cache_clear()

    def test_level_functions(self):
        prog = fcheck.Program(0)
        self.assertEqual(prog.functions(), {"func_00150000": (0x00150000, 64), "func_00200000": (0x002A0100, 32),
                                            "func_L00_002A0200": (0x002A0200, 8)})
        self.assertTrue(prog.own("func_00200000") and prog.own("func_L00_002A0200"))
        self.assertFalse(prog.own("func_00150000") or prog.own("func_L03_002B0300") or prog.own("func_00210000"))
        self.assertTrue(fcheck.BOOT_PROGRAM.own("func_00200000"))
        self.assertFalse(fcheck.BOOT_PROGRAM.own("func_L00_002A0200"))

    def test_states_and_capture_lines(self):
        level = fcheck.Program(0)
        self.assertEqual(fcheck.script_program("level00"), level)
        self.assertEqual(fcheck.script_program("menu"), fcheck.BOOT_PROGRAM)
        self.assertEqual(fcheck.state_program("func_00200000", Path("states/level00/func_00200000.0.snap")), level)
        self.assertEqual(fcheck.state_program("func_00200000", Path("states/menu/func_00200000.0.snap")), fcheck.BOOT_PROGRAM)
        # a resident boot function called in the level is the boot's code
        self.assertEqual(fcheck.state_program("func_00150000", Path("states/level00/func_00150000.0.snap")), fcheck.BOOT_PROGRAM)
        code = bytes(range(32))
        with mock.patch.object(fcheck.Program, "retail", lambda self, a, n: code[:n] if a == 0x002A0100 else bytes(n)):
            line = fcheck.capture_line("func_00200000", level, 1).split()
            self.assertEqual(line, ["002a0100", "32", f"{fcheck.zlib.crc32(code):08x}", "func_00200000", "1"])
            self.assertEqual(fcheck.capture_line("func_00150000", level).split()[:2], ["00150000", "64"])
            self.assertIsNone(fcheck.capture_line("func_00210000", level))
            self.assertIsNone(fcheck.capture_line("func_L03_002B0300", level))

    def test_level_scripts(self):
        s = fcheck.SCRIPTS["level00"]
        self.assertEqual(s["level"], 0)
        self.assertGreaterEqual(s["phases"][0], 1500)          # level 00 is loaded by then
        self.assertTrue(all(int(p.split(":")[0]) < s["frames"] for p in s["sticks"]))

    def test_copy_map(self):
        # func_00200000's level copy is its code with the data it addresses moved: lui/addiu of
        # 0x00263640 and a lw at 0x00263690 in the boot, of 0x0028C080 and 0x0028C0D0 in the level.
        LUI_V1, LW_V1 = 0x3C030000, 0x8C620000      # lui $v1, 0; lw $v0, 0($v1)
        def code(a, b):
            return words(LUI_V0 | (a + 0x8000) >> 16, ADDIU_V0 | (a & 0xFFFF), LUI_V1 | (b + 0x8000) >> 16,
                         LW_V1 | (b & 0xFFFF), JR_RA, 0, 0, 0)
        boot, level = code(0x00263640, 0x00263690), code(0x0028C080, 0x0028C0D0)
        fcheck.copy_map.cache_clear()
        with mock.patch.object(fcheck, "retail_bytes", lambda a, n: boot[:n] if a == 0x00200000 else bytes(n)), \
                mock.patch.object(fcheck.Program, "retail", lambda self, a, n: level[:n] if a == 0x002A0100 else bytes(n)):
            self.assertEqual(fcheck.copy_map(0), {0x00263640: 0x0028C080, 0x00263690: 0x0028C0D0})
            self.assertEqual(fcheck.level_address(0, 0x00263640), 0x0028C080)
            self.assertEqual(fcheck.level_address(0, 0x00263660), 0x0028C0A0)   # between two pairs that agree
            self.assertIsNone(fcheck.level_address(0, 0x002636A0))              # past the last: not inferred
        fcheck.copy_map.cache_clear()

    def test_own_copy_pairs_win(self):
        # func_00200000's level copy stores the address of the level's own variant of a callback
        # (0x002A0400) where the boot's stores func_00210000: the copy's own pairing gives it,
        # though the catalogue would not (func_00210000 has no place in level 00).
        boot = words(LUI_V0 | 0x0021, ADDIU_V0, JR_RA, 0, 0, 0, 0, 0)
        level = words(LUI_V0 | 0x002A, ADDIU_V0 | 0x0400, JR_RA, 0, 0, 0, 0, 0)
        fcheck.copy_pairs.cache_clear()
        fcheck.copy_map.cache_clear()
        import build
        placement = build.Placement("00_aranos_tutorial", {"segments": [], "sections": []})
        with mock.patch.object(fcheck, "retail_bytes", lambda a, n: boot[:n] if a == 0x00200000 else bytes(n)), \
                mock.patch.object(fcheck.Program, "retail", lambda self, a, n: level[:n] if a == 0x002A0100 else bytes(n)), \
                mock.patch.object(fcheck, "program_placement", lambda level: placement), \
                mock.patch.object(fcheck, "program_placed", lambda key: {"values": {}}), \
                mock.patch.object(fcheck, "placed", lambda: {"values": {}}), \
                mock.patch.object(fcheck, "aligned_values", lambda *a: {}):
            self.assertEqual(fcheck.copy_pairs("func_00200000", 0), [(("data", 0x00210000), 0x002A0400)])
            r = fcheck.Resolver(fcheck.Program(0), "func_00200000", {"symbols": [], "sections": []}, {}, {})
            self.assertEqual(r.named("func_00210000"), 0x002A0400)
            self.assertEqual(r.function("func_00210000"), 0x002A0400)
            # another function's candidate has no such pairing: func_00210000 is not in level 00
            r = fcheck.Resolver(fcheck.Program(0), "func_L00_002A0200", {"symbols": [], "sections": []}, {}, {})
            self.assertIsNone(r.named("func_00210000"))
        fcheck.copy_pairs.cache_clear()
        fcheck.copy_map.cache_clear()

    def test_resolver_in_a_level(self):
        import build
        prog = fcheck.Program(0)
        placement = build.Placement("00_aranos_tutorial", {"segments": [], "sections": []})
        level_values = {"D_001B0960": "0x001b2000", "F1234_FUN_x": "0x002a0100"}
        boot_values = {"D_00140000_x": "0x00140000",         # resident data: kept
                       "r1_helper": "0x00200000",            # a replaced boot function: its copy
                       "r1_gone": "0x00210000",              # replaced, no copy: not known in the level
                       "D_001B0960": "0x001b0960"}           # the level's own value wins
        with mock.patch.object(fcheck, "program_placement", lambda level: placement), \
                mock.patch.object(fcheck, "program_placed", lambda key: {"values": level_values}), \
                mock.patch.object(fcheck, "placed", lambda: {"values": boot_values}), \
                mock.patch.object(fcheck, "aligned_values", lambda *a: {}), \
                mock.patch.object(fcheck, "level_address", lambda level, a: 0x0028C080 if a == 0x00263640 else None):
            r = fcheck.Resolver(prog, "func_L00_002A0200", {"symbols": [], "sections": []}, {}, {})
            self.assertEqual(r.named("func_00200000"), 0x002A0100)
            self.assertEqual(r.named("func_00150000"), 0x00150000)
            self.assertEqual(r.named("D_001B0960"), 0x001B2000)
            self.assertEqual(r.named("D_00140000_x"), 0x00140000)
            self.assertEqual(r.named("r1_helper"), 0x002A0100)
            self.assertIsNone(r.named("r1_gone"))
            self.assertEqual(r.named("D_L00_001B4000"), 0x001B4000)
            self.assertIsNone(r.named("D_L03_001B4000"))         # another level's data
            self.assertIsNone(r.named("D_001B5000"))             # a boot address the level replaces
            self.assertEqual(r.named("D_00160000"), 0x00160000)  # resident boot data
            self.assertIsNone(r.named("func_00210000"))          # a boot function not in the level
            self.assertEqual(r.named("D_00263640"), 0x0028C080)  # boot data the level's copies moved
            # a name stating a boot function's address that the boot table names otherwise
            self.BOOT_FUNCS["func_002001F8"] = (0x00200200, 8)
            self.CATALOGUE["func_002001F8"] = {0: 0x002A0300, -1: 8}
            fcheck.level_functions.cache_clear()
            r = fcheck.Resolver(prog, "func_L00_002A0200", {"symbols": [], "sections": []}, {}, {})
            self.assertEqual(r.named("func_00200200"), 0x002A0300)


if __name__ == "__main__":
    unittest.main()
