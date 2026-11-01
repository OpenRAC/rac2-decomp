#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
extern u16 *D_L18_001FB320[];
extern u8 *D_L18_001B281C[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern u8 *func_002A9640(u8 *, s32, s32);
extern s32 func_PAL_002B1A50(u8 *, u8 *, s32);
extern void func_PAL_002A7650(u8 *, s32, s32);
extern s32 func_002A77E0(s32);
extern void func_PAL_002B3F18(u8 *, u8 *, u8 *);
extern u8 *func_0029EFD0(s32);
extern void func_002A0F48(u8 *);
extern void func_PAL_002A7E68(u8 *, s32, s32, s32);
extern void func_002A04B8(u8 *, s32 *, s32 *, s32 *);
extern void func_002A0488(u8 *, s32, s32, s32);
extern s32 func_002B3BA8(u8 *, s32, s32, s32, float, float);
extern void func_PAL_L18_00437A28(u8 *);
extern void func_L18_00432D60(u8 *);
extern void func_L18_00432E78(u8 *, s32, s32, s32);
extern s32 func_L18_00432E28(u8 *);

void func_PAL_L18_00435908(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *t;
    u8 *e;
    u16 *p;
    u8 saved;
    s32 b0;
    s32 b1;
    s32 b2;
    float t20;

    t = func_002A9640(object, 0x10000, 1);
    if (t != 0) {
        if (*(u8 **)(t + 0x20) != 0) {
            if (*(s16 *)(*(u8 **)(t + 0x20) + 0xAA) == 0xF0A || *(s16 *)(*(u8 **)(t + 0x20) + 0xAA) == 0xF9E)
                *(s32 *)(t + 0x2C) = 0;
        }
        if ((u8)(object[0x20] - 1) < 2)
            *(s32 *)(t + 0x2C) = 0;
    }
    saved = object[0x94];
    if (func_PAL_002B1A50(object, state + 0x50, 0)) {
        if (object[0x94] == 0xD || object[0x94] == 9 || object[0x94] == 0xA || object[0x94] == 0xB ||
            object[0x94] == 0xC || object[0x94] == 5)
            object[0x94] = saved;
        t20 = *(float *)(state + 0x20);
        if (*(u8 **)(state + 0x7C0) == 0) {
            if (t20 <= 0.0f) {
                func_PAL_002A7650(object, 0, 3);
                func_PAL_L18_00437A28(object);
                return;
            }
        }
        if (t20 <= 0.0f && func_002A77E0(7) == 0) {
            *(float *)(state + 0x20) = 8.0f;
            *(s32 *)(object + 0x98) = *(s32 *)(*(u8 **)(object + 0x24) + 0x10);
            func_002A7750(object, 0xE, -1);
            *(s16 *)(state + 0x88) = 0;
            state[0x6A] = 0;
        } else {
            func_L18_00432E78(object, object[0x43], 0, 2);
        }
        func_L18_00432D60(object);
    }
    object[0xA8] = 0xFF;
    if (*(u8 **)(state + 0x188) != 0 && *(s16 *)(*(u8 **)(state + 0x188) + 0xAA) == 0xF59) {
        func_PAL_002A7650(object, 0, 3);
        func_PAL_L18_00437A28(object);
    }
    if (*(u8 **)(state + 0x7C0) != 0) {
        func_PAL_002B3F18(*(u8 **)(state + 0x7C0), *(u8 **)(*(u8 **)(state + 0x7C0) + 0x68) + 0x20, state + 0x20);
        if (!(*(u16 *)(*(u8 **)(state + 0x7C0) + 0x7C) & 2) && *(u8 **)(state + 0x7C4) == 0) {
            u8 *v = func_0029EFD0(0xF0C);
            *(u8 **)(state + 0x7C4) = v;
            if (v != 0) {
                v[0x30] = object[0x30];
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x32) = *(u16 *)(object + 0x32);
                *(long *)(*(u8 **)(state + 0x7C4) + 0x38) = *(long *)(object + 0x38);
                func_002A0F48(*(u8 **)(state + 0x7C4));
                *(s32 *)(*(u8 **)(state + 0x7C4) + 0x98) = 0;
                if ((*(u8 **)(state + 0x7C4))[0x43] != 0x14)
                    func_PAL_002A7E68(*(u8 **)(state + 0x7C4), 0x14, 0, 2);
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= 6;
                *(u16 *)(*(u8 **)(state + 0x7C4) + 0x34) |= *(u16 *)(object + 0x34) & 0x8000;
                *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                    *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
            } else {
                func_PAL_L18_00437A28(object);
            }
        }
        if (*(u8 **)(state + 0x7C0) != 0) {
            func_002A04B8(object, &b0, &b1, &b2);
            func_002A0488(*(u8 **)(state + 0x7C0), b0, b1, b2);
        }
    }
    if (*(u8 **)(state + 0x7C4) != 0) {
        func_002A04B8(object, &b0, &b1, &b2);
        func_002A0488(*(u8 **)(state + 0x7C4), b0, b1, b2);
    }
    if (*(s16 *)(state + 0x7F4) != -1) {
        *(u16 *)(state + 0x7F6) = 0;
        for (p = D_L18_001FB320[object[0x21]];
             object[0x21] != 0xFF && object[0x21] <= D_L18_001B2838[0] && p != 0 &&
             ((p != 0 && (s16)p[-1] >= 0) || p == D_L18_001FB320[object[0x21]]);
             p++) {
            e = D_L18_001B281C[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (func_L18_00432E28(e))
                *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F6) + 1;
        }
    } else {
        *(u16 *)(state + 0x7F6) = *(u16 *)(state + 0x7F4);
    }
    if (*(float *)(object + 0x18) < 90.0f ||
        (*(float *)(state + 0x800) != -1.0f && *(float *)(object + 0x18) < *(float *)(state + 0x800)))
        func_PAL_L18_00437A28(object);
    if (state[0x2E] == 2)
        func_PAL_L18_00437A28(object);
    if (*(float *)(state + 0x20) <= 0.0f) {
        if (object[0x20] != 0xD)
            func_PAL_L18_00437A28(object);
    }
    *(s32 *)(state + 0x79C) =
        func_002B3BA8(object, *(s32 *)(state + 0x790), 0, 0, *(float *)(state + 0x794), 0.0f);
    if (object[0x20] < 4) {
        if (object[0x20] != 3)
            return;
        if (object[0xBC] == 0)
            return;
    }
    if (*(float *)(state + 0x7E8) < 1.5f) {
        *(float *)(state + 0x7E8) = *(float *)(state + 0x7E8) + 0.01f;
        *(float *)(object + 0x2C) = *(float *)(*(u8 **)(object + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C0) != 0)
            *(float *)(*(u8 **)(state + 0x7C0) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C0) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C4) != 0)
            *(float *)(*(u8 **)(state + 0x7C4) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C4) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
        if (*(u8 **)(state + 0x7C8) != 0)
            *(float *)(*(u8 **)(state + 0x7C8) + 0x2C) =
                *(float *)(*(u8 **)(*(u8 **)(state + 0x7C8) + 0x24) + 0x24) * *(float *)(state + 0x7E8);
    }
}
