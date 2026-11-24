#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: every body here reaches a global through $gp.
   The small-data symbols are declared with the sda attribute, which makes the
   compiler emit the bare GPREL16 form; the type needs a size at most the -G8
   threshold, and the typedefs have to come before the externs. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed long long s64;
typedef float f32;

/* 0x1AEFF0 + 0xF10 : the level word func_L20_002B93E0 reads through $gp. */
extern s32 g_hero_hazard_flag __attribute__((sda));

/* 0x1AEFF0 - 0x7C60 : the word the retail reads both absolutely and through
   $gp, so it needs two names: the sda one is the $gp form, the plain one the
   absolute form.  A plain extern is the absolute form here: marking it nosda
   makes cc1 keep the address in a register of its own and the load does not
   match the retail any more (see nonmatching/levels/func_L20_002B93E0.c). */
extern s32 g_frame_counter __attribute__((sda));
extern s32 D_001A7390_1;

/* 0x1AEFF0 - 0x72F8 : the float the retail copies through $gp. */
extern float g_hero_float_param __attribute__((sda));

/* 0x1AEFF0 - 0x7660 : the word the retail reads absolutely (plain extern, see
   the note on D_001A7390_1 above). */
extern s32 g_current_map_index;

/* 0x140000 - 0x69A2 : the byte the retail reads absolutely. */
extern u8 g_hero_frame_flag __attribute__((nosda));

extern char g_hero_state[];
extern char g_hero_position[];
extern char g_subtitle_history[];
extern float g_hero_frame_time __attribute__((nosda));

/* The calls func_L20_002B93E0 makes. */
extern void AdvanceHeroAnimation(void);
extern void hero_update_frame_input(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab(char *, char *, char *);
extern void UpdateHeroMotionResponseParameters(void);
extern s32 FastDecTimer(s32);
extern s32 hero_l20_set_move_state(s32, s32);
extern s32 subtitle_request_voice_line(s32, s32);
extern void hero_l20_decide_state_transition(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds(void);
extern void attachment_update_all(void);
extern void hero_update_moby_from_hero(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void UpdateHeroGlowAndExtraManipulators(void);
extern void UpdateHeroJointEffect(void);
extern void hero_update_held_object(void);
extern int PlayMobySound(void *, void *, void *);
extern void coll_clear_map_bits_around_pos(void *);
extern s32 receiver_bot_start_sequence(s32);
extern void UpdateHeroMobyProbedHeightBounds(void);
extern void func_002A677C(s32);

/* The hero's per-frame update: the state-1 fixups, then in state 4 (outside cutscenes, not
   in mode 0x6F) the arming check and the resident timestamp catch-up; then the sub-updates,
   gated twice more by the state byte, and the hand-off of the hero's record. Same game code as
   func_L18_002C41F0. */
/* Runs the hero once per frame: checks for damage, updates timers and hands the hero over to the game. */
void hero_l20_update_frame(void)
{
    char *base;
    char *blk;
    char *hero;
    unsigned int now;
    unsigned int then;

    AdvanceHeroAnimation();
    hero_update_frame_input();
    hero_process_action_command();

    base = g_hero_state;
    if (*(u8 *)(base + 0x22B4) == 1) {
        hero_find_ledge_grab(base + 0x80, base + 0x90, base + 0x550);
        UpdateHeroMotionResponseParameters();
    }
    if (*(u8 *)(base + 0x22B4) == 4) {
        if (g_hero_hazard_flag == 0) {
            if (*(s16 *)(base + 0x1E0) == 0) {
                if (*(int *)(base + 0x2294) != 0x6F) {
                    if (FastDecTimer(*(int *)(*(int *)(base + 0x2290) + 0x68) + 0x3BC) != 0) {
                        *(int *)(base + 0x24CC) = 0;
                        hero_l20_set_move_state(0x91, 1);
                    }
                    if (g_current_map_index == 0x14) {
                        if (g_hero_frame_flag == 0) {
                            blk = g_subtitle_history;
                            if (D_001A7390_1 - *(unsigned int *)(blk + 0x7900) >= 0xB5) {
                                if (subtitle_request_voice_line(0xA15, 0x6C) != 0) {
                                    now = g_frame_counter;
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

    base = g_hero_state;
    hero_l20_decide_state_transition();
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
    if (*(u8 *)(base + 0x22B4) == 1) {
        g_hero_frame_time = g_hero_float_param;
        UpdateHeroGlowAndExtraManipulators();
        UpdateHeroJointEffect();
        hero_update_held_object();
        if (*(u32 *)(base + 0x24E4) != 0) {
            PlayMobySound((void *)(*(u32 *)(base + 0x24E4) + 0x10), 0,
                          (void *)(*(u32 *)(base + 0x2290)));
            *(u16 *)(base + 0x2520) = 0x39;
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
