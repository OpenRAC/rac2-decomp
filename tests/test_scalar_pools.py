"""Whole compiler constant-pool placement; synthetic inputs, no game data."""
from copy import deepcopy
from contextlib import ExitStack, redirect_stdout
from io import StringIO
from pathlib import Path
import struct
import sys
import tempfile
from types import SimpleNamespace
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parent.parent / "tools"))
import build


def words(*values):
    return struct.pack("<" + "I" * len(values), *values)


def object_with_pool(name="example", data=words(0x3F800000), alignment=4):
    text = words(0x3C020000, 0x24420000, 0x8C420000, 0x03E00008)
    return {
        "sections": [
            {"name": ".text." + name, "type": 1, "flags": 6, "align": 4,
             "size": len(text), "data": text},
            {"name": ".rodata", "type": 1, "flags": 2, "align": alignment,
             "size": len(data), "data": data}],
        "symbols": [{"name": "", "type": 3, "section": 1},
                    {"name": name, "type": 2, "section": 0, "size": len(text), "value": 0}],
        "relocations": {0: [(0, build.elf.R_MIPS_HI16, 0), (4, build.elf.R_MIPS_LO16, 0)]},
    }


def image_with_pool(data=words(0x3F800000), table_address=0x1000):
    image = {"data": bytearray(0x2000),
             "segments": [{"type": 1, "address": 0x1000, "offset": 0, "filesz": 0x2000}],
             "sections": [{"name": ".data", "type": 1, "flags": 3, "address": 0x1000, "size": 0x1000},
                          {"name": ".text", "type": 1, "flags": 6, "address": 0x2000, "size": 0x1000}]}
    image["data"][table_address - 0x1000:table_address - 0x1000 + len(data)] = data
    return image


class ScalarPoolValidation(unittest.TestCase):
    def setUp(self):
        self.obj = object_with_pool()
        self.image = image_with_pool()

    def accepts(self, address=0x1000):
        with patch.object(build, "program_functions", return_value={}):
            placement = build.Placement("boot", self.image)
        return placement.scalar_pool(self.obj, 1, address)

    def test_scalar_float_and_entire_256_byte_lookup_pool(self):
        self.assertTrue(self.accepts())
        data = bytes(range(256))
        self.obj = object_with_pool(data=data)
        self.image = image_with_pool(data)
        self.assertTrue(self.accepts())

    def test_byte_pool_does_not_require_word_size_or_alignment(self):
        self.obj = object_with_pool(data=b"\x01\x02\x03", alignment=1)
        self.image = image_with_pool(b"\x01\x02\x03", 0x1001)
        self.assertTrue(self.accepts(0x1001))

    def test_rdata_double_and_local_lookup_object_preserve_eight_byte_alignment(self):
        for data in (struct.pack("<d", 1.5), bytes(range(256))):
            with self.subTest(size=len(data)):
                self.obj = object_with_pool(data=data, alignment=8)
                self.obj["sections"][1]["name"] = ".rdata"
                self.obj["symbols"].append({"name": "constant", "type": 1, "section": 1,
                                            "value": 0, "size": len(data), "bind": 0})
                self.image = image_with_pool(data)
                self.assertTrue(self.accepts())
                self.image = image_with_pool(data, 0x1004)
                self.assertFalse(self.accepts(0x1004))

    def test_every_byte_including_padding_must_match(self):
        self.obj = object_with_pool(data=words(0x3F800000, 0))
        self.image = image_with_pool(words(0x3F800000, 1))
        self.assertFalse(self.accepts())

    def test_value_elsewhere_does_not_authorize_another_address(self):
        self.assertFalse(self.accepts(0x1004))

    def test_alignment_type_flags_name_and_size_are_checked(self):
        original = deepcopy(self.obj)
        for field, value in (("align", 0), ("align", 3), ("align", 0x2000),
                             ("flags", 0), ("flags", 3), ("flags", 6), ("type", 8),
                             ("name", ".sdata"), ("size", 0), ("size", 8)):
            with self.subTest(field=field, value=value):
                self.obj = deepcopy(original)
                self.obj["sections"][1][field] = value
                self.assertFalse(self.accepts())
        self.obj = original
        self.assertFalse(self.accepts(0x1001))

    def test_relocations_and_mixed_tables_remain_unsupported(self):
        for reloc in ((0, build.elf.R_MIPS_32, 0), (0, build.elf.R_MIPS_HI16, 0)):
            with self.subTest(reloc=reloc):
                self.obj["relocations"][1] = [reloc]
                self.assertFalse(self.accepts())

    def test_text_symbol_cannot_hide_inside_a_pool(self):
        self.obj["symbols"].append({"name": "hidden", "type": 2, "section": 1})
        self.assertFalse(self.accepts())

    def test_missing_truncated_or_ambiguous_initialized_owner(self):
        original = deepcopy(self.image)
        variants = [[], [deepcopy(self.image["sections"][0])] * 2]
        for sections in variants:
            with self.subTest(sections=sections):
                self.image = deepcopy(original)
                self.image["sections"] = sections
                self.assertFalse(self.accepts())
        self.image = original
        self.image["sections"][0]["size"] = 3
        self.assertFalse(self.accepts())

    def test_executable_nobits_and_unloaded_data_are_rejected(self):
        original = deepcopy(self.image)
        for field, value in (("flags", 6), ("type", 8), ("name", "core.text")):
            with self.subTest(field=field, value=value):
                self.image = deepcopy(original)
                self.image["sections"][0][field] = value
                self.assertFalse(self.accepts())
        self.image = deepcopy(original)
        self.image["segments"][0]["filesz"] = 3
        self.assertFalse(self.accepts())
        self.image = deepcopy(original)
        self.image["segments"] *= 2
        self.assertFalse(self.accepts())

    def test_unknown_or_unallocated_retail_flags_fail_closed(self):
        owner = self.image["sections"][0]
        for flags in (0, 1):
            owner["flags"] = flags
            self.assertFalse(self.accepts())
        del owner["flags"]
        self.assertFalse(self.accepts())

    def test_real_elf_parser_preserves_flags_for_nonstandard_executable_sections(self):
        import tempfile
        with tempfile.TemporaryDirectory() as directory:
            path = Path(directory) / "authored.elf"
            build.elf.write_exec(path, 0x2000, [
                {"name": ".vutext", "type": 1, "address": 0x1000, "data": words(0x3F800000)},
                {"name": ".text", "type": 1, "address": 0x2000, "data": words(0x03E00008)}])
            data = bytearray(path.read_bytes())
            shoff = struct.unpack_from("<I", data, 0x20)[0]
            struct.pack_into("<I", data, shoff + 40 + 8, 6)  # SHF_ALLOC | SHF_EXECINSTR
            path.write_bytes(data)
            self.image = build.elf.read(path)
            self.assertEqual(self.image["sections"][1]["flags"], 6)
            self.assertFalse(self.accepts())
            struct.pack_into("<I", data, shoff + 40 + 8, 2)  # same bytes, allocated data
            path.write_bytes(data)
            self.image = build.elf.read(path)
            self.assertTrue(self.accepts())


