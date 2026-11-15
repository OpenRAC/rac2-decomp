#include "common.h"
typedef int TI128 __attribute__((mode(TI)));

extern short D_L05_00221D50;
extern void FastVecAdd(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern int math_fast_float_d(char *);
extern float FastAddRotations(float, float);
extern void gfx_l04_draw_billboard_sprite(char *, int, int, int, float, float, float, float);

/* Draws glowing sprites at the back of the object. Their colour changes while a timer runs. */
void gfx_draw_thruster_glow(char *object)
{
    char *vars = *(char **)(object + 0x68);
    TI128 offset;
    char *source;
    int colorA;
    int colorB;

    *(float *)(vars + 0x60) = FastAddRotations(*(float *)(vars + 0x60), 0.01f);
    *(float *)(vars + 0x64) = FastAddRotations(*(float *)(vars + 0x64), -0.007f);
    *(float *)(vars + 0x68) = FastAddRotations(*(float *)(vars + 0x68), 0.007f);
    *(float *)(vars + 0x6C) = FastAddRotations(*(float *)(vars + 0x6C), *(float *)(vars + 0x38) * 0.02f);
    source = object + 0xE0;
    qcopy(&offset, source);
    colorA = 0;
    vec_scale_to_length((char *)&offset, (char *)&offset, 0.05f);
    colorB = 0;
    FastVecAdd((char *)&offset, object + 0x10, (char *)&offset);
    if (D_L05_00221D50 != 0) {
        *(int *)(vars + 0xA0) = 7;
    } else {
        colorA = 0x0FC85A5A;
        colorB = 0x28FF3232;
    }
    if (math_fast_float_d(vars + 0xA0) == 0) {
        int step = *(int *)(vars + 0xA0) * 5;
        int lowBits = (0x6E - step) | 0x1E000000;

        colorA = ((step + 0x6E) << 16) | lowBits;
        colorB = ((step + 0x96) << 16) | lowBits;
    }
    gfx_l04_draw_billboard_sprite((char *)&offset, *(int *)(vars + 0x58), colorA, 1, 0.27f, 0.35f, *(float *)(vars + 0x60), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&offset, *(int *)(vars + 0x58), colorA, 1, 0.27f, 0.35f, *(float *)(vars + 0x64), 0.0f);
    gfx_l04_draw_billboard_sprite((char *)&offset, 0x36, colorB, 1, 0.22f, 0.35f, *(float *)(vars + 0x68), 0.0f);
}
