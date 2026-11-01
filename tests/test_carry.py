"""Tests for tools/carry.py and levels.cross_identity(): no game data, no toolchains."""
import struct
import sys
import unittest
import tempfile
from unittest.mock import patch
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import carry  # noqa: E402
import levels  # noqa: E402

JR_RA, NOP = 0x03E00008, 0


def code(*w: int) -> bytes:
    return struct.pack(f"<{len(w)}I", *w)


def lui(rt: int, imm: int) -> int:
    return 0x0F << 26 | rt << 16 | imm


def addiu(rt: int, rs: int, imm: int) -> int:
    return 0x09 << 26 | rs << 21 | rt << 16 | (imm & 0xFFFF)


def lw(rt: int, rs: int, imm: int) -> int:
    return 0x23 << 26 | rs << 21 | rt << 16 | (imm & 0xFFFF)


class Identity(unittest.TestCase):
    def test_a_packed_constant_is_compared_and_an_address_is_not(self):
        def packed(high):
            return code(lui(2, high), 0x0D << 26 | 2 << 21 | 2 << 16 | 0x1010, JR_RA, NOP)
        self.assertNotEqual(levels.identity(packed(0x20)), levels.identity(packed(0x80)))
        self.assertEqual(levels.identity(code(lui(2, 0x20), addiu(2, 2, 0x10), JR_RA, NOP)),
                         levels.identity(code(lui(2, 0x80), addiu(2, 2, 0x10), JR_RA, NOP)))

    def test_an_ori_of_another_value_is_no_constant(self):
        def overwritten(high):
            return code(lui(2, high), lw(2, 18, 8), 0x0D << 26 | 2 << 21 | 2 << 16 | 0x88, JR_RA, NOP)
        self.assertEqual(levels.identity(overwritten(0x1F)), levels.identity(overwritten(0x20)))


class CrossIdentity(unittest.TestCase):
    def test_addresses_are_masked_resident_too(self):
        a = code(lui(2, 0x1A), lw(2, 2, 0x7BB4), JR_RA, NOP)
        b = code(lui(2, 0x1A), lw(2, 2, 0x7C3C), JR_RA, NOP)
        self.assertEqual(levels.cross_identity(a), levels.cross_identity(b))
        c = code(lui(2, 0x13), lw(2, 2, 0x7BB4), JR_RA, NOP)     # resident within one release
        d = code(lui(2, 0x13), lw(2, 2, 0x7C3C), JR_RA, NOP)
        self.assertNotEqual(levels.identity(c, 0x200000), levels.identity(d, 0x200000))
        self.assertEqual(levels.cross_identity(c), levels.cross_identity(d))

    def test_fields_of_a_whole_address_are_compared(self):
        # lui + addiu make a pointer; the offsets on it are fields, not address halves
        a = code(lui(2, 0x1C), addiu(3, 2, -0x5380), lw(4, 3, 0x2AC), JR_RA, NOP)
        b = code(lui(2, 0x1C), addiu(3, 2, -0x5300), lw(4, 3, 0x2DC), JR_RA, NOP)
        self.assertNotEqual(levels.cross_identity(a), levels.cross_identity(b))
        c = code(lui(2, 0x1C), addiu(3, 2, -0x5300), lw(4, 3, 0x2AC), JR_RA, NOP)
        self.assertEqual(levels.cross_identity(a), levels.cross_identity(c))

    def test_jumps_and_gp_offsets_are_masked(self):
        a = code(3 << 26 | 0x100, 0x8F820010, JR_RA, NOP)        # jal; lw v0,0x10(gp)
        b = code(3 << 26 | 0x200, 0x8F820018, JR_RA, NOP)
        self.assertEqual(levels.cross_identity(a), levels.cross_identity(b))

    def test_constants_are_compared(self):
        self.assertNotEqual(levels.cross_identity(code(addiu(4, 0, 60), JR_RA, NOP)),
                            levels.cross_identity(code(addiu(4, 0, 50), JR_RA, NOP)))


