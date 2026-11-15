#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
extern unsigned char g_hero_state[];
extern float math_random_float_range(float, float);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void FastVecScale(void *, void *, float);
extern void part_spawn_spark_effect(Vector *, void *, float);
extern unsigned char *part_spawn_bubble(Vector *, Vector *, float, float);

/* Joint branches and velocity copy follow RAC1 emit_hero_randomized_motion_effects
 * in overlays/shared/hero_idle_and_animation.c (OpenRAC/rac1-decomp, GPL-3.0). */
/* Emit particles either around the player or alternately from selected joints. */
void EmitHeroRandomizedMotionEffects(int count, int sourceMode, int sparks) {
    Vector position;
    Vector velocity;
    unsigned char *player;
    Vector *inheritedVelocity;
    int index;
    float size;
    for (index = 0; index < count; ++index) {
        player = g_hero_state;
        inheritedVelocity = (Vector *)(player + 0x110);
        if (sourceMode == 0) {
            position.f[0] = *(float *)(player + 0x80) + math_random_float_range(-0.1f, 0.1f);
            position.f[1] = *(float *)(player + 0x84) + math_random_float_range(-0.1f, 0.1f);
            position.f[2] = *(float *)(player + 0x88) + math_random_float_range(-0.5f, 0.1f);
        } else if (sourceMode == 1) {
            if (!(index & 1))
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 0, (char *)&position);
            else
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 14, (char *)&position);
        } else if (sourceMode == 2) {
            if (!(index & 1))
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 23, (char *)&position);
            else
                moby_transform_joint_to_world(*(char **)(player + 0x2290), 22, (char *)&position);
        }
        qcopy(&velocity, inheritedVelocity);
        if (*(int *)(player + 0x2294) == 0x33) FastVecScale(&velocity, &velocity, 1.15f);
        else FastVecScale(&velocity, &velocity, 0.7f);
        velocity.f[0] += math_random_float_range(-0.0066666672937572f, 0.0066666672937572f);
        velocity.f[1] += math_random_float_range(-0.0066666672937572f, 0.0066666672937572f);
        velocity.f[2] += math_random_float_range(-0.01666666753590107f, 0.0f);
        if (sparks) {
            unsigned char *matrix = *(unsigned char **)(player + 0x2290) + 0xC0;
            size = math_random_float_range(0.7f, 1.1f);
            part_spawn_spark_effect(&position, matrix, *(float *)(player + 0x170) * size);
        } else {
            size = math_random_float_range(4200.0f, 7350.0f);
            part_spawn_bubble(&position, &velocity, size, -1.0f);
        }
    }
}
