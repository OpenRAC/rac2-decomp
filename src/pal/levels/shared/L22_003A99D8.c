#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_003A99D8);

typedef unsigned char u8;
typedef float f32;
extern u8 D_001A63A8_4[];
extern u8 D_00189E20[];
extern f32 func_00282E48(void *a0, void *a1);
extern void func_L22_002B70F8(int a0, int a1, void *a2);
extern f32 func_002A7878(f32 low, f32 high);

void func_PAL_L22_003ABFB8(u8 *a0) {
    if (D_00189E20[0x22B4] != 0) return;
    if (func_00282E48(D_00189E20 + 0x80, a0 + 0x10) < 4.0f) {
        func_L22_002B70F8(2, 0x56, a0);
    }
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L22_003AF154);

