#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));
extern char D_L05_001B1310 __attribute__((sda));
extern char D_L05_001B1320 __attribute__((sda));
extern char D_L05_001B1330 __attribute__((sda));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(char *, void *, void *, void *, int);

/* Builds a unit vector pointing back along the object's -0.8 axis, rotated into the world, then
   fires three bursts, one from each of three copies of it, each with a random upward kick
   in the second vector's first word. */
void func_PAL_L05_00421BC0(char *object)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float v3[4];
    float v4[4];
    float v5[4];
    float f;
    float half;

    *(TI128 *)v0 = 0;
    *(TI128 *)v1 = 0;
    v0[0] = -0.8f;
    v0[3] = 1.0f;
    func_00283098(v2, v0, object + 0xC0);
    half = 0.5f;
    func_00282CC0(v2, v2, object + 0x10);
    v2[3] = 0.0f;
    *(TI128 *)v3 = *(TI128 *)v2;
    *(TI128 *)v4 = *(TI128 *)v2;
    *(TI128 *)v5 = *(TI128 *)v2;
    func_002ACB48(v2, 0.1f);
    func_002ACB48(v3, 0.1f);
    func_002ACB48(v4, 0.1f);
    func_002ACB48(v5, 0.1f);
    f = func_002A7878(7.5f, 10.0f);
    v1[0] = -(f * 0.020000001f) * half;
    func_L00_0033C0D0(object, v3, v1, &D_L05_001B1310, 1);
    f = func_002A7878(7.5f, 10.0f);
    v1[0] = -(f * 0.020000001f) * half;
    func_L00_0033C0D0(object, v4, v1, &D_L05_001B1320, 1);
    f = func_002A7878(7.5f, 10.0f);
    v1[0] = -(f * 0.020000001f) * half;
    func_L00_0033C0D0(object, v5, v1, &D_L05_001B1330, 1);
}
