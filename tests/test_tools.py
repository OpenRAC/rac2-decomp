"""Tests for tools/levels.py and tools/elf.py: no game data, no toolchains."""
import json
import struct
import sys
import tempfile
import unittest
from unittest.mock import patch
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf  # noqa: E402
import levels  # noqa: E402
import check as function_check  # noqa: E402


def j(target):
    return (2 << 26) | (target >> 2)


def lui(rt, imm):
    return (0x0F << 26) | (rt << 16) | imm


def addiu(rt, rs, imm):
    return (0x09 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def lw(rt, rs, imm):
    return (0x23 << 26) | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


JR_RA, NOP = 0x03E00008, 0


class R5900Diagnostics(unittest.TestCase):
    def test_ee_specific_words_keep_their_operands(self):
        cases = ((0x00A22818, "mult", ["$a1", "$a1", "$v0"]),
                 (0x700014A9, "por", ["$v0", "$zero", "$zero"]),
                 (0x70851389, "pcpyld", ["$v0", "$a0", "$a1"]),
                 (0x78A20010, "lq", ["$v0", "0x10($a1)"]),
                 (0x7FA20020, "sq", ["$v0", "0x20($sp)"]),
                 (0x68A20000, "ldl", ["$v0", "0x0($a1)"]),
                 (0x6CA20000, "ldr", ["$v0", "0x0($a1)"]))
        for word, mnemonic, operands in cases:
            with self.subTest(word=hex(word)):
                rendered = function_check.disassemble(struct.pack("<I", word), 0x1000)[0]
                instruction, args = rendered.split(None, 1)
                self.assertEqual(instruction, mnemonic)
                self.assertEqual([x.strip() for x in args.split(",")], operands)


def code(*w):
    return struct.pack(f"<{len(w)}I", *w)


class LevelExtents(unittest.TestCase):
    def test_proven_entries_preserve_end_and_replay(self):
        cases = ((0, 0x354DE8, 288, 0x354DF8),
                 (0, 0x3D54A8, 4432, 0x3D54B0),
                 (0, 0x40EA98, 1548, 0x40EAA0),
                 (23, 0x4277B0, 52, 0x4277B8))
        for number, address, size, entry in cases:
            with self.subTest(address=address):
                new_address, new_size = levels.level_extent(number, address, size)
                self.assertEqual(new_address, entry)
                self.assertEqual(new_address + new_size, address + size)
                self.assertEqual(levels.level_extent(number, new_address, new_size),
                                 (new_address, new_size))

    def test_same_address_in_another_level_is_unchanged(self):
        self.assertEqual(levels.level_extent(7, 0x3D54A8, 4432), (0x3D54A8, 4432))
        self.assertEqual(levels.level_extent(10, 0x4277B0, 52), (0x4277B0, 52))

    def test_invalid_corrected_extent_is_rejected(self):
        with self.assertRaises(ValueError):
            levels.level_extent(0, 0x354DE8, 16)
        with self.assertRaises(ValueError):
            levels.level_extent(23, 0x4277B0, 8)


class FunctionExtents(unittest.TestCase):
    def test_preprologue_load_entry_recovers_only_the_known_legacy_extent(self):
        name = "func_L05_0042AFE0"
        for base in (0x210000, 0x310008, 0x410010):
            for displacement in (0, 0x2000, 0x4000, 0x6000):
                original = base + displacement
                with self.subTest(address=original):
                    expected = (original + 8, 724)
                    self.assertEqual(levels.function_extent(name, original, 732), expected)
                    self.assertEqual(levels.function_extent(name, original + 12, 720), expected)
                    self.assertEqual(levels.function_extent(name, *expected), expected)
                    self.assertEqual(sum(expected), original + 732)
        for size in (716, 728, 736):
            with self.subTest(size=size), self.assertRaises(ValueError):
                levels.function_extent(name, 0x210000, size)
        self.assertEqual(levels.function_extent("unrelated", 0x21000C, 720), (0x21000C, 720))

    def test_named_residues_require_the_measured_size(self):
        for name, size in levels.FUNCTION_RESIDUES.items():
            with self.subTest(name=name):
                self.assertTrue(levels.function_residue(name, size))
                with self.assertRaises(ValueError):
                    levels.function_residue(name, size + 4)
        self.assertFalse(levels.function_residue("func_00002000", 4))

    def test_named_entries_preserve_ends_and_replay_at_each_release_address(self):
        for name, (original, skip) in levels.FUNCTION_ENTRY_OFFSETS.items():
            for address in (0x210000, 0x220008, 0x230010):
                with self.subTest(name=name, address=address):
                    entry, size = levels.function_extent(name, address, original)
                    self.assertEqual((entry, size), (address + skip, original - skip))
                    self.assertEqual(entry + size, address + original)
                    self.assertEqual(levels.function_extent(name, entry, size), (entry, size))

    def test_unrelated_name_is_not_shifted_and_unexpected_sizes_fail(self):
        self.assertEqual(levels.function_extent("func_00002000", 0x2000, 64), (0x2000, 64))
        for name, size in (("func_002C38A0", 60), ("func_00335918", 64)):
            with self.subTest(name=name), self.assertRaises(ValueError):
                levels.function_extent(name, 0x2000, size)


class Filler(unittest.TestCase):
    """The linker's filler between the bodies: stack adjustments and nops only."""

    def test_stack_adjustments_and_nops_are_filler(self):
        self.assertTrue(levels.is_padding(code(0x27BD0030, 0, 0x27BD0010)))
        self.assertTrue(levels.is_padding(code()))
        self.assertTrue(levels.is_padding(code(0x00000000)))

    def test_arithmetic_is_not_filler(self):
        # addu $t0,$t1,$t2
        self.assertFalse(levels.is_padding(code(0x012A4021)))
        # addiu $sp,$a0,16: a write through a register, not a stack adjustment
        self.assertFalse(levels.is_padding(code(0x249D0010)))

    def test_a_body_without_a_return_can_still_be_code(self):
        # func_00115E90 is matched C and has no jr $ra: it ends in a trap.
        self.assertFalse(levels.is_padding(code(0x27BD0030, 0x00000000, 0x0C0A0A5E)))


class EpilogueResidue(unittest.TestCase):
    """The word a body leaves behind after its `jr $ra` and its delay slot."""

    def test_the_word_after_a_jr_is_the_residue(self):
        previous = code(0x03E00008, 0x27BD0010)          # jr $ra ; addiu $sp,$sp,0x10
        self.assertTrue(levels.is_epilogue_residue(code(0x00621021), previous))

    def test_a_body_that_does_not_follow_a_jr_is_not_the_residue(self):
        previous = code(0x0080802D, 0x27BD0010)
        self.assertFalse(levels.is_epilogue_residue(code(0x00621021), previous))

    def test_more_than_one_word_is_not_the_residue(self):
        previous = code(0x03E00008, 0x27BD0010)
        self.assertFalse(levels.is_epilogue_residue(code(0x00621021, 0), previous))


class Identity(unittest.TestCase):
    def test_words_and_trim(self):
        self.assertEqual(levels.words(code(1, 2, 3)), (1, 2, 3))
        self.assertEqual(levels.words(b"\1\0\0\0\2"), (1,))        # partial word dropped
        self.assertEqual(levels.trim(code(5, 0, 0)), code(5))
        self.assertEqual(levels.trim(code(0, 0)), b"")
        self.assertEqual(levels.trim(b"\0\0\0\0\0\0"), b"\0\0")    # only whole words

    def test_trailing_zero_words_ignored(self):
        body = code(addiu(4, 0, 5), JR_RA, NOP)
        padded = body + code(0, 0, 0)
        self.assertEqual(levels.identity(padded), levels.identity(body))
        self.assertEqual(levels.fingerprint(padded), levels.fingerprint(body))

    def test_fingerprint_shape(self):
        fp = levels.fingerprint(code(JR_RA, NOP))
        self.assertEqual(len(fp), 16)
        int(fp, 16)

    def test_jump_target_masked_without_address(self):
        a = code(j(0x100000), NOP)
        b = code(j(0x200000), NOP)
        self.assertEqual(levels.identity(a), levels.identity(b))

    def test_jump_target_below_level_base_kept_with_address(self):
        a = code(j(0x100000), NOP)
        b = code(j(0x200000), NOP)
        self.assertNotEqual(levels.identity(a, 0x2A0000), levels.identity(b, 0x2A0000))
        self.assertNotEqual(levels.fingerprint(a, 0x2A0000), levels.fingerprint(b, 0x2A0000))

    def test_jump_target_in_levels_masked_with_address(self):
        a = code(j(0x2B0000), NOP)
        b = code(j(0x2C0000), NOP)
        self.assertEqual(levels.identity(a, 0x2A0000), levels.identity(b, 0x2A0000))
        self.assertEqual(levels.identity(a, 0x2A0000), code(2 << 26))

    def test_lui_of_non_resident_address_masked(self):
        a = code(lui(4, 0x2A), lw(5, 4, 0x1234), JR_RA)
        b = code(lui(4, 0x2B), lw(5, 4, 0x5678), JR_RA)
        self.assertEqual(levels.identity(a), levels.identity(b))

    def test_lui_of_resident_address_kept(self):
        # 0x15 is below LEVEL_BASE >> 16: the same in every program, so it is compared,
        # and so is the offset used on it.
        a = code(lui(4, 0x15), lw(5, 4, 0x1234), JR_RA)
        b = code(lui(4, 0x16), lw(5, 4, 0x1234), JR_RA)
        c = code(lui(4, 0x15), lw(5, 4, 0x1238), JR_RA)
        self.assertNotEqual(levels.identity(a), levels.identity(b))
        self.assertNotEqual(levels.identity(a), levels.identity(c))
        self.assertEqual(levels.identity(a), a)

    def test_constants_compared(self):
        a = code(addiu(4, 0, 5), JR_RA, NOP)
        b = code(addiu(4, 0, 6), JR_RA, NOP)
        self.assertNotEqual(levels.identity(a), levels.identity(b))

    def test_stack_offsets_compared(self):
        a = code(lw(4, 29, 0x10), JR_RA)
        b = code(lw(4, 29, 0x14), JR_RA)
        self.assertNotEqual(levels.identity(a), levels.identity(b))

    def test_gp_relative_masked(self):
        a = code(lw(4, 28, 0x1234), JR_RA)
        b = code(lw(4, 28, 0x4321), JR_RA)
        self.assertEqual(levels.identity(a), levels.identity(b))
        self.assertEqual(levels.identity(a), code(lw(4, 28, 0), JR_RA))

    def test_small_field_offsets_compared(self):
        a = code(lw(4, 5, 0x10), JR_RA)
        b = code(lw(4, 5, 0x20), JR_RA)
        self.assertNotEqual(levels.identity(a), levels.identity(b))


class Catalogue(unittest.TestCase):
    def test_legacy_preprologue_load_is_recovered_before_identity_replay(self):
        name = "func_L05_0042AFE0"
        # Authored synthetic instructions: filler, a GP FP load before the
        # prologue, a constant result and a normal return. No retail arrays.
        load = (0x31 << 26) | (28 << 21) | (1 << 16) | 0x1234
        method = code(load, addiu(29, 29, -64), addiu(2, 0, 9))
        method += bytes(724 - len(method) - 8) + code(JR_RA, addiu(29, 29, 64))
        raw = code(addiu(29, 29, 16), NOP) + method
        places = [(5, 0x210000), (10, 0x230008), (15, 0x250010), (25, 0x270018)]
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
            boot.write_text("# name\taddress\tsize\nfunc_00001000\t00001000\t8\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" +
                f"{name}\tshared\t720\told\t4\t" +
                ",".join(f"{n:02d}:{a+12:08X}" for n, a in places) + "\n")
            for n, a in places:
                directory = dump / f"{n:02d}_test"
                directory.mkdir(parents=True)
                (directory / "manifest.json").write_text(json.dumps({"sections": [
                    {"name": "text", "address": a}]}))
                (directory / "text.bin").write_bytes(raw)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue,
                                LEVELS=root, BOOT_PAIRS=root / "absent.tsv", DUMP=dump,
                                NAMES={n:"test" for n, _ in places}, BOOT_RESIDUES={},
                                FUNCTION_RESIDUES={}, FUNCTION_ENTRY_OFFSETS={name:(732,8)}), \
                 patch.object(levels, "boot_image", return_value=(code(JR_RA,NOP), [(0x1000,0,8)])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                row, = levels.read_catalogue()
                self.assertEqual((row[0],row[1],row[2],row[4]),
                                 (name,"shared",724,[(n,a+8) for n,a in places]))
                self.assertEqual(row[3], levels.fingerprint(method, places[0][1]+8))
                first = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first)
                # A different first FP destination in another copy must fail
                # before either catalogue is written, rather than hide the load.
                changed = dump / "10_test" / "text.bin"
                changed.write_bytes(raw[:8] + code(load ^ (1 << 16)) + raw[12:])
                with self.assertRaisesRegex(ValueError, "differs after entry correction"):
                    levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first)

    def test_historical_bootstrap_does_not_require_an_existing_catalogue(self):
        raw = code(JR_RA,NOP)
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue = root/"boot.tsv", root/"levels.tsv"
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                NAMES={}, BOOT_RESIDUES={}, FUNCTION_ENTRY_OFFSETS={}, FUNCTION_RESIDUES={},
                                BOOT_PAIRS=root/"absent.tsv"), \
                 patch.object(levels,"boot_image",return_value=(raw,[(0x1000,0,len(raw))])), \
                 patch.object(levels,"old_extents",return_value=[(0x1000,8)]), \
                 patch.object(sys,"argv",["levels.py","catalogue","--from-old"]):
                levels.catalogue()
                self.assertEqual(levels.read_boot_functions(),[("func_00001000",0x1000,8)])
                self.assertEqual(levels.read_catalogue(),[])

    def test_named_residue_does_not_remove_an_identical_unrelated_instruction(self):
        raw = code((0x2B << 26) | (4 << 21) | (2 << 16), NOP) * 2
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
            boot.write_text("# name\taddress\tsize\nfunc_00001000\t00001000\t4\n"
                            "func_00001008\t00001008\t4\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n"
                                 "func_00001000\tboot\t4\tunused\t1\t00:00002000\n"
                                 "func_L00_00002008\tlevel\t4\tunused\t1\t00:00002008\n")
            directory = dump / "00_test"
            directory.mkdir(parents=True)
            (directory / "manifest.json").write_text(
                '{"sections":[{"name":"text","address":8192}]}')
            (directory / "text.bin").write_bytes(raw)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                BOOT_PAIRS=root / "absent.tsv", DUMP=dump, NAMES={0:"test"},
                                BOOT_RESIDUES={}, FUNCTION_ENTRY_OFFSETS={},
                                FUNCTION_RESIDUES={"func_00001000": 4}), \
                 patch.object(levels, "boot_image", return_value=(raw, [(0x1000,0,len(raw))])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                self.assertEqual(levels.read_boot_functions(), [("func_00001008",0x1008,4)])
                self.assertEqual([(r[0],r[4]) for r in levels.read_catalogue()],
                                 [("func_L00_00002008",[(0,0x2008)])])
                first_output = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first_output)

    def test_level_only_entries_keep_distinct_names_after_identity_collisions(self):
        names = ("func_L00_004263A8", "func_L02_003F0788")
        # Identical short methods, with distinct or identical original prefixes.
        # A third uncorrected method and a boot method have the same short code.
        for second_restore in (80, 96):
            with self.subTest(second_restore=second_restore), tempfile.TemporaryDirectory() as d:
                root = Path(d)
                boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
                method = code(JR_RA, NOP)
                data = code(addiu(29, 29, 80), NOP) + method
                data += code(addiu(29, 29, second_restore), NOP) + method + method
                boot.write_text("# name\taddress\tsize\nfunc_00001000\t00001000\t8\n")
                catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" +
                    "".join(f"{name}\tshared\t16\tunused\t2\t00:{0x2000+i*16:08X},01:{0x3000+i*16:08X}\n"
                            for i, name in enumerate(names)) +
                    "func_L00_00002020\tshared\t8\tunused\t2\t00:00002020,01:00003020\n")
                for number in (0, 1):
                    directory = dump / f"{number:02d}_test"
                    directory.mkdir(parents=True)
                    (directory / "manifest.json").write_text(
                        '{"sections":[{"name":"text","address":' + str(0x2000 + number * 0x1000) + '}]}')
                    (directory / "text.bin").write_bytes(data)
                with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                    BOOT_PAIRS=root / "absent.tsv", DUMP=dump,
                                    NAMES={0:"test", 1:"test"}, BOOT_RESIDUES={}, FUNCTION_RESIDUES={},
                                    FUNCTION_ENTRY_OFFSETS={n: (16,8) for n in names}), \
                     patch.object(levels, "boot_image", return_value=(method, [(0x1000,0,len(method))])), \
                     patch.object(sys, "argv", ["levels.py", "catalogue"]):
                    levels.catalogue()
                    rows = {r[0]: (r[1], r[2], r[4]) for r in levels.read_catalogue()}
                    self.assertEqual(rows, {
                        names[0]: ("shared", 8, [(0,0x2008),(1,0x3008)]),
                        names[1]: ("shared", 8, [(0,0x2018),(1,0x3018)]),
                        "func_L00_00002020": ("shared", 8, [(0,0x2020),(1,0x3020)])})
                    first_output = boot.read_bytes(), catalogue.read_bytes()
                    levels.catalogue()
                    self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first_output)
                    # A later copy whose code changed must fail replay, not keep
                    # a measured identity based only on its input name and size.
                    (dump / "01_test" / "text.bin").write_bytes(
                        data[:12] + code(addiu(2, 0, 1)) + data[16:])
                    with self.assertRaisesRegex(ValueError, "differs after entry correction"):
                        levels.catalogue()
                    self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first_output)

    def test_named_entry_corrections_reach_boot_and_level_copies_and_are_stable(self):
        # Synthetic bodies, not retail bytes. A separately named method with
        # identical full code must not inherit another method's correction.
        first = code(addiu(29, 29, -16), *([addiu(2, 0, 17)] * 10), JR_RA,
                     addiu(29, 29, 16), NOP)
        second = code(addiu(29, 29, -32), *([addiu(3, 0, 33)] * 5), JR_RA,
                      addiu(29, 29, 32), NOP)
        unrelated = code(addiu(29, 29, 80), NOP) + first
        data = code(addiu(29, 29, 80), NOP) + first
        data += code(*([addiu(29, 29, 16), NOP] * 4)) + second + unrelated + first
        rows = [("func_002C38A0", 0x1000, 64), ("func_00335918", 0x1040, 68),
                ("func_00001084", 0x1084, 64), ("func_000010C4", 0x10C4, 56)]
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
            boot.write_text("# name\taddress\tsize\n" + "".join(
                f"{name}\t{address:08X}\t{size}\n" for name, address, size in rows))
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" + "".join(
                f"{name}\tboot\t{size}\tunused\t2\t00:{address+0x1000:08X},01:{address+0x2000:08X}\n"
                for name, address, size in rows[:3]))
            for number in (0, 1):
                directory = dump / f"{number:02d}_test"
                directory.mkdir(parents=True)
                (directory / "manifest.json").write_text(
                    '{"sections":[{"name":"text","address":' + str(0x2000 + number * 0x1000) + '}]}')
                (directory / "text.bin").write_bytes(data)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                BOOT_PAIRS=root / "absent.tsv", DUMP=dump,
                                NAMES={0:"test", 1:"test"}, BOOT_RESIDUES={}, FUNCTION_RESIDUES={}), \
                 patch.object(levels, "boot_image", return_value=(data, [(0x1000,0,len(data))])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                self.assertEqual(levels.read_boot_functions(), [
                    ("func_002C38A0", 0x1008, 56), ("func_00335918", 0x1060, 36),
                    ("func_00001084", 0x1084, 64), ("func_000010C4", 0x10C4, 56)])
                corrected = {r[0]: (r[2], r[4]) for r in levels.read_catalogue()}
                self.assertEqual(corrected["func_002C38A0"], (56, [(0,0x2008),(1,0x3008)]))
                self.assertEqual(corrected["func_00335918"], (36, [(0,0x2060),(1,0x3060)]))
                self.assertEqual(corrected["func_00001084"], (64, [(0,0x2084),(1,0x3084)]))
                first_output = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first_output)

    def test_measured_residue_removed_in_boot_and_level_and_replay_is_stable(self):
        # Synthetic residue: a store without a complete function around it.
        # A different store and a tail jump of the same size must remain.
        body = code(0xAC400020, NOP)
        other = code(0xAC400024, NOP)
        tail = code(j(0x3000), NOP)
        data = body + other + tail
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
            boot.write_text("# name\taddress\tsize\nfunc_00001000\t00001000\t8\n"
                            "func_00001008\t00001008\t8\nfunc_00001010\t00001010\t8\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" + "".join(
                f"func_L00_{a:08X}\tlevel\t8\tunused\t1\t00:{a:08X}\n" for a in (0x2000,0x2008,0x2010)))
            level = dump / "00_test"
            level.mkdir(parents=True)
            (level / "manifest.json").write_text('{"sections":[{"name":"text","address":8192}]}')
            (level / "text.bin").write_bytes(data)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                BOOT_PAIRS=root / "absent.tsv", DUMP=dump, NAMES={0:"test"},
                                BOOT_RESIDUES={0x1000:8}, FUNCTION_RESIDUES={}), \
                 patch.object(levels, "boot_image", return_value=(data, [(0x1000,0,len(data))])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                self.assertEqual([a for _,a,_ in levels.read_boot_functions()], [0x1008,0x1010])
                places = [a for row in levels.read_catalogue() for _,a in row[4]]
                self.assertEqual(places, [0x2008,0x2010])
                first = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), first)

    def test_read_catalogue_and_boot(self):
        with tempfile.TemporaryDirectory() as d:
            cat = Path(d) / "functions.tsv"
            cat.write_text(
                "# name\tkind\tsize\tfingerprint\tlevels\tplaces\n"
                "func_L00_002A3B80\tshared\t8\t17b4ae028fe3a32c\t2\t00:002A3B80,01:002A5F80\n"
                "func_L01_002A6000\tlevel\t16\t0123456789abcdef\t1\t01:002A6000\n")
            boot = Path(d) / "boot.tsv"
            boot.write_text("# name\taddress\tsize\nfunc_00115200\t00115200\t12\nfunc_00115210\t00115210\t4\n")
            old = levels.CATALOGUE, levels.BOOT_FUNCTIONS
            levels.CATALOGUE, levels.BOOT_FUNCTIONS = cat, boot
            try:
                rows = levels.read_catalogue()
                self.assertEqual(rows, [
                    ("func_L00_002A3B80", "shared", 8, "17b4ae028fe3a32c", [(0, 0x2A3B80), (1, 0x2A5F80)]),
                    ("func_L01_002A6000", "level", 16, "0123456789abcdef", [(1, 0x2A6000)]),
                ])
                self.assertEqual(levels.read_boot_functions(),
                                 [("func_00115200", 0x115200, 12), ("func_00115210", 0x115210, 4)])
            finally:
                levels.CATALOGUE, levels.BOOT_FUNCTIONS = old

    def test_level_names(self):
        self.assertEqual(len(levels.NAMES), 27)
        self.assertEqual(levels.level_dir(1), "01_oozla")


