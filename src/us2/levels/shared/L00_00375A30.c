#include "include_asm.h"

extern void func_3747B0(void);

void func_US2_L00_00375EA0(void) {
    func_3747B0();
}

extern int D_0022F810;

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
void func_US2_L00_00375EC0(void)
{
    switch (D_0022F810) {
    case 0:
        func_002F93B0();
        break;
    case 1:
        func_L00_00374B78();
        break;
    case 2:
        func_002F93B0();
        break;
    case 3:
        func_002F93B0();
        break;
    }
}
