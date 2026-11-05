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
extern char D_L00_001B8DC0[];
extern ArcVector D_L00_0018A560[];
extern float D_L00_001B0218 __attribute__((sda));
extern int func_00282978(short *);
extern float func_002A7878(float, float), func_002A78D8(float, float), func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282D30(void *, void *, float), func_002ACEC0(void *, void *, void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282CF0(void *, void *, void *);
void func_L00_003D3388(char *object)
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
        if (func_00282978(&D_L00_001B2AE0[i])) {
            D_L00_001B2AF0[i] = 0;
            if (i < 4) {
                D_L00_001B2AE0[i] = D_L00_001B2B00[i];
                turn = func_002A78D8(0.3490659f, 1.3962636f);
                angle = func_002A7878(-1.0471977f, 0.17453295f);
                func_00282D30(&local, &direction, scale);
                func_002ACEC0(&local, &local, D_L00_0018A560, angle);
                func_002ACEC0(&local, &local, D_L00_0018A560 + 1, turn);
                qcopy(&D_L00_00247310[i][0], &position);
                func_00282CC0(&D_L00_00247310[i][1], &position, &local);
                sign = 1.0f;
                for (j = 2; j < 5; j++) {
                    func_00282CF0(&eye, &D_L00_00247310_1[i][j - 1], D_L00_001B8DC0);
                    angle = func_002A7878(0.17453295f, 0.9599312f) * sign;
                    sign = -sign;
                    func_002ACEC0(&local, &local, &eye, angle);
                    func_00282CC0(&D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1], &local);
                }
            }
        } else {
            shortArc = i < 4;
            for (j = 1; j < 5; j++) {
                func_00282CF0(&delta[j], &D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1]);
                delta[j].f[0] += func_002A78D8(0, 0.1f);
                delta[j].f[1] += func_002A78D8(0, 0.1f);
                delta[j].f[2] += func_002A78D8(0, 0.1f);
            }
            qcopy(&D_L00_00247310[i][0], &position);
            for (j = 1; j < 5; j++)
                func_00282CC0(&D_L00_00247310[i][j], &D_L00_00247310_1[i][j - 1], &delta[j]);
            if (D_L00_001B2AE0[i] > D_L00_001B2B10[i]) {
                ratio = func_00283CE0(D_L00_001B2AE0[i] - D_L00_001B2B10[i]) / func_00283CE0(15);
                {
                float alphaScale = 32.0f;
                if (!shortArc) alphaScale = 255.0f;
                D_L00_001B2AF0[i] = func_00283CF0((1.0f - ratio) * alphaScale);
                }
            } else {
                ratio = func_00283CE0(D_L00_001B2B10[i] - D_L00_001B2AE0[i]) / func_00283CE0(15);
                D_L00_001B2AF0[i] = func_00283CF0((1.0f - ratio) * 32.0f);
            }
        }
    }
}
