#include "include_asm.h"

#include "common.h"
extern int D_L10_001B1648 __attribute__((sda));
extern u8 D_L10_0042BEE0[];
extern int func_L00_002FCF18(void *a0, f32 f12, f32 f13, f32 f14, f32 f15, f32 f16);
extern f32 func_00283B98(f32 f12, f32 f13);
extern void func_L00_002E6EF8(void *a0, void *a1);
extern u8 *D_001B2614;
extern f32 func_002A7878(f32 low, f32 high);
extern f32 func_002A7940(void);
extern f32 func_00283CE0(int);
extern u8 D_L10_001C7800[];

/* Two-state start-up for a cloud puff: state 0 lays the record at +0x10 out (position
   reset, colour limits, the builder call, its handle in the $gp variable), and states 0
   and 1 both fade the +0xF8 value down; anything else goes straight to the update. */
void func_PAL_L10_00431BD0(u8 *a0) {
    u8 *s0 = a0;
    u8 state = *(u8 *)(s0 + 0x20);
    f32 v;

    switch (state) {
    case 0:
        *(int *)(s0 + 0x1C) = 0;
        *(u8 *)(s0 + 0x20) = 1;
        v = *(f32 *)(s0 + 0x1C);
        *(u16 *)(s0 + 0x32) = 0x1FF;
        *(u8 *)(s0 + 0x30) = 0xFF;
        *(f32 *)(s0 + 0x10) = 512.0f;
        *(f32 *)(s0 + 0x14) = 512.0f;
        *(f32 *)(s0 + 0x18) = 512.0f;
        D_L10_001B1648 = func_L00_002FCF18(s0 + 0x10, 40.0f, v, v, v, 1.0f);
    case 1:
        *(f32 *)(s0 + 0xF8) =
            func_00283B98(*(f32 *)(s0 + 0xF8), 0.011780974f);
        break;
    default:
        break;
    }
    func_L00_002E6EF8(D_L10_0042BEE0, s0);
}
