#include "include_asm.h"
#include "names.h"

extern void func_3747B0(void);

void menu_call_update_us2(void) {
    func_3747B0();
}

extern int g_menu_dispatch_mode;

/* Dispatch on a mode word: mode 1 goes through the recording wrapper, the other modes replay. */
void menu_dispatch_by_mode_us2(void)
{
    switch (g_menu_dispatch_mode) {
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
