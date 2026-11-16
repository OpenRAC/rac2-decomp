#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int menu_list_get_count(u8 *);
extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern float g_menu_empty_label_y_offset;
extern float g_menu_empty_label_x_offset __attribute__((sda));

/* Hides the menu's label when its list is empty, otherwise places it next to the menu. */
void menu_update_empty_label_pal(u8 *menu) {
    if (menu_list_get_count(menu + 0x2C8) == 0) {
        object_set_flag_value(menu + 0x208, 0);
    } else {
        int *position = *(int **)(menu + 0x2B8);
        object_set_first_float4(menu + 0x208, g_menu_empty_label_x_offset + *(float *)position,
                      g_menu_empty_label_y_offset + *(float *)((u8 *)position + 4), 0.0f, 0.0f);
    }
}
