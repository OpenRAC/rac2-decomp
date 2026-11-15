#include "common.h"

typedef struct { char pad[0x14]; int name; char pad18[0x70]; unsigned short valid; char pad8a[4]; unsigned short ammo; char pad90[0x50]; } Info;
typedef struct { char pad[0x148]; float x, y; char pad150[0x70]; int held, pressed, pad1c8, inhibit, pad1d0, pad1d4, repeat; } Controller;
typedef struct { char pad[0xf0]; unsigned short uses; char padf2[2]; unsigned int maxFrame, levels; } Stats;
typedef struct { char pad[0x1248]; int selected; char pad124c[0x107c]; int pending; } Hero;
typedef struct { int f0; int f4; int f8; int fC; int f10; int f14; int f18; } Slot;
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

extern int g_notice_owner;
extern unsigned char D_001A7BB0[] __attribute__((sda));
#define D_001A7BB3 D_001A7BB0[3]
extern int D_001A8CFC;
extern int D_001A8D30 __attribute__((sda));
extern int g_radial_menu_page_index __attribute__((sda));
extern int D_001A8D90[] __attribute__((sda));
extern int g_radial_slot_count;
extern Slot **g_radial_menu_pages;
extern float D_001A8E10;
extern int D_001B1900;
extern int D_001B18FC;
extern int D_001B1598, D_001B18F8;
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
extern Info g_weapon_table[];
extern Controller g_pad_state;
extern char D_0018C316[];
extern char D_001A8E18[];
extern Stats g_progress_statistics;
extern Hero g_hero_state;
extern unsigned int D_001A7390;
extern int g_current_map_index;
extern short D_001A63AC NOT_SDA;
extern int menu_is_state_seven(void), hud_is_open_done(void);
extern void hud_request_open(void), menu_set_state_word_three(void);
extern void menu_set_screen_value_restart_six_fades(void *, int);
extern int FastDecTimer(void *);
extern float square_root(float), mat_fast_helper_a(float, float), IntToFloat(int), fast_subtract_rotations(float, float), FastDiffRots(float, float), math_fast_float_g(float);
extern int FloatToInt(float);
extern void STUB_printf(void *), load_request_disc_read_break(void), snd_play_from_global_bank(int, int, int);
extern int load_is_class_cached(int);
extern void LoadClassIntoFreeCacheSlot(int), menu_advance_state_in_mode_seven(void), hud_clear_flag_b(void), hud_clear_flag_a(void);
extern int hud_close_element_by_key(int);

static inline Info *InfoOf(int id)
{
    return &g_weapon_table[g_item_slot_to_record[id]];
}

