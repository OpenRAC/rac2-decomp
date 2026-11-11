#include "common.h"

INCLUDE_ASM("asm/kr/game", func_KR_0027FCA0);

void func_KR_002803B0(void) {
    extern void func_00284F40(int);
    extern void func_KR_0027FCA0(void);
    extern int D_001B1594 __attribute__((sda));
    func_00284F40(0);
    D_001B1594 = 0x7F;
    func_KR_0027FCA0();
}

extern unsigned int func_00285850(void);
extern void func_00284F40(int);
extern int D_001B1594 __attribute__((sda));
extern void func_KR_0027FCA0(void);
extern void func_KR_002D0E58(int);
extern void func_KR_0028AB78(void);

void func_KR_002803D8(void)
{
    if (func_00285850() == 1) {
        func_00284F40(0);
        D_001B1594 = 0x100FF;
        func_KR_0027FCA0();
    } else if (!func_00285850()) {
        func_KR_002D0E58(1);
    }
    func_KR_0028AB78();
}

void func_KR_00280450(void)
{
    func_KR_002D0E58(0);
}
