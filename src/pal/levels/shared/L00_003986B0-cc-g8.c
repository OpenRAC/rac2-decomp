#include "names.h"
/* func_PAL_L00_003986B0, the PAL copy of func_L00_00395428: the same C, where scale D_L00_001AF278; scale D_L00_001AF27C; scale D_L00_001AF278; scale D_L00_001AF27C; scale D_L00_001AF278; scale D_L00_001AF27C; rename func_002A7470 becomes func_PAL_002A7E68. */
/* Side-arc emitter: times the arcs' regrowth, then regrows or jitters each of the ten arcs.
 * Built with -G8 (the timers and lengths are read through $gp).
 */

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { char pad[0x2290]; char *object; int mode; } WorldState;
extern WorldState g_hero_state;
extern float g_weapon_effect_scale NOT_SDA;
extern short g_arc_timers[] MACRO_ADDR, g_arc_alphas[] MACRO_ADDR, g_arc_kinds[] MACRO_ADDR, g_arc_flags[] MACRO_ADDR;
extern int g_arc_duration_ticks_a __attribute__((sda));
extern int g_arc_duration_ticks_b __attribute__((sda));
extern float g_arc_effect_speed __attribute__((sda));
extern float g_arc_fade_scale __attribute__((sda));
extern int g_arc_cooldown_a, g_arc_cooldown_b;
extern Vector g_arc_points[][5];
/* The same arcs seen from 16 bytes before them, as in RAC1 (electric_bolt_branch_points_base). */
typedef struct { Vector hdr; Vector p[4]; } ArcBase;
extern ArcBase g_arc_bases[];
extern Vector g_camera_l00_position;
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float moby_get_anim_value(void *);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void part_spawn_random_direction_effect(void *, float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void UpdateScaledRecords(void);
/* func_L00_002E6EF8 in most levels; its address differs per level. */
extern void ref_L00_00395428_00(void *, void *);

void func_PAL_L00_003986B0(char *object)
{
    Vector origin, random, difference, offsets[5];
    int emitting = 0;
    int i, j, k, active;
    float distance;
    if (*(unsigned char *)(g_hero_state.object + 0x43) != 0x7B)
        g_weapon_effect_scale = 0.1f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 2;
        {
            int n;
            for (n = 0; n < 10; n++) {
                g_arc_timers[n] = 0;
                g_arc_kinds[n] = 2;
                g_arc_flags[n] = 1;
            }
        }
        g_arc_cooldown_a = (((int)(g_arc_duration_ticks_a) * 5 + 2) / 6);
        g_arc_cooldown_b = (((int)(g_arc_duration_ticks_b) * 5 + 2) / 6);
        break;
    case 2:
        if (g_hero_state.mode == 31) {
            distance = moby_get_anim_value(object);
            if (distance >= 6.0f) {
                emitting = 1;
                if (!math_fast_float_d(&g_arc_cooldown_a)) {
                    float elapsed = IntToFloat(g_arc_cooldown_a);
                    elapsed /= IntToFloat((((int)(g_arc_duration_ticks_a) * 5 + 2) / 6));
                    g_arc_fade_scale = 1.0f - elapsed;
                } else if (distance >= 12.0f) {
                    if (!math_fast_float_d(&g_arc_cooldown_b)) {
                        float elapsed = IntToFloat(g_arc_cooldown_b);
                        elapsed /= IntToFloat((((int)(g_arc_duration_ticks_b) * 5 + 2) / 6));
                        g_arc_fade_scale = elapsed;
                    } else {
                        g_arc_fade_scale = 0.0f;
                    }
                } else {
                    g_arc_fade_scale = 1.0f;
                }
            }
        } else {
            g_arc_cooldown_a = (((int)(g_arc_duration_ticks_a) * 5 + 2) / 6);
            g_arc_cooldown_b = (((int)(g_arc_duration_ticks_b) * 5 + 2) / 6);
            func_PAL_002A7E68(object, 1, 0, 10);
        }
        break;
    }
    FastVecScale(&origin, object + 0xD0, -0.5f);
    FastVecAdd(&origin, &origin, object + 0x10);
    active = 0;
    for (k = 0; k < 10; k++) {
        if (g_arc_timers[k]) {
            active = 1;
            break;
        }
    }
    if (!emitting && !active)
        return;
    for (i = 0; i < 10; i++) {
        if (--g_arc_timers[i] < 0)
            g_arc_timers[i] = 0;
        if (!g_arc_timers[i]) {
            if (emitting) {
                g_arc_timers[i] = 2;
                g_arc_alphas[i] = 64;
                part_spawn_random_direction_effect(&random, g_arc_effect_speed, g_arc_effect_speed);
                qcopy(&g_arc_points[i][0], &origin);
                {
                    float sign = 1.0f;
                    for (j = 1; j < 5; j++) {
                        FastVecSub(&difference, &g_arc_bases[i].p[j - 1], &g_camera_l00_position);
                        math_apply_axis_rotation_to_quat(&random, &random, &difference,
                                     math_random_float_range(0.174532949924469f, 0.7853982448577881f) * sign);
                        sign = -sign;
                        FastVecAdd(&g_arc_points[i][j], &g_arc_bases[i].p[j - 1], &random);
                    }
                }
            } else {
                /* Emits nothing, but gives this path a block of its own, so gcse puts the
                   next i there (the `b; addiu` after the regrow arm) and not before the test. */
                active = 0;
            }
        } else {
            for (j = 1; j < 5; j++) {
                FastVecSub(&offsets[j], &g_arc_points[i][j], &g_arc_bases[i].p[j - 1]);
                offsets[j].f[0] += math_random_signed_float_range(0.0f, 0.1f);
                offsets[j].f[1] += math_random_signed_float_range(0.0f, 0.1f);
                offsets[j].f[2] += math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_arc_points[i][0], &origin);
            for (j = 1; j < 5; j++)
                FastVecAdd(&g_arc_points[i][j], &g_arc_bases[i].p[j - 1], &offsets[j]);
            if (g_arc_timers[i] > 0)
                g_arc_alphas[i] = 32;
            else
                g_arc_alphas[i] = 0;
        }
    }
    ref_L00_00395428_00(UpdateScaledRecords, object);
}