class Carry(unittest.TestCase):
    def test_legacy_preprologue_entry_refresh_keeps_load_end_and_identity(self):
        name = "func_L05_0042AFE0"
        load = (0x31 << 26) | (28 << 21) | (1 << 16) | 0x3456
        method = code(load, addiu(29,29,-64), addiu(2,0,11))
        method += bytes(724-len(method)-8) + code(JR_RA,addiu(29,29,64))
        raw = code(addiu(29,29,16),NOP) + method
        for release_base in (0x210000,0x310008,0x410010):
            with self.subTest(release_base=release_base), tempfile.TemporaryDirectory() as d:
                boot, catalogue = Path(d)/"boot.tsv", Path(d)/"levels.tsv"
                places = [(n,release_base+i*0x2000) for i,n in enumerate((5,10,15,25))]
                images = {n:(a,raw) for n,a in places}
                boot.write_text("# name\taddress\tsize\n")
                catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" +
                    f"{name}\tshared\t720\told\t4\t" +
                    ",".join(f"{n:02d}:{a+12:08X}" for n,a in places) + "\n")
                with patch.multiple(levels,BOOT_FUNCTIONS=boot,CATALOGUE=catalogue,
                                    NAMES={n:"test" for n,_ in places}, FUNCTION_RESIDUES={}), \
                     patch.object(levels,"level_text",side_effect=lambda p: images[int(p.name[:2])]):
                    carry.refresh_entries()
                    row, = levels.read_catalogue()
                    self.assertEqual((row[0],row[1],row[2],row[4]),
                                     (name,"shared",724,[(n,a+8) for n,a in places]))
                    self.assertEqual(row[3],levels.fingerprint(method,places[0][1]+8))
                    self.assertTrue(all(a+8+724 == a+732 for _,a in places))
                    first = boot.read_bytes(),catalogue.read_bytes()
                    carry.refresh_entries()
                    self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),first)
                    catalogue.write_text(catalogue.read_text().replace("\t724\t","\t728\t"))
                    before = boot.read_bytes(),catalogue.read_bytes()
                    with self.assertRaises(ValueError):carry.refresh_entries()
                    self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),before)

    def test_entry_refresh_preserves_identities_removes_only_named_remnants_and_replays(self):
        with tempfile.TemporaryDirectory() as d:
            boot, catalogue = Path(d)/"boot.tsv", Path(d)/"levels.tsv"
            name = "func_PAL_00002000"
            boot.write_text(f"# name\taddress\tsize\n{name}\t00002000\t20\n"
                            "remnant\t00002100\t4\nuntouched\t00002200\t4\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" +
                                 f"{name}\tboot\t20\told\t2\t00:00003000,01:00004000\n"
                                 "remnant\tlevel\t4\told\t1\t00:00003100\n"
                                 "untouched\tshared\t4\tsame\t2\t00:00003200,01:00004200\n")
            raw = code(addiu(29,29,80),NOP,addiu(2,0,7),JR_RA,NOP)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue,
                                FUNCTION_ENTRY_OFFSETS={name:(20,8)}, FUNCTION_RESIDUES={"remnant":4}), \
                 patch.object(levels,"level_text",side_effect=[(0x3000,raw),(0x4000,raw)]):
                carry.refresh_entries()
                self.assertEqual(levels.read_boot_functions(),[(name,0x2008,12),("untouched",0x2200,4)])
                rows = levels.read_catalogue()
                self.assertEqual((rows[0][0],rows[0][1],rows[0][2],rows[0][4]),
                                 (name,"boot",12,[(0,0x3008),(1,0x4008)]))
                self.assertEqual(rows[1],("untouched","shared",4,"same",[(0,0x3200),(1,0x4200)]))
                first = boot.read_bytes(), catalogue.read_bytes()
                carry.refresh_entries()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()), first)
                # A changed level extent must fail before either file is written.
                catalogue.write_text(catalogue.read_text().replace("\t12\t","\t16\t"))
                before = boot.read_bytes(), catalogue.read_bytes()
                with self.assertRaises(ValueError):carry.refresh_entries()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()), before)

    def test_entry_refresh_rejects_disagreement_between_shortened_copies(self):
        name = "func_US2_L00_00002000"
        rows = [(name,"shared",20,"old",[(0,0x2000),(1,0x3000)])]
        first = code(addiu(29,29,80),NOP,addiu(2,0,7),JR_RA,NOP)
        second = code(addiu(29,29,80),NOP,addiu(2,0,9),JR_RA,NOP)
        with patch.dict(levels.FUNCTION_ENTRY_OFFSETS,{name:(20,8)}), \
             patch.object(levels,"level_text",side_effect=[(0x2000,first),(0x3000,second)]), \
             self.assertRaisesRegex(ValueError,"corrected level copies differ"):
            carry.correct_level_entries(rows)

    def test_branch_target(self):
        self.assertEqual(carry.branch_target(0x10400003, 0x1000), 0x1010)   # beqz v0,+3
        self.assertEqual(carry.branch_target(0x1000FFFF, 0x1000), 0x1000)   # b .
        self.assertIsNone(carry.branch_target(0x0C000000, 0x1000))          # jal

    def test_cut_after_a_return(self):
        data = code(addiu(29, 29, -16), JR_RA, NOP, 0, addiu(29, 29, -32), JR_RA, NOP, 0)
        self.assertEqual(carry.cut(data, 0x1000, 0x1000, 0x1020, set()), [(0x1000, 12), (0x1010, 12)])

    def test_align_finds_moved_and_changed_functions(self):
        f = code(addiu(29, 29, -16), lw(2, 4, 8), JR_RA, NOP)
        g = code(addiu(4, 0, 60), addiu(5, 0, 1), JR_RA, NOP)
        h = code(addiu(29, 29, -32), lw(3, 4, 12), lw(2, 4, 16), JR_RA, NOP, 0)
        us = (0x1000, f + g + h)
        g_pal = code(addiu(4, 0, 50), addiu(5, 0, 1), JR_RA, NOP)
        v = (0x2000, code(0, 0) + f + g_pal + h)            # moved by 8 bytes, g changed
        ext = [(0x1000, 16, "f"), (0x1010, 16, "g"), (0x1020, 24, "h")]
        out = {e[0]: e[:4] for e in carry.align(us, ext, v)}
        self.assertEqual(out[0x2008], (0x2008, 16, "f", "same"))
        self.assertEqual(out[0x2018], (0x2018, 16, None, "changed"))
        self.assertEqual(out[0x2028], (0x2028, 24, "h", "same"))


if __name__ == "__main__":
    unittest.main()
