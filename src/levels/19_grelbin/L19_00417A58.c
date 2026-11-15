#include "common.h"

extern float math_random_float_range(float, float);
extern void moby_transform_joint_point(void *, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float math_random_angle(void);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void part_spawn_random_direction_effect(void *, float, float);
/* The integer and floating argument banks retain their respective orders. */
extern void gfx_draw_billboard_quad(void *, int, int, float, int, float, float);
extern void part_spawn_fading_drift(void *, void *, int, int, int, int, int, int, float, float, float);

/* Draws the Leviathan's charge-up flash in front of it and shoots sparks outward while the flash grows. */
void leviathan_draw_charge_flash(char *moby)
{
    float bodyMatrix[16] __attribute__((aligned(16)));
    float muzzlePos[4] __attribute__((aligned(16)));
    float muzzleOffset[4] __attribute__((aligned(16)));
    float sparkVelBuf[4] __attribute__((aligned(16)));
    float sparkPosBuf[4] __attribute__((aligned(16)));
    char *vars = *(char **)(moby + 0x68);
    float primaryRadius, secondaryRadius, phase;
    int particleType;

    moby_transform_joint_point(moby, 0, bodyMatrix);
    qcopy(muzzlePos, bodyMatrix + 12);
    vec_scale_to_length(muzzleOffset, bodyMatrix, 0.25f);
    FastVecAdd(muzzlePos, muzzlePos, muzzleOffset);
    muzzlePos[2] += 2.0f;
    primaryRadius = *(float *)(vars + 0x228) * 2.0f;
    phase = math_random_angle();
    gfx_draw_billboard_quad(muzzlePos, 0x31, 0x60804020, primaryRadius, 1, 0.08f, phase);
    secondaryRadius = *(float *)(vars + 0x228);
    secondaryRadius *= 1.5f;
    gfx_draw_billboard_quad(muzzlePos, 0x31, 0x80808080, secondaryRadius, 1, 0.08f, math_random_angle());
    *(float *)(vars + 0x228) += 0.03f;
    if (*(float *)(vars + 0x228) < 1.15f) {
        float *particlePos = sparkPosBuf;
        float *particleVel = sparkVelBuf;
        int i;

        for (i = 19; i >= 0; i--) {
            particleType = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            part_spawn_random_direction_effect(particlePos, 2.5f, 3.0f);
            FastVecAdd(particlePos, particlePos, muzzlePos);
            FastVecSub(particleVel, muzzlePos, particlePos);
            vec_scale_to_length(particleVel, particleVel, 0.050000004f);
            part_spawn_fading_drift(particlePos, particleVel, 30, 0x804020, particleType, 0, 127, 5,
                          math_random_float_range(0.2f, 0.5f) * 210000.0f, 126000.0078125f, 0.0f);
        }
    }
}
