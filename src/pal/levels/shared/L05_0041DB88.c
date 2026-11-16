#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern short g_thruster_glow_enabled;
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int math_fast_float_d(char *);
extern float FastAddRotations(float, float);
extern void gfx_l04_draw_billboard_sprite(char *, int, int, int, float, float, float, float);

/* Spins the thruster glow angles and draws three billboard sprites in front of the object, colored by whether the glow is on. */
void gfx_draw_thruster_glow_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    TI128 v;
    char *up_axis;
    int color_a;
    int color_b;

    *(float *)(state + 0x60) = FastAddRotations(*(float *)(state + 0x60), 0.01f);
    *(float *)(state + 0x64) = FastAddRotations(*(float *)(state + 0x64), -0.007f);
    *(float *)(state + 0x68) = FastAddRotations(*(float *)(state + 0x68), 0.007f);
    *(float *)(state + 0x6C) = FastAddRotations(*(float *)(state + 0x6C), *(float *)(state + 0x38) * 0.02f);
    up_axis = object + 0xE0;
    qcopy(&v, up_axis);
    color_a = 0;
    vec_scale_to_length((char *)&v, (char *)&v, 0.05f);
    color_b = 0;
    FastVecAdd((char *)&v, object + 0x10, (char *)&v);
    if (g_thruster_glow_enabled != 0) {
        *(int *)(state + 0xA0) = 6;
    } else {
        color_a = 0x0FC85A5A;
        color_b = 0x28FF3232;
    }
    if (math_fast_float_d(state + 0xA0) == 0) {
        int k = *(int *)(state + 0xA0) * 5;
        int lo = (0x6E - k) | 0x1E000000;

        color_a = ((k + 0x6E) << 16) | lo;
        color_b = ((k + 0x96) << 16) | lo;
    }
    gfx_l04_draw_billboard_sprite((char *)&v, *(int *)(state + 0x58), color_a, 1, 0.27f, 0.35f, *(float *)(state + 0x60), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&v, *(int *)(state + 0x58), color_a, 1, 0.27f, 0.35f, *(float *)(state + 0x64), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&v, 0x36, color_b, 1, 0.22f, 0.35f, *(float *)(state + 0x68), 0.0f);
}



/* func_L05_00419F10 is defined in L05_00419F10-g8.c. */

/* Does nothing. */
void stub_l05_empty_pal(void)
{
    char buf[0x20];
}

