#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void func_00282CC0(void *out, void *a, void *b);
extern float func_002B0520(void *position);
extern void func_002B9180(void *object);
extern float D_L01_001B27A0[];
extern float D_L01_001B27B0 MACRO_ADDR;
extern float D_L01_001B27A8 MACRO_ADDR;

void func_L01_00331E08(char *object)
{
    float offset[4] __attribute__((aligned(16)));
    float test1[4] __attribute__((aligned(16)));
    float test2[4] __attribute__((aligned(16)));
    float *velocity = (float *)(object + 0x20);
    float *position;
    float height = velocity[3];
    float measured;
    int x;
    int y;
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f || *(float *)(object + 0x10) > 512.0f || *(float *)(object + 0x14) > 512.0f || *(float *)(object + 0x18) < height) {
        func_002B9180(object);
        return;
    }
    position = (float *)(object + 0x10);
    *(Quad *)offset = *(Quad *)velocity;
    x = (int)*(float *)(object + 0x10);
    y = (int)*(float *)(object + 0x14);
    offset[3] = 0.0f;
    func_00282CC0(position, position, offset);
    func_00282CC0(position, position, D_L01_001B27A0);
    if (x != (int)*(float *)(object + 0x10) || y != (int)*(float *)(object + 0x14)) {
        *(Quad *)test1 = *(Quad *)position;
        measured = func_002B0520(test1);
        if (D_L01_001B27B0 <= measured) {
            *(Quad *)test2 = *(Quad *)position;
            height = func_002B0520(test2);
        } else {
            height = D_L01_001B27B0;
        }
        if (*(float *)(object + 0x18) < height) {
            func_002B9180(object);
            return;
        }
    }
    offset[0] = 0.0f;
    offset[1] = 0.0f;
    offset[2] = -0.00013888889225199819f;
    offset[3] = 0.0f;
    func_00282CC0(velocity, offset, velocity);
    velocity[3] = height + D_L01_001B27A8;
}
