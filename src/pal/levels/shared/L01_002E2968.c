#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern float ref_L01_002E1680_00(float, float);
extern int ref_L01_002E1680_01(int, int, float);
extern void ref_L01_002E1680_02(float *, float, float);
extern void ref_L01_002E1680_03(float *, float *, float *);
extern char *ref_L01_002E1680_04(float, float *, float, float, float, int, float *, int, int);

/* Spawns count short-lived sparks at a position, each with a random spread, a direction from the matrix and a tint taken from the colour; optionally marks them with effect type 0x44. */
void func_PAL_L01_002E2968(float *a0, float *a1, int count, int color, int flag, float g, float h, float k) {
    float v[4];
    float spread;
    int tint;
    char *p;
    char *q;
    int i;

    for (i = 0; i < count; i++) {
        spread = h * ref_L01_002E1680_00(70000.0f, 150000.0f);
        tint = ref_L01_002E1680_01(0, color, ref_L01_002E1680_00(0.2f, 1.0f));
        ref_L01_002E1680_02(v, 0.0f, g);
        ref_L01_002E1680_03(v, v, a1);
        p = ref_L01_002E1680_04(h * 0.5f, a0, 1.0f, k, spread, 0, v, color, 0);
        if (p != 0) {
            FLD(p, s16, 0xA) = 0x64;
            q = p + 0x20;
            FLD(q, int, 4) = 2;
            FLD(q, u8, 0xA) = tint >> 24;
            FLD(q, u8, 0xB) = FLD(p, u8, 0xA);
            if (flag != 0) {
                FLD(p, u8, 3) = 0x44;
            }
        }
    }
}

