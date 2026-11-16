#include "include_asm.h"
#include "names.h"







extern void F6402b823_FUN_00336320(char *a);
extern void F6402b823_FUN_00336A78(char *a);
extern void F6402b823_FUN_00335E68(char *a, int b);
extern void F6402b823_FUN_00345268(char *a);
extern void F6402b823_FUN_00345088(char *a);
extern void F6402b823_FUN_00344F98(char *a);
extern void F6402b823_FUN_00345178(char *a);
extern void F6402b823_FUN_00344938(char *a);

/* Draws the menu screen's parts when it is shown. */
void menu_screen_draw_parts_pal(char *menu)
{
    if (*(int *)(menu + 1192) != 0) {
        char *label = menu + 456;

        F6402b823_FUN_00336320(menu);
        F6402b823_FUN_00336320(menu + 76);
        F6402b823_FUN_00336320(menu + 152);
        F6402b823_FUN_00336320(menu + 228);
        F6402b823_FUN_00336A78(label);
        F6402b823_FUN_00336A78(menu + 696);
        F6402b823_FUN_00336A78(label);
        F6402b823_FUN_00335E68(menu + 544, 0);
        F6402b823_FUN_00345268(menu);
        F6402b823_FUN_00345088(menu);
        F6402b823_FUN_00344F98(menu);
        F6402b823_FUN_00345178(menu);
        F6402b823_FUN_00344938(menu);
        F6402b823_FUN_00336320(menu + 380);
    }
}


extern void *F449e2f67_FUN_003361A8(char *p);
extern char *F449e2f67_FUN_00336968(char *p);
extern void *F449e2f67_FUN_003366D0(char *p);

/* Constructs the fourteen in-place sub-records of the menu screen and returns the menu. */
char *menu_screen_init_parts_pal(char *menu)
{
    F449e2f67_FUN_003361A8(menu);
    F449e2f67_FUN_003361A8(menu + 76);
    F449e2f67_FUN_003361A8(menu + 152);
    F449e2f67_FUN_003361A8(menu + 228);
    F449e2f67_FUN_003361A8(menu + 304);
    F449e2f67_FUN_003361A8(menu + 380);
    F449e2f67_FUN_00336968(menu + 456);
    F449e2f67_FUN_00336968(menu + 544);
    F449e2f67_FUN_003366D0(menu + 632);
    F449e2f67_FUN_00336968(menu + 696);
    F449e2f67_FUN_00336968(menu + 784);
    F449e2f67_FUN_00336968(menu + 872);
    F449e2f67_FUN_00336968(menu + 960);
    F449e2f67_FUN_00336968(menu + 1048);
    return menu;
}


