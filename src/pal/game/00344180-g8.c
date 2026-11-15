#include "include_asm.h"
#include "names.h"
extern void object_set_value_float(void *, float);
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char D_001ADC10[], D_001ADC18[];
extern char *D_001A8CFC[] __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void list_menu_reset_attach_items(void *, void *);
extern char D_001ADC20[], D_001ADFC0[], D_001AE0C0[];
extern int D_001AE138 __attribute__((sda));
extern void object_init_derived_c(void *, void *, void *);
extern void hud_set_widget_value_pair(void *, int, int);
extern void memset(void *, int, int);
extern void menu_set_selected_index(void *, int);
extern void object_set_second_float4(void *, float, float, float, float);

/* Sets up a level object: it allocates the pair of positions at +0x180 and puts
   253.0 and 200.0 in it, names the four children at +0x00, +0x4C, +0xE4 and
   +0x130, gives each of them its colour and its metric, and ends with the
   object's own fields at +0x170, +0x174, +0x178 and +0x17C. */
void func_PAL_00344180(char *object, void *arg)
{
    int *allocation;
    *(void **)(object + 0x184) = arg;
    if (arg != 0) {
        allocation = ui_return_second_arg(16, pool_alloc_cell(arg));
        *(int **)(object + 0x180) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(object + 0x170) = 1;
    (*(float **)(object + 0x180))[0] = 253.0f;
    (*(float **)(object + 0x180))[1] = 200.0f;
    object_init_derived_arrays(object, D_001ADC10, arg);
    object_init_derived_arrays(object + 0x4C, D_001ADC20, arg);
    object_init_derived_arrays(object + 0xE4, D_001ADFC0, arg);
    object_init_derived_c(object + 0x130, D_001AE0C0, arg);
    list_menu_reset_attach_items(object + 0x188, arg);
    *object_get_fourth_field(object) = 0x60442D00;
    *object_get_fourth_field(object + 0x4C) = 0x55F0C070;
    *object_get_fourth_field(object + 0xE4) = 0x70FFFEED;
    *object_get_fourth_field(object + 0x130) = 0x60F0F0B0;
    object_set_value_float(object, 1.0f);
    object_set_value_float(object + 0x4C, 1.0f);
    object_set_helper_result(object, D_001A8CFC[0] + 0x8710, 0xCD);
    object_set_helper_result(object + 0x4C, D_001A8CFC[0] + 0x8710, 0xCE);
    object_set_helper_result(object + 0xE4, D_001A8CFC[0] + 0x8710, 0x95);
    object_set_second_float4(object + 0xE4, 1.0f, 1.05f, 0.0f, 0.0f);
    hud_set_widget_value_pair(object + 0x130, 0xEA9D, 0);
    memset(object + 0x16C, 0, 4);
    object_set_second_float4(object + 0x130, 32.0f, 32.0f, 0.0f, 0.0f);
    *(int *)(object + 0x174) = 0xEAA6;
    *(void **)(object + 0x178) = &D_001AE138;
    *(int *)(object + 0x17C) = 4;
    menu_set_selected_index(object + 0x188, *(int *)(object + 0x16C));
}
