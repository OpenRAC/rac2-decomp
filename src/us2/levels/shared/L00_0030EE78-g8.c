#include "include_asm.h"
#include "names.h"
extern int D_L00_001A904C;
extern void UpdateBoltCounter(int);
extern int D_L00_001A904C;

void func_US2_L00_0030EE78(int argument)
{
    if (D_L00_001A904C != 0) {
        UpdateBoltCounter(argument);
    }
}
