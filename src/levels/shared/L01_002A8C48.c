#include "names.h"
/* Per-frame level update: the resident block through a pointer, the tail through fresh
   pointers (retail re-derives them from the kept %hi), the mode word as a macro load. */

#include "common.h"

extern char g_hero_state[];
extern int g_hero_l01_control_mode MACRO_ADDR;
extern char g_hero_position[];

extern void hero_update_subsystems(void);
extern void func_2C7CA8(void);
extern void UpdateHeroInputAndHistory(void);
extern void hero_read_input_command_flags(void);
extern int ProbeLedgeGrab(char *a0, char *a1, char *a2);
extern void hero_l01_update_state_transitions(void);
extern void func_2C8628(void);
extern void hero_clear_objects_flag_bit(void);
extern void func_2AEB80(void);
extern void func_2B9878(void);
extern void UpdateHeroEasingTargetsAndPointEffects(void);
extern void cam_update_blend_angles(void);
extern void UpdateHeroPitchAndYawEasingTargets(void);
extern void UpdateHeroAutoAimAngles(void);
extern void UpdateHeroIdleRandomRotationTargets(void);
extern void ClampHeroControlAndUpdateEffects(void);
extern void UpdateHeroGlowAndExtraManipulators(void);
extern void UpdateHeroTiltPoseTargets(void);
extern void func_2A7740(void);
extern void func_2AB028(void);
extern void part_spawn_effect_from_record(int a0);
extern void hero_update_items_and_flags(void);
extern void hero_update_lock_on_weapon_fire(void);
extern void hero_play_voice_line_for_progress(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void hero_update_stat_trackers(void);
extern void hero_update_collection_progress(void);
extern void hero_check_targeting_triggers(void);
extern void UpdateHeroAimAndTransitions(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_30F444(int a0);
extern void weapon_update_equipped_effect(void);
extern void func_2AB328(void);

/* Runs one frame of the main game update: reads input, moves the hero and camera, and updates effects and menus. A shorter path is used when the game is in a special mode. */
void game_update_frame(void) {
    char *hero;

    hero = g_hero_state;
    *(short *)(hero + 0x2162) = 0;
    *(short *)(hero + 0x2160) = 0;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        hero_update_subsystems();
        return;
    }
    func_2C7CA8();
    UpdateHeroInputAndHistory();
    hero_read_input_command_flags();
    ProbeLedgeGrab(hero + 0x80, hero + 0x90, hero + 0x550);
    hero_l01_update_state_transitions();
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
    UpdateHeroEasingTargetsAndPointEffects();
    cam_update_blend_angles();
    UpdateHeroPitchAndYawEasingTargets();
    UpdateHeroAutoAimAngles();
    UpdateHeroIdleRandomRotationTargets();
    ClampHeroControlAndUpdateEffects();
    UpdateHeroGlowAndExtraManipulators();
    UpdateHeroTiltPoseTargets();
    func_2A7740();
    func_2AB028();
    part_spawn_effect_from_record(0);
    hero_update_items_and_flags();
    hero_update_lock_on_weapon_fire();
    hero_play_voice_line_for_progress();
    hero_update_items_frame();
    if (*(unsigned char *)(hero + 0x22B5) != 0 || hero_is_action_allowed() != 0)
        func_2C8628();
    else
        hero_clear_objects_flag_bit();
    func_2A9520();
    func_2A9310();
    hero_update_stat_trackers();
    hero_update_collection_progress();
    hero_check_targeting_triggers();
    UpdateHeroAimAndTransitions();
    {
        char *hero_block = g_hero_state;
        if ((*(int *)(hero_block + 0x229C) != 0x16 && *(int *)(hero_block + 0x229C) != 0x1F
             && *(int *)(hero_block + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *hero_block = g_hero_state;
        func_30F444(*(int *)(hero_block + 0x2290));
    }
    weapon_update_equipped_effect();
    func_2AB328();
}
