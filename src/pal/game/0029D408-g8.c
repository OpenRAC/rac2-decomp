#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int list_menu_update(void *, int);

int func_PAL_0029D408(int value) {
    if (D_001A8CFC != 0)
        return list_menu_update(D_001A8CFC + 0x3E810, value);
    return 0;
}

extern void menu_draw_if_active(void *);

void func_PAL_0029D448(void) {
    if (D_001A8CFC != 0)
        menu_draw_if_active(D_001A8CFC + 0x3E810);
}

extern int list_menu_set_selection(void *, int);

int func_PAL_0029D478(int value) {
    if (D_001A8CFC != 0)
        return list_menu_set_selection(D_001A8CFC + 0x3EA78, value);
    return 0;
}

extern void small_list_menu_draw_rows(void *);

void func_PAL_0029D4B8(void) {
    if (D_001A8CFC != 0)
        small_list_menu_draw_rows(D_001A8CFC + 0x3EA78);
}

extern void UpdateBoltCounter(void);

void func_PAL_0029D4F0(void) {
    if (D_001A8CFC != 0)
        UpdateBoltCounter();
}

extern void DrawBoltCounterDeltas(void);

void func_PAL_0029D518(void) {
    if (D_001A8CFC != 0)
        DrawBoltCounterDeltas();
}
