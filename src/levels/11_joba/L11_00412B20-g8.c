#include "common.h"

extern void func_L01_002EABA8(s32, s32, s32, s32, s32);
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00282948(void *);
extern s32 func_00288E18(s32, s32);
extern u16 D_0018CD60 NOT_SDA;
extern u16 D_00194158 NOT_SDA;
extern u16 D_0018D048 NOT_SDA;
extern s32 D_L11_001B30C8 __attribute__((sda));
extern u8 D_00189EA0[];
/* g_inventoryOwned: 0x38 item ownership flags (public USA v2 symbol map). */
extern u8 D_001A7B00[0x38] __attribute__((sda));
extern s32 D_L11_001A9010[] __attribute__((sda));

/* Queues Joba subtitles when inventory and cuboid gates permit, with retry timers. */
void func_L11_00412B20(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);

    if (*(u8 *)(object + 0x20) == 0) {
        *(u8 *)(object + 0x20) = 1;
        *(u8 *)(object + 0x30) = 0xFF;
        *(s32 *)(state + 0x8) = 0x1A4;
        *(s32 *)(state + 0x10) = 0x12C;
    }
    if (*(u8 *)(object + 0x20) != 1) {
        return;
    }
    if (D_001A7B00[0]) {
        TriggerSubtitleInCuboid(0x9FF, 0x56, 3, *(s32 *)(state + 0x4), -1);
    }
    if (D_L11_001A9010[0] != 0 && D_L11_001B30C8 >= 3) {
        D_0018CD60 = 0xFFFF;
    }
    if (IsPointInCuboid(D_00189EA0, *(s32 *)(state + 0x0)) != 0) {
        if (func_00282948(state + 0x8) != 0) {
            if (D_00194158 == 0) {
                func_00288E18(0xA00, 0x57);
                *(s32 *)(state + 0x8) = 0x1A4;
            }
        }
    }
    if (D_001A7B00[0x2E]) {
        TriggerSubtitleInCuboid(0xA03, 0x5A, 0, *(s32 *)(state + 0xC), -1);
    }
    if (D_001A7B00[0xB]) {
        if (D_0018D048 == 0) {
            if (func_00282948(state + 0x10) != 0) {
                func_00288E18(0xA3D, 0x94);
            }
        }
    }
}
