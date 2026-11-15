/* func_L00_002FC058 (184 bytes, 27 levels): a small state machine. State 1 arms the
   counter from the saved word; state 2 counts it down, runs the two hooks when
   func_L00_002FC018 says so, and otherwise advances or resets on the 0x10 pad flag.
   The empty case 0 gives retail's slti dispatch. */
#include "common.h"

extern int ref_L00_002FC058_00 __attribute__((sda));
extern int ref_L00_002FC058_01 __attribute__((sda));
extern int ref_L00_002FC058_02 __attribute__((sda));
extern char D_00138320[];

extern int func_L00_002FC018(void);
extern void func_L00_002FC020(void);
extern void func_L00_002FC028(void);

void func_L00_002FC058(void)
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
        if (GetLevelFlagD() != 0) {
            ClearLevelFlagE();
            ClearLevelFlagF();
        } else if (ref_L00_002FC058_02 == 0) {
            if (*(int *)D_00138320 & 0x10)
                ref_L00_002FC058_00++;
            else
                ref_L00_002FC058_00 = 0;
        } else if ((*(int *)D_00138320 & 0x10) == 0) {
            ref_L00_002FC058_00 = 0;
        }
        break;
    }
}
