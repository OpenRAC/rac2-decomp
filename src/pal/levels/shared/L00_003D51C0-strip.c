#include "include_asm.h"

#include "common.h"
extern short g_lightning_arc_timers[] __attribute__((sda));
extern short g_lightning_arc_alphas[] __attribute__((sda));
extern short g_lightning_arc_periods[] __attribute__((sda));
extern short g_lightning_arc_midpoints[] __attribute__((sda));
extern char g_lightning_arc_points[];
extern char g_lightning_l00_strip_points[];
extern char g_strip_axis[];
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float IntToFloat(int);
extern void lerp_vector(void *, void *, void *, float);
extern void vec_random_direction(void *, float, float);

/* Resets the strip tables, then aims strips 4 and 5 from position: the D_0018A580 axis scaled
   by 32, turned by a random 10 to 24 degrees about D_0018A580 - 0x20 and by a random 22 to 30
   degrees (mirrored for strip 5) about D_0018A580 - 0x10; the three inner points are
   interpolated between the ends and jittered. */
void func_PAL_L00_003D6C38(void *object, void *position, int unused)
{
    char delta[16] __attribute__((aligned(16)));
    char end[16] __attribute__((aligned(16)));
    char jitter[16] __attribute__((aligned(16)));
    int i, j, k;
    float angle, t;

    for (k = 0; k < 4; k++)
        g_lightning_arc_timers[k] = -1;

    g_lightning_arc_periods[0] = 8;
    g_lightning_arc_midpoints[0] = 4;
    g_lightning_arc_periods[1] = 4;
    g_lightning_arc_midpoints[1] = 2;
    g_lightning_arc_periods[2] = 8;
    g_lightning_arc_midpoints[2] = 4;
    g_lightning_arc_periods[3] = 4;
    g_lightning_arc_midpoints[3] = 2;
    g_lightning_arc_periods[4] = 8;
    g_lightning_arc_midpoints[4] = 4;
    g_lightning_arc_periods[5] = 4;
    g_lightning_arc_midpoints[5] = 3;

    for (i = 4; i < 6; i++) {
        g_lightning_arc_timers[i] = 7;
        g_lightning_arc_alphas[i] = 255;

        qcopy(g_lightning_arc_points + i * 80, position);
        FastVecScale(delta, g_strip_axis, 32.0f);
        math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 32, -(math_random_float_range(10.0f, 24.0f) * 0.017453294f));
        angle = math_random_float_range(22.0f, 30.0f) * 0.017453294f;
        if (i == 5)
            math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 16, -angle);
        else
            math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 16, angle);

        FastVecAdd(end, position, delta);
        qcopy(g_lightning_l00_strip_points + i * 80, end);
        for (j = 1; j < 4; j++) {
            t = IntToFloat(j) / IntToFloat(4);
            lerp_vector(g_lightning_arc_points + i * 80 + j * 16, position, end, t);
            vec_random_direction(jitter, t * 2.0f, t * 2.0f);
            FastVecAdd(g_lightning_arc_points + i * 80 + j * 16, g_lightning_arc_points + i * 80 + j * 16, jitter);
        }
    }
}