class Elf(unittest.TestCase):
    SECTIONS = [
        {"name": ".text", "address": 0x100000, "type": elf.SHT_PROGBITS, "data": code(addiu(4, 0, 1), JR_RA, NOP, NOP)},
        {"name": ".data", "address": 0x200000, "type": elf.SHT_PROGBITS, "data": bytes(range(40))},
        {"name": ".bss", "address": 0x300000, "type": elf.SHT_NOBITS, "data": b"\0" * 64},
    ]

    def write(self, d, name, sections=None, entry=0x100000):
        p = Path(d) / name
        elf.write_exec(p, entry, sections or self.SECTIONS)
        return p

    def test_round_trip(self):
        with tempfile.TemporaryDirectory() as d:
            e = elf.read(self.write(d, "a.elf"))
            self.assertEqual(e["entry"], 0x100000)
            self.assertEqual(e["type"], 2)
            loads = [s for s in e["segments"] if s["type"] == elf.PT_LOAD]
            self.assertEqual([(s["address"], s["filesz"]) for s in loads],
                             [(0x100000, 16), (0x200000, 40)])
            by_name = {s["name"]: s for s in e["sections"]}
            for want in self.SECTIONS:
                got = by_name[want["name"]]
                self.assertEqual((got["address"], got["type"], got["size"]),
                                 (want["address"], want["type"], len(want["data"])))
            text = by_name[".text"]
            self.assertEqual(e["data"][text["offset"]:text["offset"] + text["size"]], self.SECTIONS[0]["data"])

    def test_compare_loads(self):
        with tempfile.TemporaryDirectory() as d:
            a = self.write(d, "a.elf")
            self.assertEqual(elf.compare_loads(a, self.write(d, "b.elf"))[0], True)
            self.assertIn("loaded bytes equal", elf.compare_loads(a, a)[1])
            changed = [dict(s) for s in self.SECTIONS]
            changed[1]["data"] = bytes([0xFF]) + changed[1]["data"][1:]
            ok, why = elf.compare_loads(a, self.write(d, "c.elf", changed))
            self.assertFalse(ok)
            self.assertIn("0x00200000", why)
            ok, why = elf.compare_loads(a, self.write(d, "d.elf", entry=0x100004))
            self.assertFalse(ok)
            self.assertIn("entry", why)
            fewer = self.SECTIONS[:1]
            ok, why = elf.compare_loads(a, self.write(d, "e.elf", fewer))
            self.assertFalse(ok)
            self.assertIn("loadable segments", why)

    def test_not_elf(self):
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "x"
            p.write_bytes(b"nope")
            with self.assertRaises(ValueError):
                elf.read(p)


