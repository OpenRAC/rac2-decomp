#include "common.h"

extern u8 *D_L03_001B2A1C __attribute__((sda));
extern s32 D_001A79F0[] __attribute__((sda));
extern u8 D_001395B8[];
extern void func_002A7750(u8 *, s32, s32);
extern void func_L00_003294F0(u8 *, s32);
extern void func_L03_00419850(u8 *);

void func_L03_00419578(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);
    u8 *other;
    s32 index;
    s32 state;
    if (*(s32 *)(vars + 0x14) != 0)
        *(s32 *)(object + 0x98) = 0;
    state = object[0x20];
    switch (state) {
    case 0:
        if (*(s32 *)(vars + 0x14) != 0)
            *(u16 *)(object + 0x34) |= 0x41;
        if (*(s32 *)(vars + 8) == -1 || *(s32 *)(vars + 0xC) == -1)
            func_002A7750(object, 2, -1);
        else
            func_002A7750(object, 1, -1);
    case 1:
        index = *(s32 *)(vars + 8);
        if (index != -1) {
            other = D_L03_001B2A1C + (index << 8);
            if (other != 0 && other[0x20] != 0xFE && other[0x20] != 0xFD)
                break;
        }
        index = *(s32 *)(vars + 0xC);
        if (index != -1) {
            other = D_L03_001B2A1C + (index << 8);
            if (other != 0 && other[0x20] != 0xFE && other[0x20] != 0xFD)
                break;
        }
        func_002A7750(object, 2, -1);
        break;
    case 3:
        other = *(u8 **)(vars + 0x1C);
        if (other == 0)
            break;
        if (other[0x20] == 0xFE)
            goto owner_finished;
        if (other[0x20] != 0xFD)
            break;
owner_finished:
        index = *(s32 *)(vars + 0);
        if (index != -1)
            func_L00_003294F0(D_L03_001B2A1C + (index << 8), 1);
        index = *(s32 *)(vars + 4);
        if (index != -1)
            func_L00_003294F0(D_L03_001B2A1C + (index << 8), 1);
        if (D_001A79F0[0] == state)
            D_001395B8[0x78] |= 1;
        if (D_001A79F0[0] == 0xE)
            D_001395B8[0x78] |= 2;
        func_002A7750(object, 4, -1);
        break;
    }
    if (*(s32 *)(vars + 0x10) != 0 && object[0x31] != 0)
        func_L03_00419850(object);
}
