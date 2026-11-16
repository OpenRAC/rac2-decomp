#include "include_asm.h"

#include "common.h"
extern void *g_group_id_lists[];
extern u8 *g_moby_l11_table;
extern s32 g_active_rider_count;
extern f32 coll_probe_ground_height_below(void *, s32, f32);
extern s32 FloatToInt(f32);
extern s32 path_build_route_nodes(void *, s32, void *, s32);
extern void STUB_printf(void *, ...);
extern char g_str_jobian_lieutenant_debug[];
extern f32 math_random_signed_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern void moby_set_flag_bit(void *, s32);
extern void moby_set_controller_speed_limits(void *, f32, f32, f32, f32);
extern char g_str_debug_lieutenant[];
extern char g_hero_l11_position[];
extern s32 g_enemy_spawn_enabled, g_tribe_group_limit, g_arena_progress_level;
extern u8 *CreateMoby(s32);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_002A0F48(void *);
extern void moby_copy_joint_transform_to_object(void *, void *, s32, s32);
extern f32 fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_transform_joint_point(void *, s32, void *);
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void func_PAL_002A0F68(void *);
extern void copy_matrix3x4(void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, f32);
extern void mat_normalize_columns(void *);
extern void func_002A10E8(void *);
extern void part_spawn_explosion_with_sparks_pal(void *, void *, f32, f32, s32);
extern s32 func_PAL_002B1A50(void *, void *, s32);
extern void func_PAL_L11_0042F7E8(void *, s32);
extern void func_PAL_002AC290(void *, void *);
extern void MarkGroupClassCF5CF6Members(void *);
extern s32 moby_count_group_not_in_state(s32, s32);
extern s32 hero_check_distance_zones(void *, void *, s32, s32, f32, f32, s32);
extern void SetDeathBits_pal(void *, s32, s32);
extern char g_hero_l11_position[];
extern char g_hero_l11_position[];

