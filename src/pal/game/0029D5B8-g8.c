#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void radial_menu_draw(void *);

void func_PAL_0029D5B8(void) {
    if (D_001A8CFC != 0)
        radial_menu_draw(D_001A8CFC + 0x3A570);
}

extern void msg_box_init_localized(void *, int, int, int);

void func_PAL_0029D5E8(int a0, int a1, int a2) { if (D_001A8CFC != 0) msg_box_init_localized(D_001A8CFC + 0x36F28, a0, a1, a2); }

extern void msg_box_init_short(void *, int, int);

void func_PAL_0029D630(int first, int second) {
    if (D_001A8CFC != 0)
        msg_box_init_short(D_001A8CFC + 0x36F28, first, second);
}
