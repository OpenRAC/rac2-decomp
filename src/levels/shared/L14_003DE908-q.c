#include "include_asm.h"
#include "common.h"

extern int func_L00_00324120(char *object);
extern int func_002761F8(void *a, void *b, int mode, void *self, int flag);
extern char D_00189EA0[];
extern int ref_L14_003DE908_00;

int func_L14_003DE908(char *a0)
{
    char buf[0x20];

    if (func_L00_00324120(a0) != 0)
        return 1;
    qcopy(buf, D_00189EA0);
    qcopy(buf + 0x10, D_00189EA0);
    *(float *)(buf + 0x18) = *(float *)(buf + 0x18) - 3.0f;
    if (CollLine(buf, buf + 0x10, 0x10, 0, 0) != 0 && ref_L14_003DE908_00 == (int)a0)
        return 1;
    return 0;
}
