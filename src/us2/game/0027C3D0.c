#include "include_asm.h"


extern void func_00284F40(int);
extern int D_001B1594 __attribute__((sda));
extern void func_0027BD70(void);

void func_US2_0027CAE0(void) {
    extern void func_00284F40(int);
    extern void func_0027BD70(void);
    extern int D_001B1594 __attribute__((sda));
    func_00284F40(0);
    D_001B1594 = 0x7F;
    func_0027BD70();
}

void func_002CBC58(int);
extern unsigned int func_00285850(void);
extern void func_002CBC58(int);
extern void func_002859C8(void);

void func_US2_0027CB08(void)
{
    if (func_00285850() == 1) {
        func_00284F40(0);
        D_001B1594 = 0x100FF;
        func_0027BD70();
    } else if (func_00285850() == 0) {
        func_002CBC58(1);
    }
    func_002859C8();
}

void func_US2_0027CB80(void)
{
  func_002CBC58(0);
  return;
}

