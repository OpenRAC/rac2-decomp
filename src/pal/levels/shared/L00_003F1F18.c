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
extern void FastVecSub(char *local, char *first, char *second);
extern float mat_fast_helper_a(float a, float b);
extern void FastVecScale(char *dst, char *src, float scale);
extern float math_random_float_range(float a, float b);
extern float math_random_signed_float_range(float a, float b);
extern int FloatToInt(float f);
extern float IntToFloat(int v);
extern float FastAddRotations(float a, float b);
extern void vec_build_spherical_offset(float *p, float a, float b, float c);
extern char *part_spawn_spinning_spark_pal(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);
extern void *part_spawn_burst_pal(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);
extern char g_camera_l00_position[];
extern char g_hero_state_block[];

/* Twenty times over: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   scale the hero facing direction by a random small amount, spawn a particle at the point
   jittered by a random amount on each axis and fill the new record's fields, then spawn a
   second particle along a random direction with a random magnitude; the original game role
   is unknown. */
void part_l00_spawn_impact_spark_burst_pal(float *origin)
{
    float to_camera[4];
    float dir[4];
    float out[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float f;
    int id;
    int i;
    char *particle;
    char *record;

    FastVecSub((char *)to_camera, g_camera_l00_position, (char *)origin);
    ang = mat_fast_helper_a(to_camera[0], to_camera[1]);

    for (i = 19; i >= 0; i--) {
        f = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)dir, g_hero_state_block, -(f * 0.020000001f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        f = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        out[0] = origin[0] + math_random_signed_float_range(0.0f, 0.2f);
        out[1] = origin[1] + math_random_signed_float_range(0.0f, 0.2f);
        out[2] = origin[2] + math_random_signed_float_range(0.0f, 0.2f);
        particle = part_spawn_spinning_spark_pal((char *)out, 0.0f, 1.0f, 1.01f, f, id, (char *)dir, 0x7F202020, 1);
        if (particle != 0) {
            record = particle + 32;
            *(unsigned char *)(particle + 3) = 0x44;
            *(short *)(particle + 10) = 0x4B;
            *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(record + 0x1C) = IntToFloat(4);
            *(int *)(record + 4) = 3;
            *(unsigned char *)(record + 0xA) = 0x30;
            *(unsigned char *)(record + 0xB) = *(unsigned char *)(particle + 10);
        }
        scale = math_random_float_range(1.0f, 2.0f);
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, mag);
        out[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst_pal(out, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}


/* Twenty rounds: take the angle of the constant vector at D_L00_001B8DC0 and the point,
   build a direction from a random step and a random magnitude, jitter the point by a
   random small amount on each axis and hand the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
void part_spawn_small_spark_burst_pal(float *origin)
{
    float to_camera[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    FastVecSub((char *)to_camera, g_camera_l00_position, (char *)origin);
    ang = mat_fast_helper_a(to_camera[0], to_camera[1]);

    for (i = 19; i >= 0; i--) {
        scale = math_random_float_range(0.5f, 1.0f);
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        math_random_float_range(0.05f, 0.2f);
        speed = 210000.0f;
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, mag);
        out[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst_pal(out, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

