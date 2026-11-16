#include "common.h"
extern void *part_find_owned_effect_slot(void *, u32, s32);
extern void moby_set_state(u8 *, s32, s32);
extern s32 moby_apply_damage_to_object(void *, void *, s32);
extern void group_update_members(u8 *);
extern void protopet_end_action(u8 *, s32);
extern void SetDeathBits(u8 *, s32, s32);
extern s32 moby_run_slot_handler(s32, s32, s32);
extern s32 weapon_select_aim_target(u8 *, s32, void *, s32, float, float);
extern void protopet_set_ready_flag(u8 *);
extern s32 g_game_mode;
/* Checks if the Protopet was hit or lost its target, and switches its state when needed. */
void protopet_check_hit_target(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *contact;
    u8 saved;
    u64 mode;
    contact = part_find_owned_effect_slot(object, 0x10000, 1);
    if (contact && *(u8 **)(contact + 0x20) && *(s16 *)(*(u8 **)(contact + 0x20) + 0xAA) == 0xF9E /* moby class 3998 */) {
        if (object[0x20] < 6 || object[0x20] == 19 || object[0x20] == 18) return;
        moby_set_state(object, 18, -1);
        return;
    }
    saved = object[0x94];
    if (moby_apply_damage_to_object(object, state + 0x50, 0)) {
        if (object[0x94] == 17 || object[0x94] == 8 || object[0x94] == 9 || object[0x94] == 16 || object[0x94] == 10 || object[0x94] == 7) object[0x94] = saved;
        if (object[0x94] != 14) group_update_members(object);
    }
    object[0xA8] = 255;
    if (*(float *)(object + 0x18) < 90.0f || (*(float *)(state + 0x2A0) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x2A0))) protopet_end_action(object, 0);
    if (state[0x2E] == 2) {
        protopet_end_action(object, 1);
        return;
    }
    contact = *(u8 **)(state + 0x188);
    if (contact && *(s16 *)(contact + 0xAA) == 0xF59 /* moby class 3929 */) {
        SetDeathBits(object, 0, 1);
        goto stop;
    }
    mode = object[0x20];
    if (*(s32 *)(state + 0x180) > 300 && mode != 2) goto stop;
    if ((u8)mode >= 6 && *(s32 *)(state + 0x260) != -1 && !moby_run_slot_handler((s32)(object + 0x10), *(s32 *)(state + 0x260), 0)) {
stop:
        protopet_end_action(object, 0);
        return;
    }
    *(s32 *)(state + 0x248) = weapon_select_aim_target(object, *(s32 *)(state + 0x240), 0, 0, *(float *)(state + 0x244), 0.0f);
    if (*(u8 **)(state + 0x258)) protopet_set_ready_flag(*(u8 **)(state + 0x258));
    if (g_game_mode == 0x6F && (u32)(object[0x20] - 9) < 4) moby_set_state(object, 6, -1);
}
