#include "include_asm.h"

#include "common.h"
extern void func_L07_003F8010(void *);
extern void func_PAL_002AC3C0(void *, void *);
extern f32 func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, f32);
extern s32 func_00282948(void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AFDD8(void *, void *, void *, s32);
extern f32 func_00283248(f32, f32);
extern f32 func_00283BE0(f32, f32);
extern void func_PAL_002B14F8(void *, void *, s32, s32, f32);
extern void func_002AEC48(void *, void *, s32, f32, f32);
extern f32 func_00282E20(void *);
extern void func_00282D30(void *, void *, f32);
extern f32 D_L07_001B1100[4] __attribute__((sda));
extern f32 D_L07_001B10F0[4] __attribute__((sda));
extern f32 D_L07_001B1110 __attribute__((sda));
extern f32 D_L07_001B1114 __attribute__((sda));

void func_PAL_L07_003FD690(u8 *obj)
{
    f32 delta[4], pos[4];
    u8 *state = *(u8 **)(obj + 0x68);
    f32 angle, pitch, limit;
    if (obj[0x95] != 2) func_L07_003F8010(obj);
    func_PAL_002AC3C0(obj, state + 0x160);
    if (obj[0x95] < 2) func_L01_002F14E8(6, 0, *(f32 *)(state + 0x20) / func_00283CE0(*(s16 *)(state + 0x24)));
    (*(u16 *)(obj + 0x96))++;
    func_00282948(state + 0x42C);
    func_00283098(pos, D_L07_001B1100, obj + 0xC0);
    func_00282CC0(pos, pos, obj + 0x10);
    func_00282CF0(delta, state + 0x140, pos);
    func_002AFDD8(obj, delta, delta, 0);
    angle = func_00283248(delta[0], delta[1]);
    switch (obj[0x43]) { case 2: case 3: angle = func_00283BE0(angle, 3.14159274f); break; }
    func_PAL_002B14F8(obj, state + 0x360, 2, 0, 2.5f);
    if (angle > 0.785398244f) angle = 0.785398244f;
    else if (angle < -0.785398244f) angle = -0.785398244f;
    *(f32 *)(state + 0x3C8) = angle * 0.5f;
    func_002AEC48(obj, state + 0x360, 2, 0.0432f, 0.43200004f);
    if ((u32)(obj[0x43] - 2) < 2) {
        pitch = func_00283248(func_00282E20(delta), delta[2]) * D_L07_001B1114;
        limit = D_L07_001B1110 * 0.0174532942f;
        if (pitch > limit) pitch = limit;
        else if (pitch < -limit) pitch = -limit;
        func_00282D30(state + 0x340, D_L07_001B10F0, pitch);
        *(f32 *)(state + 0x2C8) = angle * 0.5f;
    }
    func_002AEC48(obj, state + 0x2E0, 3, 0.0432f, 0.43200004f);
    func_002AEC48(obj, state + 0x260, 1, 0.0432f, 0.43200004f);
}
