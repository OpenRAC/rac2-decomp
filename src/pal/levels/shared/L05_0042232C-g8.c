#include "include_asm.h"

extern int D_001A79F0;
extern float func_00282E48(void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern void func_L05_0037AB88(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern int D_L05_001B1348 __attribute__((sda));
extern void func_PAL_L05_004225D0(char *);

void func_PAL_L05_0042232C(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1348 != 0) {
        scale = func_00282E48((void *)(D_L05_001B1348 + 0x10), object + 0x10);

        if (D_001A79F0 == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.012800001f, 0.0048f, 1.2800001f);
            goto check_scale;
        }
        if (scale < 6e+01f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.3f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            func_002AA458(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.008f, 0.0024f, 0.6f);
        }
    check_scale:
        if (scale < 0.5f) {
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_L05_0037AB88(1, 10);
            func_PAL_0029D5E8(0x1286, 10, -1);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_PAL_L05_004225D0(object);
}
