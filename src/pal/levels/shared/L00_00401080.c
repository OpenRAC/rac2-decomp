#include "include_asm.h"
#include "names.h"

extern char g_camera_l00_position[];
extern void FastVecSub(char *, char *, char *);
extern float mat_fast_helper_a(float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void *func_PAL_002C23B8(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);
extern float math_random_float_range(float, float);

/* Fifteen times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a random
   small amount on each axis and hand the result to the spawn helper with 210000.0f, 500.0f,
   1.0f, 0.0f and 0.0f; the original game role is unknown. */
void part_l00_spawn_spark_spray_2_pal(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    FastVecSub((char *)v, g_camera_l00_position, (char *)pos);
    ang = mat_fast_helper_a(v[0], v[1]);

    for (i = 14; i >= 0; i--) {
        scale = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, mag);
        out[0] = pos[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = pos[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = pos[2] + math_random_signed_float_range(0.0f, 0.1f);
        func_PAL_002C23B8(out, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}


