#include "include_asm.h"
#include "names.h"

#ifndef RAC2_T_F32_F7036EF03
#define RAC2_T_F32_F7036EF03
typedef float f32_F7036ef03;
#endif

extern f32_F7036ef03 D_L04_001AE4A8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4B0 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4B8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4C0 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4C8 __attribute__((sda));

extern f32_F7036ef03 D_L04_001AE4AC;

extern f32_F7036ef03 D_L04_001AE4B4;

extern f32_F7036ef03 D_L04_001AE4BC;

extern f32_F7036ef03 D_L04_001AE4C4;

extern f32_F7036ef03 D_L04_001AE4CC;

extern void func_00335E38_2(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2, f32_F7036ef03 a3, f32_F7036ef03 a4);

extern void stub_store_two_floats(void *a0, f32_F7036ef03 a1, f32_F7036ef03 a2);

extern void menu_update_title_text(void *a0);

extern void menu_update_empty_label(void *a0);

extern int UpdateListSelection(void *a0, int a1);

/* Moves every part of the item menu to its place, refreshes the labels and updates the list. */
void item_menu_update(char *self, int buttons)
{
    f32_F7036ef03 *position;
    char *list = self + 664;

    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self, D_L04_001AE4A8 + position[0], D_L04_001AE4AC + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 76, D_L04_001AE4B0 + position[0], D_L04_001AE4B4 + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 152, D_L04_001AE4B8 + position[0], D_L04_001AE4BC + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    func_00335E38_2(self + 576, D_L04_001AE4C0 + position[0], D_L04_001AE4C4 + position[1], 0.0f, 0.0f);
    position = *(f32_F7036ef03 **)(self + 648);
    stub_store_two_floats(list, D_L04_001AE4C8 + position[0], D_L04_001AE4CC + position[1]);
    menu_update_title_text(self);
    menu_update_empty_label(self);
    *(int *)(self + 416) = UpdateListSelection(list, buttons);
}


extern void gfx_draw_screen_element_stored(void *a0);
extern void text_label_draw(void *a0);
extern void menu_list_draw_entries(void *a0);
extern int menu_list_get_selected_id(void *a0);
extern int GetLocalizedString(int);
extern void hud_set_widget_field_b(void *a0, int a1);
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];

/* Draws the item menu: its frame, list, and the description of the selected item. */
void item_menu_draw(char *self)
{
    int itemId;
    char *itemRecord;

    if (*(int *)(self + 0x290) != 0) {
        gfx_draw_screen_element_stored(self);
        gfx_draw_screen_element_stored(self + 0x4C);
        gfx_draw_screen_element_stored(self + 0x98);
        text_label_draw(self + 0x1B0);
        menu_list_draw_entries(self + 0x298);
        itemId = menu_list_get_selected_id(self + 0x298);
        itemRecord = g_weapon_table + g_item_slot_to_record[itemId] * 224;
        hud_set_widget_field_b(self + 0x1F8, GetLocalizedString(*(int *)(itemRecord + 8)));
        text_label_draw(self + 0x1F8);
        text_label_draw(self + 0x240);
    }
}
