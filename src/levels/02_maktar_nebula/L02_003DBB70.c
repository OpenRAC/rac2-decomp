#include "include_asm.h"
#include "names.h"

/* func_L02_003DBB70 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern char *g_moby_l02_pool[] __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_add_random_offset(float *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern int FloatToInt(float);
extern void part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);

/* Throws bursts of green glitter particles out from a part of the actor,
   drifting outward and upward. */
void part_spawn_green_glitter(char *actor, char *baseVel) {
    float startPos[4];
    float vel[4];
    float endVel[4];
    int burst;
    int i;
    float angle;
    float radius;
    float lift;
    int colorA;
    int colorB;

    for (burst = 0; burst < 30; burst++) {
        moby_transform_joint_to_world(g_moby_l02_pool[0] + (*(int *)(*(char **)(actor + 0x68) + 0x244) << 8), 4, startPos);
        vec_add_random_offset(startPos, 0.5f);
        startPos[2] += 0.25f;
        angle = math_random_angle();
        radius = math_random_float_range(3.0f, 16.0f);
        lift = math_random_float_range(3.0f, 12.0f);
        FastVecScale(vel, baseVel, math_random_float_range(0.0f, 0.0f) * 0.016666668f);
        vel[0] += math_fast_sin_or_cos_a(angle) * 0.016666668f * radius;
        vel[1] += math_fast_sin_or_cos_b(angle) * 0.016666668f * radius;
        vel[2] += lift * 0.016666668f;
        *(TI128 *)endVel = *(TI128 *)vel;
        endVel[2] -= 0.33333334f;
        for (i = 0; i < 20; i++) {
            float scale = math_random_float_range(0.5f, 1.5f);

            vel[3] = scale * 0.25f;
            endVel[3] = scale * 0.125f;
            vec_add_random_offset(startPos, 0.25f);
            vec_add_random_offset(endVel, 0.016666668f);
            colorA = FastTweenColor(0x80FF00EA, 0x80FF00EA, math_random_float_range(0.0f, 1.0f));
            colorB = FastTweenColor(0x00FF0020, 0x00FF00AA, math_random_float_range(0.0f, 1.0f));
            part_spawn_trail(startPos, vel, endVel, colorA, colorB, 20, 60, FloatToInt(math_random_float_range(10.0f, 50.0f)), -1);
        }
    }
}
