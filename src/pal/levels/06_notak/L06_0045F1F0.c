#include "include_asm.h"

#include "common.h"
extern float math_step_value_toward_target(char *, char *, float, float, float, float);
extern int math_blend_scaled_count(char *, char *, int, int, float, float);
extern void FastVecScale(char *, char *, float);

/* Moves the object using its stored speed, pulls it down when it is high, and slows it after a bump (PAL: 50 Hz timings). */
void actor_apply_fall_move_pal(char *moby, char *vars, float f, float g, float h)
{
    char position[16];
    char *q = vars;

    if (*(float *)(*(char **)(vars + 0x11C)) - 0.3f < *(float *)(moby + 0x18)) {
        *(float *)(vars + 0xC8) -= 0.19600002f;
    }
    qcopy(position, moby + 0x10);
    math_step_value_toward_target(position + 8, q + 0xC8, *(float *)(q + 0x128), f, g, h);
    if (math_blend_scaled_count(moby, q + 0xC0, 0x400, 0x10, 1.0f, 0.0f) != 0) {
        FastVecScale(q + 0xC0, q + 0xC0, 0.5f);
    }
}

