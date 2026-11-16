#include "include_asm.h"


#include "common.h"
extern s32 func_313EA0(s32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int hero_set_control_motion_and_step(void *, void *);
extern u8 *g_beam_definition_table[] __attribute__((sda));
extern u8 g_snivelak_boss_state;
extern s32 math_fast_float_d(void *);
extern u8 *g_path_l16_table[];
extern s32 FloatToInt(float);
extern s32 moby_apply_damage_to_object(void *, void *, s32);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern u8 *g_moby_instance_table[] __attribute__((sda));
extern s32 g_group_id_limit[] __attribute__((sda));
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 coll_test_point(void *, s32, void *, float);

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
s32 path_follow_points_pal(u8 *moby)
{
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = g_path_l16_table[*(s32 *)(state + 0x294)];

    if (*(s32 *)(state + 0x2A4) >= *(s32 *)path)
        return 1;
    qcopy(point, path + 16 + *(s32 *)(state + 0x2A4) * 16);
    FastVecSub(step, point, moby + 0x10);
    vec_scale_to_length(step, step, 0.24000001f);
    hero_set_control_motion_and_step(moby, step);
    if (*(s32 *)(state + 0x2AC) != 0) {
        if (fast_vec_dist(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    } else {
        if (vec_distance_xy(moby + 0x10, point) < 0.5f)
            (*(s32 *)(state + 0x2A4))++;
    }
    return 0;
}


