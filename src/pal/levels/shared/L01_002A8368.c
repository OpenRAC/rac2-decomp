#include "include_asm.h"
#include "names.h"

extern char g_hero_l01_state_block[];
extern void func_002C7CA8(void);
extern void func_002B4070(void);
extern void func_002ADDC8(void);
extern void func_002C37C8(void);
extern void func_002AEB80(void);
extern void func_002B9878(void);
extern void func_002A7740(void);
extern void func_002AB1C8(void);
extern void func_002A9520(void);
extern void func_002A9310(void);
extern void func_002FDB00(void *a0);
extern void func_002AB328(void);
extern void func_0030F444(int a0);
extern char g_hero_l01_state_block[];

/* Updates the hero subsystems for one frame, running the extra steps only while the hero state byte is set (PAL). */
void hero_update_subsystems_pal(void) {
    char *hero;

    func_002C7CA8();
    func_002B4070();
    func_002ADDC8();
    func_002C37C8();
    func_002AEB80();
    hero = g_hero_l01_state_block;
    if (*(unsigned char *)(hero + 0x22B4) != 0) {
        func_002B9878();
        func_002A7740();
        if (*(unsigned char *)(hero + 0x22B4) != 0) {
            func_002AB1C8();
            func_002A9520();
            func_002A9310();
            func_002FDB00(hero + 0x80);
            func_002AB328();
            func_0030F444(*(int *)(hero + 0x2290));
        }
    }
}

#include "common.h"
extern char g_hero_state[];
extern int g_hero_l01_control_mode MACRO_ADDR;
extern char g_hero_position[];
extern void hero_update_subsystems_pal(void);
extern void AdvanceHeroAnimation_pal(void);
extern void UpdateHeroInputAndHistory_pal(void);
extern void hero_read_input_command_flags(void);
extern int ProbeLedgeGrab_pal(char *a0, char *a1, char *a2);
extern void hero_l01_update_state_transitions_pal(void);
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
extern void weapon_update_equipped_effect(void);
extern void UpdateHeroMobyProbedHeightBounds(void);







