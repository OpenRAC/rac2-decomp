#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern int func_PAL_00341C18(void *, int);

int func_PAL_0029D578(int value) {
    if (g_resident_data_base != 0)
        return func_PAL_00341C18(g_resident_data_base + 0x3A570, value);
    return 0;
}
