#include "include_asm.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ff971bf89acc2217_u32;

typedef unsigned char Rac2Native_ff971bf89acc2217_u8;

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B6F0_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B6F0_01[];

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B750_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B750_01[];

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B7B0_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B7B0_01[];

void func_L00_0037B6F0(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 4) = (Rac2Native_ff971bf89acc2217_u32)ref_L00_0037B6F0_01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 12) = 0x50000003u;
    ref_L00_0037B6F0_00 += 16;
}

void func_L00_0037B750(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 4) = (Rac2Native_ff971bf89acc2217_u32)ref_L00_0037B750_01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 12) = 0x50000003u;
    ref_L00_0037B750_00 += 16;
}

void func_L00_0037B7B0(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B7B0_00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B7B0_00 + 4) = (Rac2Native_ff971bf89acc2217_u32)ref_L00_0037B7B0_01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B7B0_00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B7B0_00 + 12) = 0x50000003u;
    ref_L00_0037B7B0_00 += 16;
}


typedef struct {
    Rac2Native_ff971bf89acc2217_u32 field00, field04;
    int field08;
    Rac2Native_ff971bf89acc2217_u8 gap0c[4];
} Rac2Native_ff971bf89acc2217_Entry;

extern Rac2Native_ff971bf89acc2217_Entry D_L00_00231340[32];

void func_L00_0037DD18(int a0, int a1, int a2)
{
    int i = 0;
    Rac2Native_ff971bf89acc2217_Entry *e;

    if (D_L00_00231340[0].field04 == 0) {
        D_L00_00231340[0].field00 = a1;
        D_L00_00231340[0].field04 = a0;
        D_L00_00231340[0].field08 = a2;
        return;
    }
loop:
    i++;
    if (i >= 32)
        return;
    if (D_L00_00231340[i].field04 != 0)
        goto loop;
    e = &D_L00_00231340[i];
    e->field04 = a0;
    e->field00 = a1;
    e->field08 = a2;
}
