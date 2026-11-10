/* Not a C row: not code at all. The four bytes at 0x0011F864 are 0xCDCDCDCD, the
 * linker's fill between two objects (rabbitizer prints the word as
 * `pref 0x0D,-0x3233($t6)`). It is the gap between func_0011F828 (whose tail
 * `j func_11F058` and its `addiu $sp,$sp,0x10` delay slot end at 0x0011F860)
 * and func_0011F868 at 0x0011F868 - the two are in different source objects
 * (src/core/0011F828.c and src/core/0011F868.c), and the fill is what the
 * catalogue's object boundary is made of (docs/build/levels.md). Nothing in the boot
 * jumps to 0x0011F864.
 *
 * tools/check.py func_0011F864: the smallest C function is `jr $ra; nop`, so the
 * candidate is 8 bytes against the row's 4 - "boot: 8 bytes, expected 4", 0 of 1
 * places match. No C produces a 0xCDCDCDCD word.
 *
 * Same class as func_00127218 and func_00127340: a split between two entries,
 * fixed in tools/levels.py, not a C body. */
