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