/* Updates the round weapon-select menu: reads the stick, picks a slot, plays the click sound and equips the chosen weapon when the button is let go. */
void weapon_wheel_update_select(Selector *selector)
{
    float stick_x, stick_y, stick_magnitude, stick_angle, shifted_angle, slot_position, old_slot_angle;
    int old_selection, nudge, slot, next_slot, weapon_id;
    int active;
    unsigned char *fade, *fade_start;

    if (g_notice_owner) return;
    active = 0;
    if (!D_001A7BB3 || menu_is_state_seven() || !D_001A7BB3) {
        active = 1;
        if (!D_001A7BB3) {
            hud_request_open();
            if (!hud_is_open_done()) active = 0;
        }
    }
    fade_start = selector->fade;
    if (active && D_001A8CFC) {
        menu_set_screen_value_restart_six_fades((char *)D_001A8CFC + 0x376C8, menu_is_state_seven() ? D_001A8D30 : 2);
        menu_set_state_word_three();
    }
    selector->timeout = 180;
    selector->timer = 24;
    if (FastDecTimer(D_0018C316) && !D_001A7BB3) g_pad_state.inhibit = 2;
    stick_x = g_pad_state.x;
    stick_y = g_pad_state.y;
    stick_magnitude = square_root(stick_x * stick_x + stick_y * stick_y);
    if (stick_magnitude != 0.0f) {
        stick_x /= stick_magnitude;
        stick_y /= stick_magnitude;
    }
    stick_angle = mat_fast_helper_a(stick_x, stick_y);
    if ((selector->state >> 24) == 0) {
        if ((g_pad_state.pressed & 0xF000) || stick_magnitude < 0.5f || --selector->state == -1) {
            selector->selected = -1;
            selector->state = 0x10000FF;
        }
    }
    nudge = 0;
    old_selection = selector->selected;
    if ((selector->state >> 24) == 1 && (g_pad_state.held & 0x10) && active) {
        if (stick_magnitude > 0.9f) {
            shifted_angle = stick_angle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)g_radial_slot_count;
            slot_position = shifted_angle * 0.15915494f * (float)g_radial_slot_count;
            old_slot_angle = (float)old_selection * 6.2831855f / IntToFloat(g_radial_slot_count) - 3.1415927f;
            if (old_selection == -1 || FastDiffRots(old_slot_angle, fast_subtract_rotations(stick_angle, 1.5707964f)) > 0.5890487f) {
                slot = (int)slot_position % g_radial_slot_count;
                if ((slot ^ 1) & 1) {
                    float fraction = slot_position - (float)FloatToInt(slot_position);
                    if (fraction > 0.8f) slot++;
                    else if (fraction < 0.2f) slot--;
                    slot = (slot + g_radial_slot_count) % g_radial_slot_count;
                }
                selector->selected = slot;
                nudge = -1;
                D_001A8E10 = math_fast_float_g(shifted_angle - ((float)slot * 0.78539824f + 0.39269912f));
                if (D_001A8E10 > 0.0f) nudge = 1;
            }
        } else if (g_pad_state.repeat == 0 && (g_pad_state.pressed & 0xF000)) {
            int wanted;
            wanted = old_selection;
            if (g_pad_state.pressed & 0x1000) {
                int target;
                if (wanted == -1) target = D_001A8D90[4];
                else target = g_radial_menu_pages[g_radial_menu_page_index][wanted].f10;
                wanted = target;
            }
            if (g_pad_state.pressed & 0x4000) {
                int target;
                if (wanted == -1) target = D_001A8D90[5];
                else target = g_radial_menu_pages[g_radial_menu_page_index][wanted].f14;
                wanted = target;
            }
            if (g_pad_state.pressed & 0x8000) {
                int target;
                if (wanted == -1) target = D_001A8D90[2];
                else target = g_radial_menu_pages[g_radial_menu_page_index][wanted].f8;
                wanted = target;
            }
            if (g_pad_state.pressed & 0x2000) {
                int target;
                if (wanted == -1) target = D_001A8D90[3];
                else target = g_radial_menu_pages[g_radial_menu_page_index][wanted].fC;
                wanted = target;
            }
            selector->selected = wanted;
        }
        {
            Slot *target = g_radial_menu_pages[g_radial_menu_page_index];
            int current = selector->selected;
            if (target[current].f0 == 0 && nudge != 0) {
                next_slot = (current + nudge) % g_radial_slot_count;
                if (target[next_slot].f0 != 0) selector->selected = next_slot;
            }
        }
    }
    fade = selector->fade;
    if (selector->selected != old_selection) {
        STUB_printf(D_001A8E18);
        load_request_disc_read_break();
        fade[1] = 0;
        snd_play_from_global_bank(3, 0, 0);
    } else if (fade[1] < 8) fade[1]++;
    if (selector->selected >= 0 && !load_is_class_cached(InfoOf(g_radial_menu_pages[g_radial_menu_page_index][selector->selected].f18)->name)) {
        LoadClassIntoFreeCacheSlot(InfoOf(g_radial_menu_pages[g_radial_menu_page_index][selector->selected].f18)->name);
    } else {
        if (!(g_pad_state.held & 0x10) && !D_001A63AC) {
            if (fade[0]) fade[0]--;
            if (fade[0] == 0 && selector->selected >= 0 && (weapon_id = g_radial_menu_pages[g_radial_menu_page_index][selector->selected].f18) != 0) {
                Info *info;
                if (g_hero_state.selected != weapon_id && g_progress_statistics.uses < 0xFFFF) g_progress_statistics.uses++;
                if (g_progress_statistics.maxFrame < D_001A7390) g_progress_statistics.maxFrame = D_001A7390;
                g_progress_statistics.levels = g_progress_statistics.levels | (1 << g_current_map_index) | 0x80000000;
                g_hero_state.pending = weapon_id;
                info = InfoOf(weapon_id);
                if (info->valid && info->ammo < g_item_ammo_counts[weapon_id]) g_item_ammo_counts[weapon_id] = info->ammo;
            }
            if (D_001A7BB3) menu_advance_state_in_mode_seven();
            else {
                hud_clear_flag_b();
                hud_clear_flag_a();
            }
        } else if (fade[0] < 8) fade[0]++;
    }
    if (fade_start[0] == 0) {
        {
            int state = selector->state;
            D_001B1900 = selector->selected;
            D_001B18FC = state;
        }
        hud_close_element_by_key(selector->handle);
        selector->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
