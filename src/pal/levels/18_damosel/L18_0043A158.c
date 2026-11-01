#include "include_asm.h"

#include "common.h"
extern float D_L18_001B97C0[];
extern float func_002A7878(float, float);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);

void func_PAL_L18_0043A158(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L18_001B97C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (0.020000001f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (0.020000001f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 50, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 50, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        } else {
            func_00282CF0(extra, D_L18_001B97C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 33, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.0028800003f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 33, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L18_0043A56C);


