#include "names.h"
/* func_L00_003D2C00 is a unit of its own: it needs common.h's qcopy, which the -G0
 * L00_003C6298.c unit does not include. The strip tables are incomplete sda arrays, which
 * gives retail's unsplit table addresses and its lui $at stores.
 */
#include "common.h"

/* Six 0x50-byte strips of five points at D_L00_00247310 (drawn by func_L00_003D2ED0);
   D_L00_00247350 is the last point of the first one. The four short tables hold one entry
   per strip; their roles are unknown. */
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
void InitEffectStrips(void *object, void *position, int unused)
{
    char delta[16] __attribute__((aligned(16)));
    char end[16] __attribute__((aligned(16)));
    char jitter[16] __attribute__((aligned(16)));
    int strip, point, index;
    float angle, fraction;

    for (index = 0; index < 4; index++)
        g_lightning_arc_timers[index] = -1;

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

    for (strip = 4; strip < 6; strip++) {
        g_lightning_arc_timers[strip] = 8;
        g_lightning_arc_alphas[strip] = 255;

        qcopy(g_lightning_arc_points + strip * 80, position);
        FastVecScale(delta, g_strip_axis, 32.0f);
        math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 32, -(math_random_float_range(10.0f, 24.0f) * 0.017453294f));
        angle = math_random_float_range(22.0f, 30.0f) * 0.017453294f;
        if (strip == 5)
            math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 16, -angle);
        else
            math_apply_axis_rotation_to_quat(delta, delta, g_strip_axis - 16, angle);

        FastVecAdd(end, position, delta);
        qcopy(g_lightning_l00_strip_points + strip * 80, end);
        for (point = 1; point < 4; point++) {
            fraction = IntToFloat(point) / IntToFloat(4);
            lerp_vector(g_lightning_arc_points + strip * 80 + point * 16, position, end, fraction);
            vec_random_direction(jitter, fraction * 2.0f, fraction * 2.0f);
            FastVecAdd(g_lightning_arc_points + strip * 80 + point * 16, g_lightning_arc_points + strip * 80 + point * 16, jitter);
        }
    }
}
