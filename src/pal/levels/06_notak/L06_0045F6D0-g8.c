#include "include_asm.h"

#include "common.h"
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_002A77E0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_PAL_L06_00380B10(void *, void *, int, float, float);
extern float D_L06_001B1AC0 __attribute__((sda));
extern float D_L06_001B1AC4 __attribute__((sda));
extern float D_L06_001B1AC8 __attribute__((sda));
extern float D_L06_001B1ACC __attribute__((sda));
extern float D_L06_001B1AD0 __attribute__((sda));
extern float D_L06_001B1AD4 __attribute__((sda));
extern float D_L06_001B1AD8 __attribute__((sda));
extern float D_L06_001B1ADC __attribute__((sda));
extern int D_L06_001B1AE0 __attribute__((sda));
extern int D_L06_001B1AE4 __attribute__((sda));
extern int D_L06_001B1AE8 __attribute__((sda));

void func_PAL_L06_00461850(char *a0) {
    float velocity[4], pos[4], offset[4];
    qcopy(pos, a0 + 0x10);
    pos[2] += 3.3f + func_002A7878(-0.05f, 0.05f);
    pos[0] += func_002A7878(-0.1f, 0.1f);
    pos[1] += func_002A7878(-0.1f, 0.1f);
    offset[0] = func_00283180(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[1] = func_00283198(*(float *)(a0 + 0xF8)) * 1.5f;
    offset[2] = 0;
    func_00282CC0(pos, pos, offset);
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.020000001f, D_L06_001B1ACC * 0.020000001f);
    func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE4, 0.5f, 50.4f);
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AC0 * 0.020000001f, D_L06_001B1AC4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AC8 * 0.020000001f, D_L06_001B1ACC * 0.020000001f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.5f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) != 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.020000001f, 0.036000002f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
    if (func_002A77E0(D_L06_001B1AE8) == 1) {
    velocity[0] = func_00283180(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[1] = func_00283198(*(float *)(a0 + 0xF8)) * func_002A7878(D_L06_001B1AD0 * 0.020000001f, D_L06_001B1AD4 * 0.020000001f);
    velocity[2] = 0;
    velocity[2] = func_002A7878(D_L06_001B1AD8 * 0.020000001f, D_L06_001B1ADC * 0.020000001f);
        func_PAL_L06_00380B10(pos, velocity, D_L06_001B1AE0, 0.75f, 50.4f);
    }
}
