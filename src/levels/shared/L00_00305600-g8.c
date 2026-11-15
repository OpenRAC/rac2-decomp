#include "names.h"
/* Looks the object up in the 0x30 five-word entries at +0x4B40 of D_0014FB540; when it is
   there and D_L00_001A9670 is -1, calls func_002FC3C0(1) and hands the object, the short at
   D_00152CE4 and the argument to func_002946C0. Returns 0 only when the entry is found but
   the word is not -1. */
typedef struct { char gap[0x4B40]; int entries[0x30 * 5]; } TocBase_L00_00305600;

extern TocBase_L00_00305600 D_0014FB540;

extern int D_L00_001A9670 __attribute__((sda));

extern short D_00152CE4[];

extern void gfx_wait_for_dma_status_bits(int);

extern void load_cached_moby_class(int, int, int);

int menu_try_start_toc_entry(int object, int argument)
{
    int i;

    for (i = 0; i < 0x30; i++) {
        if (D_0014FB540.entries[i * 5] == object)
            break;
    }
    if (i == 0x30)
        return 1;
    if (D_L00_001A9670 != -1)
        return 0;
    gfx_wait_for_dma_status_bits(1);
    load_cached_moby_class(object, D_00152CE4[0], argument);
    return 1;
}
