#include "common.h"

extern void func_00282CF0(char *local, char *first, char *second);
extern float func_00283248(float a, float b);
extern void func_00282D30(char *dst, char *src, float scale);
extern float func_002A7878(float a, float b);
extern float func_002A78D8(float a, float b);
extern int func_00283CF0(float f);
extern float func_00283CE0(int v);
extern float func_00283B98(float a, float b);
extern void func_002AF000(float *p, float a, float b, float c);
extern char *func_002BDCE8(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);
extern void func_002C16C0(float *out, float *dir, int a, int b, unsigned int color, int id,
                           float fa, float fb, float fc, float fd, float fe);
extern char D_L20_001B9FC0[];
extern char D_0018A0E0[];

/* Throws 20 bursts of sparks and smoke out from a point. */
void func_L20_0039C8C8(float *origin)
{
    float toCamera[4];
    float dir[4];
    float out[4];
    float ang;
    float scale;
    float mag;
    float angle;
    float rnd;
    int id;
    int i;
    char *smoke;
    char *smokeExt;

    FastVecSub((char *)toCamera, D_L20_001B9FC0, (char *)origin);
    ang = FastMatrixHelperA(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        rnd = RandomFloatRange(0.2f, 3.0f);
        FastVecScale((char *)dir, D_0018A0E0, -(rnd * 0.01666666753590107f));
        id = FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
        rnd = RandomFloatRange(0.3f, 0.75f) * 210000.0f;
        out[0] = origin[0] + RandomSignedFloatRange(0.0f, 0.2f);
        out[1] = origin[1] + RandomSignedFloatRange(0.0f, 0.2f);
        out[2] = origin[2] + RandomSignedFloatRange(0.0f, 0.2f);
        smoke = SpawnSpinningSparkParticle((char *)out, 0.0f, 1.0f, 1.01f, rnd, id, (char *)dir, 0x7F202020, 0);
        if (smoke != 0) {
            smokeExt = smoke + 32;
            *(unsigned char *)(smoke + 3) = 0x44;
            *(short *)(smoke + 10) = 0x5A;
            *(unsigned char *)(smoke + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(smokeExt + 0x1C) = IntToFloat(5);
            *(int *)(smokeExt + 4) = 3;
            *(unsigned char *)(smokeExt + 0xA) = 0x30;
            *(unsigned char *)(smokeExt + 0xB) = *(unsigned char *)(smoke + 10);
        }
        scale = RandomFloatRange(1.0f, 2.0f);
        mag = RandomFloatRange(0.0f, 1.396263599395752f);
        angle = FastAddRotations(ang, RandomSignedFloatRange(0.0f, 1.396263599395752f));
        BuildSphericalOffset(dir, scale * 0.01666666753590107f, angle, mag);
        out[0] = origin[0] + RandomSignedFloatRange(0.0f, 0.1f);
        out[1] = origin[1] + RandomSignedFloatRange(0.0f, 0.1f);
        out[2] = origin[2] + RandomSignedFloatRange(0.0f, 0.1f);
        SpawnBurstParticle_002C16C0(out, dir, 30, 127, 0x007F7F7F, id,
                      RandomFloatRange(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
    }
}
