/* 2 November 2026 retail recheck; this supersedes conflicting historical notes below.
 * Fresh US retail in both placements has16-byte prefix sw t3,0x40(v1);nop;addiu sp,sp,+0x20;nop, after prior completed return. Real menu body at+16; loaded pointers291790->363330 and2887C0->34CCD8 witness both entries. No external static ref to prefix in direct/pointer/nearby-pair scan. Reopen on reviewed16-byte entry correction; no fake C prefix.
 * No matching credit, generator change or ASM_FUNC classification.
 */
/* func_L08_00363320 - 288 bytes, 2 place(s), level 08_tabora, retail at
   0x00363320. Screened with tools/w10_screen.py: 0 call(s) [-]; data
   addresses materialised [0x220000, 0x290000, 0x290000, 0x1d0000]; float
   constants [0x140000]; $gp-relative small data: no   saves: -; callee-
   saved registers saved [-]; words plain C cannot emit [-]. Head: sw $t3,
   0x40($v1) ; nop ; addiu $sp, $sp, 0x20 ; nop ; lui $a1, 0x14 ; daddu $t2,
   $a0, $zero. Not matched in this wave: the body is straight-line code
   whose register allocation and the materialisation of its constant
   addresses have to be reproduced word for word. What would unblock it: the
   exact source expression tree, so this cc1 picks the same registers in the
   same order. */
