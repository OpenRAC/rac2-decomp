/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections.
 * 500 bytes, 0/23 in US, US2 and PAL. Switch and resident-record selection match; table-loop allocation and base-plus-field addressing differ from +0x1A4 onward. The loop returns its index, not an incoming fallback argument. Reopen with truthful table ownership/lifetimes evidence.
 * No strict linked validation or matching credit.
 */
#include "common.h"

typedef struct { u8 before[0x1220]; u8 *owner; u8 gap[0x24]; s32 value; } HeroFields;
extern HeroFields D_00189E20;
extern u8 D_00139568[];
typedef struct { u8 before[0x14]; s32 kind; u8 after[0xE0 - 0x18]; } KindRecord;
extern KindRecord D_00239BA0[];

s32 func_002AD980(u8 *object)
{
    u8 *other;
    s32 i;
    switch (*(short *)(object + 0xAA)) {
    case 0xA66: case 0xA82: return 0x29;
    case 0xC07: case 0xCE4: case 0xCE5: return 0x2A;
    case 0x87A: return 0x16;
    case 0xD01: return 0x18;
    case 0xB2E: return 0x1D;
    case 0xE64: case 0xECE: return 0x25;
    case 0x5DA: return 0x1B;
    case 0x9A9: case 0xA9B: return 0x1C;
    case 0xB58: case 0xE79: return 0x20;
    case 0x79: return 0xC;
    case 0xAC: return 0xE;
    }
    if (object == D_00189E20.owner)
        return D_00189E20.value;
    other = *(u8 **)(object + 0xB8);
    if (other != 0 && other == D_00189E20.owner)
        return D_00189E20.value;
    for (i = 0; i < 0x38; i++) {
        s32 type = D_00239BA0[D_00139568[i]].kind;
        if (*(short *)(object + 0xAA) == type)
            return i;
        if (other != 0 && *(short *)(other + 0xAA) == type)
            return i;
    }
    return 0xFF;
}
