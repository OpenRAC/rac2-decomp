#include "include_asm.h"
#include "names.h"
extern void gfx_append_vu1_preset_c(void);
extern void gfx_draw_shockwave_ring(void *);
extern void part_draw_spinning_billboard_pair(void *, void *, int, float);
extern float ref_L00_00330E48_00 __attribute__((sda));

void func_PAL_003329A8(char *owner)
{
    char *data;
    gfx_append_vu1_preset_c();
    data = *(char **)(owner + 0x68);
    if (*(float *)(data + 0x64) < ref_L00_00330E48_00)
        gfx_draw_shockwave_ring(owner);
    if (*(int *)(data + 0x78))
        part_draw_spinning_billboard_pair(data + 0x30, data + 0x40, 0, 0.2f);
}
