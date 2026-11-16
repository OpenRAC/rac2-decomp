#include "common.h"

/* func_PAL_L00_00371E28, the PAL copy of func_L00_0036F488: the same C, with a second gate before
 * the third call, a state test on three more paths and the times scaled for 50 Hz. */

/* -G8 unit with -frac2-gcse-unsplit-edges (config/cflags.txt): retail keeps one %hi of the hero
 * and one of the pad state in saved registers and forms each block's %lo base afresh; the pad's
 * %hi is hoisted above the first branch on the gate's result. The globals below that retail reads
 * both $gp-relative (in delay slots) and absolute are MACRO_ADDR. */

typedef struct HeroObject { char pad00[0xAA]; short id; } HeroObject;
typedef struct Hero {
    char pad0000[0x123C];
    unsigned char mode;          /* 0x123C */
    char pad123D[0x1248 - 0x123D];
    int submode;                 /* 0x1248 */
    char pad124C[0x1830 - 0x124C];
    HeroObject *object;          /* 0x1830 */
    char pad1834[0x2294 - 0x1834];
    int state;                   /* 0x2294 */
    char pad2298[0x229C - 0x2298];
    int f229C;                   /* 0x229C */
    char pad22A0[0x22B4 - 0x22A0];
    unsigned char f22B4;         /* 0x22B4 */
} Hero;
typedef struct PadState { char pad000[0x1A4]; unsigned int pressed; } PadState;
typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;

extern char g_hero_state[];
extern char g_pad_state[];

extern int g_game_l00_mode MACRO_ADDR;
extern int g_pad_press_window MACRO_ADDR;
extern int g_hero_locked_flag MACRO_ADDR;
extern int g_pad_device_idle_flag MACRO_ADDR;
extern int g_pad_hold_frame_count MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern u32 g_frame_counter MACRO_ADDR;
extern int g_pickup_request_pending MACRO_ADDR;
extern Statistics g_progress_statistics[];
extern unsigned char g_language_settings[] __attribute__((sda));
extern int g_save_menu_flags __attribute__((sda));
extern int g_input_block_flag __attribute__((sda));
extern int g_hero_action_blocked_flag __attribute__((sda));
extern float g_hero_scalar_transition_value __attribute__((sda));

extern int level_get_flag_b(void);
extern int request_begin_slot(int, int, int, int, int);
/* The neighbouring stub in most programs; another function in six of them. */
extern unsigned int ref_L00_0036F488_00(void);
extern int func_PAL_L00_0030BA48(void);
extern int func_PAL_00299538(void);
extern int func_PAL_L00_002D6E48(void);
extern int level_is_mode_in_set(void);
extern int level_run_mode_update_zero(void);
extern int level_is_tracked_object_of_selected_class(int);
extern int level_is_special_mode_active(void);
extern void level_update_countdown_state_machine(void);
extern int PadPressedWithin(int, int, int *);
extern void hud_request_open(void);
extern int hud_is_open_done(void);
extern void func_PAL_L00_002CB5E8(void);
extern int level_is_counter_positive(void);
extern int level_get_setting_value(void);
extern void level_set_global_setting_value(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void hero_update_hit_streak_effect(void);
extern void module_l00_call_handler_with_arg_4_pal(int);
extern void func_L00_0030C710(int);
extern void game_reset_frame_counters(void);
extern void level_run_per_frame_passes(void);
extern void level_count_active_records(void);
extern void moby_update_visible_objects(void);
extern void snd_run_callbacks(void);
extern void hero_l00_update_frame_2_pal(void);
extern void part_update_all(void);
extern void part_l00_update_effect_slots_pal(void);
extern void cam_update_state_pal(void);
extern s32 UpdateSoundVoices_pal(void);
extern void UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void);
extern int hud_update_record_timers_pal(int);
extern void level_run_callbacks(void);
extern void func_PAL_00289AA8(void);
extern void game_update_idle_frame_counters_pal(void);

