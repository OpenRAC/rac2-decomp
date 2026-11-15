#include "include_asm.h"
#include "names.h"

/* func_L00_003F34D8 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which gives retail's grouped
   `lq`/`sq` with register addresses and keeps the copy a scheduling barrier, so the load
   of the source colour stays on the copy's side. */

typedef int TI128 __attribute__((mode(TI)));

/* Appends the source's 16-byte block and its colour to the list, up to 70 entries. */
void gfx_append_point_and_color(char *src, int *src4, char *dst16, int *dst4, int *count)
{
    int i = *count;

    if (i < 0x46) {
        *(TI128 *)(dst16 + i * 16) = *(TI128 *)src;
        dst4[i] = *src4;
        (*count)++;
    }
}
