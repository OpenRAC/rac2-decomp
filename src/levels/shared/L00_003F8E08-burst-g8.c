#include "common.h"

typedef int SpawnVectorWord __attribute__((mode(TI)));

extern char D_L00_001B8DC0[];
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);
extern float func_00283B98(float, float);
extern void func_002A7A00(float *, float, float);
extern void *func_002C16C0(void *, void *, int, u32, int, int, float, float, float, float, float);
extern void *func_002C2210(float, void *, int, float, u32, int, int, void *, int, float);

/* Fifteen particles thrown from the point, as in func_L00_003FC820, then five pairs of trail
   effects around it, differently coloured and with opposite random signs. */
void func_L00_003FD178(float *point)
{
    float delta[4];
    float direction[4];
    float position[4];
    float base_angle;
    float scale;
    float angle;
    float elevation;
    float speed;
    float trail_scale;
    int kind;
    int sign;
    int i;
    int j;
    char *effect;

    FastVecSub((char *)delta, gCameraPosition_L00, (char *)point);
    base_angle = FastMatrixHelperA(delta[0], delta[1]);
    for (i = 0; i < 15; i++) {
        scale = RandomFloatRange(0.5f, 1.25f);
        kind = FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
        elevation = RandomFloatRange(0.0f, 1.3962636f);
        angle = FastAddRotations(base_angle, RandomSignedFloatRange(0.0f, 1.3962636f));
        BuildSphericalOffset(direction, scale * 0.016666668f, angle, elevation);
        position[0] = point[0] + RandomSignedFloatRange(0.0f, 0.2f);
        position[1] = point[1] + RandomSignedFloatRange(0.0f, 0.2f);
        position[2] = point[2] + RandomSignedFloatRange(0.0f, 0.2f);
        SpawnBurstParticle_002C16C0(position, direction, 30, 127, 0x007F7F7F, kind,
                      RandomFloatRange(0.1f, 0.3f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
    for (j = 0; j < 5; j++) {
        trail_scale = RandomFloatRange(0.25f, 0.75f);
        sign = RandomIntBelow(2);
        if (sign == 0)
            sign--;
        speed = RandomFloatRange(1.0f, 4.0f);
        RandomDirectionVector(direction, speed * 0.016666668f, speed * 0.016666668f);
        *(SpawnVectorWord *)position = *(SpawnVectorWord *)point;
        position[0] += RandomSignedFloatRange(0.0f, 0.15f);
        position[1] += RandomSignedFloatRange(0.0f, 0.15f);
        position[2] += RandomSignedFloatRange(0.0f, 0.15f);
        effect = SpawnGroundEffectParticle(trail_scale * 0.1f, position, 60, trail_scale,
                               0x7FFF1010, 0, sign, direction, 0, 0.003f);
        if (effect != 0)
            effect[9] = FloatToInt(4.0f) + 112;
        effect = SpawnGroundEffectParticle(trail_scale * 0.05f, position, 60, trail_scale * 0.5f,
                               0x7F7F7F7F, 1, -sign, direction, 0, 0.003f);
        if (effect != 0)
            effect[9] = FloatToInt(4.0f) + 112;
    }
}
