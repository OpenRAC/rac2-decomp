/* No attempt: the extent is not a function - a catalogue split error.

   The catalogue's 288-byte extent at 0x0034B1C0 (level 01) holds sixteen bytes of
   dead code and then the real function:

     0034B1C0  sw   $t3, 0x40($v1)     <- $t3 and $v1 are never set here
     0034B1C4  nop
     0034B1C8  addiu $sp, $sp, 0x20    <- a frame release without an allocation
     0034B1CC  nop
     0034B1D0  lui  $a1, 0x14          <- the real function starts here

   The sixteen bytes sit between the previous function's `jr $ra` (the body that
   ends at 0x0034B1BC, a copy of the boot's func_002DB7F0) and the real
   function's first instruction; no code branches or calls into them, and the
   real function is 272 bytes long, with its own `jr $ra` at 0x0034B2D8 and
   return-value delay slot at 0x0034B2DC.

   The real function's entry is 0x0034B1D0: level 01's data section holds the
   pointer 0x0034B1D0 at offset 0x2B380 (data.bin + 0x2B380), and the boot
   carries the same code as func_002DB988 (0x002DB988, 288 bytes) with the
   same sixteen dead bytes in front of it and the same 272-byte body behind them;
   the boot's pointer to that body is at 0x0025E630.

   So the extent needs a separately preserved sixteen-byte prefix and a
   272-byte function at 0x0034B1D0 - a fix in
   `tools/levels.py`, not in C.  The body itself reads the table at 0x00139948,
   fills twelve-byte records at 0x0022D5F0 from it, writes the object's flag
   word at +0x30, clears the index at +0x40 and searches the table at
   0x001D9AA0; it needs the `$gp`-relative load of the global at 0x001AA7F0
   (`lw $a0,-0x4800($gp)`), so it belongs in a `-g8.c` unit when it is matched.
   The existing R5900 reader reconfirmed the sixteen-byte prefix in USA v1.01,
   PAL and USA v2.00 on 2 November 2026; the corrected size and return addresses
   above describe the USA v1.01 row. No catalogue edit or match is claimed. */
