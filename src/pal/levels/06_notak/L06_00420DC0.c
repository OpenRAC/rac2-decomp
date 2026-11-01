#include "include_asm.h"


INCLUDE_ASM("asm/pal/levels", func_PAL_L06_00422184);

INCLUDE_ASM("asm/pal/levels", func_PAL_L06_00423250);

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DF0(float *);
extern void func_00282F20(float *, float *, float);
extern int func_002A7EA0(char *, char *, char *, int, float, float, float, float);
extern float func_002AA2E8(float *, float, float);
extern void func_002AA548(float *, char *, float, float, float, float);
extern void func_002AAA00(char *, float, float, float, float, char *, int);
extern float func_00283C80(float, float);
extern int func_L02_0032E998(char *, int, float *, char *, int, char *, char *, float,
                             float);
extern void func_00282CC0(void *, void *, void *);

/* Turns the actor toward its target and keeps the two angles it stores at +0x470 and
   +0x474 of its state; returns 1 when the actor's state changed. */
int func_PAL_L06_004235E8(char *a0, char *a1, float f1, float f2, float f3, float f4)
{
    char *st = *(char **)(a0 + 0x68);
    float v[4];
    float w[4];
    float x[4];
    float d = 0.0f;
    float out;
    float f24;
    float t;
    int ret = 0;

    func_00282CF0(v, (float *)a1, (float *)(a0 + 0x10));
    v[2] = 0.0f;
    f24 = func_00282DF0(v);
    t = f2 * 0.0012f;
    if (f3 < f24) {
        int c = *(int *)(st + 0x480);

        out = 0.0f;
        func_L02_0032E998(a0 + 0x10, (int)a1, &out, st + 0x260, c, st + 0x488,
                          st + 0x48C, f4, 0.5f);
        func_002AAA00(a0 + 0xF8, out, 0.005445428f,
                      0.005445428f, 0.35604724f, st + 0x474, 0);
        if (func_00283C80(*(float *)(a0 + 0xF8), out) < 1.3089970350265503f) {
            func_002AA548(&d, st + 0x470, f24, t, t, f2 * 0.020000001f);
        } else {
            *(float *)(st + 0x470) = 0.0f;
        }
    } else {
        func_002AAA00(a0 + 0xF8, f1, 0.005445428f,
                      0.005445428f, 0.35604724f, st + 0x474, 0);
        func_002AA2E8((float *)(st + 0x470), 0.0f, t);
        if (*(float *)(st + 0x470) == 0.0f) {
            if (func_00283C80(*(float *)(a0 + 0xF8), f1) < 0.0872664749622345f) {
                *(float *)(st + 0x474) = 0.0f;
                ret = 1;
            }
        }
    }
    func_00282F20(w, (float *)(a0 + 0xC0), *(float *)(st + 0x470));
    func_00282CC0(x, w, (float *)(a0 + 0x10));
    if (func_002A7EA0(a0, a0 + 0x10, (char *)x, 0, 0.8999999761581421f, 1.0f, 0.5f,
                     0.7853982448577881f) == 0) {
        *(int *)(st + 0x5A8) = *(int *)(st + 0x5A8) + 1;
    }
    /* The counter at +0x5A8 wraps at 0x14, and the actor then reports the change. */
    if (*(int *)(st + 0x5A8) < 0x14) {
        goto done;
    }
    *(int *)(st + 0x5A8) = 0;
    ret = 1;
done:
    return ret;
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L06_004238A0);
