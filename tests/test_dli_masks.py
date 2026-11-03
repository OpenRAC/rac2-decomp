"""Authored, asset-free R5900 dli regression cases.

Ordinary CI validates fixture semantics and skips assembler execution if absent.
Compiler qualification must run with RAC2_COMPILER_ROOT set to the new tools;
an explicit missing assembler is an error, never a skip.

The isolated sign-bit form is independently documented by the public RAC1
assembler model (GPL-3.0), commit 813090403fe822acd929616da0fee2081131f92e:
https://github.com/OpenRAC/rac1-decomp/blob/813090403fe822acd929616da0fee2081131f92e/tools/ps2eeas_dli.py
The shifted-mask interval matrix and fixed constant cases are authored
independently; no game bytes, SDK sources, or assembler-output rewriting are used.

The positive 32-bit mask profile follows the same public RAC1 model, checked at
1d8228cc0c81da7bc2bdc3e77479ee050e0ef434, and an independent authored SN control:
addiu -1; dsrl32 0. The default GNU seed and every other constant stay unchanged.
"""
import json
import os
from pathlib import Path
import struct
import subprocess
import sys
import tempfile
import unittest

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import elf

STATIC_CASES = json.loads((ROOT / "tests/fixtures/dli_masks.json").read_text())
REGISTERS = (2, 3, 8, 16, 31)
ASSEMBLER_REGISTERS = (0, *REGISTERS)
MASK64 = (1 << 64) - 1
PROFILE_OPTIONS = {
    "default": [],
    "signed": ["--r5900-sign-bit=signed"],
    "unsigned": ["--r5900-sign-bit=unsigned"],
    "mask_gnu": ["--r5900-unsigned32-mask=gnu"],
    "mask_sn": ["--r5900-unsigned32-mask=sn"],
    "mask_sn_unsigned": ["--r5900-unsigned32-mask=sn", "--r5900-sign-bit=unsigned"],
}


def shifted_family_cases():
    """All positive contiguous runs wider than 32 bits, shifted off bit zero.

    This enumerates the mathematical interval specification independently of
    gas's low-bit predicate. Both ends have zeros, so both shifts fit 1..31.
    """
    cases = []
    for width in range(33, 63):
        for low in range(1, 64 - width):
            value = ((1 << width) - 1) << low
            left, right = 64 - width, 64 - width - low
            cases.append({"name": f"shifted_family_w{width}_s{low}",
                          "literal": f"0x{value:016x}", "value": f"{value:016x}",
                          "words_r2": ["2402ffff", f"{0x21000 | left << 6 | 0x38:08x}",
                                       f"{0x21000 | right << 6 | 0x3a:08x}"],
                          "changed_by_fix": True})
    return cases


SHIFTED_CASES = shifted_family_cases()
CASES = STATIC_CASES + SHIFTED_CASES


def retarget(words, reg):
    """Retarget the authored $2 golden sequence using instruction register fields."""
    out = []
    for encoded in words:
        word = int(encoded, 16)
        opcode = word >> 26
        if opcode in (9, 13, 15):
            rs, rt = (word >> 21) & 31, (word >> 16) & 31
            if rt != 2 or rs not in (0, 2):
                raise ValueError("unexpected immediate register in fixture")
            word &= ~((31 << 21) | (31 << 16))
            word |= (reg if rs == 2 else 0) << 21 | reg << 16
        elif opcode == 0 and (word & 63) in (0x38, 0x3A, 0x3C, 0x3E):
            if (word >> 16) & 31 != 2 or (word >> 11) & 31 != 2:
                raise ValueError("unexpected shift register in fixture")
            word = (word & ~((31 << 16) | (31 << 11))) | reg << 16 | reg << 11
        else:
            raise ValueError(f"unsupported fixture opcode: {word:08x}")
        out.append(word)
    return out


