#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int UpdateFourOptionMenuInput(void *, int);

int func_US2_0029D528(int value) {
    if (D_001A8CFC != 0)
        return UpdateFourOptionMenuInput(D_001A8CFC + 0x3D4B8, value);
    return 0;
}

extern void four_option_menu_draw(void *);

void func_US2_0029D568(void) {
    if (D_001A8CFC != 0)
        four_option_menu_draw(D_001A8CFC + 0x3D4B8);
}

extern int two_toggle_a_update(void *, int);

int func_US2_0029D598(int value) {
    if (D_001A8CFC != 0)
        return two_toggle_a_update(D_001A8CFC + 0x3D798, value);
    return 0;
}

extern void two_toggle_a_draw(void *);

void func_US2_0029D5D8(void) {
    if (D_001A8CFC != 0)
        two_toggle_a_draw(D_001A8CFC + 0x3D798);
}

extern int single_toggle_a_update(void *, int);

int func_US2_0029D608(int value) {
    if (D_001A8CFC != 0)
        return single_toggle_a_update(D_001A8CFC + 0x3DDE8, value);
    return 0;
}

extern void single_toggle_a_draw(void *);

void func_US2_0029D648(void) {
    if (D_001A8CFC != 0)
        single_toggle_a_draw(D_001A8CFC + 0x3DDE8);
}

extern int screen_adjust_menu_update(void *, int);

int func_US2_0029D678(int value) {
    if (D_001A8CFC != 0)
        return screen_adjust_menu_update(D_001A8CFC + 0x3E0C8, value);
    return 0;
}

extern void onoff_menu_draw_with_help(void *);

void func_US2_0029D6B8(void) {
    if (D_001A8CFC != 0)
        onoff_menu_draw_with_help(D_001A8CFC + 0x3E0C8);
}

extern int onoff_menu_update(void *, int);

int func_US2_0029D6E8(int value) {
    if (D_001A8CFC != 0)
        return onoff_menu_update(D_001A8CFC + 0x3E3A8, value);
    return 0;
}

extern void onoff_menu_draw(void *);

void func_US2_0029D728(void) {
    if (D_001A8CFC != 0)
        onoff_menu_draw(D_001A8CFC + 0x3E3A8);
}
