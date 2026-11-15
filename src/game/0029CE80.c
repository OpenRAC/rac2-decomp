#include "include_asm.h"
#include "names.h"

extern int D_001A79F0 __attribute__((sda));
extern void func_00288CB0(int, int);

/* Picks a number based on the current level (9 or 18 for two levels, else 0) and passes it on. */
void func_0029CE80(void)
{
    int value = 0;
    switch (gCurrentMapIndex) {
    case 22: value = 9; break;
    case 23: value = 18; break;
    }
    SetSmallDataValueAndRefresh(value, 1);
}
