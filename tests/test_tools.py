"""Tests for tools/levels.py and tools/elf.py: no game data, no toolchains."""
import copy
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


class SplitLevelEntries(unittest.TestCase):
    def fixture(self, root, table="camvtbl", count=1):
        name = "func_L06_0047C1D0"
        parts = ((name,8), ("func_L06_0047C1D8",8), ("func_L06_0047C1E0",8))
        body = code(0x03E00008,0) * 3
        kind = "shared" if count > 1 else "level"
        places = []
        for number in (6,13)[:count]:
            address = 0x2000 + number * 0x100
            places.append((number,address))
            directory = root / levels.level_dir(number)
            directory.mkdir(parents=True)
            (directory/"manifest.json").write_text(json.dumps({"sections":[
                {"name":"text","address":address,"size":len(body),"type":1}]}))
            (directory/"text.bin").write_bytes(body)
            (directory/"camvtbl.bin").write_bytes(code(23,0,address,address+8,address+16,0xFFFFFFFF))
            (directory/"vtbl.bin").write_bytes(code(4563,address+8,0))
        if table == "vtbl":
            parts = parts[:2]
            body = body[:16]
            for number,_ in places:
                (root/levels.level_dir(number)/"text.bin").write_bytes(body)
        fp = levels.fingerprint(body, places[0][1])
        spec = {name:(fp,kind,count,table,1,parts)}
        return [(name,kind,len(body),fp,places)], spec

    def test_witnessed_split_preserves_end_places_and_replays(self):
        for table,count in (("camvtbl",1),("camvtbl",2),("vtbl",1)):
            with self.subTest(table=table,count=count), tempfile.TemporaryDirectory() as d:
                root=Path(d);rows,spec=self.fixture(root,table,count)
                before=list(rows)
                with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec):
                    split=levels.split_level_rows(rows)
                    self.assertEqual(levels.split_level_rows(split),split)
                self.assertEqual(rows,before)
                self.assertEqual(sum(r[2] for r in split),rows[0][2])
                for index,row in enumerate(split):
                    self.assertEqual(row[4],[(lv,a+8*index) for lv,a in rows[0][4]])
                    self.assertEqual(row[1],rows[0][1])

    def test_changed_body_or_missing_dispatch_witness_is_rejected(self):
        for change in ("body","outside text","wrong slot","unentered","after terminator"):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as d:
                root=Path(d);rows,spec=self.fixture(root)
                directory=root/levels.level_dir(6);a=rows[0][4][0][1]
                if change=="body": (directory/"text.bin").write_bytes(code(0x24020001,0)*3)
                elif change=="outside text": (directory/"text.bin").write_bytes(code(0x03E00008,0)*2)
                elif change=="wrong slot": (directory/"camvtbl.bin").write_bytes(code(a,a+8,a+16,0,0))
                elif change=="after terminator": (directory/"camvtbl.bin").write_bytes(code(0xFFFFFFFF,0,0,0,0,23,0,a,a+8,a+16))
                else: (directory/"camvtbl.bin").write_bytes(code(23,0,a,0,a+16))
                with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec), self.assertRaises(ValueError):
                    levels.split_level_rows(rows)

    def test_partial_conflicting_overlapping_and_duplicate_metadata_is_rejected(self):
        for change in ("duplicate","child in merged","missing child","wrong child","overlap","kind","places","fingerprint"):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as d:
                root=Path(d);rows,spec=self.fixture(root)
                with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec):
                    split=levels.split_level_rows(rows)
                    if change=="duplicate": bad=rows+rows
                    elif change=="child in merged": bad=rows+[split[1]]
                    elif change=="missing child": bad=split[:-1]
                    elif change=="wrong child":
                        bad=list(split);r=bad[1];bad[1]=(r[0],r[1],r[2],r[3],[(6,r[4][0][1]+4)])
                    elif change=="overlap": bad=rows+[("unrelated","level",8,"",[(6,rows[0][4][0][1]+8)])]
                    else:
                        r=list(rows[0]);r[{"kind":1,"places":4,"fingerprint":3}[change]]={"kind":"shared","places":r[4]*2,"fingerprint":"wrong"}[change];bad=[tuple(r)]
                    with self.assertRaises(ValueError): levels.split_level_rows(bad)

    def test_changed_second_shared_copy_is_rejected(self):
        with tempfile.TemporaryDirectory() as d:
            root=Path(d);rows,spec=self.fixture(root,count=2)
            (root/levels.level_dir(13)/"text.bin").write_bytes(code(0x24020001,0)*3)
            with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec), self.assertRaises(ValueError):
                levels.split_level_rows(rows)

    def test_shared_callbacks_accept_each_measured_dispatch_kind(self):
        with tempfile.TemporaryDirectory() as d:
            root=Path(d);rows,spec=self.fixture(root,count=2)
            name=rows[0][0];rule=list(spec[name]);rule[3]={"default":"camvtbl",13:"vtbl"};spec[name]=tuple(rule)
            a=rows[0][4][1][1]
            (root/levels.level_dir(13)/"vtbl.bin").write_bytes(code(101,a,0,102,a+8,0,103,a+16,0))
            with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec):
                split=levels.split_level_rows(rows)
                self.assertEqual(levels.split_level_rows(split),split)
                self.assertEqual([r[4] for r in split],
                    [[(lv,p+8*i) for lv,p in rows[0][4]] for i in range(3)])

    def test_object_dispatch_must_witness_all_three_callback_entries(self):
        for missing in (0,1,2):
            with self.subTest(missing=missing), tempfile.TemporaryDirectory() as d:
                root=Path(d);rows,spec=self.fixture(root,count=2)
                name=rows[0][0];rule=list(spec[name]);rule[3]={"default":"camvtbl",13:"vtbl"};spec[name]=tuple(rule)
                a=rows[0][4][1][1];data=[]
                for i in range(3):data.extend((101+i,0 if i==missing else a+8*i,0))
                (root/levels.level_dir(13)/"vtbl.bin").write_bytes(code(*data))
                with patch.object(levels,"DUMP",root), patch.object(levels,"LEVEL_FUNCTION_SPLITS",spec), self.assertRaises(ValueError):
                    levels.split_level_rows(rows)

    def test_unrelated_rows_are_not_split_from_return_bytes(self):
        rows=[("unrelated","level",24,"",[(6,0x2000)])]
        self.assertEqual(levels.split_level_rows(rows),rows)

    def test_catalogue_keeps_equal_byte_families_and_unrelated_old_extents(self):
        with tempfile.TemporaryDirectory() as d:
            root=Path(d);rows,spec=self.fixture(root,count=2)
            body=code(0x03E00008,0)*3
            address=rows[0][4][1][1]
            other="func_L13_00002E00"
            parts=((other,8),("func_L13_00002E08",8),("func_L13_00002E10",8))
            fp=levels.fingerprint(body,address)
            spec[other]=(fp,"level",1,"camvtbl",1,parts)
            unrelated="func_L13_00002F00"
            rows += [(other,"level",24,fp,[(13,address+0x100)]),
                     (unrelated,"level",24,fp,[(13,address+0x200)])]
            directory=root/levels.level_dir(13)
            raw=bytearray(0x218)
            for offset in (0,0x100,0x200): raw[offset:offset+24]=body
            (directory/"text.bin").write_bytes(raw)
            (directory/"camvtbl.bin").write_bytes(code(
                23,0,address,address+8,address+16,
                17,0,address+0x100,address+0x108,address+0x110,0xFFFFFFFF))
            boot,catalogue=root/"boot.tsv",root/"levels.tsv"
            boot.write_text("# name\taddress\tsize\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n"+"".join(
                f"{n}\t{k}\t{s}\t{f}\t{len(p)}\t"+",".join(f"{lv:02d}:{a:08X}" for lv,a in p)+"\n"
                for n,k,s,f,p in rows))
            with patch.multiple(levels, DUMP=root, LEVELS=root, CATALOGUE=catalogue,
                                BOOT_FUNCTIONS=boot, BOOT_PAIRS=root/"absent.tsv",
                                NAMES={6:"notak",13:"boldan"}, LEVEL_FUNCTION_SPLITS=spec,
                                FUNCTION_ENTRY_OFFSETS={},FUNCTION_RESIDUES={},BOOT_RESIDUES={}), \
                 patch.object(levels,"boot_image",return_value=(bytes(4),[(0x1000,0,4)])), \
                 patch.object(sys,"argv",["levels.py","catalogue"]):
                levels.catalogue()
                result={r[0]:r for r in levels.read_catalogue()}
                expected={n for rule in spec.values() for n,_ in rule[-1]}|{unrelated}
                self.assertEqual(set(result),expected)
                self.assertEqual(result[unrelated],rows[-1])
                for name,_ in spec[rows[0][0]][-1]:
                    self.assertEqual(result[name][1],"shared")
                    self.assertEqual({lv for lv,_ in result[name][4]},{6,13})
                for name,_ in parts:
                    self.assertEqual(result[name][1],"level")
                    self.assertEqual({lv for lv,_ in result[name][4]},{13})
                snapshot=boot.read_bytes(),catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),snapshot)
                legacy={"boot":[], "6_notak":[(rows[0][4][0][1],24)],
                        "13_boldan":[(address,24),(address+0x100,24),(address+0x200,24)]}
                with patch.object(sys,"argv",["levels.py","catalogue","--from-old"]), \
                     patch.object(levels,"old_extents",side_effect=lambda program:legacy[program]):
                    levels.catalogue()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),snapshot)
                raw[0]=1
                (directory/"text.bin").write_bytes(raw)
                with self.assertRaises(ValueError): levels.catalogue()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),snapshot)


