#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern void moby_set_state(char *, int, int);
extern void object_life_timer_update_pal(char *);
extern void trooper_aim_at_target_pal(char *);
extern s32 flag_set_first_pending(char *);
extern void anim_start_blended_pal(char *, s32, s32, s32);
extern void moby_transform_joint_to_world(char *, s32, char *);
extern void moby_transform_joint_point(char *, s32, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char *projectile_l09_spawn_pal(char *, char *, char *, s32, s32, float, float, float, float);
extern void FastVecSub(char *, void *, char *);
extern char *part_spawn_blast_effect_moby_pal(char *, char *, char *, float);
extern void SetDeathBits_pal(char *, s32, s32);
extern void moby_mark_spawned(char *);
extern int g_hero_vehicle_mode;
extern int g_level_l20_progress_stage __attribute__((nosda));
extern int g_frame_l20_counter;
extern void *g_camera_l20_position[];
extern float g_yeedil_enemy_speed __attribute__((sda));
extern float g_yeedil_enemy_scale __attribute__((sda));
extern u8 g_moby_group_flags[] __attribute__((nosda));
extern u8 g_collectable_group_flags[] __attribute__((nosda));
extern s32 g_current_map_index __attribute__((sda));

/* Runs the per-frame states of this enemy: it picks its animation by state, spreads a trail effect while it walks, and removes itself when it dies. */
void yeedil_enemy_update_pal(char *moby)
{
    char buf_a[0x10];
    char buf_b[0x40];
    char buf_c[0x10];
    char *state;

    state = *(char **)(moby + 0x68);
    object_life_timer_update_pal(moby);
    if (g_hero_vehicle_mode == 2 && g_level_l20_progress_stage >= 5) {
        moby_mark_spawned(moby);
        return;
    }
    switch (*(u8 *)(moby + 0x20)) {
    case 2:
        if (flag_set_first_pending(moby) != 0 && *(u8 *)(moby + 0x43) != 0)
            anim_start_blended_pal(moby, 0, 0, 0x8);
        if (*(u8 *)(moby + 0x31) != 0 && *(u16 *)(moby + 0x96) >= 0x97)
            moby_set_state(moby, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(moby) != 0 && *(u8 *)(moby + 0x43) != 1)
            anim_start_blended_pal(moby, 1, 0, 0xC);
        if ((g_frame_l20_counter & 0xF) == (((int)moby >> 8) & 0xF)) {
            moby_transform_joint_to_world(moby, 2, buf_a);
            moby_transform_joint_point(moby, 2, buf_b);
            vec_scale_to_length(buf_c, buf_b, g_yeedil_enemy_speed * 0.020000001f);
            projectile_l09_spawn_pal(buf_a, moby, buf_c, 1, 1, (float)*(u8 *)(state + 0x34),
                              g_yeedil_enemy_scale, 1.0f, 1.0f);
        }
        if (*(u8 *)(moby + 0x31) == 0 || *(u16 *)(moby + 0x96) >= 0x97)
            moby_set_state(moby, 2, -1);
        break;
    case 4:
        if (flag_set_first_pending(moby) != 0 && *(u8 *)(moby + 0x43) != 2)
            anim_start_blended_pal(moby, 2, 0, 0x8);
        if (*(u8 *)(moby + 0x60) & 0x2)
            moby_set_state(moby, 2, -1);
        break;
    case 5:
        FastVecSub(buf_a, g_camera_l20_position, moby + 0x10);
        vec_scale_to_length(buf_a, buf_a, 1.0f);
        part_spawn_blast_effect_moby_pal(moby, moby + 0x10, buf_a, 0.0f);
        SetDeathBits_pal(moby, 0, 3);
        moby_mark_spawned(moby);
        return;
    default:
        break;
    case 1:
        return;
    }
    trooper_aim_at_target_pal(moby);
}
