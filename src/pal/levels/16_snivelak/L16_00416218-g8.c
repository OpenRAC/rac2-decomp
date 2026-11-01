#include "include_asm.h"

#include "common.h"
extern u8 *D_L16_001FE7C0[];
extern float D_L16_001B1750 __attribute__((sda));
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_002AAC80(float *, float, float, float, float);
extern float func_00283248(float, float);
extern float func_002AAA00(float *, float *, int, float, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A8D70(void *, float, int, int, float, float, int, int, int);
extern void func_L16_00410FA8(u8 *);

void func_PAL_L16_00416218(u8 *moby, float dt)
{
    float point[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *path = D_L16_001FE7C0[*(int *)(state + 0x170)];
    int finalPoint = 1;
    float distance, heading;
    float *orientation;
    *(float *)(moby + 0x48) = *(float *)(state + 0x230) * 2.4999998f;
    *(float *)(*(u8 **)(state + 0x1f0) + 0x48) = *(float *)(moby + 0x48);
    if (*(int *)(state + 0x220) == *(int *)(state + 0x1f4) && *(int *)(state + 0x224) == *(int *)(state + 0x1f8)) {
        qcopy(point, (state + 0x200));
    } else {
        int previous = *(int *)(state + 0x22c);
        if (previous == *(int *)(state + 0x220) || previous == *(int *)(state + 0x224) ||
            *(int *)(state + 0x228) != *(int *)(state + 0x220) || *(int *)(state + 0x228) != *(int *)(state + 0x224)) func_L16_00410FA8(moby);
        qcopy(point, (path + *(int *)(state + 0x228) * 16 + 16));
        finalPoint = 0;
    }
    orientation = (float *)(moby + 0xf8);
    func_00282CF0(delta, point, moby + 0x10);
    delta[2] = 0.0f;
    distance = func_00282DF0(delta);
    func_002AAC80((float *)(state + 0x230), distance, D_L16_001B1750 * 0.00040000002f, D_L16_001B1750 * 0.00040000002f, dt);
    heading = func_00283248(delta[0], delta[1]);
    func_002AAA00(orientation, (float *)(state + 0x234), 0, heading, 0.0025132746f, 0.0025132746f, 0.12566373f);
    func_00282F20(step, delta, *(float *)(state + 0x230));
    func_00282CC0(moby + 0x10, moby + 0x10, step);
    if (!*(int *)(state + 0x26c)) {
        func_002A8D70(moby, 6.0f, 0, 0x90000, 50.0f, 1.0f, 0, 1, 0);
        func_002A8D70(moby, 6.0f, 1, 0x90000, 50.0f, 1.0f, 0, 1, 0);
    }
    if (!finalPoint && distance < 0.5f) {
        int current = *(int *)(state + 0x228);
        int previous = *(int *)(state + 0x22c);
        if (previous < current) { *(int *)(state + 0x220) = previous; *(int *)(state + 0x224) = current; }
        else { *(int *)(state + 0x220) = current; *(int *)(state + 0x224) = previous; }
    }
}
