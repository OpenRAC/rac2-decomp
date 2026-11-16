#include "names.h"
/* func_PAL_L03_003D5360, the PAL copy of func_L03_003D11E0: the same C, where rename func_00273730 becomes func_PAL_002735D0; expr 0.016666668f becomes 0.020000001f; wrap func_002A7820(D_L03_001B0638, D_L03_001B0638_1[1]) (((i; rename func_002C16C0 becomes func_PAL_002C23B8. */
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
extern char *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern float math_random_signed_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern int FastTweenColor(int, int, float);
extern int math_random_int_range(int, int), math_random_int_below(int);
extern char *part_spawn_burst_pal(void *, void *, int, int, int, int, float, float, float, float, float);

/* Emits twelve objects followed by the configured randomized particle burst. */
void part_emit_debris_burst_pal(char *obj)
{
    float velocity_offset[4], vector[4], particle_vector[4], vertical_velocity[4];
    float angle, radius, size, spin;
    int color, alpha, count;
    char *spawn, *particle;

    vec_scale_to_length(velocity_offset, obj + 0xc0, -(g_debris_burst_back_speed*(0.020000001f)));
    { int i = 0; float param_a, param_b;
    do {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, g_debris_burst_radius_max)*(0.020000001f);
        vector[0] = math_fast_sin_or_cos_a(angle)*radius;
        vector[1] = math_fast_sin_or_cos_b(angle)*radius;
        vector[2] = 0.0f;
        vector[2] = math_random_float_range(g_debris_burst_vertical_speed_range, D_L03_001B05F0_1[1])*(0.020000001f);
        FastVecAdd(vector, vector, velocity_offset);
        param_a = math_random_float_range(g_debris_burst_param_a_range, D_L03_001B0600_1[1]);
        param_b = math_random_float_range(g_debris_burst_param_b_range, D_L03_001B0608_1[1]);
        spawn = cam_moby_create_pal(obj, 2, *(short *)(obj + 0xaa), i, obj + 0x10, obj + 0xf0, vector, 255, param_a, param_b);
        { char *state = *(char **)(spawn + 0x68);
        float life = g_debris_burst_life*(0.020000001f);
        *(float *)(state + 0x38) = g_debris_burst_state_value;
        *(float *)(state + 0x3c) = life; }
        i++;
    } while (i < 12);
    }
    { int i;
    for (i = 0;i<g_debris_burst_particle_count;i++) {
        char *context = g_debris_burst_context;
        *(TI128 *)particle_vector = 0;
        particle_vector[0] = math_random_signed_float_range(0.0f, 0.5f);
        particle_vector[1] = math_random_signed_float_range(0.0f, 1.4f);
        particle_vector[2] = math_random_float_range(0.3f, 1.5f);
        *(TI128 *)(vector) = *(TI128 *)(particle_vector);
        matrix_mul_vec3(vector, vector, obj + 0xc0);
        FastVecAdd(vector, vector, obj + 0x10);
        size = math_random_float_range(g_debris_burst_size_range, D_L03_001B0628_1[1])*210000.0f;
        spin = math_random_float_range(g_debris_burst_spin_range, D_L03_001B0620_1[1])*0.00040000002f;
        angle = math_random_float_range(0.0f, 1.0f);
        color = FastTweenColor(g_debris_burst_color_pair, D_L03_001B0630_1[1], angle);
        alpha = color>>24;
        count = (((int)(math_random_int_range(g_debris_burst_count_range, D_L03_001B0638_1[1])) * 5 + 2) / 6);
        *(TI128 *)vertical_velocity = 0;
        vertical_velocity[2] = math_random_float_range(0.0f, g_debris_burst_rise_speed*(0.020000001f));
        *(TI128 *)(particle_vector) = *(TI128 *)(vertical_velocity);
        color&=0xffffff;
        particle = part_spawn_burst_pal(vector, particle_vector, count, alpha, color, math_random_int_below(3)-1, size, 500.0f, 1.0f, spin, 0.0f);
        if (particle) {
            u8 type = **(u8 **)(context + 0x5c);
            particle[3] = 0x44;
            particle[2] = type;
        }
    }
    }
}
