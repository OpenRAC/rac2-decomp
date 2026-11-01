#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_003A1940);

INCLUDE_ASM("asm/pal/levels", func_PAL_L20_003A1B00);




#include "common.h"
extern void func_L20_0039F268(char *);
extern void func_L20_0039F560(char *);
extern void func_L20_0039F968(char *);

void func_PAL_L20_003A21A0(char *arg0) {
    func_L20_0039F268(arg0);
    func_L20_0039F560(arg0);
    func_L20_0039F968(arg0);
}

