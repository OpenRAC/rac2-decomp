#include "names.h"
/* func_PAL_0028D738, the PAL copy of func_0028CCE0: the same C, where rename func_002A9588 becomes func_PAL_002A9FA0. */
#include "common.h"

extern void menu_set_state_word_three(void);
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern int math_ping_pong_blend_values_pal(int, int, int, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void menu_advance_state_in_mode_seven(void);
extern int hud_close_element_by_key(int);
typedef struct { char pad0[0x148]; float x, y; char pad150[0x70]; int held, pressed, released, mode; } RadialInput;
extern RadialInput g_pad_state;
typedef struct { char pad0[0x24E4]; int choice; } RadialState;
extern RadialState g_hero_state;
extern short g_weapon_wheel_slot_state, g_weapon_wheel_slot_six, g_weapon_wheel_slot_five, g_weapon_wheel_slot_seven;
extern int g_radial_slot_count __attribute__((sda));
extern int g_radial_menu_page_index;
extern int **g_radial_menu_pages;
extern int g_radial_default_choices[] __attribute__((sda));
extern unsigned char g_weapon_wheel_enabled;
extern int g_weapon_wheel_state, g_weapon_wheel_open_frame, g_frame_counter_3;
extern int g_weapon_wheel_selected __attribute__((sda));
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

/* Updates the simple round weapon-select menu: reads the stick, picks a slot and closes the menu when the button is let go (PAL: timeout 150). */
void UpdateRadialMenuSelection_pal(Selector *selector)
{
    float stick_x, stick_y, stick_magnitude, stick_angle;
    int old_selection, choice;
    unsigned char *fade = selector->fade;
    menu_set_state_word_three();
    selector->timeout = 150;
    selector->timer = 24;
    g_pad_state.mode = 2;
    stick_x = g_pad_state.x;
    stick_y = g_pad_state.y;
    stick_magnitude = square_root(stick_x * stick_x + stick_y * stick_y);
    if (stick_magnitude != 0.0f) {
        stick_x /= stick_magnitude;
        stick_y /= stick_magnitude;
    }
    stick_angle = mat_fast_helper_a(stick_x, stick_y);
    if ((selector->state >> 24) == 0 && g_weapon_wheel_slot_state) {
        if (g_pad_state.pressed & 0xF000) goto reset_selection;
        if (stick_magnitude < 0.5f) goto reset_selection;
        --selector->state;
        if (selector->state == -1) {
reset_selection:
            selector->selected = -1;
            selector->state = 0x10000FF;
        }
    }
    old_selection = selector->selected;
    if ((selector->state >> 24) == 1) {
        if (stick_magnitude > 0.0f) {
            if (stick_magnitude > 0.9f) {
                float slot_position;
                slot_position = stick_angle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)g_radial_slot_count;
                slot_position = slot_position * 0.15915494f * (float)g_radial_slot_count;
                selector->selected = (int)slot_position % g_radial_slot_count;
            }
        } else if (g_pad_state.pressed & 0xF000) {
            choice = old_selection;
            if (g_pad_state.pressed & 0x1000) {
                choice = choice == -1 ? g_radial_default_choices[4] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 4];
            }
            if (g_pad_state.pressed & 0x4000) {
                choice = choice == -1 ? g_radial_default_choices[5] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 5];
            }
            if (g_pad_state.pressed & 0x8000) {
                choice = choice == -1 ? g_radial_default_choices[2] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 2];
            }
            if (g_pad_state.pressed & 0x2000) {
                choice = choice == -1 ? g_radial_default_choices[3] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 3];
            }
            selector->selected = choice;
        }
    }
    if (selector->selected != old_selection) {
        math_ping_pong_blend_values_pal(0, 0, 1, 0, 1);
        fade[1] = 0;
        snd_play_from_global_bank(3, 0, 0);
    } else if (fade[1] < 8) ++fade[1];
    if (!(g_pad_state.held & 0x10)) {
        if (g_pad_state.released & 0x10) {
            int current = selector->selected;
            if (current == -1) g_hero_state.choice = 0;
            else g_hero_state.choice = g_radial_menu_pages[g_radial_menu_page_index][current * 7 + 6];
        }
        if (g_weapon_wheel_enabled) menu_advance_state_in_mode_seven();
        if (*fade) --*fade;
    } else if (*fade < 8) ++*fade;
    if (g_hero_state.choice == 6 && !g_weapon_wheel_slot_six)
        g_hero_state.choice = 0;
    if (g_hero_state.choice == 7 && !g_weapon_wheel_slot_seven)
        g_hero_state.choice = 0;
    if (g_hero_state.choice == 5 && !g_weapon_wheel_slot_five)
        g_hero_state.choice = 0;
    if (!*fade) {
        g_weapon_wheel_selected = selector->selected;
        g_weapon_wheel_state = selector->state;
        hud_close_element_by_key(selector->handle);
        selector->timer = -6;
        g_weapon_wheel_open_frame = g_frame_counter_3;
    }
}
