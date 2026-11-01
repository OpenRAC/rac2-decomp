#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L18_00304BD8);

#include "common.h"
extern int func_PAL_L18_00304BD8(u8 *, int, float);
extern u64 func_0027C878(int);
extern void func_PAL_0027FB48(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L18_00296510[];
extern u8 D_PAL_00296290[];

void func_PAL_L18_00305968(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_PAL_L18_00304BD8(text, length, scale) >> 1);
    fy = y;
    texture = func_0027C878(3);
    func_PAL_0027FB48(fx, fy, color, text, length, scale, texture, D_PAL_00296290);
}

