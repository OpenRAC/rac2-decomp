#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern char g_hero_state[];
extern char *g_carried_marker_cam_slot __attribute__((sda));
extern float g_carried_marker_radius __attribute__((sda));
extern float g_carried_marker_override_x __attribute__((sda));
extern float g_carried_marker_override_x_alt __attribute__((sda));
extern float g_carried_marker_override_w __attribute__((sda));
extern float g_carried_marker_override_z __attribute__((sda));
extern int g_carried_marker_state;
extern char g_hero_origin_vec[];
extern int IsPointInCuboid(char *, int);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(float *, float *, char *);
extern char *cam_alloc_override_slot_pal(int);
extern void cam_end_override(char *);
extern void FastVecSub(char *, float *, char *);

/* Per-frame update of the carried-object marker: arms it, tracks a linked flag, and while the hero is in state 0x31 places and sizes the marker from the grabbed object's bounds. */
void carried_marker_update_pal(char *moby) {
    float offset[4];
    float target_position[4];
    char *hero_ptr;

    int *link = FLD(moby, int *, 0x68);

    switch (FLD(moby, u8, 0x20)) {
    case 0:
        g_carried_marker_cam_slot = 0;
        FLD(moby, u8, 0x20) = 1;
        FLD(moby, u8, 0x30) = 0xFF;
        return;
    case 1:
        if (link[0] != -1) {
            if (IsPointInCuboid(g_hero_origin_vec, link[0]) != 0) {
                g_carried_marker_state = 2;
            } else if (g_carried_marker_state == 2) {
                g_carried_marker_state = 0;
            }
        }
        break;
    default:
        return;
    }
    if (FLD(g_hero_state, int, 0x2294) == 0x31 && (hero_ptr = FLD(g_hero_state, char *, 0x1830)) != 0) {
        vec_build_spherical_offset(offset, g_carried_marker_radius, FLD(hero_ptr, float, 0xF8), -FLD(hero_ptr, float, 0xF4) * 0.5f);
        FastVecAdd(target_position, offset, FLD(g_hero_state, char *, 0x1830) + 0x10);
        if (g_carried_marker_cam_slot == 0) {
            g_carried_marker_cam_slot = cam_alloc_override_slot_pal(5);
            if (g_carried_marker_cam_slot == 0) {
                return;
            }
        }
        if (FLD(FLD(g_hero_state, char *, 0x1830), s16, 0xAA) == MOBY_CLASS_GLIDER) {
            FLD(g_carried_marker_cam_slot, float, 0) = g_carried_marker_override_x;
            FLD(g_carried_marker_cam_slot, float, 0xC) = -1.0f;
            FLD(g_carried_marker_cam_slot, float, 8) = -1.0f;
        } else {
            FLD(g_carried_marker_cam_slot, float, 0) = g_carried_marker_override_x_alt;
            FLD(g_carried_marker_cam_slot, float, 0xC) = g_carried_marker_override_w;
            FLD(g_carried_marker_cam_slot, float, 8) = g_carried_marker_override_z;
        }
        FLD(g_carried_marker_cam_slot, u8, 0x1F) = 1;
        FastVecSub(g_carried_marker_cam_slot + 0x20, target_position, g_hero_origin_vec);
        return;
    }
    if (g_carried_marker_cam_slot != 0) {
        cam_end_override(g_carried_marker_cam_slot);
        g_carried_marker_cam_slot = 0;
    }
}

extern int g_hero_l19_mode __attribute__((sda));
extern u8 g_warp_trigger_flags[] __attribute__((sda));
extern int g_glow_state_flags[4] __attribute__((sda));
extern char *g_linked_object_table[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern char g_hero_position[];
extern char g_request_l19_queue[];
extern void moby_reset_matching_effects(char *a0);
extern void moby_mark_spawned(char *a0);
extern void moby_set_state(char *a0, s32 a1, s32 a2);
extern void moby_reset_vars_defaults(char *a0);
extern s32 IsPointInCuboid(char *a0, s32 a1);
extern s32 req_push_queue(char *a0, s32 a1);
extern void level_apply_index_for_key(char *a0);
extern s32 req_launch_queued(char *a0);
extern s32 game_is_either_mode_two(void);
extern void moby_mark_flag_and_append_to_list(s32 a0);
extern void snd_play_indexed_pal(s32 a0);
extern void hero_reset_position_and_direction_pal(char *a0, char *a1, s32 a2, s32 a3);
extern void moby_mark_table_entry_flagged(s32 a0);
extern void level_capture_checkpoint_state(char *a0, char *a1);
extern int MemcardSave(s32 a0, s32 a1);

/* Per-frame update for a warp trigger (class 4711). When triggered it fades the screen and moves the hero to a linked spot. (PAL version) */
void warp_trigger_update_pal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    u8 id;

    moby_reset_matching_effects(moby);
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(s32 *)(moby + 0x98) = 0;
        *(u16 *)(moby + 0x34) = (*(u16 *)(moby + 0x34) | 0x41) & 0xEFFF;
        if (g_warp_trigger_flags[0] != 0) {
            moby_mark_spawned(moby);
        } else {
            moby_set_state(moby, 1, -1);
            moby_reset_vars_defaults(moby);
        }
        break;
    case 1:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(vars + 0x120)) != 0) {
            if (req_push_queue(g_request_l19_queue, 0x96) != 0) {
                req_push_queue(g_request_l19_queue, 0x14);
                req_push_queue(g_request_l19_queue, 0x97);
                level_apply_index_for_key(moby);
                req_launch_queued(g_request_l19_queue);
                moby_set_state(moby, 2, -1);
            }
        }
        break;
    case 2:
        g_glow_state_flags[1] = 1;
        if (g_hero_l19_mode == 2) {
            *(u8 *)(moby + 0x31) = 0;
            *(u16 *)(moby + 0x34) |= 1;
        }
        if (game_is_either_mode_two() == 0) {
            g_glow_state_flags[1] = 0;
            moby_mark_flag_and_append_to_list(0x14);
            snd_play_indexed_pal(0x14);
            hero_reset_position_and_direction_pal(g_linked_object_table[0] + (*(s32 *)(vars + 0x120) << 7) + 0x30,
                        g_linked_object_table[0] + (*(s32 *)(vars + 0x120) << 7) + 0x70, 0, 1);
            *(u16 *)(moby + 0x34) &= 0xFFFE;
            *(u8 *)(moby + 0x31) = 1;
            if (*(u8 *)(moby + 0xB0) != 0xFF) {
                id = *(u8 *)(moby + 0xB0);
                if ((g_moby_group_flags[id + (g_current_map_index[0] << 4)] & 0x80) == 0)
                    moby_mark_table_entry_flagged(id);
                level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                MemcardSave(0, -1);
            } else {
                MemcardSave(0, -1);
            }
            moby_mark_spawned(moby);
        }
        break;
    }
}
