#include "include_asm.h"
#include "common.h"
extern void func_003384C0(char *, unsigned int, unsigned int, float, float, float, float);
extern s32 D_001A8CFC;

/* The renderer consumes all four FP bounds, unchanged by this setup. */
void func_US2_0029C448(s32 arg0, s32 arg1, float top, float bottom, float left, float right) {
    s32 a;
    s32 b;

    a = arg0;
    b = arg1;
    if (D_001A8CFC != 0) {
        func_003384C0((char *)(D_001A8CFC + 0x36F28), a, b, top, bottom, left, right);
    }
}
