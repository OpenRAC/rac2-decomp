#include "include_asm.h"

#include "common.h"
extern int Fc10c1216_FUN_00282978(char *);
extern void Fc10c1216_FUN_002B9180(char *);
extern int Fc10c1216_FUN_00283CF0(float);
extern void Fc10c1216_FUN_00282CC0(char *, char *, char *);

void part_update_glow_pulse_pal(char *p)
{
    float *q = (float *)(p + 32);

    if (0.0f < q[3])
        q[1] = q[1] + q[3] * 0.008400001f;
    else if (0.03f < q[1])
        q[1] = q[1] + q[3] * 0.008400001f;
    else {
        q[1] = q[1] + q[3] * 0.0016800001f;
        *(float *)(p + 12) = *(float *)(p + 12) + 6552.0005f;
    }

    if (q[1] <= 0.0244f || Fc10c1216_FUN_00282978(p + 10) != 0) {
        Fc10c1216_FUN_002B9180(p);
        return;
    }

    if (q[1] >= 0.12f) {
        q[3] = -q[3];
        q[1] = q[1] + q[3] * 0.008400001f;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 6552.0005f;
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xffffff) | (Fc10c1216_FUN_00283CF0(q[1] * 255.0f) << 24);
    q[2] = q[2] + 0.0024f;
    if (q[2] > 1.0f)
        q[2] = q[2] - 1.0f;
    *(char *)(p + 8) = (char)(q[2] * 255.0f);
    Fc10c1216_FUN_00282CC0(p + 16, p + 16, (char *)(q + 4));
}





extern int FloatToInt(float);
extern int gfx_pack_color_floats(float, float, float, float);
extern void part_kill(char *);

/* func_002BEBC0 is in 002BEBC0-hazard-labels.c (retail keeps a branch label on its
   mtc1 hazard nop, which only a -frac2-hazard-labels unit reproduces). */

/* func_002BEE70 is in 002BEE70-g.c (it needs -g for its line notes' pre-division nops). */

void func_PAL_002C0218(char *o)
{
    float *s;
    char *parent;
    float t;

    if (o == 0)
        return;
    s = (float *)(o + 0x20);
    parent = *(char **)s;
    if (parent == 0 || (*(unsigned char *)(parent + 0x20) & 0xF0) == 0xF0) {
        part_kill(o);
        return;
    }
    qcopy(o + 0x10, parent + 0x10);
    t = s[1] + s[2];
    s[1] = t;
    if (t < 0.0f) {
        part_kill(o);
        return;
    }
    if (t > 0.6f) {
        s[2] = -s[2];
        s[1] = t + s[2];
    }
    s[4] += -0.02088f;
    if (s[4] < 0.0f)
        s[4] = 0.0f;
    s[5] += -0.017352002f;
    if (s[5] < 0.0f)
        s[5] = 0.0f;
    s[6] += -0.0018000001f;
    if (s[6] < 0.0f)
        s[6] = 0.0f;
    *(int *)(o + 4) = gfx_pack_color_floats(s[4], s[5], s[6], s[1]);
    s[3] += 0.00132f;
    if (s[3] > 1.0f)
        s[3] -= 1.0f;
    *(char *)(o + 8) = FloatToInt(s[3] * 255.0f);
    *(float *)(o + 0xC) = (*(float **)(o + 0x20))[0xB] * 3e+06f + 50000.0f;
}