def dir_record(extent, size, name):
    n = name.encode()
    length = 33 + len(n)
    length += length & 1
    rec = bytearray(length)
    rec[0] = length
    struct.pack_into("<I", rec, 2, extent)
    struct.pack_into(">I", rec, 6, extent)
    struct.pack_into("<I", rec, 10, size)
    struct.pack_into(">I", rec, 14, size)
    rec[32] = len(n)
    rec[33:33 + len(n)] = n
    return bytes(rec)


class IsoTest(unittest.TestCase):
    def test_find(self):
        img = bytearray(2048 * 24)
        root, gdir, content = 20, 21, 22
        pvd = bytearray(2048)
        pvd[156:156 + 34] = dir_record(root, 2048, "\0")[:34].ljust(34, b"\0")
        struct.pack_into("<I", pvd, 158, root)
        struct.pack_into("<I", pvd, 166, 2048)
        img[16 * 2048:17 * 2048] = pvd
        img[root * 2048:root * 2048 + 40] = dir_record(gdir, 2048, "G")
        img[gdir * 2048:gdir * 2048 + 60] = dir_record(content, 4096, "LEVEL0.WAD;1")
        img[content * 2048:content * 2048 + 4] = b"WAD!"
        with tempfile.TemporaryDirectory() as d:
            p = Path(d) / "t.iso"
            p.write_bytes(bytes(img))
            iso = levels.Iso(p)
            self.assertEqual(iso.find("G/LEVEL0.WAD"), (content, 4096))
            self.assertEqual(iso.find("G"), (gdir, 2048))
            self.assertEqual(iso.read(content, 4), b"WAD!")
            with self.assertRaises(KeyError):
                iso.find("G/MISSING")
            iso.f.close()


