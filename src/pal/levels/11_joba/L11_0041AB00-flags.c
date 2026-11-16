#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 g_sound_state[];
extern u8 g_hero_position[];
extern u8 g_moby_group_flags[][16];
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 *g_path_l11_table[];
extern s32 PlayMobySound(s32, s32, u8 *);
extern void snd_stop_voice(s32);
extern s32 hero_is_current_selected_id(u8 *);
extern u8 *cam_alloc_override_slot_pal(s32);
extern void cam_end_override(u8 *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, const void *, const void *);
extern f32 fast_vec_dist(void *, void *);
extern f32 vec_distance_xy(void *, void *);
extern void moby_set_byte_on_group(s32, s32);
extern s32 IsPointInCuboid(void *, s32);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern void glow_flicker_update_pal(u8 *, void *, s32);

/* Moves the entity along its path, managing its effect and sound during state changes. */
void joba_path_follower_update_pal(u8 *object) {
    f32 previous[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 rotation[4] __attribute__((aligned(16)));
    f32 point[4] __attribute__((aligned(16)));
    f32 step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(object + 0x68);
    u8 *position;
    s32 slot;
    *(TI128 *)(previous) = *(TI128 *)(object + 0x10);
    *(TI128 *)(rotation) = *(TI128 *)(object + 0xF0);
    if (object[0x95] == 0) {
        object[0x95] = 1;
        *(u16 *)(object + 0x34) |= 0x2000;
    }
    if (object[0xBC] == 0) *(s32 *)(object + 0x98) = 0;
    else *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
    if (hero_is_current_selected_id(object)) {
        if (object[0x20] == 0) {
            {
                u8 *record = (u8 *)g_sound_state + *(s32 *)(state + 0x70) * 0x70;
                if (*(u8 **)(record + 0x88) != object || record[0x74] == 0)
                    *(s32 *)(state + 0x70) = PlayMobySound(0, 4, object);
            }
            *(u8 **)(state + 0x68) = cam_alloc_override_slot_pal(5);
            *(f32 *)(*(u8 **)(state + 0x68)) = 10.0f;
            *(s16 *)(*(u8 **)(state + 0x68) + 0x1A) = 1;
            *(s32 *)(*(u8 **)(state + 0x68) + 0x3C) = 1;
            (*(u8 **)(state + 0x68))[0x18] = 1;
            {
                u8 *record = *(u8 **)(state + 0x68) + 0x20;
                *(TI128 *)(record) = *(TI128 *)(object + 0xC0);
                vec_scale_to_length(record, record, -1.0f);
            }
            (*(u8 **)(state + 0x68))[0x1E] = 1;
            object[0x20] = 1;
            if (g_moby_group_flags[g_current_map_index[0]][object[0xB0]] & 0x80) {
                u8 *path;
                cam_end_override(*(u8 **)(state + 0x68));
                path = g_path_l11_table[*(s32 *)(state + 0x60)];
                object[0x20] = 6;
                *(s32 *)(state + 0x64) = *(s32 *)path - 1;
            }
        }
    } else if (object[0x20] == 0) {
        slot = *(s32 *)(state + 0x70);
        if (slot != -1) {
            u8 *record = (u8 *)g_sound_state + slot * 0x70;
            if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
        }
        *(s32 *)(state + 0x70) = -1;
    }
    if (object[0x20] == 1) {
        u8 *path;
        path = g_path_l11_table[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) >= *(s32 *)path) {
            if (!hero_is_current_selected_id(object)) {
                object[0x20] = 2;
                cam_end_override(*(u8 **)(state + 0x68));
                moby_set_byte_on_group(object[0x21], 0);
            }
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)g_sound_state + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
            }
            *(s32 *)(state + 0x70) = -1;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            FastVecSub(step, point, (object + 0x10));
            vec_scale_to_length(step, step, 0.040000003f);
            FastVecAdd((object + 0x10), (object + 0x10), step);
            if (vec_distance_xy((object + 0x10), point) < 0.05f) ++*(s32 *)(state + 0x64);
        }
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 0x6C))) {
            moby_set_byte_on_group(object[0x21], 0);
            *(TI128 *)((object + 0x10)) = *(TI128 *)(path + 0x10);
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)g_sound_state + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
            }
            *(s32 *)(state + 0x70) = -1;
            cam_end_override(*(u8 **)(state + 0x68));
        }
    }
    position = object + 0x10;
    if (object[0x20] == 2) {
        u8 *path;
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 0x6C))) {
            path = g_path_l11_table[*(s32 *)(state + 0x60)];
            moby_set_byte_on_group(object[0x21], 0);
            *(TI128 *)(position) = *(TI128 *)(path + 0x10);
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)g_sound_state + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
            }
            *(s32 *)(state + 0x70) = -1;
            cam_end_override(*(u8 **)(state + 0x68));
        }
    }
    if (object[0x20] == 3) {
        u8 *path;
        path = g_path_l11_table[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) < 0) {
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            FastVecSub(step, point, position);
            vec_scale_to_length(step, step, 0.080000006f);
            FastVecAdd(position, position, step);
            if (vec_distance_xy(position, point) < 0.05f) --*(s32 *)(state + 0x64);
        }
    }
    if (object[0x20] == 5) {
        u8 *path;
        path = g_path_l11_table[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) < 0) {
            object[0x20] = 0;
            *(s32 *)(state + 0x64) = 0;
            slot = *(s32 *)(state + 0x70);
            if (slot != -1) {
                u8 *record = (u8 *)g_sound_state + slot * 0x70;
                if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
            }
            *(s32 *)(state + 0x70) = -1;
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            FastVecSub(step, point, position);
            vec_scale_to_length(step, step, 0.080000006f);
            FastVecAdd(position, position, step);
            if (fast_vec_dist(position, point) < 0.05f) --*(s32 *)(state + 0x64);
        }
    }
    if (object[0x20] == 6) {
        u8 *path;
        path = g_path_l11_table[*(s32 *)(state + 0x60)];
        if (*(s32 *)(state + 0x64) >= *(s32 *)path) {
            if (!hero_is_current_selected_id(object)) {
                object[0x20] = 2;
                *(s32 *)(state + 0x64) = 0;
                moby_set_byte_on_group(object[0x21], 0);
                slot = *(s32 *)(state + 0x70);
                if (slot != -1) {
                    u8 *record = (u8 *)g_sound_state + slot * 0x70;
                    if (*(u8 **)(record + 0x88) == object && record[0x74]) snd_stop_voice(slot);
                }
                *(s32 *)(state + 0x70) = -1;
            }
        } else {
            *(TI128 *)(point) = *(TI128 *)(path + 0x10 + *(s32 *)(state + 0x64) * 16);
            FastVecSub(step, point, position);
            vec_scale_to_length(step, step, 0.080000006f);
            FastVecAdd(position, position, step);
            if (fast_vec_dist(position, point) < 0.05f) ++*(s32 *)(state + 0x64);
        }
    }
    FastVecSub(delta, position, previous);
    mat_combine_and_store(state + 0x20, delta, rotation, rotation);
    glow_flicker_update_pal(object, state + 0x74, object[0xBC]);
}
