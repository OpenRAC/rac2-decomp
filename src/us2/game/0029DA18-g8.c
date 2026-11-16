#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int func_US2_00340AA8(void *, int);

int func_US2_0029DA18(int value) {
    if (g_resident_data_base != 0)
        return func_US2_00340AA8(g_resident_data_base + 0x3A4C0, value);
    return 0;
}
