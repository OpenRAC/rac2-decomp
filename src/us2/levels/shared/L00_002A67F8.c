#include "names.h"
/* func_US2_L00_002A6DD0, the USA v2.00 copy of func_L00_002A6DD0: the same update, with the pad's
   held and pressed words masked while the player's 0x1E0 timer runs and restored on every exit. */

#include "common.h"

extern char g_pad_state[];
extern char g_hero_state[];
extern int D_L00_001A8F00 MACRO_ADDR;
extern char g_hero_position[];

extern void hero_l00_update_frame(void);
extern void AdvanceHeroAnimation(void);
extern void UpdateHeroInputAndHistory(void);
extern void hero_process_action_command(void);
extern int hero_find_ledge_grab(void *a0, void *a1, void *a2);
extern void FindGrindRail(void);
extern void hero_find_ledge_candidate(void);
extern void func_US2_L00_002CB650(void);
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
extern void func_US2_L00_002B2408(void);
extern void func_US2_L00_002B22D0(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void gfx_fade_screen_effect(void);
extern void ApplyHeroAxisScales(void);
extern void func_US2_L00_002A67F8(void);
extern void func_US2_L00_002D6258(void);
extern void hero_check_targeting_triggers(void);
extern void UpdateHeroAimAndTransitions(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_002A677C(void *a0);
extern void UpdateHeroBlinkAndItemTint(void);
extern void UpdateHeroMobyProbedHeightBounds(void);

void func_US2_L00_002A6DD0(void) {
    char *pad;
    char *player;
    char *p;
    int held;
    int pressed;
    int timer;
    int masked;
    int masked_pressed;

    pad = g_pad_state;
    player = g_hero_state;
    held = *(int *)(pad + 0x1A0);
    pressed = *(int *)(pad + 0x1A4);
    timer = *(short *)(player + 0x1E0);
    /* Tested through the value being built, so jump1 keeps both arms and cse1 stops at their join. */
    masked = timer;
    if (masked != 0)
        masked = 0;
    else
        masked = *(int *)(pad + 0x1A0);
    *(int *)(pad + 0x1A0) = masked;
    masked_pressed = 0;
    if (timer == 0)
        masked_pressed = *(int *)(pad + 0x1A4);
    *(int *)(pad + 0x1A4) = masked_pressed;
    p = g_hero_state;
    *(short *)(p + 0x2162) = 0;
    *(short *)(p + 0x2160) = 0;
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        hero_l00_update_frame();
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    AdvanceHeroAnimation();
    UpdateHeroInputAndHistory();
    hero_process_action_command();
    hero_find_ledge_grab(p + 0x80, p + 0x90, p + 0x550);
    FindGrindRail();
    hero_find_ledge_candidate();
    func_US2_L00_002CB650();
    if (D_L00_001A8F00 == 2 || D_L00_001A8F00 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            hero_set_objects_flag_bit();
        else
            hero_clear_objects_flag_bit();
        {
            char *q = g_pad_state;
            *(int *)(q + 0x1A0) = held;
            *(int *)(q + 0x1A4) = pressed;
        }
        return;
    }
    RebuildRegionObjectMembership();
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
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
    func_US2_L00_002B2408();
    func_US2_L00_002B22D0();
    hero_update_items_frame();
    {
        char *q = g_hero_state;
        if (*(unsigned char *)(q + 0x22B5) != 0 || hero_is_action_allowed() != 0)
            hero_set_objects_flag_bit();
        else
            hero_clear_objects_flag_bit();
    }
    gfx_fade_screen_effect();
    ApplyHeroAxisScales();
    func_US2_L00_002A67F8();
    func_US2_L00_002D6258();
    hero_check_targeting_triggers();
    UpdateHeroAimAndTransitions();
    {
        char *q = g_hero_state;
        if ((*(int *)(q + 0x229C) != 0x16 && *(int *)(q + 0x229C) != 0x1F
             && *(int *)(q + 0x2294) != 0x31) || hero_is_in_swing_or_grind_mode() != 0)
            coll_clear_map_bits_around_pos(g_hero_position);
    }
    {
        char *q = g_hero_state;
        func_002A677C(*(void **)(q + 0x2290));
    }
    UpdateHeroBlinkAndItemTint();
    UpdateHeroMobyProbedHeightBounds();
    {
        char *q = g_pad_state;
        *(int *)(q + 0x1A0) = held;
        *(int *)(q + 0x1A4) = pressed;
    }
}
