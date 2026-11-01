#include "include_asm.h"

#include "common.h"
extern void ref_L00_003DC3E0_00(int, int, char *);
extern void ref_L00_003DC3E0_01(float *, char *, float);
extern void ref_L00_003DC3E0_02(float *, char *, char *);
extern void ref_L00_003DC3E0_03(float *, char *, float *);
extern void ref_L00_003DC3E0_04(float *, char *, float);
extern struct C3PairGlobal { int x[2]; } ref_L00_003DC3E0_05;
extern void ref_L00_003DC3E0_06(float *, float *, char *, float);
extern int ref_L00_003DC3E0_07(void);
extern unsigned char *ref_L00_003DC3E0_08(float *, float *, int, int, float);
extern float ref_L00_003DC3E0_09(float, float);
extern float ref_L00_003DC3E0_10(int);
extern int ref_L00_003DC3E0_11(int, int);
extern unsigned char *ref_L00_003DC3E0_12(char *, float *, float, int, int);
extern float func_002A7940(void);

/* func_L00_003DBF50 lives in L00_003D37E8-g8.c. */



void func_PAL_L00_003E05B0(char *object, int unused, char *pos, char *direction)
{
    float a[4], b[4], c[4], d[4];
    struct C3PairGlobal colors;
    float e[4];
    char *state = *(char **)(object + 0x68);
    float angle, scale;
    int i;
    ref_L00_003DC3E0_00(0, 0, object);
    ref_L00_003DC3E0_01(a, direction, 2.0f);
    ref_L00_003DC3E0_02(a, a, pos);
    ref_L00_003DC3E0_03(d, pos, a);
    ref_L00_003DC3E0_01(b, direction, 0.15f);
    ref_L00_003DC3E0_02(b, pos, b);
    ref_L00_003DC3E0_01(d, d, 1.0f);
    ref_L00_003DC3E0_04(c, direction, 0.0009765625f);
    ref_L00_003DC3E0_01(c, c, 1.0f);
    colors = ref_L00_003DC3E0_05;
    angle = func_002A7940();
    i = 23;
    do {
        ref_L00_003DC3E0_06(e, d, direction, angle);
        --i;
        ref_L00_003DC3E0_08(b, e, colors.x[ref_L00_003DC3E0_07() % 2], 17, 0.050000004f);
        angle = ref_L00_003DC3E0_09(angle, 0.2731819748878479f);
    } while (i >= 0);
    for (i = 0; i < 24; i++) {
        scale = ref_L00_003DC3E0_10(i) * 0.06521739065647125f;
        {
            int *color = &colors.x[ref_L00_003DC3E0_07() % 2];
            int n = ref_L00_003DC3E0_11(25, 42);
            ref_L00_003DC3E0_12(pos, c, scale, *color, n);
        }
    }
    qcopy(state, c);
}

