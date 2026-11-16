#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u32 g_emitter_pair_table;
extern void moby_set_state(u8 *, u8, s32);
extern u32 flag_is_third_pending_set(u8 *);
typedef float f32;
extern f32 g_timer_tick_step __attribute__((sda));
extern u8 *g_moby_record_base __attribute__((sda));
/* func_L03_003C5B28 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5CE8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

/* func_L03_003C5DC8 is defined in L03_003C5B28-g8.c (it reads the group count through $gp). */

static __inline__ void qcopy(void *dst, const void *src) {
    __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                         : : "r"(dst), "r"(src) : "$2", "memory");
}
extern void route_choose_target_point(u8 *, void *, f32 *);
extern void route_set_node_enabled_flag(u32, u8 *, s32);
extern s32 coll_test_point(void *, s32, void *, f32);
extern void anim_start_blended_pal(void *, int, int, int);
extern void moby_set_flag_bit(u8 *entity, s32 enabled);
extern char g_hero_position[];
typedef struct {
    u8 pad0[0x110];
    f32 f110;
    f32 f114;
    u8 pad118[0x220 - 0x118];
    u32 f220;
    u8 pad224[0x340 - 0x224];
    f32 f340[4];
    u8 pad350[0x358 - 0x350];
    u8 *f358;
} L03_5EE8Vars;
typedef struct {
    u8 pad0[0x10];
    s32 f10;
} L03_5EE8Class;
typedef struct {
    u8 pad0[0x24];
    L03_5EE8Class *f24;
    u8 pad28[0x43 - 0x28];
    u8 f43;
    u8 pad44[0x68 - 0x44];
    L03_5EE8Vars *f68;
    u8 pad6c[0x98 - 0x6C];
    s32 f98;
} L03_5EE8Moby;
s32 route_check_points(u32 a0, u8 *first, u8 *second);
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

/* Finds a safe spot for the object this one is holding and puts it down there. If the spot is blocked, it keeps holding the object. */
void moby_place_held_object_pal(L03_5EE8Moby *moby) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 test[4] __attribute__((aligned(16)));
    L03_5EE8Vars *vars = moby->f68;

    route_set_node_enabled_flag(vars->f220, vars->f358 + 0x10, 0);
    route_choose_target_point(vars->f358, g_hero_position, pos);
    qcopy(test, pos);
    test[2] += vars->f110 + vars->f114;
    if (coll_test_point(test, 0, moby, vars->f110) == 0) {
        qcopy(vars->f340, pos);
        moby_set_flag_bit(vars->f358, 0);
        vars->f358 = 0;
        moby->f98 = moby->f24->f10;
        moby_set_state((u8 *)moby, 0x11, 4);
        if (moby->f43 != 0) {
            anim_start_blended_pal(moby, 0, 0, 0x11);
        }
    } else {
        route_set_node_enabled_flag(vars->f220, vars->f358 + 0x10, 1);
    }
}

