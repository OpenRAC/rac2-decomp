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

/* Sets up the Endako sky each frame: resets the tables, links the view transforms and packets, and scrolls the sky. (PAL: 50 Hz scroll speed) */
void sky_update_scroll_pal(void) {
    float *scroll;

    gfx_resident_table_reset();
    g_sky_scroll_value = (int)g_str_sky_scroll_data;
    gfx_update_all_view_transforms();
    gfx_link_packet_chain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x1000000 | (g_vram_zbuffer_address >> 13));
    scroll = (float *)(g_sky_scroll_base + 0x74);
    *scroll += 0.013320001f;
    if (*scroll > 1.0f)
        *scroll -= 1.0f;
}
