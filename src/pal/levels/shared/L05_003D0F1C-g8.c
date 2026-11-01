#include "include_asm.h"

extern int D_001A79F0;
extern float func_00282E48(void *, void *);
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern int func_002ED8A0(int);
extern int func_002A77E0(int);
extern int func_00288FB8(int);
extern void func_PAL_L00_0030FBC0(int, int);
typedef struct L05Slot40 {
    int state;
    int next;
    int pad08[2];
    int limit;
    int value;
    int pad18[4];
} L05Slot40;
extern L05Slot40 D_002A1800[];
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern int D_L05_001AFAA0 __attribute__((sda));
extern void func_PAL_L05_003D1248(char *);

void func_PAL_L05_003D0F1C(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001AFAA0 != 0) {
        scale = func_00282E48((void *)(D_L05_001AFAA0 + 0x10), object + 0x10);

        if (D_001A79F0 == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
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
            func_002AA458(object + 0x10, (void *)(D_L05_001AFAA0 + 0x10), state + 0x40,
                         0.008f, 0.0024f, 0.6f);
        }
    check_scale:
        if (scale < 0.5f) {
            int slot = func_002ED8A0(6);
            int add = D_002A1800[slot].limit;

            if (func_002A77E0(4) != 0) {
                func_PAL_L00_0030FBC0(func_00288FB8(0x1283), -1);
                add = 0x21;
            } else {
                func_PAL_L00_0030FBC0(func_00288FB8(0x1284), -1);
            }
            func_002E5DA0(0xC, 0, object, 0xFBF);
            D_002A1800[slot].value += add;
            if (D_002A1800[slot].limit < D_002A1800[slot].value)
                D_002A1800[slot].value = D_002A1800[slot].limit;
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.03f);
    func_PAL_L05_003D1248(object);
}
