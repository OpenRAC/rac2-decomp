#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern void *object_construct_derived_a(void *);
extern char *hud_construct_widget_base(char *);
extern void *object_construct_derived_b(void *);
extern void *object_construct_derived_c(void *);
extern void *object_construct_derived_a(void *);
extern char *hud_construct_widget_base(char *);
extern void *object_construct_derived_b(void *);
extern void *object_construct_derived_c(void *);

/* Constructs the six widgets of the small menu and returns the menu pointer (PAL). */
u8 *small_menu_construct_pal(u8 *self)
{
    object_construct_derived_a(self);
    object_construct_derived_a(self + 76);
    hud_construct_widget_base((char *)self + 152);
    object_construct_derived_a(self + 240);
    object_construct_derived_b(self + 316);
    object_construct_derived_c(self + 388);
    return self;
}


typedef struct {
    char reserved00[6];
    short value;
    char reserved08[2];
} MenuEntry;
extern MenuEntry D_001FCE0[];
extern int snd_play_from_global_bank(int, unsigned int, void *);
extern void *memset(void *, int, unsigned int);
extern void object_set_first_float4(void *, float, float, float, float);

/* func_00340D68 is in 0033F030-grid-g8.c. */

/* Moves the selection of a menu grid and keeps the selected entry's value at
   0x214: the buttons 0x1000 and 0x4000 step the row (0x208, wrapping at the row
   count at 0x210), 0x8000 and 0x2000 the column (0x204, wrapping at 0x20C). A
   step down is stored, read back and stored again after the wrap test. */
int grid_menu_update_selection_pal(char *self, unsigned int buttons, MenuEntry *table)
{
    float offset[2];
    memset(offset, 0, 8);
    if (table) {
        float *position;
        *(int *)(self + 0x224) = 0;
        position = *(float **)(self + 0x1C0);
        object_set_first_float4(self, offset[0] + position[0], offset[1] + position[1], 0.0f, 0.0f);
        if (buttons & 0x1000) {
            int n;
            snd_play_from_global_bank(3, 0, 0);
            *(int *)(self + 0x218) -= 1;
            n = *(int *)(self + 0x218);
            if (n < 0) n = *(int *)(self + 0x220) - 1;
            *(int *)(self + 0x218) = n;
        } else if (buttons & 0x4000) {
            int n;
            snd_play_from_global_bank(3, 0, 0);
            n = *(int *)(self + 0x218) + 1;
            *(int *)(self + 0x218) = n < *(int *)(self + 0x220) ? n : 0;
        } else if (buttons & 0x8000) {
            int n;
            snd_play_from_global_bank(3, 0, 0);
            *(int *)(self + 0x214) -= 1;
            n = *(int *)(self + 0x214);
            if (n < 0) n = *(int *)(self + 0x21C) - 1;
            *(int *)(self + 0x214) = n;
        } else if (buttons & 0x2000) {
            int n;
            snd_play_from_global_bank(3, 0, 0);
            n = *(int *)(self + 0x214) + 1;
            *(int *)(self + 0x214) = n < *(int *)(self + 0x21C) ? n : 0;
        }
        *(int *)(self + 0x224) = table[*(int *)(self + 0x214) + *(int *)(self + 0x218) * *(int *)(self + 0x21C)].value;
    }
    return 0;
}


extern char *func_L00_0042BAD0_6(u8 *);
extern char *func_L00_0042BFF8_5(u8 *);
extern char *func_L00_0042C290_6(u8 *);
extern unsigned long long func_00347EA0_1(u8 *);

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
u8 *tab_menu_construct_pal(u8 *self) {
    func_L00_0042BAD0_6(self);
    func_L00_0042BAD0_6(self + 76);
    func_L00_0042BAD0_6(self + 152);
    func_L00_0042BAD0_6(self + 228);
    func_L00_0042BAD0_6(self + 304);
    func_L00_0042BFF8_5(self + 380);
    func_L00_0042C290_6(self + 464);
    func_00347EA0_1(self + 568);
    return self;
}

typedef int s32;

/* stores three consecutive words; byte-identical across all 27 levels. */
/* Stores the three record tables of the tab menu (PAL). */
void tab_menu_set_tables_pal(u8 *self, s32 table_a, s32 table_b, s32 table_c) { *(s32 *)(self + 0x310) = table_a; *(s32 *)(self + 0x314) = table_b; *(s32 *)(self + 0x318) = table_c; }

/* Measured target: byte-identical across all 27 levels. */
/* Sets whether the tab menu is enabled (PAL). */
void tab_menu_set_enabled_pal(u8 *self, s32 enabled) { *(s32 *)(self + 0x230) = enabled; }

