#include "names.h"
/* Player frame update: the ordered resident-player steps while control is active.
   The player record is reached through pointer locals (one per stretch, sharing the
   %hi of D_00189E20) and the control mode is a macro-addressed word. */
#include "common.h"
/*
 * Retained handwritten near miss; historical evidence only.
 * No linked-image equality or complete retail semantics is established.
 * Compiler: game EE-GCC 2.9-ee-991111b (project profile).
 * Profile: -O2 -G0 -ffunction-sections.
 * Reported final C / retail: 552 / 556 bytes; size equality is not a match.
 * us: 0/13 placements; 552/556 bytes.
 * us2: absent from catalogue (not a match).
 * pal: absent from catalogue (not a match).
 * Residual: The 552/556-byte form hoists the repeated position address and saves an additional GPR. Disabling GCSE and using documented position/root views did not close the gap.
 * Reopening condition: Reopen only after independent source, data-layout, ABI or compiler evidence specifically explains the residual above; then test that single hypothesis. Do not repeat tied source forms or flag sweeps.
 * Where listed, tools/check.py measurements predate retention; no compilation was rerun for this copy.
 */

/* Readable manual reconstruction, measured 2026-10-23.
 * Retained profile: -O2 -G0 -ffunction-sections.
 * us: 0 of 13 places match; exit 1.
 * us2: absent from both catalogues (exit 1).
 * pal: absent from both catalogues (exit 1).
 * The 552/556-byte form hoists the repeated position address and saves an additional GPR. Disabling GCSE and using documented position/root views did not close the gap.
 * 4 bounded source/profile trials; no exact-C credit is claimed.
 * Live helper inputs and consumed return banks were checked against retail and
 * current definitions. Original scalar-return intent remains unqualified for
 * procedural ASM callees whose results this body does not consume.
 * Reopen with independent layout/lifetime, table-extent or scheduling evidence;
 * no source barriers, register pins, invented aliases or padding were used.
 */

extern unsigned char g_hero_state[];
extern unsigned char g_hero_position[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern void hero_l00_update_frame(void);
extern void AdvanceHeroAnimation(void);
extern void UpdateHeroInputAndHistory(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab(void *, void *, void *);
extern void FindGrindRail(void);
extern void hero_find_ledge_candidate(void);
extern void hero_l00_decide_state(void);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_objects_flag_bit(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds(void);
extern void UpdateHeroEasingTargetsAndPointEffects(void);
extern void cam_update_blend_angles(void);
extern void UpdateHeroPitchAndYawEasingTargets(void);
extern void UpdateHeroAutoAimAngles(void);
extern void UpdateHeroIdleRandomRotationTargets(void);
extern void ClampHeroControlAndUpdateEffects(void);
extern void UpdateHeroGlowAndExtraManipulators(void);
extern void UpdateHeroTiltPoseTargets(void);
extern void attachment_update_all(void);
extern void update_hero_moby(void);
extern void part_spawn_effect_from_record(int);
extern void hero_update_items_and_flags(void);
extern void hero_update_lock_on_weapon_fire(void);
extern void hero_play_voice_line_for_progress(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void hero_update_stat_trackers(void);
extern void hero_update_collection_progress(void);
extern void hero_check_targeting_triggers(void);
extern void UpdateHeroAimAndTransitions(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *);
extern void func_002A677C(void *);
extern void UpdateHeroBlinkAndItemTint(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

/* Run the frame's ordered resident-player updates while its control mode is active. */
void hero_l00_update_frame_2(void) {
    unsigned char *player = g_hero_state;
    unsigned char *hero;
    *(short *)(player + 0x2162) = 0;
    *(short *)(player + 0x2160) = 0;
    if (player[0x22B4]) { hero_l00_update_frame(); return; }
    AdvanceHeroAnimation();
    UpdateHeroInputAndHistory();
    hero_process_action_command();
    hero_find_ledge_grab(player + 0x80, player + 0x90, player + 0x550);
    FindGrindRail();
    hero_find_ledge_candidate();
    hero_l00_decide_state();
    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        if (player[0x22B5]) hero_set_objects_flag_bit();
        else hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (player[0x22B4]) return;
    UpdateDelayedSounds();
    UpdateHeroEasingTargetsAndPointEffects();
    cam_update_blend_angles();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    attachment_update_all();
    update_hero_moby();
    part_spawn_effect_from_record(0);
    hero_update_items_and_flags();
    hero_update_lock_on_weapon_fire();
    hero_play_voice_line_for_progress();
    hero_update_items_frame();
    if (player[0x22B5] || hero_is_action_allowed()) hero_set_objects_flag_bit();
    else hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    hero_update_stat_trackers();
    hero_update_collection_progress();
    hero_check_targeting_triggers();
    UpdateHeroAimAndTransitions();
    hero = g_hero_state;
    if ((*(int *)(hero + 0x229C) != 0x16 && *(int *)(hero + 0x229C) != 0x1F && *(int *)(hero + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode())
        coll_clear_map_bits_around_pos(g_hero_position);
    { unsigned char *base = g_hero_state; func_002A677C(*(void **)(base + 0x2290)); }
    UpdateHeroBlinkAndItemTint();
    UpdateHeroMobyProbedHeightBounds();
}
