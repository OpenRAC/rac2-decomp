#include "include_asm.h"

#include "common.h"
extern u16 *D_L19_001FB5A0[];
extern u8 *D_L19_001B2A1C[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];
extern void func_0029F338(u8 *);
extern struct { u8 header[0x464]; u8 entries[0]; } D_L19_0021EA30;
extern s32 D_L19_001B1D20 __attribute__((sda));
extern s32 D_L19_001B1D24 __attribute__((sda));
extern s32 func_002ACD38(void *);
extern float func_002A89A8(void *, s32, f32);
extern float func_002A7878(f32, f32);
extern s32 func_002B3BA8(u8 *, s32, f32, f32, s32, s32);
extern void func_PAL_002B15D8(u8 *, s32, void *, s32, f32, f32, f32, f32);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_002A7750(u8 *, s32, s32);
extern s32 func_00282948(void *);
#define GROUP(off) (*(s32 *)(state + (off)))
#define FOR_EACH_ID(p, off) \
    for (p = D_L19_001FB5A0[GROUP(off)]; \
         (GROUP(off) & 0xFF) != 0xFF && GROUP(off) <= D_L19_001B2A38[0] && p != 0 && \
         ((p != 0 && (s16)p[-1] >= 0) || p == D_L19_001FB5A0[GROUP(off)]); \
         p++)

void func_PAL_L19_0042451C(u8 *object)
{
    u8 *state;
    s32 c;

    if (func_002ACD38(object + 0x10) == 0)
        return;
    state = *(u8 **)(object + 0x68);
    if (GROUP(0x120) == -1 ||
        (object[0xB0] != 0xFF &&
         (D_L19_0021EA30.entries[(s16)*(u16 *)(object + 0xB2)] != 0 ||
          ((c = *(u8 *)(D_0019B4A8 + (((s16) * (u16 *)(object + 0xB2) >> 1) + (D_001A79F0 << 10)))),
           (*(u16 *)(object + 0xB2) & 1) ? ((c >> 4) & 7) != 0 : (c & 7) != 0)))) {
        func_0029F338(object);
        return;
    }
    switch (object[0x20]) {
    case 0: {
        u16 *p;
        u8 *e;
        u8 *s;
        f32 x;

        x = func_002A89A8(object + 0x10, 0, 0.5f);
        x -= func_002A7878(0.1f, 0.3f);
        *(s16 *)(object + 0x7C) = 0x1F;
        *(s32 *)(object + 0x48) = 0;
        *(f32 *)(object + 0x18) = x;
        FOR_EACH_ID(p, 0x120) {
            e = D_L19_001B2A1C[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(s16 *)(e + 0xAA) == 0x10D0) {
                s = *(u8 **)(e + 0x68);
                *(f32 *)(s + 0x22C) = *(f32 *)(state + 0x128) + 10.0f;
                *(s32 *)(s + 0x26C) = 1;
                *(s32 *)(s + 0x274) = 1;
            }
        }
        func_002A7750(object, 1, -1);
        break;
    }
    case 1: {
        u8 *e;
        f32 vec[4];
        s32 gone;

        func_002B3BA8(object, -1, *(f32 *)(state + 0x128), *(f32 *)(state + 0x128), 0, 0);
        gone = 0;
        if (GROUP(0x138) == -1) {
            gone = 1;
        } else {
            e = D_L19_001B2A1C[0] + (GROUP(0x138) << 8);
            if (e == 0 || e[0x20] == 0xFE || e[0x20] == 0xFD)
                gone = 1;
        }
        if (GROUP(0x64) == 1 && gone) {
            qzero(vec);
            vec[2] = 0.18f;
            *(s16 *)(object + 0x7C) = 0;
            func_PAL_002B15D8(object, 0x1F, vec, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
            func_002E5CF8(0, 0, object);
            func_002A7750(object, 3, -1);
        }
        break;
    }
    case 3: {
        u16 *p;
        u8 *e;
        u8 *s;
        s32 found = 0;

        FOR_EACH_ID(p, 0x120) {
            e = D_L19_001B2A1C[0] + ((*p & 0x7FFF) << 8);
            if (e == 0)
                break;
            if (*(s16 *)(e + 0xAA) == 0x10D0) {
                s = *(u8 **)(e + 0x68);
                if (*(s32 *)(s + 0x26C) == 1) {
                    qcopy(e + 0x10, object + 0x10);
                    qcopy(s + 0x210, object + 0x10);
                    *(f32 *)(e + 0x18) = func_002A89A8(e + 0x10, 0, 1.0f);
                    found = 1;
                    *(s32 *)(s + 0x26C) = 0;
                    *(u16 *)(e + 0x34) &= 0xFF7F;
                    break;
                }
            }
        }
        if (!found) {
            func_002A7750(object, 4, -1);
        } else {
            GROUP(0x13C) = 167;
            func_002A7750(object, 2, -1);
        }
        break;
    }
    case 2: {
        u16 *p;
        u8 *e;
        u8 *s;
        s32 n;

        func_002B3BA8(object, -1, *(f32 *)(state + 0x128) + 10.0f, *(f32 *)(state + 0x128), 0, 0);
        if (GROUP(0x64) == 1) {
            n = 0;
            FOR_EACH_ID(p, 0x120) {
                e = D_L19_001B2A1C[0] + ((*p & 0x7FFF) << 8);
                if (e == 0)
                    break;
                if (*(s16 *)(e + 0xAA) == 0x10D0) {
                    s = *(u8 **)(e + 0x68);
                    if (*(s32 *)(s + 0x26C) == 0) {
                        if (e[0x20] != 0xFE) {
                            if (e[0x20] != 0xFD)
                                n++;
                        }
                    }
                }
            }
            if (D_L19_001B1D20 < D_L19_001B1D24) {
                if (n < 3) {
                    if (func_00282948(state + 0x13C))
                        func_002A7750(object, 3, -1);
                }
            }
        }
        break;
    }
    }
}
