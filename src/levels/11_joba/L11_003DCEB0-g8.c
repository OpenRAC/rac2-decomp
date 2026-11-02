#include "common.h"

/* func_L11_003DCEB0: a Joba moby's update. State 0 moves it along its velocity and, on a
   func_002761F8 hit, snaps to the hit point and switches to state 1; state 1 counts frames
   at 0x96. It is removed with an effect (func_002ABBB8) when func_002A9640 finds a target,
   or from frame 0x79 of state 1.
   Built -O2 -G8 in its own unit. The flag takes the state value (1) only once the count
   reaches 0x79, which gives retail's movn; the effect table is the sda incomplete array
   most callers declare, so its address is one macro load beside the argument moves. */
extern f32 D_L11_001B0170 __attribute__((sda));
extern f32 D_L11_001B016C __attribute__((sda));
extern f32 D_L11_001B0174 __attribute__((sda));
extern u8 D_L11_001C0D20[];
extern u8 D_L11_001A8F20[] __attribute__((sda));
extern s32 func_002761F8(void *, void *, s32, void *, s32);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_002E5CF8(s32, s32, u8 *);
extern void func_0029F338(u8 *);
extern void *func_002A9640(void *, int, int);
extern void func_00282CC0(void *, void *, void *);
extern void func_002A7750(void *, int, int);

void func_L11_003DCEB0(u8 *a0) {
    u8 vec[16] __attribute__((aligned(16)));
    u8 *s0 = *(u8 **)(a0 + 0x68);
    s32 flag = 0;
    u8 state = a0[0x20];

    switch (state) {
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
        *(u16 *)(a0 + 0x96) += 1;
        if (*(u16 *)(a0 + 0x96) >= 0x79) flag = state;
        break;
    }
    if (func_002A9640(a0, -1, 0) != 0 || flag != 0) {
        func_002ABBB8(a0, D_L11_001A8F20, a0 + 0x10, D_L11_001B0174, 1.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        func_002E5CF8(0, 0, a0);
        func_0029F338(a0);
    }
}
