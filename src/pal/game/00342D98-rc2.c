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

void tab_menu_init_pal(s8 *arg0, s8 *arg1) {
    s8 *p;
    s8 *s5;
    s8 *s2;
    s8 *s3;
    s8 *s4;
    s8 *s6;
    s8 *l0;

    (*(s8 **)((s8 *)(arg0) + (0x22C))) = arg1;
    if (arg1 != 0) {
        p = ui_return_second_arg(0x10, pool_alloc_cell(arg1));
        (*(s8 **)((s8 *)(arg0) + (0x228))) = p;
        (*(s32 *)((s8 *)(p) + (4))) = 0;
        (*(s32 *)((s8 *)(p) + (8))) = 0;
        (*(s32 *)((s8 *)(p) + (0xC))) = 0;
        (*(s32 *)((s8 *)(p) + (0))) = 0;
    }
    (*(s32 *)((s8 *)(arg0) + (0x230))) = 1;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(arg0) + (0x228)))) + (0))) = 251.0f;
    s5 = arg0 + 0x98;
    s2 = arg0 + 0x4C;
    s3 = arg0 + 0xE4;
    (*(f32 *)((s8 *)((*(s8 **)((s8 *)(arg0) + (0x228)))) + (4))) = 170.0f;
    s4 = arg0 + 0x130;
    object_init_derived_arrays(arg0, g_menu_widget_desc_first, arg1);
    s6 = arg0 + 0x17C;
    l0 = arg0 + 0x1D0;
    object_init_derived_arrays(s5, g_menu_widget_desc_second, arg1);
    object_init_derived_arrays(s2, g_menu_widget_desc_third, arg1);
    object_init_derived_arrays(s3, g_menu_widget_desc_fourth, arg1);
    object_init_derived_arrays(s4, g_menu_frame_desc, arg1);
    hud_init_widget_defaults(l0, g_menu_hud_label_desc, arg1);
    object_init_derived_c(s6, g_menu_small_icon_desc, arg1);
    list_menu_reset_attach_items(arg0 + 0x238, arg1);
    *object_get_fourth_field(arg0) = 0x60442D00;
    *object_get_fourth_field(s5) = 0x80FFDE8D;
    *object_get_fourth_field(s2) = 0x55F0C070;
    *object_get_fourth_field(s3) = 0x55F0C070;
    *object_get_fourth_field(s4) = 0x70FFFEED;
    *object_get_fourth_field(l0) = 0x80F0F0F0;
    *object_get_fourth_field(s6) = 0x60F0F0B0;
    object_set_value_float(arg0, 1.0f);
    object_set_value_float(s2, 1.0f);
    object_set_value_float(s3, 1.0f);
    object_set_helper_result(arg0, g_resident_data_base + 0x8710, 0x91);
    object_set_helper_result(s5, g_resident_data_base + 0x8710, 0x94);
    object_set_helper_result(s2, g_resident_data_base + 0x8710, 0x92);
    object_set_helper_result(s3, g_resident_data_base + 0x8710, 0x93);
    object_set_helper_result(s4, g_resident_data_base + 0x8710, 0x95);
    object_set_second_float4(s4, 1.0f, 1.05f, 0.0f, 0.0f);
    hud_set_widget_field_b(l0, GetLocalizedString(0xB66));
    hud_set_widget_value_pair(s6, 0xEA9D, 0);
    memset(arg0 + 0x1B8, 0, 12);
    object_set_second_float4(s6, 32.0f, 32.0f, 0.0f, 0.0f);
}
