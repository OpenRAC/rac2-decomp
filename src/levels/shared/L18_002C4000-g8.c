#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

/* The hero state block, and the second block the frame counter lives in. Both are
   resident (below 0x1A7C80), so every level sees them at the same address. */
extern char g_hero_state[];
extern char g_subtitle_history[];

/* A byte global read as an absolute (its low half has bit 15 set, so it needs the
   %hi/%lo pair), and the two counters read the same way. */
extern unsigned char g_hero_frame_flag __attribute__((nosda));
extern int g_current_map_index;
extern int g_frame_counter;

/* The counter the level publishes in its literal pool: read absolutely in the
   first block and through $gp in the second, so it needs two names. */
extern int g_hero_frozen_flag;
extern int D_L18_001AFBB0_sda __attribute__((sda));

/* The resident counter, likewise read absolutely once and through $gp once. */
extern int D_001A7390_sda __attribute__((sda));

extern void AdvanceHeroAnimation(void);
extern void hero_update_frame_input(void);
extern void ref_L18_002C41F0_00(void);
extern int FastDecTimer(int a0);
extern void ref_L18_002C41F0_01(int a0, int a1);
extern int subtitle_request_voice_line(int a0, int a1);
extern void ref_L18_002C41F0_02(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern int receiver_bot_start_sequence(void *a0);
extern void UpdateHeroMobyProbedHeightBounds(void);
extern void func_002A677C(void *a0);

/* One frame of level 18's hero update. Three openers run, then the hero block
   gates a block of work: the state byte has to be 4, the level's own counter has
   to be clear, the hero has to be idle and its state word must not be 0x6F. Inside
   that, a helper may arm the hero (the state word is cleared and a message is
   sent), then the frame counter and a byte global gate a second block that keeps
   a timestamp in step with the resident one. The closing half always runs: the
   sub-updates are gated twice more by the state byte, and the last of them hands
   the hero's record to a helper. */
/* Runs one frame of the player update for this level. */
void hero_l18_update_frame(void)
{
    char *base;
    char *hero;
    char *blk;
    unsigned int now;
    unsigned int then;

    AdvanceHeroAnimation();
    hero_update_frame_input();
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
                            if (g_frame_counter - *(unsigned int *)(blk + 0x7900) >= 0xB5) {
                                if (subtitle_request_voice_line(0xA15, 0x6C) != 0) {
                                    now = D_001A7390_sda;
                                    then = *(unsigned int *)(blk + 0x7900);
                                    if (then < now) {
                                        *(unsigned int *)(blk + 0x7900) = now;
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
    UpdateDelayedSounds();
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

/* The group id lists and the entity bank base are read absolutely, the resident group count
   through $gp. */
extern unsigned int g_condition_target_lists[];
extern char *g_moby_l18_table;
extern int g_max_l18_group_index __attribute__((sda));
extern void protopet_choose_anim_if_active(unsigned char *a0);

/* Walks the id list of the object's group and hands every entity it names to
   func_L18_003F7A88. Retail's loop is not rotated (the test sits below the body); the second
   `q != 0` in the condition keeps the test from being copied in front of the loop. */
/* Goes through every object in the same group as this one and updates each of them. */
void group_update_members(unsigned char *object)
{
    unsigned short *idList;
    unsigned char *member;

    if (object[0x21] == 0xFF)
        return;
    idList = (unsigned short *)g_condition_target_lists[object[0x21]];
    while (object[0x21] != 0xFF && object[0x21] <= g_max_l18_group_index && idList != 0 &&
           ((idList != 0 && (short)idList[-1] >= 0) || idList == (unsigned short *)g_condition_target_lists[object[0x21]])) {
        member = (unsigned char *)(g_moby_l18_table + ((*idList & 0x7FFF) << 8));
        if (member == 0)
            break;
        protopet_choose_anim_if_active(member);
        idList++;
    }
}
