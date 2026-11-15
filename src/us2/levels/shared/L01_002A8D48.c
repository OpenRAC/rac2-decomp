#include "names.h"
/* func_US2_L01_002A8D48, the USA v2.00 copy of func_L01_002A8C48: the same update, with the pad's
   held and pressed words masked while the player's 0x1E0 timer runs and restored on every exit. */

#include "common.h"

extern char g_pad_state[];
extern char g_hero_state[];
extern int D_L01_001A8F40 MACRO_ADDR;
extern char g_hero_position[];

extern void hero_update_subsystems(void);
extern void func_2C7CA8(void);
extern void UpdateHeroInputAndHistory(void);
extern void hero_read_input_command_flags(void);
extern int ProbeLedgeGrab(char *a0, char *a1, char *a2);
extern void func_US2_L01_002C3B08(void);
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
extern void func_US2_L00_002B2408(void);
extern void func_US2_L00_002B22D0(void);
extern void hero_update_items_frame(void);
extern int hero_is_action_allowed(void);
extern void func_2A9520(void);
extern void func_2A9310(void);
extern void func_US2_L00_002A67F8(void);
extern void func_US2_L00_002D6258(void);
extern void hero_check_targeting_triggers(void);
extern void UpdateHeroAimAndTransitions(void);
extern int hero_is_in_swing_or_grind_mode(void);
extern void coll_clear_map_bits_around_pos(void *a0);
extern void func_30F444(int a0);
extern void weapon_update_equipped_effect(void);
extern void func_2AB328(void);

void func_US2_L01_002A8D48(void) {
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
        hero_update_subsystems();
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
    func_2C7CA8();
    UpdateHeroInputAndHistory();
    hero_read_input_command_flags();
    ProbeLedgeGrab(p + 0x80, p + 0x90, p + 0x550);
    func_US2_L01_002C3B08();
    if (D_L01_001A8F40 == 2 || D_L01_001A8F40 == 6) {
        if (*(unsigned char *)(p + 0x22B5) != 0)
            func_2C8628();
        else
            hero_clear_objects_flag_bit();
        {
            char *q = g_pad_state;
            *(int *)(q + 0x1A0) = held;
            *(int *)(q + 0x1A4) = pressed;
        }
        return;
    }
    func_2AEB80();
    if (*(unsigned char *)(p + 0x22B4) != 0) {
        *(int *)(pad + 0x1A0) = held;
        *(int *)(pad + 0x1A4) = pressed;
        return;
    }
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
    func_US2_L00_002B2408();
    func_US2_L00_002B22D0();
    hero_update_items_frame();
    {
        char *q = g_hero_state;
        if (*(unsigned char *)(q + 0x22B5) != 0 || hero_is_action_allowed() != 0)
            func_2C8628();
        else
            hero_clear_objects_flag_bit();
    }
    func_2A9520();
    func_2A9310();
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
        func_30F444(*(int *)(q + 0x2290));
    }
    weapon_update_equipped_effect();
    func_2AB328();
    {
        char *q = g_pad_state;
        *(int *)(q + 0x1A0) = held;
        *(int *)(q + 0x1A4) = pressed;
    }
}
