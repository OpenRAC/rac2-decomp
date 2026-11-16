#include "include_asm.h"
#include "names.h"



typedef int s32;
typedef unsigned char u8;

void menu_set_settings_pal(u8 *a0, s32 a1, s32 a2) { *(s32 *)(a0 + 0xB8) = a1; *(s32 *)(a0 + 0xBC) = a2; }

void func_PAL_0034A2B0(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0xC8) = param_2;
  return;
}

typedef float f32;

void menu_set_position_pal(u8 *a0,f32 f0,f32 f1) {
 (*(f32 **)(a0+0x5C))[0]=f0;
 (*(f32 **)(a0+0x5C))[1]=f1;
 (*(s32 **)(a0+0x5C))[2]=0;
 (*(s32 **)(a0+0x5C))[3]=0;
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

char *menu_init_seven_labels_pal(char *a0)
{
    char *p = a0 + 536;
    int i;

    Faac80289_FUN_003361A8(a0);
    Faac80289_FUN_003361A8(a0 + 76);
    Faac80289_FUN_003361A8(a0 + 152);
    Faac80289_FUN_003361A8(a0 + 228);
    Faac80289_FUN_003361A8(a0 + 304);
    Faac80289_FUN_003361A8(a0 + 380);
    Faac80289_FUN_003361A8(a0 + 456);

    for (i = 6; i != -1; i--) {
        Faac80289_FUN_00336968(p);
        p += 88;
    }
    return a0;
}

/* Measured target: byte-identical across all 27 levels. */
void menu_set_field_448_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4B8) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void menu_set_field_44c_pal(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x4BC) = a1; }

