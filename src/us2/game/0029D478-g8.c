#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int simple_page_update(void *, int);

int func_US2_0029D478(int value) {
    if (D_001A8CFC != 0)
        return simple_page_update(D_001A8CFC + 0x3C7E8, value);
    return 0;
}

extern void two_toggle_b_draw(void *);

void func_US2_0029D4B8(void) {
    if (D_001A8CFC != 0)
        two_toggle_b_draw(D_001A8CFC + 0x3D1D8);
}

extern int two_toggle_b_update(void *, int);

int func_US2_0029D4E8(int value) {
    if (D_001A8CFC != 0)
        return two_toggle_b_update(D_001A8CFC + 0x3D1D8, value);
    return 0;
}
