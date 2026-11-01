#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F449178;
extern s32 D_L20_001B23A0 __attribute__((sda));
extern s32 D_L20_001B23A8 __attribute__((sda));
extern s32 D_L20_001B23B0 __attribute__((sda));
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern void func_L00_0033E220(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern s32 func_PAL_L00_0032C328(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L01_0031A278(char *, void *, float, float, float);
extern void func_PAL_L00_003FB330(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_L00_00326620(char *, s32, s32);
extern void func_0029F338(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then plays the burst and retires. */
void func_PAL_L20_0044EDF0(char *obj)
{
    V4_F449178 v;
    s32 *rec = *(s32 **)(obj + 0x68);

    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        v.q = 0;
        v.f[2] = 2.0f;
        func_L00_0033E220(&v, obj, 0x40204080, -1, 420000.0f, 1.0f, 1, -1, 0, -1);
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (func_002A9640(obj, 0x04010000, 0) != 0 && *rec == 0)
            func_002A7750(obj, 2, -1);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        func_PAL_L00_0032C328(obj, &D_L20_001B23B0, &D_L20_001B23A8, &D_L20_001B23A0, 0xFFFF, 0, -1, 0, 0xFFFF, 0xFF, 0);
        func_L01_0031A278(obj, &v, 0.0f, 0.0f, 2.0f);
        func_PAL_L00_003FB330(&v, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        func_L00_00326620(obj, 0x126A, 0);
        func_0029F338(obj);
        return;
    }
}
