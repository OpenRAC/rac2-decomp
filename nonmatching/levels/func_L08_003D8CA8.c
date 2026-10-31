/* func_L08_003D8CA8: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -g.
   Scoping the target pointer improved 872 to 880 bytes. The measured pre-division nop pair with -g gives 888. Frame/allocation and address setup remain. The group cursor is one 32-bit stored address.
   No linked match is claimed.
*/

#include "common.h"
extern f32 func_00282E80(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002A77E0(s32);
extern f32 func_002A7878(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern s32 func_002A8600(s32 *, s32, s32, s32);
extern s32 func_002A86E8(s32 *, u8 *, s32, s32);
extern void func_L08_003D8AB0(void *);
extern u8 D_00189EA0[];
extern u8 *D_L08_001B29DC MACRO_ADDR;
extern u8 *D_L08_001B29DC_gp SDATA(D_L08_001B29DC);

void func_L08_003D8CA8(u8 *object)
{
    f32 difference[4];
    s32 cursor;
    u8 *state = *(u8 **)(object + 0x68);
    f32 *target;
    u8 *entry;
    f32 distance;
    if (*(s32 *)(state + 0x44C) && func_00282E80(object + 0x10, D_00189EA0) < 8.0f) {
        func_00282CF0(difference, object + 0x10, D_00189EA0);
        difference[2] = 0.0f;
        func_00282F20(difference, difference, 8.0f);
        target = (f32 *)(state + 0x3F0);
        func_00282CC0(target, object + 0x10, difference);
    } else if (*(s32 *)(state + 0x254) != 2 && func_002A77E0(2) == 0) {
        target = (f32 *)(state + 0x3F0);
        target[0] = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        target[1] = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
        target[2] = 0.0f;
        func_00282CC0(target, target, D_00189EA0);
    } else {
        target = (f32 *)(state + 0x3F0);
        target[0] = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 8.0f;
        target[1] = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 8.0f;
        target[2] = 0.0f;
        func_00282CC0(target, target, object + 0x10);
    }
    cursor = 0;
    func_002A8600(&cursor, object[0x21], 0, 0);
    while (cursor) {
        distance = func_00282E80(object + 0x10, (u8 *)cursor + 0x10);
        if (distance < 3.0f) {
            func_00282CF0(difference, object + 0x10, (u8 *)cursor + 0x10);
            func_00282F20(difference, difference, 4.0f / distance);
            func_00282CC0(target, target, difference);
        }
        func_002A86E8(&cursor, (u8 *)cursor, 0, 0);
    }
    if (*(s32 *)(state + 0x468) != -1) {
        entry = D_L08_001B29DC_gp + (*(s32 *)(state + 0x468) << 8);
        if (entry && entry[0x20] != 0xFE && entry[0x20] != 0xFD) {
            if (func_00282E80(object + 0x10, entry + 0x10) < 3.6f ||
                func_00282E80(target, D_L08_001B29DC + (*(s32 *)(state + 0x468) << 8) + 0x10) < 3.6f) {
                func_00282CF0(difference, object + 0x10, D_L08_001B29DC + (*(s32 *)(state + 0x468) << 8) + 0x10);
                difference[2] = 0.0f;
                func_00282F20(difference, difference, 5.0f);
                func_00282CC0(target, difference, object + 0x10);
            }
        }
    }
    target[2] = *(f32 *)(object + 0x18);
    func_L08_003D8AB0(object);
}