def execute_constant(words, result_register):
    """Execute the six scalar operations used by these authored dli sequences."""
    registers = [0] * 32
    for word in words:
        opcode, rs, rt = word >> 26, (word >> 21) & 31, (word >> 16) & 31
        rd, shift, function = (word >> 11) & 31, (word >> 6) & 31, word & 63
        immediate = word & 0xFFFF
        if opcode == 15:  # lui sign-extends its 32-bit result to 64 bits.
            value = immediate << 16
            registers[rt] = value - (1 << 32) if value & (1 << 31) else value
        elif opcode == 13:
            registers[rt] = registers[rs] | immediate
        elif opcode == 9:
            signed = immediate - 0x10000 if immediate & 0x8000 else immediate
            value = (registers[rs] + signed) & 0xFFFFFFFF
            registers[rt] = value - (1 << 32) if value & (1 << 31) else value
        elif opcode == 0 and function in (0x38, 0x3C):
            registers[rd] = registers[rt] << (shift + (32 if function == 0x3C else 0))
        elif opcode == 0 and function in (0x3A, 0x3E):
            registers[rd] = registers[rt] >> (shift + (32 if function == 0x3E else 0))
        else:
            raise ValueError(f"unsupported instruction: {word:08x}")
        registers = [value & MASK64 for value in registers]
        registers[0] = 0
    return registers[result_register]


class FixtureTests(unittest.TestCase):
    def test_baseline_and_expected_sequences_preserve_64_bit_values(self):
        for case in STATIC_CASES:
            for reg in REGISTERS:
                for field in ("baseline_words_r2", "words_r2"):
                    with self.subTest(case=case["name"], reg=reg, version=field):
                        self.assertEqual(execute_constant(retarget(case[field], reg), reg),
                                         int(case["value"], 16))

    def test_controls_and_positive_boundaries_are_present(self):
        cases = {case["name"]: case for case in STATIC_CASES}
        for name in ("zero", "minus_one", "low_run_31", "low_run_63",
                     "pack_neighbor_minus_one", "pack_neighbor_plus_one",
                     "pack_hole_bit30", "long_max",
                     "gs_control", "sparse_control", "signed32_control", "unsigned32_control",
                     "width31_shift2", "width32_shift1", "width32_shift16",
                     "width16_shift17", "existing_width20_shift36", "internal_hole",
                     "target_minus1", "target_plus1", "unshifted_width33",
                     "touch_sign_width59", "touch_sign_width33",
                     "leading_ones_pure_shift_unchanged", "unsigned32_mask",
                     "unsigned32_mask_decimal", "unsigned32_mask_zero_padded",
                     "unsigned32_mask_lower_neighbor", "unsigned32_mask_upper_neighbor",
                     "positive_low_mask31"):
            with self.subTest(control=name):
                self.assertFalse(cases[name]["changed_by_fix"])
                self.assertEqual(cases[name]["words_r2"], cases[name]["baseline_words_r2"])
        expected_lengths = {"sign_bit": 2, "sign_bit_signed": 2, "low_run_32": 5,
                            "pack_d_mask": 6, "low_run_62": 6, "shifted_long_ones": 3}
        for name, length in expected_lengths.items():
            self.assertTrue(cases[name]["changed_by_fix"])
            self.assertEqual(len(cases[name]["words_r2"]), length)
        self.assertEqual(cases["sign_bit"]["words_r2"], ["2402ffff", "000217fc"])
        self.assertEqual(cases["sign_bit"]["words_r2"], cases["sign_bit_signed"]["words_r2"])
        # Retail lockB mask (func_0030A348 and its level copies): sign-extending lui first.
        self.assertTrue(cases["leading_ones_top16_lui"]["changed_by_fix"])
        self.assertEqual(cases["leading_ones_top16_lui"]["words_r2"],
                         ["3c028000", "00021078", "3442ffff", "00021438"])


    def test_exhaustive_shifted_family_specification(self):
        self.assertEqual(len(SHIFTED_CASES), 465)
        self.assertEqual(len({case["value"] for case in SHIFTED_CASES}), 465)
        for case in SHIFTED_CASES:
            value = int(case["value"], 16)
            self.assertGreater(value, 0)
            self.assertLess(value, 1 << 63)
            self.assertEqual(value & 1, 0)
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    self.assertEqual(execute_constant(retarget(case["words_r2"], reg), reg), value)