class CodeWitnessedSplit(unittest.TestCase):
    """The 5 November 2026 boundary audit: a code-built callback address is an entry witness."""

    def fixture(self, root, pairs=1, target_offset=8):
        name, child, address = "func_L10_00419188", "func_L10_00419190", 0x2000
        body = code(0x24020001, 0) + code(0x03E00008, 0)
        caller = []
        for _ in range(pairs):
            caller += [lui(5, (address + target_offset + 0x8000) >> 16), 0,
                       addiu(5, 5, (address + target_offset) & 0xFFFF)]
        text = body + code(*caller)
        directory = root / levels.level_dir(10)
        directory.mkdir(parents=True)
        (directory / "manifest.json").write_text(json.dumps({"sections": [
            {"name": "text", "address": address, "size": len(text), "type": 1}]}))
        (directory / "text.bin").write_bytes(text)
        fp = levels.fingerprint(body, address)
        spec = {name: (fp, "level", 1, "text", 1, ((name, 8), (child, 8)))}
        return [(name, "level", 16, fp, [(10, address)])], spec

    def test_code_witness_splits_and_replays(self):
        with tempfile.TemporaryDirectory() as d:
            rows, spec = self.fixture(Path(d))
            with patch.object(levels, "DUMP", Path(d)), patch.object(levels, "LEVEL_FUNCTION_SPLITS", spec):
                split = levels.split_level_rows(rows)
                self.assertEqual(levels.split_level_rows(split), split)
            self.assertEqual([(r[0], r[2], r[4]) for r in split],
                             [("func_L10_00419188", 8, [(10, 0x2000)]), ("func_L10_00419190", 8, [(10, 0x2008)])])

    def test_missing_extra_or_misaimed_code_witness_is_rejected(self):
        for pairs, offset in ((0, 8), (2, 8), (1, 4), (1, 0)):
            with self.subTest(pairs=pairs, offset=offset), tempfile.TemporaryDirectory() as d:
                rows, spec = self.fixture(Path(d), pairs, offset)
                with patch.object(levels, "DUMP", Path(d)), patch.object(levels, "LEVEL_FUNCTION_SPLITS", spec), \
                        self.assertRaises(ValueError):
                    levels.split_level_rows(rows)

    def test_address_pair_needs_the_same_register(self):
        text = code(lui(5, 0x42), addiu(6, 4, 0x91E0), lui(4, 0x42), addiu(4, 4, -0x6E20))
        self.assertEqual(levels.code_address_pairs(text, 0, 0x4191E0), 1)
        self.assertEqual(levels.code_address_pairs(text, 0, 0x4291E0), 0)

    def test_audited_rows_keep_real_entries_and_the_pal_exception(self):
        # Referenced or returning rows of the audit stay functions.
        for name in ("func_002B9030", "func_002B9380", "func_002A1378", "func_002A677C", "func_002A08A0",
                     "func_00282848", "func_001325E0", "func_00131CB0"):
            with self.subTest(name=name):
                self.assertNotIn(name, levels.FUNCTION_RESIDUES)
        for name in ("func_0032A130", "func_L03_0041B848", "func_PAL_0032B920", "func_PAL_L00_003E63F0"):
            with self.subTest(name=name):
                self.assertEqual(levels.FUNCTION_ENTRY_OFFSETS[name], (16, 8))
                self.assertEqual(levels.function_extent(name, 0x32A130, 16), (0x32A138, 8))
                self.assertEqual(levels.function_extent(name, 0x32A138, 8), (0x32A138, 8))


