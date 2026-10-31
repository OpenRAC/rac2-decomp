/* func_L14_00422498: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections -g -frac2-qcopy.
   1052/1064 bytes; local checks reject every carrying release.
   Complete five 16-byte vectors and aligned 0x30 query storage. Grouped TI copies improve 1056 to 1052 bytes; explicit point cursors worsen to 1116 and remain private. Loop address formation, frame allocation and FP lifetimes differ. Both chained point arrays remain incomplete globals; no artificial bound or local padding is added.
   No linked match is claimed.
*/

#include "common.h"
typedef s32 Quad __attribute__((mode(TI)));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
typedef struct { Vector direction; void *owner; s32 flags; u8 type, count; u16 classId; f32 amount; s32 mode; f32 extra; } Query;
extern s32 D_L14_001B1618 __attribute__((sda));
extern f32 D_L14_001B1620 __attribute__((sda));
extern f32 D_L14_001B1638 __attribute__((sda)), D_L14_001B1640 __attribute__((sda));
extern f32 D_L14_001B1648 __attribute__((sda)), D_L14_001B164C __attribute__((sda));
extern f32 D_L14_001B1650 __attribute__((sda)), D_L14_001B1654 __attribute__((sda));
extern f32 D_L14_001B1658 __attribute__((sda)), D_L14_001B165C __attribute__((sda));
extern f32 D_L14_001B1670 __attribute__((sda)), D_L14_001B1674 __attribute__((sda));
extern u8 *D_L14_001FE1C0[];
extern u8 D_L14_002594F0[], D_L14_002594E0[], D_L14_00259630[];
extern u8 D_L14_001A8F20[], D_L14_001BF940[], D_00189E20[];
extern f32 func_002A7940(void), func_00283B98(f32, f32), func_002A78D8(f32, f32);
extern void func_00282C88(void *), func_00282CF0(void *, void *, void *), func_00282F20(void *, void *, f32);
extern void func_00282D30(void *, void *, f32), func_00282CC0(void *, void *, void *);
extern f32 func_002ABB18(f32), func_00283198(f32), func_00283180(f32), func_00283248(f32, f32);
extern void func_002A8C00(void *, void *, s32, void *, f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);

void func_L14_00422498(u8 *object)
{
    Vector cleared, direction, difference, step, offset;
    Query query;
    u8 *state = *(u8 **)(object + 0x68), *path;
    f32 scale = D_L14_001B1620 / (f32)D_L14_001B1618;
    f32 z, x, y, phase, wave, radius, angle, perturbation;
    s32 i;
    D_L14_001B1638 = func_002A7940();
    D_L14_001B1640 = func_002A7940();
    D_L14_001B1654 = func_00283B98(D_L14_001B1654, D_L14_001B1658);
    func_00282C88(&cleared);
    *(s32 *)(state + 0x2C) = D_L14_001B1618;
    func_00282CF0(&direction, state + 0x10, state);
    func_00282F20(&direction, &direction, 1.0f);
    func_00282D30(&step, &direction, scale);
    path = D_L14_001FE1C0[*(s32 *)(state + 0x34)];
    *(Quad *)(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280) = *(Quad *)(path + 0x10);
    *(Quad *)(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + 0x140) = *(Quad *)(path + 0x10);
    for (i = 1; i < D_L14_001B1618; i++) {
        z = func_002A78D8(D_L14_001B1670, D_L14_001B1674);
        x = func_002A78D8(D_L14_001B1670, D_L14_001B1674);
        y = func_002A78D8(D_L14_001B1670, D_L14_001B1674);
        *(Quad *)(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10) = *(Quad *)(path + (i + 1) * 0x10);
        F(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10, 8) += z;
        F(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10, 0) += x;
        F(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10, 4) += y;
        func_00282CF0(&difference, D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10,
                     D_L14_002594E0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10);
        phase = func_002ABB18(D_L14_001B1640 + (f32)i * D_L14_001B1648);
        wave = func_002ABB18(D_L14_001B1654 + (f32)i * D_L14_001B165C);
        radius = D_L14_001B164C * func_00283198(wave);
        *(Quad *)(D_L14_00259630 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10) = *(Quad *)(D_L14_002594F0 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10);
        radius *= func_00283198(phase);
        perturbation = radius + func_002A78D8(0.0f, 0.1f);
        F(D_L14_00259630 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10, 8) += perturbation;
        angle = func_00283B98(func_00283248(difference.f[0], difference.f[1]), 1.5707965f);
        radius = D_L14_001B1650 * func_00283180(phase);
        offset.f[0] = func_00283180(angle) * radius;
        offset.f[1] = func_00283198(angle) * radius;
        offset.f[2] = 0.0f;
        func_00282CC0(D_L14_00259630 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10,
                     D_L14_00259630 + *(s32 *)(state + 0x38) * 0x280 + i * 0x10, &offset);
        if (i >= 2 && (i == D_L14_001B1618 - 1 || !(i & 1))) {
            func_002A8C00(&query, object, 1, D_L14_001A8F20, 0.0f);
            query.classId = *(u16 *)(object + 0xAA);
            if (func_002761F8(path + (i - 1) * 0x10, path + (i + 1) * 0x10, 17, object, &query) &&
                *(u8 **)(D_L14_001BF940 + 0x18) == *(u8 **)(D_00189E20 + 0x2290)) {
                F(D_00189E20, 0x5B8) = 0.0f;
                F(D_00189E20, 0x5B0) = 0.0f;
            }
        }
    }
}
