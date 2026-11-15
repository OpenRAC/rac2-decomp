/* Side-arc emitter: times the arcs' regrowth, then regrows or jitters each of the ten arcs.
 * Built with -G8 (the timers and lengths are read through $gp).
 */

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { char pad[0x2290]; char *object; int mode; } WorldState;
extern WorldState g_hero_state;
extern float D_L00_0025C64C NOT_SDA;
extern short D_L00_001B2778[] MACRO_ADDR, D_L00_001B2790[] MACRO_ADDR, D_L00_001B27A8[] MACRO_ADDR, D_L00_001B27C0[] MACRO_ADDR;
extern int D_L00_001AF278 __attribute__((sda));
extern int D_L00_001AF27C __attribute__((sda));
extern float D_L00_001AF274 __attribute__((sda));
extern float D_L00_001B27DC __attribute__((sda));
extern int D_L00_001B27D4, D_L00_001B27D8;
extern Vector D_L00_00239EF0[][5];
/* The same arcs seen from 16 bytes before them, as in RAC1 (electric_bolt_branch_points_base). */
typedef struct { Vector hdr; Vector p[4]; } ArcBase;
extern ArcBase D_L00_00239EE0[];
extern Vector g_camera_l00_position;
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float moby_get_anim_value(void *);
extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern void anim_start_blended(void *, int, int, int);
extern void part_spawn_random_direction_effect(void *, float, float);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void UpdateScaledRecords(void);
/* func_L00_002E6EF8 in most levels; its address differs per level. */
extern void ref_L00_00395428_00(void *, void *);

/* Updates the lightning arcs on the side of the hero while the special move is held. */
void UpdateLightningArcs(char *object)
{
    Vector origin, random, difference, offsets[5];
    int emitting = 0;
    int i, j, k, active;
    float distance;
    if (*(unsigned char *)(g_hero_state.object + 0x43) != 0x7B)
        D_L00_0025C64C = 0.1f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned char *)(object + 0x20) = 2;
        {
            int n;
            for (n = 0; n < 10; n++) {
                D_L00_001B2778[n] = 0;
                D_L00_001B27A8[n] = 2;
                D_L00_001B27C0[n] = 1;
            }
        }
        D_L00_001B27D4 = D_L00_001AF278;
        D_L00_001B27D8 = D_L00_001AF27C;
        break;
    case 2:
        if (g_hero_state.mode == 31) {
            distance = moby_get_anim_value(object);
            if (distance >= 6.0f) {
                emitting = 1;
                if (!math_fast_float_d(&D_L00_001B27D4)) {
                    float elapsed = IntToFloat(D_L00_001B27D4);
                    elapsed /= IntToFloat(D_L00_001AF278);
                    D_L00_001B27DC = 1.0f - elapsed;
                } else if (distance >= 12.0f) {
                    if (!math_fast_float_d(&D_L00_001B27D8)) {
                        float elapsed = IntToFloat(D_L00_001B27D8);
                        elapsed /= IntToFloat(D_L00_001AF27C);
                        D_L00_001B27DC = elapsed;
                    } else {
                        D_L00_001B27DC = 0.0f;
                    }
                } else {
                    D_L00_001B27DC = 1.0f;
                }
            }
        } else {
            D_L00_001B27D4 = D_L00_001AF278;
            D_L00_001B27D8 = D_L00_001AF27C;
            anim_start_blended(object, 1, 0, 12);
        }
        break;
    }
    FastVecScale(&origin, object + 0xD0, -0.5f);
    FastVecAdd(&origin, &origin, object + 0x10);
    active = 0;
    for (k = 0; k < 10; k++) {
        if (D_L00_001B2778[k]) {
            active = 1;
            break;
        }
    }
    if (!emitting && !active)
        return;
    for (i = 0; i < 10; i++) {
        if (--D_L00_001B2778[i] < 0)
            D_L00_001B2778[i] = 0;
        if (!D_L00_001B2778[i]) {
            if (emitting) {
                D_L00_001B2778[i] = 2;
                D_L00_001B2790[i] = 64;
                part_spawn_random_direction_effect(&random, D_L00_001AF274, D_L00_001AF274);
                qcopy(&D_L00_00239EF0[i][0], &origin);
                {
                    float sign = 1.0f;
                    for (j = 1; j < 5; j++) {
                        FastVecSub(&difference, &D_L00_00239EE0[i].p[j - 1], &g_camera_l00_position);
                        math_apply_axis_rotation_to_quat(&random, &random, &difference,
                                     math_random_float_range(0.174532949924469f, 0.7853982448577881f) * sign);
                        sign = -sign;
                        FastVecAdd(&D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1], &random);
                    }
                }
            } else {
                /* Emits nothing, but gives this path a block of its own, so gcse puts the
                   next i there (the `b; addiu` after the regrow arm) and not before the test. */
                active = 0;
            }
        } else {
            for (j = 1; j < 5; j++) {
                FastVecSub(&offsets[j], &D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1]);
                offsets[j].f[0] += math_random_signed_float_range(0.0f, 0.1f);
                offsets[j].f[1] += math_random_signed_float_range(0.0f, 0.1f);
                offsets[j].f[2] += math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_L00_00239EF0[i][0], &origin);
            for (j = 1; j < 5; j++)
                FastVecAdd(&D_L00_00239EF0[i][j], &D_L00_00239EE0[i].p[j - 1], &offsets[j]);
            if (D_L00_001B2778[i] > 0)
                D_L00_001B2790[i] = 32;
            else
                D_L00_001B2790[i] = 0;
        }
    }
    ref_L00_00395428_00(UpdateScaledRecords, object);
}
