#include "include_asm.h"
#include "names.h"

extern float D_001AE180 __attribute__((sda));
extern float D_001AE17C;
extern float D_001AE178 __attribute__((sda));
extern void object_set_first_float4(void *, float, float, float, float);
/* Moves the cursor to the row of the selected entry. */
void list_menu_position_cursor(char *self)
{
    int index = *(int *)(self + 0x16C);
    float *v = *(float **)(self + 0x180);
    object_set_first_float4(self + 0xE4, D_001AE178 + v[0],
            (D_001AE17C + D_001AE180 * (float)index) + v[1],
            0.0f, 0.0f);
}

extern float D_001AE188 __attribute__((sda));
extern float D_001AE18C;
extern float D_001AE190 __attribute__((sda));
extern float D_001AE194 __attribute__((sda));
extern void menu_set_position(void *, float, float);
extern void menu_set_settings(void *, int, int);
extern void *UpdateMenuListSelection(void *, int);
extern int menu_get_selected_index(void *);
/* Updates the list from the player input and stores the selected entry. */
void list_menu_update_from_input(char *self, int arg)
{
    char *child = self + 0x188;
    float *position = *(float **)(self + 0x180);
    menu_set_position(child, position[0] + D_001AE188, position[1] + D_001AE18C);
    menu_set_settings(child, (int)D_001AE190, (int)D_001AE194);
    UpdateMenuListSelection(child, arg);
    *(int *)(self + 0x16C) = menu_get_selected_index(child);
}
extern float D_001AE198 __attribute__((sda));
extern float D_001AE19C;
extern float D_001AE1A0 __attribute__((sda));
extern float D_001AE1A4;
extern float D_001AE1A8[2] __attribute__((sda));
extern int menu_get_entry_count(void *);
extern void object_set_value_float(void *, float);
extern void list_menu_noop_hook(void *);
/* Updates the list menu each frame and returns the selected entry. */
int list_menu_update(char *self, int arg)
{
    char *child = self + 0x4C;
    float *position = *(float **)(self + 0x180);
    float *scale;
    unsigned int index;
    object_set_first_float4(self, D_001AE198 + position[0], D_001AE19C + position[1], 0.0f, 0.0f);
    position = *(float **)(self + 0x180);
    object_set_first_float4(child, D_001AE1A0 + position[0], D_001AE1A4 + position[1], 0.0f, 0.0f);
    index = menu_get_entry_count(self + 0x188) - 1;
    scale = (float *)((char *)D_001AE1A8 + (index << 2));
    object_set_value_float(self, *scale);
    object_set_value_float(child, *scale);
    list_menu_update_from_input(self, arg);
    list_menu_position_cursor(self);
    list_menu_noop_hook(self);
    return *(int *)(self + 0x16C);
}
extern int pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char D_001ADC10[], D_001ADC18[];
extern char *D_001A8CFC[] __attribute__((sda));
extern float D_001AE12C __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void list_menu_reset_attach_items(void *, void *);
extern void list_menu_set_selection(void *, int);
/* Sets up a small list menu: its position, two panels and its scrolling list. */
void small_list_menu_init(char *object, void *argument)
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
    first = object + 0xDC;
    second = object + 0x128;
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
void list_menu_init(char *object, void *arg)
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

extern float D_001AE130 __attribute__((sda));
extern float D_001AE134 __attribute__((sda));
extern int D_00138344[];
extern int list_menu_get_selection(void *);
extern int *object_get_fourth_field(void *);
extern void gfx_draw_screen_element_stored(void *);
extern void option_list_draw_rows(void *);
extern int math_ping_pong_blend_values(int, int, int, int, int);

/* Draws every row of the list menu and highlights the selected row. */
void small_list_menu_draw_rows(char *self)
{
    int count = menu_get_entry_count(self + 0x10);
    int i;
    int *slot;

    if (D_00138344[0] & 0x5000)
        math_ping_pong_blend_values(0, 0, 1, 0, 1);
    for (i = 0; i < count; i++) {
        float step = (float)i;
        object_set_first_float4(self + 0xDC, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        object_set_first_float4(self + 0x128, (*(float **)self)[0] + D_001AE134,
                      (*(float **)self)[1] + D_001AE130 * step, 0.0f, 0.0f);
        slot = object_get_fourth_field(self + 0x128);
        *slot = list_menu_get_selection(self) == i ? math_ping_pong_blend_values(0x20FFFEED, 0x70FFFEED, 0x14, 0, 0) : 0x55F0C070;
        gfx_draw_screen_element_stored(self + 0xDC);
        gfx_draw_screen_element_stored(self + 0x128);
    }
    option_list_draw_rows(self + 0x10);
}
