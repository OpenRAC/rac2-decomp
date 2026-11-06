"""Tests for tools/carry.py and levels.cross_identity(): no game data, no toolchains."""
import contextlib
import json
import os
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


class BootSplits(unittest.TestCase):
    def fixture(self, root, corrupt=None, length=656, named_callee="callee"):
        main, sound = "func_00131D98", "func_00131DE8"
        start, other = 0x00131D98, 0x00131DF8
        primary = code(0x24020001, 0x0C000000 | (0x00150000 >> 2), *([0x24020001] * 18))
        tail = code(0x24030002, 0x0C000000 | (0x00150000 >> 2), *([0x24030002] * 142))
        target = bytearray(primary + tail)
        struct.pack_into("<I", target, 4, 0x0C000000 | (0x00150100 >> 2))
        struct.pack_into("<I", target, 84, 0x0C000000 | (0x00150100 >> 2))
        if corrupt is not None:
            target[corrupt] ^= 1
        path = root / "config/boot/functions.tsv"
        path.parent.mkdir(parents=True)
        path.write_text(f"{main}\t{start:08X}\t80\n{sound}\t{start + 80:08X}\t576\n"
                        "callee\t00150000\t8\n")
        rows = [(main, other, length), (named_callee, 0x00150100, 8)]
        return rows, other, primary + tail, bytes(target)

    def run_fixture(self, root, rows, other, reference, target, target_sections=None):
        def sections(path):
            if path == root / "baserom/SCUS_972.68":
                return [("core.text", 0x00131D98, reference)]
            return target_sections if target_sections is not None else [("core.text", other, target)]
        with patch.object(carry, "ROOT", root), \
             patch.object(carry, "boot_sections", side_effect=sections), \
             patch.object(levels, "BOOT", root / "secondary"):
            return carry.correct_boot_splits(rows)

    def test_split_preserves_end_and_is_idempotent(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            rows, other, reference, target = self.fixture(root)
            fixed = self.run_fixture(root, rows, other, reference, target)
            self.assertEqual(fixed[:2], [("func_00131D98", other, 80), ("func_00131DE8", other + 80, 576)])
            self.assertEqual(fixed[1][1] + fixed[1][2], other + 656)
            self.assertEqual(self.run_fixture(root, fixed, other, reference, target), fixed)

    def test_changed_body_or_callee_is_rejected(self):
        for corrupt, named in ((0, "callee"), (80, "callee"), (None, "different")):
            with self.subTest(corrupt=corrupt, callee=named), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                rows, other, reference, target = self.fixture(root, corrupt=corrupt, named_callee=named)
                with self.assertRaises(ValueError):
                    self.run_fixture(root, rows, other, reference, target)

    def test_partial_or_unexpected_extent_is_rejected(self):
        for size in (80, 652):
            with self.subTest(size=size), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                rows, other, reference, target = self.fixture(root, length=size)
                with self.assertRaises(ValueError):
                    self.run_fixture(root, rows, other, reference, target)

    def test_unrelated_rows_are_untouched(self):
        rows = [("another", 0x1000, 656)]
        self.assertIs(carry.correct_boot_splits(rows), rows)

    def test_conflicting_target_metadata_is_rejected(self):
        for conflict in ("duplicate", "overlap", "sound"):
            with self.subTest(conflict=conflict), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                rows, other, reference, target = self.fixture(root)
                if conflict == "duplicate":
                    rows.append(rows[0])
                elif conflict == "overlap":
                    rows.append(("inside", other + 40, 8))
                else:
                    rows.append(("func_00131DE8", other + 80, 576))
                with self.assertRaises(ValueError):
                    self.run_fixture(root, rows, other, reference, target)

    def test_changed_primary_boundary_is_rejected(self):
        for old, new in (("00131DE8", "00131DEC"), ("\t576", "\t572")):
            with self.subTest(new=new), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                rows, other, reference, target = self.fixture(root)
                path = root / "config/boot/functions.tsv"
                path.write_text(path.read_text().replace(old, new))
                with self.assertRaises(ValueError):
                    self.run_fixture(root, rows, other, reference, target)

    def test_target_data_or_section_crossing_is_rejected(self):
        for kind in (".data", ".vutext", "crossing"):
            with self.subTest(kind=kind), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                rows, other, reference, target = self.fixture(root)
                sections = [(kind, other, target)] if kind != "crossing" else [
                    ("core.text", other, target[:80]), (".text", other + 80, target[80:])]
                with self.assertRaises(ValueError):
                    self.run_fixture(root, rows, other, reference, target, target_sections=sections)


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
    def test_core_only_repairs_leave_level_rows_and_reject_changed_residue_atomically(self):
        for base in (0x110000, 0x210008, 0x310010):
            with self.subTest(base=base), tempfile.TemporaryDirectory() as d:
                boot, catalogue = Path(d)/"boot.tsv", Path(d)/"levels.tsv"
                boot.write_text("# name\taddress\tsize\n" +
                    f"func_001158F4\t{base:08X}\t460\n" +
                    f"func_0011B320\t{base+0x200:08X}\t4\n" +
                    f"func_0011B450\t{base+0x300:08X}\t4\n" +
                    f"unrelated\t{base+0x400:08X}\t4\n")
                catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n"
                    "untouched\tshared\t4\tsame\t1\t00:00400000\n")
                with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue), \
                     patch.object(levels, "level_text", side_effect=AssertionError("core-only repair read a level")):
                    carry.refresh_entries()
                    self.assertEqual(levels.read_boot_functions(),
                        [("func_001158F4",base+4,456), ("unrelated",base+0x400,4)])
                    self.assertEqual(levels.read_catalogue(),
                        [("untouched","shared",4,"same",[(0,0x400000)])])
                    first = boot.read_bytes(),catalogue.read_bytes()
                    carry.refresh_entries()
                    self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),first)
                    with boot.open("a") as f:
                        f.write(f"func_0011B450\t{base+0x300:08X}\t8\n")
                    invalid = boot.read_bytes(),catalogue.read_bytes()
                    with self.assertRaisesRegex(ValueError,"residue changed"):
                        carry.refresh_entries()
                    self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),invalid)

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

    def split_fixture(self, *tail):
        """A boot with two closed functions at 0x2000, a gap word between them, and one level copy."""
        body = code(addiu(2,0,1),JR_RA,NOP,NOP,addiu(2,0,2),JR_RA,NOP)
        spec = {"whole": (28, (("whole",0,12), ("part",16,12)))}
        boot = [("before",0x1FF8,8), ("whole",0x2000,28), ("after",0x2020,8)]
        rows = [("whole","boot",28,"old",[(0,0x3000),(1,0x4000)])]
        read = lambda p, n: (body + b"".join(tail))[p - 0x2000:p - 0x2000 + n]
        return spec, boot, rows, read, body

    def split_release(self, spec, boot, rows, read, level_text):
        with patch.dict(levels.RELEASE_FUNCTION_SPLITS, spec, clear=True), \
             patch.object(levels,"boot_bytes",side_effect=read), \
             patch.object(levels,"level_text",side_effect=level_text):
            return carry.split_release_rows(boot, rows)

    def test_release_split_gives_each_function_a_row_at_every_place(self):
        spec, boot, rows, read, body = self.split_fixture()
        new_boot, new_rows = self.split_release(spec, boot, rows, read, [(0x3000,body),(0x4000,body)])
        self.assertEqual(new_boot, [("before",0x1FF8,8), ("whole",0x2000,12), ("part",0x2010,12), ("after",0x2020,8)])
        self.assertEqual([(r[0],r[1],r[2],r[4]) for r in new_rows],
                         [("whole","boot",12,[(0,0x3000),(1,0x4000)]), ("part","boot",12,[(0,0x3010),(1,0x4010)])])
        again = self.split_release(spec, new_boot, new_rows, read, [])
        self.assertEqual(again, (new_boot, new_rows))

    def test_release_split_rejects_what_was_not_measured(self):
        spec, boot, rows, read, body = self.split_fixture()
        other = code(addiu(2,0,1),JR_RA,NOP,NOP,lui(2,3),JR_RA,NOP)
        for why, changed, message in (
                ("no return", {"whole": (28, (("whole",0,8), ("part",16,12)))}, "does not close"),
                ("short", {"whole": (28, (("whole",0,4), ("part",16,12)))}, "does not close")):
            with self.subTest(why=why), self.assertRaisesRegex(ValueError, message):
                self.split_release(changed, boot, rows, read, [(0x3000,body),(0x4000,body)])
        gap = code(addiu(2,0,1),JR_RA,NOP,addiu(2,0,9),addiu(2,0,2),JR_RA,NOP)
        with self.assertRaisesRegex(ValueError, "non-zero"):
            self.split_release(spec, boot, rows, read, [(0x3000,gap),(0x4000,gap)])
        with self.assertRaisesRegex(ValueError, "split copies differ"):
            self.split_release(spec, boot, rows, read, [(0x3000,body),(0x4000,other)])
        with self.assertRaisesRegex(ValueError, "child identity"):
            self.split_release(spec, boot + [("part",0x2010,12)], [], read, [])
        with self.assertRaisesRegex(ValueError, "20 bytes, expected 28 or 12"):
            self.split_release(spec, [("whole",0x2000,20)], [], read, [])
        with self.assertRaisesRegex(ValueError, "20 bytes, expected 28 or 12"):
            self.split_release(spec, [], [("whole","boot",20,"old",[(0,0x3000)])], read, [])

    def place_split(self, words, spec=("old", (8, 0xAA, "new", 0xBB))):
        rows = [("old","shared",12,"fp",[(n,0x1000) for n in range(len(words))])]
        texts = [(0x1000,code(0,0,w)) for w in words]
        with patch.dict(levels.RELEASE_PLACE_SPLITS, dict([spec]), clear=True), \
             patch.object(levels,"level_text",side_effect=texts):
            return carry.split_release_places(rows)

    def test_release_place_split_regroups_by_the_measured_word(self):
        self.assertEqual(self.place_split((0xAA,0xAA,0xBB)),
                         [("old","shared",12,"fp",[(0,0x1000),(1,0x1000)]), ("new","level",12,"fp",[(2,0x1000)])])
        self.assertEqual(self.place_split((0xAA,0xAA)), [("old","shared",12,"fp",[(0,0x1000),(1,0x1000)])])
        for words in ((0xAA,0xCC), (0xBB,0xBB)):
            with self.subTest(words=words), self.assertRaises(ValueError):
                self.place_split(words)

    def row_merge(self, rows, texts, spec=("kept", ("copy",))):
        with patch.dict(levels.RELEASE_ROW_MERGES, dict([spec]), clear=True), \
             patch.object(levels,"level_text",side_effect=lambda path: texts[int(path.name[:2])]):
            return carry.merge_release_rows([], rows)[1]

    def test_release_row_merge_gives_the_kept_row_every_place(self):
        body = code(addiu(29,29,-16), lui(2,0x30), lw(2,2,8), lw(3,4,0x2000), JR_RA, addiu(29,29,16))
        moved = code(addiu(29,29,-16), lui(2,0x31), lw(2,2,12), lw(3,4,0x2000), JR_RA, addiu(29,29,16))
        fp = levels.fingerprint(body, 0x1000)
        self.assertEqual(levels.fingerprint(moved, 0x1000), fp)
        texts = {0:(0x1000,body), 1:(0x1000,moved), 2:(0x1000,body)}
        rows = [("kept","shared",24,fp,[(0,0x1000),(2,0x1000)]), ("other","level",4,"x",[(0,0x2000)]),
                ("copy","level",24,fp,[(1,0x1000)])]
        out = self.row_merge(rows, texts)
        self.assertEqual(out, [("kept","shared",24,fp,[(0,0x1000),(1,0x1000),(2,0x1000)]), rows[1]])
        self.assertEqual(self.row_merge(out, texts), out)
        # A constant the fingerprint masks, another fingerprint, a level twice, or no kept row: all fail.
        other = code(addiu(29,29,-16), lui(2,0x30), lw(2,2,8), lw(3,4,0x3000), JR_RA, addiu(29,29,16))
        self.assertEqual(levels.fingerprint(other, 0x1000), fp)
        for why, change, message in (
                ("constant", lambda t, r: t.update({1:(0x1000,other)}), "not the body"),
                ("fingerprint", lambda t, r: r.__setitem__(2, ("copy","level",24,"x",[(1,0x1000)])), "fingerprint"),
                ("level twice", lambda t, r: r.__setitem__(2, ("copy","level",24,fp,[(2,0x1000)])), "one level"),
                ("no kept row", lambda t, r: r.__delitem__(0), "no kept row")):
            with self.subTest(why=why), self.assertRaisesRegex(ValueError, message):
                t, r = dict(texts), list(rows)
                change(t, r)
                self.row_merge(r, t)

    def test_release_row_merge_gives_a_merged_boot_entry_the_kept_name(self):
        body = code(addiu(29,29,-16), lui(2,0x30), lw(2,2,8), lw(3,4,0x2000), JR_RA, addiu(29,29,16))
        fp = levels.fingerprint(body, 0x1000)
        texts = {0:(0x1000,body), 1:(0x1000,body)}
        boot = [("before",0x5000,8), ("copy",0x5008,24), ("after",0x5020,8)]
        rows = [("kept","shared",24,fp,[(0,0x1000)]), ("copy","boot",24,fp,[(1,0x1000)])]
        boot_image = bytes(8) + body + bytes(8)

        def merge(boot, rows, image=boot_image):
            with patch.dict(levels.RELEASE_ROW_MERGES, {"kept": ("copy",)}, clear=True), \
                 patch.object(levels,"boot_bytes",side_effect=lambda a, n: image[a - 0x5000:a - 0x5000 + n]), \
                 patch.object(levels,"level_text",side_effect=lambda path: texts[int(path.name[:2])]):
                return carry.merge_release_rows(boot, rows)

        new_boot, new_rows = merge(boot, rows)
        self.assertEqual(new_boot, [("before",0x5000,8), ("kept",0x5008,24), ("after",0x5020,8)])
        self.assertEqual(new_rows, [("kept","boot",24,fp,[(0,0x1000),(1,0x1000)])])
        self.assertEqual(merge(new_boot, new_rows), (new_boot, new_rows))
        other = code(addiu(29,29,-16), lui(2,0x30), lw(2,2,8), lw(3,4,0x3000), JR_RA, addiu(29,29,16))
        with self.assertRaisesRegex(ValueError, "the boot's copy is not the body of kept"):
            merge(boot, rows, bytes(8) + other + bytes(8))
        with self.assertRaisesRegex(ValueError, "kept is a boot function already"):
            merge(boot + [("kept",0x6000,24)], rows)
        with self.assertRaisesRegex(ValueError, "boot entry is left without its row"):
            merge(boot, rows[:1])

    def realign(self, images, rows, spec, boot=()):
        """realign_release_places() over level texts IMAGES {level: (base, bytes)}."""
        with patch.dict(levels.RELEASE_PLACE_RUNS, spec, clear=True), \
             patch.object(levels, "NAMES", {n: "test" for n in images}), \
             patch.object(levels, "level_text", side_effect=lambda p: images[int(p.name[:2])]):
            return carry.realign_release_places(list(boot), rows)

    T = 0x300000        # level code, above the boot's resident memory

    def stretch(self, call=0x301000):
        """Levels 0 and 1 hold A (constant 1, calling H) then B (constant 2); level 2 holds
        the same two bodies, and the catalogue has a miscut row there and A one body late."""
        jal = lambda t: 3 << 26 | ((t >> 2) & 0x3FFFFFF)
        body = lambda k, c: code(addiu(4, 0, k), jal(c), NOP, JR_RA, NOP, 0)
        pad = lambda b: b + bytes(0x1000 - len(b)) + code(JR_RA, NOP, JR_RA, NOP)
        images = {lv: (self.T, pad(body(1, 0x301000) + body(2, 0x301000))) for lv in (0, 1)}
        images[2] = (self.T, pad(body(1, call) + body(2, 0x301000)))
        T = self.T
        rows = [("A", "shared", 20, "fa", [(0, T), (1, T), (2, T + 0x18)]),
                ("B", "shared", 20, "fb", [(0, T + 0x18), (1, T + 0x18)]),
                ("miscut", "level", 24, "fm", [(2, T)]),
                ("H", "shared", 8, "fh", [(0, T + 0x1000), (1, T + 0x1000), (2, T + 0x1000)]),
                ("G", "shared", 8, "fh", [(0, T + 0x1008), (1, T + 0x1008), (2, T + 0x1008)])]
        spec = {"A": ({2: T}, (("A", 0, 20), ("B", 0x18, 20)), ("miscut",))}
        return images, rows, spec

    def test_realign_gives_each_body_its_row_and_replays(self):
        images, rows, spec = self.stretch()
        T = self.T
        new = self.realign(images, rows, spec)
        self.assertEqual([r[0] for r in new], ["A", "B", "H", "G"])
        self.assertEqual(new[0], ("A", "shared", 20, "fa", [(0, T), (1, T), (2, T)]))
        self.assertEqual(new[1], ("B", "shared", 20, "fb", [(0, T + 0x18), (1, T + 0x18), (2, T + 0x18)]))
        self.assertEqual(self.realign(images, new, spec), new)
        self.assertEqual(self.realign(images, rows, {}), rows)

    def test_realign_rejects_what_the_bytes_do_not_show(self):
        images, rows, spec = self.stretch()
        T = self.T
        swapped = {"A": ({2: T}, (("A", 0x18, 20), ("B", 0, 20)), ("miscut",))}
        with self.assertRaisesRegex(ValueError, "another function|differs at"):
            self.realign(images, rows, swapped)
        # Level 2's first body calls G where levels 0 and 1 call H: not A's copy.
        with self.assertRaisesRegex(ValueError, "A: level 2 place 00300000 calls G, level 0 calls H"):
            self.realign(self.stretch(call=0x301008)[0], rows, spec)
        with self.assertRaisesRegex(ValueError, "C: level 2 place 00300010 overlaps the stretch"):
            self.realign(images, rows + [("C", "level", 8, "fc", [(2, T + 0x10)])], spec)
        # A retired row reaching a word the stretch does not hold would leave that word rowless.
        base, data = images[2]
        tail = {**images, 2: (base, data[:0x30] + code(JR_RA) + data[0x34:])}
        with self.assertRaisesRegex(ValueError, "word 00300030 would lose its row"):
            self.realign(tail, [r if r[0] != "miscut" else (r[0], r[1], 64, r[3], r[4]) for r in rows], spec)
        with self.assertRaisesRegex(ValueError, "partly realigned"):
            self.realign(images, [r for r in rows if r[0] != "miscut"], spec)
        done = self.realign(images, rows, spec)
        with self.assertRaisesRegex(ValueError, "partly realigned"):
            self.realign(images, done + [rows[2]], spec)
        with self.assertRaisesRegex(ValueError, "A: 20 bytes, expected 24"):
            self.realign(images, rows, {"A": ({2: T}, (("A", 0, 24),), ("miscut",))})
        with self.assertRaisesRegex(ValueError, "miscut: retired row has a place outside"):
            self.realign(images, [r if r[0] != "miscut" else (r[0], r[1], r[2], r[3], [(1, T + 0x800), (2, T)])
                                  for r in rows], spec)

    def test_realign_ignores_only_words_that_differ_between_the_rows_own_copies(self):
        images, rows, spec = self.stretch()
        gp = lambda off: 0x8F820000 | off                                  # lw v0,off(gp)
        # A's $gp offset (its jal's delay slot) differs between levels 0 and 1: level 2's third is no evidence.
        for lv, off in ((0, 0x10), (1, 0x18), (2, 0x20)):
            base, data = images[lv]
            images[lv] = (base, data[:8] + code(gp(off)) + data[12:])
        new = self.realign(images, rows, spec)
        self.assertEqual(new[0][4][2], (2, self.T))
        # B's constant is the same in levels 0 and 1, so a third value in level 2 is another function.
        base, data = images[2]
        images[2] = (base, data[:0x18] + code(addiu(4, 0, 3)) + data[0x1C:])
        with self.assertRaisesRegex(ValueError, "B: level 2 place 00300018 (is another function|differs at)"):
            self.realign(images, rows, spec)

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


