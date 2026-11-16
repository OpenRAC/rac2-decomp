#include "include_asm.h"

#include "common.h"
extern char g_hero_state[];
extern int g_hero_l03_mode MACRO_ADDR;
extern char g_hero_position[];
extern void ref_L03_002AD540_00(void);
extern void AdvanceHeroAnimation_pal(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
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
extern void part_spawn_effect_from_record(int a0);
extern void hero_update_items_and_flags_pal(void);
extern void hero_update_lock_on_weapon_fire_pal(void);
extern void hero_play_voice_line_for_progress_pal(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void hero_update_stat_trackers_pal(void);
extern void hero_update_collection_progress_pal(void);
extern void hero_check_targeting_triggers_pal(void);
extern void UpdateHeroAimAndTransitions_pal(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_002A677C(int a0);
extern void ref_L03_002AD540_06(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

/* Runs one frame of the level: updates the hero, camera, effects and every game system, then the sound and the HUD. (PAL: 50 Hz timings) */
void level_update_frame_pal(void) {
    char *hero;

    hero = g_hero_state;
    *(short *)(hero + 0x2162) = 0;
    *(short *)(hero + 0x2160) = 0;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        ref_L03_002AD540_00();
        return;
    }
    AdvanceHeroAnimation_pal();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(hero + 0x80, hero + 0x90, hero + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (g_hero_l03_mode == 2 || g_hero_l03_mode == 6) {
        if (*(unsigned char *)(hero + 0x22B5) != 0)
            hero_set_objects_flag_bit();
        else
            hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (*(unsigned char *)(hero + 0x22B4) != 0)
        return;
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
    hero_update_lock_on_weapon_fire_pal();
    hero_play_voice_line_for_progress_pal();
    hero_update_items_frame();
    if (*(unsigned char *)(hero + 0x22B5) != 0 || hero_is_action_allowed() != 0)
        hero_set_objects_flag_bit();
    else
        hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    hero_update_stat_trackers_pal();
    hero_update_collection_progress_pal();
    hero_check_targeting_triggers_pal();
    UpdateHeroAimAndTransitions_pal();
    {
        char *state = g_hero_state;
        if ((*(int *)(state + 0x229C) != 0x16 && *(int *)(state + 0x229C) != 0x1F
             && *(int *)(state + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *state = g_hero_state;
        func_002A677C(*(int *)(state + 0x2290));
    }
    ref_L03_002AD540_06();
    UpdateHeroMobyProbedHeightBounds();
}

