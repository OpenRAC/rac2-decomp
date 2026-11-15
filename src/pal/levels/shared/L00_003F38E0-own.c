#include "common.h"

typedef int BurstWord128 __attribute__((mode(TI)));
typedef union { BurstWord128 word; float f[4]; } BurstVector;
typedef struct { unsigned int values[6]; } BurstColors;
extern BurstVector g_camera_l00_position __attribute__((nosda));
extern BurstColors D_L00_001B0840 __attribute__((nosda));
extern BurstColors D_L00_001B0858 __attribute__((nosda));
typedef struct { char pad[0x20]; float x, y, z; } BurstLight;
extern BurstLight D_L00_0029AEF0 __attribute__((nosda));
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int math_random_int_range(int, int);
extern char *part_spawn_spinning_debris(void *, void *, int, int, int);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void vec_clear_128(BurstWord128 *);
extern int math_random_int_below(int);
extern char *part_spawn_firework_spark(void *, void *, unsigned int, unsigned int, int, int, int, int, float, float);
extern char *moby_spawn_template_effect(void *, void *, int, int);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern char *part_spawn_spark(void *, void *, int, int, int, int, int, int, int, float);

void func_PAL_L00_003F38E0(char *object, BurstVector *position) {
    BurstVector delta, velocity, random;
    /* Both 24-byte local copies begin on observed 16-byte stack boundaries. */
    BurstColors colorsA __attribute__((aligned(16)));
    BurstColors colorsB __attribute__((aligned(16)));
    char *base;
    char *base2;
    BurstVector *vp;
    float distance, pitch, yaw, speed, rate;
    int i, j, k, a, b, lifetimeA, lifetimeB;
    int colorA, colorB;
    unsigned int *pa, *pb;
    rate = 0.020000001415610313f;
    base = object + 0xC0;
    FastVecSub(&delta, &g_camera_l00_position, position);
    distance = FastVecLength(&delta);
    random.word = 0;
    random.f[0] = math_random_float_range(-1.0f, 1.0f);
    random.f[1] = math_random_float_range(-1.0f, 1.0f);
    random.f[2] = math_random_float_range(-1.0f, 1.0f);
    delta.f[2] += distance * 0.5f;
    velocity.word = random.word;
    vec_scale_to_length(&velocity, &velocity, distance * 0.004000000189989805f);
    vec_scale_to_length(&delta, &delta, (distance + distance) * rate);
    FastVecAdd(&velocity, &velocity, &delta);
    vec_fast_divide_helper(&velocity, &velocity, 0.20000001788139343f);
    matrix_mul_vec3(&velocity, &velocity, base);
    lifetimeA = math_random_int_range(50, 75);
    part_spawn_spinning_debris(position, &velocity, lifetimeA, 0, 0);
    i = 8;
    do {
        i--;
        pitch = math_random_float_range(0.4363323450088501f, 0.7853982448577881f);
        yaw = math_random_angle();
        speed = math_random_float_range(13.0f, 20.0f);
        vec_build_spherical_offset(random.f, speed * 0.020000001415610313f, yaw, pitch);
        matrix_mul_vec3(&random, &random, object + 0xC0);
        lifetimeA = math_random_int_range(50, 75);
        part_spawn_spinning_debris(position, &random, lifetimeA, 1, 0);
    } while (i >= 0);
    vp = &velocity;
    vec_clear_128(&vp->word);
    j = 9;
    do {
        j--;
        speed = math_random_float_range(8.0f, 10.0f) * 0.020000001415610313f;
        colorsA = D_L00_001B0840;
        colorsB = D_L00_001B0858;
        pa = &colorsA.values[math_random_int_below(6)];
        pb = &colorsB.values[math_random_int_below(6)];
        lifetimeA = math_random_int_range(17, 33);
        lifetimeB = math_random_int_range(42, 58);
        part_spawn_firework_spark(position, vp, *pa, *pb, lifetimeA, lifetimeB, 0, 0,
                     600000.0f, speed * 1.5f);
    } while (j >= 0);
    D_L00_0029AEF0.x = D_L00_0029AEF0.z = D_L00_0029AEF0.y = 40.0f;
    moby_spawn_template_effect(&D_L00_0029AEF0, position, 0, 0);
    base2 = object + 0xC0;
    k = 49;
    do {
        k--;
        pitch = math_random_float_range(0.13962635397911072f, 0.6108652949333191f);
        yaw = math_random_angle();
        speed = math_random_float_range(16.0f, 30.0f);
        vec_build_spherical_offset(random.f, speed * 0.020000001415610313f, yaw, pitch);
        colorA = gfx_swap_packed_color_channels(0x4F007FFF, 0);
        colorB = gfx_swap_packed_color_channels(0x1F00007F, 0);
        matrix_mul_vec3(&random, &random, base2);
        lifetimeA = math_random_int_range(50, 100);
        part_spawn_spark(position, &random, colorA, colorB, lifetimeA - 10, 1, -1, -1, 0, 40000.0f);
    } while (k >= 0);
}
