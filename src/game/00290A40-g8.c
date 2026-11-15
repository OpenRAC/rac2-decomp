#include "include_asm.h"
#include "names.h"

extern void gfx_resident_table_reset(void);
extern void gfx_update_sky_shell_heights(void);
extern void gfx_update_all_view_transforms(void);
extern void gfx_link_packet_chain(void);
extern void VU1_addGSregister(unsigned int, unsigned long);
extern float D_00255B40[];
extern float *D_001B1990 __attribute__((sda));
extern int g_current_map_index;
extern int D_001A72E0;

/* Sets up level drawing: picks one of two set-up paths by level number and writes two graphics settings. */
void level_init_rendering(void)
{
    gfx_resident_table_reset();
    D_001B1990 = D_00255B40;
    if (g_current_map_index == 0)
        gfx_update_sky_shell_heights();
    else
        gfx_update_all_view_transforms();
    gfx_link_packet_chain();
    VU1_addGSregister(0x47, 0x5360BUL);
    VU1_addGSregister(0x4E, (D_001A72E0 >> 13) | 0x1000000);
}
