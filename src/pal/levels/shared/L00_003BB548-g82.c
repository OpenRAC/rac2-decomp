#include "include_asm.h"

#include "common.h"
extern void func_0029FCC0(void *, int, void *);
extern int func_00282948(char *);
extern char D_00189E20[];
extern void func_002FDF40(void *, void *, int, int, float, float, float, float);
extern int func_PAL_002FF5F8(void *, void *, void *, void *, void *, char **, int *, float);
extern int func_00300540(int);
extern void func_002FE8D8(void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_L00_002D3F30(int, int);
extern int func_002B0CE0(int, int, int);
extern void func_PAL_L00_002AF458(void);
extern void func_PAL_L00_002AF6C0(void);
extern void func_002E5CF8(int, int, void *);
extern char *func_L00_003DE088(void *, void *);
extern void ref_L00_003B7D48_00(void (*)(void *), void *);
extern void func_PAL_L00_003BBD00(void *);
typedef struct OBJ2 {
    char pad0[0x28];
    int f28;
    char pad1[0x68 - 0x2C];
    struct OBJ2 *f68;
} OBJ2;
extern OBJ2 *D_L00_001AFBC0 __attribute__((sda));
extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001A8F08 MACRO_ADDR;
extern int D_L00_001A8FF4 MACRO_ADDR;
extern int D_00138324 NOT_SDA;

void func_PAL_L00_003BB8F0(char *m) {
    float pos[4], sweep_storage[4], normal[4];
    float *sweep;
    char *hit;
    int aux;
    char *d = *(char **)(m + 0x68);
    int result, state, ready;
    float height;

    {
        char *g = D_00189E20;

        if (*(int *)(g + 0x1244) == 3)
            D_L00_001AFBC0 = 0;
        func_0029FCC0(m, 0, pos);
        *(int *)(d + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(g + 0x2294) == 29) ? 11.0f : 4.5f;
        func_002FDF40(sweep, pos, 0, 0, 1.6f, height, 0.16000001f, 0.0044f);
    }
    *(int *)(d + 0x24) = func_PAL_002FF5F8(pos, sweep, d, d + 0x10, m, &hit, &aux, 0.0044f);
    result = func_00300540(aux);
    if (D_L00_001A8F00 || D_L00_001A8F08 != -2)
        *(int *)(d + 0x2C) = 1;
    if (D_L00_001A8FF4 && *(float *)(d + 8) < 462.42999267578125f)
        *(int *)(d + 0x2C) = 1;
    if (result || !*(int *)(d + 0x24) || !*(int *)(d + 0x28))
        goto blocked;
    {
        char *g = D_00189E20;

        state = *(int *)(g + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(g + 0x33C) && (*(short *)(*(char **)(g + 0x33C) + 0xAA) == 0x330 ||
                                      *(short *)(*(char **)(g + 0x33C) + 0xAA) == 0xB21))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 || *(short *)(hit + 0xAA) == 0xB5B))
            goto blocked;
    }
    func_002FE8D8(d, normal);
    if (!(func_00282DB0(d + 0x10, normal) < 0.75f))
        goto timer;
blocked:
    *(int *)(d + 0x2C) = 1;
timer:
    {
        char *g = D_00189E20;

        ready = 1;
        if (*(int *)(g + 0x2294) == 29) {
            if (!func_00282948(g + 0x2534))
                ready = 0;
        } else
            *(int *)(g + 0x2534) = 33;
    }
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        D_L00_001AFBC0 = (OBJ2 *)m;
        *(unsigned char *)(m + 0x20) = 1;
        *(int *)(d + 0x28) = 1;
        *(int *)(d + 0x24) = 0;
        /* falls through */
    case 1: {
        char *g = D_00189E20;

        if ((D_00138324 & *(int *)(g + 0x1230)) && !*(unsigned char *)(g + 0x22BC) &&
            !*(int *)(d + 0x2C) && ready) {
            if (func_L00_002D3F30(-1, 1)) {
                *(short *)(g + 0x1E0) = 120;
                func_002B0CE0(6, 0, 1);
                *(short *)(g + 0x1D2) = 0;
                func_PAL_L00_002AF458();
                *(unsigned char *)(m + 0x20) = 2;
                *(int *)(d + 0x20) = 10;
                *(int *)(d + 0x28) = 0;
            } else
                func_002E5CF8(0, 0, m);
        }
        break;
    }
    case 2:
        if (func_00282948(d + 0x20)) {
            char *p = func_L00_003DE088(pos, sweep);

            if (p)
                *(char **)(p + 0xB8) = m;
            func_002E5CF8(1, 0, m);
            func_PAL_L00_002AF6C0();
            *(unsigned char *)(m + 0x20) = 3;
            *(int *)(d + 0x20) = 4;
        }
        break;
    case 3:
        if (func_00282948(d + 0x20))
            *(unsigned char *)(m + 0x20) = 1;
        break;
    }
    ref_L00_003B7D48_00(func_PAL_L00_003BBD00, m);
}
