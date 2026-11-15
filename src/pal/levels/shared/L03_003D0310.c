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

void func_PAL_L03_003D0310(u8 *a0) {
    if (*(u8 *)(a0 + 0x31) == 0)
        return;
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4),
                                        0.12566373f);
    *(f32 *)(a0 + 0xF8) = FastAddRotations(*(f32 *)(a0 + 0xF8),
                                        0.055850547f);
}


