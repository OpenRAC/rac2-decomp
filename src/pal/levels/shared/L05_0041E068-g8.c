#include "names.h"
/* func_PAL_L05_0041E068, the PAL copy of func_L05_00419370: the same C, where both effect lifetimes are scaled for 50 Hz. */
#include "common.h"

extern int g_current_map_index;
typedef struct { char pad[0x68]; char *state; char rest[0x94]; } EffectOwner;
extern EffectOwner *g_feltzin_target_mobys;
extern int g_level_effect_enabled __attribute__((sda));
/* The resident level index is also read through its GP address view. */
extern int current_level_gp SDATA(D_001A79F0);
extern float g_effect_direction_vec[4] __attribute__((sda));
extern int coll_is_point_inside_unit_sphere(void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);
extern char *SpawnSpinningSparkParticle(void *, float, float, int, void *, int, float, float, int);
extern int math_random_int_range(int, int);
extern int FloatToInt(float);

/* Updates the trail particles around the beam object and draws them as sprites (PAL: both effect lifetimes scaled for 50 Hz). */
void UpdateBeamTrailParticles_pal(char *object)
{
    float back_step[4];
    char *state = *(char **)(object + 0x68);
    char *target_vars;
    char *axis;
    float step, size;
    char *effect, *detail;
    int sprite_kind, life_divisor;

    if (g_current_map_index == 5 || g_current_map_index == 25) {
        target_vars = ((EffectOwner *)((char *)g_feltzin_target_mobys + (*(int *)(state + 0xA4) << 8)))->state;
        if (g_current_map_index == 25 ||
            (!coll_is_point_inside_unit_sphere(object + 0x10, *(int *)(target_vars + 4)) &&
             !coll_is_point_inside_unit_sphere(object + 0x10, *(int *)(target_vars + 8)) &&
             !coll_is_point_inside_unit_sphere(object + 0x10, *(int *)(target_vars + 12)) &&
             !coll_is_point_inside_unit_sphere(object + 0x10, *(int *)(target_vars + 16)))) {
            char *p;
            float *life;
            int i;

            axis = object + 0xC0;
            p = state + 0xB0;
            life = (float *)(state + 0x1B0);
            for (i = 15; i >= 0; i--) {
                if (*life <= 0.0f) {
                    qcopy(p, axis);
                    *(float *)(p) += math_random_float_range(-0.2f, 0.2f);
                    *(float *)(p + 4) += math_random_float_range(-0.2f, 0.2f);
                    *(float *)(p + 8) += math_random_float_range(-0.2f, 0.2f);
                    vec_scale_to_length(p, p, math_random_float_range(24.0f, 30.0f));
                    FastVecAdd(p, p, object + 0x10);
                    *life = math_random_float_range(11.0f, 14.0f);
                }
                qcopy(back_step, axis);
                step = math_random_float_range(0.15f, 0.25f);
                vec_scale_to_length(back_step, back_step, -step);
                *life -= step;
                FastVecAdd(p, p, back_step);
                size = math_random_float_range(0.07f, 0.12f);
                step = math_random_float_range(0.0f, 1.0f);
                gfx_draw_billboard_quad(p, 0x47, 0x7F7F6464, 0, size, 0.0f, step);
                life++;
                p += 16;
            }
        }
    }
    if (g_level_effect_enabled && current_level_gp == 15) {
        float *life = (float *)(state + 0x1B0);
        int i;

        axis = object + 0xC0;
        sprite_kind = 0x44;
        life_divisor = 6;
        state += 0xB0;
        for (i = 3; i >= 0; i--) {
            if (*life <= 0.0f) {
                qcopy(state, axis);
                *(float *)state += math_random_float_range(-0.2f, 0.2f);
                *(float *)(state + 4) += math_random_float_range(-0.2f, 0.2f);
                *(float *)(state + 8) += math_random_float_range(-0.2f, 0.2f);
                vec_scale_to_length(state, state, math_random_float_range(15.0f, 30.0f));
                FastVecAdd(state, state, object + 0x10);
                *life = math_random_float_range(10.0f, 30.0f);
            }
            qcopy(back_step, axis);
            step = math_random_float_range(0.15f, 0.25f);
            vec_scale_to_length(back_step, back_step, -step);
            *life -= step;
            FastVecAdd(state, state, back_step);
            effect = SpawnSpinningSparkParticle(state, 2.0f, 1.03f, 1, g_effect_direction_vec, 0x0A786E64, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = sprite_kind;
                *(short *)(effect + 10) = (math_random_int_range(40, 70) * 5 + 2) / life_divisor;
            }
            effect = SpawnSpinningSparkParticle(state, 1.8f, 1.03f, 1, g_effect_direction_vec, 0x0AADA196, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = sprite_kind;
                detail = effect + 0x20;
                *(short *)(effect + 10) = (math_random_int_range(40, 70) * 5 + 2) / life_divisor;
                effect[9] = FloatToInt(4.0f) + 0x40;
                *(float *)(detail + 0x1C) = 20.0f;
                *(int *)(detail + 4) = 3;
                detail[10] = 0x7F;
                detail[11] = effect[10];
            }
            state += 16;
            life++;
        }
    }
}
