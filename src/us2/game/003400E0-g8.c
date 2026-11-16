#include "names.h"
/* func_US2_003400E0, the USA v2.00 copy of func_0033F218. */
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, char *, void *);
extern void hud_init_widget_defaults_us2(void *, char *, void *);
extern void object_init_derived_c(void *, char *, void *);
extern void object_set_second_float4(void *, float, float, float, float);
extern void object_set_first_float4(void *, float, float, float, float);
extern unsigned int *object_get_fourth_field(void *);
extern float *object_get_second_field(void *);
extern void object_change_first_value(void *, void *);
extern void object_set_helper_result(void *, char *, int);
extern void object_set_flag_value(void *, int);
extern int sprintf(char *, char *, ...);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *GetLocalizedString(int);
extern void hud_set_widget_field_b(void *, unsigned int);
extern void object_init_derived_b(void *, int, int, char *, void *);
extern void widget_set_pos_y(void *, int);
extern void func_US2_00337A38(void *, int);
extern void meter_set_value(void *, int);
extern void object_set_first_pair(void *, unsigned int, unsigned int);
extern void object_set_second_pair(void *, unsigned int, unsigned int);
extern void text_set_alignment(void *, unsigned int);
extern void widget_store_field(void *, int);
extern int radial_menu_update_us2(void *, int);
extern char *g_resident_data_base;
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[], g_menu_widget_desc_third[], g_menu_widget_desc_fourth[];
extern char g_menu_backdrop_desc[], g_radial_menu_hud_desc_first[], g_menu_hud_desc_body[], g_radial_menu_hud_desc_second[], g_radial_menu_hud_desc_third[];
extern char g_menu_frame_desc[], g_menu_panel_desc[], g_menu_extra_widget_desc[], g_menu_icon_desc[];
extern char g_ammo_bolt_widget_desc_first[], g_ammo_bolt_widget_desc_second[], g_ammo_bolt_widget_desc_third[], g_str_ammo_bolt_name_format_first[], g_str_ammo_bolt_name_format_second[];
extern char g_menu_hud_desc_title[], g_menu_hud_label_desc_alt[], g_menu_bar_desc[];
extern unsigned int g_radial_menu_field_data_first __attribute__((sda));
extern unsigned int g_radial_menu_field_data_second __attribute__((sda));

