#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } V4_F38c810;
extern float D_L13_001A8F20;
extern void func_002A7750(char *, s32, s32);
extern s32 func_002A9640(char *, s32, s32);
extern void func_L00_0033E220(void *, char *, s32, s32, float, float, s32, s32, s32, s32);
extern void func_002E5CF8(s32, s32, char *);
extern void func_PAL_L00_003281C0(char *, s32, float);
extern void func_PAL_L00_003FB330(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern float func_00283B98(float, float);
extern void func_002833F0(void *, void *);
extern void func_PAL_002B15D8(char *, s32, float *, float, float, float, float, s32);
extern void func_0029F338(char *);

/* Three-state effect object: arms its emitter, waits for the trigger, then spins a burst of four sprites and retires. */
void func_PAL_L13_0038F5E0(char *obj)
{
    V4_F38c810 v;
    s32 *rec = *(s32 **)(obj + 0x68);
    s32 i;
    char *pos, *rot;

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
        func_002E5CF8(0, 0, obj);
        func_PAL_L00_003281C0(obj, 4, 0.0f);
        pos = obj + 0xC0;
        rot = obj + 0xF0;
        func_PAL_L00_003FB330(obj + 0x10, 0, 0x19, 0x14, 0.5f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 1, 0, 0);
        i = 3;
        do {
            i--;
            *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8), 1.5707964f);
            func_002833F0(pos, rot);
            func_PAL_002B15D8(obj, 0xF, &D_L13_001A8F20, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            *(short *)(obj + 0x7C) = 0;
        } while (i >= 0);
        func_0029F338(obj);
        return;
    }
}
