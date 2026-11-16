#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

void prompt_bar_set_text_offsets_pal(u8 *a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, f32 a6) {
    *(f32 *)(a0 + 0x2A8) = a1;
    *(f32 *)(a0 + 0x2AC) = a2;
    *(f32 *)(a0 + 0x2B8) = a3;
    *(f32 *)(a0 + 0x2BC) = a4;
    *(f32 *)(a0 + 0x2B0) = a5;
    *(f32 *)(a0 + 0x2B4) = a6;
}

void prompt_bar_set_texts_pal(int object, unsigned int a1, unsigned int a2, unsigned int a3)
{
    hud_set_widget_field_b(object + 0x198, a1);
    hud_set_widget_field_b(object + 0x248, a2);
    hud_set_widget_field_b(object + 0x1F0, a3);
}

/* Measured target: byte-identical across all 27 levels. */
void prompt_bar_set_spacing_pal(u8 *a0, f32 a1) { *(f32 *)(a0 + 0x2A4) = a1; }

extern void *F8b17817c_FUN_003361A8(char *block);
extern char *F8b17817c_FUN_00336968(char *block);
extern void *F8b17817c_FUN_003366D0(char *block);

char *map_screen_destroy_pal(char *object)
{
    int index;
    char *block;

    F8b17817c_FUN_003361A8(object);
    F8b17817c_FUN_003361A8(object + 76);
    F8b17817c_FUN_003361A8(object + 152);
    block = object + 228;
    for (index = 2; index != -1; index--) {
        F8b17817c_FUN_003361A8(block);
        block += 76;
    }
    F8b17817c_FUN_00336968(object + 472);
    F8b17817c_FUN_00336968(object + 560);
    F8b17817c_FUN_00336968(object + 648);
    F8b17817c_FUN_003366D0(object + 736);
    F8b17817c_FUN_003366D0(object + 796);
    return object;
}

