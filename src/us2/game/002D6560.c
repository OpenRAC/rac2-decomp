#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int func_0029C3A0(int);

int menu_page_draw_with_pad_state_us2(void) {
    func_0029C3A0(g_menu_input_flags);
    return 0;
}

