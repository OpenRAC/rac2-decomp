#include "include_asm.h"

#include "common.h"
extern float D_L16_001B16D0[4] __attribute__((sda));
extern float D_L16_001B16E0 __attribute__((sda));
extern u8 D_L16_00189EF0[] __attribute__((nosda));
extern void func_0029FC20(void *, s32, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L13_00412518(void *, void *, void *, s32, float);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);

void func_PAL_L16_00416C90(u8 *arg)
{
    float matrix[16];
    float origin[4];
    float direction[4];
    float offset[4];
    u8 *state;
    float angle;
    float radius;
    float zero = 0.0f;
    float scale = 0.020000001f;
    state = *(u8 **)(arg + 0x68);
    func_0029FC20(*(void **)(state + 0x1F0), 2, matrix);
    func_002830C0(origin, D_L16_001B16D0, matrix);
    func_00282CF0(direction, D_L16_00189EF0, origin);
    func_00282F20(direction, direction, D_L16_001B16E0 * scale);
    func_PAL_L13_00412518(arg, direction, origin, 0, (float)state[0x34]);
    angle = func_002A7940();
    radius = func_002A7878(zero, 4.0f);
    func_00282CF0(direction, D_L16_00189EF0, arg + 0x10);
    func_00282F20(direction, direction, -4.0f);
    func_00282CC0(direction, direction, D_L16_00189EF0);
    offset[0] = func_00283180(angle) * radius;
    offset[1] = func_00283198(angle) * radius;
    offset[2] = zero;
    func_00282CC0(direction, direction, offset);
    func_00282CF0(direction, direction, origin);
    func_00282F20(direction, direction, D_L16_001B16E0 * scale);
    func_PAL_L13_00412518(arg, direction, origin, 0, (float)state[0x34]);
}
