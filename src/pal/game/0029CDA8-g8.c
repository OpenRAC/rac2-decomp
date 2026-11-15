#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern int info_panel_update(void *, int);

int func_PAL_0029CDA8(int value) {
    if (D_001A8CFC != 0)
        return info_panel_update(D_001A8CFC + 0x3BB08, value);
    return 0;
}
