/* func_PAL_L15_00433068, the PAL copy of func_L15_0042DCE0: the same C, where the timers are
   scaled to 50 Hz, the search of the mission records is gone (the kind index starts at 1
   instead) and D_L15_001B15C4 is set after the other mission state. */
#include "common.h"

/* A moby: one 0x100-byte entry of the moby table. */
typedef struct {
    u8 pad00[0x20];
    u8 state;                   /* 0x20 */
    u8 pad21[0x30 - 0x21];
    u8 updateDistance;          /* 0x30 */
    u8 pad31;
    u16 drawDistance;           /* 0x32 */
    u16 flags;                  /* 0x34 */
    u8 pad36[0x68 - 0x36];
    void *vars;                 /* 0x68: the instance data */
    u8 pad6C[0x100 - 0x6C];
} Moby;

/* The controller's instance data. */
typedef struct {
    s32 index;                  /* 0x00: copied to the mission state */
    u8 pad04[0x24 - 0x04];
    s32 moby;                   /* 0x24: index in the moby table */
    u8 pad28[0x34 - 0x28];
    s32 f34;                    /* 0x34 */
    u8 pad38[0x50 - 0x38];
    s32 f50;                    /* 0x50 */
    s32 f54;                    /* 0x54 */
    u8 pad58[0x64 - 0x58];
    s32 f64;                    /* 0x64 */
    s32 timer;                  /* 0x68: counted down by func_00282948 */
    s32 f6C;                    /* 0x6C */
} ControllerVars;

typedef struct {
    s32 index;                  /* 0x00 */
    u8 pad04[0x14 - 0x04];
    s32 rounds;                 /* 0x14: counted when state 3 ends */
    u8 pad18[0x24 - 0x18];
    s32 f24;                    /* 0x24 */
    u8 pad28[0x2C - 0x28];
    s32 waiting;                /* 0x2C: 1 while the controller's timer runs */
    f32 f30;                    /* 0x30 */
    u8 pad34[0x4C - 0x34];
    void (*reset)(void);        /* 0x4C */
    void (*resetAll)(void);     /* 0x50 */
    s32 (*onHit)(Moby *moby, s32 keep); /* 0x54 */
    u8 pad58[0x78 - 0x58];
    Moby *controller;           /* 0x78 */
} MissionState;

typedef struct {
    u8 pad00[0x6B];
    u8 completions[4];          /* 0x6B */
} SaveGame;

typedef struct {
    u8 pad0000[0x2290];
    Moby *moby;                 /* 0x2290 */
} Hero;

extern MissionState g_gorn_challenge_vars;
extern SaveGame g_game_flag_table;
extern Hero g_hero_state;
extern Moby *g_moby_base;
extern s32 g_gorn_timer_start_value;
extern s32 g_gorn_timer_limit_value;
extern void (*g_challenge_callback_a)(void);
extern void (*g_challenge_callback_b)(void);
extern s32 g_challenge_completed_b;
extern s32 g_challenge_completed_c;
extern s32 g_challenge_completed_d;
extern s32 g_challenge_mode;
extern f32 g_screen_l15_scale;
extern s32 g_item_state_words[];
extern s32 g_challenge_menu_choice __attribute__((sda));
extern Moby *g_gorn_hud_moby __attribute__((sda));
extern s32 g_gorn_enabled_flag __attribute__((sda));
extern s32 g_gorn_weapon_slot_index __attribute__((sda));
extern s32 g_cutscene_l15_started_flag __attribute__((sda));
extern s32 g_gorn_path_effect __attribute__((sda));
extern s32 g_label_sprite_a __attribute__((sda));
extern s32 g_label_sprite_b __attribute__((sda));
extern s32 g_label_sprite_c __attribute__((sda));
extern s32 g_challenge_menu_loaded __attribute__((sda));
extern s32 g_gorn_challenge_active_flag __attribute__((sda));
extern s32 g_gorn_message_counter __attribute__((sda));
extern s32 g_gorn_save_loaded_flag __attribute__((sda));
extern s32 g_challenge_completed_a __attribute__((sda));
extern s32 g_gorn_cutscene_active_flag __attribute__((sda));
extern s32 g_gorn_hud_first_flag __attribute__((sda));
extern s32 g_gorn_setup_flag __attribute__((sda));
extern s32 g_gorn_challenge_count __attribute__((sda));
extern s32 g_challenge_menu_data MACRO_ADDR;
extern s32 g_gorn_stage_finished_flag __attribute__((sda));

extern void hero_set_state_value_a(s32 value);
extern void hero_set_state_value_b(s32 value);
extern void level_select_random_object(void);
extern void level_store_pair_with_increment(s32 a0, s32 a1);
extern void moby_set_flag_bit(Moby *moby, s32 enabled);
extern s32 func_PAL_L00_002C4480(s32 action, s32 animate);
extern void hero_set_state_value_c(s32 value);
extern s32 LockedEntryMenuInput_pal(void);
extern void ship_save_transform_state_pal(void);
extern s32 func_PAL_00289730(s32 key, s32 selection);
extern s32 status_any_record_nonzero(void);
extern s32 math_fast_float_d(s32 *timer);
extern void func_PAL_L15_00436368(Moby *moby);
extern void func_PAL_L15_004366F0(Moby *moby);
extern void func_PAL_L15_00436870(Moby *moby);
extern void func_PAL_L15_00436A10(Moby *moby);
extern void level_store_value_pair_pal(s32 a0, void (*callback)(void));
extern s32 cam_is_mode_active(void);
extern s32 func_PAL_L15_004334B0(void);
extern void func_PAL_L10_00428C8C(void);
extern void func_PAL_L10_00428D58(void);
extern s32 moby_l15_apply_hit_damage(Moby *moby, s32 keep);

