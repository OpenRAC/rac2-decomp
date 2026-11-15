#include "common.h"
#include "structs.h"

extern void r1_func_0012CD60(void *arg0);

/* rac1-decomp src/core/0012CC70.c: func_0012CC70 */
/* Stops the picture DMA for this decoder and saves its state. */
void func_00130AA0(void *mpeg) {
    r1_func_0012CD60((char *)*(void **)((char *)mpeg + 0x40) + 0x4C);
}
