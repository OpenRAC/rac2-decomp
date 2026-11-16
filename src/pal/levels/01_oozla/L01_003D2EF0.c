#include "include_asm.h"
#include "common.h"

/* func_PAL_L01_003D2EF0, the PAL copy of func_L01_003CEDA0: the same C, where the turn rate takes
   6/5, the subtitle timer's 180 frames and each read of the frame counter take the 5/6 scale. */
extern void moby_mark_spawned(void *a0);
extern void moby_set_state(void *a0, s32 a1, s32 a2);
extern u8 *g_moby_l01_table __attribute__((sda));
extern u8 g_swamp_cutscene_flag __attribute__((sda));
extern u8 g_subtitle_history[];
extern u8 g_hero_position[];
extern u8 g_cutscene_vars[];
extern u8 *g_swamp_patrol_positions __attribute__((sda));
extern int g_hero_l01_control_mode __attribute__((sda));
extern int g_cutscene_flag __attribute__((sda));
extern float g_hero_l01_reach_timer_b __attribute__((sda));
extern u32 g_frame_counter __attribute__((sda));
extern float FastAddRotations(float, float);
extern int IsPointInCuboid(void *, int);
extern int req_push_queue(void *, int);
extern s32 req_launch_queued(void *);
extern void func_PAL_L01_003D2C38(void *);
extern int game_is_either_mode_two(void);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void help_unlock_entry(int);
extern int moby_handle_request_slot_state(int);
extern void value_set_entry_by_index(int, int);
extern int MemcardSave(int, int);
extern void cam_lock_entry(int);
extern int subtitle_request_voice_line(int, int);

void func_PAL_L01_003D2EF0(u8 *a0)
{
    u8 *p = *(u8 **)(a0 + 0x68), *q;
    int mode;

    switch (a0[0x20]) {
    case 0:
        if (g_swamp_cutscene_flag) {
            moby_mark_spawned(a0);
            break;
        }
        *(float *)(a0 + 0x18) += 0.75f;
        *(float *)(a0 + 0x2C) = *(float *)(*(u8 **)(a0 + 0x24) + 0x24) * 1.5f;
        moby_set_state(a0, 1, -1);
        break;
    case 1:
        *(float *)(a0 + 0xF8) = FastAddRotations(*(float *)(a0 + 0xF8), 0.094247796f);
        if (IsPointInCuboid(g_hero_position, *(int *)(p + 4))) {
            p = g_cutscene_vars;
            if (req_push_queue(p, 0x26)) {
                req_launch_queued(p);
                moby_set_state(a0, 2, -1);
            }
        }
        if (a0[0x31])
            func_PAL_L01_003D2C38(a0);
        break;
    case 2:
        mode = g_hero_l01_control_mode;
        (*(u16 *)(a0 + 0x96))++;
        if (mode == 2) {
            a0[0x31] = 0;
            *(u16 *)(a0 + 0x34) |= 1;
        }
        if (game_is_either_mode_two())
            break;
        q = g_swamp_patrol_positions + (*(int *)(p + 8) << 7);
        g_cutscene_flag = 0;
        g_hero_l01_reach_timer_b = 0;
        hero_reset_position_and_direction(q + 0x30, q + 0x70, 0x6F, 1);
        help_unlock_entry(0x24);
        moby_handle_request_slot_state(0x24);
        value_set_entry_by_index(0x1225, -1);
        MemcardSave(0, -1);
        if (*(int *)(p + 12) != -1) {
            p = *(u8 **)(g_moby_l01_table + (*(int *)(p + 12) << 8) + 0x68);
            if (!*(int *)(p + 0x3C)) {
                cam_lock_entry(*(int *)(p + 0x38));
                *(int *)(p + 0x3C) = 1;
            }
            p = g_subtitle_history;
            if (!*(u16 *)(p + 0xC0)) {
                u16 elapsed = *(u16 *)(p + 0xC2);
                u32 start = *(u32 *)(p + 0xC4);
                u32 now = g_frame_counter;

                if (start + elapsed >= ((s32)(now) * 5 + 2) / 6 - 2) {
                    *(u16 *)(p + 0xC2) = ++elapsed;
                    if (elapsed >= ((s32)(180) * 5 + 2) / 6) {
                        subtitle_request_voice_line(0x9B9, 0x10);
                        *(u16 *)(p + 0xC2) = 0;
                    }
                } else {
                    if (start < ((s32)(now) * 5 + 2) / 6)
                        *(u32 *)(p + 0xC4) = ((s32)(now) * 5 + 2) / 6;
                    *(u16 *)(p + 0xC2) = 0;
                }
            }
        }
        moby_mark_spawned(a0);
        break;
    }
}
