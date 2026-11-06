/* 6 November 2026, round 6: marked ASM_FUNC in src/ (original assembly, pending maintainer review); see the src comment for the evidence. */
/* func_00282848, 72-byte original extent, 28 placements.
   A measured tools/levels.py entry correction skips the 56-byte prefix and
   retains the final 16-byte function. In level 00 the original row starts at
   0x002EDC48 and the function starts at 0x002EDC80; every other placement has
   the same prefix/body split and bytes. The prefix contains six positive
   stack adjustments and eight nops after a completed neighboring return.
   Scans found no branch, jump, address-pair or aligned-word reference into
   the prefix or to the shortened entry.

   The corrected 16-byte function is:

     lwc1   $f0, -0x76E4($gp)
     nop
     jr     $ra
     mul.s  $f0, $f0, $f12

   This is the same load/nop/jr/mul shape measured in blocker 4 for
   func_L00_002EDCB8 and its twins: C emits 12 bytes, omitting the nop before
   jr. No source or compiler variant is repeated here. */

#include "include_asm.h"
