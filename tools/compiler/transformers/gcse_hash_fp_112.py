#!/usr/bin/env python3
"""Add the opt-in -frac2-gcse-hash-fp-112: the frame pointer hashes 112 buckets further on in gcse.

A sibling of -frac2-gcse-hash-fp-117: as if frame addresses were based on register 113. It
changes PRE's bucket walk, so the reaching registers' creation and spill-slot order. In
func_L20_0039BEC8 offsets 111..113 give retail's slot order at sp+0x148..0x168.

Forced on for every USA v1.01 C unit it changes 102 functions: an opt-in per-unit model under the
owner's standard of 12 November 2026. Default compilation is unchanged.

Usage: gcse_hash_fp_112.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {'gcse.c': [('\t   creates its reaching registers (and so their spill slots).  */\n\tif (flag_rac2_gcse_hash_fp_117 && regno == FRAME_POINTER_REGNUM)\n\t  hash += 117;\n\treturn hash;\n      }\n', '\t   creates its reaching registers (and so their spill slots).  */\n\tif (flag_rac2_gcse_hash_fp_117 && regno == FRAME_POINTER_REGNUM)\n\t  hash += 117;\n\t/* RAC2: -frac2-gcse-hash-fp-112, the same with 112 buckets, as if\n\t   frame addresses were based on register 113.  */\n\tif (flag_rac2_gcse_hash_fp_112 && regno == FRAME_POINTER_REGNUM)\n\t  hash += 112;\n\treturn hash;\n      }\n')], 'toplev.c': [('/* RAC2: opt-in, GCSE hashes the frame pointer 117 buckets further on.  */\nint flag_rac2_gcse_hash_fp_117 = 0;\n\n/* RAC2: opt-in, paired giv initial values share base + product.  */\nint flag_rac2_giv_pair_init = 0;\n', '/* RAC2: opt-in, GCSE hashes the frame pointer 117 buckets further on.  */\nint flag_rac2_gcse_hash_fp_117 = 0;\n\n/* RAC2: opt-in, GCSE hashes the frame pointer 112 buckets further on.  */\nint flag_rac2_gcse_hash_fp_112 = 0;\n\n/* RAC2: opt-in, paired giv initial values share base + product.  */\nint flag_rac2_giv_pair_init = 0;\n'), ('   "Prefer lower displacement for tied memory stores to same base"},\n  {"rac2-gcse-hash-111", &flag_rac2_gcse_hash_111, 1,\n   "Force GCSE expression hash table to 111 buckets"},\n  {"rac2-gcse-hash-fp-117", &flag_rac2_gcse_hash_fp_117, 1,\n   "Add 117 to the GCSE expression hash of the frame pointer"},\n  {"rac2-giv-pair-init", &flag_rac2_giv_pair_init, 1,\n', '   "Prefer lower displacement for tied memory stores to same base"},\n  {"rac2-gcse-hash-111", &flag_rac2_gcse_hash_111, 1,\n   "Force GCSE expression hash table to 111 buckets"},\n  {"rac2-gcse-hash-fp-112", &flag_rac2_gcse_hash_fp_112, 1,\n   "Add 112 to the GCSE expression hash of the frame pointer"},\n  {"rac2-gcse-hash-fp-117", &flag_rac2_gcse_hash_fp_117, 1,\n   "Add 117 to the GCSE expression hash of the frame pointer"},\n  {"rac2-giv-pair-init", &flag_rac2_giv_pair_init, 1,\n')], 'flags.h': [('extern int flag_rac2_gcse_hash_111;\n/* RAC2: GCSE hashes the frame pointer 117 buckets further on.  */\nextern int flag_rac2_gcse_hash_fp_117;\n/* RAC2: paired giv initial values share base + product.  */\nextern int flag_rac2_giv_pair_init;\n/* RAC2: cse2 does not record a register sum set into a multiply-set\n', 'extern int flag_rac2_gcse_hash_111;\n/* RAC2: GCSE hashes the frame pointer 117 buckets further on.  */\nextern int flag_rac2_gcse_hash_fp_117;\n/* RAC2: GCSE hashes the frame pointer 112 buckets further on.  */\nextern int flag_rac2_gcse_hash_fp_112;\n/* RAC2: paired giv initial values share base + product.  */\nextern int flag_rac2_giv_pair_init;\n/* RAC2: cse2 does not record a register sum set into a multiply-set\n')]}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_gcse_hash_fp_112" in text for text in sources.values()):
        raise ValueError("gcse-hash-fp-112 option already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
