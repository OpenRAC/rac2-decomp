#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 D_L03_0024A7B0;
extern u32 flag_is_third_pending_set(u8 *);
typedef float f32;
extern f32 D_L04_001B1C88 __attribute__((sda));
extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 coll_test_point(void *, s32, void *, f32);
s32 route_check_points(u32 a0, u8 *first, u8 *second);
extern s32 FindRouteNodeIndex(u32, f32 *);
extern f32 vec_distance_xy(void *, f32 *);
extern f32 coll_probe_ground_height_below(f32 *, s32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern void vec_random_direction(f32 *, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_ground_effect(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);
extern u32 D_0024A7B0;
extern s32 ref_L03_003E3750_00(u8 *, u32);
extern u8 *CreateMoby(s32);
extern s32 g_activeGadgetItem;
extern f32 D_001B9C14;
extern f32 D_001B2464 __attribute__((sda));
extern f32 math_fabs(f32);
extern u32 path_build_region_link_graph(u8 *, u8 *, u8 *, s32);
extern s32 ComputeRegionRouteHeading(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);
extern s32 path_find_route_node_containing_point(u8 *, u8 *, s32, s32 *);
s32 route_check_object_points(u8 *, u8 *, u8 *);
extern s32 math_random_int_below(s32);
extern f32 D_L03_001B9BEC;

void func_PAL_L03_003D5148(u8 *a0, s32 a1, s32 a2) {
    f32 buf[3];
    f32 f20, f21;
    s32 s1, s2;

    s2 = a2;
    f20 = math_random_float_range(0.25f, 1.0f);
    s1 = math_random_int_below(2);
    f21 = math_random_float_range(3.0f, 7.0f) * (0.00040000002f);
    vec_random_direction(buf, 0.0f, 0.1f);
    FastVecAdd(buf, buf, a1);
    part_spawn_ground_effect(buf, 0x21, 0x7F800000, 0, s1, s2, 0, f20 * 0.2f, f20, f21);
    part_spawn_ground_effect(buf, 0x32, 0x7F7F7F7F, 1, -s1, s2, 0, f20 * 0.14f, f20 * 0.7f, f21);
}

