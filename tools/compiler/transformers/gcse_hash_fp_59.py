#!/usr/bin/env python3
"""Add the opt-in -frac2-gcse-hash-fp-59 and -frac2-gcse-hash-parm-91 to gcse's expression hash.

Siblings of -frac2-gcse-hash-fp-54 and -frac2-gcse-hash-parm-85 (cea0_rules.py):
-frac2-gcse-hash-fp-59 hashes the frame pointer 59 buckets further on, and
-frac2-gcse-hash-parm-91 hashes the pseudo register that holds an incoming argument 91 buckets
further on. They change PRE's bucket walk, so the order in which reaching registers are created
and spilled. In the PAL and USA v2.00 copies of func_0034CEA0 (func_PAL_0034F068,
func_US2_0034DBE0), whose larger menu object moves its fields, these offsets with the 415-bucket
table give retail's spill-slot order where fp-54/parm-85 give v1.01's.

An opt-in per-unit model under the owner's standard of 12 November 2026 (allowed for these two
functions by owner ruling, 14 November 2026). Default compilation is unchanged.

Usage: gcse_hash_fp_59.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {
    'gcse.c': [(
        '\tif (flag_rac2_gcse_hash_parm_85 && rac2_parm_pseudo_p (REGNO (x)))\n'
        '\t  hash += 85;\n',
        '\tif (flag_rac2_gcse_hash_parm_85 && rac2_parm_pseudo_p (REGNO (x)))\n'
        '\t  hash += 85;\n'
        '\t/* RAC2: -frac2-gcse-hash-fp-59 and -frac2-gcse-hash-parm-91, the\n'
        '\t   same with 59 buckets for the frame pointer and 91 for an\n'
        '\t   argument\'s pseudo register.  */\n'
        '\tif (flag_rac2_gcse_hash_fp_59 && regno == FRAME_POINTER_REGNUM)\n'
        '\t  hash += 59;\n'
        '\tif (flag_rac2_gcse_hash_parm_91 && rac2_parm_pseudo_p (REGNO (x)))\n'
        '\t  hash += 91;\n',
    )],
    'toplev.c': [(
        'int flag_rac2_gcse_hash_parm_85 = 0;\n',
        'int flag_rac2_gcse_hash_parm_85 = 0;\n'
        '/* RAC2: opt-in, GCSE hashes the frame pointer 59 and an argument\'s\n'
        '   pseudo register 91 buckets further on.  */\n'
        'int flag_rac2_gcse_hash_fp_59 = 0;\n'
        'int flag_rac2_gcse_hash_parm_91 = 0;\n',
    ), (
        '  {"rac2-gcse-hash-parm-85", &flag_rac2_gcse_hash_parm_85, 1,\n'
        '   "Add 85 to the GCSE expression hash of an argument\'s pseudo register"},\n',
        '  {"rac2-gcse-hash-parm-85", &flag_rac2_gcse_hash_parm_85, 1,\n'
        '   "Add 85 to the GCSE expression hash of an argument\'s pseudo register"},\n'
        '  {"rac2-gcse-hash-fp-59", &flag_rac2_gcse_hash_fp_59, 1,\n'
        '   "Add 59 to the GCSE expression hash of the frame pointer"},\n'
        '  {"rac2-gcse-hash-parm-91", &flag_rac2_gcse_hash_parm_91, 1,\n'
        '   "Add 91 to the GCSE expression hash of an argument\'s pseudo register"},\n',
    )],
    'flags.h': [(
        'extern int flag_rac2_gcse_hash_parm_85;\n',
        'extern int flag_rac2_gcse_hash_parm_85;\n'
        '/* RAC2: GCSE hashes the frame pointer 59 and an argument\'s pseudo\n'
        '   register 91 buckets further on.  */\n'
        'extern int flag_rac2_gcse_hash_fp_59;\n'
        'extern int flag_rac2_gcse_hash_parm_91;\n',
    )],
}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_gcse_hash_fp_59" in text for text in sources.values()):
        raise ValueError("gcse-hash-fp-59 option already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
