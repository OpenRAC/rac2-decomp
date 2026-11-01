#include "include_asm.h"


#include "common.h"
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(char *, char *, float);
extern char D_L02_001BA500[];
extern float func_002A7878_range(float, float) __asm__("func_002A7878");
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int func_00283CF0(float);
extern int func_002A77E0(int);

/* Emits paired particles with opposite spin and randomized velocities. */
void func_PAL_L02_003C8738(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    func_00282CF0(direction, (float *)D_L02_001BA500, pos);
    func_00282F20((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878_range(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7878_range(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20((char *)velocity, (char *)velocity, func_002A7878_range(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = func_002A7878_range(1.0f, 5.0f) * 0.020000001f;
        func_00282CC0(origin, pos, offset);
        pos[0] += func_002A78D8(0, 0.15f);
        pos[1] += func_002A78D8(0, 0.15f);
        pos[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(origin, 50, size * 0.1f, size, 0xDDFF1010, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
        particle = func_002C2210(origin, 50, size * 0.07f, size * 0.7f, 0xDDFF1010, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}


