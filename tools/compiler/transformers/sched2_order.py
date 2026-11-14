#!/usr/bin/env python3
"""Add the opt-in -frac2-sched2-order: the after-reload sibling of -frac2-sched1-order.

With -frac2-sched2-order, the second scheduling pass (after reload) issues the insns named by
`#pragma rac2_sched2_order UID...' in the listed order, one per cycle, where the dependences
allow, through the same hooks as -frac2-sched1-order (rac2_order_of answers from this second
list once reload has completed). The list belongs to the next function compiled and is dropped
after its second scheduling pass.

This is an instruction-order hint, not a model of the retail compiler. By owner ruling of
14 November 2026 instruction-order hints are a fakematch mechanism allowed, besides
func_L05_0042B2C0, only for the last PAL and USA v2.00 functions (AGENTS.md); every unit that
uses one is a FAKEMATCH unit. Default compilation is unchanged.

Usage: sched2_order.py <gcc directory>
"""
import sys
from pathlib import Path

HUNKS = {
    "haifa-sched.c": [(
        "/* RAC2: the -frac2-sched1-order place of INSN, or 0.  */\n"
        "static int\n"
        "rac2_order_of (insn)\n"
        "     rtx insn;\n"
        "{\n"
        "  int uid = INSN_UID (insn);\n"
        "  if (!flag_rac2_sched1_order || reload_completed || uid >= rac2_order_size)\n"
        "    return 0;\n"
        "  return rac2_order_key[uid];\n"
        "}\n",
        "/* RAC2: -frac2-sched2-order.  rac2_order2_key[UID] is the 1-based place\n"
        "   of insn UID in the list given by #pragma rac2_sched2_order, or 0.  The\n"
        "   list belongs to the next function scheduled and is dropped after its\n"
        "   second scheduling pass.  */\n"
        "static int *rac2_order2_key;\n"
        "static int rac2_order2_size;\n"
        "static int rac2_order2_n;\n"
        "\n"
        "void\n"
        "rac2_sched2_order_add (uid)\n"
        "     int uid;\n"
        "{\n"
        "  if (uid < 0)\n"
        "    return;\n"
        "  if (uid >= rac2_order2_size)\n"
        "    {\n"
        "      int n = (uid + 1) * 2;\n"
        "      int *t = (int *) xcalloc (n, sizeof (int));\n"
        "      if (rac2_order2_key)\n"
        "\t{\n"
        "\t  bcopy ((char *) rac2_order2_key, (char *) t,\n"
        "\t\t rac2_order2_size * sizeof (int));\n"
        "\t  free (rac2_order2_key);\n"
        "\t}\n"
        "      rac2_order2_key = t;\n"
        "      rac2_order2_size = n;\n"
        "    }\n"
        "  rac2_order2_key[uid] = ++rac2_order2_n;\n"
        "}\n"
        "\n"
        "/* RAC2: the -frac2-sched1-order place of INSN before reload, or its\n"
        "   -frac2-sched2-order place after reload; else 0.  */\n"
        "static int\n"
        "rac2_order_of (insn)\n"
        "     rtx insn;\n"
        "{\n"
        "  int uid = INSN_UID (insn);\n"
        "  if (reload_completed)\n"
        "    {\n"
        "      if (!flag_rac2_sched2_order || uid >= rac2_order2_size)\n"
        "\treturn 0;\n"
        "      return rac2_order2_key[uid];\n"
        "    }\n"
        "  if (!flag_rac2_sched1_order || uid >= rac2_order_size)\n"
        "    return 0;\n"
        "  return rac2_order_key[uid];\n"
        "}\n",
    ), (
        "  if (!reload_completed && rac2_order_n)\n"
        "    {\n"
        "      bzero ((char *) rac2_order_key, rac2_order_size * sizeof (int));\n"
        "      rac2_order_n = 0;\n"
        "    }\n",
        "  if (!reload_completed && rac2_order_n)\n"
        "    {\n"
        "      bzero ((char *) rac2_order_key, rac2_order_size * sizeof (int));\n"
        "      rac2_order_n = 0;\n"
        "    }\n"
        "  /* RAC2: -frac2-sched2-order: the list served this function's second\n"
        "     pass.  */\n"
        "  if (reload_completed && rac2_order2_n)\n"
        "    {\n"
        "      bzero ((char *) rac2_order2_key, rac2_order2_size * sizeof (int));\n"
        "      rac2_order2_n = 0;\n"
        "    }\n",
    )],
    "c-lex.c": [(
        "\t\tstatic char rac2_name[] = \"rac2_sched1_order\";\n"
        "\t\textern void rac2_sched1_order_add PROTO((int));\n"
        "\t\tint k = 0;\n"
        "\n"
        "\t\twhile (rac2_name[k] && c == rac2_name[k])\n"
        "\t\t  c = GETC (), k++;\n",
        "\t\tstatic char rac2_name[] = \"rac2_sched1_order\";\n"
        "\t\textern void rac2_sched1_order_add PROTO((int));\n"
        "\t\textern void rac2_sched2_order_add PROTO((int));\n"
        "\t\tint k = 0, pass2 = 0;\n"
        "\n"
        "\t\t/* RAC2: #pragma rac2_sched2_order UID... names insns for\n"
        "\t\t   -frac2-sched2-order the same way.  */\n"
        "\t\twhile (rac2_name[k]\n"
        "\t\t       && (c == rac2_name[k] || (k == 10 && c == '2')))\n"
        "\t\t  {\n"
        "\t\t    if (k == 10 && c == '2')\n"
        "\t\t      pass2 = 1;\n"
        "\t\t    c = GETC (), k++;\n"
        "\t\t  }\n",
    ), (
        "\t\t      rac2_sched1_order_add (n);\n",
        "\t\t      if (pass2)\n"
        "\t\t\trac2_sched2_order_add (n);\n"
        "\t\t      else\n"
        "\t\t\trac2_sched1_order_add (n);\n",
    )],
    "flags.h": [(
        "extern int flag_rac2_sched1_order;\n",
        "extern int flag_rac2_sched1_order;\n"
        "/* RAC2: -frac2-sched2-order, the after-reload order hint.  */\n"
        "extern int flag_rac2_sched2_order;\n",
    )],
    "toplev.c": [(
        "int flag_rac2_sched1_order = 0;\n",
        "int flag_rac2_sched1_order = 0;\n"
        "int flag_rac2_sched2_order = 0;\n",
    ), (
        "  {\"rac2-sched1-order\", &flag_rac2_sched1_order, 1,\n"
        "   \"Before reload, schedule the insns named by #pragma rac2_sched1_order in that order\"},\n",
        "  {\"rac2-sched1-order\", &flag_rac2_sched1_order, 1,\n"
        "   \"Before reload, schedule the insns named by #pragma rac2_sched1_order in that order\"},\n"
        "  {\"rac2-sched2-order\", &flag_rac2_sched2_order, 1,\n"
        "   \"After reload, schedule the insns named by #pragma rac2_sched2_order in that order\"},\n",
    )],
}


def replace_once(text: str, before: str, after: str, label: str) -> str:
    if text.count(before) != 1:
        raise ValueError(f"{label}: expected one insertion point, found {text.count(before)}")
    return text.replace(before, after)


def patch(gcc: Path) -> None:
    sources = {name: (gcc / name).read_text(encoding="latin-1") for name in HUNKS}
    if any("flag_rac2_sched2_order" in text for text in sources.values()):
        raise ValueError("sched2-order option already present")
    for name, hunks in HUNKS.items():
        for k, (old, new) in enumerate(hunks):
            sources[name] = replace_once(sources[name], old, new, f"{name} hunk {k}")
    for name, text in sources.items():
        (gcc / name).write_text(text, encoding="latin-1", newline="")


if __name__ == "__main__":
    patch(Path(sys.argv[1]))
