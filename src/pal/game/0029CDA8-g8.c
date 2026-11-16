#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int info_panel_update(void *, int);

int func_PAL_0029CDA8(int value) {
    if (g_resident_data_base != 0)
        return info_panel_update(g_resident_data_base + 0x3BB08, value);
    return 0;
}
