#include "common.h"

extern f32 D_001AC1A0[4] __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_002A77E0(int);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Two puffs at the object's offset point, each with a small random drift and growth. */
void func_002E9110(char *object)
{
    f32 position[4] __attribute__((aligned(16)));
    f32 from[4] __attribute__((aligned(16)));
    f32 to[4] __attribute__((aligned(16)));
    int i;

    matrix_mul_vec3(position, D_001AC1A0, object + 0xC0);
    FastVecAdd(position, position, object + 0x10);
    for (i = 0; i < 2; i++) {
        from[0] = func_002A7878(-0.008333334f, 0.008333334f);
        from[1] = func_002A7878(-0.008333334f, 0.008333334f);
        from[2] = func_002A7878(-0.008333334f, 0.008333334f);
        from[3] = func_002A7878(0.6f, 0.8f);
        qcopy(to, from);
        to[3] = from[3] + func_002A7878(0.1f, 0.2f);
        func_002BAA28(position, from, to, 0x30C0C0C0, 0x20C0C0C0, 4, 0x10, func_002A77E0(0xC) + 8, 0x17);
    }
}
