#include "include_asm.h"
#include "names.h"

extern char g_str_sky_scroll_data[];
extern int g_sky_scroll_value __attribute__((sda));
extern int g_vram_zbuffer_address;
extern int g_sky_scroll_base;
extern void gfx_resident_table_reset(void);
extern void gfx_update_all_view_transforms(void);
extern void gfx_link_packet_chain(void);
extern void VU1_addGSregister(unsigned int, unsigned long);

void func_PAL_L03_002FF6E0(void) {
    float *p;

    gfx_resident_table_reset();
    g_sky_scroll_value = (int)g_str_sky_scroll_data;
    gfx_update_all_view_transforms();
    gfx_link_packet_chain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x1000000 | (g_vram_zbuffer_address >> 13));
    p = (float *)(g_sky_scroll_base + 0x74);
    *p += 0.013320001f;
    if (*p > 1.0f)
        *p -= 1.0f;
}
