#include "include_asm.h"

#include "common.h"
extern void vec_build_spherical_offset(void *, float, float, float);
extern int D_L05_00221D10[];
extern float math_random_float_range(float, float);
extern char *moby_get_motion_data(char *);
extern void FastVecAdd(void *, void *, void *);
extern int D_L05_00221D10[];
extern char *D_L05_001B2614 __attribute__((sda));
extern void func_PAL_L05_0037D610(char *, int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);

/* func_L05_003D1368 is in L05_003D1368-g8.c. */

/* func_L05_003D15E8 is in L05_003D15E8.c. */

void func_PAL_L05_003D5628(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(obj) + 0x148) = 5;
    func_PAL_L05_0037D610(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x2F0) = -1;
    *(int *)(sub + 0x2F4) = -1;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.04f;
    a = math_random_float_range(0.0f, *(float *)table);
    b = math_random_angle();
    c = math_random_angle();
    vec_build_spherical_offset(obj + 0x10, a, b, c);
    FastVecAdd(obj + 0x10, table + 0x30, obj + 0x10);
    *(int *)(sub + 0x26C) = 0;
}
