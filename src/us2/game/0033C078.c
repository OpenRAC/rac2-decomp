#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

/* Sets the position offsets of the prompt bar texts. */
void prompt_bar_set_text_offsets_us2(u8 *object, f32 first_x, f32 first_y, f32 second_x, f32 second_y, f32 third_x, f32 third_y) {
    *(f32 *)(object + 0x2A8) = first_x;
    *(f32 *)(object + 0x2AC) = first_y;
    *(f32 *)(object + 0x2B8) = second_x;
    *(f32 *)(object + 0x2BC) = second_y;
    *(f32 *)(object + 0x2B0) = third_x;
    *(f32 *)(object + 0x2B4) = third_y;
}

/* Sets the three prompt texts of the prompt bar. */
void prompt_bar_set_texts_us2(int object, unsigned int first_text, unsigned int second_text, unsigned int third_text)
{
    hud_set_widget_field_b(object + 0x198, first_text);
    hud_set_widget_field_b(object + 0x248, second_text);
    hud_set_widget_field_b(object + 0x1F0, third_text);
}

/* Measured target: byte-identical across all 27 levels. */
void prompt_bar_set_spacing_us2(u8 *a0, f32 a1) { *(f32 *)(a0 + 0x2A4) = a1; }

extern void *F8b17817c_FUN_003361A8(char *block);
extern char *F8b17817c_FUN_00336968(char *block);
extern void *F8b17817c_FUN_003366D0(char *block);

/* Destroys all the widgets of the map screen. */
char *map_screen_destroy_us2(char *object)
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

