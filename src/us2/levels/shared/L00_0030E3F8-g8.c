#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int func_US2_00349728(void *, int);

int func_US2_L00_0030E488(int value) {
    if (g_resident_data_base != 0)
        return func_US2_00349728(g_resident_data_base + 0x39160, value);
    return 0;
}

extern int func_US2_00347B88(void *, int);

int func_US2_L00_0030E528(int value) {
    if (g_resident_data_base != 0)
        return func_US2_00347B88(g_resident_data_base + 0x39620, value);
    return 0;
}