class AssemblerOutputTests(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        compiler = Path(os.environ.get("RAC2_COMPILER_ROOT", ROOT / "build/compiler/tools")).resolve()
        assembler = compiler / "as"
        if not assembler.is_file():
            if "RAC2_COMPILER_ROOT" in os.environ:
                raise RuntimeError("RAC2_COMPILER_ROOT must contain the newly built as")
            raise unittest.SkipTest("EE assembler absent; compiler build must run with RAC2_COMPILER_ROOT")
        cls.assembler = assembler
        cls.profiles = {name: {} for name in PROFILE_OPTIONS}
        with tempfile.TemporaryDirectory() as directory:
            temporary = Path(directory)
            lines = [".text", ".set noreorder", ".set noat"]
            for case in CASES:
                for reg in ASSEMBLER_REGISTERS:
                    symbol = f'dli_{case["name"]}_r{reg}'
                    lines += [f".globl {symbol}", f".type {symbol},@function", f"{symbol}:",
                              f'dli ${reg},{case["literal"]}', f".size {symbol},.-{symbol}"]
            for mnemonic in ("li", "la"):
                for reg in REGISTERS:
                    symbol = f"control_{mnemonic}_r{reg}"
                    lines += [f".globl {symbol}", f".type {symbol},@function", f"{symbol}:",
                              f"{mnemonic} ${reg},0xffffffff", f".size {symbol},.-{symbol}"]
            source, output = temporary / "authored.s", temporary / "authored.o"
            source.write_text("\n".join(lines) + "\n")
            for profile, bodies in cls.profiles.items():
                options = PROFILE_OPTIONS[profile]
                result = subprocess.run([str(assembler), *options, "-o", str(output), str(source)],
                                        capture_output=True, text=True)
                if result.returncode:
                    raise RuntimeError(f"authored dli assembly failed ({profile}): {result.stderr}")
                obj = elf.read_object(output)
                symbols = {symbol["name"]: symbol for symbol in obj["symbols"]}
                for case in CASES:
                    for reg in ASSEMBLER_REGISTERS:
                        name = f'dli_{case["name"]}_r{reg}'
                        symbol = symbols[name]
                        data = obj["sections"][symbol["section"]]["data"]
                        bodies[case["name"], reg] = data[symbol["value"]:symbol["value"] + symbol["size"]]
                for mnemonic in ("li", "la"):
                    for reg in REGISTERS:
                        symbol = symbols[f"control_{mnemonic}_r{reg}"]
                        data = obj["sections"][symbol["section"]]["data"]
                        bodies[mnemonic, reg] = data[symbol["value"]:symbol["value"] + symbol["size"]]
        cls.outputs = cls.profiles["default"]

    def test_explicit_signed_profile_preserves_every_default_output(self):
        self.assertEqual(self.profiles["signed"], self.outputs)

    def test_explicit_gnu_mask_profile_preserves_every_default_output(self):
        self.assertEqual(self.profiles["mask_gnu"], self.outputs)

    def test_sn_mask_profile_changes_only_positive_unsigned32_mask(self):
        for case in CASES:
            value = int(case["value"], 16)
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    expected = self.outputs[case["name"], reg]
                    if value == 0xffffffff:
                        expected = b"".join(struct.pack("<I", word) for word in
                                            retarget(["2402ffff", "0002103e"], reg))
                    body = self.profiles["mask_sn"][case["name"], reg]
                    self.assertEqual(body, expected)
                    self.assertEqual(execute_constant(
                        [word[0] for word in struct.iter_unpack("<I", body)], reg), value)

    def test_unsigned_sign_bit_and_sn_mask_profiles_compose(self):
        for case in CASES:
            reference = "mask_sn" if int(case["value"], 16) == 0xffffffff else "unsigned"
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    self.assertEqual(self.profiles["mask_sn_unsigned"][case["name"], reg],
                                     self.profiles[reference][case["name"], reg])

    def test_zero_destination_does_not_broaden_the_mask_selector(self):
        # The loader also uses the register number as a temporary sentinel.
        # A zero destination must not confuse a nonzero high word with zero.
        for case in CASES:
            with self.subTest(case=case["name"]):
                expected = self.outputs[case["name"], 0]
                if int(case["value"], 16) == 0xffffffff:
                    expected = b"".join(struct.pack("<I", word) for word in
                                        retarget(["2402ffff", "0002103e"], 0))
                body = self.profiles["mask_sn"][case["name"], 0]
                self.assertEqual(body, expected)
                self.assertEqual(execute_constant(
                    [word[0] for word in struct.iter_unpack("<I", body)], 0), 0)

    def test_word_and_address_macros_keep_their_original_bytes(self):
        for mnemonic in ("li", "la"):
            for reg in REGISTERS:
                for profile in PROFILE_OPTIONS:
                    with self.subTest(mnemonic=mnemonic, reg=reg, profile=profile):
                        self.assertEqual(self.profiles[profile][mnemonic, reg],
                                         self.outputs[mnemonic, reg])

    def test_unsigned_profile_changes_only_the_isolated_sign_bit(self):
        for case in CASES:
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    body = self.profiles["unsigned"][case["name"], reg]
                    expected = self.outputs[case["name"], reg]
                    if int(case["value"], 16) == 1 << 63:
                        expected = b"".join(struct.pack("<I", word)
                                            for word in retarget(["34028000", "0002143c"], reg))
                    self.assertEqual(body, expected)
                    words = [item[0] for item in struct.iter_unpack("<I", body)]
                    self.assertEqual(execute_constant(words, reg), int(case["value"], 16))

    def test_bad_or_missing_sign_bit_profile_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            source, output = Path(directory) / "control.s", Path(directory) / "control.o"
            source.write_text(".text\nnop\n")
            for option in ("--r5900-sign-bit=typo", "--r5900-sign-bit=", "--r5900-sign-bit"):
                with self.subTest(option=option):
                    result = subprocess.run([str(self.assembler), "-o", str(output),
                                             str(source), option], capture_output=True, text=True)
                    self.assertNotEqual(result.returncode, 0)

    def test_bad_or_missing_unsigned32_mask_profile_is_rejected(self):
        with tempfile.TemporaryDirectory() as directory:
            source, output = Path(directory) / "control.s", Path(directory) / "control.o"
            source.write_text(".text\nnop\n")
            for option in ("--r5900-unsigned32-mask=typo", "--r5900-unsigned32-mask=",
                           "--r5900-unsigned32-mask"):
                with self.subTest(option=option):
                    result = subprocess.run([str(self.assembler), "-o", str(output),
                                             str(source), option], capture_output=True, text=True)
                    self.assertNotEqual(result.returncode, 0)

    def test_forms_encodings_and_sizes_in_five_registers(self):
        for case in STATIC_CASES:
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    expected = b"".join(struct.pack("<I", word) for word in retarget(case["words_r2"], reg))
                    self.assertEqual(self.outputs[case["name"], reg], expected)

    def test_assembled_sequences_have_the_required_64_bit_semantics(self):
        for case in CASES:
            for reg in REGISTERS:
                with self.subTest(case=case["name"], reg=reg):
                    body = self.outputs[case["name"], reg]
                    words = [item[0] for item in struct.iter_unpack("<I", body)]
                    self.assertEqual(execute_constant(words, reg), int(case["value"], 16))

    def test_unaffected_controls_keep_baseline_bytes(self):
        for case in CASES:
            if not case["changed_by_fix"]:
                for reg in REGISTERS:
                    with self.subTest(control=case["name"], reg=reg):
                        baseline = b"".join(struct.pack("<I", word)
                                            for word in retarget(case["baseline_words_r2"], reg))
                        self.assertEqual(self.outputs[case["name"], reg], baseline)

    def test_every_shifted_run_uses_the_three_instruction_form(self):
        failures = []
        for case in SHIFTED_CASES:
            for reg in REGISTERS:
                expected = b"".join(struct.pack("<I", word)
                                    for word in retarget(case["words_r2"], reg))
                actual = self.outputs[case["name"], reg]
                if actual != expected:
                    failures.append((case["name"], reg, actual.hex(), expected.hex()))
        self.assertFalse(failures,
                         f"{len(failures)} shifted cases differ; first ten: {failures[:10]}")


if __name__ == "__main__":
    unittest.main()
