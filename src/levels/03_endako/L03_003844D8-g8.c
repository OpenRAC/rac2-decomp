#include "common.h"
typedef int ParticleQuad __attribute__((mode(TI)));
typedef struct { int id[16]; } ParticleIds;
extern char *g_linked_effect_records MACRO_ADDR;
extern float g_effect_count_scale __attribute__((sda)), g_effect_lower_bound __attribute__((sda));
extern float g_effect_upper_bound __attribute__((nosda)), g_effect_param_min __attribute__((nosda)), g_effect_param_max __attribute__((nosda));
extern float g_effect_velocity_min __attribute__((sda)), g_effect_velocity_max __attribute__((nosda)), g_effect_spread_min __attribute__((nosda)), g_effect_spread_max __attribute__((nosda));
extern unsigned int g_effect_color_start __attribute__((sda)), g_effect_color_end __attribute__((nosda)), g_effect_flags __attribute__((sda)), g_effect_start_value __attribute__((nosda)), g_effect_end_value __attribute__((nosda));
extern int math_fast_helper_a(void *, float);
extern float math_random_float_range(float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern void *part_spawn_trail(void *, void *, void *, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, int);
/* Spawns drifting particles around each of up to 16 linked effect entries. Fewer particles appear when the spot is far away. */
void linked_effect_spawn_particles(char *moby)
{
    float point[4], position[4], velocity[4], params[4];
    int i;
    ParticleIds *ids = *(ParticleIds **)(moby + 0x68);
    for (i = 0; i < 16; i++) {
        int index = ids->id[i];
        char *base = g_linked_effect_records;
        if (index != -1) {
            char *entry = (char *)(index * 128 + (unsigned int)base);
            float count = g_effect_count_scale * *(float *)(entry + 0x7C);
            qcopy(point, entry + 0x30);
            point[3] = *(float *)(entry + 0x3C);
            if (math_fast_helper_a(point, 64) == -1) count *= 0.5f;
            while (count > 0) {
                if (count >= 1 || math_random_float_range(0, 1) < count) {
                    unsigned int color;
                    *(ParticleQuad *)velocity = 0;
                    velocity[0] = math_random_float_range(-0.9f, 0.9f);
                    velocity[1] = math_random_float_range(-0.9f, 0.9f);
                    *(ParticleQuad *)position = *(ParticleQuad *)velocity;
                    matrix_mul_vec3(position, position, g_linked_effect_records + ids->id[i] * 128);
                    FastVecAdd(position, position, g_linked_effect_records + ids->id[i] * 128 + 0x30);
                    qzero_nc(velocity);
                    {
                        float upper = g_effect_upper_bound;
                        float lower = g_effect_lower_bound;
                        velocity[2] = math_random_float_range(lower, upper) * (1.0f/60.0f);
                    }
                    qzero_nc(params);
                    params[2] = math_random_float_range(g_effect_param_min, g_effect_param_max) * (1.0f/60.0f);
                    velocity[3] = math_random_float_range(g_effect_velocity_min, g_effect_velocity_max);
                    params[3] = math_random_float_range(g_effect_spread_min, g_effect_spread_max);
                    {
                        float blend = math_random_float_range(0, 1);
                        color = FastTweenColor(g_effect_color_start, g_effect_color_end, blend);
                    }
                    {
                        unsigned int flags = g_effect_flags;
                        unsigned int start = g_effect_start_value;
                        unsigned int end = g_effect_end_value;
                        part_spawn_trail(position, velocity, params, color, color & 0xFFFFFF, flags, start, end, -1);
                    }
                }
                count -= 1;
            }
        }
    }
}