class Demotion(unittest.TestCase):
    """tools/carry.py --demote: what the build disproves, without realigning the release."""

    # A release's catalogues: the boot's functions and the levels' rows, in the order the
    # files hold them. func_00292078 and func_002923C0 are v1.01's and carried;
    # func_US2_0026EDE8 is the release's own already; func_L00_002A4EF8 is v1.01's level code.
    BOOT = [("func_US2_0026EDE8", 0x0026EDE8, 2340), ("func_00270000", 0x00270000, 64),
            ("func_00292078", 0x00292928, 684), ("func_002923C0", 0x00292C70, 72)]
    LEVELS = [("func_L00_002A4EF8", "shared", 100, "a1b2c3d4e5f60718", [(0, 0x002A4EF8), (1, 0x002A5000)]),
              ("func_US2_0026EDE8", "boot", 2340, "0f0f0f0f0f0f0f0f", [(0, 0x002C0000), (1, 0x002C1000)]),
              ("func_00292078", "boot", 684, "7b47d4fd57697082", [(0, 0x002FE988), (1, 0x002F4360)]),
              ("func_002923C0", "boot", 72, "24842a773af07fe4", [(0, 0x002FECD0), (1, 0x002F46A8)])]

    @contextlib.contextmanager
    def release(self, root: Path):
        """The tools work on ROOT's copies of the release's tables, and back again after."""
        saved = {k: getattr(levels, k) for k in
                 ("VERSION", "ISO", "BOOT", "DUMP", "LEVELS", "CATALOGUE", "BOOT_FUNCTIONS",
                  "BOOT_PAIRS", "LEVEL_BASE", "GP")}
        try:
            with patch.dict(os.environ), patch.object(carry, "ROOT", root), \
                 patch.object(levels, "ROOT", root):
                yield
        finally:
            for k, v in saved.items():
                setattr(levels, k, v)

    def write_release(self, root: Path) -> None:
        """A release tree: its catalogues, what its last build found, its own sources."""
        (root / "config/us2/boot").mkdir(parents=True)
        (root / "config/us2/levels").mkdir(parents=True)
        (root / "config/us2/boot/functions.tsv").write_text(
            "# name\taddress\tsize -- tools/carry.py\n" +
            "".join(f"{n}\t{a:08X}\t{s}\n" for n, a, s in self.BOOT))
        (root / "config/us2/levels/functions.tsv").write_text(
            "# name\tkind\tsize\tfingerprint\tlevels\tplaces (level:address) -- tools/carry.py\n" +
            "".join(f"{n}\t{k}\t{s}\t{fp}\t{len({p[0] for p in places})}\t" +
                    ",".join(f"{lv:02d}:{a:08X}" for lv, a in places) + "\n"
                    for n, k, s, fp, places in self.LEVELS))
        (root / "config/us2/not_carried.tsv").write_text(
            "# v1.01 function\twhat tools/build.py said (the first program) -- tools/carry.py --demote\n"
            "func_0029B720\tboot: instruction at +0x1c differs\n")
        (root / "build/us2/boot").mkdir(parents=True)
        (root / "build/us2/boot/placed.json").write_text(json.dumps({"differ": {
            "func_00292078": "instruction at +0x4f0 differs"}}))
        (root / "src/us2/game").mkdir(parents=True)
        (root / "src/us2/game/0026EDE8.c").write_text(
            '#include "include_asm.h"\n\nINCLUDE_ASM("asm/us2/game", func_US2_0026EDE8);\n')

    @staticmethod
    def sections(*_):
        """The boot's sections, without the boot executable: enough for the layout rules."""
        return [("core.text", 0x001E0000, code(0, 0)), (".text", 0x00200000, code(0, 0))]

    def test_the_calls_of_the_release_are_read_from_its_own_code(self):
        """The boot's calls, and a level's calls to the boot's resident code and to its own."""
        jal = lambda target: 3 << 26 | (target >> 2)
        boot = [("func_00100000", 0x00100000, 8), ("func_00100008", 0x00100008, 4)]
        rows = [("func_L00_002A4EF8", "level", 8, "a" * 16, [(0, 0x002A4EF8)]),
                ("func_L00_002A5000", "level", 4, "b" * 16, [(0, 0x002A5000)])]
        boot_data = code(jal(0x00100008), NOP) + code(JR_RA, NOP)
        level_data = code(jal(0x00100000), jal(0x002A5000)) + bytes(0x100) + code(JR_RA, NOP)
        with patch.object(carry, "boot_sections", return_value=[("core.text", 0x00100000, boot_data)]), \
             patch.object(levels, "level_text", return_value=(0x002A4EF8, level_data)):
            edges = carry.call_edges(boot, rows)
        self.assertEqual(sorted(edges), [("func_00100000", "func_00100008"),
                                         ("func_L00_002A4EF8", "func_00100000"),
                                         ("func_L00_002A4EF8", "func_L00_002A5000")])

    def test_only_the_measured_function_and_its_carried_callers_are_demoted(self):
        edges = [("func_002923C0", "func_00292078"), ("func_US2_0026EDE8", "func_00292078")]
        carried = {"func_00292078", "func_002923C0", "func_00270000", "func_L00_002A4EF8"}
        demoted = carry.demoted_names({"func_00292078"}, edges, carried)
        self.assertEqual(demoted, {"func_00292078", "func_002923C0"})

    def test_demotion_reaches_a_fixed_point(self):
        edges = [("b", "a"), ("c", "b"), ("d", "c")]
        demoted = carry.demoted_names({"a"}, edges, {"a", "b", "c", "d"})
        self.assertEqual(demoted, {"a", "b", "c", "d"})

    def test_demotion_keeps_every_other_row_of_the_catalogue(self):
        boot, rows, renames = carry.demote_catalogue("US2", self.BOOT, self.LEVELS, {"func_00292078"})
        self.assertEqual(renames, {"func_00292078": "func_US2_00292928"})
        self.assertEqual(boot[0], ("func_US2_0026EDE8", 0x0026EDE8, 2340))
        self.assertEqual(boot[1], ("func_00270000", 0x00270000, 64))
        self.assertEqual(boot[2], ("func_US2_00292928", 0x00292928, 684))
        self.assertEqual(boot[3], ("func_002923C0", 0x00292C70, 72))
        self.assertEqual(rows[0], self.LEVELS[0])
        self.assertEqual(rows[1], self.LEVELS[1])
        self.assertEqual(rows[2], ("func_US2_00292928", "boot", 684, "7b47d4fd57697082",
                                   [(0, 0x002FE988), (1, 0x002F4360)]))
        self.assertEqual(rows[3], self.LEVELS[3])

    def test_a_demoted_level_function_is_named_by_its_first_place(self):
        rows = [("func_L00_002A4EF8", "shared", 100, "a1b2c3d4e5f60718",
                 [(0, 0x002A4EF8), (1, 0x002A5000)])]
        boot, new, renames = carry.demote_catalogue("US2", [], rows, {"func_L00_002A4EF8"})
        self.assertEqual(renames, {"func_L00_002A4EF8": "func_US2_L00_002A4EF8"})
        self.assertEqual(new, [("func_US2_L00_002A4EF8", "shared", 100, "a1b2c3d4e5f60718",
                                [(0, 0x002A4EF8), (1, 0x002A5000)])])

    def test_the_build_measurements_keep_the_knock_on_rows_out(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / "build/us2/boot").mkdir(parents=True)
            (root / "build/us2/boot/placed.json").write_text(json.dumps({"differ": {
                "func_00292078": "instruction at +0x4f0 differs",
                "func_002923C0": "needs func_00292078 at its place, which is not C",
                "func_US2_0026EDE8": "instruction at +0x4 differs"}}))
            with patch.object(carry, "ROOT", root):
                measured = carry.measured_not_carried("us2")
            self.assertEqual(measured, {"func_00292078": "boot: instruction at +0x4f0 differs"})

    def test_a_knock_on_row_is_not_a_mismatch_even_with_a_reason_of_its_own(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            (root / "build/us2/00_aranos_tutorial").mkdir(parents=True)
            (root / "build/us2/00_aranos_tutorial/placed.json").write_text(json.dumps({"differ": {
                "func_00292078": "instruction at +0x4f0 differs, which is not C"}}))
            with patch.object(carry, "ROOT", root):
                self.assertEqual(carry.measured_not_carried("us2"), {})

    def test_the_list_of_what_a_release_does_not_carry_keeps_its_rows(self):
        with tempfile.TemporaryDirectory() as d:
            path = Path(d) / "not_carried.tsv"
            path.write_text("# a header\nfunc_0029B720\tboot: instruction at +0x1c differs\n")
            names = carry.read_not_carried(path)
            self.assertEqual(names, {"func_0029B720": "boot: instruction at +0x1c differs"})
            names.setdefault("func_00292078", "boot: instruction at +0x4f0 differs")
            carry.write_not_carried(path, names)
            self.assertEqual(path.read_text(),
                             "# v1.01 function\twhat tools/build.py said (the first program) -- tools/carry.py --demote\n"
                             "func_0029B720\tboot: instruction at +0x1c differs\n"
                             "func_00292078\tboot: instruction at +0x4f0 differs\n")

    def test_the_demotion_changes_only_what_the_build_disproved(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.write_release(root)
            edges = [("func_002923C0", "func_00292078"), ("func_US2_0026EDE8", "func_00292078")]
            with self.release(root), \
                 patch.object(carry, "call_edges", return_value=edges), \
                 patch.object(carry, "boot_sections", side_effect=self.sections):
                carry.demote("us2")
            self.assertEqual((root / "config/us2/boot/functions.tsv").read_text(),
                             "# name\taddress\tsize -- tools/carry.py\n"
                             "func_US2_0026EDE8\t0026EDE8\t2340\n"
                             "func_00270000\t00270000\t64\n"
                             "func_US2_00292928\t00292928\t684\n"
                             "func_US2_00292C70\t00292C70\t72\n")
            self.assertEqual((root / "config/us2/levels/functions.tsv").read_text(),
                             "# name\tkind\tsize\tfingerprint\tlevels\tplaces (level:address) -- tools/carry.py\n"
                             "func_L00_002A4EF8\tshared\t100\ta1b2c3d4e5f60718\t2\t00:002A4EF8,01:002A5000\n"
                             "func_US2_0026EDE8\tboot\t2340\t0f0f0f0f0f0f0f0f\t2\t00:002C0000,01:002C1000\n"
                             "func_US2_00292928\tboot\t684\t7b47d4fd57697082\t2\t00:002FE988,01:002F4360\n"
                             "func_US2_00292C70\tboot\t72\t24842a773af07fe4\t2\t00:002FECD0,01:002F46A8\n")
            self.assertEqual((root / "config/us2/not_carried.tsv").read_text(),
                             "# v1.01 function\twhat tools/build.py said (the first program) -- tools/carry.py --demote\n"
                             "func_0029B720\tboot: instruction at +0x1c differs\n"
                             "func_00292078\tboot: instruction at +0x4f0 differs\n")
            self.assertNotIn(b"\r\n", (root / "config/us2/not_carried.tsv").read_bytes())
            self.assertEqual((root / "src/us2/game/00292928.c").read_text(),
                             '#include "include_asm.h"\n\n'
                             'INCLUDE_ASM("asm/us2/game", func_US2_00292928);\n\n'
                             'INCLUDE_ASM("asm/us2/game", func_US2_00292C70);\n')

    def test_the_demotion_is_idempotent(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.write_release(root)
            edges = [("func_002923C0", "func_00292078")]
            with self.release(root), \
                 patch.object(carry, "call_edges", return_value=edges), \
                 patch.object(carry, "boot_sections", side_effect=self.sections):
                carry.demote("us2")
                first = {p: p.read_bytes() for p in sorted(root.rglob("*")) if p.is_file()}
                carry.demote("us2")
                second = {p: p.read_bytes() for p in sorted(root.rglob("*")) if p.is_file()}
            self.assertEqual(first, second)

    def test_a_marker_file_that_is_there_is_not_overwritten(self):
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            self.write_release(root)
            (root / "src/us2/game/00292928.c").write_text("# a file of my own\n")
            before = (root / "config/us2/boot/functions.tsv").read_bytes()
            edges = [("func_002923C0", "func_00292078")]
            with self.release(root), \
                 patch.object(carry, "call_edges", return_value=edges), \
                 patch.object(carry, "boot_sections", side_effect=self.sections):
                with self.assertRaises(SystemExit):
                    carry.demote("us2")
            self.assertEqual((root / "src/us2/game/00292928.c").read_text(), "# a file of my own\n")
            self.assertEqual((root / "config/us2/boot/functions.tsv").read_bytes(), before)
            self.assertFalse((root / "src/us2/game/00292C70.c").exists())
            self.assertFalse((root / "src/us2/game/00292928.c").read_text().count("INCLUDE_ASM"))


if __name__ == "__main__":
    unittest.main()
