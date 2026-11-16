#include "include_asm.h"

#include "common.h"
extern unsigned char g_hero_state[];
extern unsigned char g_hero_position[];
extern int g_game_l00_mode MACRO_ADDR;
extern void hero_l00_update_frame_pal(void);
extern void func_PAL_L00_002D29E8(void);
extern void UpdateHeroInputAndHistory_pal(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab_pal(void *, void *, void *);
extern void FindGrindRail(void);
extern void hero_find_ledge_candidate(void);
extern void func_PAL_L00_002CB7A0(void);
extern void hero_set_objects_flag_bit(void);
extern void hero_clear_objects_flag_bit(void);
extern void RebuildRegionObjectMembership(void);
extern void UpdateDelayedSounds_pal(void);
extern void UpdateHeroEasingTargetsAndPointEffects_pal(void);
extern void cam_update_blend_angles_pal(void);
extern void UpdateHeroPitchAndYawEasingTargets_pal(void);
extern void UpdateHeroAutoAimAngles_pal(void);
extern void UpdateHeroIdleRandomRotationTargets_pal(void);
extern void ClampHeroControlAndUpdateEffects_pal(void);
extern void UpdateHeroGlowAndExtraManipulators_pal(void);
extern void UpdateHeroTiltPoseTargets_pal(void);
extern void attachment_update_all(void);
extern void update_hero_moby(void);
extern void part_spawn_effect_from_record(int);
extern void hero_update_items_and_flags_pal(void);
extern void func_PAL_L00_002B2230(void);
extern void func_PAL_L00_002B20F8(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void func_PAL_L00_002A6688(void);
extern void hero_update_collection_progress_pal(void);
extern void hero_check_targeting_triggers_pal(void);
extern void func_PAL_L00_002D5680(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *);
extern void func_002A677C(void *);
extern void UpdateHeroBlinkAndItemTint_pal(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

/* Run the frame's ordered resident-player updates while its control mode is active. */
void hero_l00_update_frame_2_pal(void) {
    unsigned char *player = g_hero_state;
    unsigned char *hero;
    *(short *)(player + 0x2162) = 0;
    *(short *)(player + 0x2160) = 0;
    if (player[0x22B4]) { hero_l00_update_frame_pal(); return; }
    func_PAL_L00_002D29E8();
    UpdateHeroInputAndHistory_pal();
    hero_process_action_command();
    hero_find_ledge_grab_pal(player + 0x80, player + 0x90, player + 0x550);
    FindGrindRail();
    hero_find_ledge_candidate();
    func_PAL_L00_002CB7A0();
    if (g_game_l00_mode == 2 || g_game_l00_mode == 6) {
        if (player[0x22B5]) hero_set_objects_flag_bit();
        else hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (player[0x22B4]) return;
    UpdateDelayedSounds_pal();
    UpdateHeroEasingTargetsAndPointEffects_pal();
    cam_update_blend_angles_pal();
    UpdateHeroPitchAndYawEasingTargets_pal();
    UpdateHeroAutoAimAngles_pal();
    UpdateHeroIdleRandomRotationTargets_pal();
    ClampHeroControlAndUpdateEffects_pal();
    UpdateHeroGlowAndExtraManipulators_pal();
    UpdateHeroTiltPoseTargets_pal();
    attachment_update_all();
    update_hero_moby();
    part_spawn_effect_from_record(0);
    hero_update_items_and_flags_pal();
    func_PAL_L00_002B2230();
    func_PAL_L00_002B20F8();
    hero_update_items_frame();
    if (player[0x22B5] || hero_is_action_allowed()) hero_set_objects_flag_bit();
    else hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    func_PAL_L00_002A6688();
    hero_update_collection_progress_pal();
    hero_check_targeting_triggers_pal();
    func_PAL_L00_002D5680();
    hero = g_hero_state;
    if ((*(int *)(hero + 0x229C) != 0x16 && *(int *)(hero + 0x229C) != 0x1F && *(int *)(hero + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode())
        coll_clear_map_bits_around_pos(g_hero_position);
    { unsigned char *base = g_hero_state; func_002A677C(*(void **)(base + 0x2290)); }
    UpdateHeroBlinkAndItemTint_pal();
    UpdateHeroMobyProbedHeightBounds();
}

