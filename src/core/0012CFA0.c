#include "common.h"
#include "structs.h"

extern void func_0012C788(void *, int);

extern int func_0012C878(void *, int);

extern void func_0012CFA0(void *);

/* rac1-decomp src/core/00125630.c: func_00129180 */
/* Skips extra information bytes, each one marked by a leading 1 bit. */
void func_0012CFA0(void *decoderPtr) {
    while (ReadMpegBits(decoderPtr, 1) != 0) {
        SkipMpegBits(decoderPtr, 8);
    }
}
