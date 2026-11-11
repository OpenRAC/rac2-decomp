/* 11 November 2026: August 6 preview anchor (aug6-retail-anchors.tsv row
 * 0x002ED880, unique_masked_candidate) confirms the full function spans 72 bytes
 * at 0x002ED880. The 28-byte extent in the retail catalogue is an orphaned
 * fragment split before the function's branch/return.
 */
/* Catalogue review pending: the 28-byte USA v1.01 extent at 0x002ED880 is
 * `sw $a0,0x48($v0); nop; lw $v0,0x48($v1); nop; nop; nop;
 * addiu $sp,$sp,0xB0; nop`. It has no branch or return in its listed extent.
 * The next instruction is part of a later body at 0x002ED8A0, while the next
 * catalogue entry func_002ED8F0 is farther ahead. Establish control-flow
 * ownership before changing the generated catalogue.
 */
