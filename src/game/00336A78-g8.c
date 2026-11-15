#include "include_asm.h"
#include "names.h"

extern int D_001ADAF8 __attribute__((sda));

/* Returns one of four colour values from a table, or 0 if the index is too big. */
int func_00336EF8(unsigned int index) {
    if (index >= 4u) return 0;
    return ((int *)&gItemLevelColors)[index];
}
