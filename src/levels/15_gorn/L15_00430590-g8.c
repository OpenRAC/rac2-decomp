#include "common.h"
extern char *D_L15_001B261C;
extern char g_sound_state[];

typedef struct { char pad[0x270]; int id; } GornData;
extern int D_L15_001A8F00 MACRO_ADDR;
extern int D_L15_001A904C __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
extern int D_L15_001B1520[4] __attribute__((sda));
extern int D_L15_001B15D8[4][3] __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda)), D_L15_001B1578 __attribute__((sda));
extern int D_L15_001B15C8 __attribute__((sda)), D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B36A4, g_player_bolts;
extern unsigned char D_001A7A0A;
extern int D_00138324 NOT_SDA;
/* Absolute suffix view shared with func_L15_00432008. */
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void FadeToBlack(int);
extern void level_store_value_pair(int, void *);
extern void gorn_reward_panel_draw(void);
extern void snd_clamp_copy_volumes(void);
extern void MemcardSave(int,int);
extern void hero_set_state_value_c(int);
extern void ResetGornStageCounters(void *);
extern void request_begin_slot(int,int,int,int,int);
/* Ends a Gorn challenge stage: stops its sound, pays the reward, shows the reward panel and then picks the next menu entry. */
void gorn_finish_challenge_stage(char *moby, int stage_num)
{
    char *vars = *(char **)(moby + 0x68);
    char *target_moby = D_L15_001B261C + (*(int *)(vars + 0x20) << 8);
    GornData *data = *(GornData **)(target_moby + 0x68);
    int sound_id = data->id;
    if (sound_id != -1) {
        char *entry = g_sound_state + sound_id * 0x70;
        if (*(char **)(entry + 0x88) == target_moby && *(unsigned char *)(entry + 0x74))
            snd_stop_voice(sound_id);
    }
    data->id = -1;
    if (D_L15_001A8F00 == 2) {
        return;
    }
    if (!math_fast_float_d(vars + 0x6C)) {
        return;
    }
    if (D_L15_001A904C && !D_L15_001B15CC) {
        int times_done, reward;
        FadeToBlack(30);
        level_store_value_pair(0, gorn_reward_panel_draw);
        times_done = D_L15_001B1520[stage_num];
        reward = D_L15_001B15D8[stage_num][times_done < 3 ? times_done : 2];
        D_L15_001B15CC = 1;
        D_L15_001B36A4 = stage_num;
        D_L15_001B157C = 0;
        D_L15_001B1578 = 0;
        if (D_001A7A0A) reward *= 10;
        D_L15_001B1520[stage_num] = times_done + 1;
        g_player_bolts = g_player_bolts + reward;
        snd_clamp_copy_volumes();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (!math_fast_float_d(vars + 0x50)) {
        if (D_00138324 & 0x40) {
            D_L15_001B15CC = 0;
            *(int *)(vars + 0x50) = 5400;
            FadeToBlack(30);
            hero_set_state_value_c(0);
            *(int *)(vars + 0x6C) = 120;
            if (D_L15_001B1520[0]) {
                if (D_L15_001B1520_4[1] && D_L15_001B1520_4[2]) {
                    D_L15_001B15C8 = 3;
                } else if (D_L15_001B1520[0]) {
                    if (D_L15_001B1520_4[1]) {
                        D_L15_001B15C8 = 2;
                    } else {
                        D_L15_001B15C8 = 1;
                    }
                }
            }
            D_L15_001B15BC = 0;
            ResetGornStageCounters(moby);
        } else if (D_00138324 & 0x10) {
            request_begin_slot(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(vars + 0x50) = 5400;
    }
}
