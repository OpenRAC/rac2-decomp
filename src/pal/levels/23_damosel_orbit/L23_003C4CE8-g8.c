#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_L23_001AFA64 __attribute__((sda));
extern char D_00189EA0[];
extern void func_0029FCC0(void *, int, void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_0029FC20(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern float func_002B04E0(void *, void *, int);
extern float func_002AAA00(void *, float, float, float, float, void *, int);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_PAL_002A0F68(void *);
extern void func_002A0F48(void *);
extern void func_00282D30(void *, void *, float);
extern void func_002B0408(void *, void *, void *);
extern int func_00282978(short *);
extern void func_00282CF0(void *, void *, void *);

void func_PAL_L23_003C4FC0(char *obj) {
    TI128 v0[1], v1[3], t[1], u[1], r3[3], r4[1];
    float fz0, fz1;
    char *state = *(char **)(obj + 0x68);
    float r;
    float a1;
    float b1;
    float c1;

    if (*(unsigned char *)(obj + 0x95) == 2 || *(short *)(state + 0x2A6) != 0)
        func_0029FCC0(obj, 1, *(char **)(state + 0x2A0) + 0x10);
    else
        func_002AF1D0(obj, *(char **)(state + 0x2A0), 1, 0);
    if (*(unsigned char *)(obj + 0x95) == 2) {
        if (*(short *)(state + 0x2A6) == 0)
            *(int *)(state + 0x2AC) = 0;
        func_00282CF0(v0, D_00189EA0, *(char **)(state + 0x2A0) + 0x10);
        r = func_002B04E0(*(char **)(state + 0x2A0), v0, 0);
        b1 = *(float *)(state + 0x68) + *(float *)(state + 0x68);
        a1 = *(float *)(state + 0x64);
        c1 = *(float *)(state + 0x6C);
        fz0 = 0;
        func_002AAA00(&fz0, r, a1, b1, c1, state + 0x2AC, 0);
        qzero_nc(t);
        ((float *)t)[2] = *(float *)(state + 0x2AC);
        func_002833F0(v1, t);
        func_00283738(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, v1);
        func_PAL_002A0F68(*(char **)(state + 0x2A0));
        *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
        func_002A0F48(*(char **)(state + 0x2A0));
        func_00282D30(u, state + 0x280, -1.0f);
        func_002B0408(*(char **)(state + 0x2A0) + 0xC0, u, 0);
        *(short *)(state + 0x2A6) = ((s32)(D_L23_001AFA64) * 5 + 2) / 6;
        return;
    }
    {
        short v = *(short *)(state + 0x2A6);

        if (v != 0) {
            if (v == ((s32)(D_L23_001AFA64) * 5 + 2) / 6)
                *(int *)(state + 0x2AC) = 0;
            *v0 = 0;
            ((float *)v0)[0] = 1.0f;
            ((float *)v0)[3] = 1.0f;
            func_0029FC20(obj, 1, v1);
            qzero_nc(t);
            func_00283098(v0, v0, v1);
            r = func_002B04E0(*(char **)(state + 0x2A0), v0, 0);
            a1 = *(float *)(state + 0x64) + *(float *)(state + 0x64);
            c1 = *(float *)(state + 0x6C);
            b1 = *(float *)(state + 0x68) * 4.0f;
            fz1 = 0;
            func_002AAA00(&fz1, r, a1, b1, c1, state + 0x2AC, 0);
            qzero_nc(u);
            ((float *)u)[2] = *(float *)(state + 0x2AC);
            func_002833F0(r3, u);
            func_00283738(*(char **)(state + 0x2A0) + 0xC0, *(char **)(state + 0x2A0) + 0xC0, r3);
            func_PAL_002A0F68(*(char **)(state + 0x2A0));
            *(unsigned short *)(*(char **)(state + 0x2A0) + 0x34) |= 0x106;
            func_002A0F48(*(char **)(state + 0x2A0));
            func_00282D30(r4, state + 0x280, -1.0f);
            func_002B0408(*(char **)(state + 0x2A0) + 0xC0, r4, 0);
            func_00282978((short *)(state + 0x2A6));
        }
    }
}
