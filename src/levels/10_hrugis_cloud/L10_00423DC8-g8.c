#include "common.h"

/* The owner record keeps its effect slot at +0x270. */
typedef struct { u8 pad[0x270]; s32 effect; } RewardOwnerState;

extern u8 *D_001B251C;
extern u8 D_L10_00188660[];
extern s32 D_L10_001A8F00;
extern s32 D_L10_001A904C __attribute__((sda));
extern s32 D_L10_001B1440 __attribute__((sda));
/* Completion counts per kind: retail reads count 0 and the kind-indexed count through
   $gp and counts 1 and 2 with absolute addresses, so the table has both views. */
extern s32 g_mission_completion_counts[] __attribute__((sda));
extern s32 D_L10_001B1390_gp[] SDATA(D_L10_001B1390);
/* Reward per kind and capped count. */
extern s32 D_L10_001B1448_gp[][3] SDATA(D_L10_001B1448);
extern s32 D_L10_001B355C;
extern s32 D_L10_001B13EC __attribute__((sda));
extern s32 D_L10_001B13E8 __attribute__((sda));
extern s32 g_player_bolts;
extern u8 D_001A7A0A;
extern u32 D_00138324;
extern s32 g_selected_mission_index __attribute__((sda));

extern void func_00373410(s32);
extern s32 math_fast_float_d(void *);
extern void FadeToBlack(s32);
extern void level_store_value_pair(s32, void *);
extern void menu_draw_reward_panel(void);
extern void mission_store_completion_counts(void);
extern void MemcardSave(s32, s32);
extern void hero_set_state_value_c(s32);
extern void hrugis_reset_mission_state(u8 *);
extern void request_begin_slot(s32, s32, s32, s32, s32);

/* Stops the owner's effect. Unless state D_L10_001A8F00 is 2, once func_00282948(s + 0x58)
   reports done, the first pass with D_L10_001A904C set adds the kind's reward (times 10
   when D_001A7A0A is set) to D_001A79F8 and counts the run. Then, once
   func_00282948(s + 0x40) reports done, pad bit 0x40 (D_00138324) grades the runs 1..3
   into D_L10_001B143C and calls func_L10_00423500, and bit 0x10 calls
   func_002B49E0(3, 1, 4, 0, 0). One variable, tmp, holds the state and later the 0x40
   test: retail allocates it that way (the test in $v1, the pad word kept in $v0). */
void hrugis_finish_mission_reward(u8 *obj, s32 kind) {
    u8 *s = *(u8 **)(obj + 0x68);
    u8 *owner_moby = D_001B251C + *(s32 *)(s + 0x24) * 256;
    RewardOwnerState *os = *(RewardOwnerState **)(owner_moby + 0x68);
    s32 id = os->effect;
    s32 completed_count, reward, tmp, capped;
    u8 multiplier;

    if (id != -1) {
        u8 *record = D_L10_00188660 + id * 0x70;
        if (*(u8 **)(record + 0x88) == owner_moby && record[0x74])
            func_00373410(id);
    }
    os->effect = -1;
    tmp = D_L10_001A8F00;
    if (tmp == 2)
        return;
    if (!math_fast_float_d(s + 0x58))
        return;
    if (D_L10_001A904C && !D_L10_001B1440) {
        FadeToBlack(30);
        level_store_value_pair(0, menu_draw_reward_panel);
        completed_count = D_L10_001B1390_gp[kind];
        capped = completed_count < 3 ? completed_count : 2;
        multiplier = D_001A7A0A;
        D_L10_001B1440 = 1;
        D_L10_001B355C = kind;
        D_L10_001B13EC = 0;
        D_L10_001B13E8 = 0;
        reward = D_L10_001B1448_gp[kind][capped];
        if (multiplier)
            reward *= 10;
        D_L10_001B1390_gp[kind] = completed_count + 1;
        g_player_bolts = g_player_bolts + reward;
        mission_store_completion_counts();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (!math_fast_float_d(s + 0x40)) {
        tmp = D_00138324 & 0x40;
        if (tmp) {
            D_L10_001B1440 = 0;
            *(s32 *)(s + 0x40) = 0x278D0;
            FadeToBlack(30);
            hero_set_state_value_c(0);
            *(s32 *)(s + 0x58) = 120;
            *(s32 *)(s + 0x48) = 0x2A30;
            if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1] && g_mission_completion_counts[2])
                g_selected_mission_index = 3;
            else if (D_L10_001B1390_gp[0] && g_mission_completion_counts[1])
                g_selected_mission_index = 2;
            else if (D_L10_001B1390_gp[0])
                g_selected_mission_index = 1;
            hrugis_reset_mission_state(obj);
        } else if (D_00138324 & 0x10)
            request_begin_slot(3, 1, 4, 0, 0);
    } else
        *(s32 *)(s + 0x40) = 0x278D0;
}
