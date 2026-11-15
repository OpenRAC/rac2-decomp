#include "names.h"
typedef int Rac2TI128 __attribute__((mode(TI)));

extern float func_002B04E0(char *a0, float *src, char *third);
extern void func_002AAA00(void *out, float f12, float f13, float f14, float f15, char *in, int a2);
extern void func_002833F0(void *out, void *in);
extern void func_00283738(char *a0, char *a1, void *a2);
extern float func_00282C48(float f);

/* Turns the object toward a direction and returns how much it turned. */
float func_0031AB18(char *moby, char *params, char *direction, char *extra)
{
    char scratch[0x50];
    float f;

    *(Rac2TI128 *)scratch = *(Rac2TI128 *)direction;
    f = GetHeadingAngleOfVector(moby, (float *)scratch, extra);
    *(int *)(scratch + 0x40) = 0;
    ApproachTargetWithDirectionMode(scratch + 0x40, f, *(float *)(params + 0x14), *(float *)(params + 0x18), 3.14159274f, params + 0xB4, 0);
    *(Rac2TI128 *)scratch = 0;
    *(float *)(scratch + 8) = *(float *)(params + 0xB4);
    euler_rotation_basis(scratch + 0x10, scratch);
    multiply_matrix3x3(moby + 0xC0, moby + 0xC0, scratch + 0x10);
    return FloatAbs(f) - FloatAbs(*(float *)(params + 0xB4));
}