/* func_PAL_00347570, the PAL copy of func_00345490: the same C with the fields moved
 * and the text ids renumbered, plus the func_00336A30 calls, the two stores at 0x220 + 0x48 and the
 * 0.8 scale on the items at 0x310 and 0x2b8. */
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void object_set_flag_value(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void hud_set_widget_field_b(void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern char *GetLocalizedString(int);
extern int selection_menu_update_layout_pal(void *, int, void *);
extern char *g_resident_data_base[] __attribute__((sda));
extern char g_menu_widget_desc_first[];
extern char g_menu_widget_desc_second[];
extern char g_menu_widget_desc_third[];
extern char g_menu_widget_desc_fourth[];
extern char g_menu_frame_desc[];
extern char g_menu_panel_desc[];
extern char g_menu_hud_desc_label[];
extern char g_menu_hud_desc_body[];
extern char g_selection_menu_widget_defaults_a[];
extern char g_selection_menu_widget_defaults_b[];
extern char g_selection_menu_widget_defaults_c[];
extern char g_menu_hud_desc_title[];
extern char g_menu_hud_label_desc_alt[];
extern char g_menu_icon_desc[];

void selection_menu_init_pal(char *self, void *owner)
{
    int scratch;
    *(void **)(self + 0x474) = owner;
    if (owner) {
        int *position = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x470) = position;
        position[1] = 0; position[2] = 0; position[3] = 0; position[0] = 0;
    }
    *(int *)(self + 0x4f8) = 1;
    (*(float **)(self + 0x470))[0] = 250.0f;
    (*(float **)(self + 0x470))[1] = 207.0f;
    object_init_derived_arrays(self + 0x0, g_menu_widget_desc_first, owner);
    object_init_derived_arrays(self + 0x4c, g_menu_widget_desc_second, owner);
    object_init_derived_arrays(self + 0x98, g_menu_widget_desc_third, owner);
    object_init_derived_arrays(self + 0xe4, g_menu_widget_desc_fourth, owner);
    object_init_derived_arrays(self + 0x130, g_menu_frame_desc, owner);
    object_init_derived_arrays(self + 0x17c, g_menu_panel_desc, owner);
    hud_init_widget_defaults_pal(self + 0x2b8, g_menu_hud_desc_label, owner);
    hud_init_widget_defaults_pal(self + 0x310, g_menu_hud_desc_body, owner);
    hud_init_widget_defaults_pal(self + 0x368, g_selection_menu_widget_defaults_a, owner);
    hud_init_widget_defaults_pal(self + 0x3c0, g_selection_menu_widget_defaults_b, owner);
    hud_init_widget_defaults_pal(self + 0x418, g_selection_menu_widget_defaults_c, owner);
    hud_init_widget_defaults_pal(self + 0x1c8, g_menu_hud_desc_title, owner);
    hud_init_widget_defaults_pal(self + 0x220, g_menu_hud_label_desc_alt, owner);
    *object_get_fourth_field(self + 0x0) = 0x60442d00;
    *object_get_fourth_field(self + 0x98) = 0x55f0c070;
    *object_get_fourth_field(self + 0xe4) = 0x55f0c070;
    *object_get_fourth_field(self + 0x130) = 0x55f0c070;
    *object_get_fourth_field(self + 0x17c) = 0x70fffeed;
    *object_get_fourth_field(self + 0x4c) = 0x60241700;
    *object_get_fourth_field(self + 0x310) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x2b8) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x368) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x3c0) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x418) = 0x80f0f0f0;
    object_set_helper_result(self + 0x0, g_resident_data_base[0] + 0x8710, 0x59);
    object_set_helper_result(self + 0x98, g_resident_data_base[0] + 0x8710, 0x5b);
    object_set_helper_result(self + 0xe4, g_resident_data_base[0] + 0x8710, 0x5c);
    object_set_helper_result(self + 0x130, g_resident_data_base[0] + 0x8710, 0x5d);
    object_set_helper_result(self + 0x17c, g_resident_data_base[0] + 0x8710, 0x5e);
    object_set_helper_result(self + 0x4c, g_resident_data_base[0] + 0x8710, 0x5a);
    object_set_flag_value(self + 0x17c, 0);
    *(int *)(self + 0x4fc) = 0;
    *(int *)(self + 0x500) = 0;
    *(int *)(self + 0x508) = 0;
    object_init_derived_c(self + 0x278, g_menu_icon_desc, owner);
    *object_get_fourth_field(self + 0x278) = 0x60f0f0b0;
    object_set_second_float4(self + 0x278, 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(self + 0x1c8) = 0x80f0f0f0;
    *object_get_fourth_field(self + 0x220) = 0x80f0f0f0;
    hud_set_widget_field_b(self + 0x1c8, GetLocalizedString(0xb63));
    self[0x4b8] = 0;
    hud_set_widget_field_b(self + 0x220, self + 0x4b8);
    *(int *)(self + 0x504) = 0;
    hud_set_widget_field_b(self + 0x310, GetLocalizedString(0xb60));
    hud_set_widget_field_b(self + 0x2b8, GetLocalizedString(0xb6c));
    hud_set_widget_field_a(self + 0x310, 0);
    hud_set_widget_field_a(self + 0x2b8, 2);
    {
        char *label = self + 0x220;
        *(int *)(label + 0x48) = 1;
        *(int *)(label + 0x4c) = 0x78;
    }
    object_set_second_float4(self + 0x310, 0.8f, 0.8f, 0.0f, 0.0f);
    object_set_second_float4(self + 0x2b8, 0.8f, 0.8f, 0.0f, 0.0f);
    hud_set_widget_field_b(self + 0x368, GetLocalizedString(0xb68));
    hud_set_widget_field_b(self + 0x3c0, GetLocalizedString(0xb69));
    hud_set_widget_field_b(self + 0x418, GetLocalizedString(0xb6b));
    selection_menu_update_layout_pal(self, 0, &scratch);
}
