#include "include_asm.h"
#include "names.h"

extern void flare_spawn(float *p, float a, int b, int c, int d, int e, int f, int g, int h, int i, int j);

extern void FastVecSub(char *local, char *first, char *second);

extern float mat_fast_helper_a(float a, float b);

extern void FastVecScale(char *dst, char *src, float scale);

extern float math_random_float_range(float a, float b);

extern float math_random_signed_float_range(float a, float b);

extern int FloatToInt(float f);

extern float IntToFloat(int v);

extern float FastAddRotations(float a, float b);

extern void vec_build_spherical_offset(float *p, float a, float b, float c);

extern char *SpawnSpinningSparkParticle(char *p, float fa, float fb, float fc, float fd, int v, char *local,
                            unsigned int color, int flag);

extern char *part_spawn_burst(float *out, float *dir, int a, int b, unsigned int color, int id,
                            float fa, float fb, float fc, float fd, float fe);

extern char g_camera_l00_position[];

extern char D_0018A0E0[];

extern char D_001FE940[];

/* Throws out a puff of grey smoke and bright sparks at a point. The sparks are red when the flag is set and green otherwise. */
void part_spawn_smoke_and_sparks(float *position, int unused, int flag)
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
        flare_spawn(position, 0.25f, 0, 15, 10, 0, 20, 0, 0, 1, 0);
    } else {
        color = 0x7F20FF20;
    }
    FastVecSub((char *)toCamera, g_camera_l00_position, (char *)position);
    facingAngle = mat_fast_helper_a(toCamera[0], toCamera[1]);

    for (i = 19; i >= 0; i--) {
        randomValue = math_random_float_range(0.2f, 3.0f);
        FastVecScale((char *)velocity, D_0018A0E0, -(randomValue * 0.01666666753590107f));
        spin = FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        randomValue = math_random_float_range(0.3f, 0.75f) * 210000.0f;
        spawnPos[0] = position[0] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[1] = position[1] + math_random_signed_float_range(0.0f, 0.2f);
        spawnPos[2] = position[2] + math_random_signed_float_range(0.0f, 0.2f);
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
        speed = math_random_float_range(1.0f, 2.0f);
        pitchSpread = math_random_float_range(0.0f, 1.396263599395752f);
        yaw = FastAddRotations(facingAngle, math_random_signed_float_range(0.0f, 1.396263599395752f));
        vec_build_spherical_offset(velocity, speed * 0.01666666753590107f, yaw, pitchSpread);
        spawnPos[0] = position[0] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[1] = position[1] + math_random_signed_float_range(0.0f, 0.1f);
        spawnPos[2] = position[2] + math_random_signed_float_range(0.0f, 0.1f);
        part = part_spawn_burst(spawnPos, velocity, 30, 127, color, spin,
                          math_random_float_range(0.25f, 0.7f) * 210000.0f, 500.0f, 1.0f, 0.0f, 0.0f);
        if (part != 0) {
            char *resident = D_001FE940;
            *(unsigned char *)(part + 2) = *(unsigned char *)(*(char **)(resident + 0x184) + 6);
        }
    }
}
