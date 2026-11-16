#include "common.h"

typedef unsigned int EffectQuad __attribute__((mode(TI)));
extern const EffectQuad g_exhaust_effect_offsets[3];
extern unsigned char g_exhaust_effect_params_a[], g_exhaust_effect_params_b[];
extern int g_exhaust_fade_timer __attribute__((sda));
extern unsigned char g_sound_state[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern float func_0033BB18(float, float);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern void snd_stop_voice(int);

/* `object` is a late copy of the parameter and `m` a copy of that copy: gcse's copy
   propagation follows one copy per pass, so its PRE pass hashes the addresses off
   `object`'s higher pseudo.  That puts the third vector's reaching register before
   those of m + 0x10 and m + 0xc0, the spill-slot order retail has; the next pass
   restores the parameter and leaves no copy in the output. */
/* Spawns exhaust puffs behind each of the racer's three engines, bigger and stronger as it speeds up. */
void racer_spawn_exhaust_effects(unsigned char *self)
{
    EffectQuad offsets[3];
    float velocity[4];
    float point[4], first[4], second[4], third[4];
    unsigned char *vars;
    unsigned char *effect_params;
    float strength, scale, fade, spread;
    int i, handle;

    *(EffectQuad *)velocity = 0;
    offsets[0] = g_exhaust_effect_offsets[0];
    offsets[1] = g_exhaust_effect_offsets[1];
    offsets[2] = g_exhaust_effect_offsets[2];
    {
        unsigned char *object = self;

        vars = *(unsigned char **)(object + 0x68);
        if (object[0xbc] == 3 || object[0xbc] == 4) g_exhaust_fade_timer = 0;
        strength = *(float *)(vars + 0x27c) * 9.999999f;
        if (strength > 1.0f) strength = 1.0f;
        else if (strength < 0.0f) strength = 0.0f;
        scale = *(float *)(vars + 0x30c) * 3.0f;
        if (scale > 1.0f) scale = 1.0f;
        else if (scale < 0.5f) scale = 0.5f;
        {
            unsigned char *m = object;

            for (i = 0; i < 3; i++) {
                if (i == 1) effect_params = g_exhaust_effect_params_b;
                else effect_params = g_exhaust_effect_params_a;
                matrix_mul_vec3(point, &offsets[i], m + 0xc0);
                FastVecAdd(point, point, m + 0x10);
                point[3] = 0.0f;
                qcopy(first, point);
                qcopy(second, point);
                qcopy(third, point);
                spread = strength * 0.01f;
                spread += 0.005f;
                vec_add_random_offset(first, spread);
                vec_add_random_offset(second, spread);
                vec_add_random_offset(third, strength * 0.009f + 0.005f);
                if (strength > 0.0f || g_exhaust_fade_timer > 0 || *(int *)(vars + 0x278) > 0) {
                    if (strength == 0.0f && *(int *)(vars + 0x278) == 0) {
                        fade = (float)g_exhaust_fade_timer * 0.033333335f;
                        g_exhaust_fade_timer--;
                    } else {
                        fade = 1.0f;
                        g_exhaust_fade_timer = 30;
                    }
                    spread = strength * 0.01f;
                    spread += 0.01f;
                    vec_add_random_offset(first, spread);
                    vec_add_random_offset(second, spread);
                    velocity[0] = (func_0033BB18(3.0f, 5.25f) + strength * 2.0f) * 0.016666668f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    part_spawn_object_relative_particle(m, first, velocity, effect_params + 0x30, 1);
                    velocity[0] = (func_0033BB18(1.0f, 2.25f) + strength * 3.0f) * 0.016666668f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    part_spawn_object_relative_particle(m, second, velocity, effect_params + 0x40, 1);
                    part_spawn_object_relative_particle(m, point, velocity, effect_params + 0x50, 1);
                } else {
                    handle = *(int *)(vars + 0x714);
                    if (handle != -1) {
                        unsigned char *record = g_sound_state + handle * 0x70;
                        if (*(unsigned char **)(record + 0x88) == m && record[0x74]) snd_stop_voice(handle);
                    }
                    *(int *)(vars + 0x714) = -1;
                    velocity[0] = (func_0033BB18(1.5f, 2.5f) + strength * 1.5f) * 0.016666668f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, first, velocity, effect_params, 1);
                    velocity[0] = (func_0033BB18(1.5f, 2.5f) + strength * 2.45f) * 0.016666668f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, second, velocity, effect_params + 0x10, 1);
                    velocity[0] = (func_0033BB18(1.5f, 2.5f) + strength * 3.25f) * 0.016666668f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, third, velocity, effect_params + 0x20, 1);
                }
            }
        }
    }
}
