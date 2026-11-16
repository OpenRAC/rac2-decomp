#include "include_asm.h"

#include "common.h"
typedef union {
    u8 b[0x3F4];
    u16 uh[0x1FA];
    s32 i[0xFD];
    float f[0xFD];
    u8 *p[0xFD];
} EnemyStateView;
typedef union {
    s16 h[0x114C];
    s32 i[0x8A6];
} PlayerView;
typedef union {
    u16 uh[0x150];
    u32 ui[0xA8];
} HistoryView;
typedef union {
    u8 b[0x20];
    float f[8];
} PositionView;
extern PlayerView g_hero_state;
extern HistoryView g_statistics_table;
extern u8 g_player_bolts[] __attribute__((sda));
extern unsigned g_frame_counter[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 g_moby_group_flags[];
extern PositionView g_camera_l18_position;
extern int g_hero_frozen_flag __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern int g_receiver_targeting_frames __attribute__((sda));
extern float g_receiver_targeting_distance __attribute__((sda));
extern float g_enemy_smooth_time;
extern int shooter_init(void *);
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern int moby_apply_damage_to_object(void *,void *,int);
extern void moby_rebuild_scale_matrix(void *);
extern void shooter_flag_group(void *,int);
extern void func_US2_002A7AA8(void *,int,int);
extern void spawner_activate_nearest_enemy(void *);
extern void moby_set_state(void *,int,int);
extern int weapon_select_aim_target(void *, int, float, float, void *, int);
extern int flag_is_third_pending_set(void *);
extern void level_store_value_pair_us2(int,int);
extern void SetCamera5Pose(void *,void *,int,int,int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern s32 func_US2_L18_002E02E8(int,int);
extern float vec_distance_xy(void *,void *);
extern void moby_set_flag_bit(void *,int);
extern void moby_start_or_forward_anim(void *,int,int,float);
extern int TryClaimNotice(int,int,int);

/* Refreshes targeting and combat reactions, including the player capture transition. */
void receiver_bot_update_targeting_us2(u8 *o) {
    EnemyStateView *s = *(EnemyStateView **)(o + 0x68);
    int hit;
    if (!o[0x95]) {
        s->i[0x3F0/4] = -1;
        if (shooter_init(o)) {
            moby_mark_spawned(o);
            return;
        }
    }
    if (o[0x31] && fast_vec_dist(o+0x10, &g_camera_l18_position) < 24.0f) {
        moby_update_ground_check(o);
        o[0x6F] = 22;
    }
    if (!(s->b[0x3B1] & 0x80) || *(s16 *)(o+0xAA) != 0xEE1) {
        s->f[0x2B0/4] = 0.0f;
        moby_update_eased_node(o, s->b+0x240,4,1.0f,1.0f);
    } else if (g_player_bolts[0x4F]) {
        s->f[0x2B0/4] = 0.5f / g_enemy_smooth_time;
        moby_update_eased_node(o,s->b+0x240,4,1.0f,1.0f);
    }
    if (o[0x95] != 8 && o[0xBC] != 1 && o[0x95] != 7 && !g_hero_frozen_flag && g_hero_state.i[0x2294/4] != 111) {
        hit = moby_apply_damage_to_object(o,s->b+0x50,0);
        if (hit) {
            moby_rebuild_scale_matrix(o);
            shooter_flag_group(o,o[0x21]);
            if (hit == 4) {
                func_US2_002A7AA8(o,0,3);
                spawner_activate_nearest_enemy(o);
                moby_set_state(o,12,10);
            }
        }
        s->b[0x3B2] = s->b[0x3B3];
        weapon_select_aim_target(o, s->i[0x37C / 4], 0.0f, 0.0f, 0, 0);
        {
            int id = *(s16 *)(s->p[0x230/4]+0xAA);
            s->b[0x3B3] = id == 0xEC0 || id == 0xED4 || id == 0xEE1;
        }
        if (!o[0xBC] && o[0x95] != 7 && flag_is_third_pending_set(o)) {
            o[0x30] = 255;
            level_store_value_pair_us2(0,0);
            moby_rebuild_scale_matrix(o);
            SetCamera5Pose(&g_camera_l18_position,g_camera_l18_position.b+0x10,1,0,0);
            object_copy_vector_to_selected(&g_camera_l18_position);
            cam_set_state_rotation(g_camera_l18_position.b+0x10);
            if (g_hero_state.i[0x2294/4] == 1 || g_hero_state.i[0x2294/4] == 29)
                func_US2_L18_002E02E8(0, 1);
            g_hero_state.h[0x1E0/2] = 20;
            s->f[0x3B8/4] = (vec_distance_xy(o+0x10,&g_camera_l18_position)-g_receiver_targeting_distance) / g_receiver_targeting_frames;
            if (g_statistics_table.uh[0x294/2] < 65535)
                ++g_statistics_table.uh[0x294/2];
            if (g_frame_counter[0] > g_statistics_table.ui[0x298/4])
                g_statistics_table.ui[0x298/4] = g_frame_counter[0];
            g_statistics_table.ui[0x29C/4] = (g_statistics_table.ui[0x29C/4] | (1 << g_current_map_index[0])) | 0x80000000;
            moby_set_flag_bit(o,0);
            s->uh[0x396/2] = *(u16 *)&g_receiver_targeting_frames;
            moby_start_or_forward_anim(o,16,0,10.0f);
            g_hero_frozen_flag = 1;
            TryClaimNotice(6,0,20);
            moby_set_state(o,0,7);
        }
    }
    o[0xA8] = 255;
    if (!s->i[0x1D8/4])
        moby_set_state(o, 12, 10);
    if (s->b[0x3E9] && (g_moby_group_flags[o[0xB0]+(D_001A79F0_gp<<4)] & 0x80))
        moby_set_state(o, 12, 10);
    if (s->b[0x2E] == 2) {
        moby_rebuild_scale_matrix(o);
        shooter_flag_group(o,o[0x21]);
        spawner_activate_nearest_enemy(o);
        moby_set_state(o,11,10);
    }
}