class ScalarPoolDependencies(unittest.TestCase):
    def place(self, objects, references, extra_data=None):
        image = image_with_pool()
        for address, data in (extra_data or {}).items():
            image["data"][address - 0x1000:address - 0x1000 + len(data)] = data
        functions, paths = {}, [Path(f"input{i}.o") for i in range(len(objects))]
        for i, obj in enumerate(objects):
            for symbol in obj["symbols"]:
                if symbol["type"] != 2:
                    continue
                name, section = symbol["name"], obj["sections"][symbol["section"]]
                address, pool = references[name]
                functions[name] = [(address, section["size"])]
                code = words(0x3C020000 | ((pool + 0x8000) >> 16),
                             0x24420000 | (pool & 0xFFFF), 0x8C420000, 0x03E00008)
                image["data"][address - 0x1000:address - 0x1000 + len(code)] = code
        with patch.object(build, "program_functions", return_value=functions), \
             patch.object(build, "sources_for", return_value=paths), \
             patch.object(build, "compile_c", side_effect=lambda p: p), \
             patch.object(build.elf, "read_object", side_effect=objects):
            placement = build.Placement("boot", image)
            placement.place()
        return placement

    def test_text_relocations_independently_derive_pool_address(self):
        obj = object_with_pool()
        original = deepcopy(obj)
        result = self.place([obj], {"example": (0x2000, 0x1000)})
        self.assertEqual(set(result.placed), {"example"})
        self.assertEqual(result.tables, {(Path("input0.o"), ".rodata"): (0x1000, 4)})
        self.assertEqual(result.scalar_pools, {(Path("input0.o"), ".rodata")})
        self.assertEqual(result.differ, [])
        self.assertEqual(obj, original, "placing a section must not change instructions or values")

    def test_rejected_pool_cannot_borrow_another_objects_section(self):
        bad = object_with_pool("first", words(0xDEADBEEF))
        good = object_with_pool("second")
        result = self.place([bad, good], {"first": (0x2000, 0x1000), "second": (0x2100, 0x1000)})
        self.assertEqual(set(result.placed), {"second"})
        self.assertEqual(set(result.tables), {(Path("input1.o"), ".rodata")})

    def test_conflicting_pool_owners_are_both_rejected(self):
        result = self.place([object_with_pool("first"), object_with_pool("second")],
                            {"first": (0x2000, 0x1000), "second": (0x2100, 0x1000)})
        self.assertEqual(result.placed, {})
        self.assertEqual(result.tables, {})

    def test_conflicting_bindings_to_one_input_section_are_both_rejected(self):
        obj = object_with_pool("first")
        second = deepcopy(obj["sections"][0])
        second["name"] = ".text.second"
        obj["sections"].append(second)
        obj["symbols"].append({"name": "second", "type": 2, "section": 2, "size": 16, "value": 0})
        obj["relocations"][2] = deepcopy(obj["relocations"][0])
        result = self.place([obj], {"first": (0x2000, 0x1000), "second": (0x2100, 0x1004)},
                            extra_data={0x1004: words(0x3F800000)})
        self.assertEqual(result.placed, {})
        self.assertEqual(result.tables, {})


