#include "common.h"

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x70];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} ClassRecord;

extern ClassRecord D_00239BA0[];

extern unsigned char D_00139568[];

extern unsigned char D_001A7AF8[] MACRO_ADDR;

/* 32 slot bytes: the low six bits hold a class id, 0xFF marks a free slot. */
extern unsigned char D_001A7B68[] MACRO_ADDR;

/* Puts a help id into the first free slot of the 32-slot list. Returns 1 if it was stored. */
int func_002883E8(int helpId)
{
    ClassRecord *record = &gWeaponTable_00239BA0[gItemSlotToRecord[helpId]];
    int result;
    int i;

    result = 0;
    if (record->word00 != 0 && record->byte04 == 0
        && (record->word80 != 0 || record->half88 != 0)) {
        for (i = 0; i < 32; i++) {
            if ((D_001A7B68[i] & 0x3F) == helpId || D_001A7B68[i] == 0xFF) {
                unsigned int mask = gItemOwnedFlags[helpId] ? 0x40 : 0;
                result = 1;
                D_001A7B68[i] = helpId | mask;
                break;
            }
        }
    }
    return result;
}
