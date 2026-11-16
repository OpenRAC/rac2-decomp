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

/* Sets up the tab menu: its position, widgets, colors, title text and tab icon (PAL). */
void tab_menu_init_pal(s8 *self, s8 *parent) {
    s8 *allocation;
    s8 *highlight;
    s8 *widget_b;
    s8 *widget_c;
    s8 *frame;
    s8 *icon;
    s8 *title;

    (*(s8 **)((s8 *)(self) + (0x22C))) = parent;
    if (parent != 0) {
        allocation = ui_return_second_arg(0x10, pool_alloc_cell(parent));
        (*(s8 **)((s8 *)(self) + (0x228))) = allocation;
        (*(s32 *)((s8 *)(allocation) + (4))) = 0;
        (*(s32 *)((s8 *)(allocation) + (8))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0xC))) = 0;
        (*(s32 *)((s8 *)(allocation) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(self) + (0x230))) = 1;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x228)))) + (0))) = 251.0f;
    highlight = self + 0x98;
    widget_b = self + 0x4C;
    widget_c = self + 0xE4;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(self) + (0x228)))) + (4))) = 170.0f;
    frame = self + 0x130;
    object_init_derived_arrays(self, g_menu_widget_desc_first, parent);
    icon = self + 0x17C;
    title = self + 0x1D0;
    object_init_derived_arrays(highlight, g_menu_widget_desc_second, parent);
    object_init_derived_arrays(widget_b, g_menu_widget_desc_third, parent);
    object_init_derived_arrays(widget_c, g_menu_widget_desc_fourth, parent);
    object_init_derived_arrays(frame, g_menu_frame_desc, parent);
    hud_init_widget_defaults(title, g_menu_hud_label_desc, parent);
    object_init_derived_c(icon, g_menu_small_icon_desc, parent);
    list_menu_reset_attach_items(self + 0x238, parent);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(highlight) = 0x80FFDE8D;
    *object_get_fourth_field(widget_b) = 0x55F0C070;
    *object_get_fourth_field(widget_c) = 0x55F0C070;
    *object_get_fourth_field(frame) = 0x70FFFEED;
    *object_get_fourth_field(title) = 0x80F0F0F0;
    *object_get_fourth_field(icon) = 0x60F0F0B0;
    object_set_value_float(self, 1.0f);
    object_set_value_float(widget_b, 1.0f);
    object_set_value_float(widget_c, 1.0f);
    object_set_helper_result(self, g_resident_data_base + 0x8710, 0x91);
    object_set_helper_result(highlight, g_resident_data_base + 0x8710, 0x94);
    object_set_helper_result(widget_b, g_resident_data_base + 0x8710, 0x92);
    object_set_helper_result(widget_c, g_resident_data_base + 0x8710, 0x93);
    object_set_helper_result(frame, g_resident_data_base + 0x8710, 0x95);
    object_set_second_float4(frame, 1.0f, 1.05f, 0.0f, 0.0f);
    hud_set_widget_field_b(title, GetLocalizedString(0xB66));
    hud_set_widget_value_pair(icon, 0xEA9D, 0);
    memset(self + 0x1B8, 0, 12);
    object_set_second_float4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
}
