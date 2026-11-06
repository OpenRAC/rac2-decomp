#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned long u64;
extern u64 func_US2_0027CED8(int);
extern void func_US2_0027FCB0(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_00263B50[];

/* func_US2_0027FFF0 has no USA v1.01 twin: a wrapper like func_0027F980 that draws at a float
   position and scale through func_US2_0027FCB0, without subtracting the text width. */
void func_US2_0027FFF0(float x, float y, u64 color, u8 *text, int length, float scale) {
    u64 texture;

    texture = func_US2_0027CED8(1);
    func_US2_0027FCB0(x, y, color, text, length, scale, texture, D_00263B50);
}
