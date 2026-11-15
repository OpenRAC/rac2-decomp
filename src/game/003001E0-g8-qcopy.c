/* func_003001E0 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -frac2-qcopy). */
#include "include_asm.h"
#include "names.h"


typedef int TI128 __attribute__((mode(TI)));

extern int ref_L00_003001E0_00 __attribute__((sda));

extern unsigned char D_0018C0B0[];

extern void func_002AD330(void *, void *, void *, void *);

extern void func_00282CC0(void *, void *, void *);

/* Adds a vector to another one, first transforming it when a transform is set, otherwise copies it. */
void func_003001E0(void *dest, void *source, void *extra)
{
    TI128 transformed;
    int *state = ref_L00_003001E0_00;

    if (state != 0) {
        TransformPointByMobyAttachment(*(int *)gHeroMoby_0018C0B0, state, extra, &transformed);
        FastVecAdd(dest, source, &transformed);
    } else {
        *(TI128 *)dest = *(TI128 *)source;
    }
}
