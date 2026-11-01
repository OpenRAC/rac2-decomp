#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F41A4C0;
extern s32 D_L17_001B1EE0 __attribute__((sda));
extern s32 D_L17_001B1EE8 __attribute__((sda));
extern s32 D_L17_001B1EF0 __attribute__((sda));
extern s32 D_L17_001B1F10 __attribute__((sda));
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern void func_L17_00326F38(char *, void *, float, float, float);
extern void func_L00_0033E220(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern void func_PAL_L00_0032C328(char *, s32 *, s32 *, s32 *, s32, s32, s32, s32, s32, s32, s32);
extern void func_L00_00324F18(char *, void *, float, float, float);
extern void func_PAL_L00_003FB330(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_0029F338(char *);

/* The func_L20_00449178 three-state effect for level 17: the start point is taken from the
   object (func_L17_00326F38) and the closing spray is sized by the object's scale.
   func_PAL_L00_0032C328 is void here: a value-returning prototype moves the 0xFFFF
   argument's load. */
void func_PAL_L17_0041FC60(char *obj)
{
    V4_F41A4C0 v;
    s32 *rec = *(s32 **)(obj + 0x68);

    v.q = 0;
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        func_L17_00326F38(obj, &v, 0.0f, 0.0f, 20.0f);
        func_L00_0033E220(&v, obj, 0x10008080, -1, 336000.0f, 0.75f, 1, -1, 0, 0x60);
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (func_002A9640(obj, 0x04010000, 0) != 0 && *rec == 0)
            func_002A7750(obj, 2, -1);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    case 2:
        func_PAL_L00_0032C328(obj, &D_L17_001B1EF0, &D_L17_001B1EE8, &D_L17_001B1EE0, 0xFFFF, 0, D_L17_001B1F10, 0, 0xFFFF, 0xFF, 0);
        func_L00_00324F18(obj, &v, 0.0f, 0.0f, 20.0f);
        func_PAL_L00_003FB330(&v, 0, 0xC, 0xA, *(float *)(obj + 0x2C) * 10.0f, 20.0f, 0xA, 0xA, 0, 0, 1, 0, 0, 0);
        func_0029F338(obj);
        return;
    }
}
