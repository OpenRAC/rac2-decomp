#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_debris_burst_back_speed __attribute__((sda)), g_debris_burst_radius_max __attribute__((sda)), g_debris_burst_vertical_speed_range __attribute__((sda)), g_debris_burst_param_a_range __attribute__((sda)), g_debris_burst_param_b_range __attribute__((sda));
extern float g_debris_burst_state_value __attribute__((sda)), g_debris_burst_life __attribute__((sda));
extern int g_debris_burst_particle_count __attribute__((sda));
extern float g_debris_burst_size_range __attribute__((sda)), g_debris_burst_spin_range __attribute__((sda));
extern int g_debris_burst_color_pair __attribute__((sda)), g_debris_burst_count_range __attribute__((sda));
extern float g_debris_burst_rise_speed __attribute__((sda));
/* Each upper bound is the second word of its measured min/max pair.
 * The scalar lower bounds use GP loads; these views keep the upper loads absolute. */
extern float D_L03_001B05F0_1[] MACRO_ADDR, D_L03_001B0600_1[] MACRO_ADDR, D_L03_001B0608_1[] MACRO_ADDR, D_L03_001B0628_1[] MACRO_ADDR, D_L03_001B0620_1[] MACRO_ADDR;
extern int D_L03_001B0630_1[] MACRO_ADDR, D_L03_001B0638_1[] MACRO_ADDR;
extern char g_debris_burst_context[];
extern void vec_scale_to_length(void *, void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern char *cam_moby_create(void *, int, int, int, void *, void *, void *, int, float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern int math_random_int_range(int, int), math_random_int_below(int);
extern char *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);

/* Emits twelve objects followed by the configured randomized particle burst. */
void part_emit_debris_burst(char *obj)
{
    float velocityOffset[4], vector[4], particleVector[4], verticalVelocity[4];
    float angle, radius, param_a, param_b;
    int color, alpha, count;
    char *spawn, *particle;

    vec_scale_to_length(velocityOffset, obj + 0xc0, -(g_debris_burst_back_speed*(1.0f/60.0f)));
    { int i = 0; float param_a, param_b;
    do {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, g_debris_burst_radius_max)*(1.0f/60.0f);
        vector[0] = math_fast_sin_or_cos_a(angle)*radius;
        vector[1] = math_fast_sin_or_cos_b(angle)*radius;
        vector[2] = 0.0f;
        vector[2] = math_random_float_range(g_debris_burst_vertical_speed_range, D_L03_001B05F0_1[1])*(1.0f/60.0f);
        FastVecAdd(vector, vector, velocityOffset);
        param_a = math_random_float_range(g_debris_burst_param_a_range, D_L03_001B0600_1[1]);
        param_b = math_random_float_range(g_debris_burst_param_b_range, D_L03_001B0608_1[1]);
        spawn = cam_moby_create(obj, 2, *(short *)(obj + 0xaa), i, obj + 0x10, obj + 0xf0, vector, 255, param_a, param_b);
        { char *state = *(char **)(spawn + 0x68);
        float life = g_debris_burst_life*(1.0f/60.0f);
        *(float *)(state + 0x38) = g_debris_burst_state_value;
        *(float *)(state + 0x3c) = life; }
        i++;
    } while (i < 12);
    }
    { int i;
    for (i = 0;i<g_debris_burst_particle_count;i++) {
        char *context = g_debris_burst_context;
        *(TI128 *)particleVector = 0;
        particleVector[0] = math_random_signed_float_range(0.0f, 0.5f);
        particleVector[1] = math_random_signed_float_range(0.0f, 1.4f);
        particleVector[2] = math_random_float_range(0.3f, 1.5f);
        *(TI128 *)(vector) = *(TI128 *)(particleVector);
        matrix_mul_vec3(vector, vector, obj + 0xc0);
        FastVecAdd(vector, vector, obj + 0x10);
        param_a = math_random_float_range(g_debris_burst_size_range, D_L03_001B0628_1[1])*210000.0f;
        param_b = math_random_float_range(g_debris_burst_spin_range, D_L03_001B0620_1[1])*0.000277777785f;
        angle = math_random_float_range(0.0f, 1.0f);
        color = FastTweenColor(g_debris_burst_color_pair, D_L03_001B0630_1[1], angle);
        alpha = color>>24;
        count = math_random_int_range(g_debris_burst_count_range, D_L03_001B0638_1[1]);
        *(TI128 *)verticalVelocity = 0;
        verticalVelocity[2] = math_random_float_range(0.0f, g_debris_burst_rise_speed*(1.0f/60.0f));
        *(TI128 *)(particleVector) = *(TI128 *)(verticalVelocity);
        color&=0xffffff;
        particle = part_spawn_burst(vector, particleVector, count, alpha, color, math_random_int_below(3)-1, param_a, 500.0f, 1.0f, param_b, 0.0f);
        if (particle) {
            u8 type = **(u8 **)(context + 0x5c);
            particle[3] = 0x44;
            particle[2] = type;
        }
    }
    }
}
