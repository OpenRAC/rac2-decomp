#include "include_asm.h"


#include "common.h"
extern u8 D_L07_001B31AF __attribute__((sda));
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 D_L07_00189E20[];
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern s32 D_L07_001B22F8[] __attribute__((sda));
extern s32 func_002A77E0(s32 n);
extern s32 func_00282948(s32 *counter);
extern u8 *func_L07_003F6B88(u8 *a);
extern u8 D_001A7BD0 __attribute__((sda));
extern void func_002A7A00(void *a, f32 b, f32 c);
extern f32 func_00282C48(f32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern void func_L00_00324F18(void *a, void *b, f32 c, f32 d, f32 e);
extern void func_PAL_002C84A8(void *a, void *b, s32 c);
extern f32 D_L07_001AA698 __attribute__((sda));
extern f32 D_L07_001B3198 __attribute__((sda));
extern f32 func_2E4508(void *a, void *b);

/* Runs the object's own 200 steps: each step advances the shared record's third
   float, then the three angles are computed and handed to the shared passes. */
void func_PAL_L07_0040D030(u8 *a0)
{
    f32 v[4];
    f32 buf[4];
    s32 i;
    f32 f14;
    f32 f20;
    f32 f21;

    D_L07_001B3198 = D_L07_001AA698;
    D_L07_001AA698 = 0.99f;
    for (i = 0xC7; i >= 0; i--) {
        func_002A7A00(buf, 0.020000001f, 0.28000003f);
        buf[2] = func_00282C48(buf[2]) + 0.10000001f;
        f21 = func_002A7878(-5.0f, 5.0f);
        f20 = func_002A7878(-5.0f, 5.0f);
        f14 = func_002A7878(10.0f, 25.0f);
        func_L00_00324F18(a0, v, f21, f20, f14);
        func_PAL_002C84A8(v, buf, 0x190);
    }
}

