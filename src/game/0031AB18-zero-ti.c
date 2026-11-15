#include "names.h"
typedef int Rac2TI128 __attribute__((mode(TI)));

extern float vec_get_heading_angle(char *a0, float *src, char *third);
extern float math_approach_target_with_direction_mode(void *out, float f12, float f13, float f14, float f15, char *in, int a2);
extern void euler_rotation_basis(void *out, void *in);
extern void multiply_matrix3x3(char *a0, char *a1, void *a2);
extern float math_fabs(float f);

/* Turns the object toward a direction and returns how much it turned. */
float moby_turn_toward_direction(char *moby, char *params, char *direction, char *extra)
{
    char scratch[0x50];
    float f;

    *(Rac2TI128 *)scratch = *(Rac2TI128 *)direction;
    f = vec_get_heading_angle(moby, (float *)scratch, extra);
    *(int *)(scratch + 0x40) = 0;
    math_approach_target_with_direction_mode(scratch + 0x40, f, *(float *)(params + 0x14), *(float *)(params + 0x18), 3.14159274f, params + 0xB4, 0);
    *(Rac2TI128 *)scratch = 0;
    *(float *)(scratch + 8) = *(float *)(params + 0xB4);
    euler_rotation_basis(scratch + 0x10, scratch);
    multiply_matrix3x3(moby + 0xC0, moby + 0xC0, scratch + 0x10);
    return math_fabs(f) - math_fabs(*(float *)(params + 0xB4));
}
