#include "include_asm.h"

INCLUDE_ASM("asm/pal/game", func_PAL_002CC7B8);

#include "common.h"
extern int func_PAL_002D6710(int, char *);
extern char D_0025BA90[];
extern short D_0018A000[];
extern void func_0029CE80(void);

int func_PAL_002CC8C8(int mode)
{
    int result = 0;
    switch (mode) {
    case 0: D_0018A000[0] = 8; result = 1; break;
    case 1: result = func_PAL_002D6710(3, D_0025BA90); break;
    case 2: func_0029CE80(); result = 1; break;
    }
    return result;
}


INCLUDE_ASM("asm/pal/game", func_PAL_002CC950);

INCLUDE_ASM("asm/pal/game", func_PAL_002CCAC8);
