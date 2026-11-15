#include "include_asm.h"
#include "names.h"

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_ff971bf89acc2217_u32;

typedef unsigned char Rac2Native_ff971bf89acc2217_u8;

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B6F0_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B6F0_01[];

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B750_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B750_01[];

extern Rac2Native_ff971bf89acc2217_u32 ref_L00_0037B7B0_00;

extern Rac2Native_ff971bf89acc2217_u8 ref_L00_0037B7B0_01[];

/* Adds a small fixed graphics packet to the end of the draw list and moves the list pointer forward. */
void func_L00_0037B6F0(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 4) = (Rac2Native_ff971bf89acc2217_u32)ref_L00_0037B6F0_01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B6F0_00 + 12) = 0x50000003u;
    ref_L00_0037B6F0_00 += 16;
}

/* Adds a small fixed graphics packet to the end of the draw list and moves the list pointer forward. */
void func_L00_0037B750(void)
{
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 0) = 0x30000003u;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 4) = (Rac2Native_ff971bf89acc2217_u32)ref_L00_0037B750_01;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 8) = 0;
    *(Rac2Native_ff971bf89acc2217_u32 *)(ref_L00_0037B750_00 + 12) = 0x50000003u;
    ref_L00_0037B750_00 += 16;
}

/* Adds a small fixed graphics packet to the end of the draw list and moves the list pointer forward. */
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

/* Stores a key, an owner and a value in the first free slot of the 32-entry key table. */
void func_L00_0037DD18(int key, int owner, int value)
{
    int i = 0;
    Rac2Native_ff971bf89acc2217_Entry *slot;

    if (gOwnerKeyTable[0].field04 == 0) {
        gOwnerKeyTable[0].field00 = owner;
        gOwnerKeyTable[0].field04 = key;
        gOwnerKeyTable[0].field08 = value;
        return;
    }
loop:
    i++;
    if (i >= 32)
        return;
    if (gOwnerKeyTable[i].field04 != 0)
        goto loop;
    slot = &gOwnerKeyTable[i];
    slot->field04 = key;
    slot->field00 = owner;
    slot->field08 = value;
}