class ProgressChecks(unittest.TestCase):
    def test_primary_check_keeps_pending_original_assembly_separate_from_c(self):
        import contextlib
        import io
        import progress
        with tempfile.TemporaryDirectory() as d:
            path=Path(d)/"report.json"
            path.write_text(json.dumps({"units":[{"functions":[]}]}))
            before=path.read_bytes();output=io.StringIO()
            with patch.object(progress,"REPORT",path), \
                 patch.object(progress,"source_functions",return_value={"x.c":[("c_body",True),("assembly_body",False)]}), \
                 patch.object(progress,"handwritten",return_value={"assembly_body"}), \
                 patch.object(sys,"argv",["progress.py","--check"]), contextlib.redirect_stdout(output):
                progress.check()
            self.assertIn("1 C and 1 original-assembly functions",output.getvalue())
            self.assertEqual(path.read_bytes(),before)

    def test_release_check_does_not_present_new_asm_func_as_new_c(self):
        import contextlib
        import io
        import progress
        with tempfile.TemporaryDirectory() as d:
            root=Path(d);path=root/"report.json"
            path.write_text(json.dumps({"units":[{"functions":[{"name":"assembly_body","fuzzy_match_percent":0.0}]}]}))
            before=path.read_bytes();output=io.StringIO()
            with patch.object(progress,"ROOT",root), \
                 patch.object(progress,"release_functions",return_value={"assembly_body":(0x1000,8,"boot",None)}), \
                 patch.object(progress,"source_functions",return_value={"x.c":[("assembly_body",False)]}), \
                 patch.object(progress,"handwritten",return_value={"assembly_body"}), \
                 patch.object(sys,"argv",["progress.py","--check"]), contextlib.redirect_stdout(output):
                progress.release_check("pal",path)
            self.assertIn("0 C and 1 original-assembly functions",output.getvalue())
            self.assertEqual(path.read_bytes(),before)

    def test_linked_code_sums_the_complete_units(self):
        import progress
        row=lambda name,size,address,matched:{"name":name,"size":size,"address":address,"matched":matched}
        groups={"game/done":{"rows":[row("a",8,0x100,True),row("b",4,0x108,True)],
                             "source_path":"src/game/done.c","categories":["executable","game"]},
                "game/open":{"rows":[row("c",16,0x200,True),row("d",4,0x210,False)],
                             "source_path":"src/game/open.c","categories":["executable","game"]},
                "Shared level code":{"rows":[row("e",8,0x300,False)],
                                     "source_path":"src/levels/shared","categories":["level_code","common"]}}
        report=progress.build_report(groups,lambda n:f"Level {n:02d}",{})
        total=report["measures"]
        self.assertEqual((total["complete_code"],total["complete_units"],total["total_code"]),("12",1,"40"))
        self.assertAlmostEqual(total["complete_code_percent"],30.0)
        cats={c["id"]:c["measures"] for c in report["categories"]}
        self.assertEqual(cats["game"]["complete_code"],"12")
        self.assertAlmostEqual(cats["game"]["complete_code_percent"],37.5)
        self.assertEqual(cats["common"]["complete_code"],"0")
        units={u["name"]:u["measures"]["complete_code"] for u in report["units"]}
        self.assertEqual(units,{"game/done":"12","game/open":"0","Shared level code":"0"})

    def release(self, functions, flags=(), where=None):
        import progress
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            path = root / "report.json"
            path.write_text(json.dumps({"units":[{"functions":functions}]}))
            before = path.read_bytes()
            with patch.object(progress,"ROOT",root), \
                 patch.object(progress,"release_functions",return_value=where or {"kept":(0x1000,8,"boot",None)}), \
                 patch.object(progress,"source_functions",return_value={}), \
                 patch.object(progress,"handwritten",return_value=set()), \
                 patch.object(levels,"FUNCTION_RESIDUES",{"retired":4}), \
                 patch.object(sys,"argv",["progress.py","--check",*flags]):
                progress.release_check("pal",path)
            self.assertEqual(path.read_bytes(),before)

    def test_unmatched_named_retirement_can_wait_for_a_report_refresh(self):
        self.release([{"name":"kept","fuzzy_match_percent":0.0},
                      {"name":"retired","fuzzy_match_percent":0.0}])

    def test_strict_report_check_still_requires_the_retired_row_removed(self):
        with self.assertRaises(SystemExit):
            self.release([{"name":"kept","fuzzy_match_percent":0.0},
                          {"name":"retired","fuzzy_match_percent":0.0}],flags=("--strict",))

    def test_report_cannot_keep_matching_credit_for_a_retired_function(self):
        for percentage in (25.0,100.0):
            with self.subTest(percentage=percentage), self.assertRaises(SystemExit):
                self.release([{"name":"kept","fuzzy_match_percent":0.0},
                              {"name":"retired","fuzzy_match_percent":percentage}])

    def test_unknown_deletion_is_not_a_measured_retirement(self):
        with self.assertRaises(SystemExit):
            self.release([{"name":"kept","fuzzy_match_percent":0.0},
                          {"name":"unknown","fuzzy_match_percent":0.0}])

    def test_duplicate_retired_rows_are_not_tolerated(self):
        with self.assertRaises(SystemExit):
            self.release([{"name":"kept","fuzzy_match_percent":0.0},
                          {"name":"retired","fuzzy_match_percent":0.0},
                          {"name":"retired","fuzzy_match_percent":0.0}])

    def test_a_retirement_cannot_hide_an_added_catalogue_function(self):
        with self.assertRaises(SystemExit):
            self.release([{"name":"kept","fuzzy_match_percent":0.0},
                          {"name":"retired","fuzzy_match_percent":0.0}],
                         where={"kept":(0x1000,8,"boot",None),"new":(0x2000,8,"boot",None)})


