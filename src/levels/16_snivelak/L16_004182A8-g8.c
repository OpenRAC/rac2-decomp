#include "common.h"
extern int D_L16_001B1C38 __attribute__((sda));
extern float func_002A78D8(float,float);
extern int func_00283CF0(float);
extern long long func_0027C878(int);
extern void func_00283410(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00280B90(void *,void *,int);
extern void func_L16_00418218(void *);
/* The record func_L16_00418218 resets: four vertices, four words, eight floats,
   then three 64-bit fields. */
typedef struct {
    struct {
        int textureId;
        float x;
        float y;
        float z;
    } v[4];
    int p[4];
    float f[8];
    long long q;
    long long r;
    long long s;
} L16_004182A8_rec;

/* The record, a 64-bit word, a matrix, a vector and a direction. */
typedef struct {
    L16_004182A8_rec rec;
    long long t;
    float mat[12];
    float vec[4];
    float dir[4];
} L16_004182A8_frame;

/* The caller supplies an unused scale in F12; the body replaces it before use. */
/* Draws two fading, randomly tinted strips of ground effect around a hit point. */
void func_L16_004182A8(char *moby, char *hitPoint, float unused_scale, int baseColor, int fadeA, int fadeB) {
    L16_004182A8_frame fr;
    char *vars;
    long long textureId;
    long long sv;
    long long tw;
    long long tv;

    vars = *(char **)(moby + 0x68);

    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 5.0f)) << 24);
    InitQuadPacketTable(&fr.rec);

    fr.rec.f[0] = *(float *)(vars + 0x10);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(vars + 0x10);
    fr.rec.f[3] = 1.0f;
    fr.rec.f[4] = *(float *)(vars + 0x10) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(vars + 0x10) + 1.0f;
    fr.rec.f[7] = 1.0f;

    textureId = GetEffectTextureDescriptor(D_L16_001B1C38);
    fr.rec.r = textureId;
    fr.rec.s = 280993940374112LL;
    fr.t = 0x8000000048LL;
    fr.rec.p[0] = baseColor + fadeA;
    fr.rec.q = 0LL;

    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = baseColor + fadeA;
    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = baseColor + fadeA;
    fadeA = fadeA - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = baseColor + fadeA;

    fr.dir[2] = *(float *)(moby + 0xF8);
    fr.dir[1] = *(float *)(moby + 0xF4);
    fr.dir[0] = 1.5707965f;
    fr.dir[3] = 0.0f;
    euler_to_matrix(fr.mat, fr.dir);

    fr.vec[0] = *(float *)hitPoint;
    fr.vec[1] = *(float *)(hitPoint + 4);
    fr.vec[2] = *(float *)(hitPoint + 8);
    fr.vec[3] = 1.0f;
    FastVecScale(&fr.rec.v[0], &fr.rec.v[0], 1.0f);
    FastVecScale(&fr.rec.v[1], &fr.rec.v[1], 1.0f);
    FastVecScale(&fr.rec.v[2], &fr.rec.v[2], 1.0f);
    FastVecScale(&fr.rec.v[3], &fr.rec.v[3], 1.0f);
    draw_world_quad(&fr.rec, fr.mat, 0);

    tv = 0x8000000044LL;
    fr.rec.f[0] = *(float *)(vars + 0x18);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(vars + 0x18);
    fr.rec.f[3] = 1.0f;
    fr.t = tv;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[0] = baseColor + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = baseColor + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = baseColor + fadeB;
    fadeB = fadeB - ((int)FloatToInt(RandomSignedFloatRange(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = baseColor + fadeB;
    fr.rec.f[4] = *(float *)(vars + 0x18) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(vars + 0x18) + 1.0f;
    fr.rec.f[7] = 1.0f;
    draw_world_quad(&fr.rec, fr.mat, 0);
}
