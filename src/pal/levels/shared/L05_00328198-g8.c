#include "names.h"
/* func_PAL_L05_00328198, the PAL copy of func_L05_003263F8: the same store of value + 1,
   scaled to 50 Hz, with a new test that skips it while D_0018A000 is positive. */
typedef int s32;

extern short g_menu_command_flag[];
extern int g_level_counter __attribute__((sda));

void func_PAL_L05_00328198(int value) {
    if (g_menu_command_flag[0] <= 0) {
        g_level_counter = ((s32)(value + 1) * 5 + 2) / 6;
    }
}
