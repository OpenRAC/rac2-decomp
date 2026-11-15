#include "common.h"

/* func_PAL_L18_0042C768, the PAL copy of func_L18_00427BE0: the same C, where the frame counts take the 50 Hz scale. */

/* Typed views cover the fields this update reads; unknown fields retain their offsets. */
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
extern HistoryView D_0018C360;
/* This flag is save-block byte +0x4F (absolute 0x001A7A47). Keeping its
 * enclosing block preserves the two-instruction load and empty branch slot. */
extern u8 g_player_bolts[] __attribute__((sda));
extern unsigned D_001A7390[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern u8 D_0019B2E8[];
extern PositionView g_camera_l18_position;
extern int D_L18_001AFBB0 __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern int D_L18_001B1290 __attribute__((sda));
extern float D_L18_001B1294 __attribute__((sda));
extern float D_L18_001B12FC;
extern int func_PAL_L18_0042C210(void *);
extern void moby_mark_spawned(void *);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern void moby_update_eased_node(void *,void *,int,float,float);
extern int func_PAL_002B1A50(void *,void *,int);
extern void func_PAL_L18_0042BAE0(void *);
extern void shooter_flag_group(void *,int);
extern void func_PAL_002A7650(void *,int,int);
extern void func_PAL_L18_0042BF58(void *);
extern void moby_set_state(void *,int,int);
/* EE argument banks preserve the pointer/index/point/force and range/height
 * orders while this declaration places the range pair before the optional point. */
extern int weapon_select_aim_target(void *, int, float, float, void *, int);
extern int flag_is_third_pending_set(void *);
extern void func_PAL_0029C0F0(int,int);
extern void SetCamera5Pose(void *,void *,int,int,int);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern s32 func_PAL_L18_002E01E0(int,int);
extern float vec_distance_xy(void *,void *);
extern void moby_set_flag_bit(void *,int);
extern void func_PAL_L18_0042BA90(void *,int,int,float);
extern int TryClaimNotice(int,int,int);
/* Refreshes targeting and combat reactions, including the player capture transition. */
void func_PAL_L18_0042C768(u8 *o) {
    EnemyStateView *s = *(EnemyStateView **)(o + 0x68);
    int hit;
    if (!o[0x95]) {
        s->i[0x3F0/4] = -1;
        if (func_PAL_L18_0042C210(o)) {
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
        s->f[0x2B0/4] = 0.5f / D_L18_001B12FC;
        moby_update_eased_node(o,s->b+0x240,4,1.0f,1.0f);
    }
    if (o[0x95] != 8 && o[0xBC] != 1 && o[0x95] != 7 && !D_L18_001AFBB0 && g_hero_state.i[0x2294/4] != 111) {
        hit = func_PAL_002B1A50(o,s->b+0x50,0);
        if (hit) {
            func_PAL_L18_0042BAE0(o);
            shooter_flag_group(o,o[0x21]);
            if (hit == 4) {
                func_PAL_002A7650(o,0,3);
                func_PAL_L18_0042BF58(o);
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
            func_PAL_0029C0F0(0,0);
            func_PAL_L18_0042BAE0(o);
            SetCamera5Pose(&g_camera_l18_position,g_camera_l18_position.b+0x10,1,0,0);
            object_copy_vector_to_selected(&g_camera_l18_position);
            cam_set_state_rotation(g_camera_l18_position.b+0x10);
            if (g_hero_state.i[0x2294/4] == 1 || g_hero_state.i[0x2294/4] == 29)
                func_PAL_L18_002E01E0(0, 1);
            g_hero_state.h[0x1E0/2] = ((s32)(20) * 5 + 2) / 6;
            s->f[0x3B8/4] = (vec_distance_xy(o+0x10,&g_camera_l18_position)-D_L18_001B1294) / (((s32)(D_L18_001B1290) * 5 + 2) / 6);
            if (D_0018C360.uh[0x294/2] < 65535)
                ++D_0018C360.uh[0x294/2];
            if (((s32)(D_001A7390[0]) * 5 + 2) / 6 > D_0018C360.ui[0x298/4])
                D_0018C360.ui[0x298/4] = ((s32)(D_001A7390[0]) * 5 + 2) / 6;
            D_0018C360.ui[0x29C/4] = (D_0018C360.ui[0x29C/4] | (1 << g_current_map_index[0])) | 0x80000000;
            moby_set_flag_bit(o,0);
            s->uh[0x396/2] = ((s32)(D_L18_001B1290) * 5 + 2) / 6;
            func_PAL_L18_0042BA90(o,16,0,10.0f);
            D_L18_001AFBB0 = 1;
            TryClaimNotice(6,0,20);
            moby_set_state(o,0,7);
        }
    }
    o[0xA8] = 255;
    if (!s->i[0x1D8/4])
        moby_set_state(o, 12, 10);
    if (s->b[0x3E9] && (D_0019B2E8[o[0xB0]+(D_001A79F0_gp<<4)] & 0x80))
        moby_set_state(o, 12, 10);
    if (s->b[0x2E] == 2) {
        func_PAL_L18_0042BAE0(o);
        shooter_flag_group(o,o[0x21]);
        func_PAL_L18_0042BF58(o);
        moby_set_state(o,11,10);
    }
}
