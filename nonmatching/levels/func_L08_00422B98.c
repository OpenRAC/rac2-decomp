/* func_L08_00422B98: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Scoping the target pointer after the initial probe improved 820 to 828 bytes. Frame/allocation and branch scheduling remain.
   No linked match is claimed.
*/

#include "common.h"
extern s32 func_L01_003165E8(void *, s32, s32, s32, s32);
extern s32 func_001163B0(void);
extern f32 func_002A7878(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_00282E80(void *, void *);
extern void func_L01_00337A60(void *, void *, void *, s32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_002A89A8(void *, void *, f32);
extern u8 *D_L08_001B29DC MACRO_ADDR;
extern u8 *D_L08_001FE7BC;
extern u8 D_00189EA0[];
extern u8 D_L08_001BFF60[];

void func_L08_00422B98(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    f32 *target;
    f32 amount, value;
    if (!func_L01_003165E8(state + 0x160, *(s32 *)(state + 0x1A8), -1, -1, -1)) {
        target = (f32 *)(state + 0x160);
        if ((func_001163B0() & 1) || *(s32 *)(state + 0x144) == 2 || *(s16 *)(state + 0x1BC)) {
            if (*(s32 *)(state + 0x184) != -1 && (func_001163B0() & 1))
                qcopy(target, state + 0x150);
            else {
                target[0] = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                target[1] = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                target[2] = 0.0f;
                func_00282CC0(target, target, D_L08_001B29DC + (*(s32 *)(state + 0x184) << 8) + 0x10);
                target[2] += 1.7f;
            }
        } else {
            target[0] = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
            target[1] = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
            target[2] = 0.0f;
            func_00282CC0(target, target, D_00189EA0);
            target[2] += 1.7f;
        }
        if (*(s16 *)(state + 0x1BC) && func_00282E80(target, D_00189EA0) < 3.0f) {
            amount = func_002A7878(3.0f, 5.0f);
            value = target[0];
            if (func_001163B0() & 1) target[0] = value - amount;
            else target[0] = value + amount;
            amount = func_002A7878(3.0f, 5.0f);
            value = target[1];
            if (func_001163B0() & 1) target[1] = value - amount;
            else target[1] = value + amount;
        }
    } else {
        target = (f32 *)(state + 0x160);
        if (*(s32 *)(state + 0x1A8) == -1) {
        func_L01_00337A60(target, target, D_L08_001FE7BC + 0x10, *(s32 *)D_L08_001FE7BC);
        }
    }
    if (func_002761F8(object + 0x10, target, 2, object, 0)) {
        func_00282CF0(target, D_L08_001BFF60, target);
        func_00282F20(target, target, 2.0f);
        func_00282CC0(target, target, D_L08_001BFF60);
    }
    target[2] = func_002A89A8(target, 0, 4.0f) + 1.7f;
}
