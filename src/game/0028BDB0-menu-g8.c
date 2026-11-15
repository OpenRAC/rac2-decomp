#include "common.h"

extern int D_001A8FBC SDATA(D_001A8FBC);
extern unsigned char g_item_slot_to_record[];
extern int g_item_ammo_counts[];
typedef struct { int active; unsigned char pad04[0x38]; unsigned short label; unsigned char pad3E[0x50]; unsigned short value; unsigned char pad90[0x50]; } MapClass;
extern MapClass g_weapon_table[];
extern unsigned char g_hero_state[];
typedef struct { int active; int selected; int handle; int busy; } MapMenuGlobals;
extern MapMenuGlobals D_001A8FB0 MACRO_ADDR;
extern int D_001A8FB0_gp SDATA(D_001A8FB0);
extern int gauge_update_fade_counters(char *);
extern int menu_draw_progress_bar_panel(char *);
extern int weapon_get_usable_selected(void);
extern int hud_set_slot_contents(int, int, void *, void *, void *, int, int);
extern void set_animation_parameter(int, int);
extern void menu_init_small_panel(char *);
extern int hud_return_zero(void);
extern void hud_init_counter_element(void *);
extern void hud_update_counter_element(void *);

/* Opens the weapon menu entry for the selected weapon, or closes the open entry when none is chosen. */
void weapon_menu_update_entry(void)
{
    int selected;
    unsigned char *state;
    MapClass *record;
    int isActive;
    unsigned short label;
    unsigned char *lookup;

    if (D_001A8FBC != 0) return;
    if (D_001A8FB0_gp != 0) return;
    selected = weapon_get_usable_selected();
    lookup = g_item_slot_to_record + selected;
    record = (MapClass *)(*lookup * 0xE0 + (unsigned int)g_weapon_table);
    label = record->label;
    isActive = record->active;
    if (selected != 0 && isActive != 0) {
        D_001A8FB0.selected = selected;
        D_001A8FB0.handle = hud_set_slot_contents(0x10, label,
            menu_init_small_panel, gauge_update_fade_counters, hud_return_zero,
            (int)&g_item_ammo_counts[selected],
            ((MapClass *)(*lookup * 0xE0 + (unsigned int)g_weapon_table))->value);
        return;
    }
    state = g_hero_state;
    if (state[0x22B4] == 2) {
        if (D_001A8FB0.handle != -1) {
            set_animation_parameter(D_001A8FB0.handle, 0);
            D_001A8FB0.handle = -1;
        }
        *(unsigned short *)(state + 0x1878) = hud_set_slot_contents(0x10, 0xFFFF,
            hud_init_counter_element, hud_update_counter_element, menu_draw_progress_bar_panel, (int)(state + 0x1874), 0xC8);
    } else if (D_001A8FB0.handle != -1) {
        set_animation_parameter(D_001A8FB0.handle, 0);
        D_001A8FB0.handle = -1;
    }
}
