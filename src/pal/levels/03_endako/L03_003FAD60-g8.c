#include "include_asm.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;
extern u8 *func_PAL_L00_002D7850(s32 a0);
extern f32 func_00283248(f32 a, f32 b);
extern f32 func_00283B98(f32 a, f32 b);
extern f32 func_00283BE0(f32 a, f32 b);
extern void func_002AAA00(void *a0, void *a1, f32 a3, f32 a4, f32 a5, f32 a6, void *a2);
extern f32 D_L03_001B1090 __attribute__((sda));
extern f32 D_L03_001B1094 __attribute__((sda));
typedef struct { u8 pad[0x80]; f32 x, y; } Hero;
extern Hero D_00189E20;
extern u8 *D_L03_001B99D0 __attribute__((nosda));

void func_PAL_L03_003FAD60(u8 *entity) {
    u8 *state;
    u8 *obj;
    u8 *s0;
    f32 f0;
    f32 f12;
    f32 f13;
    f32 f14;
    f32 f15;
    f32 first;
    f32 local;

    state = *(u8 **)(entity + 0x68);
    if (entity[0x95] < 2)
        return;
    if (*(u8 **)(state + 0x2C8) == 0)
        *(u8 **)(state + 0x2C8) = func_PAL_L00_002D7850(5);
    obj = *(u8 **)(state + 0x2C8);
    { f32 x = D_L03_001B1090; f32 y = D_L03_001B1094;
    *(f32 *)obj = x;
    *(f32 *)(*(u8 **)(state + 0x2C8) + 4) = y; }

    f12 = *(f32 *)(entity + 0x10) - D_00189E20.x;
    f13 = *(f32 *)(entity + 0x14) - D_00189E20.y;
    s0 = *(u8 **)(D_L03_001B99D0 + 0x70);
    first = func_00283248(f12, f13);
    /* The base moves on between the two reads: combine cannot then fold the
     * second read's address, so retail's addiu and based load remain. */
    { f32 *rot = (f32 *)(s0 + 0x160);
    f12 = rot[0];
    s0 += 0x1C0;
    f13 = rot[1]; }
    f0 = func_00283248(f12, f13);

    f13 = 3.14159274f;
    f0 = func_00283B98(f0, f13);
    f0 = func_00283BE0(first, f0);

    f13 = 0.005026549f;
    f14 = f13;
    f15 = 0.25132746f;
    local = f0;
    f12 = 0.0f;
    func_002AAA00(&local, state + 0xCC, f12, f13, f14, f15, 0);

    *(f32 *)(s0 + 0x1C) = 1.0f;
    *(f32 *)(s0 + 0x14) = -*(f32 *)(state + 0xCC);
}
