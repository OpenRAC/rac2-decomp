/* Set the initial state, then trigger the event when no active class 0xD3D remains. */
#include "common.h"

extern s32 D_L22_001B2128 __attribute__((sda));

extern u8 D_001A7A78 __attribute__((nosda));

extern s32 D_L22_001A903C __attribute__((sda));

extern void func_002A7750(u8 *, s32, s32);

extern s32 func_002E5E58(s32, s32, void *);

extern void func_002B0A18(s32, s32);

/* Starts in the idle state, then waits until no other object of class 3389 is still active before it fires the one-time event. */
void func_L22_00385F40(s32 moby)
{
    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        *(u8 *)(moby + 0x30) = 0xFF;
        SetMobyState((u8 *)moby, 1, -1);
        break;
    case 1: {
        s32 activeFound = 0;
        s32 other = D_L22_001B2128;

        while (other != 0) {
            if (*(s16 *)(other + 0xAA) == 0xD3D /* moby class 3389 */) {
                if (*(u8 *)(other + 0x20) != 3)
                    activeFound = 1;
            }
            other = *(s32 *)(other + 0x28);
        }
        if (activeFound != 0)
            break;
        if (D_001A7A78 == 0) {
            D_001A7A78 = 1;
            PlaySoundFromGlobalBank(1, 0, 0);
            SetEntryValueByIndex(0x1233, -1);
            D_L22_001A903C = 1;
        }
        break;
    }
    }
}
