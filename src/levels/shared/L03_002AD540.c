#include "include_asm.h"
#include "names.h"
/* Per-frame level update (the L01 body's layout): the resident block through a pointer, the
   tail through fresh pointers, the mode word as a macro load; program-specific calls by ref_. */

#include "common.h"

extern char g_hero_state[];
extern int D_L03_001A8F00 MACRO_ADDR;
extern char g_hero_position[];

extern void ref_L03_002AD540_00(void);
extern void AdvanceHeroAnimation(void);
extern void ref_L03_002AD540_01(void);
extern void ref_L03_002AD540_02(void);
extern void ref_L03_002AD540_03(char *a0, char *a1, char *a2);
extern void ref_L03_002AD540_04(void);
extern void ref_L03_002AD540_05(void);
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
extern void part_spawn_effect_from_record(int a0);
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
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_002A677C(int a0);
extern void ref_L03_002AD540_06(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

/* Runs one frame of the level: updates the hero, camera, effects and every game system, then the sound and the HUD. */
void level_update_frame(void) {
    char *resident;

    resident = g_hero_state;
    *(short *)(resident + 0x2162) = 0;
    *(short *)(resident + 0x2160) = 0;
    if (*(unsigned char *)(resident + 0x22B4) != 0) {
        ref_L03_002AD540_00();
        return;
    }
    AdvanceHeroAnimation();
    ref_L03_002AD540_01();
    ref_L03_002AD540_02();
    ref_L03_002AD540_03(resident + 0x80, resident + 0x90, resident + 0x550);
    ref_L03_002AD540_04();
    ref_L03_002AD540_05();
    if (D_L03_001A8F00 == 2 || D_L03_001A8F00 == 6) {
        if (*(unsigned char *)(resident + 0x22B5) != 0)
            hero_set_objects_flag_bit();
        else
            hero_clear_objects_flag_bit();
        return;
    }
    RebuildRegionObjectMembership();
    if (*(unsigned char *)(resident + 0x22B4) != 0)
        return;
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
    if (*(unsigned char *)(resident + 0x22B5) != 0 || hero_is_action_allowed() != 0)
        hero_set_objects_flag_bit();
    else
        hero_clear_objects_flag_bit();
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    hero_update_stat_trackers();
    hero_update_collection_progress();
    hero_check_targeting_triggers();
    UpdateHeroAimAndTransitions();
    {
        char *resident_copy = g_hero_state;
        if ((*(int *)(resident_copy + 0x229C) != 0x16 && *(int *)(resident_copy + 0x229C) != 0x1F
             && *(int *)(resident_copy + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *resident_copy = g_hero_state;
        func_002A677C(*(int *)(resident_copy + 0x2290));
    }
    ref_L03_002AD540_06();
    UpdateHeroMobyProbedHeightBounds();
}
