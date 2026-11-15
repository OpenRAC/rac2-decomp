/* func_L00_003D3388: a unit of its own for -frac2-qcopy -frac2-qcopy-barrier. */
#include "common.h"
typedef int ArcQuad __attribute__((mode(TI)));
typedef union { ArcQuad q; float f[4]; } ArcVector;
extern short D_L00_001B2AE0[] MACRO_ADDR;
extern short D_L00_001B2AF0[] MACRO_ADDR;
extern short D_L00_001B2B00[] MACRO_ADDR;
extern short D_L00_001B2B10[] MACRO_ADDR;
/* Six strips of five points; _1 names the same table where a loop reads the point before j. */
extern ArcVector D_L00_00247310[][5], D_L00_00247310_1[][5];
extern char g_camera_l00_position[];
extern ArcVector D_L00_0018A560[];
extern float D_L00_001B0218 __attribute__((sda));
extern int FastDecTimer(short *);
extern float math_random_float_range(float, float), math_random_signed_float_range(float, float), IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecScale(void *, void *, float), math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *), FastVecSub(void *, void *, void *);
/* Updates six lightning arcs: restarts finished ones with new random points, jitters the rest and fades them. */
void lightning_update_arcs(char *object)
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
        scale = D_L00_001B0218;
        qcopy(&position, data + 0x10);
        if (FastDecTimer(&D_L00_001B2AE0[i])) {
            D_L00_001B2AF0[i] = 0;
            if (i < 4) {
                D_L00_001B2AE0[i] = D_L00_001B2B00[i];
                turn = math_random_signed_float_range(0.3490659f, 1.3962636f);
                angle = math_random_float_range(-1.0471977f, 0.17453295f);
                FastVecScale(&local, &direction, scale);
                math_apply_axis_rotation_to_quat(&local, &local, D_L00_0018A560, angle);
                math_apply_axis_rotation_to_quat(&local, &local, D_L00_0018A560 + 1, turn);
                qcopy(&D_L00_00247310[i][0], &position);
                FastVecAdd(&D_L00_00247310[i][1], &position, &local);
                sign = 1.0f;
                for (j = 2; j < 5; j++) {
                    FastVecSub(&eye, &D_L00_00247310_1[i][j - 1], g_camera_l00_position);
                    angle = math_random_float_range(0.17453295f, 0.9599312f) * sign;
                    sign = -sign;
                    math_apply_axis_rotation_to_quat(&local, &local, &eye, angle);
                    FastVecAdd(&D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1], &local);
                }
            }
        } else {
            shortArc = i < 4;
            for (j = 1; j < 5; j++) {
                FastVecSub(&delta[j], &D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1]);
                delta[j].f[0] += math_random_signed_float_range(0, 0.1f);
                delta[j].f[1] += math_random_signed_float_range(0, 0.1f);
                delta[j].f[2] += math_random_signed_float_range(0, 0.1f);
            }
            qcopy(&D_L00_00247310[i][0], &position);
            for (j = 1; j < 5; j++)
                FastVecAdd(&D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1], &delta[j]);
            if (D_L00_001B2AE0[i] > D_L00_001B2B10[i]) {
                ratio = IntToFloat(D_L00_001B2AE0[i] - D_L00_001B2B10[i]) / IntToFloat(15);
                {
                float alphaScale = 32.0f;
                if (!shortArc) alphaScale = 255.0f;
                D_L00_001B2AF0[i] = FloatToInt((1.0f - ratio) * alphaScale);
                }
            } else {
                ratio = IntToFloat(D_L00_001B2B10[i] - D_L00_001B2AE0[i]) / IntToFloat(15);
                D_L00_001B2AF0[i] = FloatToInt((1.0f - ratio) * 32.0f);
            }
        }
    }
}
