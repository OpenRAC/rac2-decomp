#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_967caba148c0b35c_u32;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_00;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_01;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_04;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_05;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_06;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_07;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_08;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_09;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_10;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_11;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_02;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_03;

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_12 __attribute__((sda));

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_13 __attribute__((sda));

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_14 __attribute__((sda));

extern Rac2Native_967caba148c0b35c_u32 ref_L00_002E56B0_15;

/* Sets a group of counters and flags to zero. */
void counter_clear_group(void)
{
    ref_L00_002E56B0_00 = 0;
    ref_L00_002E56B0_01 = 0;
    ref_L00_002E56B0_04 = 0;
    ref_L00_002E56B0_05 = 0;
    ref_L00_002E56B0_06 = 0;
    ref_L00_002E56B0_07 = 0;
    ref_L00_002E56B0_08 = 0;
    ref_L00_002E56B0_09 = 0;
    ref_L00_002E56B0_12 = 0;
    ref_L00_002E56B0_13 = 0;
    ref_L00_002E56B0_14 = 0;
    ref_L00_002E56B0_10 = 0;
    ref_L00_002E56B0_11 = 0;
    ref_L00_002E56B0_02 = 0;
    ref_L00_002E56B0_03 = 0;
    ref_L00_002E56B0_15 = 0;
}

extern char *g_dma_packet_cursor __attribute__((sda));
extern char *ref_L00_0027B858_00;
extern char g_gfx_clear_color_packet[];
extern char g_gs_draw_env_regs[];
extern char g_view_params[];
extern void VU1_addGSregister(unsigned int, unsigned long);

/* Writes two drawing packets and sends the current color to the graphics chip. */
void gfx_write_clear_color_packets(void)
{
    unsigned long packed;
    *(int *)(ref_L00_0027B858_00 + 0) = 0x30000013;
    *(char **)(ref_L00_0027B858_00 + 4) = g_gfx_clear_color_packet;
    *(int *)(ref_L00_0027B858_00 + 8) = 0;
    *(int *)(ref_L00_0027B858_00 + 12) = 0x50000013;
    {
        char *old = ref_L00_0027B858_00;
        ref_L00_0027B858_00 = old + 16;
        *(int *)(old + 16) = 0x3000000B;
    }
    *(char **)(ref_L00_0027B858_00 + 4) = g_gs_draw_env_regs;
    *(int *)(ref_L00_0027B858_00 + 8) = 0;
    *(int *)(ref_L00_0027B858_00 + 12) = 0x5000000B;
    {
        char *base = g_view_params;
        int w0 = *(int *)(base + 0x230);
        int w1 = *(int *)(base + 0x234);
        int w2 = *(int *)(base + 0x238);
        packed = (unsigned long)w0 | ((unsigned long)w1 << 8) | ((unsigned long)w2 << 16);
    }
    g_dma_packet_cursor = ref_L00_0027B858_00 + 16;
    VU1_addGSregister(0x3D, packed);
}
