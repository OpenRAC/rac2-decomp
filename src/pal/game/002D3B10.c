#include "include_asm.h"
#include "names.h"

extern int g_menu_input_flags;
extern int g_menu_input_flags;
extern int func_0029C640(int);

/* Passes the menu input buttons on to the page handler. */
int menu_forward_pad_buttons_pal(void) {
    func_0029C640(g_menu_input_flags);
    return 0;
}

