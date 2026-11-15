/* func_US2_L00_003706F0, the USA v2.00 copy of func_L00_0036F488: the same C, with a second gate
 * after the first (func_US2_L00_0030AF78, func_US2_00299980), D_001A7424's mask 1 becoming 0x600, and
 * func_US2_L00_002D6C98 added to the three hero-state tests; three callees are v2.00's own. */
#include "common.h"

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

extern Hero g_hero_state;
extern PadState g_pad_state;

extern int D_L00_001A8F00 MACRO_ADDR;
extern int D_L00_001A8FB8 MACRO_ADDR;
extern int D_L00_001A8FF0 MACRO_ADDR;
extern int D_001A7428 MACRO_ADDR;
extern int D_L00_001B19C4 MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern u32 D_001A7390 MACRO_ADDR;
extern int D_L00_001B1AE0 MACRO_ADDR;
extern Statistics g_progress_statistics[];
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int g_save_menu_flags __attribute__((sda));
extern int D_L00_001A8FB4 __attribute__((sda));
extern int D_L00_001A8FF4 __attribute__((sda));
extern float D_L00_001B18E0 __attribute__((sda));

extern int level_get_flag_b(void);
extern int request_begin_slot(int, int, int, int, int);
/* The neighbouring stub in most programs; another function in six of them. */
extern unsigned int ref_L00_0036F488_00(void);
extern int level_is_mode_in_set(void);
extern int func_US2_L00_0030AF78(void);
extern int func_US2_00299980(void);
extern int func_US2_L00_002D6C98(void);
extern int level_run_mode_update_zero(void);
extern int level_is_tracked_object_of_selected_class(int);
extern int level_is_special_mode_active(void);
extern void level_update_countdown_state_machine(void);
extern int PadPressedWithin(int, int, int *);
extern void hud_request_open(void);
extern int hud_is_open_done(void);
extern void hero_update_button_hold_timers(void);
extern int level_is_counter_positive(void);
extern int level_get_setting_value(void);
extern void level_set_global_setting_value(int);
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void hero_update_hit_streak_effect(void);
extern void func_US2_L00_0030D9F8(int);
extern void func_L00_0030C710(int);
extern void game_reset_frame_counters(void);
extern void level_run_per_frame_passes(void);
extern void level_count_active_records(void);
extern void moby_update_visible_objects(void);
extern void snd_run_callbacks(void);
extern void func_US2_L00_002A6DD0(void);
extern void part_update_all(void);
extern void part_l00_update_effect_slots(void);
extern void cam_update_state(void);
extern void UpdateSoundVoices(void);
extern void UpdateLightingEnvironment(void);
extern void gfx_compute_light_direction(void);
extern void hud_update_record_timers(int);
extern void func_US2_0029CA98(void);
extern void subtitle_update_state_machine(void);
extern void game_update_idle_frame_counters(void);

