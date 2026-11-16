#include "names.h"
/* func_US2_002D5C08, the USA v2.00 copy of func_002D4FF0: the same C, without the store of -0x2BC
 * at 0x3C. */
#include "common.h"

extern s32 g_choice_slide_choice __attribute__((sda));
extern s32 g_choice_slide_values __attribute__((sda));
extern s8 g_menu_choice_number_source[];
extern s8 g_menu_choice_counter[];

/* Starts a choice slide: remembers the current choice, copies its value into the menu and advances the counter. (USA v2.00) */
s32 menu_choice_slide_init_us2(s32 menu) {
    s32 choice;
    s32 offset;

    choice = *(s32 *)g_menu_choice_number_source;
    if (g_choice_slide_choice != choice) {
        g_choice_slide_choice = choice;
    }
    offset = choice * 4;
    (*(s32 *)((s8 *)(menu) + (0x34))) = *(s32 *)((s8 *)&g_choice_slide_values + offset);
    *(s32 *)g_menu_choice_counter = choice + 1;
    return 0;
}
