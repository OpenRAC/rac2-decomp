#include "include_asm.h"
#include "common.h"

typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} Quad __attribute__((aligned(16)));

extern u8 g_tether_origin[];
extern s32 g_spray_max_count_base;
extern f32 g_spray_count_scale __attribute__((sda));
extern f32 g_spray_max_count_scale __attribute__((sda));
extern f32 fast_vec_dist(void *a0, void *a1);
extern f32 IntToFloat(s32 a0);
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_angle(void);
extern void matrix_mul_vec3(void *a0, void *a1, void *a2);
extern void FastVecAdd(void *a0, void *a1, void *a2);
extern char *bouncing_debris_create(void *a0, void *a1, void *a2);

/* Sprinkles particles along the object's height, scattered around it with random speeds. */
void part_spray_height(u8 *moby)
{
    u8 *state = *(u8 **)(moby + 0x68);
    f32 distance_scale = 60.0f / fast_vec_dist(g_tether_origin, moby + 0x10);
    f32 count;
    f32 step_size;
    f32 max_count;
    f32 height;
    s32 i;
    Quad position, scratch, random_vec;

    if (distance_scale > 2.2f)
        distance_scale = 2.7f;
    height = *(f32 *)(state + 0xA0);
    count = distance_scale * distance_scale * height * g_spray_count_scale;
    max_count = (f32)g_spray_max_count_base * g_spray_max_count_scale;
    step_size = height / count;
    if (count > max_count)
        count = max_count;
    for (i = 0; (f32)i < count; i++) {
        f32 progress = IntToFloat(i) * step_size;
        f32 spread = distance_scale + progress * 0.1f;

        scratch.q = 0;
        scratch.f[0] = math_random_signed_float_range(0.0f, spread);
        scratch.f[1] = math_random_signed_float_range(0.0f, spread);
        scratch.f[2] = progress;
        position.q = scratch.q;
        matrix_mul_vec3(&position, &position, moby + 0xC0);
        FastVecAdd(&position, &position, moby + 0x10);
        random_vec.q = 0;
        random_vec.f[0] = math_random_angle();
        random_vec.f[1] = math_random_angle();
        random_vec.f[2] = math_random_angle();
        scratch.q = random_vec.q;
        bouncing_debris_create(moby, &position, &scratch);
    }
}
