#include "include_asm.h"
#include "names.h"
extern void gfx_draw_screen_element_stored(void *a0);
extern void text_label_draw(void *a0);
extern void menu_list_draw_entries(void *a0);
extern int menu_list_get_selected_id(void *a0);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *a0, int a1);
extern unsigned char g_item_slot_to_record[];
extern char g_weapon_table[];

/* Draws the item menu's parts, list and the name of the selected item when the menu is shown (PAL). */
void item_menu_draw_pal(char *self)
{
    int selected_id;
    char *rec;

    if (*(int *)(self + 0x2C0) != 0) {
        gfx_draw_screen_element_stored(self);
        gfx_draw_screen_element_stored(self + 0x4C);
        gfx_draw_screen_element_stored(self + 0x98);
        text_label_draw(self + 0x1B0);
        menu_list_draw_entries(self + 0x2C8);
        selected_id = menu_list_get_selected_id(self + 0x2C8);
        rec = g_weapon_table + g_item_slot_to_record[selected_id] * 224;
        hud_set_widget_field_b(self + 0x208, GetLocalizedString(*(int *)(rec + 8)));
        text_label_draw(self + 0x208);
        text_label_draw(self + 0x260);
    }
}
