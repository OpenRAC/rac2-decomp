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
extern void *part_spawn_burst_pal(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);
extern float math_random_float_range(float, float);

/* Fifteen times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a random
   small amount on each axis and hand the result to the spawn helper with 210000.0f, 500.0f,
   1.0f, 0.0f and 0.0f; the original game role is unknown. */
void part_l00_spawn_spark_spray_2_pal(float *pos)
{
    float to_camera[4];
    float dir[4];
    float spawn_pos[4];
    float base_angle;
    float angle;
    float scale;
    float elevation;
    float speed;
    int id;
    int i;

    FastVecSub((char *)to_camera, g_camera_l00_position, (char *)pos);
    base_angle = mat_fast_helper_a(to_camera[0], to_camera[1]);

    for (i = 14; i >= 0; i--) {
        scale = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        elevation = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(base_angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, elevation);
        spawn_pos[0] = pos[0] + math_random_signed_float_range(0.0f, 0.1f);
        spawn_pos[1] = pos[1] + math_random_signed_float_range(0.0f, 0.1f);
        spawn_pos[2] = pos[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst_pal(spawn_pos, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}


