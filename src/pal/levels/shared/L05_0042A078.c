#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern void ref_L05_004247C8_00(char *, void *);
extern char ref_L05_004247C8_01[];
extern float ref_L05_004247C8_02(void);
extern float ref_L05_004247C8_03(float);
extern float ref_L05_004247C8_04(float);
extern void ref_L05_004247C8_05(float *, float *, char *);
extern void ref_L05_004247C8_06(float *, float *, char *);
extern int ref_L05_004247C8_07(float);
extern void ref_L05_004247C8_08(float *, int, int, int, float, float, float);
extern float ref_L05_004247C8_09(float, float);
extern float ref_L05_004247C8_10(float);

void func_PAL_L05_0042A078(char *obj) {
    float v[4];
    char *state;
    int color;
    int grey;
    int i;
    float full;

    full = 128.0f;
    grey = 0x808080;
    state = FLD(obj, char *, 0x68);
    ref_L05_004247C8_00(obj + 0x10, ref_L05_004247C8_01);
    for (i = 29; i >= 0; i--) {
        float angle = ref_L05_004247C8_02();
        v[0] = 0.0f;
        v[1] = ref_L05_004247C8_03(angle);
        v[2] = -ref_L05_004247C8_04(angle);
        ref_L05_004247C8_05(v, v, obj + 0xC0);
        ref_L05_004247C8_06(v, v, obj + 0x10);
        ref_L05_004247C8_08(v, 0x13, (ref_L05_004247C8_07(full) << 24) | grey, 1, 0.25f, 0.1f, ref_L05_004247C8_02());
        {
            float half = 0.5f;
            int alpha = ref_L05_004247C8_07(full * half);
            color = FLD(state, int, 8);
            color &= 0xFFFFFF;
            color |= alpha << 24;
            ref_L05_004247C8_08(v, 0x13, color, 1, half, 0.1f, ref_L05_004247C8_02());
        }
    }
    FLD(state, float, 4) = 0.16057032f;
    FLD(state, float, 0) = ref_L05_004247C8_09(FLD(state, float, 0), 0.16057032f);
    ref_L05_004247C8_10(FLD(state, float, 0));
}

