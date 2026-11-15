#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void func_002A7750(char *, int, int);
extern int func_L03_00419BD8(int, char *, char *);

/* hands an active entity a corrected world position: when its state check passes, switches it
   to state 7 and copies the position into its state block */
void func_L14_003C9658(char *entity, char *position)
{
    char *state;

    if (*(u8 *)(entity + 0x95) != 1)
        return;
    state = *(char **)(entity + 0x68);
    if (*(u8 *)(entity + 0x20) == 7)
        return;
    if (CheckPointsOnRouteGraph(*(s32 *)(state + 0x220), entity + 0x10, position) == 0)
        return;
    SetMobyState(entity, 7, -1);
    *(s32 *)(state + 0x37C) = 0x3C;
    *(TI128 *)(state + 0x340) = *(TI128 *)position;
}
