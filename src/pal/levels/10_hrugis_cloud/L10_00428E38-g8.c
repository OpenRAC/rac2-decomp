#include "include_asm.h"

#include "common.h"
typedef struct { u8 pad[0x270]; s32 effect; } RewardOwnerState;
extern u8 *g_moby_pool_base;
extern u8 g_effect_l10_record_table[];
extern s32 g_mission_reward_state;
extern s32 g_hud_sprite_table_base __attribute__((sda));
extern s32 g_reward_active_flag __attribute__((sda));
extern s32 g_mission_completion_counts[] __attribute__((sda));
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
extern s32 D_L10_001B1448_gp[][3] SDATA(D_L10_001B1448);
extern s32 g_reward_kind;
extern s32 g_hud_state_flag __attribute__((sda));
extern s32 g_hud_setup_done __attribute__((sda));
extern s32 g_player_bolts;
extern u8 g_extras_unlocked_flag;
extern u32 g_pad_held_flags;
extern s32 g_selected_mission_index __attribute__((sda));
extern void snd_stop_voice(s32);
extern s32 math_fast_float_d(void *);
extern void FadeToBlack(s32);
extern void level_store_value_pair_pal(s32, void *);
extern s32 menu_draw_reward_panel_pal(void);
extern void mission_store_completion_counts(void);
extern int MemcardSave(s32, s32);
extern void hero_set_state_value_c(s32);
extern void hrugis_reset_mission_state(u8 *);
extern int request_begin_slot(s32, s32, s32, s32, s32);

/* Stops the owner's effect. Unless state D_L10_001A8F00 is 2, once func_00282948(s + 0x58)
   reports done, the first pass with D_L10_001A904C set adds the kind's reward (times 10
   when D_001A7A0A is set) to D_001A79F8 and counts the run. Then, once
   func_00282948(s + 0x40) reports done, pad bit 0x40 (D_00138324) grades the runs 1..3
   into D_L10_001B143C and calls func_L10_00423500, and bit 0x10 calls
   func_002B49E0(3, 1, 4, 0, 0). One variable, tmp, holds the state and later the 0x40
   test: retail allocates it that way (the test in $v1, the pad word kept in $v0). */
void hrugis_finish_mission_reward_pal(u8 *obj, s32 kind) {
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *other = g_moby_pool_base + *(s32 *)(s + 0x24) * 256;
    RewardOwnerState *os = *(RewardOwnerState **)(other + 0x68);
    s32 id = os->effect;
    s32 n, reward, tmp, capped;
    u8 multiplier;

    if (id != -1) {
        u8 *p = g_effect_l10_record_table + id * 0x70;
        if (*(u8 **)(p + 0x88) == other && p[0x74])
            snd_stop_voice(id);
    }
    os->effect = -1;
    tmp = g_mission_reward_state;
    if (tmp == 2)
        return;
    if (!math_fast_float_d(s + 0x58))
        return;
    if (g_hud_sprite_table_base && !g_reward_active_flag) {
        FadeToBlack(25);
        level_store_value_pair_pal(0, menu_draw_reward_panel_pal);
        n = D_L10_001B1390_gp[kind];
        capped = n < 3 ? n : 2;
        multiplier = g_extras_unlocked_flag;
        g_reward_active_flag = 1;
        g_reward_kind = kind;
        g_hud_state_flag = 0;
        g_hud_setup_done = 0;
        reward = D_L10_001B1448_gp[kind][capped];
        if (multiplier)
            reward *= 10;
        D_L10_001B1390_gp[kind] = n + 1;
        g_player_bolts = g_player_bolts + reward;
        mission_store_completion_counts();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (!math_fast_float_d(s + 0x40)) {
        tmp = g_pad_held_flags & 0x40;
        if (tmp) {
            g_reward_active_flag = 0;
            *(s32 *)(s + 0x40) = 0x20F58;
            FadeToBlack(25);
            hero_set_state_value_c(0);
            *(s32 *)(s + 0x58) = 100;
            *(s32 *)(s + 0x48) = 0x2328;
            if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1] && g_mission_completion_counts[2])
                g_selected_mission_index = 3;
            else if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1])
                g_selected_mission_index = 2;
            else if (D_L10_001B1390_gp[0])
                g_selected_mission_index = 1;
            hrugis_reset_mission_state(obj);
        } else if (g_pad_held_flags & 0x10)
            request_begin_slot(3, 1, 4, 0, 0);
    } else
        *(s32 *)(s + 0x40) = 0x20F58;
}
