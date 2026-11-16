#include "include_asm.h"
#include "names.h"

extern void gfx_resident_table_reset(void);
extern void gfx_update_all_view_transforms(void);
extern void gfx_link_packet_chain(void);
extern void VU1_addGSregister(unsigned int reg, unsigned long value);

/* per level: the pointer handed to the first setter and the $gp slot it lands in */
extern int ref_L01_002F1F70_00 __attribute__((sda));
extern char ref_L01_002F1F70_01[];

extern int g_vram_zbuffer_address __attribute__((sda));

/* Sets up the drawing state for effects by running three setup routines and writing two graphics chip registers. */
void gfx_init_effect_draw_state(void)
{
    gfx_resident_table_reset();
    ref_L01_002F1F70_00 = (int)ref_L01_002F1F70_01;
    gfx_update_all_view_transforms();
    gfx_link_packet_chain();
    VU1_addGSregister(0x47, 0x5360B);
    VU1_addGSregister(0x4E, 0x01000000 | (g_vram_zbuffer_address >> 13));
}
