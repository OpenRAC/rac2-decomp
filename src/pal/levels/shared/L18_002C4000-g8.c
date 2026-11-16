#include "include_asm.h"
#include "names.h"

/* func_PAL_L18_002C4000, the PAL copy of func_L18_002C41F0: the same C, where the resident
   counter is scaled to 50 Hz at each use, every read of it goes through $gp, and the 0xB5
   threshold becomes 0x97. */
typedef unsigned char u8;
typedef short s16;
typedef int s32;

extern char g_hero_state[];
extern char g_subtitle_history[];
extern unsigned char g_hero_frame_flag __attribute__((nosda));
extern int g_current_map_index;
extern int g_hero_frozen_flag;
extern int D_L18_001AFBB0_sda __attribute__((sda));
extern int D_001A7390_sda __attribute__((sda));

extern void AdvanceHeroAnimation_pal(void);
extern void hero_update_frame_input_pal(void);
extern void ref_L18_002C41F0_00(void);
extern int FastDecTimer(int a0);
extern void ref_L18_002C41F0_01(int a0, int a1);
extern int subtitle_request_voice_line_pal(int a0, int a1);
extern void ref_L18_002C41F0_02(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds_pal(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern s32 receiver_bot_start_sequence(void *a0);
extern void UpdateHeroMobyProbedHeightBounds(void);
extern void func_002A677C(int a0);

/* Runs once per frame for the hero: handles the frame input, the held-object timer, sounds, attachments and the collision cleanup (PAL: 50 Hz timings). */
void hero_l18_update_frame_pal(void)
{
    char *base;
    char *hero;
    char *blk;

    AdvanceHeroAnimation_pal();
    hero_update_frame_input_pal();
    ref_L18_002C41F0_00();

    base = g_hero_state;
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (g_hero_frozen_flag == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (FastDecTimer(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        ref_L18_002C41F0_01(0x91, 1);
                    }
                    if (g_current_map_index == 0x14) {
                        if (g_hero_frame_flag == 0) {
                            blk = g_subtitle_history;
                            if (((s32)D_001A7390_sda * 5 + 2) / 6 - *(unsigned int *)(blk + 0x7900) >= 0x97) {
                                if (subtitle_request_voice_line_pal(0xA15, 0x6C) != 0) {
                                    if (*(unsigned int *)(blk + 0x7900) < ((s32)D_001A7390_sda * 5 + 2) / 6) {
                                        *(unsigned int *)(blk + 0x7900) = ((s32)D_001A7390_sda * 5 + 2) / 6;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    ref_L18_002C41F0_02();

    base = g_hero_state;
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
    coll_clear_map_bits_around_pos(base + 0x80);
    if (*(u8 *)(base + 0x22B4) == 4 && D_L18_001AFBB0_sda == 0 && *(s16 *)(base + 0x1E0) == 0 &&
        *(int *)(base + 0x2294) != 0x6F) {
        receiver_bot_start_sequence(*(int *)(base + 0x2290));
    }
    UpdateHeroMobyProbedHeightBounds();
    hero = g_hero_state;
    func_002A677C(*(int *)(hero + 0x2290));
}
