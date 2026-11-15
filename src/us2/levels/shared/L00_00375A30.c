#include "include_asm.h"
#include "names.h"

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
        UpdateShopMenuInput();
        break;
    case 1:
        menu_call_update();
        break;
    case 2:
        UpdateShopMenuInput();
        break;
    case 3:
        UpdateShopMenuInput();
        break;
    }
}
