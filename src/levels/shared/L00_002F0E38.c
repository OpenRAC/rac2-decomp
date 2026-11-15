#include "include_asm.h"
#include "names.h"

typedef int s32;

extern s32 D_L24_001BE840;

extern s32 D_L24_001BE888;

typedef unsigned int u32;

extern u32 D_L24_001BE894;

/* returns the signed word at 0x001be840 */
s32 level_get_word_a(void) {
 return D_L24_001BE840;
}

/* returns the signed word at 0x001be888 */
s32 level_get_word_b(void) {
 return D_L24_001BE888;
}

/* stores the provided word at 0x001be894 */
void level_set_word_c(u32 value) {
 D_L24_001BE894=value;
}

extern short D_L00_001BEF84[];

/* Sets the first entry of a level table to zero. */
void level_clear_first_table_entry(void) {
    D_L00_001BEF84[0] = 0;
}
