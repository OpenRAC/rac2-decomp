#include "names.h"
extern int pool_alloc_cell(void *);
extern float *ui_return_second_arg(int, int);
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern unsigned int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void hud_set_widget_field_b(void *, void *);
extern void *GetLocalizedString(int);
extern int mission_screen_place_parts(void *, int);
extern char *ref_L00_0042E9A8_00;
extern char ref_L00_0042E9A8_01[];
extern char ref_L00_0042E9A8_02[];
extern char ref_L00_0042E9A8_03[];
extern char ref_L00_0042E9A8_04[];
extern char ref_L00_0042E9A8_05[];
extern char ref_L00_0042E9A8_06[];
extern char ref_L00_0042E9A8_07[];
extern char ref_L00_0042E9A8_08[];
extern char ref_L00_0042E9A8_09[15] __attribute__((sda));

/* Creates the mission screen's panels and labels, then applies its layout. */
void mission_screen_init(char *screen, void *parent)
{
    char *title;
    char *city;
    char *planet;
    char *mission;
    char *name;
    char *description;
    char *details;
    float *position;
    *(void **)screen = parent;
    *(int *)(screen + 0x298) = 1;
    if (parent) {
        position = ui_return_second_arg(16, pool_alloc_cell(parent));
        *(float **)(screen + 4) = position;
        position[1] = 0.0f;
        position[2] = 0.0f;
        position[3] = 0.0f;
        position[0] = 0.0f;
    }
    (*(float **)(screen + 4))[0] = 256.0f;
    (*(float **)(screen + 4))[1] = 198.0f;
    name = screen + 0x138;
    title = screen + 8;
    city = screen + 0x54;
    planet = screen + 0xa0;
    mission = screen + 0xec;
    description = screen + 0x180;
    details = screen + 0x1c8;
    object_init_derived_arrays(title, ref_L00_0042E9A8_01, parent);
    object_init_derived_arrays(city, ref_L00_0042E9A8_02, parent);
    object_init_derived_arrays(planet, ref_L00_0042E9A8_03, parent);
    object_init_derived_arrays(mission, ref_L00_0042E9A8_04, parent);
    hud_init_widget_defaults(name, ref_L00_0042E9A8_05, parent);
    hud_init_widget_defaults(description, ref_L00_0042E9A8_06, parent);
    hud_init_widget_defaults(details, ref_L00_0042E9A8_07, parent);
    hud_init_widget_defaults(screen + 0x210, ref_L00_0042E9A8_08, parent);
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
    hud_set_widget_field_b(name, ref_L00_0042E9A8_09);
    hud_set_widget_field_b(description, GetLocalizedString(0x2d4f));
    hud_set_widget_field_b(details, screen + 0x258);
    mission_screen_place_parts(screen, 0);
}
