#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_0043ECA0);

#include "common.h"
extern float func_00283B98(float, float);
extern int D_L18_001C9D40;
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void *func_002A9640(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);
extern void func_002A7750(void *, int, int);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern int D_L18_001C9D40;
extern float func_00283B98(float, float);
extern s32 func_002E59B0(void *, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void *func_002A9640(void *, s32, s32);
extern float func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);

void func_PAL_L18_0043F330(u8 *obj) {
    u8 *state;
    u8 *p;
    float f;

    if (D_L18_001C9D40 != 0) return;
    state = *(u8 **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(short *)(state + 0x24) = 0x12;
        *(float *)(state + 0x20) = 18.0f;
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (func_002E59B0(obj, *(s32 *)(state + 0x68)) == 0) {
            *(s32 *)(state + 0x68) = func_002E5CF8(0, 4, obj);
        }
        p = state + 0x50;
        *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.0003490659f);
        f = func_PAL_002AA108(obj, func_002A9640(obj, 0x230000, 0));
        if (f > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            func_PAL_002AC290(obj, p);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - f;
        }
        func_PAL_002AC3C0(obj, p);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_00441640);


