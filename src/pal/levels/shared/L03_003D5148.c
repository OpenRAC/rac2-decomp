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
extern void vec_random_direction(f32 *, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void *part_spawn_ground_effect(void *, u32, u32, u32, s32, s32, s32, f32, f32, f32);
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

/* Spawns two puffs of particles with random size and speed, used by the particle emitter. */
void part_spawn_emitter_pair_pal(u8 *moby, s32 position, s32 velocity) {
    f32 spawn_pos[3];
    f32 size, life;
    s32 spin, vel;

    vel = velocity;
    size = math_random_float_range(0.25f, 1.0f);
    spin = math_random_int_below(2);
    life = math_random_float_range(3.0f, 7.0f) * (0.00040000002f);
    vec_random_direction(spawn_pos, 0.0f, 0.1f);
    FastVecAdd(spawn_pos, spawn_pos, position);
    part_spawn_ground_effect(spawn_pos, 0x21, 0x7F800000, 0, spin, vel, 0, size * 0.2f, size, life);
    part_spawn_ground_effect(spawn_pos, 0x32, 0x7F7F7F7F, 1, -spin, vel, 0, size * 0.14f, size * 0.7f, life);
}

