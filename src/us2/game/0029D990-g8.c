#include "include_asm.h"
#include "names.h"
extern char *D_001A8CFC;
extern void UpdateBoltCounter(void);

void func_US2_0029D990(void) {
    if (D_001A8CFC != 0)
        UpdateBoltCounter();
}
