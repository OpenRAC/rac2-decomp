#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed int s32;
extern void moby_set_state(char *, int, int);
extern void object_life_timer_update_pal(char *);
extern void trooper_aim_at_target_pal(char *);
extern s32 flag_set_first_pending(char *);
extern void func_PAL_002A7E68(char *, s32, s32, s32);
extern void moby_transform_joint_to_world(char *, s32, char *);
extern void moby_transform_joint_point(char *, s32, char *);
extern void vec_scale_to_length(char *, char *, float);
extern char *func_PAL_L09_003B20E8(char *, char *, char *, s32, s32, float, float, float, float);
extern void FastVecSub(char *, void *, char *);
extern char *func_PAL_0032F3B8(char *, char *, char *, float);
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

void yeedil_enemy_update_pal(char *arg0)
{
    char bufA[0x10];
    char bufB[0x40];
    char bufC[0x10];
    char *state;

    state = *(char **)(arg0 + 0x68);
    object_life_timer_update_pal(arg0);
    if (g_hero_vehicle_mode == 2 && g_level_l20_progress_stage >= 5) {
        moby_mark_spawned(arg0);
        return;
    }
    switch (*(u8 *)(arg0 + 0x20)) {
    case 2:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 0)
            func_PAL_002A7E68(arg0, 0, 0, 0x8);
        if (*(u8 *)(arg0 + 0x31) != 0 && *(u16 *)(arg0 + 0x96) >= 0x97)
            moby_set_state(arg0, 3, -1);
        break;
    case 3:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 1)
            func_PAL_002A7E68(arg0, 1, 0, 0xC);
        if ((g_frame_l20_counter & 0xF) == (((int)arg0 >> 8) & 0xF)) {
            moby_transform_joint_to_world(arg0, 2, bufA);
            moby_transform_joint_point(arg0, 2, bufB);
            vec_scale_to_length(bufC, bufB, g_yeedil_enemy_speed * 0.020000001f);
            func_PAL_L09_003B20E8(bufA, arg0, bufC, 1, 1, (float)*(u8 *)(state + 0x34),
                              g_yeedil_enemy_scale, 1.0f, 1.0f);
        }
        if (*(u8 *)(arg0 + 0x31) == 0 || *(u16 *)(arg0 + 0x96) >= 0x97)
            moby_set_state(arg0, 2, -1);
        break;
    case 4:
        if (flag_set_first_pending(arg0) != 0 && *(u8 *)(arg0 + 0x43) != 2)
            func_PAL_002A7E68(arg0, 2, 0, 0x8);
        if (*(u8 *)(arg0 + 0x60) & 0x2)
            moby_set_state(arg0, 2, -1);
        break;
    case 5:
        FastVecSub(bufA, g_camera_l20_position, arg0 + 0x10);
        vec_scale_to_length(bufA, bufA, 1.0f);
        func_PAL_0032F3B8(arg0, arg0 + 0x10, bufA, 0.0f);
        SetDeathBits_pal(arg0, 0, 3);
        moby_mark_spawned(arg0);
        return;
    default:
        break;
    case 1:
        return;
    }
    trooper_aim_at_target_pal(arg0);
}
