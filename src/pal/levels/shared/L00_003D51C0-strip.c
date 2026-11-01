#include "include_asm.h"

#include "common.h"
extern short D_L00_001B2AE0[] __attribute__((sda));
extern short D_L00_001B2AF0[] __attribute__((sda));
extern short D_L00_001B2B00[] __attribute__((sda));
extern short D_L00_001B2B10[] __attribute__((sda));
extern char D_L00_00247310[];
extern char D_L00_00247350[];
extern char D_0018A580[];
extern void func_00282D30(void *, void *, float);
extern float func_002A7878(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern void func_002A7A00(void *, float, float);

/* Resets the strip tables, then aims strips 4 and 5 from position: the D_0018A580 axis scaled
   by 32, turned by a random 10 to 24 degrees about D_0018A580 - 0x20 and by a random 22 to 30
   degrees (mirrored for strip 5) about D_0018A580 - 0x10; the three inner points are
   interpolated between the ends and jittered. */
void func_PAL_L00_003D6C38(void *object, void *position, int unused)
{
    char delta[16] __attribute__((aligned(16)));
    char end[16] __attribute__((aligned(16)));
    char jitter[16] __attribute__((aligned(16)));
    int i, j, k;
    float angle, t;

    for (k = 0; k < 4; k++)
        D_L00_001B2AE0[k] = -1;

    D_L00_001B2B00[0] = 8;
    D_L00_001B2B10[0] = 4;
    D_L00_001B2B00[1] = 4;
    D_L00_001B2B10[1] = 2;
    D_L00_001B2B00[2] = 8;
    D_L00_001B2B10[2] = 4;
    D_L00_001B2B00[3] = 4;
    D_L00_001B2B10[3] = 2;
    D_L00_001B2B00[4] = 8;
    D_L00_001B2B10[4] = 4;
    D_L00_001B2B00[5] = 4;
    D_L00_001B2B10[5] = 3;

    for (i = 4; i < 6; i++) {
        D_L00_001B2AE0[i] = 7;
        D_L00_001B2AF0[i] = 255;

        qcopy(D_L00_00247310 + i * 80, position);
        func_00282D30(delta, D_0018A580, 32.0f);
        func_002ACEC0(delta, delta, D_0018A580 - 32, -(func_002A7878(10.0f, 24.0f) * 0.017453294f));
        angle = func_002A7878(22.0f, 30.0f) * 0.017453294f;
        if (i == 5)
            func_002ACEC0(delta, delta, D_0018A580 - 16, -angle);
        else
            func_002ACEC0(delta, delta, D_0018A580 - 16, angle);

        func_00282CC0(end, position, delta);
        qcopy(D_L00_00247350 + i * 80, end);
        for (j = 1; j < 4; j++) {
            t = func_00283CE0(j) / func_00283CE0(4);
            func_00282D08(D_L00_00247310 + i * 80 + j * 16, position, end, t);
            func_002A7A00(jitter, t * 2.0f, t * 2.0f);
            func_00282CC0(D_L00_00247310 + i * 80 + j * 16, D_L00_00247310 + i * 80 + j * 16, jitter);
        }
    }
}
