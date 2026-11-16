#include "names.h"
/* func_US2_002D5C08, the USA v2.00 copy of func_002D4FF0: the same C, without the store of -0x2BC
 * at 0x3C. */
#include "common.h"

extern s32 g_choice_slide_choice __attribute__((sda));
extern s32 g_choice_slide_values __attribute__((sda));
extern s8 g_menu_choice_number_source[];
extern s8 g_menu_choice_counter[];

s32 func_US2_002D5C08(s32 arg0) {
    s32 temp_a1;
    s32 idx;

    temp_a1 = *(s32 *)g_menu_choice_number_source;
    if (g_choice_slide_choice != temp_a1) {
        g_choice_slide_choice = temp_a1;
    }
    idx = temp_a1 * 4;
    (*(s32 *)((s8 *)(arg0) + (0x34))) = *(s32 *)((s8 *)&g_choice_slide_values + idx);
    *(s32 *)g_menu_choice_counter = temp_a1 + 1;
    return 0;
}
