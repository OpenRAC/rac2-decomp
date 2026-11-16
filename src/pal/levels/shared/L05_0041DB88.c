#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern short g_thruster_glow_enabled;
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int math_fast_float_d(char *);
extern float FastAddRotations(float, float);
extern void gfx_l04_draw_billboard_sprite(char *, int, int, int, float, float, float, float);

void gfx_draw_thruster_glow_pal(char *arg0)
{
    char *st = *(char **)(arg0 + 0x68);
    TI128 v;
    char *q;
    int c1;
    int c2;

    *(float *)(st + 0x60) = FastAddRotations(*(float *)(st + 0x60), 0.01f);
    *(float *)(st + 0x64) = FastAddRotations(*(float *)(st + 0x64), -0.007f);
    *(float *)(st + 0x68) = FastAddRotations(*(float *)(st + 0x68), 0.007f);
    *(float *)(st + 0x6C) = FastAddRotations(*(float *)(st + 0x6C), *(float *)(st + 0x38) * 0.02f);
    q = arg0 + 0xE0;
    qcopy(&v, q);
    c1 = 0;
    vec_scale_to_length((char *)&v, (char *)&v, 0.05f);
    c2 = 0;
    FastVecAdd((char *)&v, arg0 + 0x10, (char *)&v);
    if (g_thruster_glow_enabled != 0) {
        *(int *)(st + 0xA0) = 6;
    } else {
        c1 = 0x0FC85A5A;
        c2 = 0x28FF3232;
    }
    if (math_fast_float_d(st + 0xA0) == 0) {
        int k = *(int *)(st + 0xA0) * 5;
        int lo = (0x6E - k) | 0x1E000000;

        c1 = ((k + 0x6E) << 16) | lo;
        c2 = ((k + 0x96) << 16) | lo;
    }
    gfx_l04_draw_billboard_sprite((char *)&v, *(int *)(st + 0x58), c1, 1, 0.27f, 0.35f, *(float *)(st + 0x60), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&v, *(int *)(st + 0x58), c1, 1, 0.27f, 0.35f, *(float *)(st + 0x64), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&v, 0x36, c2, 1, 0.22f, 0.35f, *(float *)(st + 0x68), 0.0f);
}



/* func_L05_00419F10 is defined in L05_00419F10-g8.c. */

void stub_l05_empty_pal(void)
{
    char buf[0x20];
}

