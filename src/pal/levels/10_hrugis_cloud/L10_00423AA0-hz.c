/* func_PAL_L10_00423AA0, the PAL copy of func_L10_0041EC10: the same C with the per-frame phase
   step 2*pi/60 becomes 2*pi/50 (0.12566373f); the callee is PAL's func_PAL_L10_00423BE0, and the
   8-byte callback is catalogued in PAL as func_L00_00410D18. */
#include "common.h"

extern u32 *func_0037BA88(u8 *arg0);
extern f32 func_00335320(void);
extern u8 *func_0037B670();
extern void func_0037BC48(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern s32 func_0037D390(u8 *arg0, s32 a1, s32 a2, s32 a3);
extern f32 func_00309120(f32 f12);

extern f32 func_00309B38(f32 f12, f32 f13);
extern u8 func_L10_00423780(void);
extern s32 func_00283D38(s32 a0, s32 a1, f32 f12);
extern void func_L00_00410D18(void);
extern void func_L10_0041EE00(u8 *arg0);
extern s32 D_001A79F0[] __attribute__((sda));

extern void func_PAL_L10_00423BE0(u8 *arg0);
void func_PAL_L10_00423AA0(u8 *arg0) {
    u8 *s1 = *(u8 **)(arg0 + 0x68);
    f32 f;
    u8 *p;
    s32 mode;

    switch (arg0[0x20]) {
    case 0:
        arg0[0x30] = 0xFF;
        if (func_0037B670() != 0) {
            func_PAL_L10_00423BE0(arg0);
            if (*(s32 *)(s1 + 0x264) != 0) {
                func_0037BC48(arg0, (s32)func_L00_00410D18, (s32)func_L10_0041EE00, 0);
            }
            *(f32 *)(s1 + 0x268) = func_00335320();
        }
        break;
    case 1:
        p = func_0037BA88(arg0);
        mode = D_001A79F0[0];
        *(s32 *)((u8 *)p + 0x14C) = 0;
        if (mode == 10 && func_L10_00423780() == 2) {
            *(u16 *)(arg0 + 0x34) |= 0x1000;
        } else {
            *(u16 *)(arg0 + 0x34) &= 0xEFFF;
        }
        func_0037D390(arg0, 0, 0, 0);
        f = func_00309B38(*(f32 *)(s1 + 0x268), 0.12566373f);
        *(f32 *)(s1 + 0x268) = f;
        *(s32 *)(arg0 + 0x78) = func_00283D38(0x20202020, -1, (func_00309120(f) + 1.0f) * 0.5f);
        break;
    }
}
