#include "common.h"

typedef struct {
    float b0[4];
    float b1[4];
    float b2[4];
    float b3[4];
    int k0, k1, k2, k3;
    int z80, z84, z88;
    float f92, f96;
    int z100;
    float f104, f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_L11_458DF0;

extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_L02_00333480(char *a, char *b, char *c);

extern float func_00282C10(float a);

extern void func_00283CF0(float a);

extern int func_002A7820(int lo, int hi);

extern float func_002A7940(void);

extern void func_L11_004507B0(void *a0, unsigned int color, float f, int rand, float a, int a3,
                              int a4, float one, void *a5);

extern void ref_L11_00458DF0_00(char *p);

extern void ref_L11_00458DF0_01(char *p, float scale);

extern long long func_0027C878(int id);

extern float func_00283248(float x, float y);

extern float func_00282E80(char *a0, float *a1);

extern void func_00283410(void *dst, void *src);

extern void func_00280B90(void *dst, void *src, int flag);

extern float D_L11_001BA780[];

extern int func_002ACBC8(void *a, int b);

extern void func_002829D8(void *a);

extern unsigned char D_L11_00189EA0[];

/* func_L11_002C5E80 lives in L11_002C5E80-nearby-g8.c. */

/* func_L11_002CDE10 lives in L11_002CDE10-motion.c. */

/* Passes the object and two data blocks inside it (at +0x10 and +0xC0) to a shared helper. */
void func_L11_003404E0(char *moby)
{
    UpdateObjectController(moby, moby + 0x10, moby + 0xC0);
}

/* func_L11_00397C08 lives in L11_00397C08-helpers.c. */

/* func_L11_00397E68 lives in L11_00397E68-g8.c. */

/* func_L11_003CF250 lives in L11_003CF250-trigger.c. */

/* func_L11_003F4198 lives in L11_003F4198-helpers.c. */

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void func_L11_00414660(float *out, float *b, float *c, float *a, float *d, float t)
{
    float t2, t3, p, q, r;

    if (t == 0.0f) {
        qcopy(out, b);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, c);
        return;
    }
    t2 = t * t;
    t3 = t2 * t;

    p = (d[0] - c[0]) - (a[0] - b[0]);
    q = (a[0] - b[0]) - p;
    r = c[0] - a[0];
    out[0] = p * t3 + q * t2 + r * t + b[0];

    p = (d[1] - c[1]) - (a[1] - b[1]);
    q = (a[1] - b[1]) - p;
    r = c[1] - a[1];
    out[1] = p * t3 + q * t2 + r * t + b[1];

    p = (d[2] - c[2]) - (a[2] - b[2]);
    q = (a[2] - b[2]) - p;
    r = c[2] - a[2];
    out[2] = p * t3 + q * t2 + r * t + b[2];
    out[3] = 0.0f;
}

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L11_0041E460(char *vectors, float scale)
{
    func_00282D30_2(vectors, vectors, scale);
    func_00282D30_2(vectors + 16, vectors + 16, scale);
    func_00282D30_2(vectors + 32, vectors + 32, scale);
    func_00282D30_2(vectors + 48, vectors + 48, scale);
}

/* Works out how long a thrown object takes to land, from the height gap, its launch speed and gravity. */
void func_L11_00439D78(float startHeight, float endHeight, float launchSpeed, float gravity)
{
    float heightTerm = (gravity + gravity) * (startHeight - endHeight);

    FloatToInt((launchSpeed + square_root(launchSpeed * launchSpeed + heightTerm)) / gravity);
}

/* func_L11_0044FFA0 lives in L11_0044FFA0-g8.c. */

/* Draws the record's two markers, the scaled radius and the two colours, for each of the
   two record kinds the byte at 0x20 selects. */
