#include "include_asm.h"

#include "common.h"
extern u8 D_001395B8[];
extern u8 *D_L16_001B2B1C[] __attribute__((sda));
extern u8 *D_L16_001B16C0 __attribute__((sda));
extern int D_L16_001B16C4 __attribute__((sda));
extern u8 g_sound_state[];
extern void SetMobyAndGroupsEnabled(u8 *, int);
extern void moby_mark_spawned(void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern u8 *CreateMoby(int);
extern void moby_init_child_from_parent(u8 *, u8 *);
extern void mem_clear(void *, int, int);
extern void snivelak_copy_position_pair_after_setup(u8 *);
extern void moby_set_state(u8 *, u8, int);
extern void anim_play_on_self_or_child(u8 *, int, int, float);
extern void snivelak_clean_up_arena_mobys(u8 *);
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern float math_interpolate_between_limits(int, int, float, float);
extern void func_PAL_002AC290(int, char *);
extern float func_PAL_002AA108(u8 *, void *);
extern float ApproachValue(float *, float, float);
extern void snd_stop_voice(int);
extern void func_PAL_L16_00417C58(u8 *);
extern void weapon_select_aim_target(u8 *, int, void *, void *, float, float);

/* Initializes the boss hierarchy and applies damage, phase changes and speech. */
void func_PAL_L16_00415760(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *child, *attacker, *damage;
    u8 **arms;
    u8 *speech;
    int i, threshold, sound;
    float quantum, amount, divisor;
    if (!moby[0x20]) {
        if (D_001395B8[0x83] == 2) {
            SetMobyAndGroupsEnabled(moby, 0);
            moby_mark_spawned(D_L16_001B2B1C[0] + *(int *)(state + 0x174) * 256);
            moby_mark_spawned(moby);
            return;
        }
        if (!*(short *)(state + 0x24)) {
            *(short *)(state + 0x24) = 600;
            *(float *)(state + 0x20) = 600.0f;
        }
        speech = state + 0x310;
        state[0x2e] = 1;
        divisor = IntToFloat(D_L16_001B16C4);
        quantum = (float)*(short *)(state + 0x24);
        quantum /= divisor;
        threshold = FloatToInt((*(float *)(state + 0x20) - 1.0f) / quantum);
        *(float *)(state + 0x248) = (float)threshold * quantum;
        arms = (u8 **)(state + 0x238);
        for (i = 1; i >= 0; i--, arms++) {
            child = CreateMoby(0x7e8);
            if (child) {
                moby_init_child_from_parent(child, moby);
                *(unsigned short *)(child + 0x34) |= 0x4100;
                *arms = child;
            }
        }
        {
            int bodyIndex = *(int *)(state + 0x174);
            u8 *pool = D_L16_001B2B1C[0];
            float initialHeight = *(float *)(moby + 0x18);
            D_L16_001B16C0 = 0;
            *(float *)(state + 0x264) = initialHeight;
            *(u8 **)(state + 0x1f0) = pool + bodyIndex * 256;
        }
        *(unsigned short *)(moby + 0x34) |= 0x4000;
        *(unsigned short *)(*(u8 **)(state + 0x1f0) + 0x34) |= 0x4000;
        *(unsigned short *)(moby + 0x32) = 500;
        *(unsigned short *)(*(u8 **)(state + 0x1f0) + 0x32) = 500;
        *(unsigned short *)(moby + 0x34) |= 0x400;
        mem_clear(speech, 0, 48);
        *(int *)(state + 0x350) = 0;
        *(int *)(state + 0x354) = -1;
        snivelak_copy_position_pair_after_setup(moby);
        moby_set_state(moby, 1, 0);
        anim_play_on_self_or_child(moby, 0, 0, 0.0f);
        if (D_001395B8[0x83] == 1) {
            snivelak_clean_up_arena_mobys(moby);
            SetMobyAndGroupsEnabled(moby, 1);
        } else SetMobyAndGroupsEnabled(moby, 0);
    }
    if (!moby[0x95] || moby[0x95] == 5) return;
    damage = part_find_owned_effect_slot(moby, 0x10000, 0);
    if (!damage) damage = part_find_owned_effect_slot(*(u8 **)(state + 0x1f0), 0x10000, 0);
    if (!damage) damage = part_find_owned_effect_slot(*(u8 **)(state + 0x238), 0x10000, 0);
    if (!damage) damage = part_find_owned_effect_slot(*(u8 **)(state + 0x23c), 0x10000, 0);
    if (damage) {
        *(float *)(damage + 0x2c) *= math_interpolate_between_limits(0, 20, 0.5f, 1.5f);
        if (moby[0x95] == 3) *(float *)(damage + 0x2c) *= 0.333f;
        attacker = *(u8 **)(damage + 0x20);
        if (attacker && *(short *)(attacker + 0xaa) != 0xea7) {
            *(float *)(damage + 0x2c) *= 0.2f;
            if (*(short *)(attacker + 0xaa) == 0x5c9) *(float *)(damage + 0x2c) *= 0.05f;
        }
        else func_PAL_002AC290((int)moby, (char *)(state + 0x50));
        amount = func_PAL_002AA108(moby, damage);
        ApproachValue((float *)(state + 0x20), 0.0f, amount);
        if (D_L16_001B16C0 && moby[0x95] != 3 && *(float *)(state + 0x20) < *(float *)(state + 0x248)) {
            divisor = IntToFloat(D_L16_001B16C4);
            quantum = (float)*(short *)(state + 0x24);
            quantum /= divisor;
            threshold = FloatToInt((*(float *)(state + 0x20) - 1.0f) / quantum);
            (*(int *)(state + 0x260))++;
            *(float *)(state + 0x248) = (float)threshold * quantum;
            moby_set_state(moby, 9, 3);
            sound = *(int *)(state + 0x368);
            if (sound != -1) {
                u8 *soundRecord = g_sound_state + sound * 112;
                if (*(u8 **)(soundRecord + 0x88) == *(u8 **)(state + 0x1f0) && soundRecord[0x74]) snd_stop_voice(sound);
            }
            {
                u8 *target = D_L16_001B16C0;
                *(int *)(state + 0x368) = -1;
                *(u8 **)(state + 0x24c) = target;
            }
        } else if (*(float *)(state + 0x20) == 0.0f || state[0x2e] == 2) {
            sound = *(int *)(state + 0x368);
            if (sound != -1) {
                u8 *soundRecord = g_sound_state + sound * 112;
                if (*(u8 **)(soundRecord + 0x88) == *(u8 **)(state + 0x1f0) && soundRecord[0x74]) snd_stop_voice(sound);
            }
            *(int *)(state + 0x368) = -1;
            moby_set_state(moby, 17, 5);
        }
    }
    func_PAL_L16_00417C58(moby);
    moby[0xa8] = 255;
    (*(u8 **)(state + 0x1f0))[0xa8] = 255;
    (*(u8 **)(state + 0x238))[0xa8] = 255;
    (*(u8 **)(state + 0x23c))[0xa8] = 255;
    weapon_select_aim_target(moby, -1, 0, 0, 128.0f, 0.0f);
}
