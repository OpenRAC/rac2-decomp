#include "include_asm.h"
#include "names.h"
extern char *g_resident_data_base;
extern void UpdateBoltCounter(void);

void func_US2_0029D990(void) {
    if (g_resident_data_base != 0)
        UpdateBoltCounter();
}
