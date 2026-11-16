#include "common.h"
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int func_001163B0(void);
extern char g_hero_position[];
extern char *g_path_segment_list;
extern char *g_moby_array[] __attribute__((sda));
extern s32 math_closest_point_on_polygon_edge(void *, void *, void *, int);
extern int coll_test_point_against_shapes(void *, int, int, int, int);

/* Picks the next point the Spitting Dune Crawler wants to walk to, following its path or wandering around the hero. */
void crawler_pick_walk_target(char *object)
{
    char *state = *(char **)(object + 0x68);
    if (*(int *)(state + 0x428) == -1) {
        math_closest_point_on_polygon_edge(state + 0x3F0, state + 0x3F0, g_path_segment_list + 0x10, *(int *)g_path_segment_list);
        return;
    }
    {
        char *pos = state + 0x3F0;
        char *target = pos;
        if (coll_test_point_against_shapes(state + 0x3F0, *(int *)(state + 0x428), -1, -1, -1)) return;
        if ((func_001163B0() & 1) || *(int *)(state + 0x254) == 2 || *(int *)(state + 0x44C)) {
            if (*(int *)(state + 0x404) == -1 || (func_001163B0() & 1)) {
                qcopy(target, state + 0x3E0);
            } else {
                *(float *)(state + 0x3F0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
                {
                    float y = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
                    int handle = *(int *)(state + 0x404);
                    char *entry = g_moby_array[0];
                    *(float *)(state + 0x3F8) = 0;
                    *(float *)(state + 0x3F4) = y;
                    FastVecAdd(target, target, entry + (handle << 8) + 0x10);
                }
            }
        } else {
            *(float *)(state + 0x3F0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
            *(float *)(state + 0x3F4) = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 3.0f;
            *(float *)(state + 0x3F8) = 0;
            FastVecAdd(pos, pos, g_hero_position);
        }
    }
}