/* Update of the Gorn mission controller; the same body as Hrugis's func_L10_00421288.
   State 0 sets up the mission state, its callbacks and the controller's timers and
   loads the saved completion counts. State 1 runs the shared update and the chosen kind's handler.
   State 3 waits for func_L05_00442860, then counts the round and goes back to state 1. */
void func_PAL_L15_00433068(Moby *moby)
{
    ControllerVars *vars = moby->vars;
    u8 completed0;
    u8 completed1;
    u8 completed2;
    u8 completed3;

    switch (moby->state) {
    case 0:
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        g_gorn_challenge_vars.index = vars->index;
        g_gorn_challenge_vars.f30 = 8.0f;
        g_challenge_menu_choice = -2;
        g_gorn_challenge_vars.f24 = 1;
        g_gorn_hud_moby = moby;
        g_gorn_weapon_slot_index = 1;
        g_cutscene_l15_started_flag = 0;
        g_gorn_path_effect = 0;
        g_label_sprite_a = 0;
        g_label_sprite_b = 0;
        g_label_sprite_c = 0;
        g_challenge_menu_loaded = 0;
        g_gorn_challenge_active_flag = 0;
        g_gorn_enabled_flag = 1;
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        vars->f34 = 0;
        g_gorn_message_counter = 0;
        vars->f50 = 4500;
        vars->f54 = 100;
        vars->f64 = 200;
        vars->f6C = 150;
        vars->timer = 300;
        g_gorn_timer_start_value = 450;
        g_gorn_timer_limit_value = 300;
        g_gorn_challenge_vars.reset = func_PAL_L10_00428C8C;
        g_gorn_challenge_vars.resetAll = func_PAL_L10_00428D58;
        g_gorn_save_loaded_flag = 0;
        g_gorn_challenge_vars.onHit = moby_l15_apply_hit_damage;
        g_gorn_challenge_vars.controller = moby;
        hero_set_state_value_a(1);
        hero_set_state_value_b(0);
        completed0 = g_game_flag_table.completions[0];
        completed1 = g_game_flag_table.completions[1];
        completed2 = g_game_flag_table.completions[2];
        completed3 = g_game_flag_table.completions[3];
        g_challenge_callback_a = func_PAL_L10_00428C8C;
        g_challenge_callback_b = func_PAL_L10_00428D58;
        g_challenge_completed_b = completed1;
        g_challenge_completed_c = completed2;
        g_challenge_completed_d = completed3;
        g_challenge_completed_a = completed0;
        if (!g_challenge_completed_a)
            g_gorn_cutscene_active_flag = 1;
        else
            g_gorn_cutscene_active_flag = 0;
        if (g_hero_state.moby != 0)
            g_hero_state.moby->flags |= 0x41;
        /* fall through */
    case 1: {
        /* One 1 for the stores and the test below: literal 1s compile differently. */
        s32 on = 1;

        level_select_random_object();
        level_store_pair_with_increment((s32)(g_screen_l15_scale * -230.0f + 0.5f), 2);
        if (!g_gorn_hud_first_flag) {
            moby_set_flag_bit(&g_moby_base[vars->moby], 1);
            g_gorn_hud_first_flag = on;
            g_gorn_message_counter = 0;
        }
        if (g_gorn_message_counter++ < 5 || g_challenge_mode == 2)
            break;

        func_PAL_L00_002C4480(0x31, 0);
        if (g_gorn_enabled_flag) {
            hero_set_state_value_c(on);
            g_challenge_menu_choice = LockedEntryMenuInput_pal();
            if (g_challenge_menu_choice != -2)
                ship_save_transform_state_pal();
            break;
        }
        if (!g_gorn_setup_flag) {
            func_PAL_00289730(0xA17, 0x6E);
            g_gorn_setup_flag = on;
        }
        if ((g_item_state_words[5] == on || g_item_state_words[5] == 5 || g_item_state_words[5] == 10)
            && !status_any_record_nonzero() && !g_gorn_save_loaded_flag) {
            func_PAL_00289730(0xA18, 0x6F);
            g_gorn_save_loaded_flag = 1;
        }
        if (math_fast_float_d(&vars->timer))
            g_gorn_challenge_vars.waiting = 0;
        else
            g_gorn_challenge_vars.waiting = 1;
        hero_set_state_value_c(0);
        if (g_challenge_menu_choice != -2 && g_gorn_challenge_count >= 3) {
            switch (g_challenge_menu_choice) {
            case 0:
                func_PAL_L15_00436368(moby);
                break;
            case 1:
                func_PAL_L15_004366F0(moby);
                break;
            case 2:
                func_PAL_L15_00436870(moby);
                break;
            case 3:
                func_PAL_L15_00436A10(moby);
                break;
            }
        }
        if (g_challenge_menu_data && !g_challenge_menu_loaded && !g_gorn_stage_finished_flag) {
            level_store_value_pair_pal(0, func_PAL_L15_004334B0);
            g_gorn_challenge_active_flag = 0;
            g_challenge_menu_loaded = 1;
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (!cam_is_mode_active()) {
            g_gorn_challenge_vars.waiting = 0;
            g_gorn_challenge_vars.rounds++;
            moby->state = 1;
        }
        break;
    }
}
