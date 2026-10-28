/* func_L11_003DCEB0 - 436 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L11_003DCEB0 (436 B, 1 place). Goes in L11_003D6270-g8.c (-G8, uses
   $gp floats D_L11_001B016C/0170/0174, qcopy). Marker is still in
   L11_003D6270.c.
   Draft: 432 B vs 436, only difference is the state-1 flag:
     retail: daddu $s3,$a0,$zero ; addiu/andi/sh ; sltiu $v1,$v1,0x79 ; movn
   $s3,$zero,$v1   (and `lbu $a0,0x20($s1)` for the state, `beql $a0,$v0`)
     mine:   xori/sltu (flag = cnt >= 0x79), state in $v1
   Tried: flag = cnt>=0x79; flag=1; if (cnt<0x79) flag=0; flag=state; ternary
   `cnt<0x79 ? 0 : flag`; if/else chain instead of switch (worse). cse turns
   the known state==1 into a constant before combine. */

extern f32 D_L11_001B0170 __attribute__((sda));
extern f32 D_L11_001B016C __attribute__((sda));
extern f32 D_L11_001B0174 __attribute__((sda));
extern u8 D_L11_001C0D20[];
extern u8 D_L11_001A8F20[];
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002E5CF8(s32, s32, u8 *);
extern void func_0029F338(u8 *);

void func_L11_003DCEB0(u8 *a0) {
    u8 vec[16] __attribute__((aligned(16)));
    u8 *s0 = *(u8 **)(a0 + 0x68);
    s32 flag = 0;
    u16 cnt;

    switch (a0[0x20]) {
    case 0:
        func_00282CC0(vec, a0 + 0x10, s0);
        *(f32 *)(s0 + 8) = *(f32 *)(s0 + 8) - *(f32 *)(s0 + 0xC);
        if (func_002761F8(a0 + 0x10, vec, 2, 0, 0) != 0) {
            qcopy(a0 + 0x10, D_L11_001C0D20);
            *(f32 *)(a0 + 0x18) = *(f32 *)(a0 + 0x18) + D_L11_001B0170 * D_L11_001B016C;
            func_002A7750(a0, 1, -1);
        } else {
            qcopy(a0 + 0x10, vec);
        }
        break;
    case 1:
        cnt = *(u16 *)(a0 + 0x96) + 1;
        *(u16 *)(a0 + 0x96) = cnt;
        flag = cnt >= 0x79;
        break;
    }
    if (func_002A9640((s32)a0, -1, 0) != 0 || flag != 0) {
        func_002ABBB8(a0, D_L11_001A8F20, a0 + 0x10, D_L11_001B0174, 1.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        func_002E5CF8(0, 0, a0);
        func_0029F338(a0);
    }
}
