#include "include_asm.h"

extern void func_00284EA8(void);
extern void func_US2_0027B988(void);

/* func_US2_00280FB8, the v2.00 copy of func_L00_002EA600: the same C with one call fewer. */
void func_US2_00280FB8(void) {
    func_00284EA8();
    func_US2_0027B988();
}
