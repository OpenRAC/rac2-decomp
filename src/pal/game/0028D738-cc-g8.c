#include "names.h"
/* func_PAL_0028D738, the PAL copy of func_0028CCE0: the same C, where rename func_002A9588 becomes func_PAL_002A9FA0. */
#include "common.h"

extern void menu_set_state_word_three(void);
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern int func_PAL_002A9FA0(int, int, int, int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern void menu_advance_state_in_mode_seven(void);
extern int hud_close_element_by_key(int);
typedef struct { char pad0[0x148]; float x, y; char pad150[0x70]; int held, pressed, released, mode; } RadialInput;
extern RadialInput g_pad_state;
typedef struct { char pad0[0x24E4]; int choice; } RadialState;
extern RadialState g_hero_state;
extern short D_001B189C, D_001B18A0, D_001B18A2, D_001B18A4;
extern int g_radial_slot_count __attribute__((sda));
extern int g_radial_menu_page_index;
extern int **g_radial_menu_pages;
extern int D_001A8DB0[] __attribute__((sda));
extern unsigned char D_001A7BB3;
extern int D_001B18FC, D_001B18F8, D_001B1598;
extern int D_001B1900 __attribute__((sda));
typedef struct { char pad[0x64]; int handle; char pad68[4]; int timer; unsigned char fade[4]; int selected, state, timeout; } Selector;

void func_PAL_0028D738(Selector *object)
{
    float x, y, magnitude, angle;
    int old, choice;
    unsigned char *fade = object->fade;
    menu_set_state_word_three();
    object->timeout = 150;
    object->timer = 24;
    g_pad_state.mode = 2;
    x = g_pad_state.x;
    y = g_pad_state.y;
    magnitude = square_root(x * x + y * y);
    if (magnitude != 0.0f) {
        x /= magnitude;
        y /= magnitude;
    }
    angle = mat_fast_helper_a(x, y);
    if ((object->state >> 24) == 0 && D_001B189C) {
        if (g_pad_state.pressed & 0xF000) goto reset_selection;
        if (magnitude < 0.5f) goto reset_selection;
        --object->state;
        if (object->state == -1) {
reset_selection:
            object->selected = -1;
            object->state = 0x10000FF;
        }
    }
    old = object->selected;
    if ((object->state >> 24) == 1) {
        if (magnitude > 0.0f) {
            if (magnitude > 0.9f) {
                float a;
                a = angle + 3.1415927f + 3.1415927f + 1.5707964f + 3.1415927f / (float)g_radial_slot_count;
                a = a * 0.15915494f * (float)g_radial_slot_count;
                object->selected = (int)a % g_radial_slot_count;
            }
        } else if (g_pad_state.pressed & 0xF000) {
            choice = old;
            if (g_pad_state.pressed & 0x1000) {
                choice = choice == -1 ? D_001A8DB0[4] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 4];
            }
            if (g_pad_state.pressed & 0x4000) {
                choice = choice == -1 ? D_001A8DB0[5] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 5];
            }
            if (g_pad_state.pressed & 0x8000) {
                choice = choice == -1 ? D_001A8DB0[2] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 2];
            }
            if (g_pad_state.pressed & 0x2000) {
                choice = choice == -1 ? D_001A8DB0[3] : g_radial_menu_pages[g_radial_menu_page_index][choice * 7 + 3];
            }
            object->selected = choice;
        }
    }
    if (object->selected != old) {
        func_PAL_002A9FA0(0, 0, 1, 0, 1);
        fade[1] = 0;
        snd_play_from_global_bank(3, 0, 0);
    } else if (fade[1] < 8) ++fade[1];
    if (!(g_pad_state.held & 0x10)) {
        if (g_pad_state.released & 0x10) {
            int current = object->selected;
            if (current == -1) g_hero_state.choice = 0;
            else g_hero_state.choice = g_radial_menu_pages[g_radial_menu_page_index][current * 7 + 6];
        }
        if (D_001A7BB3) menu_advance_state_in_mode_seven();
        if (*fade) --*fade;
    } else if (*fade < 8) ++*fade;
    if (g_hero_state.choice == 6 && !D_001B18A0)
        g_hero_state.choice = 0;
    if (g_hero_state.choice == 7 && !D_001B18A4)
        g_hero_state.choice = 0;
    if (g_hero_state.choice == 5 && !D_001B18A2)
        g_hero_state.choice = 0;
    if (!*fade) {
        D_001B1900 = object->selected;
        D_001B18FC = object->state;
        hud_close_element_by_key(object->handle);
        object->timer = -6;
        D_001B18F8 = D_001B1598;
    }
}
