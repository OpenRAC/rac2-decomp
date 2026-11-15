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
        int id;
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
void func_L16_004182A8(char *arg0, char *arg1, float unused_scale, int arg2, int arg3, int arg4) {
    L16_004182A8_frame fr;
    char *s3;
    long long id;
    long long sv;
    long long tw;
    long long tv;

    s3 = *(char **)(arg0 + 0x68);

    arg3 = arg3 - ((int)FloatToInt(func_002A78D8(0.0f, 5.0f)) << 24);
    func_L16_00418218(&fr.rec);

    fr.rec.f[0] = *(float *)(s3 + 0x10);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(s3 + 0x10);
    fr.rec.f[3] = 1.0f;
    fr.rec.f[4] = *(float *)(s3 + 0x10) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(s3 + 0x10) + 1.0f;
    fr.rec.f[7] = 1.0f;

    id = GetEffectTextureDescriptor(D_L16_001B1C38);
    fr.rec.r = id;
    fr.rec.s = 280993940374112LL;
    fr.t = 0x8000000048LL;
    fr.rec.p[0] = arg2 + arg3;
    fr.rec.q = 0LL;

    arg3 = arg3 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = arg2 + arg3;
    arg3 = arg3 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = arg2 + arg3;
    arg3 = arg3 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = arg2 + arg3;

    fr.dir[2] = *(float *)(arg0 + 0xF8);
    fr.dir[1] = *(float *)(arg0 + 0xF4);
    fr.dir[0] = 1.5707965f;
    fr.dir[3] = 0.0f;
    euler_to_matrix(fr.mat, fr.dir);

    fr.vec[0] = *(float *)arg1;
    fr.vec[1] = *(float *)(arg1 + 4);
    fr.vec[2] = *(float *)(arg1 + 8);
    fr.vec[3] = 1.0f;
    FastVecScale(&fr.rec.v[0], &fr.rec.v[0], 1.0f);
    FastVecScale(&fr.rec.v[1], &fr.rec.v[1], 1.0f);
    FastVecScale(&fr.rec.v[2], &fr.rec.v[2], 1.0f);
    FastVecScale(&fr.rec.v[3], &fr.rec.v[3], 1.0f);
    draw_world_quad(&fr.rec, fr.mat, 0);

    tv = 0x8000000044LL;
    fr.rec.f[0] = *(float *)(s3 + 0x18);
    fr.rec.f[1] = 0.0f;
    fr.rec.f[2] = *(float *)(s3 + 0x18);
    fr.rec.f[3] = 1.0f;
    fr.t = tv;
    arg4 = arg4 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[0] = arg2 + arg4;
    arg4 = arg4 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[1] = arg2 + arg4;
    arg4 = arg4 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[2] = arg2 + arg4;
    arg4 = arg4 - ((int)FloatToInt(func_002A78D8(0.0f, 9.0f)) << 24);
    fr.rec.p[3] = arg2 + arg4;
    fr.rec.f[4] = *(float *)(s3 + 0x18) + 1.0f;
    fr.rec.f[5] = 0.0f;
    fr.rec.f[6] = *(float *)(s3 + 0x18) + 1.0f;
    fr.rec.f[7] = 1.0f;
    draw_world_quad(&fr.rec, fr.mat, 0);
}
