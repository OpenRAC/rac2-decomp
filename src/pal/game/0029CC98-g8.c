#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int list_screen_layout(void *, int);

int func_PAL_0029CC98(int value) {
    if (D_001A8CFC != 0)
        return list_screen_layout(D_001A8CFC + 0x3B030, value);
    return 0;
}

extern void list_screen_draw(void *);

void func_PAL_0029CCD8(void) {
    if (D_001A8CFC != 0)
        list_screen_draw(D_001A8CFC + 0x3B030);
}

extern void map_screen_draw(void *);

void func_PAL_0029CD08(void) {
    if (D_001A8CFC != 0)
        map_screen_draw(D_001A8CFC + 0x3B7A8);
}
