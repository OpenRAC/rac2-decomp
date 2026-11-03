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

void func_L11_003404E0(char *a0)
{
    func_L02_00333480(a0, a0 + 0x10, a0 + 0xC0);
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
void func_L11_0041E460(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

void func_L11_00439D78(float a, float b, float c, float d)
{
    float v = (d + d) * (a - b);

    func_00283CF0((c + func_00282C10(c * c + v)) / d);
}

/* func_L11_0044FFA0 lives in L11_0044FFA0-g8.c. */

/* Draws the record's two markers, the scaled radius and the two colours, for each of the
   two record kinds the byte at 0x20 selects. */
void func_L11_00450508(unsigned char *p)
{
    switch (p[0x20]) {
    case 0:
        func_L11_004507B0(p + 0x10, 0x103080, *(float *)(p + 0x2C) * 45.0f,
                         func_002A7820(95, 111), func_002A7940(), 11, 2, 1.0f, p);
        func_L11_004507B0(p + 0x10, 0x3F3F3F, *(float *)(p + 0x2C) * 22.5f,
                         func_002A7820(111, 127), func_002A7940(), 11, 2, 1.0f, p);
        break;
    case 1:
        func_L11_004507B0(p + 0x10, 0x103080, *(float *)(p + 0x2C) * 45.0f,
                         func_002A7820(95, 111), func_002A7940(), 11, 2, 1.0f, p);
        func_L11_004507B0(p + 0x10, 0x3F3F3F, *(float *)(p + 0x2C) * 22.5f,
                         func_002A7820(111, 127), func_002A7940(), 11, 2, 1.0f, p);
        break;
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_004506C0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_L11_004507B0 lives in L11_004507B0-g8.c. */

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00458D00(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* The 224-byte local record the level's camera update fills in. */

/* The record's reset and its four-vector scaler: a different function in every
 * level that holds them, so each place resolves its own target. */

/* The level's table of floats. */

/* Fills a local record: the level's handle, the four blocks it scales, and the
 * two vectors the level's own table gives against the object's position. */
void func_L11_00458DF0(char *a0, void *a1, void *a2, int a3, int t0, float f12, float f13)
{
    LOC_L11_458DF0 local;
    float x;

    ref_L11_00458DF0_00((char *)&local);
    local.v120 = func_0027C878(a3);
    local.v128 = 0xFF9000000260LL;
    local.v136 = ((long long)t0 << 2) | 0x0000008000000040LL;
    local.k3 = (int)a1 + ((int)a2 << 24);
    local.k2 = (int)a1 + ((int)a2 << 24);
    local.k1 = (int)a1 + ((int)a2 << 24);
    local.k0 = (int)a1 + ((int)a2 << 24);
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = func_00283248(D_L11_001BA780[0x50] - *(float *)a0,
                                D_L11_001BA780[0x51] - *(float *)(a0 + 4));
    x = func_00283248(func_00282E80(a0, D_L11_001BA780 + 0x50),
                      D_L11_001BA780[0x52] - *(float *)(a0 + 8));
    local.f212 = -x;
    local.v208 = f13;
    func_00283410(&local.m00, &local.v208);
    local.v192 = *(float *)a0;
    local.v196 = *(float *)(a0 + 4);
    local.v200 = *(float *)(a0 + 8);
    local.v204 = 1.0f;
    ref_L11_00458DF0_01((char *)&local, f12);
    func_00280B90(&local, &local.m00, 0);
}

/* Emits two effects at the object's position with independently sampled
 * intensities and the two colour/scale presets. */
extern int func_002A7820(int, int);

extern float func_002A7940(void);

extern void func_L11_004600A0(void *, int, int, int, int, float, float, float);

void func_L11_0045FEF8(void *a0)
{
  float new_var;
  char *p = ((char *) a0) + 0x10;
  int v = func_002A7820(0x2F, 0x3F);
  int new_var2;
  float f;
  func_L11_004600A0(p, (float) 0x103080, v, 0xB, 2, 2.0f, func_002A7940(), 1.0f);
  new_var = 1.0f;
  new_var2 = func_002A7820(0x1F, 0x3F);
  v = new_var2;
  f = func_002A7940();
  func_L11_004600A0(p, 0x606060, v, 0xB, 2, new_var, f, new_var);
}


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_0045FFB0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_L11_00460258 is defined in L11_00460258-g32.c. */

/* func_L11_0046B9F0 lives in L11_0046B9F0-g8.c. */

/* func_L11_0046BC08 lives in L11_0046BC08-g8.c. */

/* func_L11_0046BD18 is defined in L11_0046BD18-g8.c. */

/* func_L11_0046C1E0 lives in L11_002C5E80-trail-g8.c. */

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00472008(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

INCLUDE_ASM("asm/levels", func_L11_00472090);

void func_L11_00474888(char *a0)
{
    if (func_002ACBC8(D_L11_00189EA0, *(int *)(*(char **)(a0 + 0x68))) == 0) return;
    if (*(int *)(D_L11_00189EA0 + 0x2214) != 0x82) return;
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
    func_002829D8(D_L11_00189EA0 + 0x530);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L11_00478EF0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}
