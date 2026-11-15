#include "names.h"
/* Related hero layout and control flow adapted from OpenRAC/rac1-decomp
 * src/overlays/shared/hero_idle_and_animation.c (GPL-3.0). */

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x300];
    float f300;
    float f304;
    float f308;
    float f30C;
    float f310;
    float f314;
    unsigned char pad318[0x30];
    short f348;
    unsigned char pad34a[0x152];
    unsigned char f49C;
    unsigned char pad49d[0xdd3];
    int f1270;
    unsigned char pad1274[0x1bc];
    float f1430;
    float f1434;
    int f1438;
    short f143C;
    unsigned short f143E;
    unsigned char pad1440[0xe50];
    unsigned char *f2290;
    int f2294;
    unsigned char pad2298[0x4];
    int f229C;
} PointEffectHero;
extern PointEffectHero D_00189E20;
typedef struct {
    unsigned char pad0[0x320];
    float f320;
    float f324;
    unsigned char pad328[0x44];
    float f36C;
    unsigned char pad370[0x60];
    float f3D0;
    float f3D4;
    unsigned char pad3d8[0x44];
    float f41C;
    unsigned char pad420[0x60];
    float f480;
    unsigned char pad484[0xac];
    float f530;
} PointEffectJoints;
extern PointEffectJoints D_L00_0025BE10;
extern int func_L00_002ADF80(void);
extern float func_00282C48(float);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_L00_002D3248(short, unsigned char, unsigned char, unsigned char, float, float);
extern void func_0029FCC0(char *, int, char *);
extern float func_002A7878(float, float);
extern void func_L00_00335558(void *, void *, float);

/* Drive articulated offsets and emit the active pair of joint effects. */
/* Swings the hero arms and body parts as the hero moves, and makes small effects at the hands when needed. */
void func_L00_002AC1A0(void)
{
    Quadword position;
    unsigned char *matrix;
    float left, right, draw;
    int index;

    if (gHeroState.f1270) {
        D_L00_0025BE10.f36C = 0.01f;
        D_L00_0025BE10.f41C = 0.01f;
    }
    if (IsHeroInSpecialKindOrMode())
        return;
    if ((FloatAbs(gHeroState.f300) > 0.015f ||
         FloatAbs(gHeroState.f304) > 0.015f ||
         FloatAbs(gHeroState.f308) > 0.01745329424738884f ||
         FloatAbs(gHeroState.f30C) > 0.01745329424738884f ||
         FloatAbs(gHeroState.f310) > 0.01745329424738884f ||
         FloatAbs(gHeroState.f314) > 0.01745329424738884f) &&
        gHeroState.f348 != 1) {
        D_L00_0025BE10.f324 = -gHeroState.f308;
        D_L00_0025BE10.f3D4 = -gHeroState.f30C;
        left = FastMatrixHelperA(0.2f, gHeroState.f300) * 1.2f;
        right = -FastMatrixHelperA(0.2f, gHeroState.f304) * 1.2f;
        if (left > 0.785398244857788f)
            left = 0.785398244857788f;
        if (left < -0.174532949924469f)
            left = -0.174532949924469f;
        if (right > 0.174532949924469f)
            right = 0.174532949924469f;
        if (right < -0.785398244857788f)
            right = -0.785398244857788f;
        D_L00_0025BE10.f480 = left;
        D_L00_0025BE10.f530 = right;
        D_L00_0025BE10.f320 = -fast_subtract_rotations(gHeroState.f310, -left);
        D_L00_0025BE10.f3D0 = -fast_subtract_rotations(gHeroState.f314, -right);
    }
    if (!(gHeroState.f143E & 0x80)) {
        if (gHeroState.f2294 == 3)
            SetHeroLevelClockAndBytes(1, 2, 1, 0, 0.021f, 0.002f);
        if (gHeroState.f229C == 4 && gHeroState.f49C && gHeroState.f49C < 12)
            SetHeroLevelClockAndBytes(1, 2, 0, 1, 0.016f, 0.002f);
        if (gHeroState.f1438 > 0 && gHeroState.f143C) {
            matrix = 0;
            if (gHeroState.f143E & 1)
                matrix = gHeroState.f2290 + 0xC0;
            --gHeroState.f1438;
            TransformMobyJointToWorld((char *)gHeroState.f2290, 22, (char *)&position);
            for (index = 0; index < gHeroState.f143C; ++index) {
                draw = RandomFloatRange(-gHeroState.f1434, gHeroState.f1434);
                SpawnSparkEffect(&position, matrix, gHeroState.f1430 + draw);
            }
            TransformMobyJointToWorld((char *)gHeroState.f2290, 23, (char *)&position);
            for (index = 0; index < gHeroState.f143C; ++index) {
                draw = RandomFloatRange(-gHeroState.f1434, gHeroState.f1434);
                SpawnSparkEffect(&position, matrix, gHeroState.f1430 + draw);
            }
        }
    } else {
        gHeroState.f1438 = 0;
    }
}
