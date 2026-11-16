#include "include_asm.h"

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
extern void part_l00_spawn_spark_burst_3_pal(void *, int, int);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void StepAngleTowardTarget(void *, int, float, float);
extern float ApproachValue(void *, float, float);
extern float FastAddRotations(float, float);
extern void moby_mark_spawned(void *);

/* Advances the trail, resolves a collision, then settles and fades the object. */
void trail_l03_l03_projectile_update_pal(char *obj)
{
    float next_position[4], trace_end[4], matrix[12], particle_position[4], trail_position[4], trail_step[4];
    int i, color;

    char *state = *(char **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0: {
        float size;
        FastVecAdd(next_position, obj + 0x10, state);
        vec_scale_to_length(trace_end, obj + 0xc0, g_trail_projectile_trace_length);
        FastVecAdd(trace_end, trace_end, next_position);
        make_hit_descriptor(matrix, obj, 1, g_effect_descriptor_default, (float)*(int *)(state + 0x38));
        *(TI128 *)(trail_position) = *(TI128 *)(obj + 0x10);
        FastVecScale(trail_step, state, -0.2f);
        i = 4;
        do {
            i--;
            size = math_random_float_range(0.1f, 0.3f);
            color = math_random_int_below(255);
            vec_random_direction(particle_position, 0.0f, 0.1f);
            FastVecAdd(particle_position, particle_position, trail_position);
            part_spawn_gravity_fade(particle_position, g_effect_descriptor_default, 12, 0x808080, color, 32, 0, size*210000.0f, size*42000.0f, 0.0f, 0);
            FastVecAdd(trail_position, trail_position, trail_step);
        } while (i >= 0);
        if (CollLine(next_position, trace_end, 0, obj, matrix) && g_hero_ground_collision.count > 0) {
            *(TI128 *)(state + 0x20) = *(TI128 *)(g_hero_ground_collision.pos);
            *(TI128 *)(state + 0x10) = *(TI128 *)(g_hero_ground_collision.normal);
            *(float *)(state + 0x34) = g_trail_projectile_trace_length;
            part_l00_spawn_spark_burst_3_pal(g_hero_ground_collision.pos, 10, 1);
            moby_set_state(obj, 1, -1);
        }
        *(TI128 *)(obj + 0x10) = *(TI128 *)(next_position);
        if (math_fast_float_d(state + 0x30)) moby_mark_spawned(obj);
        break;
    }
    case 1: {
        void *rotation = obj + 0xf4;
        float step;
        step = mat_fast_helper_a(vec_length_xy(state + 0x10), *(float *)(state + 0x18));
        StepAngleTowardTarget(rotation, 0, step, 0.12566373f);
        *(TI128 *)(obj + 0x10) = *(TI128 *)(state + 0x20);
        vec_scale_to_length(next_position, obj + 0xc0, -*(float *)(state + 0x34));
        FastVecAdd(obj + 0x10, obj + 0x10, next_position);
        ApproachValue(state + 0x34, 0.0f, 0.0060000005f);
        { float amount = *(float *)(state + 0x34);
          step = amount*1.2566373f;
          *(float *)(obj + 0xf0) = FastAddRotations(*(float *)(obj + 0xf0), step); }
        if (*(float *)(state + 0x34) <= 0.0f) {
            moby_set_state(obj, 2, -1);
            *(int *)(state + 0x30) = 50;
        }
        break;
    }
    case 2:
        if (math_fast_float_d(state + 0x30)) goto finish;
        break;
    }
    return;
finish:
    if (*(u8 *)(obj + 0x23) < 4) moby_mark_spawned(obj);
    else *(u8 *)(obj + 0x23)-=4;
}
