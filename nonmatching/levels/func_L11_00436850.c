/* func_L11_00436850 (192 bytes, 1 place) -- measured 0 of 1.

   The retail body, decoded instruction by instruction (frame 0x20, $s0 = the object's
   state at +0x68, $s1 = the object, $s2 = 1):

     lbu $v0,0x20($s1) ; sltiu $v0,$v0,4 ; beqz $v0,.L80   (delay: lw $s0,0x68($s1))
     the byte is below 4:  b .L004368F4                   (delay: sw $zero,0x270($s0))
     .L00436880: lh $v0,0x282($s0) ; addiu $s2,$zero,1
                  bnel $v0,$s2,.L004368B0                (delay: lw $a0,0xB8($s1))
     the flag is 1:       lui/mtc1 $f12 = 100.0f ; daddu $a0,$s1 ; lw $a1,0x27C($s0)
                          daddu $a2,$zero ; daddu $a3,$zero ; b .L004368DC
                                                     (delay: mov.s $f13,$f12)
     .L004368B0: jal func_L11_00441868                  (delay: lh $a1,0xAA($s1))
                  beqz $v0,.L004368F4                   (delay: daddu $a0,$s1)
                  lui/mtc1 $f12 = 100.0f ; sh $s2,0x282($s0) ; daddu $a2,$zero
                  lw $a1,0x27C($s0) ; mov.s $f13,$f12 ; daddu $a3,$zero
     .L004368DC: jal func_002B3BA8                      (delay: nop)
                  lw $v1,0x200($s0) ; sh $v0,0x280($s0)
                  b .L004368F8                          (delay: sw $v1,0x270($s0))
     .L004368F4: sh $zero,0x282($s0)
     .L004368F8: the epilogue

   So: a byte below 0x20 below 4 clears the state's word at 0x270 and its halfword at
   0x282; otherwise a halfword at 0x282 of 1 goes straight to the call, and any other
   value asks func_L11_00441868 (the handle at +0xB8, the class at +0xAA) first, whose
   failure clears 0x282 and whose success sets it to 1.  Both paths then call
   func_002B3BA8 with the object, the state's word at 0x27C, 0, 0, 100.0f and 100.0f,
   store the result as a halfword at 0x280 and copy the state's word at 0x200 to 0x270.

   This candidate is the retail's shape: 45 of the retail's 48 words, 26 of them
   differing, all in the two paths' argument setup.  What is left:

     - the class call's first argument is the handle at +0xB8; retail loads it once, in
       the bnel delay slot, and the class path uses it there, while this cc1 loads it
       again in the class path;
     - retail's already-ready path sets up $a2, $a3 and $f13 itself and branches to the
       shared call, while this cc1 jumps into the middle of the other path's argument
       setup (the cross-jump merges more here than there);
     - retail's shared call block has a nop delay slot because both paths set $f13
       before it, while this cc1 keeps `mov.s $f13,$f12` in that delay slot.

   Tried and identical: every ordering of the two paths, the call written twice or
   once with a goto, the class call taking the object instead of the handle, the handle
   hoisted into a local, the flag read into a local, and the flags -fno-schedule-insns,
   -fno-gcse, -fno-strength-reduce, -fno-sched-interblock, -fno-thread-jumps,
   -fno-expensive-optimizations, -mno-split-addresses, -O1 and -O3.
*/

typedef int s32;
typedef unsigned char u8;
typedef short s16;
typedef float f32;

extern s32 func_L11_00441868(u8 *object, s32 class_id);
extern s32 func_002B3BA8(u8 *object, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);

void func_L11_00436850(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);

    if (*(u8 *)(obj + 0x20) < 4) {
        *(s32 *)(state + 0x270) = 0;
        goto zero;
    }
    if (*(s16 *)(state + 0x282) == 1) {
        *(s16 *)(state + 0x280) = func_002B3BA8(obj, *(s32 *)(state + 0x27C), 0, 0, 100.0f, 100.0f);
        *(s32 *)(state + 0x270) = *(s32 *)(state + 0x200);
        return;
    }
    if (!func_L11_00441868(*(u8 **)(obj + 0xB8), *(s16 *)(obj + 0xAA)))
        goto zero;
    *(s16 *)(state + 0x282) = 1;
    *(s16 *)(state + 0x280) = func_002B3BA8(obj, *(s32 *)(state + 0x27C), 0, 0, 100.0f, 100.0f);
    *(s32 *)(state + 0x270) = *(s32 *)(state + 0x200);
    return;
zero:
    *(s16 *)(state + 0x282) = 0;
}
