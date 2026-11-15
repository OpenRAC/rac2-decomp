#include "include_asm.h"
#include "names.h"
extern float D_001AE188 __attribute__((sda));
extern float D_001AE18C;
extern float D_001AE190 __attribute__((sda));
extern float D_001AE194 __attribute__((sda));
extern void menu_set_position(void *, float, float);
extern void menu_set_settings(void *, int, int);
extern void *UpdateMenuListSelection(void *, int);
extern int menu_get_selected_index(void *);

void func_PAL_00344490(char *self, int arg)
{
    char *child = self + 0x188;
    float *position = *(float **)(self + 0x180);
    menu_set_position(child, position[0] + D_001AE188, position[1] + D_001AE18C);
    menu_set_settings(child, (int)D_001AE190, (int)D_001AE194);
    UpdateMenuListSelection(child, arg);
    *(int *)(self + 0x16C) = menu_get_selected_index(child);
}

extern void object_set_first_float4(void *, float, float, float, float);
extern float D_001AE198 __attribute__((sda));
extern float D_001AE19C;
extern float D_001AE1A0 __attribute__((sda));
extern float D_001AE1A4;
extern float D_001AE1A8[2] __attribute__((sda));
extern int menu_get_entry_count(void *);
extern void object_set_value_float(void *, float);
extern void list_menu_noop_hook(void *);

int func_PAL_00344528(char *self, int arg)
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
