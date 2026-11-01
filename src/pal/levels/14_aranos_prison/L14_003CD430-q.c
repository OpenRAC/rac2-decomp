#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void func_002A7750(char *, int, int);
extern int func_L03_00419BD8(int, char *, char *);

/* hands an active entity a corrected world position: when its state check passes, switches it
   to state 7 and copies the position into its state block */
void func_PAL_L14_003CD430(char *entity, char *position)
{
    char *state;

    if (*(u8 *)(entity + 0x95) != 1)
        return;
    state = *(char **)(entity + 0x68);
    if (*(u8 *)(entity + 0x20) == 7)
        return;
    if (func_L03_00419BD8(*(s32 *)(state + 0x220), entity + 0x10, position) == 0)
        return;
    func_002A7750(entity, 7, -1);
    *(s32 *)(state + 0x37C) = 0x32;
    *(TI128 *)(state + 0x340) = *(TI128 *)position;
}