void func_PAL_L00_00371E28(void)
{
    int blocked;
    int special;

    if (level_get_flag_b() && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (func_PAL_L00_0030BA48() && !g_game_l00_mode && (g_save_menu_flags & 0x600)
        && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (func_PAL_00299538() && !g_game_l00_mode && func_PAL_L00_0030BA48()
        && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (ref_L00_0036F488_00())
        return;

    special = 0;
    blocked = ((Hero *)g_hero_state)->state != 0x31;
    if (((Hero *)g_hero_state)->object) {
        int id = ((Hero *)g_hero_state)->object->id;
        if (id == 0x905 || id == 0x85C || id == 0xEEF || id == 0x10EE)
            special = 1;
    }
    blocked |= special;
    blocked = (blocked != 0);
    blocked |= level_is_mode_in_set() != 0;
    blocked |= level_is_tracked_object_of_selected_class(3) != 0;
    blocked |= level_is_special_mode_active() != 0;
    level_update_countdown_state_machine();

    if (PadPressedWithin(16, ((s32)g_pad_press_window * 5 + 2) / 6, 0) && g_pad_hold_frame_count >= 8) {
        if (((Hero *)g_hero_state)->state != 0x6F && !func_PAL_L00_002D6E48() && ((Hero *)g_hero_state)->mode != 2 && ((Hero *)g_hero_state)->state != 0x31 && blocked
            && ((Hero *)g_hero_state)->state != 0x1C && !g_game_l00_mode && g_hero_scalar_transition_value < 0.2f
            && ((Hero *)g_hero_state)->f22B4 < 2 && !g_input_block_flag && g_language_settings[3]) {
            hud_request_open();
            if (hud_is_open_done()) {
                if (((Hero *)g_hero_state)->f22B4 != 1)
                    func_PAL_L00_002CB5E8();
                if (!request_begin_slot(4, 1, 7, 0, 0))
                    return;
            }
        }
    }

    if (!level_is_counter_positive()) {
        if ((((PadState *)g_pad_state)->pressed & 0x800) || g_pad_device_idle_flag) {
            if (g_pad_hold_frame_count < 8)
                goto normal;
            if (((Hero *)g_hero_state)->state != 0x6F && !func_PAL_L00_002D6E48()
                && (((Hero *)g_hero_state)->mode != 2 || ((Hero *)g_hero_state)->submode == 10)) {
                if (!blocked || g_game_l00_mode)
                    goto second;
                if (!request_begin_slot(3, 1, 1, 0, 0)) {
                    level_set_global_setting_value(level_get_setting_value() != 0);
                    snd_play_from_global_bank(18, 0, 0);
                    return;
                }
            }
        }
    }
second:
    if (g_pad_hold_frame_count >= 8 && (((PadState *)g_pad_state)->pressed & 0x500)) {
        if (((Hero *)g_hero_state)->f229C != 22 && ((Hero *)g_hero_state)->state != 0x6F && !func_PAL_L00_002D6E48() && blocked
            && ((Hero *)g_hero_state)->state != 0x1C
            && !g_game_l00_mode) {
            if (level_is_mode_in_set()) {
                if (level_run_mode_update_zero())
                    goto normal;
            }
            if (g_hero_locked_flag && !g_hero_action_blocked_flag) {
                if ((g_current_map_index == 26 || (((Hero *)g_hero_state)->state != 0x5B && ((Hero *)g_hero_state)->state != 0x58))
                    && request_begin_slot(4, 1, 6, 0, 0)) {
                    if (g_progress_statistics[35].count < 0xFFFF)
                        g_progress_statistics[35].count++;
                }
                if (g_progress_statistics[35].maximum < ((s32)g_frame_counter * 5 + 2) / 6)
                    g_progress_statistics[35].maximum = ((s32)g_frame_counter * 5 + 2) / 6;
                g_progress_statistics[35].levels = (g_progress_statistics[35].levels | (1 << g_current_map_index)) | 0x80000000;
                return;
            }
            if (!request_begin_slot(3, 1, 2, 0, 0)) {
                level_set_global_setting_value(level_get_setting_value() != 0);
                if (g_progress_statistics[9].count < 0xFFFF)
                    g_progress_statistics[9].count++;
                if (g_progress_statistics[9].maximum < ((s32)g_frame_counter * 5 + 2) / 6)
                    g_progress_statistics[9].maximum = ((s32)g_frame_counter * 5 + 2) / 6;
                g_progress_statistics[9].levels = (g_progress_statistics[9].levels | (1 << g_current_map_index)) | 0x80000000;
            }
            return;
        }
    }
normal:
    if (((Hero *)g_hero_state)->state != 0x1C)
        hero_update_hit_streak_effect();
    if (((PadState *)g_pad_state)->pressed & 0x200) {
        if (((Hero *)g_hero_state)->state != 0x1C && ((Hero *)g_hero_state)->state != 0x31) {
            module_l00_call_handler_with_arg_4_pal(((s32)(360) * 5 + 2) / 6);
            func_L00_0030C710(((s32)(180) * 5 + 2) / 6);
        }
    }
    if (g_pickup_request_pending && !request_begin_slot(6, 1, 0, 0, 0)) {
        level_set_global_setting_value(level_get_setting_value() != 0);
        g_pickup_request_pending = 0;
    } else {
        game_reset_frame_counters();
        level_run_per_frame_passes();
        level_count_active_records();
        moby_update_visible_objects();
        snd_run_callbacks();
        hero_l00_update_frame_2_pal();
        part_update_all();
        part_l00_update_effect_slots_pal();
        cam_update_state_pal();
        UpdateSoundVoices_pal();
        UpdateLightingEnvironment();
        gfx_compute_light_direction();
        hud_update_record_timers_pal(1);
        level_run_callbacks();
        func_PAL_00289AA8();
        game_update_idle_frame_counters_pal();
    }
}
