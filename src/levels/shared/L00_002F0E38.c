#include "include_asm.h"
#include "names.h"

typedef int s32;

extern s32 g_level_l24_word_a;

extern s32 g_level_l24_word_b;

typedef unsigned int u32;

extern u32 g_level_l24_word_c;

/* returns the signed word at 0x001be840 */
s32 level_get_word_a(void) {
 return g_level_l24_word_a;
}

/* returns the signed word at 0x001be888 */
s32 level_get_word_b(void) {
 return g_level_l24_word_b;
}

/* stores the provided word at 0x001be894 */
void level_set_word_c(u32 value) {
 g_level_l24_word_c=value;
}

extern short g_level_table_first_entry[];

/* Sets the first entry of a level table to zero. */
void level_clear_first_table_entry(void) {
    g_level_table_first_entry[0] = 0;
}
