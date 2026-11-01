#include "include_asm.h"

typedef unsigned char u8;
extern u8 D_00139648;
extern u8 D_001A7A47 __attribute__((sda));
extern void func_002AEC48(void *a0, void *a1, int a2, float f12, float f13);
extern u8 D_00139568[];
extern u8 D_00239BA0[];
extern u8 D_001A7A60[] __attribute__((sda));

/* Stores the third argument (or 1.0f) in the object's float at 0x70, and, when the fifth argument
   is set and that float differs from the one at 0x20, calls func_002AEC48 with the object's two
   first arguments, the fourth argument and the pair 0.03f, 0.3f. */
void func_PAL_002B14F8(void *a0, float *a1, float f12, int a2, int a3)
{
    if (D_001A7A47 != 0) {
        a1[28] = f12;
    } else {
        a1[28] = 1.0f;
    }
    if (a3 != 0) {
        if (a1[28] != a1[8]) {
            func_002AEC48(a0, a1, a2, 0.0432f, 0.43200004f);
        }
    }
}


INCLUDE_ASM("asm/pal/game", func_PAL_002B1570);

void func_PAL_002B1588(int first, int second)
{
    extern int func_00288FB8(int);
    extern void func_0029CC98(int, int);
    func_0029CC98(func_00288FB8(first), second);
}

extern void func_0029CC50(int, int, int);

void func_PAL_002B15B8(int first, int second, int third) {
    func_0029CC50(first, second, third);
}

INCLUDE_ASM("asm/pal/game", func_PAL_002B15D8);
