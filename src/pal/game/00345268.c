#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern void *object_construct_derived_a(u8 *);
extern char *hud_construct_widget_base(u8 *);
extern char *hud_construct_widget_base(u8 *);
extern unsigned long menu_return_argument(u8 *);
extern void *object_construct_derived_c(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *func_PAL_00345268(u8 *a0) {
    object_construct_derived_a(a0);
    object_construct_derived_a(a0 + 76);
    object_construct_derived_a(a0 + 152);
    object_construct_derived_c(a0 + 228);
    hud_construct_widget_base(a0 + 432);
    hud_construct_widget_base(a0 + 520);
    hud_construct_widget_base(a0 + 608);
    menu_return_argument(a0 + 712);
    return a0;
}


extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char g_menu_widget_desc_first[], g_menu_widget_desc_second[], g_menu_widget_desc_third[], g_menu_hud_label_desc[], g_circle_menu_icon_data[], g_menu_small_icon_desc[];
/* sda in this -G0 unit gives the one-instruction (macro) load of D_001A8CFC that retail has */
extern char *g_resident_data_base[] __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern void func_PAL_00338688(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void hud_set_widget_field_b(void *, void *);
extern void hud_set_widget_field_a(void *, int);
extern char *GetLocalizedString(int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void menu_list_init(void *, void *);
extern void menu_list_set_spacing(void *, float, float);
extern void menu_list_set_icon_size(void *, float);
extern int func_PAL_003457F0(void *, int);
extern void func_PAL_00345628(u8 *, unsigned int);

/* func_PAL_003452C8, the PAL copy of func_00343260: the same C, where the sub-objects past +0x1F8 move,
   the text id becomes 0xB60 and func_00336A30 is called after the third func_00336A38. */
void func_PAL_003452C8(char *self, void *argument)
{
    *(void **)(self + 0x2BC) = argument;
    if (argument) {
        int *allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(self + 0x2B8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(self + 0x2C0) = 1;
    **(float **)(self + 0x2B8) = 251.0f;
    (*(float **)(self + 0x2B8))[1] = 210.0f;
    object_init_derived_arrays(self, g_menu_widget_desc_first, argument);
    object_init_derived_arrays(self + 0x4C, g_menu_widget_desc_second, argument);
    object_init_derived_arrays(self + 0x98, g_menu_widget_desc_third, argument);
    func_PAL_00338688(self + 0x1B0, g_menu_hud_label_desc, argument);
    func_PAL_00338688(self + 0x208, g_circle_menu_icon_data, argument);
    func_PAL_00338688(self + 0x260, g_circle_menu_icon_data, argument);
    object_init_derived_c(self + 0xE4, g_menu_small_icon_desc, argument);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(self + 0x4C) = 0x60241700;
    *object_get_fourth_field(self + 0x98) = 0x55F0C070;
    *object_get_fourth_field(self + 0x1B0) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x260) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x208) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0xE4) = 0x80F0F0F0;
    object_set_helper_result(self, g_resident_data_base[0] + 0x8710, 0x99);
    object_set_helper_result(self + 0x4C, g_resident_data_base[0] + 0x8710, 0x9A);
    object_set_helper_result(self + 0x98, g_resident_data_base[0] + 0x8710, 0x9B);
    hud_set_widget_field_b(self + 0x1B0, self + 0x120);
    hud_set_widget_field_b(self + 0x208, self + 0x160);
    hud_set_widget_field_b(self + 0x260, (void *)GetLocalizedString(0xB60));
    hud_set_widget_field_a(self + 0x260, 2);
    func_PAL_00345628((u8 *)self, 0);
    object_set_second_float4(self + 0xE4, 32.0f, 32.0f, 0.0f, 0.0f);
    menu_list_init(self + 0x2C8, argument);
    menu_list_set_spacing(self + 0x2C8, 0.0f, 40.0f);
    menu_list_set_icon_size(self + 0x2C8, 32.0f);
    *(int *)(self + 0x360) = 0;
    func_PAL_003457F0(self, 0);
}






typedef int s32;
typedef unsigned int u32;
extern void item_menu_set_title_mode(u8 *, u32);

void func_PAL_00345628(u8 *a0, u32 a1) {
    if (a1 < 4) *(u32 *)(a0 + 0x2C4) = a1;
    *(s32 *)(a0 + 0x1a0) = 0;
}





