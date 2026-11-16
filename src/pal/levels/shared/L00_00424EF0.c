#include "include_asm.h"
#include "names.h"


extern float mat_fast_helper_a(float x, float y);
extern void FastVecSub(void *dst, void *a, void *b);
extern float math_random_float_range(float a, float b);
extern int FloatToInt(float value);
extern float g_camera_l00_position[];
extern float math_random_float_range(float a, float b);
extern float math_random_signed_float_range(float a, float b);
extern int FloatToInt(float a);
extern float FastAddRotations(float a, float b);
extern void vec_build_spherical_offset(float *p, float a, float b, float c);
extern void *func_PAL_002C23B8(float *out, float *in, int a2, int a3, unsigned int a4, int a5,
                           float f1, float f2, float f3, float f4, float f5);

/* Points the level's fixed vector at the given position, then spawns twenty
   particles around it, each one a random offset along the fixed vector.
   `size` is written but never read: that second reference to 210000.0f is what
   makes the compiler hold the constant in a saved float register ($f29) instead
   of rematerialising it at the call, which is what the retail does. */
void rocket_spawn_smoke_burst_pal(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float f20;
    float f21;
    float f28;
    float size;
    float r;
    int n;
    int id;

    FastVecSub(v, g_camera_l00_position, pos);
    f28 = mat_fast_helper_a(v[0], v[1]);
    n = 19;
    do {
        n--;
        f21 = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        size = math_random_float_range(0.05f, 0.2f) * 210000.0f;
        f20 = math_random_float_range(0.0f, 1.3962636f);
        r = FastAddRotations(f28, math_random_signed_float_range(0.0f, 1.3962636f));
        vec_build_spherical_offset(dir, f21 * (0.020000001f), r, f20);
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[0] = pos[0] + r;
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[1] = pos[1] + r;
        r = math_random_signed_float_range(0.0f, 0.1f);
        out[2] = pos[2] + r;
        func_PAL_002C23B8(out, dir, 25, 127, 0x7F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    } while (n >= 0);
}

