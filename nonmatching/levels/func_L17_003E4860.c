/* func_L17_003E4860 (124 bytes, 1 place) -- measured 0 of 1.

   The retail body, decoded instruction by instruction:

     lbu $v0,0x21($a0) ; addiu $v1,$zero,0xFF ; beq $v0,$v1,.L003E48D4
       (delay: daddu $v1,$v0,$zero -- the index copied for the table access)
     lui $v0,%hi(D_1FB720) ; sll $v1,$v1,2 ; addiu $v0,$v0,%lo(D_1FB720)
     addu $v1,$v1,$v0 ; lw $v0,0x0($v1)      (the table entry)
     beqz $v0,.L003E48D4
       (delay: lw $a2,0x3C2C($gp) -- the record base, reached through $gp)
     daddu $a0,$v0,$zero                       (the walk pointer)
     addiu $t0,$zero,0xB88 ; addiu $a3,$zero,0x1
   .L003E4898:
     lhu $v0,0x0($a0) ; andi $v0,$v0,0x7FFF ; sll $v0,$v0,8
     addu $a1,$a2,$v0                          (the record)
     lb $v1,0x20($a1)
     bltzl $v1,.L003E48CC
       (delay: lh $v0,0x0($a0) -- the next halfword)
     lh $v0,0xAA($a1)
     bnel $v0,$t0,.L003E48CC
       (delay: lh $v0,0x0($a0))
     lw $v0,0x68($a1) ; sh $a3,0x406($v0) ; lh $v0,0x0($a0)
   .L003E48CC:
     bgez $v0,.L003E4898
       (delay: addiu $a0,$a0,0x2 -- the walk pointer advances)
   .L003E48D4:
     jr $ra ; nop

   So: the byte at +0x21 of the object selects a halfword list; every record of the
   list whose byte at +0x20 is not negative and whose halfword at +0xAA is 0xB88 has
   the halfword at the word of +0x68 plus 0x406 set to 1; the list ends at the first
   negative halfword.

   This candidate is the retail's size (124 bytes, 31 words) and its instruction
   sequence is the retail's, including the two annulled branches (bltzl and bnel, each
   with the next halfword load in its delay slot), the $gp load of the record base and
   the bgez loop.  What is left is the register allocation: the byte lands in $v1
   against retail's $v0 (and the constant 0xFF in $v0 against retail's $v1), the walk
   pointer lands in $a1 against retail's $a0 and the record address in $a0 against
   retail's $a1.  The loop head follows, so this cc1 pads it with a nop where retail
   starts the loop one word earlier.

   The record base is reached through $gp, so the function needs a unit built with
   -G8 (a `-g8.c` sibling) and the sda attribute on the base.

   Tried and identical: the walk pointer as s16 * or u8 *, the table entry read into a
   second variable or used directly, the record base in a local or used inline, the
   record as u8 * or s8 *, the class halfword in a local, the index as s32, u32 or u8,
   the index copied before the table access, the loop as for(;;) with a break, as a
   while and as a do-while, and the flags -fno-schedule-insns, -fno-gcse,
   -fno-strength-reduce, -fno-sched-interblock, -fno-thread-jumps,
   -fno-expensive-optimizations, -mno-split-addresses, -O1 and -O3.
*/

typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef short s16;
typedef char s8;

extern s16 *D_L17_001FB720[];
extern s32 D_L17_001B2C1C __attribute__((sda));

void func_L17_003E4860(s32 a0)
{
    s32 i = *(u8 *)(a0 + 0x21);
    s16 *e;
    s16 *p;
    u8 *base;

    if (i == 0xFF)
        return;
    e = D_L17_001FB720[i];
    if (e == 0)
        return;
    p = e;
    base = (u8 *)D_L17_001B2C1C;
    for (;;) {
        u8 *q = base + ((*(u16 *)p & 0x7FFF) << 8);

        if (*(s8 *)(q + 0x20) >= 0) {
            if (*(s16 *)(q + 0xAA) == 0xB88)
                *(s16 *)(*(s32 *)(q + 0x68) + 0x406) = 1;
        }
        if (*(s16 *)p < 0)
            break;
        p++;
    }
}
