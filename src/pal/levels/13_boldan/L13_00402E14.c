#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
typedef short s16;
extern f32 func_2F9748(f32, f32);
extern s32 func_32A4D0(u8 *, s32);
extern void func_31A718(u8 *);
extern void func_3248E0(u8 *, s32, s32);
extern s32 func_2AF870(u8 *);
extern f32 g_hero_l13_height_limit __attribute__((sda));
extern u32 g_object_table_base[] __attribute__((sda));
extern u8 g_str_rising_platform_sound[];
extern u8 g_moby_group_flags[];
extern s32 g_current_map_index __attribute__((sda));
extern u8 *g_moby_slot_table __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 g_hero_state[];
extern int g_current_map_index __attribute__((sda));
extern f32 vec_distance_xy(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern f32 math_approach_target_with_direction_mode(void *, void *, f32, f32, f32, f32, s32);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern u8 g_str_linked_door_msg_a[];
extern u8 g_str_linked_door_msg_b[];
extern u16 *g_door_list_table[];
extern s32 g_level_l13_progress_stage __attribute__((sda));
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 flag_set_first_pending(u8 *);
extern s32 snd_start_in_slot(s32, s32, u8 *);
extern s32 math_fast_float_d(u8 *);
extern s32 IsPointInCuboid(u8 *, s32);
extern u8 g_game_flag_table[];
extern s32 func_2AF870(u8 *);
extern u8 g_str_rising_platform_sound[];

/* Lift arm that tilts down: turns toward -45 degrees when the hero is near, or -90 when the hero stands on it, then pushes itself away and back. */
void lift_arm_tilt_down_update_pal(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    f32 vec[4];

    if (*(s32 *)vars != 0) {
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                moby[0x20] = 1;
            }
        }
    } else if (*(s32 *)(vars + 8) != 0) {
        if (fast_vec_dist(moby + 0x10, g_hero_position) < 8.0f) {
            if (moby[0x20] == 0) {
                if (*(s16 *)(g_hero_position + 0x2C8) == 1) {
                    moby[0x20] = 2;
                }
            }
        }
    } else {
        if (moby[0x20] == 0) {
            *(u32 *)(moby + 0x98) = 0;
            moby[0x20] = 3;
        }
    }

    if (moby[0x20] == 1) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, -0.78539824f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (moby[0x20] == 2) {
        math_approach_target_with_direction_mode(moby + 0xF8, vars + 4, -1.5707965f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (moby[0x20] == 4) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(vec, moby + 0xD0, -0.20000002f);
        FastVecAdd(moby + 0x10, moby + 0x10, vec);
        if (*(u16 *)(moby + 0x96) >= 11) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 5;
        }
    }
    if (moby[0x20] == 5) {
        u32 count = *(u16 *)(moby + 0x96) + 1;

        *(u16 *)(moby + 0x96) = count;
        if ((u16)count >= 31) {
            *(u16 *)(moby + 0x96) = 0;
            moby[0x20] = 6;
        }
    }
    if (moby[0x20] == 6) {
        *(u16 *)(moby + 0x96) = *(u16 *)(moby + 0x96) + 1;
        vec_scale_to_length(vec, moby + 0xD0, 0.20000002f);
        FastVecAdd(moby + 0x10, moby + 0x10, vec);
        if (*(u16 *)(moby + 0x96) >= 11) {
            moby[0x20] = 0;
        }
    }
}



