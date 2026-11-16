#include "names.h"
/* func_PAL_L00_003D7400, the PAL copy of func_L00_003D3388: the same C, where scale D_L00_001B2B00[i]. */
/* func_PAL_L00_003D7400: a unit of its own for -frac2-qcopy -frac2-qcopy-barrier. */
#include "common.h"
typedef int ArcQuad __attribute__((mode(TI)));
typedef union { ArcQuad q; float f[4]; } ArcVector;
extern short g_lightning_arc_timers[] MACRO_ADDR;
extern short g_lightning_arc_alphas[] MACRO_ADDR;
extern short g_lightning_arc_periods[] MACRO_ADDR;
extern short g_lightning_arc_midpoints[] MACRO_ADDR;
/* Six strips of five points; _1 names the same table where a loop reads the point before j. */
extern ArcVector g_lightning_arc_points[][5], D_L00_00247310_1[][5];
extern char g_camera_l00_position[];
extern ArcVector g_arc_axis_table[];
extern float g_lightning_arc_scale __attribute__((sda));
extern int FastDecTimer(short *);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float), IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float), math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
void func_PAL_L00_003D7400(char *object)
{
    ArcVector local, direction, position, eye, delta[5];
    char *data = *(char **)(object + 0x68);
    int i, j;
    int shortArc;
    float angle, turn, sign, ratio;
    float scale;
    if (*(short *)(data + 0xA) == 0) return;
    qcopy(&direction, data + 0x30);
    for (i = 0; i < 6; i++) {
        scale = g_lightning_arc_scale;
        qcopy(&position, data + 0x10);
        if (FastDecTimer(&g_lightning_arc_timers[i])) {
            g_lightning_arc_alphas[i] = 0;
            if (i < 4) {
                g_lightning_arc_timers[i] = (((int)(g_lightning_arc_periods[i]) * 5 + 2) / 6);
                turn = math_random_signed_float_range(0.3490659f, 1.3962636f);
                angle = math_random_float_range(-1.0471977f, 0.17453295f);
                FastVecScale(&local, &direction, scale);
                math_apply_axis_rotation_to_quat(&local, &local, g_arc_axis_table, angle);
                math_apply_axis_rotation_to_quat(&local, &local, g_arc_axis_table + 1, turn);
                qcopy(&g_lightning_arc_points[i][0], &position);
                FastVecAdd(&g_lightning_arc_points[i][1], &position, &local);
                sign = 1.0f;
                for (j = 2; j < 5; j++) {
                    FastVecSub(&eye, &D_L00_00247310_1[i][j - 1], g_camera_l00_position);
                    angle = math_random_float_range(0.17453295f, 0.9599312f) * sign;
                    sign = -sign;
                    math_apply_axis_rotation_to_quat(&local, &local, &eye, angle);
                    FastVecAdd(&g_lightning_arc_points[i][j], &D_L00_00247310_1[i][j - 1], &local);
                }
            }
        } else {
            shortArc = i < 4;
            for (j = 1; j < 5; j++) {
                FastVecSub(&delta[j], &g_lightning_arc_points[i][j], &D_L00_00247310_1[i][j - 1]);
                delta[j].f[0] += math_random_signed_float_range(0, 0.1f);
                delta[j].f[1] += math_random_signed_float_range(0, 0.1f);
                delta[j].f[2] += math_random_signed_float_range(0, 0.1f);
            }
            qcopy(&g_lightning_arc_points[i][0], &position);
            for (j = 1; j < 5; j++)
                FastVecAdd(&g_lightning_arc_points[i][j], &D_L00_00247310_1[i][j - 1], &delta[j]);
            if (g_lightning_arc_timers[i] > g_lightning_arc_midpoints[i]) {
                ratio = IntToFloat(g_lightning_arc_timers[i] - g_lightning_arc_midpoints[i]) / IntToFloat(12);
                {
                float alphaScale = 32.0f;
                if (!shortArc) alphaScale = 255.0f;
                g_lightning_arc_alphas[i] = FloatToInt((1.0f - ratio) * alphaScale);
                }
            } else {
                ratio = IntToFloat(g_lightning_arc_midpoints[i] - g_lightning_arc_timers[i]) / IntToFloat(12);
                g_lightning_arc_alphas[i] = FloatToInt((1.0f - ratio) * 32.0f);
            }
        }
    }
}
