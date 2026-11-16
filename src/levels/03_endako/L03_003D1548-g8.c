#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_trail_projectile_trace_length __attribute__((sda));
extern char g_effect_descriptor_default[] __attribute__((sda));
typedef struct {
    char pad[0x1C];
    int count;
    float pos[4];
    char pad2[0x10];
    float normal[4];
} HitResult;
extern HitResult g_hero_ground_collision;
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void vec_random_direction(void *, float, float);
extern void *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern int CollLine(void *, void *, int, void *, void *);
extern void part_l00_spawn_spark_burst_3(void *, int, int);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void StepAngleTowardTarget(void *, int, float, float);
extern float ApproachValue(void *, float, float);
extern float FastAddRotations(float, float);
extern void moby_mark_spawned(void *);

/* Advances the trail, resolves a collision, then settles and fades the object. */
void trail_l03_projectile_update(char *moby)
{
    float nextPosition[4], traceEnd[4], matrix[12], particlePosition[4], trailPosition[4], trailStep[4];
    int i, color;

    char *vars = *(char **)(moby + 0x68);
    switch (*(u8 *)(moby + 0x20)) {
    case 0: {
        float value;
        FastVecAdd(nextPosition, moby + 0x10, vars);
        vec_scale_to_length(traceEnd, moby + 0xc0, g_trail_projectile_trace_length);
        FastVecAdd(traceEnd, traceEnd, nextPosition);
        make_hit_descriptor(matrix, moby, 1, g_effect_descriptor_default, (float)*(int *)(vars + 0x38));
        *(TI128 *)(trailPosition) = *(TI128 *)(moby + 0x10);
        FastVecScale(trailStep, vars, -0.2f);
        i = 4;
        do {
            i--;
            value = math_random_float_range(0.1f, 0.3f);
            color = math_random_int_below(255);
            vec_random_direction(particlePosition, 0.0f, 0.1f);
            FastVecAdd(particlePosition, particlePosition, trailPosition);
            part_spawn_gravity_fade(particlePosition, g_effect_descriptor_default, 15, 0x808080, color, 32, 0, value*210000.0f, value*42000.0f, 0.0f, 0);
            FastVecAdd(trailPosition, trailPosition, trailStep);
        } while (i >= 0);
        if (CollLine(nextPosition, traceEnd, 0, moby, matrix) && g_hero_ground_collision.count > 0) {
            *(TI128 *)(vars + 0x20) = *(TI128 *)(g_hero_ground_collision.pos);
            *(TI128 *)(vars + 0x10) = *(TI128 *)(g_hero_ground_collision.normal);
            *(float *)(vars + 0x34) = g_trail_projectile_trace_length;
            part_l00_spawn_spark_burst_3(g_hero_ground_collision.pos, 10, 1);
            moby_set_state(moby, 1, -1);
        }
        *(TI128 *)(moby + 0x10) = *(TI128 *)(nextPosition);
        if (math_fast_float_d(vars + 0x30)) moby_mark_spawned(moby);
        break;
    }
    case 1: {
        void *rotation = moby + 0xf4;
        float value;
        value = mat_fast_helper_a(vec_length_xy(vars + 0x10), *(float *)(vars + 0x18));
        StepAngleTowardTarget(rotation, 0, value, 0.104719773f);
        *(TI128 *)(moby + 0x10) = *(TI128 *)(vars + 0x20);
        vec_scale_to_length(nextPosition, moby + 0xc0, -*(float *)(vars + 0x34));
        FastVecAdd(moby + 0x10, moby + 0x10, nextPosition);
        ApproachValue(vars + 0x34, 0.0f, 0.00500000035f);
        { float amount = *(float *)(vars + 0x34);
          value = amount*1.0471977f;
          *(float *)(moby + 0xf0) = FastAddRotations(*(float *)(moby + 0xf0), value); }
        if (*(float *)(vars + 0x34) <= 0.0f) {
            moby_set_state(moby, 2, -1);
            *(int *)(vars + 0x30) = 60;
        }
        break;
    }
    case 2:
        if (math_fast_float_d(vars + 0x30)) goto finish;
        break;
    }
    return;
finish:
    if (*(u8 *)(moby + 0x23) < 4) moby_mark_spawned(moby);
    else *(u8 *)(moby + 0x23)-=4;
}
