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

void func_PAL_L13_00402E14(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    f32 vec[4];

    if (*(s32 *)ptr != 0) {
        if (vec_distance_xy(a0 + 0x10, g_hero_position) < 8.0f) {
            if (a0[0x20] == 0) {
                a0[0x20] = 1;
            }
        }
    } else if (*(s32 *)(ptr + 8) != 0) {
        if (fast_vec_dist(a0 + 0x10, g_hero_position) < 8.0f) {
            if (a0[0x20] == 0) {
                if (*(s16 *)(g_hero_position + 0x2C8) == 1) {
                    a0[0x20] = 2;
                }
            }
        }
    } else {
        if (a0[0x20] == 0) {
            *(u32 *)(a0 + 0x98) = 0;
            a0[0x20] = 3;
        }
    }

    if (a0[0x20] == 1) {
        math_approach_target_with_direction_mode(a0 + 0xF8, ptr + 4, -0.78539824f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (a0[0x20] == 2) {
        math_approach_target_with_direction_mode(a0 + 0xF8, ptr + 4, -1.5707965f, 0.0025132746f, 0.0025132746f, 0.04188791f, 0);
    }
    if (a0[0x20] == 4) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
        vec_scale_to_length(vec, a0 + 0xD0, -0.20000002f);
        FastVecAdd(a0 + 0x10, a0 + 0x10, vec);
        if (*(u16 *)(a0 + 0x96) >= 11) {
            *(u16 *)(a0 + 0x96) = 0;
            a0[0x20] = 5;
        }
    }
    if (a0[0x20] == 5) {
        u32 c = *(u16 *)(a0 + 0x96) + 1;

        *(u16 *)(a0 + 0x96) = c;
        if ((u16)c >= 31) {
            *(u16 *)(a0 + 0x96) = 0;
            a0[0x20] = 6;
        }
    }
    if (a0[0x20] == 6) {
        *(u16 *)(a0 + 0x96) = *(u16 *)(a0 + 0x96) + 1;
        vec_scale_to_length(vec, a0 + 0xD0, 0.20000002f);
        FastVecAdd(a0 + 0x10, a0 + 0x10, vec);
        if (*(u16 *)(a0 + 0x96) >= 11) {
            a0[0x20] = 0;
        }
    }
}



