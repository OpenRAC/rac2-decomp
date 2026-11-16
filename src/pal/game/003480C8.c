#include "include_asm.h"
#include "names.h"





extern void Fd1c2476b_FUN_00336320(char *p);
extern void Fd1c2476b_FUN_00336A78(char *p);
extern void Fd1c2476b_FUN_003462A8(char *p);
extern void Fd1c2476b_FUN_003463C8(char *p);
extern void Fd1c2476b_FUN_003464D0(char *p);

/* func_00345F70 is built from 00345358-layout-g8.c. */

/* func_003462A8 is built from 00345358-descriptor-g8.c for small-data access. */

/* func_003463C8 and func_003464D0 are built from 00345358-g8.c for small-data access. */


/* Draws the large menu screen parts when the menu is active. (PAL) */
void menu_screen_large_draw_parts_pal(char *menu)
{
    if (*(int *)(menu + 1272) == 0)
        return;
    Fd1c2476b_FUN_00336320(menu);
    Fd1c2476b_FUN_00336320(menu + 76);
    Fd1c2476b_FUN_00336320(menu + 152);
    Fd1c2476b_FUN_00336320(menu + 228);
    Fd1c2476b_FUN_00336A78(menu + 456);
    Fd1c2476b_FUN_003462A8(menu);
    Fd1c2476b_FUN_003463C8(menu);
    Fd1c2476b_FUN_003464D0(menu);
    Fd1c2476b_FUN_00336320(menu + 380);
    Fd1c2476b_FUN_00336A78(menu + 784);
    Fd1c2476b_FUN_00336A78(menu + 696);
    Fd1c2476b_FUN_00336A78(menu + 872);
    Fd1c2476b_FUN_00336A78(menu + 960);
    Fd1c2476b_FUN_00336A78(menu + 1048);
}


extern void *F5a9e4f98_FUN_003361A8(char *p);
extern void *F5a9e4f98_FUN_003363D0(char *p);
extern char *F5a9e4f98_FUN_00336968(char *p);
extern void *F5a9e4f98_FUN_003366D0(char *p);

/* Initializes the large menu screen parts and returns the menu. (PAL) */
void *menu_screen_large_init_parts_pal(char *menu)
{
    F5a9e4f98_FUN_003361A8(menu);
    F5a9e4f98_FUN_003361A8(menu + 0x4c);
    F5a9e4f98_FUN_003361A8(menu + 0x98);
    F5a9e4f98_FUN_003361A8(menu + 0xe4);
    F5a9e4f98_FUN_003361A8(menu + 0x130);
    F5a9e4f98_FUN_003361A8(menu + 0x17c);
    F5a9e4f98_FUN_003363D0(menu + 0x1c8);
    F5a9e4f98_FUN_00336968(menu + 0x210);
    F5a9e4f98_FUN_00336968(menu + 0x268);
    F5a9e4f98_FUN_00336968(menu + 0x2C0);
    F5a9e4f98_FUN_00336968(menu + 0x318);
    F5a9e4f98_FUN_00336968(menu + 0x370);
    F5a9e4f98_FUN_003366D0(menu + 0x3C8);
    F5a9e4f98_FUN_003361A8(menu + 0x404);
    F5a9e4f98_FUN_003361A8(menu + 0x450);
    F5a9e4f98_FUN_003361A8(menu + 0x49C);

    return menu;
}


extern float *object_get_first_field(char *);
typedef unsigned char u8;
extern void object_set_first_float4(char *, float, float, float, float);
typedef struct { int x; int y; } MenuLabelOffset;
typedef struct { short a, b, c, id, e; } MenuGridEntry;
extern MenuGridEntry g_menu_item_table_first[];
extern u8 g_item_owned_flags[] __attribute__((section(".sdata")));
extern u8 g_movie_seen_flags[] __attribute__((section(".sdata")));
extern MenuLabelOffset ref_003472B8_00;
extern void object_set_flag_value(void *, int);
extern void object_set_flag_value(void *, int);

/* Updates the two small labels of the selected grid entry from its seen flags and positions them from the menu origin. (PAL) */
void UpdateMenuGridLabels_pal(char *menu)
{
    MenuLabelOffset label_offset;
    char *first_label;
    char *second_label;
    float x, y, second_x, second_y;
    u8 *flags;
    int bits;
    int index = g_menu_item_table_first[*(int *)(menu + 0x574) + *(int *)(menu + 0x578) * 4].id;

    if (g_item_owned_flags[index] == 0)
        return;
    first_label = menu + 0x318;
    label_offset = ref_003472B8_00;
    flags = &g_movie_seen_flags[index];
    second_label = menu + 0x370;
    bits = flags[0] & 4;
    object_set_flag_value(first_label, (flags[0] & 1) | (bits != 0));
    {
        int bits_b = flags[0] & 0x10;
        object_set_flag_value(second_label, bits_b != 0);
    }
    x = (*(float **)(menu + 0x4E8))[0] + object_get_first_field(first_label)[0] + (float)label_offset.x;
    y = (*(float **)(menu + 0x4E8))[1] + object_get_first_field(first_label)[1] + (float)label_offset.y;
    object_set_first_float4(first_label, x, y, 0.0f, 0.0f);
    second_x = (*(float **)(menu + 0x4E8))[0] + object_get_first_field(second_label)[0] + (float)label_offset.x;
    second_y = (*(float **)(menu + 0x4E8))[1] + object_get_first_field(second_label)[1] + (float)label_offset.y;
    object_set_first_float4(second_label, second_x, second_y, 0.0f, 0.0f);
}



