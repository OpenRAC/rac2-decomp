#include "common.h"

extern void moby_compute_opposite_points(u8 *, void *, void *);
extern s32 route_check_points(u32, u8 *, u8 *);
extern s32 FindRouteNodeIndex(u32, void *);
extern f32 vec_distance_xy(void *, void *);
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern u8 g_hero_position[];

/* Picks one of two candidate points near the object's route and writes it to output, raised a little off the ground. */
void route_choose_target_point(u8 *object, void *unused, f32 *output)
{
    f32 first[4] __attribute__((aligned(16)));
    f32 second[4] __attribute__((aligned(16)));
    u8 *vars = *(u8 **)(object + 0x68);
    s32 region;
    f32 distance;
    moby_compute_opposite_points(object, first, second);
    if (route_check_points(*(u32 *)(vars + 0x64), (u8 *)first, g_hero_position) != 0) {
        qcopy(output, first);
    } else if (route_check_points(*(u32 *)(vars + 0x64), (u8 *)second, g_hero_position) != 0) {
        qcopy(output, second);
    } else {
        region = FindRouteNodeIndex(*(u32 *)(vars + 0x64), first);
        if (region != -1) {
            qcopy(output, first);
        } else if (FindRouteNodeIndex(*(u32 *)(vars + 0x64), second) != region) {
            qcopy(output, second);
        } else {
            distance = vec_distance_xy(g_hero_position, first);
            if (distance < vec_distance_xy(g_hero_position, second))
                qcopy(output, first);
            else
                qcopy(output, second);
        }
    }
    output[2] += 0.5f;
    output[2] = coll_probe_ground_height_below(output, 0, 0.5f);
}
