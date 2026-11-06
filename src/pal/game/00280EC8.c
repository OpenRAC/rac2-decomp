#include "include_asm.h"

/* func_PAL_00280EC8, the PAL copy of func_L00_002EA600: the same C without the last call. */
extern void func_00284EA8(void);
extern void func_PAL_0027B810(void);

void func_PAL_00280EC8(void) {
    func_00284EA8();
    func_PAL_0027B810();
}

