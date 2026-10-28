/* func_L11_00455DF8 - 536 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L11_00455DF8 (536 B), in L11_00453358.c (declare
   func_L11_00456540/00456378 with `char *` to match their later definitions
   there). Draft is 532 B vs 536, 72 masked lines, but shape is the same; all
   constants right (1.5707965f gives 0x3FC90FDC).
   Remaining diffs: (1) retail loads the constants in order
   0.5,0.4,1.0,0.25,1.5707965,0.5236,0.01,0.0055,0.75 into
   f0,f8,f7,f4,f5,f1,f2,f3,f6; mine gives 0.25->f6, 1.57->f4, 0.75->f5. (2)
   retail stores 0x10C (0.5) right after 0x104, mine delays it to the end ($f0
   stores 0x108/0x10C after sb 0x29); moving the statement did not change it.
   (3) in the v!=0 branch retail keeps `lw $a0,0x20($v1)` / `beql $a0,$zero`
   with the moby pointer redone in the delay slot (`daddu $a0,$s1`), mine uses
   $v0 and a plain beqz (pointer-typed field read did not change that). */

extern int func_00283CF0(f32);
extern u8 *func_002A9640(u8 *, int, int);
extern int func_002B0ED8(u8 *, u8 *, int);
extern f32 func_00282E48(u8 *, void *);
extern void func_002A93B0(u8 *);
extern void func_L11_00456540(char *);
extern void func_L11_00456378(char *);
extern u8 D_L11_001BA8C0[];

void func_L11_00455DF8(u8 *a0) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    u8 *v;

    if (a0[0x20] == 0) {
        s0[0x48] = func_00283CF0(15.0f);
        s0[0x4A] = func_00283CF0(12.0f);
        *(u16 *)(s0 + 0x256) = 0;
        s0[0x60] = 13;
        *(int *)(s0 + 0x98) = 4;
        *(f32 *)(s0 + 0x8C) = 0.4f;
        *(f32 *)(s0 + 0x100) = 1.0f;
        *(f32 *)(s0 + 0x104) = 0.25f;
        *(f32 *)(s0 + 0x10C) = 0.5f;
        *(f32 *)(s0 + 0x110) = 1.5707965f;
        *(f32 *)(s0 + 0x130) = 0.52359885f;
        *(f32 *)(s0 + 0x134) = 0.01f;
        *(f32 *)(s0 + 0x12C) = 0.0055555557f;
        s0[0x28] = 3;
        *(f32 *)(s0 + 0x30) = 0.75f;
        s0[0x29] = 1;
        *(f32 *)(s0 + 0x80) = 0.5f;
        *(f32 *)(s0 + 0x84) = 0.5f;
        *(f32 *)(s0 + 0x108) = 0.5f;
        func_L11_00456540((char *)a0);
    }
    if (a0[0x31] != 0) {
        if (a0[0x20] >= 3) {
            v = func_002A9640(a0, 0x10000, 1);
            if (v != 0 && *(u8 **)(v + 0x20) != 0 && a0[0x31] == 0) {
                if (*(short *)(a0 + 0xAA) == 0xDF9 || *(short *)(a0 + 0xAA) == 0xB89) {
                    *(int *)(v + 0x2C) = 0;
                }
            }
            if (func_002B0ED8(a0, s0 + 0x50, 0) == 5) {
                *(int *)(s0 + 0xE0) = 0;
                *(f32 *)(s0 + 0xE4) = 0.8377582f;
            }
        }
    }
    if (a0[0x31] != 0) {
        if (func_00282E48(a0 + 0x10, D_L11_001BA8C0) < 6.0f) {
            func_002A93B0(a0);
        }
        a0[0x6F] = 0x16;
    }
    if (a0[0x20] >= 2) {
        if (s0[0x2E] == 2) {
            func_L11_00456540((char *)a0);
        }
    }
    func_L11_00456378((char *)a0);
}
