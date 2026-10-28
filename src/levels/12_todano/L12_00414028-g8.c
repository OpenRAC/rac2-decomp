#include "common.h"

extern float func_002A7878(float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E80(void *, void *);
extern u8 D_00189E20[];
extern float D_L12_001B1844 __attribute__((sda));

void func_L12_00414028(u8 *obj) {
    u8 *st = *(u8 **)(obj + 0x68);
    u8 *target;
    u8 *g;
    u8 *g2;
    f32 tmp0[4] __attribute__((aligned(16)));
    f32 tmp1[4] __attribute__((aligned(16)));

    if (st[0x30F] != 0 && (target = *(u8 **)(st + 0x2F8)) != 0 && *(s16 *)(target + 0xAA) == 0x114B
        && target[0x20] != 0xFE && target[0x20] != 0xFD) {
        qcopy(tmp0, obj + 0x10);
        tmp0[2] += func_002A7878(0.0f, 1.0f);
        func_00282F20(tmp1, *(u8 **)(st + 0x2F8) + 0xC0, 4.0f);
        func_00282CC0(st + 0x1F0, tmp0, tmp1);
        return;
    }
    g = D_00189E20;
    if (*(int *)(st + 0x200) == *(int *)(g + 0x2290)) {
        if (D_L12_001B1844 < func_00282E80(obj + 0x10, g + 0x80)) {
            qcopy(st + 0x1F0, g + 0xD0);
        } else {
            qcopy(st + 0x1F0, g + 0xE0);
        }
        g2 = D_00189E20;
        if (*(int *)(g2 + 0x229C) == 0xC) {
            *(f32 *)(st + 0x1F8) += 0.2f;
        } else {
            *(f32 *)(st + 0x1F8) += 0.4f;
        }
    } else {
        qcopy(st + 0x1F0, *(u8 **)(st + 0x200) + 0x10);
        *(f32 *)(st + 0x1F8) += 0.8f;
    }
}
