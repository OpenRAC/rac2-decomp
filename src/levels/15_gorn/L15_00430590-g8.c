#include "common.h"
extern char *g_moby_base;
extern char g_sound_state[];

typedef struct { char pad[0x270]; int id; } GornData;
extern int g_challenge_mode MACRO_ADDR;
extern int g_challenge_menu_data __attribute__((sda));
extern int g_gorn_stage_finished_flag __attribute__((sda));
extern int g_challenge_completed_a[4] __attribute__((sda));
extern int g_gorn_reward_table[4][3] __attribute__((sda));
extern int g_gorn_challenge_active_flag __attribute__((sda)), g_challenge_menu_loaded __attribute__((sda));
extern int g_gorn_selected_challenge __attribute__((sda)), g_gorn_cutscene_started_flag __attribute__((sda));
extern int g_gorn_finished_stage_num, g_player_bolts;
extern unsigned char g_extras_unlocked_flag;
extern int g_pad_held_flags NOT_SDA;
/* Absolute suffix view shared with func_L15_00432008. */
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void FadeToBlack(int);
extern void level_store_value_pair(int, void *);
extern s32 gorn_reward_panel_draw(void);
extern void snd_clamp_copy_volumes(void);
extern int MemcardSave(int,int);
extern void hero_set_state_value_c(int);
extern void ResetGornStageCounters(void *);
extern int request_begin_slot(int,int,int,int,int);
/* Ends a Gorn challenge stage: stops its sound, pays the reward, shows the reward panel and then picks the next menu entry. */
void gorn_finish_challenge_stage(char *moby, int stage_num)
{
    char *vars = *(char **)(moby + 0x68);
    char *target_moby = g_moby_base + (*(int *)(vars + 0x20) << 8);
    GornData *data = *(GornData **)(target_moby + 0x68);
    int sound_id = data->id;
    if (sound_id != -1) {
        char *entry = g_sound_state + sound_id * 0x70;
        if (*(char **)(entry + 0x88) == target_moby && *(unsigned char *)(entry + 0x74))
            snd_stop_voice(sound_id);
    }
    data->id = -1;
    if (g_challenge_mode == 2) {
        return;
    }
    if (!math_fast_float_d(vars + 0x6C)) {
        return;
    }
    if (g_challenge_menu_data && !g_gorn_stage_finished_flag) {
        int times_done, reward;
        FadeToBlack(30);
        level_store_value_pair(0, gorn_reward_panel_draw);
        times_done = g_challenge_completed_a[stage_num];
        reward = g_gorn_reward_table[stage_num][times_done < 3 ? times_done : 2];
        g_gorn_stage_finished_flag = 1;
        g_gorn_finished_stage_num = stage_num;
        g_gorn_challenge_active_flag = 0;
        g_challenge_menu_loaded = 0;
        if (g_extras_unlocked_flag) reward *= 10;
        g_challenge_completed_a[stage_num] = times_done + 1;
        g_player_bolts = g_player_bolts + reward;
        snd_clamp_copy_volumes();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (!math_fast_float_d(vars + 0x50)) {
        if (g_pad_held_flags & 0x40) {
            g_gorn_stage_finished_flag = 0;
            *(int *)(vars + 0x50) = 5400;
            FadeToBlack(30);
            hero_set_state_value_c(0);
            *(int *)(vars + 0x6C) = 120;
            if (g_challenge_completed_a[0]) {
                if (D_L15_001B1520_4[1] && D_L15_001B1520_4[2]) {
                    g_gorn_selected_challenge = 3;
                } else if (g_challenge_completed_a[0]) {
                    if (D_L15_001B1520_4[1]) {
                        g_gorn_selected_challenge = 2;
                    } else {
                        g_gorn_selected_challenge = 1;
                    }
                }
            }
            g_gorn_cutscene_started_flag = 0;
            ResetGornStageCounters(moby);
        } else if (g_pad_held_flags & 0x10) {
            request_begin_slot(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(vars + 0x50) = 5400;
    }
}
