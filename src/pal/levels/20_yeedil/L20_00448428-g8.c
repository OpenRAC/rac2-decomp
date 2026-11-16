#include "names.h"
/* func_PAL_L20_00448428, the PAL copy of func_L20_004429F0: the same C, where the
 * delay scale 60.0f becomes 50.0f, its base 1200 becomes 1000, and the spawn call
 * is PAL's own. */
#include "common.h"

extern int g_yeedil_no_minions_flag __attribute__((sda));
extern char *g_path_point_tables[];
extern int group_count_live_members(int);
extern int math_fast_float_d(char *);
extern float level_interpolate_by_counter(int, int, float, float);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void lerp_vector(float *, const void *, const void *, float);
extern float coll_probe_ground_height_below(char *, int, float);
extern int coll_test_point(void *, int, void *, float);
extern u8 *trooper_spawn_from_free_slot_pal(void *, int, const float *);

/* Every so often tries to place new helper enemies at random spots along the edge of the arena, four at a time or six when the boss is angry. (PAL: 50 Hz timings) */
void yeedil_boss_spawn_minions_edge_pal(char *object)
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

    if (*(int *)(state + 0x182C) <= 0 && g_yeedil_no_minions_flag == 0)
        return;
    if (*(u8 *)(object + 0x95) == 5)
        return;
    if (group_count_live_members(*(int *)(state + 0x23C)) != 0)
        return;
    if (math_fast_float_d(state + 0x1848) == 0 && g_yeedil_no_minions_flag == 0)
        return;
    rate = 60.0f;
    requested = 4;
    interval = level_interpolate_by_counter(5, 20, 0.0f, rate);
    attempts = 0;
    spawned = 0;
    *(int *)(state + 0x1848) = FloatToInt((float)(int)(interval * 50.0f)) + 1000;
    if (*(int *)(state + 0x182C) == 2)
        requested = 6;
    polygon = g_path_point_tables[*(int *)(state + 0x234)];
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
            if (trooper_spawn_from_free_slot_pal(object, *(int *)(state + 0x23C), point) == 0)
                break;
            ++spawned;
        }
    }
}
