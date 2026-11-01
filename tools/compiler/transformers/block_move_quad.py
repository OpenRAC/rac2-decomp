"""Move 16-byte-aligned block copies by quadwords, as the R5900 compiler did.

A structure copy long enough to become a block-move loop (over 0x40 bytes) was
emitted with ld/sd, four scratch registers per 32-byte round.  Retail moves the
same 32 bytes with two lq and two sq, and the leftover quadword with lq and sq,
whenever both objects are 16-byte aligned: func_L12_00418418, func_L03_003E4148,
func_L12_0041BF88, func_002DE990 and func_00288870.

expand_block_move capped the alignment at UNITS_PER_WORD, so the 16 never
reached output_block_move, which had no quadword case.  Short copies still
go through move_by_pieces at word alignment, unchanged.
"""
from pathlib import Path
import sys

CAP_OLD = ("  if (align > UNITS_PER_WORD)\n"
           "    align = UNITS_PER_WORD;\n\n"
           "  /* Move the address into scratch registers.  */")
CAP_NEW = ("  /* A 16-byte alignment reaches a block-move loop's quadword moves.  */\n"
           "  if (align > 16)\n"
           "    align = 16;\n"
           "  else if (align > UNITS_PER_WORD && align < 16)\n"
           "    align = UNITS_PER_WORD;\n\n"
           "  /* Move the address into scratch registers.  */")
PIECES_OLD = ("  else if (constp && bytes <= 2 * MAX_MOVE_BYTES\n"
              "\t   && align == UNITS_PER_WORD)\n"
              "    move_by_pieces (orig_dest, orig_src, bytes, align);\n")
PIECES_NEW = ("  else if (constp && bytes <= 2 * MAX_MOVE_BYTES\n"
              "\t   && align >= UNITS_PER_WORD)\n"
              "    move_by_pieces (orig_dest, orig_src, bytes, UNITS_PER_WORD);\n")
OUTPUT_OLD = ("      load_store[num].offset = offset;\n\n"
              "      if (TARGET_64BIT && bytes >= 8 && align >= 8)\n")
OUTPUT_NEW = ("      load_store[num].offset = offset;\n\n"
              "      if (bytes >= 16 && align >= 16)\n"
              "\t{\n"
              "\t  load_store[num].load = \"lq\\t%0,%1\";\n"
              "\t  load_store[num].load_nop = \"lq\\t%0,%1%#\";\n"
              "\t  load_store[num].store = \"sq\\t%0,%1\";\n"
              "\t  load_store[num].last_store = \"sq\\t%0,%1\";\n"
              "\t  load_store[num].final = 0;\n"
              "\t  load_store[num].mode = TImode;\n"
              "\t  offset += 16;\n"
              "\t  bytes -= 16;\n"
              "\t}\n\n"
              "      else if (TARGET_64BIT && bytes >= 8 && align >= 8)\n")


def patch(path):
    path = Path(path)
    source = path.read_text(encoding="utf-8")
    for old, new in ((CAP_OLD, CAP_NEW), (PIECES_OLD, PIECES_NEW), (OUTPUT_OLD, OUTPUT_NEW)):
        if source.count(old) != 1:
            raise ValueError("expected once, found %d: %r" % (source.count(old), old[:40]))
        source = source.replace(old, new)
    path.write_text(source, encoding="utf-8", newline="")


if __name__ == "__main__":
    patch(sys.argv[1])
    print("16-byte-aligned block moves use lq and sq")
