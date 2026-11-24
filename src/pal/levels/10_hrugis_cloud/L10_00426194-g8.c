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
    u8 pad04[0x28 - 0x04];
    s32 moby;                   /* 0x28: index in the moby table */
    u8 pad2C[0x34 - 0x2C];
    s32 f34;                    /* 0x34 */
    u8 pad38[0x40 - 0x38];
    s32 f40;                    /* 0x40 */
    s32 f44;                    /* 0x44 */
    s32 f48;                    /* 0x48 */
    s32 f4C;                    /* 0x4C */
    s32 f50;                    /* 0x50 */
    s32 timer;                  /* 0x54: counted down by func_00282948 */
    s32 f58;                    /* 0x58 */
    s32 f5C;                    /* 0x5C */
} ControllerVars;

/* The mission state the level-5 combat code shares (D_L10_00221CD0). */
typedef struct {
    s32 index;                  /* 0x00: picks a 0x80-byte record of D_001B2614 */
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
    u8 pad7C[0x88 - 0x7C];
    s32 f88;                    /* 0x88: cleared when the selection changes */
    s32 selection;              /* 0x8C: follows D_L10_001B13A0 */
} MissionState;

/* The saved game: Hrugis keeps its four completion counts at 0x66 (func_L10_00425888). */
typedef struct {
    u8 pad00[0x66];
    u8 completions[4];          /* 0x66 */
} SaveGame;

/* The hero (D_00189E20), as far as the controller reads it. */
typedef struct {
    u8 pad0000[0x2290];
    Moby *moby;                 /* 0x2290 */
} Hero;

extern MissionState g_mission_state;
extern SaveGame g_game_flag_table;
extern Hero g_hero_state;
extern Moby *g_moby_base_table;            /* the moby table */
extern s32 g_mission_timer_a;
extern s32 g_mission_timer_b;
extern void (*g_mission_reset_callback)(void);
extern void (*g_mission_reset_alt_callback)(void);
/* The completion counts while the level runs: kind 0 at D_L10_001B1390 (sda), 1 to 3
   here (absolute). */
extern s32 g_mission_completed_first;
extern s32 g_mission_completed_second;
extern s32 g_mission_completed_third;
extern s32 g_mission_reward_state;
extern f32 g_screen_l10_scale;
extern s32 g_item_state_words[];
extern s32 g_selected_mission_kind __attribute__((sda));  /* the selected kind, -2 for none */
extern Moby *g_hud_blink_moby __attribute__((sda));
extern s32 g_kind_choosing_flag __attribute__((sda));  /* set while a kind is being chosen */
extern s32 g_mission_record_index __attribute__((sda));  /* index of a mission record */
extern s32 g_mission_initialized __attribute__((sda));
extern s32 g_gate_pending_moby __attribute__((sda));
extern s32 g_hud_label_sprite_first __attribute__((sda));
extern s32 g_hud_label_sprite_second __attribute__((sda));
extern s32 g_hud_label_sprite_third __attribute__((sda));
extern s32 g_hud_setup_done __attribute__((sda));
extern s32 g_hud_state_flag __attribute__((sda));
extern s32 g_state_frame_count __attribute__((sda));  /* frames in state 1 */
extern s32 g_subtitle_second_queued __attribute__((sda));  /* subtitle 0xA18 queued */
extern s32 g_mission_completion_counts __attribute__((sda));
extern s32 g_no_first_completion_flag __attribute__((sda));  /* no kind 0 completion yet */
extern s32 g_moby_enabled_flag __attribute__((sda));  /* vars->moby enabled */
extern s32 g_subtitle_first_queued __attribute__((sda));  /* subtitle 0xA17 queued */
extern s32 g_mission_reward_level __attribute__((sda));
extern s32 g_hud_sprite_table_base MACRO_ADDR;
extern s32 g_reward_active_flag __attribute__((sda));

extern void hero_set_state_value_a(s32 value);
extern void hero_set_state_value_b(s32 value);
extern void level_select_random_object(void);
extern void level_store_pair_with_increment(s32 a0, s32 a1);
extern void moby_set_flag_bit(Moby *moby, s32 enabled);
extern s32 hero_l00_set_move_state(s32 action, s32 animate);
extern void hero_set_state_value_c(s32 value);
extern s32 LockedEntryMenuInput(void);
extern void ship_save_transform_state(void);
extern s32 subtitle_request_voice_line(s32 key, s32 selection);
extern s32 status_any_record_nonzero(void);
extern s32 math_fast_float_d(s32 *timer);
extern void mission_first_update_pal(Moby *moby);
extern void mission_second_update_pal(Moby *moby);
extern void mission_third_update_pal(Moby *moby);
extern void gate_course_update_pal(Moby *moby);
extern void level_store_value_pair(s32 a0, void (*callback)(void));
extern s32 cam_is_mode_active(void);
extern s32 DrawHrugisMissionHud_pal(void);
extern void mission_reset_counters_pal(void);
extern void mission_reset_counters_alt_pal(void);
extern s32 process_object_collision_damage_pal(Moby *moby, s32 keep);

