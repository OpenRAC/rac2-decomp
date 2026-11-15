#include "include_asm.h"

#include "common.h"
extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_001A7A78 __attribute__((nosda));
extern s32 D_L22_001A903C __attribute__((sda));
extern void moby_set_state(u8 *, s32, s32);
extern s32 snd_play_from_global_bank(s32, s32, void *);
extern void func_US2_002B1880(s32, s32);

void func_US2_L22_00387310(s32 a0)
{
    switch (*(u8 *)(a0 + 0x20)) {
    case 0:
        *(u8 *)(a0 + 0x30) = 0xFF;
        moby_set_state((u8 *)a0, 1, -1);
        break;
    case 1: {
        s32 found = 0;
        s32 node = D_L22_001B2128;

        while (node != 0) {
            if (*(s16 *)(node + 0xAA) == 0xD3D) {
                if (*(u8 *)(node + 0x20) != 3)
                    found = 1;
            }
            node = *(s32 *)(node + 0x28);
        }
        if (found != 0)
            break;
        if (D_001A7A78 == 0) {
            D_001A7A78 = 1;
            snd_play_from_global_bank(1, 0, 0);
            func_US2_002B1880(0x1233, -1);
            D_L22_001A903C = 1;
        }
        break;
    }
    }
}
