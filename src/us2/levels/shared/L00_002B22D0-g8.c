#include "names.h"
/* func_US2_L00_002B22D0, the v2.00 copy of func_L00_002B2200: the same C, where the call ids
 * move up four and the last call runs once, behind a byte at +0xAB of D_001395B8 that it
 * sets (as in PAL's func_PAL_L00_002B20F8, which also has 250 for 300). */
#include "common.h"

extern int g_collection_progress_flag;
extern int g_voice_line_cooldown __attribute__((sda));
extern u8 g_progress_flag;
extern u8 g_item_enabled_flags[] MACRO_ADDR;
extern u8 g_game_flag_table[];
extern int math_fast_float_d(char *);
extern int save_count_nonzero_flags(void);
extern int level_get_resident_byte(void);
extern void value_set_entry_by_index_us2(int, int);

void func_US2_L00_002B22D0(void)
{
    int count;
    int selector;
    int flag;
    u8 *state;

    if (g_collection_progress_flag == 0)
        return;
    if (math_fast_float_d((char *)&g_voice_line_cooldown) == 0)
        return;
    count = save_count_nonzero_flags();
    selector = level_get_resident_byte();
    flag = g_progress_flag;
    if (flag != 0 || selector > 0) {
        if (count == 3 || count == 10 || count == 15 || count == 19 || count == 25 || count == 29)
            value_set_entry_by_index_us2(0x1b90, -1);
        else if (count == 18 || count == 26)
            value_set_entry_by_index_us2(0x1b91, -1);
    }
    if (count == 7 || count == 20 || count == 30)
        value_set_entry_by_index_us2(0x1b93, -1);
    state = g_game_flag_table;
    if (state[0xAB] == 0) {
        if (g_item_enabled_flags[0] != 0) {
            value_set_entry_by_index_us2(0x1b93, -1);
            state[0xAB] = 1;
        }
    }
    g_collection_progress_flag = 0;
    g_voice_line_cooldown = 300;
}