void func_L11_00450508(unsigned char *moby)
{
    switch (moby[0x20]) {
    case 0:
        DrawGlowSpriteWithFlares(moby + 0x10, 0x103080, *(float *)(moby + 0x2C) * 45.0f,
                         RandomIntRange(95, 111), RandomAngle(), 11, 2, 1.0f, moby);
        DrawGlowSpriteWithFlares(moby + 0x10, 0x3F3F3F, *(float *)(moby + 0x2C) * 22.5f,
                         RandomIntRange(111, 127), RandomAngle(), 11, 2, 1.0f, moby);
        break;
    case 1:
        DrawGlowSpriteWithFlares(moby + 0x10, 0x103080, *(float *)(moby + 0x2C) * 45.0f,
                         RandomIntRange(95, 111), RandomAngle(), 11, 2, 1.0f, moby);
        DrawGlowSpriteWithFlares(moby + 0x10, 0x3F3F3F, *(float *)(moby + 0x2C) * 22.5f,
                         RandomIntRange(111, 127), RandomAngle(), 11, 2, 1.0f, moby);
        break;
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_004506C0(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* func_L11_004507B0 lives in L11_004507B0-g8.c. */

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00458D00(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* The 224-byte local record the level's camera update fills in. */

/* The record's reset and its four-vector scaler: a different function in every
 * level that holds them, so each place resolves its own target. */

/* The level's table of floats. */

/* Fills a local record: the level's handle, the four blocks it scales, and the
 * two vectors the level's own table gives against the object's position. */
void func_L11_00458DF0(char *position, void *color, void *alpha, int textureId, int flags, float scale, float roll)
{
    LOC_L11_458DF0 local;
    float pitch;

    ref_L11_00458DF0_00((char *)&local);
    local.v120 = GetEffectTextureDescriptor(textureId);
    local.v128 = 0xFF9000000260LL;
    local.v136 = ((long long)flags << 2) | 0x0000008000000040LL;
    local.k3 = (int)color + ((int)alpha << 24);
    local.k2 = (int)color + ((int)alpha << 24);
    local.k1 = (int)color + ((int)alpha << 24);
    local.k0 = (int)color + ((int)alpha << 24);
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = FastMatrixHelperA(D_L11_001BA780[0x50] - *(float *)position,
                                D_L11_001BA780[0x51] - *(float *)(position + 4));
    pitch = FastMatrixHelperA(vec_distance_xy(position, D_L11_001BA780 + 0x50),
                      D_L11_001BA780[0x52] - *(float *)(position + 8));
    local.f212 = -pitch;
    local.v208 = roll;
    euler_to_matrix(&local.m00, &local.v208);
    local.v192 = *(float *)position;
    local.v196 = *(float *)(position + 4);
    local.v200 = *(float *)(position + 8);
    local.v204 = 1.0f;
    ref_L11_00458DF0_01((char *)&local, scale);
    draw_world_quad(&local, &local.m00, 0);
}

/* Emits two effects at the object's position with independently sampled
 * intensities and the two colour/scale presets. */
extern int func_002A7820(int, int);

extern float func_002A7940(void);

extern void func_L11_004600A0(void *, int, int, int, int, float, float, float);

void func_L11_0045FEF8(void *moby)
{
  float new_var;
  char *position = ((char *) moby) + 0x10;
  int amount = RandomIntRange(0x2F, 0x3F);
  int new_var2;
  float random;
  DrawAimedPacket(position, (float) 0x103080, amount, 0xB, 2, 2.0f, RandomAngle(), 1.0f);
  new_var = 1.0f;
  new_var2 = RandomIntRange(0x1F, 0x3F);
  amount = new_var2;
  random = RandomAngle();
  DrawAimedPacket(position, 0x606060, amount, 0xB, 2, new_var, random, new_var);
}


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_0045FFB0(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* func_L11_00460258 is defined in L11_00460258-g32.c. */

/* func_L11_0046B9F0 lives in L11_0046B9F0-g8.c. */

/* func_L11_0046BC08 lives in L11_0046BC08-g8.c. */

/* func_L11_0046BD18 is defined in L11_0046BD18-g8.c. */

/* func_L11_0046C1E0 lives in L11_002C5E80-trail-g8.c. */

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00472008(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}

/* func_L11_00472090 is defined in L11_00472090-curve.c. */

/* Checks that the hero is in state 0x82 on this object, then repeats one hero helper call nine times. */
void func_L11_00474888(char *moby)
{
    if (IsPointInCuboid(D_L11_00189EA0, *(int *)(*(char **)(moby + 0x68))) == 0) return;
    if (*(int *)(D_L11_00189EA0 + 0x2214) != 0x82) return;
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
    FastVectorHelperB(D_L11_00189EA0 + 0x530);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00478EF0(char *record)
{
    *(long long *)(record + 112) = 0LL;
    *(int *)(record + 80) = 0;
    *(int *)(record + 84) = 0;
    *(float *)(record + 88) = 1.0f;
    *(int *)(record + 92) = 0;
    *(int *)(record + 96) = 0;
    *(float *)(record + 100) = 1.0f;
    *(float *)(record + 104) = 1.0f;
    *(float *)(record + 108) = 1.0f;
    *(float *)(record + 8) = -1.0f;
    *(float *)(record + 24) = 1.0f;
    *(float *)(record + 40) = -1.0f;
    *(float *)(record + 56) = 1.0f;
    *(float *)(record + 4) = -1.0f;
    *(float *)(record + 36) = 1.0f;
    *(float *)(record + 52) = 1.0f;
    *(int *)(record + 0) = 0;
    *(int *)(record + 16) = 0;
    *(int *)(record + 32) = 0;
    *(int *)(record + 48) = 0;
    *(float *)(record + 12) = 1.0f;
    *(float *)(record + 28) = 1.0f;
    *(float *)(record + 44) = 1.0f;
    *(long long *)(record + 128) = 280993940374112LL;
    *(float *)(record + 20) = -1.0f;
    *(float *)(record + 60) = 1.0f;
}
