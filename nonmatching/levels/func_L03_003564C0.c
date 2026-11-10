/* 3 November 2026: entry defect resolved in FUNCTION_ENTRY_OFFSETS.
 * Matching C now lives in src/levels/shared/L03_003564C0-g8.c.
 * The earlier diagnosis below is retained as history. */
/* No attempt: the catalogue row does not start at the function. The row
   func_L03_003564C0 covers 288 bytes at 03:003564C0 and 19:00352E18, but its
   first 16 bytes are not part of the body: at 03:003564C0 they are
   0xAC6B0040 - `sw $t3, 0x40($v1)` - with a `nop` after it, then
   `addiu $sp, $sp, 0x20` and another `nop`. $v1 and $t3 are never set inside
   the extent, and the frame is released without a matching allocation, so no
   C body can produce them: they are the dead tail of the code that precedes
   the function (the previous function func_002DB7F0 ends with its `jr $ra`,
   its delay slot and one `nop` of padding at 03:003564BC). Nothing in either
   program branches to 0x003564C0 or 0x00352E18.

   The body proper is the 272 bytes from 03:003564D0 and 19:00352E28. The
   same body is the level 00 row func_L00_00354DF8 (272 bytes at 00:00354DF8),
   whose extent the catalogue already starts after the same 16-byte prefix -
   docs/build/levels.md names that correction ("00354DE8 to 00354DF8") among the
   three measured Aranos entries. The two rows here carry the prefix, so they
   are 16 bytes too long and start 16 bytes too early.

   The fix is in tools/levels.py (the level 00 correction applied to the two
   other places of the same body), not in C. No C can be placed at the rows as
   they stand. */
