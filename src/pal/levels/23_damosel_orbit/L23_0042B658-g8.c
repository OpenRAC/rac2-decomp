#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L23_001B19FC __attribute__((sda));
extern s32 D_L23_001B3918[5] MACRO_ADDR;
extern u8 D_L23_001BA500[];
extern void *func_0029EFD0(s32);
extern float func_002A78D8(float, float);
extern s32 func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L05_0042E518(void *);

/* spawns object 0x11DF at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L23_001BA500 + 0x140 */
void *func_PAL_L23_0042B658(u8 *pos, u8 *parent, s32 flag, float scale, s32 a3, s32 a4, s32 a5,
                        s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *obj;
    u8 *vars;
    float angle;

    if (D_L23_001B19FC == -1.0f) {
        for (i = 0; i < 5; i++) {
            D_L23_001B3918[i] = 0;
        }
        D_L23_001B19FC = 0.0f;
    }
    if (D_L23_001B19FC >= 5.0f) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (D_L23_001B3918[i] == 0) {
            break;
        }
    }
    D_L23_001B19FC += 1.0f;
    D_L23_001B3918[i] = 1;
    obj = func_0029EFD0(0x11DF);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        qcopy(obj + 0xC0, parent + 0xC0);
        qcopy(obj + 0xD0, parent + 0xD0);
        qcopy(obj + 0xE0, parent + 0xE0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = a3;
        *(s32 *)(vars + 0x24) = a4;
        *(s32 *)(vars + 0x28) = a5;
        *(s32 *)(vars + 0x2C) = a6;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = a7;
        *(s32 *)(vars + 0x34) = a9;
        *(s32 *)(vars + 0x48) = a12;
        *(s16 *)vars = 0x32;
        *(s16 *)(vars + 2) = 0x32;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = a10;
        *(s32 *)(vars + 0x38) = a11;
        *(s32 *)(vars + 0x18) = a8;
        *(float *)(vars + 0x44) = func_002A78D8(65.0f, 80.0f);
        qcopy(&sphere, obj + 0x10);
        ((float *)&sphere)[3] = scale * 3.0f;
        if (func_00283DB8(&sphere, 128.0f) == 1) {
            *(s16 *)(vars + 4) = 0x15;
            *(float *)(vars + 0x10) = 0.04761905f;
            if (func_00282E48(pos, D_L23_001BA500 + 0x140) < 48.0f && flag != 0) {
                u8 *ref = D_L23_001BA500;
                *(s32 *)(ref + 0x16C) = 0;
                *(s32 *)(ref + 0x168) = 0x21;
                *(float *)(ref + 0x160) = 0.075f;
            }
            if (*(s32 *)(vars + 0x18) != 0) {
                func_00282CF0(&dir, obj + 0x10, D_L23_001BA500 + 0x140);
                func_00282F20(&dir, &dir, 1.0f);
                angle = func_002831B0(func_00282DB0(&dir, D_L23_001BA500 + 0x370));
                if (1.5707964f - angle < 0.45378566f) {
                    *(s32 *)(vars + 0x18) = 1;
                } else {
                    *(s32 *)(vars + 0x18) = 0;
                }
            }
        } else {
            *(s16 *)(vars + 4) = 0;
            *(s32 *)(vars + 0x18) = 0;
        }
        func_PAL_L05_0042E518(obj);
    }
    return obj;
}
