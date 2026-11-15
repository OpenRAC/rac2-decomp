#include "common.h"

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern float ref_L04_00432258_00(float);
extern int ref_L04_00432258_01(int, float);
extern void ref_L04_00432258_02(float *, char *, char *);
extern char ref_L04_00432258_03[];
extern void ref_L04_00432258_04(float *, float *, float);
extern float ref_L04_00432258_05(char *, float *);
extern void ref_L04_00432258_06(float *);
extern void ref_L04_00432258_07(float *, float, char *, int, float, int, int, int, int, int);

/* Pulsing glow marker: spins a phase stored in its record, derives a pulsing alpha from it and, while the distance test passes, spawns a 0xC0-tick light effect with that colour. */
void func_L04_00432258(char *obj) {
    float lightData[8];
    float *vars = FLD(obj, float *, 0x68);
    float intensity;
    float sum;
    float one;
    int color;

    if (vars == 0) {
        return;
    }
    switch (FLD(obj, u8, 0x20)) {
    case 0:
        FLD(obj, u8, 0x30) = 0xFF;
        vars[1] = 0.03490658849477768f;
        vars[0] = 0;
        FLD(obj, u8, 0x20) = 1;
        return;
    case 1:
        break;
    default:
        return;
    }
    sum = vars[0] + vars[1];
    vars[0] = sum;
    if (sum >= 6.2831855f) {
        vars[0] = sum - 6.2831855f;
    }
    one = 1.0f;
    FLD(obj, int, 0x78) = ref_L04_00432258_01(0x7F, ref_L04_00432258_00(vars[0]) * 0.5235987901687622f + 0.5235987901687622f);
    ref_L04_00432258_02(lightData, ref_L04_00432258_03, obj + 0x10);
    ref_L04_00432258_04(lightData, lightData, one);
    intensity = ref_L04_00432258_05(obj + 0xC0, lightData);
    if (!(intensity < 0)) {
        color = (FLD(obj, int, 0x78) & 0xFFFFFF) | ((int)(intensity * 127.0f) << 24);
        ref_L04_00432258_06(&lightData[4]);
        ref_L04_00432258_07(&lightData[4], 105000.0f, obj, color, one, -1, 1, 2, 0, 0xC0);
    }
}
