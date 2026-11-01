#include "include_asm.h"

#include "common.h"
extern int D_L00_001B043C __attribute__((sda));
extern void func_L00_003B8138(void);

/* Writes the object's state byte (7 when arg0 is zero, 5 otherwise), lets the shared
 * updater run, then writes the caller's value in the object's slot - 10 when it is -1. */
void func_PAL_L00_003E38E8(int arg0, int arg1)
{
    char *p = (char *)D_L00_001B043C;
    int a = arg1;
    char *q;

    if (p == 0)
        return;
    q = *(char **)(p + 0x68);
    if (arg0 != 0)
        p[0x20] = 5;
    else
        p[0x20] = 7;
    func_L00_003B8138();
    if (a != -1)
        *(int *)(q + 0x20) = ((s32)(a) * 5 + 2) / 6;
    else
        *(int *)(q + 0x20) = 8;
}