/* Initializes the menu's named widgets, resource IDs, colors and radial entries. */
void radial_menu_init_us2(char *self, void *owner)
{
    char name[16];
    int i;
    int j;
    /* the widgets the last part of the function sets up are reached from here */
    char *base = self + 0x3B0;
    char *widget;
    *(void **)(self + 0x810) = owner;
    if (owner) {
        int *allocation = ui_return_second_arg(16, pool_alloc_cell(owner));
        *(int **)(self + 0x80C) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(self + 0xAB8) = 1;
    (*(float **)(self + 0x80C))[0] = 250.0f;
    (*(float **)(self + 0x80C))[1] = 200.0f;
    *(int *)(self + 0x814) = 0;
    *(int *)(self + 0x818) = 0;
    *(int *)(self + 0x81C) = 0;
    object_init_derived_arrays(self, g_menu_widget_desc_first, owner);
    object_init_derived_arrays((self + 0x4C), g_menu_widget_desc_second, owner);
    object_init_derived_arrays((self + 0xE4), g_menu_widget_desc_third, owner);
    object_init_derived_arrays((self + 0x130), g_menu_widget_desc_fourth, owner);
    object_init_derived_arrays((self + 0x98), g_menu_backdrop_desc, owner);
    hud_init_widget_defaults_us2(self + 0x8D8, g_radial_menu_hud_desc_first, owner);
    hud_init_widget_defaults_us2((self + 0x930), g_menu_hud_desc_body, owner);
    hud_init_widget_defaults_us2((self + 0x988), g_radial_menu_hud_desc_second, owner);
    hud_init_widget_defaults_us2((self + 0x9E0), g_radial_menu_hud_desc_third, owner);
    object_init_derived_arrays((self + 0x17C), g_menu_frame_desc, owner);
    object_init_derived_arrays((self + 0x1C8), g_menu_panel_desc, owner);
    object_init_derived_arrays((self + 0x214), g_menu_extra_widget_desc, owner);
    object_init_derived_c((self + 0x7D0), g_menu_icon_desc, owner);
    object_set_second_float4((self + 0x7D0), 32.0f, 32.0f, 0.0f, 0.0f);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field((self + 0x4C)) = 0x60241700;
    *object_get_fourth_field((self + 0xE4)) = 0x55F0C070;
    *object_get_fourth_field((self + 0x98)) = 0x60241700;
    *object_get_fourth_field((self + 0x130)) = 0x55F0C070;
    *object_get_fourth_field((self + 0x17C)) = 0x55F0C070;
    *object_get_fourth_field((self + 0x1C8)) = 0x55F0C070;
    *object_get_fourth_field((self + 0x214)) = 0x70FFFEED;
    *object_get_fourth_field((self + 0x7D0)) = 0x60F0F0B0;
    *object_get_fourth_field(self + 0x8D8) = 0x80F0F0F0;
    *object_get_fourth_field((self + 0x930)) = 0x80F0F0F0;
    *object_get_fourth_field((self + 0x988)) = 0x80F0F0F0;
    *object_get_fourth_field((self + 0x9E0)) = 0x80F0F0F0;
    object_set_helper_result(self, g_resident_data_base + 0x8710, 99);
    object_set_helper_result((self + 0x4C), g_resident_data_base + 0x8710, 100);
    object_set_helper_result((self + 0x98), g_resident_data_base + 0x8710, 41);
    object_set_helper_result((self + 0xE4), g_resident_data_base + 0x8710, 102);
    object_set_helper_result((self + 0x130), g_resident_data_base + 0x8710, 101);
    object_set_helper_result((self + 0x17C), g_resident_data_base + 0x8710, 93);
    object_set_helper_result((self + 0x1C8), g_resident_data_base + 0x8710, 35);
    object_set_helper_result((self + 0x214), g_resident_data_base + 0x8710, 94);
    object_init_derived_arrays((self + 0x2A8), g_ammo_bolt_widget_desc_first, owner);
    object_set_helper_result((self + 0x2A8), g_resident_data_base + 0x8710, 7);
    object_set_second_float4((self + 0x2A8), 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4((self + 0x2A8), 125.0f, 208.0f, 0.0f, 0.0f);
    *object_get_fourth_field((self + 0x2A8)) = 0x60442D00;
    object_init_derived_arrays((self + 0x2F4), g_ammo_bolt_widget_desc_second, owner);
    object_set_helper_result((self + 0x2F4), g_resident_data_base + 0x8710, 6);
    object_set_second_float4((self + 0x2F4), 1.0f, 1.0f, 0.0f, 0.0f);
    object_set_first_float4((self + 0x2F4), 125.0f, 208.0f, 0.0f, 0.0f);
    *object_get_fourth_field((self + 0x2F4)) = 0x55F0C070;
    object_init_derived_arrays((self + 0x5A0), g_ammo_bolt_widget_desc_third, owner);
    object_set_helper_result((self + 0x5A0), g_resident_data_base + 0x8710, 16);
    object_set_first_float4((self + 0x5A0), 125.0f, 208.0f, 0.0f, 0.0f);
    *object_get_fourth_field((self + 0x5A0)) = 0x80FFDE8D;
    object_set_flag_value((self + 0x5A0), 1);
    *(int *)(self + 0x7CC) = 0;
    for (i = 0; i < 8; i++) {
        float angle, x;
        char *entry, *icon;
        unsigned int panel_color = 0x60442D00;
        unsigned int icon_color = 0x60F0F0B0;
        sprintf(name, g_str_ammo_bolt_name_format_first, i);
        entry = self + (i * 0x4C + 0x340);
        object_init_derived_arrays(entry, name, owner);
        object_set_helper_result(entry, g_resident_data_base + 0x8710, i + 8);
        object_set_second_float4(entry, 1.0f, 1.0f, 0.0f, 0.0f);
        object_set_first_float4(entry, (*(float **)(self + 0x80C))[0] + 113.0f,
            (*(float **)(self + 0x80C))[1] + -72.0f, 0.0f, 0.0f);
        *object_get_fourth_field(entry) = panel_color;
        sprintf(name, g_str_ammo_bolt_name_format_second, i);
        icon = self + (i * 0x3C + 0x5EC);
        object_init_derived_c(icon, name, owner);
        object_set_flag_value(icon, 0);
        angle = FastAddRotations(((float)i + (float)i) * 0.3926990926f - 3.141592741f, 1.570796371f);
        x = (float)((int)(math_fast_sin_or_cos_a(angle) * 82.13999939f) + 348);
        object_set_first_float4(icon, x,
            (float)((int)(math_fast_sin_or_cos_b(angle) * 76.44200134f) + 109), 0.0f, 0.0f);
        object_set_second_float4(icon, 32.0f, 32.0f, 0.0f, 0.0f);
        *object_get_fourth_field(icon) = icon_color;
    }
    for (j = 1; j < 8; j++) {
        object_change_first_value(self + (j * 0x4C + 0x340), object_get_second_field(base + (0x340 - 0x3B0)));
        object_change_first_value(self + (j * 0x3C + 0x5EC), object_get_second_field(base + (0x5EC - 0x3B0)));
    }
    object_change_first_value((base + (0x2A8 - 0x3B0)), object_get_second_field(base + (0x340 - 0x3B0)));
    widget = base + (0x828 - 0x3B0);
    hud_init_widget_defaults_us2(widget, g_menu_hud_desc_title, owner);
    *(int *)(widget + 0x54) = 0;
    hud_init_widget_defaults_us2(base + (0x880 - 0x3B0), g_menu_hud_label_desc_alt, owner);
    *object_get_fourth_field(base + (0x828 - 0x3B0)) = 0x80F0F0F0;
    *object_get_fourth_field(base + (0x880 - 0x3B0)) = 0x80F0F0F0;
    hud_set_widget_field_b(base + (0x828 - 0x3B0), GetLocalizedString(0x2BE9));
    self[0xA78] = 0;
    hud_set_widget_field_b(base + (0x880 - 0x3B0), (unsigned int)(base + (0xA78 - 0x3B0)));
    hud_set_widget_field_b(base + (0x8D8 - 0x3B0), GetLocalizedString(0x2BF1));
    hud_set_widget_field_b((base + (0x930 - 0x3B0)), GetLocalizedString(0x2BE5));
    hud_set_widget_field_b((base + (0x988 - 0x3B0)), g_radial_menu_field_data_first);
    hud_set_widget_field_b((base + (0x9E0 - 0x3B0)), g_radial_menu_field_data_second);
    object_set_second_float4((base + (0x988 - 0x3B0)), 1.25f, 1.25f, 0.0f, 0.0f);
    object_set_second_float4((base + (0x9E0 - 0x3B0)), 1.25f, 1.25f, 0.0f, 0.0f);
    object_init_derived_b(base + (0x260 - 0x3B0), 32, 0, g_menu_bar_desc, owner);
    widget_set_pos_y(base + (0x260 - 0x3B0), 5);
    func_US2_00337A38(base + (0x260 - 0x3B0), 100);
    meter_set_value(base + (0x260 - 0x3B0), 0);
    object_set_first_pair(base + (0x260 - 0x3B0), 0x6049C1FF, 0x60001EFF);
    object_set_second_pair(base + (0x260 - 0x3B0), 0x50F0C070, 0x50F0C070);
    text_set_alignment(base + (0x260 - 0x3B0), 0x80000000);
    widget_store_field(base + (0x260 - 0x3B0), 0);
    radial_menu_update_us2(self, 0);
}
