#include "common.h"

/* func_PAL_L11_003F8E90, the PAL copy of func_L11_003F4A58: 1/60 becomes 0.02f, the particle lifetimes take the 50 Hz scale, and D_L11_001B0664 is scaled by 1.44f. */

extern float D_L11_001BA8C0[];

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

extern float D_L11_001B0654 __attribute__((sda));
extern float D_L11_001B0658 __attribute__((sda));
extern float D_L11_001B065C __attribute__((sda));
extern float D_L11_001B0660 __attribute__((sda));
extern float D_L11_001B0664 __attribute__((sda));
extern float D_L11_001B0668 __attribute__((sda));
extern float D_L11_001B066C __attribute__((sda));

void func_PAL_L11_003F8E90(char *pos, int count) {
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
    func_00282CF0(direction, D_L11_001BA8C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(D_L11_001B0668, D_L11_001B066C);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(D_L11_001B0654, D_L11_001B0658) * 0.020000001f;
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(D_L11_001B065C, D_L11_001B0660) * 0.020000001f;
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, ((s32)(60) * 5 + 2) / 6, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664 * 1.44f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, ((s32)(60) * 5 + 2) / 6, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664 * 1.44f);
        } else {
            func_00282CF0(extra, D_L11_001BA8C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, ((s32)(40) * 5 + 2) / 6, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, D_L11_001B0664 * 1.44f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, ((s32)(40) * 5 + 2) / 6, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, D_L11_001B0664 * 1.44f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}
