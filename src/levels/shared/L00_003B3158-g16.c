#include "include_asm.h"
#include "names.h"

extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(float *, float *, float *);
extern void matrix_mul_vec3(float *, float *, void *);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern float D_L00_001AFAE8 __attribute__((sda));
extern float D_L00_001AFAEC;
extern float D_L00_001AFAF8 __attribute__((sda));
extern float D_L00_001AFAFC;
extern int D_L00_001AFB00 __attribute__((sda));
extern int D_L00_001AFB04;
extern int D_L00_001AFB08 __attribute__((sda));
extern int D_L00_001AFB0C[] __attribute__((sda));
extern int D_L00_001AFB18 __attribute__((sda));
extern float D_L00_001AFB20[4] __attribute__((sda));
extern char g_camera_l00_position[];
extern float D_L00_001A8F20[4];

/* Spawns a few sparkles near the camera. */
void part_spawn_camera_sparkles(void)
{
    float point[4], velocity[4], scatter[4];
    int i = 0;
    unsigned char kind, random;
    matrix_mul_vec3(point, D_L00_001AFB20, g_camera_l00_position + 0x230);
    FastVecAdd(point, point, (float *)g_camera_l00_position);
    kind = math_random_int_range(D_L00_001AFB08, D_L00_001AFB0C[0]);
    random = math_random_int_below(255);
    part_spawn_hero_relative(point, D_L00_001A8F20, D_L00_001AFB00, kind, random, 0, D_L00_001AFAF8);
    vec_random_direction(velocity, D_L00_001AFAE8 * (1.0f / 60.0f), D_L00_001AFAEC * (1.0f / 60.0f));
    while (i < D_L00_001AFB18) {
        i++;
        vec_random_direction(scatter, 0.0f, 0.25f);
        FastVecAdd(scatter, scatter, point);
        kind = math_random_int_range(D_L00_001AFB0C[1], D_L00_001AFB0C[2]);
        random = math_random_int_below(255);
        part_spawn_hero_relative(scatter, velocity, D_L00_001AFB04, kind, random, 0, D_L00_001AFAFC);
    }
}

extern float D_L00_001AFB30 __attribute__((sda));
extern float D_L00_001AFB34;
extern float D_L00_001AFB40 __attribute__((sda));
extern float D_L00_001AFB44;
extern int D_L00_001AFB48[2][2] __attribute__((sda));
extern int D_L00_001AFB58 __attribute__((sda));
extern int D_L00_001AFB5C[] __attribute__((sda));

/* Spawns two small sparkles at a position, colored by the object's state. */
void part_spawn_two_colored_sparkles(char *object, void *position)
{
    float velocity[4];
    void *first = *(void **)(object + 0x68);
    unsigned char kind = math_random_int_range(D_L00_001AFB58, D_L00_001AFB5C[0]);
    int *color = &D_L00_001AFB48[(unsigned char)object[0xbc]][0];
    int *color2;
    unsigned char random = math_random_int_below(255);
    part_spawn_hero_relative(position, first, *color, kind, random, 0, D_L00_001AFB40);
    vec_random_direction(velocity, D_L00_001AFB30 * (1.0f / 60.0f), D_L00_001AFB34 * (1.0f / 60.0f));
    kind = math_random_int_range(D_L00_001AFB5C[1], D_L00_001AFB5C[2]);
    color2 = (int *)((char *)D_L00_001AFB48 + (((unsigned char)object[0xbc] << 3) | 4));
    random = math_random_int_below(255);
    part_spawn_hero_relative(position, velocity, *color2, kind, random, 0, D_L00_001AFB44);
}
