#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *D_L16_001B16C0 __attribute__((sda));
extern float D_L16_001B1780 __attribute__((sda));
extern float D_L16_001B1784 __attribute__((sda));
extern float D_L16_001B1788 __attribute__((sda));
extern float D_L16_001B1790[4] __attribute__((sda));
extern void func_0029FC20(void *, s32, void *);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7878(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_PAL_L16_00412A98(void *, void *, s32);
extern s32 func_002761F8(void *, void *, s32, void *, s32);

void func_PAL_L16_00416A50(u8 *arg)
{
    float matrix[16];
    float origin[4];
    float forward[4];
    float random[4];
    float hero[4];
    float child[4];
    float target[4];
    u8 *state;
    u8 **children;
    s32 index;
    float angle;
    float zero;
    float degree;
    float spread;
    if (D_L16_001B16C0) {
        state = *(u8 **)(arg + 0x68);
        children = (u8 **)(state + 0x238);
        func_0029FC20(*(u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2)), 0, matrix);
        children = (u8 **)((u32)children + (*(s32 *)(state + 0x240) << 2));
        func_PAL_002A7E68(*children, 1, 0, 3);
        *(TI128 *)origin = *(TI128 *)(matrix + 12);
        func_00282F20(forward, matrix, 20.0f);
        func_00282CC0(forward, forward, origin);
        *(TI128 *)hero = *(TI128 *)(D_L16_001B16C0 + 0x10);
        hero[2] += 2.0f;
        zero = 0.0f;
        degree = 0.017453294f;
        angle = func_00283248(*(float *)(arg + 0x10) - *(float *)(D_L16_001B16C0 + 0x10), *(float *)(arg + 0x14) - *(float *)(D_L16_001B16C0 + 0x14));
        spread = func_002A78D8(zero, D_L16_001B1780);
        angle = func_00283B98(angle, spread * degree);
        spread = func_002A7878(zero, D_L16_001B1784);
        func_002AF000(random, D_L16_001B1788, angle, spread * degree);
        func_00282CC0(random, random, hero);
        func_PAL_L16_00412A98(arg, origin, 150);
        index = (*(s32 *)(state + 0x240) + 1) & 1;
        *(s32 *)(state + 0x240) = index;
        *(TI128 *)child = *(TI128 *)D_L16_001B1790;
        if (index) child[1] = -child[1];
        func_00283098(child, child, *(u8 **)(state + 0x1F0) + 0xC0);
        func_00282CC0(child, child, *(u8 **)(state + 0x1F0) + 0x10);
        *(TI128 *)target = *(TI128 *)(D_L16_001B16C0 + 0x10);
        target[2] += 4.0f;
        if (func_002761F8(child, target, 2, *(u8 **)(state + 0x1F0), 0))
            *(s32 *)(state + 0x240) = (*(s32 *)(state + 0x240) + 1) & 1;
    }
}
