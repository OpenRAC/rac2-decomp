#include "include_asm.h"
#include "names.h"

/* func_PAL_L20_002B9270, the PAL copy of func_L20_002B93E0: the same C, where the resident
   counter is scaled to 50 Hz at each use, every read of it goes through $gp, the 0xB5
   threshold becomes 0x97 and the 0x39 hand-off id becomes 0x2F. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;

extern s32 g_hero_hazard_flag __attribute__((sda));
extern s32 g_frame_counter __attribute__((sda));
extern float g_hero_float_param __attribute__((sda));
extern s32 g_current_map_index;
extern u8 g_hero_frame_flag __attribute__((nosda));

extern char g_hero_state[];
extern char g_hero_position[];
extern char g_subtitle_history[];
extern float g_hero_frame_time __attribute__((nosda));

extern void func_PAL_L00_002D29E8(void);
extern void hero_update_frame_input_pal(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab_pal(char *, char *, char *);
extern void UpdateHeroMotionResponseParameters_pal(void);
extern s32 FastDecTimer(s32);
extern s32 func_PAL_L20_002D7920(s32, s32);
extern s32 func_PAL_00289730(s32, s32);
extern void hero_l20_decide_state_transition(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds_pal(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void UpdateHeroGlowAndExtraManipulators_pal(void);
extern void UpdateHeroJointEffect_pal(void);
extern void hero_update_held_object_pal(void);
extern int PlayMobySound(void *, void *, void *);
extern void coll_clear_map_bits_around_pos(void *);
extern s32 receiver_bot_start_sequence(s32);
extern void UpdateHeroMobyProbedHeightBounds(void);
extern void func_002A677C(s32);

/* The hero's per-frame update: the state-1 fixups, then in state 4 (outside cutscenes, not
   in mode 0x6F) the arming check and the resident timestamp catch-up; then the sub-updates,
   gated twice more by the state byte, and the hand-off of the hero's record. Same game code as
   func_L18_002C41F0. */
void func_PAL_L20_002B9270(void)
{
    char *base;
    char *blk;
    char *hero;

    func_PAL_L00_002D29E8();
    hero_update_frame_input_pal();
    hero_process_action_command();

    base = g_hero_state;
    if (*(u8 *)(base + 0x22B4) == 1) {
        hero_find_ledge_grab_pal(base + 0x80, base + 0x90, base + 0x550);
        UpdateHeroMotionResponseParameters_pal();
    }
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (g_hero_hazard_flag == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (FastDecTimer(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        func_PAL_L20_002D7920(0x91, 1);
                    }
                    if (g_current_map_index == 0x14) {
                        if (g_hero_frame_flag == 0) {
                            blk = g_subtitle_history;
                            if (((s32)g_frame_counter * 5 + 2) / 6 - *(unsigned int *)(blk + 0x7900) >= 0x97) {
                                if (func_PAL_00289730(0xA15, 0x6C) != 0) {
                                    if (*(unsigned int *)(blk + 0x7900) < ((s32)g_frame_counter * 5 + 2) / 6) {
                                        *(unsigned int *)(blk + 0x7900) = ((s32)g_frame_counter * 5 + 2) / 6;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    base = g_hero_state;
    hero_l20_decide_state_transition();
    RebuildRegionObjectMembership();

    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    UpdateDelayedSounds_pal();
    attachment_update_all();
    if (*(u8 *)(base + 0x22B4) == 0)
        return;
    hero_update_moby_from_hero();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    if (*(u8 *)(base + 0x22B4) == 1) {
        g_hero_frame_time = g_hero_float_param;
        UpdateHeroGlowAndExtraManipulators_pal();
        UpdateHeroJointEffect_pal();
        hero_update_held_object_pal();
        if (*(u32 *)(base + 0x24E4) != 0) {
            PlayMobySound((void *)(*(u32 *)(base + 0x24E4) + 0x10), 0,
                          (void *)(*(u32 *)(base + 0x2290)));
            *(u16 *)(base + 0x2520) = 0x2f;
            *(u16 *)(base + 0x2522) = *(u16 *)(base + 0x24E4);
        }
        *(s32 *)(base + 0x24E4) = 0;
    }
    {
        char *pos = g_hero_position;
        char *g;

        coll_clear_map_bits_around_pos(pos);
        g = pos - 0x80;
        if (*(u8 *)(g + 0x22B4) == 4 && g_hero_hazard_flag == 0 && *(s16 *)(g + 0x1E0) == 0 &&
            *(int *)(g + 0x2294) != 0x6F)
            receiver_bot_start_sequence(*(int *)(g + 0x2290));
    }
    UpdateHeroMobyProbedHeightBounds();
    hero = g_hero_state;
    func_002A677C(*(int *)(hero + 0x2290));
}