/* Initializes linked objects, updates damage, and releases children on removal. */
s32 func_PAL_L11_0042E7D0(u8 *object) {
    f32 vectors[16];
    s32 damage;
    u16 *ids;
    u8 *data = *(u8 **)(object + 0x68);
    if (object[0x20] == 0) {
        object[0x30] = 0x80;
        g_active_rider_count++;
        *(s32 *)(data + 0x5B0) = 0;
        *(void **)(data + 0x18) = data + 0x140;
        *(f32 *)(object + 0x18) = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        *(s32 *)(data + 0x554) = 0;
        *(s32 *)(data + 0x560) = 0;
        *(s32 *)(data + 0x568) = 0;
        data[0x48] = FloatToInt(20.0f);
        data[0x4A] = FloatToInt(14.0f);
        if (*(s32 *)(data + 0x528)) {
            *(s32 *)(data + 0x520) = path_build_route_nodes(object, *(s32 *)(data + 0x524), data + 0x320, 16);
            STUB_printf(g_str_jobian_lieutenant_debug, *(s32 *)(data + 0x520));
        }
        if (*(f32 *)(data + 0x298) == 0.0f)
            *(f32 *)(data + 0x298) = math_random_signed_float_range(15.0f, 25.0f) * 0.01745329424738884f;
        else
            *(f32 *)(data + 0x298) *= 0.01745329424738884f;
        if (math_random_int_below(2) == 1) {
            *(u16 *)(object + 0x34) |= 0x8000;
            moby_set_flag_bit(object, 1);
        }
        data[0x70] = 31;
        *(s32 *)(data + 0xA8) = 4;
        data[0x72] = 7;
        data[0x71] = 6;
        data[0x76] = 8;
        *(f32 *)(data + 0x7C) = 0.24000001f;
        *(f32 *)(data + 0x80) = 0.15f;
        *(f32 *)(data + 0x84) = 0.008f;
        *(f32 *)(data + 0x88) = 0.014f;
        *(f32 *)(data + 0x8C) = 0.006f;
        *(f32 *)(data + 0x90) = 0.75f;
        *(f32 *)(data + 0x94) = 0.75f;
        *(s32 *)(data + 0x9C) = 0;
        data[0xCC] = 5;
        data[0xCD] = 10;
        data[0xCE] = 8;
        data[0xCF] = 15;
        data[0xD2] = 6;
        data[0xD3] = 11;
        *(f32 *)(data + 0x10C) = 0.5f;
        *(f32 *)(data + 0xB8) = 0.18f;
        if (*(s32 *)(data + 0x5B8) != -1)
            *(s32 *)(data + 0xDC) = *(s32 *)(data + 0x5B8);
        *(void **)(data + 0x188) = data + 0x2A0;
        *(f32 *)(data + 0x174) = 0.25f;
        *(f32 *)(data + 0x140) = 0.75f;
        *(f32 *)(data + 0x144) = 0.75f;
        *(f32 *)(data + 0x148) = 0.6f;
        *(f32 *)(data + 0x14C) = 0.6f;
        if (*(s32 *)(data + 0x288) != -1)
            *(s32 *)(data + 0x17C) = *(s32 *)(data + 0x288);
        *(f32 *)(data + 0x150) = 1.483530044555664f;
        *(f32 *)(data + 0x16C) = 0.002f;
        *(f32 *)(data + 0x170) = 1.483530044555664f;
        *(f32 *)(data + 0x174) = 1.5f;
        moby_set_controller_speed_limits(object, 0.0022f, 0.055000003f, 0.0016755164f, 0.12566373f);
        data[0x28] = 3;
        data[0x29] = 1;
        *(f32 *)(data + 0x30) = 0.75f;
        *(f32 *)(data + 0x28C) = data[0x34];
        data[0x2E] = 1;
        if (*(s32 *)(data + 0x26C)) {
            moby_set_state(object, 1, 5);
            if (*(s32 *)(data + 0x270) != -1) {
                *(u8 **)(data + 0x274) = g_moby_l11_table + (*(s32 *)(data + 0x270) << 8);
                qcopy_nc(object + 0x10, *(u8 **)(data + 0x274) + 0x10);
                qcopy_nc(object + 0xF0, *(u8 **)(data + 0x274) + 0xF0);
                *(s32 *)(object + 0x98) = 0;
                *(u16 *)(object + 0x34) &= 0xAFFF;
                *(u8 **)(*(u8 **)(*(u8 **)(data + 0x274) + 0x68) + 0x27C) = object;
                *(u8 **)(data + 0x280) = CreateMoby(0x911);
                if (!*(u8 **)(data + 0x280)) return 1;
                (*(u8 **)(data + 0x280))[0x30] = object[0x30];
                (*(u8 **)(data + 0x280))[0x31] = 0;
                func_002A0F48(*(u8 **)(data + 0x280));
                qcopy_nc(*(u8 **)(data + 0x280) + 0x10, object + 0x10);
                *(f32 *)(*(u8 **)(data + 0x280) + 0x18) += 0.75f;
                *(u8 **)(data + 0x278) = CreateMoby(0xFF9);
                if (!*(u8 **)(data + 0x278)) return 1;
                (*(u8 **)(data + 0x278))[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
                (*(u8 **)(data + 0x278))[0x31] = 1;
                *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
                func_002A0F48(*(u8 **)(data + 0x278));
                moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x278), 1, 0);
                *(s32 *)(data + 0x290) = 0;
            } else {
                STUB_printf(g_str_debug_lieutenant);
                *(s32 *)(data + 0x26C) = 0;
                moby_set_state(object, 4, 0);
                return 1;
            }
        } else {
            moby_set_state(object, 4, 0);
            if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 0);
            if (*(s32 *)(data + 0x540) == 1) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 13) func_PAL_002A7E68(object, 13, 0, 0);
            } else if (*(s32 *)(data + 0x540) == 2) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 15) func_PAL_002A7E68(object, 15, 5, 0);
            } else if (*(s32 *)(data + 0x540) == 3) {
                *(u8 **)(data + 0x55C) = g_moby_l11_table + (*(s32 *)(data + 0x544) << 8);
                moby_set_state(object, 5, 0);
                if (object[0x43] != 15) func_PAL_002A7E68(object, 15, 0, 0);
            } else if (*(s32 *)(data + 0x54C) != -1) {
                moby_set_state(object, 11, 0);
                if (object[0x43] != 4) func_PAL_002A7E68(object, 4, 0, 0);
            }
            *(u8 **)(data + 0x29C) = CreateMoby(0x9AC);
            if (!*(u8 **)(data + 0x29C)) return 1;
            (*(u8 **)(data + 0x29C))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x29C) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x29C))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x29C) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x29C));
            *(s32 *)(*(u8 **)(data + 0x29C) + 0x98) = 0;
            moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x29C), 3, 0);
            *(u8 **)(data + 0x278) = CreateMoby(0xFF9);
            if (!*(u8 **)(data + 0x278)) return 1;
            (*(u8 **)(data + 0x278))[0x30] = object[0x30];
            *(u16 *)(*(u8 **)(data + 0x278) + 0x32) = *(u16 *)(object + 0x32);
            (*(u8 **)(data + 0x278))[0x31] = 1;
            *(u64 *)(*(u8 **)(data + 0x278) + 0x38) = *(u64 *)(object + 0x38);
            func_002A0F48(*(u8 **)(data + 0x278));
            moby_copy_joint_transform_to_object(object, *(u8 **)(data + 0x278), 2, 0);
        }
        qcopy_nc(data + 0x110, object + 0x10);
        *(f32 *)(data + 0x120) = 1.0f;
        *(f32 *)(data + 0x12C) = 8.0f;
        *(f32 *)(data + 0x130) = 10.0f;
    }
    if (object[0x31] && fast_vec_dist(object + 0x10, g_hero_l11_position) < 24.0f) {
        moby_update_ground_check(object);
        object[0x6F] = 22;
    }
    if (data[0x2E] == 2) {
        if (*(void **)(data + 0x29C)) {
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        if (*(void **)(data + 0x278)) {
            moby_mark_spawned(*(void **)(data + 0x278));
            *(void **)(data + 0x278) = 0;
        }
        if (*(void **)(data + 0x280)) {
            moby_mark_spawned(*(void **)(data + 0x280));
            *(void **)(data + 0x280) = 0;
        }
        return 1;
    }
    if (*(void **)(data + 0x29C)) moby_copy_joint_transform_to_object(object, *(void **)(data + 0x29C), 3, 0);
    if (*(u8 **)(data + 0x278)) {
        moby_transform_joint_point(object, 2, vectors);
        qcopy_nc(*(u8 **)(data + 0x278) + 0x10, vectors + 12);
        func_PAL_002A0F68(*(void **)(data + 0x278));
        func_002A0F48(*(void **)(data + 0x278));
        copy_matrix3x4(*(u8 **)(data + 0x278) + 0xC0, vectors);
        math_apply_axis_rotation_to_quat(*(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xD0, *(u8 **)(data + 0x278) + 0xE0, 3.14159298f);
        mat_normalize_columns(*(u8 **)(data + 0x278) + 0xC0);
        func_002A10E8(*(void **)(data + 0x278));
        *(u16 *)(*(u8 **)(data + 0x278) + 0x34) |= 6;
    }
    if (*(f32 *)(data + 0x20) <= 1.0f) {
        if (*(u8 **)(data + 0x29C)) {
            part_spawn_explosion_with_sparks_pal(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        *(s32 *)(data + 0x290) = 0;
    }
    *(s32 *)(data + 0x290) = 0;
    damage = func_PAL_002B1A50(object, data + 0x60, 0);
    if (damage) {
        u8 *attacker = *(u8 **)(data + 0x38);
        if (attacker) {
            s32 cls = *(s16 *)(attacker + 0xAA);
            if (cls != 0x47 && cls != 0xDD9 && cls != 0xD1B && cls != 0xCE7 && cls != 0xD07 && cls != 0)
                g_enemy_spawn_enabled = 0;
        }
        if (object[0xBC] == 1)
            (g_moby_l11_table + (*(s32 *)(data + 0x548) << 8))[0x20] = 4;
        if (*(f32 *)(object + 0x48) != 1.0f) *(f32 *)(object + 0x48) = 1.0f;
        if (*(s32 *)(data + 0x290)) {
            moby_transform_joint_to_world(object, 3, vectors);
            func_PAL_L11_0042F7E8(vectors, 8);
        }
        if (damage == 5) {
            *(f32 *)(data + 0xF4) = 1.0053098f;
            *(s32 *)(data + 0xF0) = 0;
            if (*(u8 **)(data + 0x29C)) {
                part_spawn_explosion_with_sparks_pal(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
                moby_mark_spawned(*(void **)(data + 0x29C));
                *(void **)(data + 0x29C) = 0;
            }
        }
        *(s32 *)(data + 0x290) = 0;
        data[0x57] = 0xD2;
        func_PAL_002AC290(object, data + 0x50);
        if (object[0x95] != 2) MarkGroupClassCF5CF6Members(object);
        if ((u32)(damage - 4) < 2 && g_tribe_group_limit >= object[0x21] && moby_count_group_not_in_state(object[0x21], -1) >= 2) {
            ids = g_group_id_lists[object[0x21]];
            do {
                u8 *entry = g_moby_l11_table + ((*ids & 0x7FFF) << 8);
                if (*(s16 *)(entry + 0xAA) == 0xCF6 && !*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)ids++ >= 0);
        }
    }
    *(s16 *)(data + 0x264) = hero_check_distance_zones(object, data + 0x268, *(s32 *)(data + 0x250), *(s32 *)(data + 0x254), *(f32 *)(data + 0x258), *(f32 *)(data + 0x25C), 0);
    if (object[0x95] != 4) {
        f32 floor = coll_probe_ground_height_below(object + 0x10, 0, 0.5f);
        *(f32 *)(object + 0x18) -= 0.37600002f;
        if (*(f32 *)(object + 0x18) < floor) *(f32 *)(object + 0x18) = floor;
    }
    if (*(f32 *)(object + 0x18) < 61.0f && g_arena_progress_level >= 6) {
        moby_mark_spawned(*(void **)(data + 0x278));
        SetDeathBits_pal(object, 0, 3);
        if (g_tribe_group_limit >= object[0x21] && moby_count_group_not_in_state(object[0x21], -1) >= 2) {
            u16 *deathIds = g_group_id_lists[object[0x21]];
            do {
                u8 *entry = g_moby_l11_table + ((*deathIds & 0x7FFF) << 8);
                if (!*(s32 *)(*(u8 **)(entry + 0x68) + 0x294)) {
                    *(s32 *)(*(u8 **)(entry + 0x68) + 0x294) = 1;
                    break;
                }
            } while (*(s16 *)deathIds++ >= 0);
        }
        if (*(u8 **)(data + 0x29C)) {
            part_spawn_explosion_with_sparks_pal(object, *(u8 **)(data + 0x29C) + 0x10, 0.5f, 3.0f, -1);
            moby_mark_spawned(*(void **)(data + 0x29C));
            *(void **)(data + 0x29C) = 0;
        }
        g_active_rider_count--;
        return 1;
    }
    return 0;
}
