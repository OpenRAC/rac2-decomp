/* func_L09_003FB860 (164 bytes, 1 place) -- measured 0 of 1.

   The retail body, decoded instruction by instruction (frame 0x20, $s0 = index * 4,
   $a0 = index * 8, $s1 = -1):

     lui/addiu $v0 = D_1B36E0            (an adjacent pair, before the first save)
     lui $a1 = %hi(D_255E90)            (split: the addiu comes after the third save)
     sll $s0,$a0,2 ; addiu $a1,$a1,%lo(D_255E90) ; sll $a0,$a0,3
     addu $s2,$s0,$v0                    (&D_1B36E0[index])
     lui/addiu $v1 = D_1B35E0            (an adjacent pair)
     lw $a2,0x0($s2)                     (the handle)
     addu $v0,$a0,$a1 ; sw $zero,0x0($v0)   (D_255E90[index * 8], the first word)
     addu $v1,$s0,$v1 ; addu $a1,$a1,$a0 ; sw $zero,0x0($v1)
     beq $a2,$s1,.L003FB8C8              (delay: sw $zero,0x4($a1), the second word)
     jal func_00291450                   (delay: daddu $a0,$a2,$zero)
     sw $s1,0x0($s2)                     (D_1B36E0[index] = -1)
     .L003FB8C8: lui/addiu $v0 = D_1B3720 ; addu $s0,$s0,$v0 ; lw $a0,0x0($s0)
     beql $a0,$s1,.L003FB8F0             (delay: ld $s0,0x0($sp))
     jal func_00291450 ; nop ; sw $s1,0x0($s0) ; ld $s0,0x0($sp)

   So: the word of D_1B35E0[index] and both words of the 8-byte entry of D_255E90 are
   cleared, the handle in D_1B36E0[index] is handed to func_00291450 and then set to -1,
   and the same is done for D_1B3720[index].

   This candidate is the retail's size (164 bytes, 41 words) and differs in 11 of the
   first 16 words, all of them in the prologue: retail keeps the D_1B36E0 and D_1B35E0
   lui/addiu pairs adjacent (the first one before the first register save, the second
   one just before the load of the handle) and splits the D_255E90 pair around the
   saves, while this cc1 splits the two pairs it emits and keeps D_255E90's adjacent.
   From the load of the handle on, the words are retail's, including the store of the
   second word in the beq delay slot and the beql with the restore in its delay slot.

   The 8-byte entry's address is computed twice in retail, once as index * 8 + base and
   once as base + index * 8, so the two halves need different source forms: the first
   as an array index (D_255E90[index * 2]) and the second as a byte pointer
   ((u8 *)D_255E90 + index * 8 + 4).  With one form for both, the compiler reuses the
   address and the body comes out four bytes short.

   Tried and identical: every order of the four statements, the handle load before or
   after the clears, the arrays indexed as D[i] or *(D + i), the pair as a struct or
   through a named pointer, and the flags -mno-split-addresses, -fno-schedule-insns,
   -fno-gcse, -fno-strength-reduce, -fno-sched-interblock, -fno-thread-jumps,
   -fno-expensive-optimizations, -O1 and -O3.
*/

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

extern int D_L09_001B35E0[];
extern int D_L09_001B36E0[];
extern int D_L09_001B3720[];
extern int D_L09_00255E90[];
extern void func_00291450(int);

void func_L09_003FB860(int index)
{
    int h;

    D_L09_001B35E0[index] = 0;
    D_L09_00255E90[index * 2] = 0;
    h = D_L09_001B36E0[index];
    *(int *)((u8 *)D_L09_00255E90 + index * 8 + 4) = 0;
    if (h != -1) {
        func_00291450(h);
        D_L09_001B36E0[index] = -1;
    }
    if (D_L09_001B3720[index] != -1) {
        func_00291450(D_L09_001B3720[index]);
        D_L09_001B3720[index] = -1;
    }
}
