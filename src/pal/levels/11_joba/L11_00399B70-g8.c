#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(f32 *a0, f32 *a1, f32 *a2);
extern f32 func_00283B98(f32 a0, f32 a1);
extern f32 func_00282C48(f32 a0);
extern s32 func_00282948(void *a0);
extern s32 func_002829A8(void *a0);
extern void func_0029F338(void *a0);
extern f32 D_L11_001AEC40 __attribute__((sda));
extern s32 func_002A7820(s32 low, s32 high);
extern f32 func_002A7878(f32 low, f32 high);
extern s32 D_L11_001AECD0 __attribute__((sda));
extern f32 D_L11_001AECD4 __attribute__((sda));
extern f32 D_L11_001AECD8 __attribute__((sda));
extern f32 D_L11_001AECDC __attribute__((sda));
extern f32 D_L11_001AECE0 __attribute__((sda));
extern f32 D_L11_001AECE4 __attribute__((sda));
extern f32 D_L11_001AECE8 __attribute__((sda));
extern f32 D_L11_001AECEC __attribute__((sda));
extern f32 D_L11_001AECF0 __attribute__((sda));
extern f32 func_002A78D8(f32 low, f32 high);
extern f32 func_002A7940(void);
extern s32 func_001163B0(void);
extern s32 func_00283CF0(f32 value);
extern s32 D_L11_001AEC3C __attribute__((sda));
extern f32 D_L11_001AEC38 __attribute__((sda));
extern u8 D_00139578[];
extern u8 D_L11_00279BA0[];

/* Scales the state's vector by the level's factor, clamps its timer to the state's
   limit, and runs the two animation angles through the engine's wrap function. */
void func_PAL_L11_00399E30(u8 *arg0) {
    u8 *s1 = arg0;
    u8 *s0 = *(u8 **)(s1 + 0x68);
    f32 f0, f1, f2, f4;

    func_00282CC0((f32 *)(s1 + 0x10), (f32 *)(s1 + 0x10), (f32 *)s0);
    f2 = *(f32 *)(s0 + 0x8) - 0.006f;
    f0 = *(f32 *)(s0 + 0x0) * D_L11_001AEC40;
    f1 = *(f32 *)(s0 + 0x4) * D_L11_001AEC40;
    f4 = *(f32 *)(s0 + 0x20);
    *(f32 *)(s0 + 0x8) = f2;
    *(f32 *)(s0 + 0x0) = f0;
    *(f32 *)(s0 + 0x4) = f1;
    if (f2 < f4)
        *(f32 *)(s0 + 0x8) = f4;
    *(f32 *)(s1 + 0xF8) = func_00283B98(*(f32 *)(s1 + 0xF8), *(f32 *)(s0 + 0x28));
    *(f32 *)(s1 + 0xF0) = func_00283B98(*(f32 *)(s1 + 0xF0), *(f32 *)(s0 + 0x2C) * (f32)*(s32 *)(s0 + 0x24));
    f0 = func_00282C48(*(f32 *)(s1 + 0xF0));
    if (f0 > 0.78539824f)
        *(s32 *)(s0 + 0x24) = -*(s32 *)(s0 + 0x24);
    if (func_00282948(s0 + 0x1C) != 0) {
        func_0029F338(s1);
    } else if (s1[0x31] == 0) {
        func_0029F338(s1);
    } else if (*(s32 *)(s0 + 0x1C) < 0x19) {
        if (func_002829A8(s1 + 0x23) != 0)
            func_0029F338(s1);
    }
}
