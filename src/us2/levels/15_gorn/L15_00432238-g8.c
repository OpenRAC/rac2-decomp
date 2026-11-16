#include "include_asm.h"

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
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void FadeToBlack(int);
extern void level_store_value_pair_us2(int, void *);
extern s32 gorn_reward_panel_draw_us2(void);
extern void snd_clamp_copy_volumes(void);
extern int MemcardSave(int,int);
extern void hero_set_state_value_c(int);
extern void ResetGornStageCounters(void *);
extern int request_begin_slot(int,int,int,int,int);

/* Finishes a Gorn challenge stage (USA v2.00): stops the stage sound, shows the reward panel and
   adds the bolts, then waits for the pad to retry or leave. */
void gorn_finish_challenge_stage_us2(char *moby, int stage)
{
    char *vars = *(char **)(moby + 0x68);
    char *stage_moby = g_moby_base + (*(int *)(vars + 0x20) << 8);
    GornData *data = *(GornData **)(stage_moby + 0x68);
    int voice_id = data->id;
    if (voice_id != -1) {
        char *entry = g_sound_state + voice_id * 0x70;
        if (*(char **)(entry + 0x88) == stage_moby && *(unsigned char *)(entry + 0x74))
            snd_stop_voice(voice_id);
    }
    data->id = -1;
    if (g_challenge_mode == 2) {
        return;
    }
    if (!math_fast_float_d(vars + 0x6C)) {
        return;
    }
    if (g_challenge_menu_data && !g_gorn_stage_finished_flag) {
        int count, value;
        FadeToBlack(30);
        level_store_value_pair_us2(0, gorn_reward_panel_draw_us2);
        count = g_challenge_completed_a[stage];
        value = g_gorn_reward_table[stage][count < 3 ? count : 2];
        g_gorn_stage_finished_flag = 1;
        g_gorn_finished_stage_num = stage;
        g_gorn_challenge_active_flag = 0;
        g_challenge_menu_loaded = 0;
        if (g_extras_unlocked_flag) value *= 10;
        g_challenge_completed_a[stage] = count + 1;
        g_player_bolts = g_player_bolts + value;
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
