#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int selection_menu_update_layout(void *, int, int);

int func_US2_0029D080(int first, int second)
{
    if (D_001A8CFC != 0)
        return selection_menu_update_layout(D_001A8CFC + 0x39AF0, first, second);
    return 0;
}

extern int mission_screen_place_parts(void *, int);

int func_US2_0029D0C8(int value) {
    if (D_001A8CFC != 0)
        return mission_screen_place_parts(D_001A8CFC + 0x3B418, value);
    return 0;
}
