#include "include_asm.h"
#include "names.h"

extern char D_L03_00282D40[];
extern int D_L03_001B2850 __attribute__((sda));
extern int D_001A72E0;
extern int D_L03_001AD390;
extern void gfx_resident_table_reset(void);
extern void gfx_update_all_view_transforms(void);
extern void gfx_link_packet_chain(void);
extern void VU1_addGSregister(unsigned int, unsigned long);

void func_PAL_L03_002FF6E0(void) {
    float *p;

    gfx_resident_table_reset();
    D_L03_001B2850 = (int)D_L03_00282D40;
    gfx_update_all_view_transforms();
    gfx_link_packet_chain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x1000000 | (D_001A72E0 >> 13));
    p = (float *)(D_L03_001AD390 + 0x74);
    *p += 0.013320001f;
    if (*p > 1.0f)
        *p -= 1.0f;
}
