#include "include_asm.h"

extern char *D_001A8CFC;
extern int D_001A9A50 __attribute__((sda));
extern int D_001A9A54 __attribute__((sda));
extern int D_001A8C64;
extern short D_0018A000[];
extern void func_PAL_0033C600(void *);

/* func_PAL_0029C820, the PAL copy of func_0029BEB8: the same C with one more
   test, D_0018A000[0] (the halfword counter other units set to 8) must be zero,
   and the callee becomes func_PAL_0033C600 at offset 0x3F860. */
void func_PAL_0029C820(void) {
    if (D_001A9A50 != 0 && D_0018A000[0] == 0 && D_001A8C64 == 0 && D_001A9A54 != 0 && D_001A8CFC != 0)
        func_PAL_0033C600(D_001A8CFC + 0x3F860);
}
