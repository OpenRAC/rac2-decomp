#include "include_asm.h"
#include "common.h"
extern void *memset(s8 *, s32, s32);
extern char *GetLocalizedString(s32);
extern s32 *object_get_fourth_field(s8 *);
extern void object_set_second_float4(s8 *, f32, f32, f32, f32);
extern void object_init_derived_arrays(s8 *, s8 *, s8 *);
extern void object_set_helper_result(s8 *, s32, s32);
extern void object_set_value_float(s8 *, f32);
extern void object_init_derived_c(s8 *, s8 *, s8 *);
extern void hud_set_widget_value_pair(s8 *, s32, s32);
extern void hud_init_widget_defaults(s8 *, s8 *, s8 *);
extern void hud_set_widget_field_b(s8 *, s32);
extern s8 *ui_return_second_arg(s32, s32);
extern void *pool_alloc_cell(s8 *);
extern void list_menu_reset_attach_items(s8 *, s8 *);
extern s32 g_resident_data_base;
extern s8 g_menu_widget_desc_first[];
extern s8 g_menu_widget_desc_second[];
extern s8 g_menu_widget_desc_third[];
extern s8 g_menu_widget_desc_fourth[];
extern s8 g_menu_hud_label_desc[];
extern s8 g_menu_frame_desc[];
extern s8 g_menu_small_icon_desc[];

/* Sets up the widgets, position and colors of a tab menu (USA v2.00 layout). */
void tab_menu_init_us2(s8 *menu, s8 *owner) {
    s8 *position;
    s8 *widget_98;
    s8 *widget_4c;
    s8 *widget_e4;
    s8 *frame;
    s8 *icon;
    s8 *label;

    (*(s8 **)((s8 *)(menu) + (0x22C))) = owner;
    if (owner != 0) {
        position = ui_return_second_arg(0x10, pool_alloc_cell(owner));
        (*(s8 **)((s8 *)(menu) + (0x228))) = position;
        (*(s32 *)((s8 *)(position) + (4))) = 0;
        (*(s32 *)((s8 *)(position) + (8))) = 0;
        (*(s32 *)((s8 *)(position) + (0xC))) = 0;
        (*(s32 *)((s8 *)(position) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(menu) + (0x230))) = 1;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(menu) + (0x228)))) + (0))) = 251.0f;
    widget_98 = menu + 0x98;
    widget_4c = menu + 0x4C;
    widget_e4 = menu + 0xE4;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(menu) + (0x228)))) + (4))) = 170.0f;
    frame = menu + 0x130;
    object_init_derived_arrays(menu, g_menu_widget_desc_first, owner);
    icon = menu + 0x17C;
    label = menu + 0x1D0;
    object_init_derived_arrays(widget_98, g_menu_widget_desc_second, owner);
    object_init_derived_arrays(widget_4c, g_menu_widget_desc_third, owner);
    object_init_derived_arrays(widget_e4, g_menu_widget_desc_fourth, owner);
    object_init_derived_arrays(frame, g_menu_frame_desc, owner);
    hud_init_widget_defaults(label, g_menu_hud_label_desc, owner);
    object_init_derived_c(icon, g_menu_small_icon_desc, owner);
    list_menu_reset_attach_items(menu + 0x238, owner);
    *object_get_fourth_field(menu) = 0x60442D00;
    *object_get_fourth_field(widget_98) = 0x80FFDE8D;
    *object_get_fourth_field(widget_4c) = 0x55F0C070;
    *object_get_fourth_field(widget_e4) = 0x55F0C070;
    *object_get_fourth_field(frame) = 0x70FFFEED;
    *object_get_fourth_field(label) = 0x80F0F0F0;
    *object_get_fourth_field(icon) = 0x60F0F0B0;
    object_set_value_float(menu, 1.0f);
    object_set_value_float(widget_4c, 1.0f);
    object_set_value_float(widget_e4, 1.0f);
    object_set_helper_result(menu, g_resident_data_base + 0x8710, 0x91);
    object_set_helper_result(widget_98, g_resident_data_base + 0x8710, 0x94);
    object_set_helper_result(widget_4c, g_resident_data_base + 0x8710, 0x92);
    object_set_helper_result(widget_e4, g_resident_data_base + 0x8710, 0x93);
    object_set_helper_result(frame, g_resident_data_base + 0x8710, 0x95);
    object_set_second_float4(frame, 1.0f, 1.05f, 0.0f, 0.0f);
    hud_set_widget_field_b(label, GetLocalizedString(0x2BEB));
    hud_set_widget_value_pair(icon, 0xEA9D, 0);
    memset(menu + 0x1B8, 0, 12);
    object_set_second_float4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
}
