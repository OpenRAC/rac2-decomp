#include "common.h"
extern float func_002A7878(float min, float max);
extern int func_002A77E0(int count);
extern float func_002A7940(void);
extern float func_002A78D8(float min, float max);
extern void func_002AF000(float *out, float a, float b, float c);
extern unsigned char *func_002C2210(float life, void *position, int size, float secondLife, int color, int mode, int flag, float *vector, float third, int counter);
extern int func_00283CF0(float value);

/* Spawns eight pairs of flying sparks at a position in the given colour. */
void func_L00_003C58E8(void *position, int color)
{
    float vector[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float scale;
    float radius;
    float a;
    float b;
    int sign;
    unsigned char *particle;
    int i = 7;
    do {
        scale = RandomFloatRange(1.0f, 6.0f);
        sign = RandomIntBelow(2);
        if (sign == 0)
            sign--;
        radius = RandomFloatRange(0.5f, 6.0f) * 0.01666666753590107f;
        a = RandomAngle();
        b = RandomAngle();
        BuildSphericalOffset(vector, radius, a, b);
        qcopy(offset, position);
        offset[0] += RandomSignedFloatRange(0.0f, 0.1f);
        offset[1] += RandomSignedFloatRange(0.0f, 0.1f);
        offset[2] += RandomSignedFloatRange(0.0f, 0.1f);
        particle = SpawnGroundEffectParticle(scale * 0.1f, offset, 20, scale, color | 0x7F000000, 0, sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        particle = SpawnGroundEffectParticle(scale * 0.04f, offset, 20, scale * 0.4f, 0x7F7F7F7F, 1, -sign, vector, 0.0f, 1);
        if (particle)
            particle[9] = FloatToInt(4.0f) + 112;
        i--;
    } while (i >= 0);
}
