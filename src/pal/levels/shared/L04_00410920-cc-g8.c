#include "names.h"
/* func_PAL_L04_00410920, the PAL copy of func_L04_0040C368: the same C, where rename func_0033BB18 becomes func_002A7878. */
#include "common.h"

typedef unsigned int EffectQuad __attribute__((mode(TI)));
extern const EffectQuad g_exhaust_effect_offsets[3];
extern unsigned char g_exhaust_effect_params_a[], g_exhaust_effect_params_b[];
extern int g_exhaust_fade_timer __attribute__((sda));
extern unsigned char g_sound_state[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern void *part_spawn_object_relative_particle(void *, void *, void *, void *, int);
extern void snd_stop_voice(int);

/* `object` is a late copy of the parameter and `m` a copy of that copy: gcse's copy
   propagation follows one copy per pass, so its PRE pass hashes the addresses off
   `object`'s higher pseudo.  That puts the third vector's reaching register before
   those of m + 0x10 and m + 0xc0, the spill-slot order retail has; the next pass
   restores the parameter and leaves no copy in the output. */
void func_PAL_L04_00410920(unsigned char *self)
{
    EffectQuad offsets[3];
    float velocity[4];
    float point[4], first[4], second[4], third[4];
    unsigned char *p;
    unsigned char *parameters;
    float strength, scale, fade, spread;
    int i, handle;

    *(EffectQuad *)velocity = 0;
    offsets[0] = g_exhaust_effect_offsets[0];
    offsets[1] = g_exhaust_effect_offsets[1];
    offsets[2] = g_exhaust_effect_offsets[2];
    {
        unsigned char *object = self;

        p = *(unsigned char **)(object + 0x68);
        if (object[0xbc] == 3 || object[0xbc] == 4) g_exhaust_fade_timer = 0;
        strength = *(float *)(p + 0x27c) * 8.333333f;
        if (strength > 1.0f) strength = 1.0f;
        else if (strength < 0.0f) strength = 0.0f;
        scale = *(float *)(p + 0x30c) * 2.4999998f;
        if (scale > 1.0f) scale = 1.0f;
        else if (scale < 0.5f) scale = 0.5f;
        {
            unsigned char *m = object;

            for (i = 0; i < 3; i++) {
                if (i == 1) parameters = g_exhaust_effect_params_b;
                else parameters = g_exhaust_effect_params_a;
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
                if (strength > 0.0f || g_exhaust_fade_timer > 0 || *(int *)(p + 0x278) > 0) {
                    if (strength == 0.0f && *(int *)(p + 0x278) == 0) {
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
                    velocity[0] = (math_random_float_range(3.0f, 5.25f) + strength * 2.0f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    part_spawn_object_relative_particle(m, first, velocity, parameters + 0x30, 1);
                    velocity[0] = (math_random_float_range(1.0f, 2.25f) + strength * 3.0f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    velocity[0] *= fade;
                    part_spawn_object_relative_particle(m, second, velocity, parameters + 0x40, 1);
                    part_spawn_object_relative_particle(m, point, velocity, parameters + 0x50, 1);
                } else {
                    handle = *(int *)(p + 0x714);
                    if (handle != -1) {
                        unsigned char *record = g_sound_state + handle * 0x70;
                        if (*(unsigned char **)(record + 0x88) == m && record[0x74]) snd_stop_voice(handle);
                    }
                    *(int *)(p + 0x714) = -1;
                    velocity[0] = (math_random_float_range(1.5f, 2.5f) + strength * 1.5f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, first, velocity, parameters, 1);
                    velocity[0] = (math_random_float_range(1.5f, 2.5f) + strength * 2.45f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, second, velocity, parameters + 0x10, 1);
                    velocity[0] = (math_random_float_range(1.5f, 2.5f) + strength * 3.25f) * 0.020000001f;
                    velocity[0] = -velocity[0];
                    velocity[0] *= scale;
                    part_spawn_object_relative_particle(m, third, velocity, parameters + 0x20, 1);
                }
            }
        }
    }
}
