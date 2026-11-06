#include "include_asm.h"
#include "common.h"

/* func_PAL_L05_00380258, the PAL copy of func_L05_0037DA58: the same C, where the duration is scaled
   to 50 Hz, 1.0f/60.0f becomes 0.020000001f and 0.002f becomes 0.0028800003f. */

extern float func_002A7878(float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
typedef unsigned int Quad37DA58 __attribute__((mode(TI)));
extern char D_L05_001B96C0[];
extern void func_00282F20(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, int, int, int, void *, int, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern unsigned char *D_L05_001FF240[];

void func_PAL_L05_00380258(float *position, int count, int color, int duration)
{
    float velocity[4], point[4], direction[4], axis[4], half[4];
    float size, angle;
    int sign, i;
    char *particle;
    *(Quad37DA58 *)axis = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    func_00282CF0(direction, D_L05_001B96C0, position);
    func_00282F20(half, direction, 0.5f);
    direction[2] = 0;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) --sign;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20(velocity, velocity, func_002A7878(0.05f, 3.0f) * 0.020000001f);
        velocity[2] = func_002A7878(1.0f, 5.0f) * 0.020000001f;
        func_00282CC0(point, position, half);
        position[0] += func_002A78D8(0, 0.15f);
        position[1] += func_002A78D8(0, 0.15f);
        position[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(position, ((s32)duration * 5 + 2) / 6, size * 0.1f, size, color, 0, sign, velocity, 0, 0.0028800003f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
        particle = func_002C2210(position, ((s32)duration * 5 + 2) / 6, size * 0.07f, size * 0.7f, 0x7f7f7f7f, 1, -sign, velocity, 0, 0.0028800003f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
    }
}
