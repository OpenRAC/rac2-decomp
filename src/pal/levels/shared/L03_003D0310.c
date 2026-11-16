#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 g_emitter_pair_table;
extern u32 flag_is_third_pending_set(u8 *);
typedef float f32;
extern f32 g_timer_tick_step __attribute__((sda));
extern u8 *g_moby_record_base __attribute__((sda));
extern s32 coll_test_point(void *, s32, void *, f32);
s32 route_check_points(u32 moby, u8 *first, u8 *second);
extern s32 FindRouteNodeIndex(u32, f32 *);
extern f32 vec_distance_xy(void *, f32 *);
extern f32 coll_probe_ground_height_below(f32 *, s32, f32);
extern f32 FastAddRotations(f32, f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern u32 g_path_puzzle_adjacency;
extern s32 ref_L03_003E3750_00(u8 *, u32);
extern u8 *CreateMoby(s32);
extern s32 g_activeGadgetItem;
extern f32 g_gadget_scale;
extern f32 g_gadget_approach_value __attribute__((sda));
extern f32 math_fabs(f32);
extern u32 path_build_region_link_graph(u8 *, u8 *, u8 *, s32);
extern s32 ComputeRegionRouteHeading(u8 *, u8 *, void *, u8 *, s32, s32 *, s32 *, float, float);
extern s32 path_find_route_node_containing_point(u8 *, u8 *, s32, s32 *);
s32 route_check_object_points(u8 *, u8 *, u8 *);
extern s32 math_random_int_below(s32);
extern f32 g_effect_aim_offset_scale;

/* Updates the Blue Swingshot Target. Once active, it turns two of its rotation values toward their goals. (PAL: 50 Hz turn rates) */
void blue_swingshot_target_update_pal(u8 *moby) {
    if (*(u8 *)(moby + 0x31) == 0)
        return;
    *(f32 *)(moby + 0xF4) = FastAddRotations(*(f32 *)(moby + 0xF4),
                                        0.12566373f);
    *(f32 *)(moby + 0xF8) = FastAddRotations(*(f32 *)(moby + 0xF8),
                                        0.055850547f);
}