class Todo(unittest.TestCase):
    def test_every_marker_is_listed_once_with_its_size(self):
        import progress
        import todo
        rows = todo.todo()
        names = [r[0] for r in rows]
        self.assertEqual(len(names), len(set(names)))
        markers = {n for fns in progress.source_functions().values() for n, has_c in fns if not has_c}
        markers -= progress.handwritten()
        self.assertEqual(set(names), markers)
        sizes = {n: s for n, _, s in levels.read_boot_functions()}
        for name, size, places, kind, path in rows:
            self.assertGreater(size, 0)
            self.assertGreaterEqual(places, 1)
            if kind == "boot":
                self.assertEqual(size, sizes[name])

    def test_tiers_cover_every_size(self):
        import todo
        self.assertEqual(todo.TIERS[0][1], 0)
        for (_, _, hi), (_, lo, _) in zip(todo.TIERS, todo.TIERS[1:]):
            self.assertEqual(lo, hi + 1)


class MobyDispatchMetadata(unittest.TestCase):
    """Keep attributed class labels separate from the legacy dispatch-name fields."""

    def test_schema_and_sourced_moby_labels(self):
        import csv
        import re

        with (ROOT / "docs/moby-dispatch.tsv").open(encoding="utf-8", newline="") as stream:
            reader = csv.DictReader(stream, delimiter="\t")
            self.assertEqual(reader.fieldnames, [
                "table", "level", "id", "role", "address", "aux", "proposed_name", "source",
                "class_label", "class_label_source", "class_label_basis",
            ])
            labels = {}
            for row in reader:
                with self.subTest(table=row["table"], level=row["level"], id=row["id"]):
                    self.assertNotIn(None, row, "unexpected extra columns")
                    self.assertNotIn(None, row.values(), "missing columns")
                    label, source = row["class_label"], row["class_label_source"]
                    self.assertEqual(bool(label), bool(source))
                    basis = row["class_label_basis"]
                    self.assertEqual(bool(label), bool(basis))
                    if label:
                        self.assertEqual(row["table"], "moby")
                        urls = source.split("; ")
                        self.assertEqual(len(urls), len(set(urls)), "duplicate provenance")
                        paths = {
                            "chaoticgd/wrench": {
                                "data/underlay/gc_moby_classes.asset", "data/underlay/level_design.asset",
                                "data/overlay/src/game_gc/update/moby4018_therm_water.h",
                            },
                            "RatchetModding/Replanetizer": {"LibReplanetizer/ModelLists/MobyModelsRC2.txt"},
                            "evilwb/APRac2": {"data/Items.py"},
                        }
                        repositories = set()
                        for url in urls:
                            match = re.fullmatch(
                                r"https://github\.com/([^/]+/[^/]+)/blob/[0-9a-f]{40}/"
                                r"([^#]+)#L([1-9][0-9]*)(?:-L([1-9][0-9]*))?", url,
                            )
                            self.assertIsNotNone(match, url)
                            repository, path, start, end = match.groups()
                            self.assertIn(path, paths.get(repository, set()))
                            self.assertGreaterEqual(int(end or start), int(start))
                            repositories.add(repository)
                        self.assertIn(basis, {"ps2-source", "ps3-source-only"})
                        if basis == "ps3-source-only":
                            self.assertEqual(repositories, {"RatchetModding/Replanetizer"})
                        else:
                            self.assertTrue(repositories & {"chaoticgd/wrench", "evilwb/APRac2"},
                                            "label marked PS2 without a PS2 source")
                        previous = labels.setdefault(row["id"], (label, source, basis))
                        self.assertEqual(previous, (label, source, basis), "conflicting class label")


if __name__ == "__main__":
    unittest.main()
