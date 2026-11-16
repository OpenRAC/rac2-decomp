#include "include_asm.h"
#include "names.h"

typedef int V4_002AE8C0 __attribute__((mode(TI)));
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern int moby_l01_turn_toward_target_pal(char *, float *);
extern float coll_probe_ground_height_below(char *, int, float);
extern float math_move_angle_toward_target(float, float, float);
extern void StepAngleTowardTarget(float *, int, float, float);
extern int FastDecTimer(char *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(char *, char *);
typedef struct {
    char reserved_000[0x80];
    float pos[4];
} GameState_189E20;
extern GameState_189E20 g_hero_state;

/* Moves an enemy along a wandering heading: picks new headings now and then, steers back toward its home point when too far, and turns away from the hero when near (PAL). Hand-adapted from func_002AE8C0. */
void enemy_update_wander_heading_pal(char *enemy, char *wander, char *context)
{
    char *pos;
    float target[4];
    float dist;

    int blocked;

    if (*(short *)(wander + 0x28) == 0) {
        *(float *)(wander + 0x24) = *(float *)(wander + 0x24) + math_random_signed_float_range(0.78539824f, 2.6179941f);
        *(short *)(wander + 0x2A) = math_random_int_range(*(short *)(wander + 0x2C), *(short *)(wander + 0x2E));
        *(short *)(wander + 0x28) = 1;
    } else {
        StepAngleTowardTarget((float *)(enemy + 0xF8), 0, *(float *)(wander + 0x24), *(float *)(wander + 0x18));
        if (FastDecTimer(wander + 0x2A) != 0)
            *(short *)(wander + 0x28) = 0;
    }
    pos = enemy + 0x10;
    *(V4_002AE8C0 *)target = *(V4_002AE8C0 *)pos;
    dist = *(float *)(context + 0x28);
    *(float *)(context + 0x28) = *(float *)(wander + 0x14);
    target[0] = target[0] + math_fast_sin_or_cos_a(*(float *)(enemy + 0xF8)) * 2.0f;
    target[1] = target[1] + math_fast_sin_or_cos_b(*(float *)(enemy + 0xF8)) * 2.0f;
    *(float *)(context + 0x28) = dist;
    blocked = moby_l01_turn_toward_target_pal(enemy, target);
    *(float *)(enemy + 0x18) = coll_probe_ground_height_below(pos, 0, 0.5f);
    dist = vec_distance_xy(pos, wander);
    if (blocked != 0 || *(float *)(wander + 0x1C) < dist) {
        *(float *)(wander + 0x24) = mat_fast_helper_a(*(float *)(wander + 0x0) - *(float *)(enemy + 0x10),
                                              *(float *)(wander + 0x4) - *(float *)(enemy + 0x14));
        *(short *)(wander + 0x2A) = math_random_int_range(25, 75);
        *(short *)(wander + 0x28) = 1;
    } else {
        float limit;

        dist = vec_distance_xy(pos, g_hero_state.pos);
        limit = *(float *)(wander + 0x20);
        if (dist < limit) {
            dist = dist / limit;
            *(float *)(wander + 0x24) = math_move_angle_toward_target(*(float *)(wander + 0x24),
                    mat_fast_helper_a(*(float *)(enemy + 0x10) - g_hero_state.pos[0],
                                  *(float *)(enemy + 0x14) - g_hero_state.pos[1]), dist);
        }
    }
}
