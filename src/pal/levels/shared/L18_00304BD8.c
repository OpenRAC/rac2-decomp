#include "include_asm.h"

#include "common.h"
extern u64 func_0027C878(int);
extern void func_PAL_0027FB48(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L18_00296510[];
extern u8 D_PAL_00296290[];

extern int func_0027F1D8(u8 *, int, u8 *, float);

/* func_PAL_L18_00304BD8, the level copy of func_PAL_0027F790: the same C, with this program's table. */
int func_PAL_L18_00304BD8(u8 *text, int length, float scale) {
    return func_0027F1D8(text, length, D_PAL_00296290, scale);
}

void func_PAL_L18_00305968(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_PAL_L18_00304BD8(text, length, scale) >> 1);
    fy = y;
    texture = func_0027C878(3);
    func_PAL_0027FB48(fx, fy, color, text, length, scale, texture, D_PAL_00296290);
}