def record(address, directive, fields):
    return f"/* 000000 {address:08X} */ .{directive} {fields}\n"


class ScalarPoolSplitting(unittest.TestCase):
    def split(self, text, address=0x1000, size=4):
        return build.split_table_data(text, {address: (size, "object(.rodata)")}, scalar=True)

    def test_byte_pool_with_internal_label_and_surrounding_strings(self):
        before = '.section .data\nmessage:\n/* 000000 00000FF8 */ .asciz "before"\n.align 2\n'
        after = 'next:\n/* 000000 00001100 */ .asciz "after"\n'
        data = 'lookup:\n'
        for at in range(0, 256, 16):
            if at == 128:
                data += "midpoint:\n"
            data += record(0x1000 + at, "byte", ", ".join(str(n) for n in range(at, at + 16)))
        pieces, labels = self.split(before + data + after, size=256)
        self.assertEqual(pieces, [("asm", before), ("c", "object(.rodata)"), ("asm", after)])
        self.assertEqual(labels, {"lookup": "0x1000", "midpoint": "0x1080"})

    def test_byte_halfword_and_word_records_cover_exact_span(self):
        text = record(0x1001, "byte", "1") + record(0x1002, "short", "0x0203")
        text += record(0x1004, "word", "0x04050607")
        self.assertEqual(self.split(text, 0x1001, 7), ([("c", "object(.rodata)")], {}))

    def test_proved_string_padding_and_numeric_records_preserve_names_and_surroundings(self):
        before = '.section .data\n' + record(0xFFC, "word", "9")
        first = record(0x1000, "asciz", '"item%d"') + "/* 6974656D25640000 */\n.align 2\n"
        empty = record(0x1008, "asciz", '""') + "/* 00000000 */\n.align 2\n.align 2\n"
        data = "formats:\n" + first + "empty:\n" + empty + record(0x100C, "word", "7")
        after = "next:\n" + record(0x1010, "word", "8")
        pieces, labels = self.split(before + data + after, size=16)
        self.assertEqual(pieces, [("asm", before), ("c", "object(.rodata)"), ("asm", after)])
        self.assertEqual(labels, {"formats": "0x1000", "empty": "0x1008"})

    def test_adjacent_scalar_pools_accept_proved_c_escapes(self):
        first = record(0x1000, "word", "1")
        second = record(0x1004, "asciz", r'"A\n\101"') + "/* 410A4100 */\n"
        pieces, labels = build.split_table_data(
            "number:\n" + first + "message:\n" + second,
            {0x1000: (4, "number(.rodata)"), 0x1004: (4, "message(.rodata)")}, scalar=True)
        self.assertEqual(pieces, [("c", "number(.rodata)"), ("c", "message(.rodata)")])
        self.assertEqual(labels, {"number": "0x1000", "message": "0x1004"})

    def test_string_bytes_padding_and_boundaries_must_be_proved(self):
        cases = [
            record(0x1000, "asciz", '"abc"') + "/* 61626400 */\n",
            record(0x1000, "asciz", '"x"') + "/* 78000100 */\n.align 2\n",
            record(0x1000, "asciz", '"x"') + "/* 78000000 */\n",
            record(0x1000, "asciz", '"abc"') + "/* 6162630000000000 */\n.align 2\n.align 2\n",
            record(0x1000, "asciz", '"x"') + "/* 78000000 */\nlabel_before_padding:\n.align 2\n",
            record(0x1000, "asciz", '"x"') + "/* 78000000 */\n.align 0\n",
            record(0x1000, "asciz", '"abcd"') + "/* 6162636400000000 */\n.align 2\n",
            record(0x1000, "asciz", '"abc"') + "/* 6162630 */\n",
            record(0x1000, "asciz", r'"\x41bc"') + "/* 41626300 */\n",
            record(0x1000, "asciz", '"abc"; .byte 0') + "/* 61626300 */\n",
        ]
        for text in cases:
            with self.subTest(text=text), self.assertRaises(SystemExit):
                self.split(text)

    def test_proved_strings_do_not_relax_branch_table_records(self):
        text = record(0x1000, "asciz", '"abc"') + "/* 61626300 */\n"
        with self.assertRaises(SystemExit):
            build.split_table_data(text, {0x1000: (4, "object(.rodata)")})

    def test_gaps_partial_records_and_missing_spans_fail(self):
        for text in (record(0x1000, "byte", "0"), record(0x1001, "word", "0"),
                     record(0x1000, "byte", "0") + record(0x1002, "byte", "0, 0"),
                     record(0x1000, "word", "0, 0")):
            with self.subTest(text=text), self.assertRaises(SystemExit):
                self.split(text)

    def test_unsupported_strings_symbols_or_directives_inside_pool_fail(self):
        for text in (record(0x1000, "asciz", '"abc"'), record(0x1000, "word", "external"),
                     record(0x1000, "byte", "0; .byte 0, 0, 0"),
                     record(0x1000, "short", "0") + ".align 2\n" + record(0x1002, "short", "0")):
            with self.subTest(text=text), self.assertRaises(SystemExit):
                self.split(text)