void func_US2_L00_003706F0(void)
{
    int blocked;
    int special;

    if (level_get_flag_b() && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (func_US2_L00_0030AF78() && !D_L00_001A8F00 && (g_save_menu_flags & 0x600)
        && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (func_US2_00299980() && !D_L00_001A8F00 && func_US2_L00_0030AF78()
        && !request_begin_slot(4, 1, 1, 0, 0))
        return;
    if (ref_L00_0036F488_00())
        return;

    special = 0;
    blocked = g_hero_state.state != 0x31;
    if (g_hero_state.object) {
        int id = g_hero_state.object->id;
        if (id == 0x905 || id == 0x85C || id == 0xEEF || id == 0x10EE)
            special = 1;
    }
    blocked |= special;
    blocked = (blocked != 0);
    blocked |= level_is_mode_in_set() != 0;
    blocked |= level_is_tracked_object_of_selected_class(3) != 0;
    blocked |= level_is_special_mode_active() != 0;
    level_update_countdown_state_machine();

    if (PadPressedWithin(16, D_L00_001A8FB8, 0) && D_L00_001B19C4 >= 8) {
        if (g_hero_state.state != 0x6F && !func_US2_L00_002D6C98() && g_hero_state.mode != 2
            && g_hero_state.state != 0x31 && blocked && g_hero_state.state != 0x1C && !D_L00_001A8F00
            && D_L00_001B18E0 < 0.2f && g_hero_state.f22B4 < 2 && !D_L00_001A8FB4 && D_001A7BB0[3]) {
            hud_request_open();
            if (hud_is_open_done()) {
                if (g_hero_state.f22B4 != 1)
                    hero_update_button_hold_timers();
                if (!request_begin_slot(4, 1, 7, 0, 0))
                    return;
            }
        }
    }

    if (!level_is_counter_positive()) {
        if ((g_pad_state.pressed & 0x800) || D_001A7428) {
            if (D_L00_001B19C4 < 8)
                goto normal;
            if (g_hero_state.state != 0x6F && !func_US2_L00_002D6C98()
                && (g_hero_state.mode != 2 || g_hero_state.submode == 10)) {
                if (!blocked || D_L00_001A8F00)
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
    if (D_L00_001B19C4 >= 8 && (g_pad_state.pressed & 0x500)) {
        if (g_hero_state.f229C != 22 && g_hero_state.state != 0x6F && !func_US2_L00_002D6C98()
            && blocked && g_hero_state.state != 0x1C
            && !D_L00_001A8F00) {
            if (level_is_mode_in_set()) {
                if (level_run_mode_update_zero())
                    goto normal;
            }
            if (D_L00_001A8FF0 && !D_L00_001A8FF4) {
                if ((g_current_map_index == 26 || (g_hero_state.state != 0x5B && g_hero_state.state != 0x58))
                    && request_begin_slot(4, 1, 6, 0, 0)) {
                    if (g_progress_statistics[35].count < 0xFFFF)
                        g_progress_statistics[35].count++;
                }
                if (g_progress_statistics[35].maximum < D_001A7390)
                    g_progress_statistics[35].maximum = D_001A7390;
                g_progress_statistics[35].levels = (g_progress_statistics[35].levels | (1 << g_current_map_index)) | 0x80000000;
                return;
            }
            if (!request_begin_slot(3, 1, 2, 0, 0)) {
                level_set_global_setting_value(level_get_setting_value() != 0);
                if (g_progress_statistics[9].count < 0xFFFF)
                    g_progress_statistics[9].count++;
                {
                    u32 tick = D_001A7390;
                    if (g_progress_statistics[9].maximum < tick)
                        g_progress_statistics[9].maximum = tick;
                }
                g_progress_statistics[9].levels = (g_progress_statistics[9].levels | (1 << g_current_map_index)) | 0x80000000;
            }
            return;
        }
    }
normal:
    if (g_hero_state.state != 0x1C)
        hero_update_hit_streak_effect();
    if (g_pad_state.pressed & 0x200) {
        if (g_hero_state.state != 0x1C && g_hero_state.state != 0x31) {
            func_US2_L00_0030D9F8(360);
            func_L00_0030C710(180);
        }
    }
    if (D_L00_001B1AE0 && !request_begin_slot(6, 1, 0, 0, 0)) {
        level_set_global_setting_value(level_get_setting_value() != 0);
        D_L00_001B1AE0 = 0;
    } else {
        game_reset_frame_counters();
        level_run_per_frame_passes();
        level_count_active_records();
        moby_update_visible_objects();
        snd_run_callbacks();
        func_US2_L00_002A6DD0();
        part_update_all();
        part_l00_update_effect_slots();
        cam_update_state();
        UpdateSoundVoices();
        UpdateLightingEnvironment();
        gfx_compute_light_direction();
        hud_update_record_timers(1);
        func_US2_0029CA98();
        subtitle_update_state_machine();
        game_update_idle_frame_counters();
    }
}
