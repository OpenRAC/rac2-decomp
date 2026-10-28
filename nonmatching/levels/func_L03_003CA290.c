/* Nonmatching reconstruction. Profile: -O2 -G8 -ffunction-sections -g.
 * 544/544 bytes; 0/2 in US and US2; PAL ABSENT. The complete state/zero/vector path matches; argument setup order around 003263D0 and 002B0A68 differs from +0x188. Retail confirms seven GPR and four FP inputs to 003263D0, which returns no meaningful scalar. Reopen with truthful bank-preserving call declarations/lifetimes.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

typedef union { int q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 *D_L03_001B2A20[] __attribute__((sda));
extern u16 D_L03_001B0300 __attribute__((sda));
extern u16 D_L03_001B0304 __attribute__((sda));
extern s32 D_L03_001B2548[] __attribute__((sda));
extern u32 D_L03_001B02F8 __attribute__((sda));
extern u32 D_L03_001B02FC[] __attribute__((sda));
extern s32 D_L03_001B0308 __attribute__((sda));
extern f32 D_L03_001B030C __attribute__((sda));
extern f32 D_L03_001B0310 __attribute__((sda));
extern f32 D_L03_001B0314 __attribute__((sda));
extern f32 D_L03_001B0318 __attribute__((sda));
extern f32 D_L03_001A8F20[];
extern void func_002A7750(u8 *, u8, s32);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L03_003CA4B0(void *);
extern f32 func_00283198(f32);
extern u32 func_00283D38(u32, u32, f32);
extern void *func_002A9640(void *, u32, s32);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_003263D0(u8 *, void *, s32, s32, void *, u32, void *, f32, f32, f32, f32);
extern void func_002B0A68(u8 *, s32, void *, u8, f32, f32, f32, f32);
extern s32 func_002E5CF8(s32, s32, u8 *);
extern void func_L00_003294F0(u8 *, s32);

void func_L03_003CA290(u8 *object)
{
    Vector position, velocity;
    switch (object[0x20]) {
    case 0:
        if ((s32)object < (s32)D_L03_001B2A20[0]) {
            *(s32 *)(object + 0x9C) = 0xF;
            func_002A7750(object, 3, -1);
        } else {
            *(u16 *)(object + 0x7C) = D_L03_001B0300;
            func_002A7750(object, 1, -1);
        }
        break;
    case 1:
        if (object[0x31] != 0) {
            func_L00_002E6CF0(func_L03_003CA4B0, object);
            *(u32 *)(object + 0x78) = func_00283D38(D_L03_001B02F8, D_L03_001B02FC[0],
                (func_00283198((f32)(D_L03_001B2548[0] % 150) * 0.04188786819577217f - 3.141590118408203f) + 1.0f) * 0.5f);
        }
        if (func_002A9640(object, 0x10000, 0) != 0) {
            position.q = 0;
            velocity.q = 0;
            velocity.f[2] = 0.05000000447034836f;
            position.f[2] = 0.5f;
            func_00282CC0(&position, &position, object + 0x10);
            func_L00_003263D0(object, &position, 5, 1, &velocity, 0x504040C0, 0,
                             0.3330000042915344f, 3.0f, 0.5f, 1.0f);
            func_002B0A68(object, D_L03_001B0308, D_L03_001A8F20, 0xFF,
                         D_L03_001B030C, D_L03_001B0310, D_L03_001B0314, D_L03_001B0318);
            func_002E5CF8(0, 0, object);
            *(u16 *)(object + 0x7C) = D_L03_001B0304;
            func_L00_003294F0(object, 1);
            *(s32 *)(object + 0x9C) = 0xF;
            *(u16 *)(object + 0x34) |= 2;
            func_002A7750(object, 2, -1);
        }
        break;
    }
}
