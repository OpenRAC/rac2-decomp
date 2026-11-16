#include "include_asm.h"
#include "names.h"

extern char *flare_spawn_pal(float *p, float a, int b, int c, int d, int e, int f, int g, int h, int i, int j);
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
extern char *part_spawn_burst_pal(float *out, float *dir, int a, int b, unsigned int color, int id,
                            float fa, float fb, float fc, float fd, float fe);
extern char g_camera_l00_position[];
extern char g_hero_state_block[];
extern char g_part_resident_buffer[];

/* Throws out a puff of grey smoke and bright sparks at a point. The sparks are red when the flag is set and green otherwise. (PAL: 50 Hz timings) */
void part_spawn_smoke_and_sparks_pal(float *position, int unused, int flag)
{
    float to_camera[4];
    float dir[4];
    float out[4];
    float camera_heading;
    float scale;
    float pitch;
    float angle;
    float random_value;
    int id;
    int i;
    unsigned int color;
    char *particle;
    char *q;

    if (flag != 0) {
        color = 0x7F2020FF;
        flare_spawn_pal(position, 0.25f, 0, 15, 10, 0, 20, 0, 0, 1, 0);
    } else {
        color = 0x7F20FF20;
    }
    FastVecSub((char *)to_camera, g_camera_l00_position, (char *)position);
    camera_heading = mat_fast_helper_a(to_camera[0], to_camera[1]);

    for (i = 19; i >= 0; i--) {
        random_value = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)dir, g_hero_state_block, -(random_value * 0.020000001f));
        id = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        random_value = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        out[0] = position[0] + math_random_signed_float_range(0.0f, 0.2f);
        out[1] = position[1] + math_random_signed_float_range(0.0f, 0.2f);
        out[2] = position[2] + math_random_signed_float_range(0.0f, 0.2f);
        particle = part_spawn_spinning_spark_pal((char *)out, 0.0f, 1.0f, 1.01f, random_value, id, (char *)dir, 0x7F202020, 0);
        if (particle != 0) {
            q = particle + 32;
            *(unsigned char *)(particle + 3) = 0x44;
            *(short *)(particle + 10) = 0x4B;
            *(unsigned char *)(particle + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(q + 0x1C) = IntToFloat(4);
            *(int *)(q + 4) = 3;
            *(unsigned char *)(q + 0xA) = 0x30;
            *(unsigned char *)(q + 0xB) = *(unsigned char *)(particle + 10);
        }
        scale = math_random_float_range(1.0f, 2.0f);
        pitch = math_random_float_range(0.0f, 1.396263599395752f);
        angle = FastAddRotations(camera_heading, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(dir, scale * 0.020000001f, angle, pitch);
        out[0] = position[0] + math_random_signed_float_range(0.0f, 0.1f);
        out[1] = position[1] + math_random_signed_float_range(0.0f, 0.1f);
        out[2] = position[2] + math_random_signed_float_range(0.0f, 0.1f);
        particle = part_spawn_burst_pal(out, dir, 25, 127, color, id,
                          math_random_float_range(0.25f, 0.7f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
        if (particle != 0) {
            char *tbl = g_part_resident_buffer;
            *(unsigned char *)(particle + 2) = *(unsigned char *)(*(char **)(tbl + 0x184) + 6);
        }
    }
}

