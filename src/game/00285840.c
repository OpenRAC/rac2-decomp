#include "include_asm.h"
#include "names.h"

/* Owner-reviewed Qwen backlog: observed operations, not recovered original object boundaries. */

/* func_00285840: owner ABI/declaration review retained. */
/* extern declaration for global variable referenced in func_00285840 */
extern unsigned int D_001BACC0;

/* func_00285850: owner ABI/declaration review retained. */
extern unsigned int D_001BAD08;

/* func_002858B0: owner ABI/declaration review retained. */
extern int D_001BAD14;

/* Returns the saved menu state value. */
unsigned int func_00285840(void)
{
    return D_001BACC0;
}

/* Returns the second saved menu value. */
unsigned int func_00285850(void)
{
    return D_001BAD08;
}

extern int func_002B49C8(int);
extern void func_00132B28(int);
extern void func_002B7320(void);
extern void func_00132028(void);
extern void func_002B8518(void);

/* Ends the menu: undoes the pause sounds when needed and clears the saved menu state. */
void func_00285860(void)
{
    if (IsCurrentRequestSlot(3) == 0) {
        SendSoundCommand23(0x5D);
        music_Unpause();
        snd_Pump();
    }
    ClearPadPortState();
    D_001BACC0 = 0;
}

/* Stores a number into a global menu setting. */
void func_002858B0(int value)
{
  D_001BAD14 = value;
}

/* func_002859C8 is defined in 002859C8-panel-g8.c. */


