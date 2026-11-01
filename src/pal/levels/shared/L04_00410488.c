#include "include_asm.h"


#include "common.h"
extern float func_002A7940(void);
extern float func_002A78D8(float, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_002C2210(void *, int, unsigned int, int, int, void *, float, float, float, int);
typedef unsigned int L04Quad __attribute__((mode(TI)));
extern int func_002A77E0(int);
extern float func_002A7878(float, float);
extern void func_00282D30(void *, void *, float);

void func_PAL_L04_00410678(L04Quad *position, L04Quad *direction, int count, int mode)
{
    float velocity[4], point[4], scaled[4], result[4];
    float size, angle, pitch;
    int sign, i;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.025f, 0.5f);
        sign = func_002A77E0(2);
        if (!sign) sign--;
        angle = func_002A7940();
        pitch = func_002A7878(0.6981318f, 1.5358899f);
        func_002AF000(velocity, func_002A7878(0.015000001f, 0.030000001f), angle, pitch);
        *(L04Quad *)scaled = *direction;
        func_00282D30(scaled, direction, func_002A7878(0.75f, 0.95f));
        if (mode) {
            velocity[0] *= 5.0f;
            velocity[1] *= 5.0f;
            size *= 3.0f;
        }
        func_00282CD8(result, velocity, scaled);
        qcopy(point, position);
        point[0] += func_002A78D8(0.0f, 0.0375f);
        point[1] += func_002A78D8(0.0f, 0.0375f);
        point[2] += func_002A78D8(0.0f, 0.0375f);
        func_002C2210(point, 25, 0x7f207f7f, 0, sign, velocity, size * 0.1f, size, 0.003f, 0);
        func_002C2210(point, 25, 0x7f7f7f7f, 1, -sign, velocity, size * 0.07f, size * 0.7f, 0.003f, 0);
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00410920);

INCLUDE_ASM("asm/pal/levels", func_PAL_L04_00410E40);
