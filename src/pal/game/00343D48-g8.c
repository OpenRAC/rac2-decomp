#include "include_asm.h"
#include "names.h"
extern void menu_set_settings(void *, int, int);
extern void object_set_value_float(void *, float);
extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char D_001ADC10[], D_001ADC18[];
extern char *D_001A8CFC[] __attribute__((sda));
extern float D_001AE12C __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void list_menu_reset_attach_items(void *, void *);
extern int list_menu_set_selection(void *, int);

void func_PAL_00343D48(char *object, void *argument)
{
    int *allocation;
    char *first, *second, *widget;
    *(void **)(object + 4) = argument;
    if (argument) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)object = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    **(float **)object = 250.0f;
    (*(float **)object)[1] = 120.0f;
    first = object + 0xEC;
    second = object + 0x138;
    widget = object + 0x10;
    object_init_derived_arrays(first, D_001ADC10, argument);
    object_init_derived_arrays(second, D_001ADC18, argument);
    *object_get_fourth_field(first) = 0x60442D00;
    *object_get_fourth_field(second) = 0x55F0C070;
    object_set_helper_result(first, D_001A8CFC[0] + 0x8710, 0x73);
    object_set_helper_result(second, D_001A8CFC[0] + 0x8710, 0x74);
    object_set_value_float(first, D_001AE12C);
    object_set_value_float(second, D_001AE12C);
    list_menu_reset_attach_items(widget, argument);
    menu_set_settings(widget, 11, 60);
    list_menu_set_selection(object, 0);
}

extern void object_set_first_float4(void *, float, float, float, float);
extern int func_PAL_0034A2F8(void *);
extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int func_PAL_00343EF8(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void func_PAL_0034A300(void *);
extern int func_PAL_002A9FA0(int, int, int, int, int);

void func_PAL_00343FA0(char *self)
{
    int count = func_PAL_0034A2F8(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        func_PAL_002A9FA0(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        object_set_first_float4(self + 0xEC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        object_set_first_float4(self + 0x138, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = object_get_fourth_field(self + 0x138);
        *slot = func_PAL_00343EF8(self) == i ? func_PAL_002A9FA0(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        gfx_draw_screen_element_stored(self + 0xEC);
        gfx_draw_screen_element_stored(self + 0x138);
    }
    func_PAL_0034A300(self + 0x10);
}
