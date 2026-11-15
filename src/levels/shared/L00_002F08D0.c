#include "names.h"


/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_73f23b7222fbc541_u32;

typedef unsigned char Rac2Native_73f23b7222fbc541_u8;

extern Rac2Native_73f23b7222fbc541_u32 ref_L00_002F08D0_00;

extern Rac2Native_73f23b7222fbc541_u8 ref_L00_002F08D0_01[];

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_571a3580c10e935f_u32;

typedef unsigned char Rac2Native_571a3580c10e935f_u8;

extern Rac2Native_571a3580c10e935f_u32 ref_L00_002F0930_00;

extern Rac2Native_571a3580c10e935f_u8 ref_L00_002F0930_01[];

extern int ref_L00_002F0DA8_00;

/* Adds a small command to the graphics packet list. */
void gfx_append_gs_packet_tag_a(void)
{
    *(Rac2Native_73f23b7222fbc541_u32 *)(ref_L00_002F08D0_00 + 0) = 0x30000026u;
    *(Rac2Native_73f23b7222fbc541_u32 *)(ref_L00_002F08D0_00 + 4) = (Rac2Native_73f23b7222fbc541_u32)ref_L00_002F08D0_01;
    *(Rac2Native_73f23b7222fbc541_u32 *)(ref_L00_002F08D0_00 + 8) = 0;
    *(Rac2Native_73f23b7222fbc541_u32 *)(ref_L00_002F08D0_00 + 12) = 0x50000026u;
    ref_L00_002F08D0_00 += 16;
}

/* Adds a small command to the graphics packet list. */
void gfx_append_gs_packet_tag_b(void)
{
    *(Rac2Native_571a3580c10e935f_u32 *)(ref_L00_002F0930_00 + 0) = 0x30000029u;
    *(Rac2Native_571a3580c10e935f_u32 *)(ref_L00_002F0930_00 + 4) = (Rac2Native_571a3580c10e935f_u32)ref_L00_002F0930_01;
    *(Rac2Native_571a3580c10e935f_u32 *)(ref_L00_002F0930_00 + 8) = 0;
    *(Rac2Native_571a3580c10e935f_u32 *)(ref_L00_002F0930_00 + 12) = 0x50000029u;
    ref_L00_002F0930_00 += 16;
}

/* Returns a stored global value. */
int level_get_stored_global(void)
{
    return ref_L00_002F0DA8_00;
}
