#include "common.h"

extern char D_00189E20[];
extern u8 D_00139568[];
extern char D_L20_0026D970[];
extern s32 func_L00_002ADEA0(s32 index);

typedef struct {
    u8 pad[0x28];
    s32 animation;
} AnimationEntry;

s32 func_L20_002B7A48(s32 allow_weapon)
{
    char *hero;
    u8 state = D_00189E20[0x22B4];

    switch (state) {
    case 1:
        return 0;
    case 4:
        return 0xD;
    }
    if (allow_weapon != 0) {
        char *hero = D_00189E20;
        if (*(u8 *)(hero + 0x22BA) != 0 && *(s16 *)(hero + 0x24EC) == 0) {
            int idx = hero_slot_item_id(0);

            return ((AnimationEntry *)(D_L20_0026D970 + D_00139568[idx] * 224))->animation;
        }
    }
    hero = D_00189E20;
    if (*(int *)(hero + 0x24CC) != 1)
        return *(u8 *)(hero + 0x1492) ? 0x67 : 0;
    return 0x51;
}