class DelaySlotBoundary(unittest.TestCase):
    """6 November 2026: a fill-prefixed syscall stub and a PAL row that left its delay slot behind."""

    def test_named_corrections(self):
        self.assertEqual(levels.function_extent("func_0011A7F8", 0x11A7F8, 24), (0x11A800, 16))
        self.assertEqual(levels.function_extent("func_0011A7F8", 0x11A800, 16), (0x11A800, 16))
        self.assertTrue(levels.function_residue("func_L00_00309DB0", 28))
        with self.assertRaises(ValueError):
            levels.function_residue("func_L00_00309DB0", 24)
        name = "func_PAL_L00_0030BA80"
        self.assertEqual(levels.function_extent(name, 0x30BA80, 336), (0x30BA80, 340))
        self.assertEqual(levels.function_extent(name, 0x30BA80, 340), (0x30BA80, 340))
        with self.assertRaises(ValueError):
            levels.function_extent(name, 0x30BA80, 344)

    def fixture(self, root, ret):
        import carry
        address = 0x2000
        text = code(0x27BDFFE0, ret, 0x27BD0020, 0, 0x0000102D, 0)
        directory = root / levels.level_dir(0)
        directory.mkdir(parents=True)
        (directory / "manifest.json").write_text(json.dumps({"sections": [
            {"name": "text", "address": address, "size": len(text), "type": 1}]}))
        (directory / "text.bin").write_bytes(text)
        rows = [("pred", "shared", 8, levels.fingerprint(text[:8], address), [(0, address)]),
                ("res", "shared", 16, "x", [(0, address + 8)])]
        with patch.object(levels, "DUMP", root), patch.object(levels, "FUNCTION_DELAY_SLOTS", {"pred": 8}), \
                patch.object(levels, "FUNCTION_RESIDUES", {"res": 16}):
            return carry.correct_level_entries(rows), text

    def test_slot_returns_to_its_function_and_the_rest_is_residue(self):
        with tempfile.TemporaryDirectory() as d:
            out, text = self.fixture(Path(d), 0x03E00008)
        self.assertEqual(out, [("pred", "shared", 12, levels.fingerprint(text[:12], 0x2000), [(0, 0x2000)])])

    def test_slot_needs_a_return_before_it(self):
        with tempfile.TemporaryDirectory() as d, self.assertRaises(ValueError):
            self.fixture(Path(d), 0)


