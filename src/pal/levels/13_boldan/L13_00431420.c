#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
typedef int s32;
typedef unsigned int u32;
typedef unsigned short u16;
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
extern int PlayMobySound(s32, s32, u8 *);
extern float math_step_value_toward_target(f32 *, f32 *, f32, f32, f32, f32);
extern s32 func_2AF870(u8 *);
extern u8 g_str_rising_platform_sound[];

void func_PAL_L13_00431420(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    if (a0[0x20] == 0) {
        *(u16 *)(a0 + 0x34) |= 0x800;
        *(f32 *)(ptr + 0x8) = *(f32 *)(a0 + 0x18);
        *(f32 *)(ptr + 0x4) = *(f32 *)(a0 + 0x18) - 6.0f;
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        u8 v = *((u8 *)g_object_table_base[0] + (*(u32 *)ptr << 8) + 0x20);
        if (v == 2) {
            PlayMobySound(0, 0, a0);
            a0[0x20] = v;
        }
    }
    if (a0[0x20] == 2) {
        math_step_value_toward_target((f32 *)(a0 + 0x18), (f32 *)(ptr + 0xC), *(f32 *)(ptr + 0x4),
                      0.0024f, 0.0024f, 0.24000001f);
    }
}


extern void STUB_printf(u8 *);
extern void STUB_printf(u8 *);

void func_PAL_L13_00431518(u8 *a0) {
    u8 *ptr = *(u8 **)(a0 + 0x68);
    if (a0[0x20] == 0) {
        *(u16 *)(a0 + 0x34) |= 0x800;
        *(f32 *)(ptr + 0x8) = *(f32 *)(a0 + 0x18);
        *(f32 *)(ptr + 0x4) = *(f32 *)(a0 + 0x18) - 6.0f;
        a0[0x20] = 1;
    }
    if (a0[0x20] == 1) {
        u8 v = *((u8 *)g_object_table_base[0] + (*(u32 *)ptr << 8) + 0x20);
        if (v == 2) {
            a0[0x20] = v;
            STUB_printf(g_str_rising_platform_sound);
        }
    }
    if (a0[0x20] == 2) {
        math_step_value_toward_target((f32 *)(a0 + 0x18), (f32 *)(ptr + 0xC), *(f32 *)(ptr + 0x4),
                    0.0024f, 0.0024f, 0.24000001f);
    }
}

