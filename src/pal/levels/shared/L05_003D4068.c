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

/* Gives the object its reach: the table's entry for the object's id picks the record, and
 * the record takes the cone the object was given. */
void func_PAL_L05_003D4068(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(moby_get_motion_data(obj) + 0x148) = 1;
    func_PAL_L05_0037D610(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1BC) = -1;
    *(int *)(sub + 0x1C0) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(obj + 0x2C) = 0.06f;
    a = math_random_float_range(0.0f, *(float *)table);
    b = math_random_angle();
    c = math_random_angle();
    vec_build_spherical_offset(obj + 0x10, a, b, c);
    FastVecAdd(obj + 0x10, table + 0x30, obj + 0x10);
}


