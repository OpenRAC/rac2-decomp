#include "names.h"
/* func_PAL_0033AF68, the PAL copy of func_00339078: the same C, where the four labels from object + 0x138
   step 0x58 instead of 0x48, the fields after them move up by 0x40, and both label texts are looked up. */
extern void *pool_alloc_cell(void *);
extern float *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults_pal(void *, void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern unsigned int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void hud_set_widget_field_b(void *, void *);
extern char *GetLocalizedString(int);
extern int mission_screen_place_parts_pal(void *, int);
extern char *ref_L00_0042E9A8_00;
extern char ref_L00_0042E9A8_01[];
extern char ref_L00_0042E9A8_02[];
extern char ref_L00_0042E9A8_03[];
extern char ref_L00_0042E9A8_04[];
extern char ref_L00_0042E9A8_05[];
extern char ref_L00_0042E9A8_06[];
extern char ref_L00_0042E9A8_07[];
extern char ref_L00_0042E9A8_08[];

/* Creates the mission screen's panels and labels, then applies its layout. */
void mission_screen_init_pal(char *object, void *parent)
{
    char *title;
    char *city;
    char *planet;
    char *mission;
    char *name;
    char *description;
    char *details;
    float *position;
    *(void **)object = parent;
    *(int *)(object + 0x2d8) = 1;
    if (parent) {
        position = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(float **)(object + 4) = position;
        position[1] = 0.0f;
        position[2] = 0.0f;
        position[3] = 0.0f;
        position[0] = 0.0f;
    }
    (*(float **)(object + 4))[0] = 256.0f;
    (*(float **)(object + 4))[1] = 198.0f;
    name = object + 0x138;
    title = object + 8;
    city = object + 0x54;
    planet = object + 0xa0;
    mission = object + 0xec;
    description = object + 0x190;
    details = object + 0x1e8;
    object_init_derived_arrays(title, ref_L00_0042E9A8_01, parent);
    object_init_derived_arrays(city, ref_L00_0042E9A8_02, parent);
    object_init_derived_arrays(planet, ref_L00_0042E9A8_03, parent);
    object_init_derived_arrays(mission, ref_L00_0042E9A8_04, parent);
    hud_init_widget_defaults_pal(name, ref_L00_0042E9A8_05, parent);
    hud_init_widget_defaults_pal(description, ref_L00_0042E9A8_06, parent);
    hud_init_widget_defaults_pal(details, ref_L00_0042E9A8_07, parent);
    hud_init_widget_defaults_pal(object + 0x240, ref_L00_0042E9A8_08, parent);
    hud_set_widget_field_a(details, 1);
    *object_get_fourth_field(title) = 0x60442d00;
    *object_get_fourth_field(city) = 0x60241700;
    *object_get_fourth_field(planet) = 0x55f0c070;
    *object_get_fourth_field(mission) = 0x55f0c070;
    *object_get_fourth_field(name) = 0x80f0f0f0;
    *object_get_fourth_field(description) = 0x80f0f0f0;
    *object_get_fourth_field(details) = 0x80f0f0f0;
    object_set_helper_result(title, ref_L00_0042E9A8_00 + 0x8710, 0x6b);
    object_set_helper_result(city, ref_L00_0042E9A8_00 + 0x8710, 0x6c);
    object_set_helper_result(planet, ref_L00_0042E9A8_00 + 0x8710, 0x6d);
    object_set_helper_result(mission, ref_L00_0042E9A8_00 + 0x8710, 0x6e);
    hud_set_widget_field_b(name, GetLocalizedString(0xbd6));
    hud_set_widget_field_b(description, GetLocalizedString(0xb60));
    hud_set_widget_field_b(details, object + 0x298);
    mission_screen_place_parts_pal(object, 0);
}
