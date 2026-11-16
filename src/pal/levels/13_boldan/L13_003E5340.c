#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;
typedef short s16;
typedef int s32;
typedef unsigned short u16;
typedef unsigned int u32;
extern f32 FastAddRotations(f32, f32);
extern f32 g_hero_l13_height_limit __attribute__((sda));
extern u8 g_str_rising_platform_sound[];
extern u8 g_moby_group_flags[];
extern u8 *g_moby_slot_table __attribute__((sda));
extern u8 *D_L13_001B291C_2;
extern u8 g_hero_state[];
extern f32 vec_distance_xy(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern u8 g_hero_position[];
extern u8 g_sound_state[];
extern u8 g_str_linked_door_msg_a[];
extern u8 g_str_linked_door_msg_b[];
extern u8 g_game_flag_table[];
extern u8 g_str_rising_platform_sound[];

void func_PAL_L13_003E5340(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.020943955f);
}


void func_PAL_L13_003E5378(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.020943955f);
}


void func_PAL_L13_003E53B0(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.03490659f);
}


void func_PAL_L13_003E53E8(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.020943955f);
}


void func_PAL_L13_003E5420(u8 *a0) {
    *(f32 *)(a0 + 0xF4) = FastAddRotations(*(f32 *)(a0 + 0xF4), 0.020943955f);
}


extern u8 g_hero_position[];
extern u8 g_progress_statistics[];
extern u32 g_frame_counter[] __attribute__((sda));
extern u8 g_item_enabled_flags[] __attribute__((sda));
extern s32 g_scene_trigger_flag[] __attribute__((sda));
extern s32 g_hint_index;
extern s32 IsPointInCuboid(void *a0, s32 a1);
extern int snd_play_from_global_bank(s32 a0, s32 a1, s32 a2);
extern void value_set_entry_by_index_pal(s32 a0, s32 a1);
extern int func_PAL_00289730(s32 a0, s32 a1);

/* func_PAL_L13_003EC9C0, the PAL copy of func_L13_003E8850: the same C, where the frame counter is scaled to 50 Hz and 0x69780 becomes 0x57E40. */
void func_PAL_L13_003EC9C0(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    s16 h;
    u8 *hero;
    u8 *timers;
    u8 *counters;

    if (self[0x20] == 0) {
        self[0x30] = 0xFF;
        *(s16 *)(state + 0xC) = 0;
        self[0x20] = 1;
    }
    if (self[0x20] != 1)
        return;
    h = *(s16 *)(state + 0xE);
    switch (h) {
    case 0:
        if (IsPointInCuboid(g_hero_position, *(s32 *)(state + 4)) != 0 && *(s32 *)(g_hero_position + 0x221C) == 0xF)
            *(s16 *)(state + 0xE) = 1;
        break;
    case 1:
        hero = g_hero_state;
        if (*(s32 *)(hero + 0x2294) == 0x3E) {
            *(s16 *)(state + 0xE) = 0;
        } else if (IsPointInCuboid(hero + 0x80, *(s32 *)(state + 8)) != 0 && g_item_enabled_flags[4] == 0) {
            g_item_enabled_flags[4] = 1;
            snd_play_from_global_bank(1, 0, 0);
            value_set_entry_by_index_pal(0x1233, -1);
            g_scene_trigger_flag[0] = 1;
        }
        break;
    }
    if (IsPointInCuboid(g_hero_position, *(s32 *)state) == 0)
        return;
    timers = g_progress_statistics;
    if (*(u16 *)(timers + 0x1BC) != 0 && !((((int)(g_frame_counter[0]) * 5 + 2) / 6) - *(u32 *)(timers + 0x1C0) > 0x57E40))
        return;
    counters = g_game_flag_table;
    if (counters[0x7E] < 2 && *(s16 *)(state + 0xC) == 0) {
        if (g_hint_index >= 0)
            func_PAL_00289730(0x9E3, 0x3A);
        counters[0x7E] = counters[0x7E] + 1;
        *(s16 *)(state + 0xC) = 1;
    }
}
