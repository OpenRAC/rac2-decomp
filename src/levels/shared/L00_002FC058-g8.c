#include "names.h"
/* func_L00_002FC058 (184 bytes, 27 levels): a small state machine. State 1 arms the
   counter from the saved word; state 2 counts it down, runs the two hooks when
   func_L00_002FC018 says so, and otherwise advances or resets on the 0x10 pad flag.
   The empty case 0 gives retail's slti dispatch. */
#include "common.h"

extern int ref_L00_002FC058_00 __attribute__((sda));
extern int ref_L00_002FC058_01 __attribute__((sda));
extern int ref_L00_002FC058_02 __attribute__((sda));
extern char g_pad_pressed_flags[];

extern int level_get_flag_d(void);
extern void level_clear_flag_e(void);
extern void level_clear_flag_f(void);

void level_update_countdown_state_machine(void)
{
    switch (ref_L00_002FC058_00) {
    case 0:
        break;
    case 1:
        ref_L00_002FC058_00 = 2;
        ref_L00_002FC058_02 = ref_L00_002FC058_01;
        break;
    case 2:
        ref_L00_002FC058_02 = ref_L00_002FC058_02 - 1;
        if (level_get_flag_d() != 0) {
            level_clear_flag_e();
            level_clear_flag_f();
        } else if (ref_L00_002FC058_02 == 0) {
            if (*(int *)g_pad_pressed_flags & 0x10)
                ref_L00_002FC058_00++;
            else
                ref_L00_002FC058_00 = 0;
        } else if ((*(int *)g_pad_pressed_flags & 0x10) == 0) {
            ref_L00_002FC058_00 = 0;
        }
        break;
    }
}
