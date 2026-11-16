/* func_US2_L05_0041EFBC, the USA v2.00 copy of func_L05_0041DA20: the same C, without the loop that
   skipped unusable D_L05_002A1800 entries. D_L05_001B13DC now starts at 1, and D_L05_001B13E8 is set
   after the other flags. */
#include "common.h"

typedef struct {
    int id, pad4[4], count, pad18[3], enabled, pad28, pending;
    float radius;
    int pad34[6]; void *callbacks[3]; int pad58[8];
    char *object; int pad7C[5]; int mode; int pad94[2];
    int settings[4];
} Control05;
extern Control05 g_feltzin_challenge_state;
typedef struct {
    int id, a4, a8, aC, a10;
    char pad14[0x28 - 0x14];
    int target; char pad2C[8]; int stage; char pad38[8];
    int warmup, delay, first, second, third, fourth, fifth, timeout;
} State05;
extern unsigned char g_game_flag_table[];
extern char g_hero_state[];
extern unsigned char g_ship_settings_byte_a[] __attribute__((sda)), g_ship_settings_byte_b[] __attribute__((sda)), g_ship_settings_byte_c[] __attribute__((sda));
extern float g_ship_settings_float_c[] __attribute__((sda)), g_ship_settings_float_a[] __attribute__((sda)), g_ship_settings_float_d[] __attribute__((sda)), g_ship_settings_float_b[] __attribute__((sda));
extern int g_ship_settings_word[] __attribute__((sda));
extern unsigned char g_feltzin_record_flag_a[] __attribute__((sda)), g_feltzin_record_flag_b[] __attribute__((sda)), g_feltzin_record_flag_c[] __attribute__((sda));
extern float g_feltzin_record_float_a[] __attribute__((sda)), g_feltzin_record_float_b[] __attribute__((sda)), g_feltzin_record_float_c[] __attribute__((sda)), g_feltzin_record_float_d[] __attribute__((sda));
extern int g_feltzin_record_word[] __attribute__((sda)), g_feltzin_countdown[] __attribute__((sda));
extern int g_feltzin_reset_callback[] __attribute__((sda)), g_feltzin_shutdown_callback[] __attribute__((sda));
extern int g_feltzin_challenge_param_a[] __attribute__((sda)), g_feltzin_challenge_param_b[] __attribute__((sda)), g_feltzin_challenge_param_c[] __attribute__((sda));
extern int g_game_mode_a[] __attribute__((sda));
extern int g_feltzin_mission_data MACRO_ADDR;
extern float g_screen_l05_scale[] __attribute__((sda));
extern char *g_feltzin_target_mobys[] __attribute__((sda));
extern void hero_set_state_value_a(int), hero_set_state_value_b(int), level_select_random_object(void);
extern void level_store_pair_with_increment(int, int), moby_set_flag_bit(void *, int);
extern int hero_l00_change_action_us2(int, int);
extern void hero_set_state_value_c(int);
extern int LockedEntryMenuInput_us2(void);
extern void ship_save_transform_state(void);
extern int subtitle_request_voice_line_us2(int, int);
extern int math_fast_float_d(void *);
extern void feltzin_mission_one_update_us2(void *), feltzin_mission_two_update_us2(void *);
extern void feltzin_mission_three_update_us2(void *), UpdateFeltzinGateCourse_us2(void *);
extern void level_store_value_pair_us2(int, void *);
extern int cam_is_mode_active(void);
extern void feltzin_challenge_reset_free_records(void), feltzin_challenge_shutdown_us2(void);
extern s32 DrawFeltzinCombatHud_us2(void);
extern int feltzin_target_damage(char *, int);
extern int g_feltzin_menu_mode __attribute__((sda));
extern int g_feltzin_controller_moby __attribute__((sda));
extern int g_feltzin_needs_reset __attribute__((sda));
extern int g_feltzin_active_slot_index __attribute__((sda));
extern int g_feltzin_challenge_active __attribute__((sda));
extern int g_feltzin_record_a __attribute__((sda));
extern int g_feltzin_record_b __attribute__((sda));
extern int g_feltzin_record_c __attribute__((sda));
extern int g_feltzin_hud_sprite_a __attribute__((sda));
extern int g_feltzin_hud_sprite_b __attribute__((sda));
extern int g_feltzin_hud_sprite_c __attribute__((sda));
extern int g_feltzin_intro_done __attribute__((sda));
extern int g_feltzin_menu_opened __attribute__((sda));
extern int g_feltzin_frame_counter __attribute__((sda));
extern int g_feltzin_challenge_data __attribute__((sda));
extern int g_feltzin_no_challenge_flag __attribute__((sda));
extern int g_feltzin_init_flag_a __attribute__((sda));
extern int g_feltzin_init_flag_b __attribute__((sda));
extern int g_feltzin_mission_index __attribute__((sda));
extern int g_feltzin_menu_started __attribute__((sda));
/* Per-frame update. The first frame resets the control record, the timers in the moby's state and
   the saved mode record and sets flags on the hero's moby; later frames run func_L05_00379B60 and,
   after five settled frames, put the hero in action 0x31 and dispatch on the mode in
   D_L05_001B1360. */
