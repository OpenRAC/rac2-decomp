/* func_003001E0 in its own unit (flags in config/cflags.txt: -O2 -G8 -ffunction-sections -frac2-qcopy). */
#include "include_asm.h"
#include "names.h"


typedef int TI128 __attribute__((mode(TI)));

extern int ref_L00_003001E0_00 __attribute__((sda));

extern unsigned char g_hero_moby[];

extern int moby_transform_point_by_attachment(void *, void *, void *, void *);

extern void FastVecAdd(void *, void *, void *);

/* Adds a vector to another one, first transforming it when a transform is set, otherwise copies it. */
void vec_add_transformed_or_copy(void *dest, void *source, void *extra)
{
    TI128 transformed;
    int *state = ref_L00_003001E0_00;

    if (state != 0) {
        moby_transform_point_by_attachment(*(int *)g_hero_moby, state, extra, &transformed);
        FastVecAdd(dest, source, &transformed);
    } else {
        *(TI128 *)dest = *(TI128 *)source;
    }
}
