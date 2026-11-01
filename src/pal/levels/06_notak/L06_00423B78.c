#include "include_asm.h"

#include "common.h"
extern void func_00282CF0(char *, char *, char *);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_00282F20(char *, char *, float);
extern int func_002A77E0(int);
extern char D_L06_001B9840[];
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);

void func_PAL_L06_00423B78(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0((char *)direction, (char *)D_L06_001B9840, (char *)pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = func_002A7878(1.0f, 5.0f) * 0.020000001f;
        func_00282CC0((char *)origin, (char *)pos, (char *)offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 17, size * 0.1f, size, 0x7F801010, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 17, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


extern void func_002A7750(char *, int, int);
extern int func_00282948(char *);
extern void func_PAL_002A7E68(char *, int, int, int);

void func_PAL_L06_00423E58(char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    if (*(int *)(o + 0x5A0) == 1) {
        if (*(int *)(o + 0x23C) == -1) {
            if (func_00282948(o + 0x25C)) {
                func_002A7750(a0, 7, 2);
                if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                    func_PAL_002A7E68(a0, 0x13, 0, 17);
                }
                o[0x48] = func_00283CF0(20.0f);
                o[0x4A] = func_00283CF0(24.0f);
            }
        } else {
            func_002A7750(a0, 8, 2);
            if (*(unsigned char *)(a0 + 0x43) != 0x12) {
                func_PAL_002A7E68(a0, 0x12, 0, 17);
            }
            o[0x48] = func_00283CF0(20.0f);
            o[0x4A] = func_00283CF0(24.0f);
        }
    } else if (*(short *)(o + 0x492) != 0 && func_00282948(o + 0x25C)) {
        *(short *)(o + 0x492) = 0;
        func_002A7750(a0, 7, 2);
        if (!func_002A77E0(2)) {
            if (*(unsigned char *)(a0 + 0x43) != 0x11) {
                func_PAL_002A7E68(a0, 0x11, 0, 17);
            }
            o[0x48] = func_00283CF0(20.0f);
            o[0x4A] = func_00283CF0(24.0f);
        } else {
            if (*(unsigned char *)(a0 + 0x43) != 0x13) {
                func_PAL_002A7E68(a0, 0x13, 0, 17);
            }
            o[0x48] = func_00283CF0(20.0f);
            o[0x4A] = func_00283CF0(24.0f);
        }
    } else if (*(short *)(o + 0x492) == 0 && func_00282948(o + 0x25C)) {
        func_002A7750(a0, 9, 2);
        if (*(unsigned char *)(a0 + 0x43) != 0x12) {
            func_PAL_002A7E68(a0, 0x12, 0, 17);
        }
        o[0x48] = func_00283CF0(20.0f);
        o[0x4A] = func_00283CF0(24.0f);
    }
}

