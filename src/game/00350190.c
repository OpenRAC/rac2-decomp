#include "common.h"
extern volatile int D_001AE7D8 __attribute__((sda));
extern char *D_001B23CC[] __attribute__((sda));
extern void func_00351FA0(unsigned char *);

int func_00350190(void)
{
    if (D_001AE7D8 != 0) {
        func_00351FA0(D_001B23CC[0] + 0xD9168);
        D_001AE7D8 = 0;
    }
    CpuSync();
    CpuEnableInt();
    return 0;
}
