#include "include_asm.h"




#include "common.h"
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
extern char g_camera_l20_position[];
extern char g_hero_state_block[];

/* Throws 20 bursts of sparks and smoke out from a point. */
void part_l20_spawn_spark_burst_pal(float *origin)
{
    float to_camera[4];
    float dir[4];
    float out[4];
    float camera_angle;
    float scale;
    float mag;
    float angle;
    float rand_value;
    int id;
    int i;
    char *effect;
    char *effect_data;

    FastVecSub((char *)to_camera, g_camera_l20_position, (char *)origin);
    camera_angle = mat_fast_helper_a(to_camera[0], to_camera[1]);

    for (i = 19; i >= 0; i--) {
        rand_value = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)dir, g_hero_state_block, -(rand_value * 0.020000001f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        rand_value = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        out[0] = origin[0] + math_random_signed_float_range(0.0f, 0.2f);
        out[1] = origin[1] + math_random_signed_float_range(0.0f, 0.2f);
        out[2] = origin[2] + math_random_signed_float_range(0.0f, 0.2f);
        effect = part_spawn_spinning_spark_pal((char *)out, 0.0f, 1.0f, 1.01f, rand_value, id, (char *)dir, 0x7F202020, 0);
        if (effect != 0) {
            effect_data = effect + 32;
            *(unsigned char *)(effect + 3) = 0x44;
            *(short *)(effect + 10) = 0x4B;
            *(unsigned char *)(effect + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(effect_data + 0x1C) = IntToFloat(4);
            *(int *)(effect_data + 4) = 3;
            *(unsigned char *)(effect_data + 0xA) = 0x30;
            *(unsigned char *)(effect_data + 0xB) = *(unsigned char *)(effect + 10);
        }
        scale = math_random_float_range(1.0f, 2.0f);
        mag = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(camera_angle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, mag);
        out[0] = origin[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = origin[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = origin[2] + math_random_signed_float_range(0.0f, 0.1f);
        part_spawn_burst_pal(out, dir, 25, 127, 0x007F7F7F, id,
                      math_random_float_range(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}

