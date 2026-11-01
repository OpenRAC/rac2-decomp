#include "include_asm.h"


extern unsigned char D_L03_00189E20[];
extern float func_2EF158(void *, void *);
extern void func_2B8300(int, int, void *);

void func_PAL_L03_00396448(unsigned char *a0) {
    unsigned char *g = D_L03_00189E20;

    if (*(unsigned char *)(g + 0x22B4) == 0)
        if (func_2EF158(g + 0x80, a0 + 0x10) < 1.7f)
            func_2B8300(1, 0x3F, a0);
}

