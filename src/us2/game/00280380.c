#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *D_0018C0B0;
extern int func_0027F288(u8 *, int, float);
extern u64 func_US2_0027CED8(int);
extern void func_US2_0027FCB0(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L08_00296CD0[];
extern u8 D_L08_001DB5E7;
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_0018C0B0;

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_US2_0027FCB0 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void func_US2_00280380(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_0027F288(text, length, scale) >> 1);
    fy = y;
    texture = func_US2_0027CED8(1);
    func_US2_0027FCB0(fx, fy, color, text, length, scale, texture, D_L08_00296CD0);
}


INCLUDE_ASM("asm/us2/game", func_US2_00280440);

INCLUDE_ASM("asm/us2/game", func_US2_002804C0);

INCLUDE_ASM("asm/us2/game", func_US2_00280550);

extern void func_US2_00280550(float);

void func_US2_00280B20(void) {
    func_US2_00280550(1.0f);
}