class InterleavedCompilerData(unittest.TestCase):
    def test_scalar_and_branch_sections_share_retail_input_without_losing_surroundings(self):
        with tempfile.TemporaryDirectory() as directory, ExitStack() as stack:
            root = Path(directory)
            scalar_object, branch_object = root / "scalar.o", root / "branch.o"
            placement = SimpleNamespace(
                functions={}, values={}, placed={"example": (0x2000, 4, scalar_object, ".text.example")},
                differ=[], objects=[scalar_object, branch_object], place=lambda: None,
                tables={(scalar_object, ".rodata"): (0x1000, 4),
                        (branch_object, ".rodata"): (0x1008, 4)},
                scalar_pools={(scalar_object, ".rodata")})

            def configure(reference, out, name):
                (out / "config").mkdir(parents=True)
                (out / "asm_pp").mkdir()
                text = '.section .data\npool:\n' + record(0x1000, "byte", "1, 2, 3, 4")
                text += record(0x1004, "word", "9")
                text += 'branch_table:\n/* 000008 00001008 00000000 */ .word target\n'
                text += record(0x100C, "word", "7")
                (out / "asm_pp/data.s").write_text(text)
                (out / "config/rac2.ld").write_text(
                    "SECTIONS { .data : { build/asm/data.s.o(.data); } }")
                return {}

            stack.enter_context(patch.object(build, "BUILD", root))
            stack.enter_context(patch.object(build, "splat_config", side_effect=configure))
            stack.enter_context(patch.object(build, "Placement", return_value=placement))
            stack.enter_context(patch.object(build.elf, "read", return_value={"entry": 0}))
            stack.enter_context(patch.object(build.elf, "compare_loads", return_value=(True, "synthetic")))
            aliases = stack.enter_context(patch.object(build, "undefined_symbols"))
            for name in ("run", "adapt_linker"):
                stack.enter_context(patch.object(build, name))
            stack.enter_context(redirect_stdout(StringIO()))
            self.assertEqual(build.build_program("boot", root / "reference", strict=True), (1, 4))
            script = (root / "boot/config/rac2.ld").read_text()
            self.assertEqual(script.count("../scalar.o(.rodata);"), 1)
            self.assertEqual(script.count("../branch.o(.rodata);"), 1)
            self.assertLess(script.index("../scalar.o(.rodata);"), script.index("../branch.o(.rodata);"))
            final_sources = "".join(Path(call.args[0][-1]).read_text()
                                    for call in build.run.call_args_list if "Ps2EeAs.exe" in call.args[0][0])
            self.assertIn(".word 9", final_sources)
            self.assertIn(".word 7", final_sources)
            self.assertNotIn(".byte 1, 2, 3, 4", final_sources)
            self.assertNotIn(".word target", final_sources)
            self.assertEqual(aliases.call_args.args[2]["pool"], "0x1000")
            self.assertEqual(aliases.call_args.args[2]["branch_table"], "0x1008")


if __name__ == "__main__":
    unittest.main()
