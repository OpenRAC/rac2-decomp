#include "include_asm.h"


#include "common.h"
extern u8 *func_0029EFD0(s32);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283BE0(f32, f32);
#define L10_PARTNER(state) (*(u8 **)((state) + 4))

/* Two-state update of a cloud body with a kind-0x11CD partner. State 0 sets the body up
   (size 512, alpha 0xFF/0x1FF, scale from its class), spawns the partner the same way and
   moves the body up 6 (facing pi) or down 6 by the state flag; both states then ease the
   +0xF8 value with one of two helpers and copy the angle, that value and the position to
   the partner. */
void func_PAL_L10_00431A50(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);

    switch (object[0x20]) {
    case 0:
        object[0x20] = 1;
        *(u16 *)(object + 0x32) = 0x1FF;
        object[0x30] = 0xFF;
        *(f32 *)(object + 0x10) = 512.0f;
        *(f32 *)(object + 0x14) = 512.0f;
        *(f32 *)(object + 0x18) = 512.0f;
        *(s32 *)(object + 0x1C) = 0;
        *(f32 *)(object + 0x2C) = *(f32 *)(*(u8 **)(object + 0x24) + 0x24) * 4.0f;
        L10_PARTNER(state) = func_0029EFD0(0x11CD);
        L10_PARTNER(state)[0x30] = 0xFF;
        *(u16 *)(L10_PARTNER(state) + 0x32) = 0x1FF;
        *(f32 *)(L10_PARTNER(state) + 0x2C) =
            *(f32 *)(*(u8 **)(L10_PARTNER(state) + 0x24) + 0x24) * 4.0f;
        if (*(s32 *)state != 0) {
            *(f32 *)(object + 0x18) += 6.0f;
            *(f32 *)(object + 0xF0) = 3.1415927f;
        } else {
            *(f32 *)(object + 0x18) -= 6.0f;
        }
    case 1:
        if (*(s32 *)state != 0)
            *(f32 *)(object + 0xF8) = func_00283B98(*(f32 *)(object + 0xF8), 0.005890487f);
        else
            *(f32 *)(object + 0xF8) = func_00283BE0(*(f32 *)(object + 0xF8), 0.005890487f);
        *(f32 *)(L10_PARTNER(state) + 0xF0) = *(f32 *)(object + 0xF0);
        *(f32 *)(L10_PARTNER(state) + 0xF8) = *(f32 *)(object + 0xF8);
        qcopy(L10_PARTNER(state) + 0x10, object + 0x10);
        break;
    }
}


