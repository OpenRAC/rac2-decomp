#include "include_asm.h"

#include "common.h"
extern u8 D_001A7BD0[] __attribute__((sda));
extern char D_00189EA0[];
extern s32 D_L07_001B1048 __attribute__((sda));
extern s32 D_L07_001B104C __attribute__((sda));
extern f32 D_L07_001B1050 __attribute__((sda));
extern s32 D_L07_001FE3B8[] NOT_SDA;
extern void func_002A7750(void *, s32, s32);
extern void func_0029F338(void *);
extern void func_002B37E8(void *, void *);
extern u8 *func_0029EFD0(s32);
extern s32 func_00283CF0(f32);
extern f32 func_L07_003F90E8(s32, s32, f32, f32);
extern void func_L07_003F78F8(void *);
extern void *func_002A9640(void *, u32, s32);
extern f32 func_PAL_002AA108(void *, void *);
extern void func_PAL_002AC290(void *, void *, s32);
extern f32 func_002AA2E8(f32 *, f32, f32);
extern s32 func_002B3BA8(void *, s32, void *, s32, f32, f32);
#define F(p, o) (*(f32 *)((p) + (o)))
#define I(p, o) (*(s32 *)((p) + (o)))
#define H(p, o) (*(s16 *)((p) + (o)))
#define U(p, o) (*(u16 *)((p) + (o)))

void func_PAL_L07_003FC408(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    u8 *child;
    f32 damage, scale;

    if (object[0x20] == 0) {
        if (D_001A7BD0[0]) {
            func_002A7750(object, 1, 2);
            func_0029F338(object);
            return;
        }
        state[0x48] = func_00283CF0(30.0f);
        state[0x4A] = func_00283CF0(11.2f);
        state[0x2E] = 1;
        object[0x30] = 255;
        child = func_0029EFD0(0xD41);
        if (child) {
            func_002B37E8(child, object);
            U(child, 0x34) |= 0x400;
            *(u8 **)(state + 0x410) = child;
        }
        child = func_0029EFD0(0xD45);
        if (child) {
            func_002B37E8(child, object);
            *(u8 **)(state + 0x414) = child;
            U(child, 0x34) |= 0x100;
        }
        if (H(state, 0x24) == 0) {
            H(state, 0x24) = 100;
            F(state, 0x20) = 100.0f;
        } else {
            scale = 1.0f - func_L07_003F90E8(5, 20, 0.0f, 0.5f);
            H(state, 0x24) = func_00283CF0(scale * (f32)H(state, 0x24));
            F(state, 0x20) *= scale;
        }
        {
            s32 active = D_L07_001B104C;

            H(*(u8 **)(object + 0x24), 0x46) = 5;
            U(object, 0x34) |= 0x5000;
            if (active)
                D_L07_001B1048++;
        }
        D_L07_001B104C = 0;
        func_002A7750(object, 1, 2);
        func_L07_003F78F8(object);
    }
    F(state, 0x30) = D_L07_001B1050;
    damage = func_PAL_002AA108(object, func_002A9640(object, 0x10000, 0));
    if ((I(state, 0x420) >= 3 || (u32)(object[0x20] - 10) >= 5) &&
        (damage != 0.0f || state[0x2E] == 2)) {
        s32 amount = (s32)(damage * 32.0f);

        D_L07_001FE3B8[state[0x37]] += amount;
        state[0x167] = 150;
        func_PAL_002AC290(object, state + 0x160, amount);
        if (I(state, 0x420) < 2)
            func_002AA2E8((f32 *)(state + 0x20), F(state, 0x430), damage);
        else
            func_002AA2E8((f32 *)(state + 0x20), 0.0f, damage);
        if (state[0x2E] == 2) {
            if ((f32)I(state, 0x420) <= 1.0f)
                F(state, 0x20) = F(state, 0x430);
            else
                F(state, 0x20) = 0.0f;
        }
        if (F(state, 0x20) <= F(state, 0x430)) {
            F(state, 0x430) = (f32)H(state, 0x24) - (f32)H(state, 0x24) *
                ((f32)(I(state, 0x420) + 2) * 0.16694492f);
            I(state, 0x420)++;
            I(state, 0x458) = func_00283CF0(func_L07_003F90E8(3, 7, 1.0f, 4.0f));
            if (F(state, 0x20) - 1.0f < F(state, 0x430))
                F(state, 0x430) = F(state, 0x20) - 1.0f;
            if (F(state, 0x430) < 0.0f)
                F(state, 0x430) = 0.0f;
            if (object[0x95] == 0)
                func_002A7750(object, 10, -1);
            else
                func_002A7750(object, 12, -1);
        }
    }
    object[0xA8] = 255;
    state[0x2E] = 1;
    if (object[0x95] == 0)
        func_002B3BA8(object, -1, D_00189EA0, 0, 16.0f, 4.0f);
    else
        func_002B3BA8(object, I(state, 0x188), 0, 0, 0.0f, 0.0f);
}
