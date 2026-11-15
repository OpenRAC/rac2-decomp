#include "include_asm.h"
#include "names.h"

extern int ref_002A0048_00[] __attribute__((sda));
extern int ref_002A0048_01[] __attribute__((sda));
extern int ref_002A0048_02[] __attribute__((sda));
extern char ref_002A0048_03[];
extern void shadow_prepare_drawing(void);
extern void gfx_shadow_list_draw(void *);

/* Splice graphics setup commands into the DMA chain, or close its tag.
 * Advance an integer cursor before publishing it to keep the saved tag address.
 */
void ConfigureGraphicsSetupDmaChain(void)
{
    unsigned int *saved;
    int next;
    if (!ref_002A0048_00[0]) {
        ((unsigned int *)ref_002A0048_01[0])[0] = 0x10000000;
        ((unsigned int *)ref_002A0048_01[0])[1] = 0;
        ((unsigned int *)ref_002A0048_01[0])[2] = 0;
        ((unsigned int *)ref_002A0048_01[0])[3] = 0;
    } else {
        next = ref_002A0048_02[0];
        saved = (unsigned int *)next;
        next += 16;
        ref_002A0048_02[0] = next;
        ((unsigned int *)ref_002A0048_01[0])[0] = 0x20000000;
        ((unsigned int *)ref_002A0048_01[0])[1] = (unsigned int)ref_002A0048_02[0];
        ((unsigned int *)ref_002A0048_01[0])[2] = 0;
        ((unsigned int *)ref_002A0048_01[0])[3] = 0;
        shadow_prepare_drawing();
        gfx_shadow_list_draw(ref_002A0048_03);
        ((unsigned int *)ref_002A0048_02[0])[0] = 0x20000000;
        ((unsigned int *)ref_002A0048_02[0])[1] = (unsigned int)(ref_002A0048_01[0] + 16);
        ((unsigned int *)ref_002A0048_02[0])[2] = 0;
        ((unsigned int *)ref_002A0048_02[0])[3] = 0;
        ref_002A0048_02[0] += 16;
        saved[0] = 0x20000000;
        saved[1] = (unsigned int)ref_002A0048_02[0];
        saved[2] = 0;
        saved[3] = 0;
    }
}
