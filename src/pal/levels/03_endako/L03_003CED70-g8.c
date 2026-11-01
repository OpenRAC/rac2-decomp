#include "include_asm.h"

#include "common.h"
extern f32  D_L03_001B0340 __attribute__((sda));
extern s32  func_31BA30(s32 a0, s32 a1);
extern s32  func_31B9F0(s32 a0);
extern f32  func_2F0000(f32 a0, f32 a1);
extern void func_L03_003CAD78(char *a0);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern void func_L00_002E6CF0(void *fn, void *entity);
extern f32  func_2EF670(f32 a0, f32 a1);
extern f32  func_2EF110(f32 *a0);
extern f32 D_L03_001B0350[] SDATA(D_L03_001B0350);
extern f32 D_L03_001B0648 __attribute__((sda));
extern u32 D_L03_001B3458;
extern s32  func_002B38B8(char *a0);
extern s32  func_002E5CF8(s32 a0, s32 a1, char *a2);
extern u8  *D_L03_001B2A1C;
extern u8   D_00188660[];
extern s32  D_L03_001B0438 __attribute__((sda));
extern f32  D_L03_001B043C __attribute__((sda));
extern s32  D_L03_001B0674 __attribute__((sda));
extern s32  func_002A8AF0(char *a0, void *a1, u32 a2);
extern f32  func_00282DF0(f32 *a0);
extern f32 func_002AAA00(char *a0, f32 *a1, f32 a3, f32 a4, f32 a5, f32 a6, s32 a2);

/* case 0 makes the object opaque and moves it to state 1; case 1 scrolls the three
   offsets in its vars by the table's rates per frame (wrapping below -1) and queues
   its draw callback with the object as argument (AddDrawCallback in rac1-decomp) */
void func_PAL_L03_003CED70(char *a0)
{
    s32 state = *(u8 *)(a0 + 0x20);
    char *s0 = *(char **)(a0 + 0x68);

    switch (state) {
    case 0:
        *(u8 *)(a0 + 0x30) = 0xFF;
        func_002A7750(a0, 1, -1);
        *(s32 *)(s0 + 0xC) = 1;
        break;
    case 1: {
        f32 *dst = (f32 *)s0;
        f32 *src = &D_L03_001B0350[0];
        s32 i;

        for (i = 2; i >= 0; i--) {
            f32 f = *dst - *src * 0.020000001f;

            *dst = f;
            if (f < -1.0f)
                *dst = f + 1.0f;
            src++;
            dst++;
        }
        func_L00_002E6CF0(func_L03_003CAD78, a0);
        break;
    }
    }
}
