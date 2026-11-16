#include "include_asm.h"



#include "common.h"
extern float math_random_float_range(float a, float b);
extern float g_emitter_vertex_offsets[][4][137][4];
extern float g_emitter_vertex_speeds[][4][137];
extern float g_emitter_group_positions[][4][4];
extern int g_emitter_group_timers[][4], g_emitter_group_alphas[][4], g_emitter_group_fade_rates[][4];
extern float g_glow_effect_scales[] __attribute__((sda)), g_glow_effect_sizes[] __attribute__((sda));
extern float g_glow_effect_angles_a[] __attribute__((sda)), g_glow_effect_angles_b[] __attribute__((sda));
extern int g_glow_effect_alphas[] __attribute__((sda)), g_glow_effect_timers[] __attribute__((sda));
extern int g_glow_effect_blends[] __attribute__((sda));
extern int func_001163B0(void);
extern void vec_clear_128(void *);

/* Clears the four emitters' 137 vectors of the object's slot, gives each a random speed, and
   starts the emitters around the object's position with random fades and lifetimes. */
void func_PAL_L05_003D7130(char *obj)
{
    int *st = *(int **)(obj + 0x68);
    char *position = obj + 0x10;
    int i, j;
    float *v;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 137; j++) {
            float speed = math_random_float_range(0.5f, 4.0f);

            vec_clear_128(g_emitter_vertex_offsets[*st][i][j]);
            g_emitter_vertex_speeds[*st][i][j] = speed;
        }
        /* This slot and the actor position do not contain the private index. */
        qcopy_nc(g_emitter_group_positions[*st][i], position);
        g_emitter_group_timers[*st][i] = 5;
        g_emitter_group_alphas[*st][i] = func_001163B0() % 128 + 128;
        g_emitter_group_fade_rates[*st][i] = func_001163B0() % 2 + 6;
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)g_emitter_group_positions + offset);
            v[0] += jitter;
        }
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)g_emitter_group_positions + offset);
            v[1] += jitter;
        }
        {
            float jitter = math_random_float_range(0.0f, 0.5f) + -0.25f;
            int offset = i * 16 + *st * 64;

            v = (float *)((char *)g_emitter_group_positions + offset);
            v[2] += jitter;
        }
    }
    g_glow_effect_scales[*st] = 0.01f;
    g_glow_effect_alphas[*st] = 128;
    g_glow_effect_sizes[*st] = 0.1f;
    g_glow_effect_timers[*st] = 5;
    g_glow_effect_blends[*st] = 128;
    g_glow_effect_angles_a[*st] = 0.0f;
    g_glow_effect_angles_b[*st] = 0.0f;
}

