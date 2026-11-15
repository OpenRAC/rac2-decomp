#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern char *func_L00_0042BAD0_3(u8 *);

extern char *func_L00_0042BFF8_2(u8 *);

extern char *func_L00_0042C290_3(u8 *);

extern unsigned long func_L00_004380E0_1(u8 *);

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_a2544d80ec96_AbiByte22;

extern int menu_list_build_ids(QwenRecovery_a2544d80ec96_AbiByte22 *owner, const QwenRecovery_a2544d80ec96_AbiByte22 *table);

extern int menu_list_get_selected_id(unsigned char *owner);

extern void menu_list_clear_state(unsigned char *owner);

typedef int s32;

typedef unsigned int u32;

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *menu_init_widgets(u8 *menu) {
    func_L00_0042BAD0_3(menu);
    func_L00_0042BAD0_3(menu + 76);
    func_L00_0042BAD0_3(menu + 152);
    func_L00_0042BFF8_2(menu + 228);
    func_L00_0042C290_3(menu + 432);
    func_L00_0042C290_3(menu + 504);
    func_L00_0042C290_3(menu + 576);
    func_L00_004380E0_1(menu + 664);
    return menu;
}

extern void *pool_alloc_cell(void *);
extern int *ui_return_second_arg(int, int);
extern char D_001ADC10[], D_001ADC18[], D_001ADC20[], D_001ADC30[], D_001ADC88[], D_001AE0C0[];
/* sda in this -G0 unit gives the one-instruction (macro) load of D_001A8CFC that retail has; a plain
   declaration splits it into lui/lw with two registers and shifts the register allocation */
extern char *D_001A8CFC[] __attribute__((sda));
extern void object_init_derived_arrays(void *, void *, void *);
extern void hud_init_widget_defaults(void *, void *, void *);
extern void object_init_derived_c(void *, void *, void *);
extern int *object_get_fourth_field(void *);
extern void object_set_helper_result(void *, void *, int);
extern void hud_set_widget_field_b(void *, void *);
extern char *GetLocalizedString(int);
extern void object_set_second_float4(void *, float, float, float, float);
extern void menu_list_init(void *, void *);
extern void menu_list_set_spacing(void *, float, float);
extern void menu_list_set_icon_size(void *, float);
extern int item_menu_update(void *, int);
extern void item_menu_set_title_mode(u8 *, u32);

/* constructor: stores the owner at +0x28C, allocates the 16-byte position at +0x288 and initialises the
   sub-objects at +0x0, +0x4C, +0x98, +0xE4, +0x1B0, +0x1F8, +0x240 and +0x298 */
void item_menu_construct(char *self, void *argument)
{
    *(void **)(self + 0x28C) = argument;
    if (argument) {
        int *allocation = ui_return_second_arg(16, pool_alloc_cell(argument));
        *(int **)(self + 0x288) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    *(int *)(self + 0x290) = 1;
    **(float **)(self + 0x288) = 251.0f;
    (*(float **)(self + 0x288))[1] = 210.0f;
    object_init_derived_arrays(self, D_001ADC10, argument);
    object_init_derived_arrays(self + 0x4C, D_001ADC18, argument);
    object_init_derived_arrays(self + 0x98, D_001ADC20, argument);
    hud_init_widget_defaults(self + 0x1B0, D_001ADC30, argument);
    hud_init_widget_defaults(self + 0x1F8, D_001ADC88, argument);
    hud_init_widget_defaults(self + 0x240, D_001ADC88, argument);
    object_init_derived_c(self + 0xE4, D_001AE0C0, argument);
    *object_get_fourth_field(self) = 0x60442D00;
    *object_get_fourth_field(self + 0x4C) = 0x60241700;
    *object_get_fourth_field(self + 0x98) = 0x55F0C070;
    *object_get_fourth_field(self + 0x1B0) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x240) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0x1F8) = 0x80F0F0F0;
    *object_get_fourth_field(self + 0xE4) = 0x80F0F0F0;
    object_set_helper_result(self, D_001A8CFC[0] + 0x8710, 0x99);
    object_set_helper_result(self + 0x4C, D_001A8CFC[0] + 0x8710, 0x9A);
    object_set_helper_result(self + 0x98, D_001A8CFC[0] + 0x8710, 0x9B);
    hud_set_widget_field_b(self + 0x1B0, self + 0x120);
    hud_set_widget_field_b(self + 0x1F8, self + 0x160);
    hud_set_widget_field_b(self + 0x240, (void *)GetLocalizedString(0x2D4F));
    item_menu_set_title_mode((u8 *)self, 0);
    object_set_second_float4(self + 0xE4, 32.0f, 32.0f, 0.0f, 0.0f);
    menu_list_init(self + 0x298, argument);
    menu_list_set_spacing(self + 0x298, 0.0f, 40.0f);
    menu_list_set_icon_size(self + 0x298, 32.0f);
    *(int *)(self + 0x330) = 0;
    item_menu_update(self, 0);
}

/* Fills the menu's item list from a table of entries. */
void item_menu_fill_list(QwenRecovery_a2544d80ec96_AbiByte22 *menu, const QwenRecovery_a2544d80ec96_AbiByte22 *table)
{
    menu_list_build_ids(menu + 0x298, table);
}


/* Returns the id of the entry selected in the menu's list. */
int item_menu_get_selected_id(unsigned char *owner)
{
    return menu_list_get_selected_id(owner + 0x298);
}

/* Clears the state of the menu's list. */
void item_menu_clear_selection_state(unsigned char *owner)
{
    menu_list_clear_state(owner + 0x298);
}

/* Measured target: byte-identical across all 27 levels. */
/* Stores an extra value in the menu. */
void item_menu_set_extra_value(u8 *menu, s32 value) { *(s32 *)(menu + 0x330) = value; }

/* Measured target: byte-identical across all 27 levels. */
/* Returns the extra value stored in the menu. */
s32 item_menu_get_extra_value(u8 *menu) { return *(s32 *)(menu + 0x330); }

/* Sets which of the four title modes the menu uses and clears a field. */
void item_menu_set_title_mode(u8 *menu, u32 mode) {
    if (mode < 4) *(u32 *)(menu + 0x294) = mode;
    *(s32 *)(menu + 0x1a0) = 0;
}



/* func_00343638 is matched in 00343200-g8.c (-G8 small data). */
