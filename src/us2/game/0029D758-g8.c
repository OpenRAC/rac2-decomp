#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int list_page_update(void *, int);

int func_US2_0029D758(int value) {
    if (D_001A8CFC != 0)
        return list_page_update(D_001A8CFC + 0x3F3F0, value);
    return 0;
}

extern void list_page_draw(void *);

void func_US2_0029D798(void) {
    if (D_001A8CFC != 0)
        list_page_draw(D_001A8CFC + 0x3F3F0);
}
