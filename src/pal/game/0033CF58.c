#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;

/* Sets the offsets of the prompt bar's three texts from its anchor. */
void prompt_bar_set_text_offsets_pal(u8 *bar, f32 first_x, f32 first_y, f32 second_x, f32 second_y, f32 third_x, f32 third_y) {
    *(f32 *)(bar + 0x2A8) = first_x;
    *(f32 *)(bar + 0x2AC) = first_y;
    *(f32 *)(bar + 0x2B8) = second_x;
    *(f32 *)(bar + 0x2BC) = second_y;
    *(f32 *)(bar + 0x2B0) = third_x;
    *(f32 *)(bar + 0x2B4) = third_y;
}

/* Sets the strings of the prompt bar's three texts. */
void prompt_bar_set_texts_pal(int object, unsigned int first_text, unsigned int second_text, unsigned int third_text)
{
    hud_set_widget_field_b(object + 0x198, first_text);
    hud_set_widget_field_b(object + 0x248, second_text);
    hud_set_widget_field_b(object + 0x1F0, third_text);
}

/* Measured target: byte-identical across all 27 levels. */
void prompt_bar_set_spacing_pal(u8 *a0, f32 a1) { *(f32 *)(a0 + 0x2A4) = a1; }

extern void *F8b17817c_FUN_003361A8(char *block);
extern char *F8b17817c_FUN_00336968(char *block);
extern void *F8b17817c_FUN_003366D0(char *block);

/* Destroys the map screen's sprites and texts and returns the screen. */
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

