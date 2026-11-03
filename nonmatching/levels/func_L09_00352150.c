/* 3 November 2026: entry defect resolved in FUNCTION_ENTRY_OFFSETS.
 * Matching C now lives in src/levels/shared/L09_00352150-g8.c.
 * The earlier diagnosis below is retained as history. */
/* func_L09_00352150 - 288 bytes, 1 place, level 09_dobbo, retail at 0x00352150.
   Screened, not attempted in this wave: the extent looks like a catalogue fragment
   rather than a function, so no C was written for it and nothing here is a
   measurement.

   The evidence:
   - the extent's first instruction is `sw $t3, 0x40($v1)`, and neither $t3 nor $v1
     is set anywhere in the 288 bytes that follow. The body sets $v1 itself, at
     0x0035217C (`lui $v1, 0x29`), eight instructions later. A compiler never emits a
     store through a register it has not written, so the extent cannot be a whole
     function that starts at 0x00352150;
   - the body has no caller: no jal, no branch and no jump table entry in level 09
     reaches 0x00352150 or the four instructions after it, and no word of level 09's
     loaded data holds the address 0x00352150;
   - the same 288 bytes are in the boot executable as func_002DB988 (0x002DB988,
     also 288 bytes), with the same first instruction `sw $t3, 0x40($v1)`, and the
     boot's copy is referenced by nothing either;
   - the previous function, func_002DB7F0 (the boot's copy is at 0x002DB7F0, 404
     bytes), ends with `jr $ra` and its delay slot `addiu $sp, $sp, 0x50` at
     0x00352144/0x00352148, so the byte before this extent (0x0035214C) is the word
     the previous body left behind, and the extent starts on a new word.

   What the body does, for whoever checks the catalogue: it reads the word at
   0x00139948 (a boot global) as a count, fills a table of twelve-byte records at
   0x0021DB30 from the entries at 0x0029E20 and 0x0029E24 (stride 12), stops after
   twenty-eight entries, zeroes the last record, clears the word at +0x40 of its
   argument, sets bit 0x8000 of the word at +0x30, and then walks the table at the
   boot global 0x001A79F0 looking for the value the argument's state holds at
   0x001CA210.

   The fix for this belongs in tools/levels.py (the extent has to be split at its real
   start), not in C: a C function cannot read a register it never set, and any C that
   did would be a different function. */
