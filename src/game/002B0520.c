#include "include_asm.h"
#include "common.h"

typedef int TI __attribute__((mode(TI)));

extern u8 *D_001B1A20 MACRO_ADDR;
extern f32 D_001B19E0[] __attribute__((sda));
extern f32 D_001B1A10 MACRO_ADDR;
extern f32 D_001B1A14 MACRO_ADDR;
extern f32 D_001B1A18 MACRO_ADDR;
extern s32 D_001A91C0 MACRO_ADDR;
extern s32 D_001C4F40;

extern void func_00282CF0(void *, void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);

float func_002B0520(TI *pos) {
    float p[4] __attribute__((aligned(16)));
    float rel[4] __attribute__((aligned(16)));
    s32 idx;
    u8 h;

    *(TI *)p = *pos;
    if (D_001B1A20 == 0) {
        return 0.0f;
    }
    FastVecSub(rel, p, D_001B19E0);
    rel[0] = rel[0] / D_001B1A10;
    rel[1] = rel[1] / D_001B1A14;
    if (rel[0] < 0.0f || 256.0f < rel[0] || rel[1] < 0.0f || 256.0f < rel[1] || D_001A91C0 != D_001C4F40) {
        return 1023.0f;
    }
    idx = FloatToInt(rel[1]) << 8;
    idx += FloatToInt(rel[0]);
    h = D_001B1A20[idx];
    if (h == 0xFF) {
        return 1023.0f;
    }
    return IntToFloat(h) * D_001B1A18 + D_001B19E0[2];
}
