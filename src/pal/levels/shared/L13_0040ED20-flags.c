#include "include_asm.h"
#include "names.h"

typedef int Rac2TI128 __attribute__((mode(TI)));
extern float vec_get_heading_angle(char *a0, void *out, char *a2);
extern float math_approach_target_with_direction_mode(void *out, float f12, float f13, float f14, float f15, char *in, int a2);
extern void euler_rotation_basis(void *out, void *in);
extern void multiply_matrix3x3(char *a0, char *a1, void *a2);
extern float math_fabs(float f);

/* Copies the caller's 16-byte block into a stack scratch area, runs the starter on it, then
   fills the scratch area's upper half from the state block's 0xB4 float and the pair helper
   before folding the starter's result against the state's own reading of that float: the
   twin of func_L00_003BFF68 with fixed turn rates. One `char scratch[0x50]` gives retail's
   frame. */
float func_PAL_L13_0040ED20(char *a0, char *a1, char *a2, char *a3)
{
    char scratch[0x50];
    float f;

    *(Rac2TI128 *)scratch = *(Rac2TI128 *)a2;
    f = vec_get_heading_angle(a0, scratch, a3);
    *(int *)(scratch + 0x40) = 0;
    math_approach_target_with_direction_mode(scratch + 0x40, f, 0.005026549f, 0.005026549f,
                  0.35744348f, a1 + 0xB4, 0);
    *(Rac2TI128 *)scratch = 0;
    *(float *)(scratch + 8) = *(float *)(a1 + 0xB4);
    euler_rotation_basis(scratch + 0x10, scratch);
    multiply_matrix3x3(a0 + 0xC0, a0 + 0xC0, scratch + 0x10);
    return math_fabs(f) - math_fabs(*(float *)(a1 + 0xB4));
}
