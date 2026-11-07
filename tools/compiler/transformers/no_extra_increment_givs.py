#!/usr/bin/env python3
"""Add the opt-in -frac2-no-extra-increment-givs: no biv-to-giv conversion of extra increments.

When a basic induction variable is incremented more than once per iteration (a cursor
advanced by `*p++ = a; *p++ = b;`), strength_reduce (loop.c) counts the extra increments
(`n_extra_increment`, biv_count - 1 per biv) and, unless the loop has a volatile reference
(`loop_has_volatile`), turns every increment but the last into a DEST_REG giv: the increment
`p = p + 4` becomes a giv `p' = p + 4` of the biv, and the uses after it read p'. The cursor's
increments are then split into several reduced registers or folded into the address offsets.

The FSF disabled that conversion for the gcc-2.95 release together with giv recombination:
Jeffrey A Law, 10 June 1999 (gcc-2.95/gcc/ChangeLog: "loop.c (strength_reduce): Disable
biv->giv translations and giv recombination.  For the release branch only."). Every 2.95
release (2.95, 2.95.1, 2.95.2, 2.95.3; gcc-core tarballs from ftp.gnu.org) ships the guard as
`if (0 && n_extra_increment  && ! loop_has_volatile)` under the comment "Disabled for the
gcc-2.95 release.  There are still some problems with giv recombination. ...". This
snapshot's own loop.c (the Cygnus development tree of 11 November 1999) runs the conversion;
that Cygnus kept it on is inferred from that source alone. no_recombine_givs.py takes the other
half of the same release-branch change, unconditionally.

Retail witness: func_00284268 (2,988 bytes, boot + 27 levels in USA v1.01, PAL and v2.00)
advances its cursors with several increments per iteration in seven loops, and retail keeps
every increment whole. This tree matches it only with a volatile view of the stored-to struct,
whose sole effect on loop.c is loop_has_volatile; with the conversion off, the same C without
the volatile view matches at all 28 places in each release. Without the option every
game-compiler unit of src/ compiles as before; forced on in all of them, only that function
changes. Of the 1,074 drafts in nonmatching/ that compile, one changes (func_L05_0042B2C0) and
gets no closer.

With this option the conversion is skipped, as in the 2.95 releases. It does not touch the
other test of loop_has_volatile, in check_dbra_loop's loop reversal. It keys on no function,
only on the option. It is off by default, enabled per unit in config/cflags.txt, and
-fno-rac2-no-extra-increment-givs disables it again. tests/test_no_extra_increment_givs.py
covers the anchors, the default/disabled equality, a loop whose code changes only with the
option and controls. See docs/COMPILER-NOTES.md.

Usage: no_extra_increment_givs.py <gcc source directory>   (the one holding toplev.c)
"""
import sys
from pathlib import Path

# loop.c, strength_reduce: the guard GCC 2.95 ships as `if (0 && ...)`.
GUARD_OLD = ("  /* If the loop contains volatile memory references do not allow any\n"
             "     replacements to take place, since this could loose the volatile markers.  */\n"
             "  if (n_extra_increment && ! loop_has_volatile)\n")
GUARD_NEW = ("  /* If the loop contains volatile memory references do not allow any\n"
             "     replacements to take place, since this could loose the volatile markers.\n"
             "\n"
             "     RAC2: -frac2-no-extra-increment-givs skips the conversion, as the\n"
             "     gcc-2.95 release branch does (law, 1999-06-10).  */\n"
             "  if (! flag_rac2_no_extra_increment_givs\n"
             "      && n_extra_increment && ! loop_has_volatile)\n")
DEFINITION_OLD = "int flag_rac2_no_static_chain_base = 0;\n"
DEFINITION_NEW = ("int flag_rac2_no_static_chain_base = 0;\n"
                  "\n"
                  "/* RAC2: opt-in, gcc-2.95's strength reduction: extra biv increments\n"
                  "   stay bivs.  */\n"
                  "int flag_rac2_no_extra_increment_givs = 0;\n")
OPTION_OLD = '   "Give the static chain and struct-value registers no alias base"},\n'
OPTION_NEW = (OPTION_OLD +
              '  {"rac2-no-extra-increment-givs", &flag_rac2_no_extra_increment_givs, 1,\n'
              '   "Do not turn extra biv increments into givs"},\n')
DECLARATION_OLD = "extern int flag_rac2_no_static_chain_base;\n"
DECLARATION_NEW = ("extern int flag_rac2_no_static_chain_base;\n"
                   "\n"
                   "/* RAC2: loop.c keeps every increment of a biv a biv increment, as\n"
                   "   gcc-2.95.  */\n"
                   "extern int flag_rac2_no_extra_increment_givs;\n")


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(root: Path) -> None:
    loop, top, flags = root / "loop.c", root / "toplev.c", root / "flags.h"
    sources = {path: path.read_text(encoding="latin-1") for path in (loop, top, flags)}
    if any("flag_rac2_no_extra_increment_givs" in text for text in sources.values()):
        raise ValueError("no-extra-increment-givs option already present")
    guard = replace_once(sources[loop], GUARD_OLD, GUARD_NEW, "strength_reduce guard")
    driver = replace_once(sources[top], DEFINITION_OLD, DEFINITION_NEW, "option definition")
    driver = replace_once(driver, OPTION_OLD, OPTION_NEW, "option table")
    declarations = replace_once(sources[flags], DECLARATION_OLD, DECLARATION_NEW,
                                "option declaration")
    # Check every anchor before writing any source: drift must leave the tree intact.
    for path, contents in ((loop, guard), (top, driver), (flags, declarations)):
        path.write_text(contents, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
