/* func_PAL_L06_00405FA8, the PAL copy of func_L06_00402230: the same C with the spawn delay scale
   1/60 becomes 0x3CA3D70B, one ulp above 1/50, written 0.020000001f; the callee is PAL's
   func_PAL_L06_00469110. */
#include "common.h"

extern void func_00282F20(void *, void *, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A7878(float low, float high);
extern void func_00283098(float *out, float *in, char *matrix);
extern void func_PAL_L06_00469110(char *moby, float *position, float *velocity,
                             int flags, float size, float life);

/* Emit three rings of particles around the moby's local frame.
 * The flat velocity[2] = 0.0f below is dead (flow deletes it), but it gives
 * the 0.0f a second use, so loop.c keeps it in a callee-saved register
 * instead of substituting it into the single call argument. This unit is
 * built with -g, as line notes bound haifa-sched's regions here. */
void func_PAL_L06_00405FA8(char *moby)
{
    float position[4];
    float velocity[4];
    int ring, spoke;
    ring = 0;
    do {
        spoke = 0;
        do {
            float shell, angle, size, life;
            if (ring != 0 || !(spoke & 1)) {
                shell = (float)ring + func_002A7878(0.0f, 1.0f);
                angle = 1.57079637f * ((float)spoke + (1.0f / 3.0f) * shell);
                velocity[0] = func_00283180(angle);
                velocity[1] = func_00283198(angle) * 0.25f;
                velocity[2] = 0.0f;
                velocity[2] = ((float)ring - 0.5f) * 0.25f;
                func_00282F20(velocity, velocity,
                              func_002A7878(8.0f, 14.0f) * 0.020000001f /* 0x3CA3D70B, one ulp above 1/50 */);
                func_00283098(velocity, velocity, moby + 0xC0);
                position[0] = *(float *)(moby + 0x10) + velocity[0];
                position[1] = *(float *)(moby + 0x14) + velocity[1] * 3.0f;
                position[2] = *(float *)(moby + 0x18) + 0.75f + shell * 0.5f;
                size = func_002A7878(0.25f, 1.0f);
                life = func_002A7878(0.25f, 1.25f);
                func_PAL_L06_00469110(moby, position, velocity, 0, size, life);
            }
            spoke++;
        } while (spoke < 4);
        ring++;
    } while (ring < 3);
}
