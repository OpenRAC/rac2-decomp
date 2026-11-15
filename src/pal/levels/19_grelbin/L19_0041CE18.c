#include "include_asm.h"

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
extern void gfx_draw_billboard_quad(void *, int, int, float, int, float, float);
extern char *part_spawn_fading_drift(void *, void *, int, int, int, int, int, int, float, float, float);

void func_PAL_L19_0041CE18(char *obj)
{
    float mat[16] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);
    float primaryRadius, secondaryRadius, phase;
    int particleType;

    moby_transform_joint_point(obj, 0, mat);
    qcopy(pos, mat + 12);
    vec_scale_to_length(scaled, mat, 0.25f);
    FastVecAdd(pos, pos, scaled);
    pos[2] += 2.0f;
    primaryRadius = *(float *)(state + 0x228) * 2.0f;
    phase = math_random_angle();
    gfx_draw_billboard_quad(pos, 0x31, 0x60804020, primaryRadius, 1, 0.08f, phase);
    secondaryRadius = *(float *)(state + 0x228);
    secondaryRadius *= 1.5f;
    gfx_draw_billboard_quad(pos, 0x31, 0x80808080, secondaryRadius, 1, 0.08f, math_random_angle());
    *(float *)(state + 0x228) += 0.03f;
    if (*(float *)(state + 0x228) < 1.15f) {
        float *particlePos = point;
        float *particleVel = vel;
        int i;

        for (i = 19; i >= 0; i--) {
            particleType = FloatToInt(math_random_signed_float_range(2.0f, 5.0f));
            part_spawn_random_direction_effect(particlePos, 2.5f, 3.0f);
            FastVecAdd(particlePos, particlePos, pos);
            FastVecSub(particleVel, pos, particlePos);
            vec_scale_to_length(particleVel, particleVel, 0.060000002f);
            part_spawn_fading_drift(particlePos, particleVel, 25, 0x804020, particleType, 0, 127, 5,
                          math_random_float_range(0.2f, 0.5f) * 210000.0f, 126000.0078125f, 0.0f);
        }
    }
}

