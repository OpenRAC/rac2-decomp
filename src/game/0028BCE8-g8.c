#include "common.h"

typedef struct {
    u32 value;
    u8 pad[0x14];
    u32 id;
} Entry_0028BCE8;

typedef struct {
    u8 pad[0x3C];
    u16 value;
    u8 pad3E[0xA2];
} Rec_0028BCE8;

extern u32 D_001B18D0;
extern u32 D_001B18D4;
extern u32 D_001A8DD0 __attribute__((sda));
extern u32 D_001A8D48 __attribute__((sda));
extern u32 D_001A73B8[] MACRO_ADDR;
extern u8 D_00139568[];
extern Rec_0028BCE8 D_00239BA0[];
extern Entry_0028BCE8 D_00255170[];

/* Sets up the eight weapon menu slots from the current weapon list. */
void func_0028BCE8(void)
{
    int i;
    u32 weaponId;
    Rec_0028BCE8 *rec;

    gRadialSlotCount = 8;
    gRadialMenuPages = (u32)&D_001A8DD0;
    gRadialMenuPageIndex = 0;
    for (i = 0; i < 8; i++) {
        weaponId = gWeaponMenuSlots[i];
        rec = &gWeaponTable_00239BA0[gItemSlotToRecord[weaponId]];
        D_00255170[i].id = weaponId;
        D_00255170[i].value = rec->value;
    }
}
