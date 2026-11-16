#include "common.h"

typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;

extern short g_jitter_trail_timers[] MACRO_ADDR;
extern short g_jitter_trail_alphas[] MACRO_ADDR;
extern Vector g_trail_points[][5];    /* trail points: [trail][point] */
extern Vector D_L00_0023D9E0_1[][5];  /* the same table: the name each point's predecessor is read through */
extern Vector g_camera_l00_position;
extern float g_jitter_effect_speed __attribute__((sda));
extern void part_spawn_random_direction_effect(void *, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);

/* Four five-point trails: one whose timer runs out is re-aimed from the object's position with
   random bends, a live one jitters each segment. */
void UpdateJitterTrails(unsigned char *object)
{
    Vector position, direction, axis, displacements[5];
    int i, j;
    float sign, angle;

    qcopy(&position, object + 0x10);
    for (i = 0; i < 4; i++) {
        short *timer = &g_jitter_trail_timers[i];

        if (*timer == 0)
            continue;
        --*timer;
        if (*timer < 0)
            *timer = 0;
        if (*timer == 0) {
            *timer = 4;
            g_jitter_trail_alphas[i] = 64;
            part_spawn_random_direction_effect(&direction, g_jitter_effect_speed, g_jitter_effect_speed);
            qcopy(&g_trail_points[i][0], &position);
            sign = 1.0f;
            for (j = 1; j < 5; j++) {
                FastVecSub(&axis, &D_L00_0023D9E0_1[i][j - 1], &g_camera_l00_position);
                angle = math_random_float_range(0.17453295f, 0.78539824f) * sign;
                sign = -sign;
                math_apply_axis_rotation_to_quat(&direction, &direction, &axis, angle);
                FastVecAdd(&g_trail_points[i][j], &D_L00_0023D9E0_1[i][j - 1], &direction);
            }
        } else {
            for (j = 1; j < 5; j++) {
                FastVecSub(&displacements[j], &g_trail_points[i][j], &D_L00_0023D9E0_1[i][j - 1]);
                displacements[j].v[0] += math_random_signed_float_range(0.0f, 0.1f);
                displacements[j].v[1] += math_random_signed_float_range(0.0f, 0.1f);
                displacements[j].v[2] += math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_trail_points[i][0], &position);
            for (j = 1; j < 5; j++)
                FastVecAdd(&g_trail_points[i][j], &D_L00_0023D9E0_1[i][j - 1], &displacements[j]);
            if (g_jitter_trail_timers[i] > 0)
                g_jitter_trail_alphas[i] = 32;
            else
                g_jitter_trail_alphas[i] = 0;
        }
    }
}
