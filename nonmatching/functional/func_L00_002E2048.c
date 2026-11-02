/* functional: high. Reads the same control word and returns -1 or the two-bit field; only instruction forms differ. */
/* 0 of 27 places match - last line: 00_aranos_tutorial: 32 bytes, expected 44
   Retail materialises the block base into $at (lui + addiu, the +0x1C left as the
   load's literal offset), loads the mask 0x60 with ADDI into $v1 and ANDs through it,
   and keeps an explicit nop in the first jr's delay slot; here gcc loads through the
   destination register (lui $v0 / lw $v0,0x1C($v0)), folds the mask into ANDI and
   fills the delay slot with the shift. Flat, base-pointer and named-symbol spellings
   all agree; s64/unsigned forms change the shift to dsrl, which retail does not use.
   Needs a lever that keeps the address in $at (a scratch register) and the mask in a
   register.

   Measured again on 22 October 2026 with the compiler rebuilt from the current sources:
   the wall is unchanged (32 bytes, the first four words differ). Three differences are
   open, and the ADDI/ADDU one is new:
     - the base is a per-level address: 0x001BF200 in level 00, and every other level
       has its own (lui 0x1C + addiu -0xE00 in 00, -0x700 in 01, ...). It is the %hi/%lo
       split of that address, so the C needs a per-level symbol (ref_L00_002E2048_00)
       and a pointer the load indexes (base[7]), not a folded displacement;
     - the mask 0x60 sits in $v1 (addi $v1,$zero,0x60) and the AND reads it; this cc1
       folds it into ANDI, and an int local does not stop it;
     - retail's failure value is `addi $v0,$zero,-1` (opcode 0x08) where this cc1 emits
       `addiu $v0,$zero,-1` (opcode 0x09): the same immediate, the other opcode. The
       brief's rule holds - `-1` gives addiu, `0xFFFFFFFFu` gives lui/ori - so a spelling
       that keeps the constant signed and small is still needed.
   The first jr's delay slot holds an explicit nop in retail and the shift here, which
   follows from the mask's shape. */

typedef int s32;

extern unsigned char D_L00_001BF200[];

s32 func_L00_002E2048(void) {
 s32 v=*(s32 *)(D_L00_001BF200+0x1C);
 if(v<0) return -1;
 return (v&0x60)>>5;
}
