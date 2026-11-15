#include "include_asm.h"
#include "names.h"

extern float D_001AE0E0 __attribute__((sda));
extern float D_001AE0DC;
extern float D_001AE0D8 __attribute__((sda));
extern void object_set_first_float4(void *, float, float, float, float);

/* Moves the tab cursor to the spot for the selected tab. */
void tab_menu_position_cursor(char *self)
{
    int index = *(int *)(self + 0x2FC);
    float *position = *(float **)(self + 0x218);
    int *base = (int *)(self + (index << 2));

    object_set_first_float4(self + 0x130, D_001AE0D8 + position[0],
            (D_001AE0DC + D_001AE0E0 * (float)base[0x6E]) + position[1],
            0.0f, 0.0f);
}

extern float D_001AE0E8 __attribute__((sda));
extern float D_001AE0EC;
extern float D_001AE0F0 __attribute__((sda));
extern float D_001AE0F4 __attribute__((sda));
extern void menu_set_position(void *, float, float);
extern void menu_set_settings(void *, int, int);
extern void *UpdateMenuListSelection(void *, int);
extern int menu_get_selected_index(void *);
extern int math_ping_pong_blend_values(int, int, int, int, int);
/* Updates the scrolling list of the selected tab and plays a sound when the choice changes. */
void tab_menu_update_list(char *self, int arg)
{
    char *indices = self + 0x1B8;
    char *child = self + 0x228;
    int old;
    float *position = *(float **)(self + 0x218);
    menu_set_position(child, position[0] + D_001AE0E8, position[1] + D_001AE0EC);
    menu_set_settings(child, (int)D_001AE0F0, (int)D_001AE0F4);
    UpdateMenuListSelection(child, arg);
    old = *(int *)(indices + (*(int *)(self + 0x2FC) << 2));
    *(int *)(indices + (*(int *)(self + 0x2FC) << 2)) = menu_get_selected_index(child);
    indices += *(int *)(self + 0x2FC) << 2;
    if (old != *(int *)indices)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
}

/* func_00341610 -- the object's index picks one of three per-index records.
   The first table is in the program's small data (reached through $gp), the
   second one in the program's data segment; both move with the program, so
   both are externs.  The retail's guard is an UNSIGNED comparison (sltiu), so
   a negative index takes the early return as well. */
extern int D_001AE0C8 __attribute__((sda));
extern char D_002652F0[];
extern void menu_set_selected_index(void *, int);
extern void menu_set_entry_table(unsigned char *, float *);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, unsigned int);
extern void object_set_value_float(void *, float);

/* Switches the menu to one of its three tabs and sets up the text, icon and entries for it. */
void tab_menu_switch_tab(char *self, int idx)
{
    float *records;
    float scale;
    unsigned char *child;
    if ((unsigned int)idx > 2) return;
    *(int *)(self + 0x1C4) = ((int *)&D_001AE0C8)[idx];
    *(int *)(self + 0x1C8) = (int)(D_002652F0 + idx * 0x20);
    *(int *)(self + 0x1CC) = (idx == 0) ? 7 : ((idx == 1) ? 8 : 6);
    if (idx != 0) {
        if (idx == 2) scale = 2.0f;
        else scale = 1.0f;
    } else {
        scale = 0.0f;
    }
    child = (unsigned char *)self + 0x228;
    {
        int *p = (int *)(self + idx * 4);
        menu_set_selected_index(child, p[0x6E]);
    }
    records = (idx == 0) ? *(float **)(self + 0x2F0) : ((idx == 1) ? *(float **)(self + 0x2F4) : *(float **)(self + 0x2F8));
    menu_set_entry_table(child, records);
    hud_set_widget_field_b(self + 0x1D0, GetLocalizedString((idx == 0) ? 0x2D55 : ((idx == 1) ? 0x2D56 : 0x31FE)));
    object_set_value_float(self, scale);
    object_set_value_float(self + 0x4C, scale);
    object_set_value_float(self + 0xE4, scale);
    *(int *)(self + 0x2FC) = idx;
}