void feltzin_challenge_controller_update_us2(char *moby)
{
    State05 *vars = *(State05 **)(moby + 0x68);
    int on;
    char *hero_data, *held_moby;
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(short *)(moby + 0x32) = 0x1FF;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        moby[0x20] = 1;
        g_feltzin_challenge_state.id = vars->id;
        g_feltzin_challenge_state.radius = 8.0f;
        g_feltzin_menu_mode = -2;
        g_feltzin_challenge_state.enabled = 1;
        g_feltzin_controller_moby = (int)moby;
        g_feltzin_active_slot_index = 1;
        g_feltzin_challenge_active = 0;
        g_feltzin_record_a = 0;
        g_feltzin_record_b = 0;
        g_feltzin_record_c = 0;
        g_feltzin_hud_sprite_a = 0;
        g_feltzin_hud_sprite_b = 0;
        g_feltzin_hud_sprite_c = 0;
        g_feltzin_intro_done = 0;
        g_feltzin_menu_opened = 0;
        g_feltzin_needs_reset = 1;
        *(short *)(moby + 0x32) = 0x1FF;
        *(unsigned char *)(moby + 0x30) = 0xFF;
        moby[0x20] = 1;
        vars->stage = 0;
        g_feltzin_frame_counter = 0;
        vars->warmup = 5400; vars->delay = 7200;
        vars->first = 150; vars->second = 180;
        vars->third = 300; vars->fourth = 480;
        vars->fifth = 120; vars->timeout = 108000;
        g_feltzin_countdown[0] = 540;
        g_feltzin_challenge_state.callbacks[0] = feltzin_challenge_reset_free_records;
        g_feltzin_challenge_state.callbacks[1] = feltzin_challenge_shutdown_us2;
        g_feltzin_challenge_state.callbacks[2] = feltzin_target_damage;
        g_feltzin_challenge_state.object = moby;
        hero_set_state_value_a(1);
        hero_set_state_value_b(0);
        g_feltzin_reset_callback[0] = (int)feltzin_challenge_reset_free_records;
        g_feltzin_shutdown_callback[0] = (int)feltzin_challenge_shutdown_us2;
        g_feltzin_challenge_data = g_game_flag_table[0x61];
        g_feltzin_challenge_param_a[0] = g_game_flag_table[0x62];
        g_feltzin_challenge_param_b[0] = g_game_flag_table[0x63];
        g_feltzin_challenge_param_c[0] = g_game_flag_table[0x64];
        if (!g_feltzin_challenge_data) g_feltzin_no_challenge_flag = 1;
        else g_feltzin_no_challenge_flag = 0;
        hero_data = g_hero_state;
        g_feltzin_record_flag_a[0] = g_ship_settings_byte_a[0];
        g_feltzin_record_flag_b[0] = g_ship_settings_byte_b[0];
        g_feltzin_record_flag_c[0] = g_ship_settings_byte_c[0];
        g_feltzin_record_float_b[0] = g_ship_settings_float_a[0];
        g_feltzin_record_float_d[0] = g_ship_settings_float_b[0];
        g_feltzin_record_float_a[0] = g_ship_settings_float_c[0];
        g_feltzin_record_float_c[0] = g_ship_settings_float_d[0];
        g_feltzin_record_word[0] = g_ship_settings_word[0];
        g_feltzin_challenge_state.mode = 4;
        g_feltzin_challenge_state.settings[0] = vars->a4;
        g_feltzin_challenge_state.settings[1] = vars->a8;
        g_feltzin_challenge_state.settings[2] = vars->aC;
        g_feltzin_challenge_state.settings[3] = vars->a10;
        held_moby = *(char **)(hero_data + 0x2290);
        if (held_moby)
            *(short *)(held_moby+0x34) |= 0x41;
        /* fall through */
    case 1:
        on = 1;
        level_select_random_object();
        level_store_pair_with_increment((int)(g_screen_l05_scale[0] * -230.0f + 0.5f), 2);
        if (!g_feltzin_init_flag_a) {
            moby_set_flag_bit(g_feltzin_target_mobys[0] + vars->target*256,1);
            g_feltzin_init_flag_a = on;
            g_feltzin_frame_counter = 0;
        }
        if (g_feltzin_frame_counter++ < 5 || g_game_mode_a[0] == 2) break;
        hero_l00_change_action_us2(0x31,0);
        if (g_feltzin_needs_reset) {
            hero_set_state_value_c(1);
            g_feltzin_menu_mode = LockedEntryMenuInput_us2();
            if (g_feltzin_menu_mode != -2) ship_save_transform_state();
            break;
        }
        if (!g_feltzin_init_flag_b) {
            subtitle_request_voice_line_us2(0xA17,110);
            g_feltzin_init_flag_b = on;
        }
        if (math_fast_float_d((char *)vars+0x54)) g_feltzin_challenge_state.pending = 0;
        else g_feltzin_challenge_state.pending = on;
        hero_set_state_value_c(0);
        if (g_feltzin_menu_mode != -2 && g_feltzin_mission_index >= 3) {
            switch (g_feltzin_menu_mode) {
            case 0: feltzin_mission_one_update_us2(moby); break;
            case 1: feltzin_mission_two_update_us2(moby); break;
            case 2: feltzin_mission_three_update_us2(moby); break;
            case 3: UpdateFeltzinGateCourse_us2(moby); break;
            }
        }
        if (g_feltzin_mission_data && !g_feltzin_intro_done && !g_feltzin_menu_started) {
            level_store_value_pair_us2(0,DrawFeltzinCombatHud_us2);
            g_feltzin_menu_opened = 0;
            g_feltzin_intro_done = 1;
        }
        break;
    case 2: break;
    case 3:
        if (!cam_is_mode_active()) {
            g_feltzin_challenge_state.pending = 0;
            g_feltzin_challenge_state.count++;
            moby[0x20] = 1;
        }
        break;
    }
}
