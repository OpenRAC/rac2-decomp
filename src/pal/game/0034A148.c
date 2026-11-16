#include "include_asm.h"
#include "names.h"



typedef int s32;
typedef unsigned char u8;

void menu_set_settings_pal(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0xB8) = a1; *(s32 *)(a0 + 0xBC) = a2; }

/* Stores a word at offset 0xC8 of the menu. (PAL) */
void menu_set_field_c8_pal(int menu, unsigned int value)
{
  *(unsigned int *)(menu + 0xC8) = value;
  return;
}

typedef float f32;

/* Sets the menu position (x, y) and clears the next two words. (PAL) */
void menu_set_position_pal(u8 *menu,f32 x,f32 y) {
 (*(f32 **)(menu+0x5C))[0]=x;
 (*(f32 **)(menu+0x5C))[1]=y;
 (*(s32 **)(menu+0x5C))[2]=0;
 (*(s32 **)(menu+0x5C))[3]=0;
}

/* Measured target: byte-identical across all 27 levels. */
void menu_set_selected_index_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x60) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void menu_set_field_bc_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0xCC) = a1; }

extern int menu_get_selected_index(unsigned char *);

/* Measured target: byte-identical across all 27 levels. */
s32 menu_get_selected_index_pal(u8 *a0) { return *(s32 *)(a0 + 0x60); }

/* Measured target: byte-identical across all 27 levels. */
s32 menu_get_entry_count_pal(u8 *a0) { return *(s32 *)(a0 + 0xC0); }


extern void *Faac80289_FUN_003361A8(char *p);
extern char *Faac80289_FUN_00336968(char *p);

/* Initializes the menu's seven widgets and seven text rows and returns the menu. (PAL) */
char *menu_init_seven_labels_pal(char *menu)
{
    char *row = menu + 536;
    int i;

    Faac80289_FUN_003361A8(menu);
    Faac80289_FUN_003361A8(menu + 76);
    Faac80289_FUN_003361A8(menu + 152);
    Faac80289_FUN_003361A8(menu + 228);
    Faac80289_FUN_003361A8(menu + 304);
    Faac80289_FUN_003361A8(menu + 380);
    Faac80289_FUN_003361A8(menu + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(row);
        row += 88;
    }
    return menu;
}

/* Measured target: byte-identical across all 27 levels. */
void menu_set_field_448_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4B8) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void menu_set_field_44c_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4BC) = a1; }

