#include "include_asm.h"

#include "common.h"
typedef u64 TI128 __attribute__((mode(TI)));
extern u8 *D_0018C0B0;
extern int func_0027F288(u8 *, int, float);
extern u64 func_0027C878(int);
extern void func_PAL_0027FB48(float, float, u64, u8 *, int, float, u64, u8 *);
extern u8 D_L08_00296CD0[];
extern u8 D_L08_001DB5E7;
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_L08_001B29E0 __attribute__((sda));
extern u8 *D_L08_001B29DC __attribute__((sda));
extern u8 *D_0018C0B0;

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_PAL_0027FB48 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void func_PAL_00280218(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_0027F288(text, length, scale) >> 1);
    fy = y;
    texture = func_0027C878(1);
    func_PAL_0027FB48(fx, fy, color, text, length, scale, texture, D_L08_00296CD0);
}


INCLUDE_ASM("asm/pal/game", func_PAL_002802D8);

INCLUDE_ASM("asm/pal/game", func_PAL_00280358);

extern int func_PAL_0027F790(u8 *, int, float);
extern u8 D_PAL_00263C70[];

/* Scaled FontPrintCenter: x is moved left by half the scaled text width, then
 * the text is drawn with font texture 1. func_PAL_0027FB48 is declared with its
 * integer and float parameters interleaved; each register bank keeps its
 * order, and the interleaving sets the order of the argument moves. */
void func_PAL_002803E8(int x, int y, u64 color, u8 *text, int length, float scale) {
    float fx, fy;
    u64 texture;

    fx = x - (func_PAL_0027F790(text, length, scale) >> 1);
    fy = y;
    texture = func_0027C878(2);
    func_PAL_0027FB48(fx, fy, color, text, length, scale, texture, D_PAL_00263C70);
}


INCLUDE_ASM("asm/pal/game", func_PAL_002804A8);

extern void func_PAL_002804A8(float);

void func_PAL_00280A30(void) {
    func_PAL_002804A8(1.0f);
}

