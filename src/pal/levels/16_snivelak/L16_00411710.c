#include "include_asm.h"

#include "common.h"
extern s32 func_313EA0(s32);
extern void moby_set_state(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern float fast_vec_dist(void *, void *);
extern u8 *g_beam_definition_table[] __attribute__((sda));
extern u8 g_snivelak_boss_state;
extern s32 math_fast_float_d(void *);
extern u8 *g_path_l16_table[];
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern s32 FloatToInt(float);
extern void moby_update_ground_check(void *);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void group_wake_members(u8 *);
extern s32 weapon_select_aim_target(void *, s32, float, float, s32, s32);
extern float g_scene_origin_transform[];
extern u8 *g_moby_instance_table[] __attribute__((sda));
extern s32 g_group_id_limit[] __attribute__((sda));
extern void *part_find_owned_effect_slot(void *, s32, s32);
extern s32 coll_test_point(void *, s32, void *, float);

/* Object update: on the first frame (+0x20 still zero) sets the state's defaults and
   rates; then, with +0x31 set and the object within 32 units of D_L16_001B9B00, runs
   func_002A93B0 and sets +0x6F to 30; marks the group when func_PAL_002B1A50 reports, and
   runs func_002B3BA8 on the state's two slots, keeping the object's +0x18 across them. */
void func_PAL_L16_00411C78(u8 *arg)
{
    u8 *state;

    state = *(u8 **)(arg + 0x68);
    if (arg[0x20] == 0) {
        *(s32 *)(state + 0x54) = 0;
        *(s32 *)(state + 0x7C) = 0;
        state[0x150] = 5;
        *(s32 *)(state + 0x188) = 3;
        *(float *)(state + 0x17C) = 0.15f;
        *(float *)(state + 0x50) = 1.868f;
        *(float *)(state + 0x170) = 0.5f;
        *(float *)(state + 0x174) = 0.5f;
        *(float *)(state + 0x58) = 0.5f;
        *(float *)(state + 0x5C) = 0.5f;
        *(float *)(state + 0x60) = 3.141593f;
        *(float *)(state + 0x80) = 0.52359885f;
        moby_set_controller_speed_limits(arg, 0.0032000002f, 0.080000006f, 0.00062831864f, 0.04188791f);
        *(s32 *)(state + 0x88) |= 2;
        if (*(s16 *)(state + 0x24) == 0) {
            *(s16 *)(state + 0x24) = 1;
            *(float *)(state + 0x20) = 1.0f;
        }
        moby_set_state(arg, 1, 0);
        if (arg[0x43])
            func_PAL_002A7E68(arg, 0, 0, 0);
        state[0x48] = FloatToInt(18.0f);
        state[0x4A] = FloatToInt(16.0f);
        *(float *)(state + 0x358) = *(float *)(arg + 0x18);
    }
    if (arg[0x31] && fast_vec_dist(arg + 0x10, g_scene_origin_transform) < 32.0f) {
        moby_update_ground_check(arg);
        arg[0x6F] = 30;
    }
    if (func_PAL_002B1A50(arg, state + 0x140, 0))
        group_wake_members(arg);
    *(s32 *)(state + 0x240) = weapon_select_aim_target(arg, *(s32 *)(state + 0x230), *(float *)(state + 0x234), 0.0f, 0, 0);
    *(s32 *)(state + 0x354) = weapon_select_aim_target(arg, *(s32 *)(state + 0x350), 0.0f, 0.0f, 0, 0);
    *(float *)(arg + 0x18) = *(float *)(state + 0x358);
}
