#include "include_asm.h"

#include "common.h"
extern f32 D_L13_001AEBF0 __attribute__((sda));
extern f32 D_L13_001AEBD0 __attribute__((sda));
extern f32 D_L13_001AEBC8 __attribute__((sda));
extern f32 D_L13_001AEBC0 __attribute__((sda));
extern f32 D_L13_001AEBF4 __attribute__((nosda));
extern f32 D_L13_001AEBF8 __attribute__((nosda));
extern s32 func_002A9640(u8 *, s32, s32);
extern s32 func_002A7750(u8 *, s32, s32);
extern s32 func_0029F338(u8 *);
extern void func_L00_0033E220(float, float, void *, u8 *, s32, s32, s32, s32, s32, s32);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L01_0031A278(u8 *, f32 *, f32, f32, f32);
extern void func_PAL_L00_003FB330(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                        float, float);

void func_PAL_L13_0038F348(u8 *a0) {
    s32 *s1 = *(s32 **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        func_L00_0033E220(210000.0f, 0.75f, &D_L13_001AEBF0, a0, 0x50204040, -1, 1, -1, 0, -1);
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (func_002A9640(a0, 0x4010000, 0) != 0 && *s1 == 0)
            func_002A7750(a0, 2, -1);
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        f32 buf[4];
        func_PAL_L00_0032C328(a0, &D_L13_001AEBD0, &D_L13_001AEBC8, &D_L13_001AEBC0,
                    0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        {
            f32 first = D_L13_001AEBF8;
            f32 x = D_L13_001AEBF0;
            f32 second = D_L13_001AEBF4;
            func_L01_0031A278(a0, buf, x, second, first);
        }
        func_PAL_L00_003FB330(buf, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0, 0.3f, 20.0f);
        func_0029F338(a0);
        break;
    }
    }
}
