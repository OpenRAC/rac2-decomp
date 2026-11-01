#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
typedef signed int s32;
extern void func_002A7750(void *, s32, s32);
extern s32 D_L16_001B18F0 __attribute__((sda));
extern s32 D_L16_001B18E0 __attribute__((sda));
extern s32 D_L16_001B1704 __attribute__((sda));
extern void func_PAL_002A7E68(void *, s32, s32, void *);
extern u32 D_001A79F0[1];
extern float D_L16_001B1444 __attribute__((sda));
extern float D_L16_001B1448 __attribute__((sda));
extern char D_L16_001B9B00[];
extern void func_002B60B0(void *, float, float, float, float);
extern s32 func_00283CF0(float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_002AEE70(void *, void *, void *, float, float, float);
extern void func_PAL_002AC3C0(void *, void *);
extern s32 func_002A9640(void *, s32, s32);
extern s32 func_00282978(void *);
extern float func_PAL_002AA108(void *, void *);
extern s32 func_002B3BA8(void *, s32, float, float, s32, s32);
extern void func_0029F338(void *);
extern void func_PAL_002A7650(void *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern u8 *D_L16_001B9B50 __attribute__((nosda));
extern s32 D_L16_001B2648[] __attribute__((sda));
extern s32 func_L02_003272D8(void *);
extern u8 D_L16_00189EF0[] __attribute__((nosda));
extern u8 D_L16_00189F30[] __attribute__((nosda));

/* func_L16_0040DAE0 is defined in L16_00403900.c (this unit has no $gp access for it). */

/* Arms the object the level has just spawned: the entry latch, the two measured speed
   ratios, the object's own timer, then the two children and the hero sensor. */
s32 func_PAL_L16_004095E0(u8 *arg0)
{
    u8 *s1;
    u8 *s0;
    float f12;
    float f13;
    float f20;
    float d;

    s1 = *(u8 **)(arg0 + 0x68);
    if (*(u8 *)(arg0 + 0x20) == 0) {
        if (D_001A79F0[0] == 0x10
            && (*(s16 *)(arg0 + 0xB2) == 0x27 || *(s16 *)(arg0 + 0xB2) == 0x114))
            *(s32 *)(s1 + 0x2AC) = 1;
        if (*(s32 *)(s1 + 0x2AC) != 0)
            *(float *)(s1 + 0x28C) = *(float *)(arg0 + 0x18) + 300.0f;
        *(u8 *)(s1 + 0x150) = 8;
        *(s32 *)(s1 + 0x188) = 3;
        *(float *)(s1 + 0x17C) = 0.15000001f;
        *(s32 *)(s1 + 0x2A4) = 0;
        *(float *)(s1 + 0x170) = 0.5f;
        *(float *)(s1 + 0x174) = 0.5f;
        if (*(s16 *)(s1 + 0x24) == 0) {
            *(s16 *)(s1 + 0x24) = 5;
            *(float *)(s1 + 0x20) = 5.0f;
        }
        f13 = *(float *)(s1 + 0x2A0);
        f12 = (f13 + f13) * 0.00040000002f;
        f13 = f13 * 0.020000001f;
        *(s32 *)(s1 + 0x50) = 0;
        *(s32 *)(s1 + 0x88) = *(s32 *)(s1 + 0x88) | 0x17;
        *(u8 *)(s1 + 0x2E) = 1;
        *(float *)(s1 + 0x84) = 0.5f;
        *(float *)(s1 + 0x54) = 1.0f;
        *(float *)(s1 + 0x58) = 0.40000001f;
        *(float *)(s1 + 0x5C) = 0.40000001f;
        *(float *)(s1 + 0x60) = 1.5707965f;
        *(float *)(s1 + 0x80) = 1.5533432f;
        func_002B60B0(arg0, f12, f13, 0.0025132746f, 0.25132746f);
        func_002A7750(arg0, 1, 0);
        if (*(u8 *)(arg0 + 0x43) != 0)
            func_PAL_002A7E68(arg0, 0, 0, 0);
        *(u8 *)(s1 + 0x48) = func_00283CF0(17.0f);
        *(u8 *)(s1 + 0x4A) = func_00283CF0(32.0f);
    }
    if (*(u8 *)(arg0 + 0x31) != 0) {
        if (func_00282E48(arg0 + 0x10, D_L16_001B9B00) < 24.0f) {
            func_002A93B0(arg0);
            *(u8 *)(arg0 + 0x6F) = 0x16;
        }
    }
    func_002AEE70(arg0, s1 + 0x284, s1 + 0x278, D_L16_001B1444,
                  D_L16_001B1448 * 0.0003490659f, -1.0f);
    func_PAL_002AC3C0(arg0, s1 + 0x140);
    s0 = func_002A9640(arg0, 0x10000, 0);
    if (func_00282978(s1 + 0x26) == 0)
        s0 = 0;
    if (s0 != 0) {
        float v = *(float *)(s0 + 0x2C);

        if (*(float *)(s1 + 0x1E8) != 0.0f
            && *(u8 **)(s0 + 0x20) != 0
            && *(s16 *)(arg0 + 0xAA) == *(s16 *)(*(u8 **)(s0 + 0x20) + 0xAA))
            *(float *)(s0 + 0x2C) = v * *(float *)(s1 + 0x1E8);
        *(u8 *)(arg0 + 0xA8) = 0xFF;
    }
    d = func_PAL_002AA108(arg0, s0);
    *(u8 *)(arg0 + 0xA8) = 0xFF;
    *(float *)(s1 + 0x20) = *(float *)(s1 + 0x20) - d;
    if ((float)*(s16 *)(s1 + 0x24) * 0.33000001f <= d || *(float *)(s1 + 0x20) <= 0.0f) {
        if (*(u8 *)(arg0 + 0x43) != 4)
            func_PAL_002A7E68(arg0, 4, 0, 2);
        func_002A7750(arg0, 9, 3);
    }
    if (*(u8 *)(s1 + 0x2E) == 2) {
        func_0029F338(*(u8 **)(s1 + 0x274));
        func_PAL_002A7650(arg0, 0, 3);
        return 1;
    }
    f20 = 0.0f;
    *(s32 *)(s1 + 0x260) = func_002B3BA8(arg0, *(s32 *)(s1 + 0x250), *(float *)(s1 + 0x254), f20, 0, 0);
    *(s32 *)(s1 + 0x2B4) = func_002B3BA8(arg0, *(s32 *)(s1 + 0x2B0), f20, f20, 0, 0);
    return 0;
}
