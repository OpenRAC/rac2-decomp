#include "common.h"

extern int D_L20_001B20EC __attribute__((sda));
extern char *D_L20_001FEC80[];
extern int group_count_live_members(int);
extern int math_fast_float_d(char *);
extern float level_interpolate_by_counter(int, int, float, float);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void lerp_vector(float *, const void *, const void *, float);
extern float coll_probe_ground_height_below(char *, int, float);
extern int coll_test_point(void *, int, void *, float);
extern u8 *trooper_spawn_from_free_slot(void *, int, const float *);

/* Every so often tries to place new helper enemies at random spots along the edge of the arena, four at a time or six when the boss is angry. */
void yeedil_boss_spawn_minions_edge(char *object)
{
    /* Interpolation, ground probing and collision use the complete quadword,
     * including the fourth lane even though this controller edits only XYZ. */
    float point[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x68);
    char *polygon;
    float rate, interval;
    int requested, attempts, spawned;
    int sides;
    int first, next;

    if (*(int *)(state + 0x182C) <= 0 && D_L20_001B20EC == 0)
        return;
    if (*(u8 *)(object + 0x95) == 5)
        return;
    if (group_count_live_members(*(int *)(state + 0x23C)) != 0)
        return;
    if (math_fast_float_d(state + 0x1848) == 0 && D_L20_001B20EC == 0)
        return;
    rate = 60.0f;
    requested = 4;
    interval = level_interpolate_by_counter(5, 20, 0.0f, rate);
    attempts = 0;
    spawned = 0;
    *(int *)(state + 0x1848) = FloatToInt((float)(int)(interval * rate)) + 1200;
    if (*(int *)(state + 0x182C) == 2)
        requested = 6;
    polygon = D_L20_001FEC80[*(int *)(state + 0x234)];
    for (; attempts < 30 && spawned < requested; ++attempts) {
        float height = 1.0f;
        float blend;
        sides = 6;
        first = math_random_int_below(6);
        next = (first + 1) % sides;
        blend = math_random_float_range(0.2f, 0.8f);
        lerp_vector(point, polygon + (first * 16 + 16),
                     polygon + (next * 16 + 16), blend);
        point[2] = coll_probe_ground_height_below((char *)point, 0, 0.5f) + height;
        if (coll_test_point(point, 0, 0, 0.9f) == 0) {
            point[2] -= height;
            if (trooper_spawn_from_free_slot(object, *(int *)(state + 0x23C), point) == 0)
                break;
            ++spawned;
        }
    }
}