/* func_PAL_L10_00426194, the PAL copy of func_L10_00421288: the same C, where the
   timers are 50 Hz values, record 1 is set instead of searched for, and
   D_L10_001B1438 is set after the other flags.

   Update of the Hrugis mission controller. State 0 sets up the mission state, its
   callbacks and the controller's timers and loads the saved completion counts. State 1
   runs the shared update:
   after five frames it lets a kind be chosen, queues two subtitles and runs the chosen
   kind's handler. State 3 waits for func_L05_00442860, then counts the round and goes
   back to state 1. */
void UpdateHrugisController_pal(Moby *moby)
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
        g_mission_state.index = vars->index;
        g_mission_state.f30 = 8.0f;
        g_selected_mission_kind = -2;
        g_mission_state.f24 = 1;
        g_hud_blink_moby = moby;
        g_mission_record_index = 1;
        g_mission_initialized = 0;
        g_gate_pending_moby = 0;
        g_hud_label_sprite_first = 0;
        g_hud_label_sprite_second = 0;
        g_hud_label_sprite_third = 0;
        g_hud_setup_done = 0;
        g_hud_state_flag = 0;
        g_kind_choosing_flag = 1;
        moby->drawDistance = 0x1FF;
        moby->updateDistance = 0xFF;
        moby->state = 1;
        vars->f34 = 0;
        g_state_frame_count = 0;
        vars->f40 = 135000;
        vars->f50 = 200;
        vars->f44 = 100;
        vars->timer = 400;
        vars->f58 = 100;
        vars->f48 = 9000;
        vars->f5C = 125;
        g_mission_timer_a = 450;
        g_mission_timer_b = 300;
        g_subtitle_second_queued = 0;
        g_mission_state.reset = mission_reset_counters_pal;
        g_mission_state.resetAll = mission_reset_counters_alt_pal;
        g_mission_state.onHit = process_object_collision_damage_pal;
        g_mission_state.controller = moby;
        hero_set_state_value_a(1);
        hero_set_state_value_b(0);
        completed0 = g_game_flag_table.completions[0];
        completed1 = g_game_flag_table.completions[1];
        completed2 = g_game_flag_table.completions[2];
        completed3 = g_game_flag_table.completions[3];
        g_mission_reset_callback = mission_reset_counters_pal;
        g_mission_reset_alt_callback = mission_reset_counters_alt_pal;
        g_mission_completed_first = completed1;
        g_mission_completed_second = completed2;
        g_mission_completed_third = completed3;
        g_mission_completion_counts = completed0;
        if (!g_mission_completion_counts)
            g_no_first_completion_flag = 1;
        else
            g_no_first_completion_flag = 0;
        if (g_hero_state.moby != 0)
            g_hero_state.moby->flags |= 0x41;
        /* fall through */
    case 1: {
        /* One 1 for the stores and the test below: literal 1s compile differently. */
        s32 on = 1;

        level_select_random_object();
        level_store_pair_with_increment((s32)(g_screen_l10_scale * -230.0f + 0.5f), 2);
        if (g_mission_state.selection != g_selected_mission_kind) {
            g_mission_state.selection = g_selected_mission_kind;
            g_mission_state.f88 = 0;
        }
        if (!g_moby_enabled_flag) {
            moby_set_flag_bit(&g_moby_base_table[vars->moby], 1);
            g_moby_enabled_flag = on;
            g_state_frame_count = 0;
        }
        if (g_state_frame_count++ < 5 || g_mission_reward_state == 2)
            break;

        hero_l00_set_move_state(0x31, 0);
        if (g_kind_choosing_flag) {
            hero_set_state_value_c(on);
            g_selected_mission_kind = LockedEntryMenuInput();
            if (g_selected_mission_kind != -2)
                ship_save_transform_state();
            break;
        }
        if (!g_subtitle_first_queued) {
            subtitle_request_voice_line(0xA17, 0x6E);
            g_subtitle_first_queued = on;
        }
        if ((g_item_state_words[0] == on || g_item_state_words[0] == 5 || g_item_state_words[0] == 10)
            && !status_any_record_nonzero() && !g_subtitle_second_queued) {
            subtitle_request_voice_line(0xA18, 0x6F);
            g_subtitle_second_queued = 1;
        }
        if (math_fast_float_d(&vars->timer))
            g_mission_state.waiting = 0;
        else
            g_mission_state.waiting = 1;
        hero_set_state_value_c(0);
        if (g_selected_mission_kind != -2 && g_mission_reward_level >= 3) {
            switch (g_selected_mission_kind) {
            case 0:
                mission_first_update_pal(moby);
                break;
            case 1:
                mission_second_update_pal(moby);
                break;
            case 2:
                mission_third_update_pal(moby);
                break;
            case 3:
                gate_course_update_pal(moby);
                break;
            }
        }
        if (g_hud_sprite_table_base && !g_hud_setup_done && !g_reward_active_flag) {
            level_store_value_pair(0, DrawHrugisMissionHud_pal);
            g_hud_state_flag = 0;
            g_hud_setup_done = 1;
        }
        break;
    }
    case 2:
        break;
    case 3:
        if (!cam_is_mode_active()) {
            g_mission_state.waiting = 0;
            g_mission_state.rounds++;
            moby->state = 1;
        }
        break;
    }
}
