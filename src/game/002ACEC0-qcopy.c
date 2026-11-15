#include "names.h"
/* func_002ACEC0 in its own unit: it copies a 128-bit vector with both
   addresses in registers, the compiler's opt-in grouped copy
   (config/cflags.txt gives this file -frac2-qcopy). */

#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_fabs(float);
extern void vec_scale_to_length(float *, float *, float);
extern void math_build_axis_angle_quat(float *, float *, float);
extern void vec_rotate_by_quaternion(void *, void *, float *);

/* Blends dst towards src along the axis by amount; when the amount is (almost)
   zero dst is just set to src. func_00282C48 is the absolute value. */
void math_apply_axis_rotation_to_quat(void *dst, void *src, float *axis, float amount)
{
    float v[4];

    if (math_fabs(amount) < 1e-5f) {
        *(TI128 *)dst = *(TI128 *)src;
    } else {
        vec_scale_to_length(v, axis, 1.0f);
        math_build_axis_angle_quat(v, v, amount);
        vec_rotate_by_quaternion(dst, src, v);
    }
}
