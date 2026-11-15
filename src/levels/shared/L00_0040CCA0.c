#include "include_asm.h"
#include "names.h"

extern void func_L00_0040DC08(float *p, float a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

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

extern char *func_002C16C0(float *out, float *dir, int a, int b, unsigned int color, int id,
                            float fa, float fb, float fc, float fd, float fe);

extern char D_L00_001B8DC0[];

extern char D_0018A0E0[];

extern char D_001FE940[];

/* Throws out a puff of grey smoke and bright sparks at a point. The sparks are red when the flag is set and green otherwise. */
void func_L00_0040CCA0(float *position, int unused, int flag)
{
    float toCamera[4];
    float velocity[4];
    float spawnPos[4];
    float facingAngle;
    float speed;
    float pitchSpread;
    float yaw;
    float randomValue;
    int spin;
    int i;
    unsigned int color;
    char *part;
    char *extra;

    if (flag != 0) {
        color = 0x7F2020FF;
        SpawnFlareMoby(position, 0.25f, 0, 15, 10, 0, 20, 0, 0, 1, 0);
    } else {
        color = 0x7F20FF20;
    }
    FastVecSub((char *)toCamera, gCameraPosition_L00, (char *)position);
    facingAngle = FastMatrixHelperA(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        randomValue = RandomFloatRange(0.2f, 3.0f);
        FastVecScale((char *)velocity, D_0018A0E0, -(randomValue * 0.01666666753590107f));
        spin = FloatToInt(RandomSignedFloatRange(1.0f, 2.0f));
        randomValue = RandomFloatRange(0.3f, 0.75f) * 210000.0f;
        spawnPos[0] = position[0] + RandomSignedFloatRange(0.0f, 0.2f);
        spawnPos[1] = position[1] + RandomSignedFloatRange(0.0f, 0.2f);
        spawnPos[2] = position[2] + RandomSignedFloatRange(0.0f, 0.2f);
        part = SpawnSpinningSparkParticle((char *)spawnPos, 0.0f, 1.0f, 1.01f, randomValue, spin, (char *)velocity, 0x7F202020, 0);
        if (part != 0) {
            extra = part + 32;
            *(unsigned char *)(part + 3) = 0x44;
            *(short *)(part + 10) = 0x5A;
            *(unsigned char *)(part + 9) = FloatToInt(4.0f) + 0x40;
            *(float *)(extra + 0x1C) = IntToFloat(5);
            *(int *)(extra + 4) = 3;
            *(unsigned char *)(extra + 0xA) = 0x30;
            *(unsigned char *)(extra + 0xB) = *(unsigned char *)(part + 10);
        }
        speed = RandomFloatRange(1.0f, 2.0f);
        pitchSpread = RandomFloatRange(0.0f, 1.396263599395752f);
        yaw = FastAddRotations(facingAngle, RandomSignedFloatRange(0.0f, 1.396263599395752f));
        BuildSphericalOffset(velocity, speed * 0.01666666753590107f, yaw, pitchSpread);
        spawnPos[0] = position[0] + RandomSignedFloatRange(0.0f, 0.1f);
        spawnPos[1] = position[1] + RandomSignedFloatRange(0.0f, 0.1f);
        spawnPos[2] = position[2] + RandomSignedFloatRange(0.0f, 0.1f);
        part = SpawnBurstParticle_002C16C0(spawnPos, velocity, 30, 127, color, spin,
                          RandomFloatRange(0.25f, 0.7f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
        if (part != 0) {
            char *resident = D_001FE940;
            *(unsigned char *)(part + 2) = *(unsigned char *)(*(char **)(resident + 0x184) + 6);
        }
    }
}
