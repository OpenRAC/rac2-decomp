#include "names.h"
/* func_PAL_L01_002A8B30, the PAL copy of func_L01_002A8C48: the same C, where func_L01_002A84D8
   becomes func_PAL_L01_002A8368; func_L00_002B36E0 becomes func_PAL_L00_002B3608;
   func_L01_002AE128 becomes func_PAL_L01_002AE010; func_L01_002C37C8 becomes
   func_PAL_L01_002C3A10; func_L00_002AC1A0 becomes func_PAL_L00_002AC088; func_L00_002AB1D8
   becomes func_PAL_L00_002AB0C0; func_L00_002AB420 becomes func_PAL_L00_002AB308;
   func_L00_002ABBA0 becomes func_PAL_L00_002ABA88; func_L00_002AB948 becomes
   func_PAL_L00_002AB830; func_L00_002A5518 becomes func_PAL_L00_002A53A8; func_L00_002A5840
   becomes func_PAL_L00_002A56D0; func_L00_002B7718 becomes func_PAL_L00_002B7688;
   func_L00_002B2120 becomes func_PAL_L00_002B2018; func_L00_002B2318 becomes
   func_PAL_L00_002B2230; func_L00_002B2200 becomes func_PAL_L00_002B20F8; func_L00_002A67F8
   becomes func_PAL_L00_002A6688; func_L00_002D5EB8 becomes func_PAL_L00_002D6408;
   func_L00_002A6420 becomes func_PAL_L00_002A62B0; func_L00_002D5158 becomes
   func_PAL_L00_002D5680. */

#include "common.h"

extern char g_hero_state[];
extern int g_hero_l01_control_mode MACRO_ADDR;
extern char g_hero_position[];

extern void hero_update_subsystems_pal(void);
extern void func_2C7CA8(void);
extern void UpdateHeroInputAndHistory_pal(void);
extern void hero_read_input_command_flags(void);
extern int ProbeLedgeGrab_pal(char *a0, char *a1, char *a2);
extern void hero_l01_update_state_transitions_pal(void);
extern void func_2C8628(void);
extern void hero_clear_objects_flag_bit(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void UpdateHeroEasingTargetsAndPointEffects_pal(void);
extern void cam_update_blend_angles_pal(void);
extern void UpdateHeroPitchAndYawEasingTargets_pal(void);
extern void UpdateHeroAutoAimAngles_pal(void);
extern void UpdateHeroIdleRandomRotationTargets_pal(void);
extern void ClampHeroControlAndUpdateEffects_pal(void);
extern void UpdateHeroGlowAndExtraManipulators_pal(void);
extern void UpdateHeroTiltPoseTargets_pal(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void part_spawn_effect_from_record(int a0);
extern void hero_update_items_and_flags_pal(void);
extern void hero_update_lock_on_weapon_fire_pal(void);
extern void hero_play_voice_line_for_progress_pal(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void hero_update_stat_trackers_pal(void);
extern void hero_update_collection_progress_pal(void);
extern void hero_check_targeting_triggers_pal(void);
extern void UpdateHeroAimAndTransitions_pal(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_30F444(int a0);
extern void weapon_update_equipped_effect(void);
extern void func_2AB328(void);

/* Runs one frame of hero and game updates: input, ledge probe, easing targets, items, collision and weapon effects (PAL). */
void game_update_frame_pal(void) {
    char *hero;

    hero = g_hero_state;
    *(short *)(hero + 0x2162) = 0;
    *(short *)(hero + 0x2160) = 0;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        hero_update_subsystems_pal();
        return;
    }
    func_2C7CA8();
    UpdateHeroInputAndHistory_pal();
    hero_read_input_command_flags();
    ProbeLedgeGrab_pal(hero + 0x80, hero + 0x90, hero + 0x550);
    hero_l01_update_state_transitions_pal();
    if (g_hero_l01_control_mode == 2 || g_hero_l01_control_mode == 6) {
        if (*(unsigned char *)(hero + 0x22B5) != 0)
            func_2C8628();
        else
            hero_clear_objects_flag_bit();
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(hero + 0x22B4) != 0)
        return;
    func_2B9878();
    UpdateHeroEasingTargetsAndPointEffects_pal();
    cam_update_blend_angles_pal();
    UpdateHeroPitchAndYawEasingTargets_pal();
    UpdateHeroAutoAimAngles_pal();
    UpdateHeroIdleRandomRotationTargets_pal();
    ClampHeroControlAndUpdateEffects_pal();
    UpdateHeroGlowAndExtraManipulators_pal();
    UpdateHeroTiltPoseTargets_pal();
    func_2A7740();
    func_2AB028();
    part_spawn_effect_from_record(0);
    hero_update_items_and_flags_pal();
    hero_update_lock_on_weapon_fire_pal();
    hero_play_voice_line_for_progress_pal();
    hero_update_items_frame();
    if (*(unsigned char *)(hero + 0x22B5) != 0 || hero_is_action_allowed() != 0)
        func_2C8628();
    else
        hero_clear_objects_flag_bit();
    func_2A9520();
    func_2A9310();
    hero_update_stat_trackers_pal();
    hero_update_collection_progress_pal();
    hero_check_targeting_triggers_pal();
    UpdateHeroAimAndTransitions_pal();
    {
        char *hero_ref = g_hero_state;
        if ((*(int *)(hero_ref + 0x229C) != 0x16 && *(int *)(hero_ref + 0x229C) != 0x1F
             && *(int *)(hero_ref + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *hero_ref = g_hero_state;
        func_30F444(*(int *)(hero_ref + 0x2290));
    }
    weapon_update_equipped_effect();
    func_2AB328();
}