class AuditedIdentitySplit(unittest.TestCase):
    """Section 34: a fingerprint shared by two bodies is regrouped only by audited digests."""

    def fixture(self, root):
        import hashlib
        a = code(0x3C02001C, 0x8C430000, 0x24420060, 0xE44C00E4)
        b = code(0x3C02001C, 0x8C430000, 0x24420020, 0xE44C001C)
        texts = {0: a, 16: b + a}
        for number, text in texts.items():
            directory = root / levels.level_dir(number)
            directory.mkdir(parents=True)
            (directory / "manifest.json").write_text(json.dumps({"sections": [
                {"name": "text", "address": 0x1000, "size": len(text), "type": 1}]}))
            (directory / "text.bin").write_bytes(text)
        digest = lambda body: hashlib.sha256(body[8:]).hexdigest()[:16]
        spec = {("fp", 16): (8, (("func_A", digest(a)), ("func_B", digest(b))), ("func_old",))}
        # the historical grouping: the first copy of each level in one row, the second in another
        rows = [("func_A", "shared", 16, "fp", [(0, 0x1000), (16, 0x1000)]),
                ("func_old", "level", 16, "fp", [(16, 0x1010)]),
                ("other", "level", 8, "x", [(0, 0x2000)])]
        return rows, spec

    def test_mixed_rows_are_regrouped_by_body_and_replay(self):
        with tempfile.TemporaryDirectory() as d:
            rows, spec = self.fixture(Path(d))
            with patch.object(levels, "DUMP", Path(d)), patch.object(levels, "IDENTITY_SPLITS", spec):
                out = levels.split_identities(rows)
                self.assertEqual(levels.split_identities(out), out)
            self.assertEqual(out, [("func_A", "shared", 16, "fp", [(0, 0x1000), (16, 0x1010)]),
                                   ("func_B", "level", 16, "fp", [(16, 0x1000)]),
                                   ("other", "level", 8, "x", [(0, 0x2000)])])

    def test_unaudited_name_unknown_body_and_double_copies_fail(self):
        for change in ("name", "body", "double"):
            with self.subTest(change=change), tempfile.TemporaryDirectory() as d:
                rows, spec = self.fixture(Path(d))
                if change == "name":
                    rows[1] = ("func_new",) + rows[1][1:]
                elif change == "body":
                    (Path(d) / levels.level_dir(16) / "text.bin").write_bytes(code(0, 0, 0, 0) * 2)
                else:
                    text = Path(d) / levels.level_dir(16) / "text.bin"
                    text.write_bytes(text.read_bytes()[16:] * 2)
                with patch.object(levels, "DUMP", Path(d)), patch.object(levels, "IDENTITY_SPLITS", spec), \
                        self.assertRaises(ValueError):
                    levels.split_identities(rows)

    def test_real_split_names_the_two_setters(self):
        skip, parts, retired = levels.IDENTITY_SPLITS[("6b8116fb9abb08d4", 72)]
        self.assertEqual(skip, 8)
        self.assertEqual([n for n, _ in parts], ["func_L00_00424B70", "func_L00_00424BB8", "func_L16_0042FB10"])
        self.assertEqual(retired, ("func_L16_0042FB58",))


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

    def test_core_fill_and_menu_prefix_repairs_keep_colliding_canonical_names(self):
        # Authored methods: the two core fill repairs and menu entry repairs
        # must retain their names/ends even when the shortened menu code is
        # identical to a boot method and an already-corrected level method.
        def method(size, value):
            return code(addiu(2, 0, value)) + bytes(size - 12) + code(JR_RA, NOP)

        first = code(0xCDCDCDCD) + method(320, 7)
        second = code(0xCDCDCDCD) + method(1676, 11)
        prefix = code(addiu(29, 29, 32), NOP, addiu(29, 29, 32), NOP)
        short = method(272, 9)
        menu = prefix + short
        image = bytearray(0x3000)
        image[:len(first)] = first
        image[0x1000:0x1000 + len(second)] = second
        image[0x2000:0x2000 + len(menu)] = menu
        names = ("func_L02_0035BD60", "func_L07_0034AEC8", "func_L00_00354DF8")
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue, dump = root / "boot.tsv", root / "levels.tsv", root / "dump"
            boot.write_text("# name\taddress\tsize\n"
                            "func_0012646C\t00001000\t324\n"
                            "func_0012672C\t00002000\t1680\n"
                            "func_002DB988\t00003000\t288\n")
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n" +
                f"{names[0]}\tlevel\t288\told\t1\t00:00004000\n" +
                f"{names[1]}\tshared\t288\told\t2\t00:00004120,01:00006120\n" +
                f"{names[2]}\tshared\t272\told\t2\t00:00004240,01:00006240\n")
            for number, base in ((0, 0x4000), (1, 0x6000)):
                directory = dump / f"{number:02d}_test"
                directory.mkdir(parents=True)
                (directory / "manifest.json").write_text(json.dumps({"sections": [
                    {"name": "text", "address": base}]}))
                (directory / "text.bin").write_bytes(menu + menu + short)
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue,
                                LEVELS=root, BOOT_PAIRS=root / "absent.tsv", DUMP=dump,
                                NAMES={0: "test", 1: "test"}, BOOT_RESIDUES={}, FUNCTION_RESIDUES={}), \
                 patch.object(levels, "boot_image", return_value=(bytes(image), [(0x1000, 0, len(image))])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                self.assertEqual(levels.read_boot_functions(), [
                    ("func_0012646C", 0x1004, 320), ("func_0012672C", 0x2004, 1676),
                    ("func_002DB988", 0x3010, 272)])
                rows = {n: (kind, size, places) for n, kind, size, _, places in levels.read_catalogue()}
                self.assertEqual(rows, {
                    names[0]: ("level", 272, [(0, 0x4010)]),
                    names[1]: ("shared", 272, [(0, 0x4130), (1, 0x6130)]),
                    names[2]: ("shared", 272, [(0, 0x4240), (1, 0x6240)])})
                original = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(), catalogue.read_bytes()), original)

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

    def test_core_entry_and_named_residues_preserve_unrelated_rows_on_replay(self):
        # Synthetic core-only layout. A fill prefix and isolated words are
        # corrected only by their measured names, never by shared byte identity.
        method = code(addiu(4, 4, 12)) + bytes(444) + code(JR_RA, NOP)
        prefixed = code(0xCDCDCDCD) + method
        remnant = code(addiu(2, 0, 7))
        named = ("func_001158F4", "func_0011B320", "func_0011B450")
        base = 0x1158F4
        entries = [(named[0], base, 460), ("uncorrected", base+460, 460),
                   (named[1], 0x11B320, 4), (named[2], 0x11B450, 4), ("unrelated", 0x11B458, 4)]
        raw = bytearray(0x11B45C - base)
        for _, address, size in entries:
            raw[address-base:address-base+size] = prefixed if size == 460 else remnant
        raw = bytes(raw)
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            boot, catalogue = root / "boot.tsv", root / "levels.tsv"
            boot.write_text("# name\taddress\tsize\n" + "".join(
                f"{name}\t{address:08X}\t{size}\n" for name, address, size in entries))
            catalogue.write_text("# name\tkind\tsize\tfingerprint\tlevels\tplaces\n")
            with patch.multiple(levels, BOOT_FUNCTIONS=boot, CATALOGUE=catalogue, LEVELS=root,
                                BOOT_PAIRS=root / "absent.tsv", NAMES={}, BOOT_RESIDUES={},
                                FUNCTION_ENTRY_OFFSETS={named[0]:(460,4)},
                                FUNCTION_RESIDUES={named[1]:4,named[2]:4}), \
                 patch.object(levels, "boot_image", return_value=(raw, [(base,0,len(raw))])), \
                 patch.object(sys, "argv", ["levels.py", "catalogue"]):
                levels.catalogue()
                self.assertEqual(levels.read_boot_functions(),
                                 [(named[0],base+4,456), ("uncorrected",base+460,460),
                                  ("unrelated",0x11B458,4)])
                self.assertEqual(base+4 + 456, base + 460)
                first_output = boot.read_bytes(), catalogue.read_bytes()
                levels.catalogue()
                self.assertEqual((boot.read_bytes(),catalogue.read_bytes()),first_output)

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

    def release(self, functions, flags=(), where=None, source=None, not_carried=()):
        import progress
        with tempfile.TemporaryDirectory() as d:
            root = Path(d)
            path = root / "report.json"
            if not_carried:
                listed = root / levels.VERSIONS["pal"]["config"] / "not_carried.tsv"
                listed.parent.mkdir(parents=True)
                listed.write_text("# header\n" + "".join(f"{n}\tmeasured\n" for n in not_carried))
            path.write_text(json.dumps({"units":[{"functions":functions}]}))
            before = path.read_bytes()
            with patch.object(progress,"ROOT",root), \
                 patch.object(progress,"release_functions",return_value=where or {"kept":(0x1000,8,"boot",None)}), \
                 patch.object(progress,"source_functions",return_value=source or {}), \
                 patch.object(progress,"handwritten",return_value=set()), \
                 patch.object(levels,"FUNCTION_RESIDUES",{"retired":4}), \
                 patch.object(sys,"argv",["progress.py","--check",*flags]):
                progress.release_check("pal",path)
            self.assertEqual(path.read_bytes(),before)

    def test_unmatched_named_retirement_can_wait_for_a_report_refresh(self):
        self.release([{"name":"kept","fuzzy_match_percent":0.0},
                      {"name":"retired","fuzzy_match_percent":0.0}])

    def split_fixture(self, address=0x00131DF8):
        main, sound = "func_00131D98", "func_00131DE8"
        functions = [{"name":main, "size":"656", "fuzzy_match_percent":0.0,
                      "metadata":{"virtual_address":str(address)}}]
        where = {main:(address,80,"boot",None), sound:(address+80,576,"boot",None)}
        return functions, where

    def test_exact_unmatched_boot_split_can_wait_without_rewriting_reports(self):
        for address in (0x00131D98, 0x00131DF8):
            with self.subTest(address=address):
                functions, where = self.split_fixture(address)
                self.release(functions, where=where,
                             source={"src/core/main.c":[("func_00131D98", True)]})

    def test_strict_check_still_rejects_the_old_merged_row(self):
        functions, where = self.split_fixture()
        with self.assertRaises(SystemExit):
            self.release(functions, flags=("--strict",), where=where)

    def test_wrong_old_split_extent_address_or_credit_is_rejected(self):
        for change in ("size", "address", "missing metadata", "matched", "partial", "numeric address"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions, where = self.split_fixture()
                row = functions[0]
                if change == "size": row["size"] = "652"
                elif change == "address": row["metadata"]["virtual_address"] = str(0x00131DFC)
                elif change == "missing metadata": del row["metadata"]
                elif change == "matched": row["fuzzy_match_percent"] = 100.0
                elif change == "partial": row["fuzzy_match_percent"] = 25.0
                else: row["metadata"]["virtual_address"] = float(0x00131DF8) + 0.5
                self.release(functions, where=where,
                             source={"src/core/main.c":[("func_00131D98", True)]})

    def test_wrong_current_split_layout_or_kind_is_rejected(self):
        main, sound = "func_00131D98", "func_00131DE8"
        for change in ("main size", "tail size", "tail start", "main kind", "tail kind", "main level"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions, where = self.split_fixture()
                name = main if change.startswith("main") else sound
                row = list(where[name])
                if change.endswith("size"): row[1] -= 4
                elif change.endswith("start"): row[0] += 4
                elif change.endswith("kind"): row[2] = "shared"
                else: row[3] = 0
                where[name] = tuple(row)
                self.release(functions, where=where)

    def test_split_does_not_hide_other_missing_entries_or_duplicate_rows(self):
        for change in ("missing", "duplicate", "compensating duplicate", "unknown deletion"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions, where = self.split_fixture()
                if change == "missing": where["other"] = (0x2000,8,"boot",None)
                elif change == "unknown deletion": functions.append({"name":"unknown","fuzzy_match_percent":0.0})
                else:
                    functions.append(dict(functions[0]))
                    if change == "compensating duplicate":
                        where["other"] = (0x2000,8,"boot",None)
                self.release(functions, where=where)

    def test_identity_split_retires_its_matched_name_only_with_its_parts(self):
        spec = {("fp", 8): (0, (("kept", "a"), ("part", "b")), ("old",))}
        with patch.object(levels, "IDENTITY_SPLITS", spec):
            where = {"kept":(0x1000,8,"boot",None), "part":(0x2000,8,"boot",None)}
            self.release([{"name":"kept","fuzzy_match_percent":0.0},
                          {"name":"old","fuzzy_match_percent":100.0}], where=where)
            for extra in ({"other":(0x3000,8,"boot",None)}, {}):
                with self.subTest(extra=extra), self.assertRaises(SystemExit):
                    w = dict(where, **extra) if extra else {"kept":where["kept"]}
                    self.release([{"name":"kept","fuzzy_match_percent":0.0},
                                  {"name":"old","fuzzy_match_percent":100.0}] + ([] if extra else
                                 [{"name":"stray","fuzzy_match_percent":0.0}]), where=w)

    def test_split_tolerance_accepts_only_a_measured_unmatched_retired_row(self):
        functions, where = self.split_fixture()
        self.release(functions + [{"name":"retired", "fuzzy_match_percent":0.0}], where=where)
        for extra in ({"name":"retired", "fuzzy_match_percent":100.0}, {"name":"unknown", "fuzzy_match_percent":0.0}):
            with self.subTest(extra=extra), self.assertRaises(SystemExit):
                self.release(functions + [extra], where=where)
        with self.assertRaises(SystemExit):
            self.release(functions + [{"name":"retired", "fuzzy_match_percent":0.0}], where=where, flags=("--strict",))

    def test_demoted_rename_is_accepted_only_as_listed_unmatched_and_same_address(self):
        old = {"name":"func_0033A520", "fuzzy_match_percent":0.0,
               "metadata":{"virtual_address":str(0x0033C448)}}
        where = {"kept":(0x1000,8,"boot",None), "func_PAL_0033C448":(0x0033C448,360,"boot",None)}
        kept = {"name":"kept", "fuzzy_match_percent":0.0}
        self.release([kept, old], where=where, not_carried=["func_0033A520"])
        for change in ("unlisted", "matched", "address", "strict"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                f = copy.deepcopy(old)
                listed, flags = ["func_0033A520"], ()
                if change == "unlisted": listed = []
                elif change == "matched": f["fuzzy_match_percent"] = 100.0
                elif change == "address": f["metadata"]["virtual_address"] = "0"
                elif change == "strict": flags = ("--strict",)
                self.release([kept, f], where=where, not_carried=listed, flags=flags)

    def test_old_merged_main_with_a_reported_tail_is_rejected(self):
        functions, where = self.split_fixture()
        functions.append({"name":"func_00131DE8", "size":"576", "fuzzy_match_percent":0.0})
        with self.assertRaises(SystemExit):
            self.release(functions, where=where)

    def test_duplicate_missing_compensation_without_a_split_is_rejected(self):
        functions = [{"name":"kept", "fuzzy_match_percent":0.0}] * 2
        where = {"kept":(0x1000,8,"boot",None), "missing":(0x2000,8,"boot",None)}
        with self.assertRaises(SystemExit):
            self.release(functions, where=where)

    def test_refreshed_separate_rows_need_no_boundary_tolerance(self):
        functions, where = self.split_fixture()
        functions[0]["size"] = "80"
        functions.append({"name":"func_00131DE8", "size":"576", "fuzzy_match_percent":0.0})
        self.release(functions, flags=("--strict",), where=where)

    def assertion_fixture(self):
        first, second, address = "func_00115E28", "func_00115E38", 0x00115E28
        functions = [{"name": first, "size": "64", "fuzzy_match_percent": 0.0,
                      "metadata": {"virtual_address": str(address)}}]
        where = {first: (address, 16, "boot", None), second: (address + 16, 48, "boot", None)}
        return functions, where

    def test_unmatched_assertion_split_waits_without_mutating_the_report(self):
        functions, where = self.assertion_fixture()
        self.release(functions, where=where,
                     source={"src/core/abort.c": [(n, True) for n in where]})
        with self.assertRaises(SystemExit):
            self.release(functions, flags=("--strict",), where=where)

    def test_boot_and_level_splits_jointly_explain_only_their_own_gaps(self):
        functions, where = self.assertion_fixture()
        level_functions, level_where = self.level_split_fixture(["func_L00_0042A4E8"])
        functions += level_functions
        where.update(level_where)
        before = copy.deepcopy(functions)
        self.release(functions, where=where)
        self.assertEqual(functions, before)
        with self.assertRaises(SystemExit):
            self.release(functions, where=where, flags=("--strict",))
        where["unknown_gap"] = (0x300000, 8, "boot", None)
        with self.assertRaises(SystemExit):
            self.release(functions, where=where)

    def test_assertion_split_rejects_credit_drift_duplicates_and_unknown_gaps(self):
        for change in ("matched", "partial", "address", "size", "tail", "duplicate",
                       "unknown", "current size", "kind", "missing metadata"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions, where = self.assertion_fixture()
                if change == "matched": functions[0]["fuzzy_match_percent"] = 100.0
                elif change == "partial": functions[0]["fuzzy_match_percent"] = 25.0
                elif change == "address": functions[0]["metadata"]["virtual_address"] = "0"
                elif change == "size": functions[0]["size"] = "60"
                elif change == "tail":
                    functions.append({"name": "func_00115E38", "size": "48", "fuzzy_match_percent": 0.0})
                elif change == "duplicate": functions.append(dict(functions[0]))
                elif change == "unknown": where["other"] = (0x2000, 8, "boot", None)
                elif change == "current size": where["func_00115E38"] = (0x00115E38, 44, "boot", None)
                elif change == "kind": where["func_00115E38"] = (0x00115E38, 48, "shared", 0)
                else: del functions[0]["metadata"]
                self.release(functions, where=where,
                             source={"src/core/abort.c": [(n, True) for n in where]})

    def level_split_fixture(self, families=None):
        families = families or ["func_L13_0043E8C0"]
        functions, where = [], {}
        for index,name in enumerate(families):
            spec=levels.LEVEL_FUNCTION_SPLITS[name];address=0x200000+0x1000*index
            kind=spec[1];level=6 if kind=="shared" else 13
            functions.append({"name":name,"size":str(sum(n for _,n in spec[-1])),
                              "fuzzy_match_percent":0.0,"metadata":{"virtual_address":str(address)}})
            offset=0
            for child,length in spec[-1]:
                where[child]=(address+offset,length,kind,level)
                offset+=length
        return functions,where

    def test_witnessed_level_splits_can_wait_for_report_refresh(self):
        for families in ([name] for name in levels.LEVEL_FUNCTION_SPLITS):
            with self.subTest(families=families):
                functions,where=self.level_split_fixture(families)
                self.release(functions,where=where)
        functions,where=self.level_split_fixture(list(levels.LEVEL_FUNCTION_SPLITS))
        self.release(functions,where=where)

    def test_level_split_staleness_still_fails_strict_check(self):
        functions,where=self.level_split_fixture()
        with self.assertRaises(SystemExit): self.release(functions,where=where,flags=("--strict",))

    def test_level_split_rejects_old_credit_and_wrong_old_metadata(self):
        for change in ("matched","partial","size","address","metadata"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions,where=self.level_split_fixture();row=functions[0]
                if change=="matched": row["fuzzy_match_percent"]=100.0
                elif change=="partial": row["fuzzy_match_percent"]=50.0
                elif change=="size": row["size"]="20"
                elif change=="address": row["metadata"]["virtual_address"]="2097160"
                else: del row["metadata"]
                self.release(functions,where=where,source={"x.c":[(row["name"],True)]})

    def test_level_split_rejects_wrong_current_layout_and_partial_children(self):
        for change in ("size","address","kind","level","reported child","unknown missing","retired"):
            with self.subTest(change=change), self.assertRaises(SystemExit):
                functions,where=self.level_split_fixture()
                child="func_L13_0043E8C8";row=list(where[child])
                if change in ("size","address","kind","level"):
                    at={"address":0,"size":1,"kind":2,"level":3}[change]
                    row[at]={"address":row[0]+4,"size":12,"kind":"shared","level":14}[change]
                    where[child]=tuple(row)
                elif change=="reported child": functions.append({"name":child,"size":"8","fuzzy_match_percent":0.0})
                elif change=="unknown missing": where["other"]=(0x300000,8,"level",13)
                else: functions.append({"name":"unmeasured","fuzzy_match_percent":0.0})
                self.release(functions,where=where)

    def test_refreshed_level_split_rows_need_no_exception(self):
        _,where=self.level_split_fixture()
        functions=[{"name":name,"size":str(size),"fuzzy_match_percent":0.0,
                    "metadata":{"virtual_address":str(address)}}
                   for name,(address,size,_,_) in where.items()]
        self.release(functions,where=where,flags=("--strict",))

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
