#include "common.h"

extern void math_fast_float_f(f32 *, f32 *);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern f32 g_shadow_direction[] __attribute__((sda));
extern f32 g_shadow_basis_axis[] __attribute__((sda));
extern f32 g_shadow_scaled_direction[4] __attribute__((sda));

/* Works out the three axes used to project a shadow from a direction, picking the smallest axis to build a stable base. */
void gfx_shadow_build_projection_basis(f32 *dir, f32 scale) {
    f32 v[4] __attribute__((aligned(16)));

    qcopy(g_shadow_direction, dir);
    math_fast_float_f(v, dir);
    FastVecScale(g_shadow_scaled_direction, g_shadow_direction, scale);
    if (v[0] < v[1]) {
        if (v[0] < v[2]) {
            g_shadow_basis_axis[0] = v[0];
            g_shadow_basis_axis[1] = v[2];
            g_shadow_basis_axis[2] = v[1];
        } else {
            g_shadow_basis_axis[0] = v[1];
            g_shadow_basis_axis[1] = v[0];
            g_shadow_basis_axis[2] = v[2];
        }
    } else if (v[1] < v[2]) {
        g_shadow_basis_axis[0] = v[2];
        g_shadow_basis_axis[1] = v[1];
        g_shadow_basis_axis[2] = v[0];
    } else {
        g_shadow_basis_axis[0] = v[1];
        g_shadow_basis_axis[1] = v[0];
        g_shadow_basis_axis[2] = v[2];
    }
    FastVecCross(g_shadow_basis_axis, g_shadow_basis_axis, g_shadow_direction);
    vec_scale_to_length(g_shadow_basis_axis, g_shadow_basis_axis, 1.0f);
}
