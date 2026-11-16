#include "common.h"

/* func_PAL_002D17F0, the PAL copy of func_002D08C8: the same C, without the
   second flag test; the last store goes to element 2 instead of 3. */

extern int g_resident_data_base;
extern int ref_002D08C8_01 __attribute__((sda));
extern int g_menu_unlock_flags[];
extern int g_extras_entries_unlocked[4] __attribute__((sda));
extern unsigned char g_extras_unlocked_flag;

int func_PAL_002D17F0(void)
{
    if (g_resident_data_base != 0) {
        g_menu_unlock_flags[0] = 1;
        if (ref_002D08C8_01 != 0)
            g_extras_entries_unlocked[1] = 1;
        if (g_extras_unlocked_flag != 0) {
            g_extras_entries_unlocked[0] = 1;
            g_extras_entries_unlocked[2] = 1;
        }
    }
    return 0;
}
