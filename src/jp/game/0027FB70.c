#include "common.h"

INCLUDE_ASM("asm/jp/game", func_JP_0027FB70);

void func_JP_00280280(void) {
    extern void func_00284F40(int);
    extern void func_JP_0027FB70(void);
    extern int D_001B1594 __attribute__((sda));
    func_00284F40(0);
    D_001B1594 = 0x7F;
    func_JP_0027FB70();
}

extern unsigned int func_00285850(void);
extern void func_00284F40(int);
extern int D_001B1594 __attribute__((sda));
extern void func_JP_0027FB70(void);
extern void func_JP_002D0198(int);
extern void func_JP_00289E68(void);

void func_JP_002802A8(void)
{
    if (func_00285850() == 1) {
        func_00284F40(0);
        D_001B1594 = 0x100FF;
        func_JP_0027FB70();
    } else if (!func_00285850()) {
        func_JP_002D0198(1);
    }
    func_JP_00289E68();
}

void func_JP_00280320(void)
{
    func_JP_002D0198(0);
}
