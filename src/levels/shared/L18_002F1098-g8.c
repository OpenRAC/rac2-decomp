#include "names.h"
/* True when the resident flag word is set or the stage byte is 4. */
typedef unsigned char u8;

extern int g_hero_frozen_flag;
extern u8 g_stage_flag_byte[];

/* Returns 1 when the flag word is set or the stage byte is 4. */
int level_is_stage_flag_or_four(void) {
    int result = 0;
    if (g_hero_frozen_flag != 0 || g_stage_flag_byte[0] == 4) {
        result = 1;
    }
    return result;
}
