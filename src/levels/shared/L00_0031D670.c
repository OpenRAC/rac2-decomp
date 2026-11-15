#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

extern float math_lerp_float(float, float, float);

/* Blends each of the four parts of one vector toward another by the given amount. */
void LerpVector4(f32 *out, const f32 *from, const f32 *to, f32 amount) {
    u128 from_vec, to_vec;
    f32 *from_f = (f32 *)&from_vec;
    f32 *to_f = (f32 *)&to_vec;
    from_vec = *(const u128 *)from;
    to_vec = *(const u128 *)to;

    out[0] = math_lerp_float(from_f[0], to_f[0], amount);
    out[1] = math_lerp_float(from_f[1], to_f[1], amount);
    out[2] = math_lerp_float(from_f[2], to_f[2], amount);
    out[3] = math_lerp_float(from_f[3], to_f[3], amount);
}
