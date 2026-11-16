#include "include_asm.h"

#include "common.h"
typedef u32 VecQuad __attribute__((mode(TI), aligned(16)));
typedef union {
    VecQuad q;
    f32 f[4];
    s32 i[4];
} Vec4;
extern s32 moby_process_collision_hit(u8 *,s32,s32,s32);
extern void moby_check_player_in_view_and_range(u8 *,s32,f32);
extern void *state_get_stored_pointer_value(void);
extern void hrugis_boss_init_pal(u8 *);
extern void hrugis_init_group_states(u8 *);
extern void hrugis_release_group_effects(u8 *);
extern void level_append_object(u8 *,void *,s32,void *);
extern u8 *SpawnAttachedObject(u8 *,s32);
extern s32 hrugis_get_boss_difficulty(void);
extern f32 IntToFloat(s32);
extern u8 *moby_get_motion_data(u8 *);
extern void hrugis_update_sway_speed_pal(u8 *);
extern f32 FastAddRotations(f32,f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 fast_vec_dist(void *,void *);
extern s32 math_fast_helper_a(void *,f32);
extern void hrugis_play_carried_flash_pal(u8 *);
extern s32 math_fast_float_d(void *);
extern f32 math_random_float_range(f32,f32);
extern void part_spawn_smoke_puff_pal(u8 *,s32,f32);
extern void part_spawn_dark_smoke_radius_pal(u8 *,s32,f32);
extern char *moby_spawn_large_explosion_pal(void *,s32,f32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern void moby_detach_manipulator(u8 *,void *);
extern void moby_mark_spawned(u8 *);
extern void hrugis_launch_child_on_curve_pal(u8 *);
extern void math_l00_interpolate_cubic_vector(void *,void *,void *,void *,void *,f32);
extern void FastVecSub(void *,void *,void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,f32);
extern void FastVecCross(void *,void *,void *);
extern void moby_transform_joint_to_world(u8 *,s32,void *);
extern void FastVecAdd(void *,void *,void *);
extern void *energy_strip_create_pal(void *,void *,s32,s32,u32,u32,f32,s32,s32,f32,f32,f32);
extern void moby_reset_action_state(u8 *);
extern u8 *g_moby_pool_base MACRO_ADDR;
extern f32 g_boss_time_limit __attribute__((sda));
extern s32 g_boss_flag_a __attribute__((sda));
extern s32 g_boss_flag_b __attribute__((sda));
extern f32 g_boss_step_rate MACRO_ADDR;

/* Updates the Hrugis boss each frame: moves it along its curve, launches children, checks the hero and the time limit (PAL copy of hrugis_boss_update). */
void hrugis_boss_update_pal(u8 *obj) {
    Vec4 up;
    Vec4 probe;
    Vec4 oldpos;
    Vec4 delta;
    Vec4 a, b;
    Vec4 c, d;
    Vec4 e, f;
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *info, *child;
    s32 hit, i;
    f32 distance, t;
    u8 *childpos, *bank;

    up.q = 0;
    up.f[2] = 1.0f;
    hit = moby_process_collision_hit(obj, 1, 1, 1);
    moby_check_player_in_view_and_range(obj, 1, 32.0f);
    switch (obj[0x20]) {
    case 0:
        obj[0x30] = 0xFF;
        *(f32 *)(vars + 0x2E0) = 1.0f;
        if (!state_get_stored_pointer_value())
            return;
        hrugis_boss_init_pal(obj);
        if (*(s32 *)(vars + 0x2B4))
            level_append_object(obj, hrugis_init_group_states, 0, hrugis_release_group_effects);
        g_boss_flag_a = 0;
        g_boss_flag_b = 0;
        g_boss_step_rate = 1.0f / (g_boss_time_limit * 5e+01f);
        break;
    case 1:
        if (!*(u8 **)(vars + 0x2C0))
            *(u8 **)(vars + 0x2C0) = SpawnAttachedObject(obj, 1);
        if (!*(u8 **)(vars + 0x2C4))
            *(u8 **)(vars + 0x2C4) = SpawnAttachedObject(obj, 0);
        g_boss_time_limit = IntToFloat(hrugis_get_boss_difficulty()) * 2.5f + 30.0f;
        if (g_boss_time_limit > 60.0f)
            g_boss_time_limit = 60.0f;
        info = moby_get_motion_data(obj);
        if (*(s32 *)(vars + 0x2B0) != -1) {
            *(s32 *)(info + 0x11C) = 1;
            bank = g_moby_pool_base;
            *(u8 **)(info + 0x120) = bank + (*(s32 *)(vars + 0x2B0) << 8);
        }
        hrugis_update_sway_speed_pal(obj);
        *(f32 *)(obj + 0xF8) = FastAddRotations(*(f32 *)(obj + 0xF8), *(f32 *)(vars + 0x2CC));
        *(f32 *)(vars + 0x2BC) = FastAddRotations(*(f32 *)(vars + 0x2BC), *(f32 *)(vars + 0x2D0));
        ((Vec4 *)(obj + 0x10))->f[2] = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x2BC)) * 4.0f + *(f32 *)(vars + 0x2B8);
        distance = fast_vec_dist(*(u8 **)(info + 0x120) + 0x10, obj + 0x10);
        qcopy(&probe, obj + 0x10);
        probe.f[3] = *(f32 *)(obj + 0xC) * 0.000976559997071f;
        if (math_fast_helper_a(&probe, 64.0f) != -1 && distance >= 24.0f)
            hrugis_play_carried_flash_pal(obj);
        math_fast_float_d(vars + 0x2E4);
        if (*(f32 *)(vars + 0x180) < 25.0f)
            part_spawn_smoke_puff_pal(obj, 0, math_random_float_range(2.0f, 3.0f));
        if (*(f32 *)(vars + 0x180) < 15.0f)
            part_spawn_dark_smoke_radius_pal(obj, 0, math_random_float_range(1.8f, 2.8f));
        if (!hit)
            break;
        moby_spawn_large_explosion_pal(*(u8 **)(vars + 0x2C0) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 1, 0);
        moby_spawn_large_explosion_pal(*(u8 **)(vars + 0x2C4) + 0x10, 0, 1.0f, 50, 30, 30, 30, 40, 1, 1, 0, 0);
        moby_detach_manipulator(*(u8 **)(vars + 0x2C0), vars + 0x2F0);
        moby_detach_manipulator(*(u8 **)(vars + 0x2C0), vars + 0x330);
        moby_detach_manipulator(*(u8 **)(vars + 0x2C4), vars + 0x370);
        moby_detach_manipulator(*(u8 **)(vars + 0x2C4), vars + 0x3B0);
        vars[0x2F1] = 0;
        vars[0x331] = 0;
        vars[0x371] = 0;
        vars[0x3B1] = 0;
        child = *(u8 **)(*(u8 **)(*(u8 **)(vars + 0x2C0) + 0x68) + 0x18);
        if (child)
            moby_mark_spawned(child);
        child = *(u8 **)(*(u8 **)(*(u8 **)(vars + 0x2C4) + 0x68) + 0x18);
        if (child)
            moby_mark_spawned(child);
        moby_mark_spawned(*(u8 **)(vars + 0x2C0));
        moby_mark_spawned(*(u8 **)(vars + 0x2C4));
        *(u8 **)(vars + 0x2C0) = 0;
        *(u8 **)(vars + 0x2C4) = 0;
        *(s32 *)(vars + 0x2E0) = 0;
        obj[0x20] = 2;
        hrugis_launch_child_on_curve_pal(obj);
        break;
    case 2:
        hrugis_update_sway_speed_pal(obj);
        *(f32 *)(obj + 0xF8) = FastAddRotations(*(f32 *)(obj + 0xF8), *(f32 *)(vars + 0x2CC));
        *(f32 *)(vars + 0x2BC) = FastAddRotations(*(f32 *)(vars + 0x2BC), *(f32 *)(vars + 0x2D0));
        ((Vec4 *)(obj + 0x10))->f[2] = math_fast_sin_or_cos_b(*(f32 *)(vars + 0x2BC)) * 4.0f + *(f32 *)(vars + 0x2B8);
        if (*(u8 **)(vars + 0x2C8)) {
            info = moby_get_motion_data(*(u8 **)(vars + 0x2C8));
            if (!*(s32 *)(info + 0x110)) {
                *(s32 *)(vars + 0x2DC) = 500;
                *(u8 **)(vars + 0x2C8) = 0;
                break;
            }
            *(f32 *)(vars + 0x2D4) += *(f32 *)(vars + 0x2D8);
            if (*(f32 *)(vars + 0x2D4) > 3.1415927f) {
                t = g_boss_step_rate;
                *(f32 *)(vars + 0x2D4) = 3.1415927f;
                *(f32 *)(vars + 0x2E0) += t;
            }
            childpos = *(u8 **)(vars + 0x2C8) + 0x10;
            qcopy(&oldpos, childpos);
            t = (math_fast_sin_or_cos_a(*(f32 *)(vars + 0x2D4) - 3.1415927f) + 1.0f) * 0.5f;
            math_l00_interpolate_cubic_vector(childpos, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, t);
            FastVecSub(&delta, *(u8 **)(vars + 0x2C8) + 0x10, &oldpos);
            if (FastVecLength(&delta) >= 0.0001f) {
                vec_scale_to_length(*(u8 **)(vars + 0x2C8) + 0xC0, &delta, 1.0f);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xC0))->i[3] = 0;
                FastVecCross(*(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xC0, &up);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xD0))->i[3] = 0;
                vec_scale_to_length(*(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xD0, 1.0f);
                FastVecCross(*(u8 **)(vars + 0x2C8) + 0xE0, *(u8 **)(vars + 0x2C8) + 0xD0, *(u8 **)(vars + 0x2C8) + 0xC0);
                ((Vec4 *)(*(u8 **)(vars + 0x2C8) + 0xE0))->i[3] = 0;
            } else {
                moby_transform_joint_to_world(*(u8 **)(vars + 0x2C8), 0, &a);
                moby_transform_joint_to_world(*(u8 **)(vars + 0x2C8), 1, &b);
                moby_transform_joint_to_world(*(u8 **)(vars + 0x2C8), 2, &c);
                moby_transform_joint_to_world(*(u8 **)(vars + 0x2C8), 3, &d);
                FastVecSub(&e, &c, &a);
                FastVecSub(&f, &d, &b);
                vec_scale_to_length(&e, &e, 4.0f);
                vec_scale_to_length(&f, &f, 4.0f);
                FastVecAdd(&e, &c, &e);
                FastVecAdd(&f, &d, &f);
                energy_strip_create_pal(&c, &e, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
                energy_strip_create_pal(&d, &f, 2, 0, 0x7F7F7F, 0xFF1010, 0.5f, 70, 70, 0.2f, 0.402000010014f, 1.1222499609f);
            }
            for (i = 0; i < 16; i++) {
                math_l00_interpolate_cubic_vector(&a, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, IntToFloat(i) * 0.0625f);
                math_l00_interpolate_cubic_vector(&b, vars + 0x260, vars + 0x270, vars + 0x280, vars + 0x290, IntToFloat(i + 1) * 0.0625f);
            }
            if (*(f32 *)(vars + 0x2E0) >= 1.0f) {
                *(s32 *)(vars + 0x2DC) = 0;
                obj[0x20] = 1;
                moby_reset_action_state(*(u8 **)(vars + 0x2C8));
                *(f32 *)(vars + 0x2E0) = 1.0f;
                *(u8 **)(vars + 0x2C8) = 0;
                info = moby_get_motion_data(obj);
                ((Vec4 *)(vars + 0x180))->f[0] = (f32)*(s32 *)(info + 0x148);
                g_boss_flag_b = 1;
            }
        } else if (math_fast_float_d(vars + 0x2DC)) {
            hrugis_launch_child_on_curve_pal(obj);
        }
        if (*(f32 *)(vars + 0x2E0) <= 0.5f)
            part_spawn_dark_smoke_radius_pal(obj, 0, math_random_float_range(1.9f, 2.25f) - *(f32 *)(vars + 0x2E0));
        if (*(f32 *)(vars + 0x2E0) <= 0.75f)
            part_spawn_smoke_puff_pal(obj, 0, math_random_float_range(2.0f, 3.0f) - *(f32 *)(vars + 0x2E0));
        break;
    }
    hrugis_update_sway_speed_pal(obj);
}
