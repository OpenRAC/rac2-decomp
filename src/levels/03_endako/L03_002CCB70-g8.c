#include "include_asm.h"
#include "names.h"

/* This unit is built with -G8: these bodies reach a global through $gp. */

extern char g_str_sky_scroll_data[];

extern int g_sky_scroll_value __attribute__((sda));

extern int g_vram_zbuffer_address;

extern int g_sky_scroll_base;

extern void func_35E6B8(void);

extern void func_35E450(void);

extern void func_35E728(void);

extern void func_37CA78(unsigned int, unsigned long);

/* Sets up the Endako sky effect each frame and slowly scrolls a texture offset that wraps around at 1.0. */
void sky_update_scroll(void) {
    float *scroll;

    func_35E6B8();
    g_sky_scroll_value = (int)g_str_sky_scroll_data;
    func_35E450();
    func_35E728();
    func_37CA78(0x47, 0x5360B);
    func_37CA78(0x4E, 0x1000000 | (g_vram_zbuffer_address >> 13));
    scroll = (float *)(g_sky_scroll_base + 0x74);
    *scroll += 0.011100001f;
    if (*scroll > 1.0f)
        *scroll -= 1.0f;
}
