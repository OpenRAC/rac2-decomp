#include "include_asm.h"

#include "common.h"
extern void func_002A7750(unsigned char *, int, int);
extern float func_00283B98(float, float);
extern float func_00282DF0(void *);
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_0036AE00(int, int);
extern int D_L07_001C9780 __attribute__((nosda));
extern unsigned short **D_L07_001A9014;
extern unsigned char *D_L07_001B295C;
extern float D_L07_001AEBF8[] SDATA(D_L07_001AEBF8);
typedef struct {
    int groups[3];
    float angles[3];
} RotState;

void func_PAL_L07_0037B4C0(unsigned char *a0)
{
    RotState *state = *(RotState **)(a0 + 0x68);
    int i;
    unsigned short *p;
    unsigned char *e;
    float v[4];
    float loc[3];
    float *q;
    int k;
    int m;
    float t;
    float ang;

    switch (a0[0x20]) {
    case 0:
        a0[0x30] = 0xFF;
        func_002A7750(a0, 1, -1);
        break;
    case 1:
        if (D_L07_001C9780 != 0)
            return;
        for (i = 0; i < 3; i++) {
            if (state->groups[i] == -1) {
                continue;
            }
            /* The transfer helper also preserves the original address recomputation. */
            qzero_nc(v);
            ang = func_00283B98(state->angles[i], D_L07_001AEBF8[i] * 0.0003490659f);
            state->angles[i] = ang;
            v[2] = ang;
            for (p = D_L07_001A9014[state->groups[i]];
                 p != 0 && ((short)p[-1] >= 0 || p == D_L07_001A9014[state->groups[i]]);
                 p++) {
                e = D_L07_001B295C + ((*p & 0x7FFF) << 6);
                if (e == 0)
                    break;
                q = loc;
                for (k = 0; k < 3; k++)
                    q[k] = *(float *)(e + 0xC + k * 16);
                t = func_00282DF0(e);
                func_002833F0(e, v);
                func_00282F20(e, e, t);
                func_00282F20(e + 0x10, e + 0x10, t);
                for (m = 0; m < 3; m++)
                    *(float *)(e + 0xC + m * 16) = q[m];
                func_L00_0036AE00(*p & 0x7FFF, 1);
            }
        }
        break;
    }
}
