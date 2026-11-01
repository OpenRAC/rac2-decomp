#include "include_asm.h"
#include "common.h"
extern int ref_L00_003DD2B8_00(void *);
extern int ref_L00_003DD2B8_01(float);
extern void ref_L00_003DD2B8_02(void *, void *, void *);
extern void ref_L00_003DD2B8_03(void *, void *, void *);
extern void ref_L00_003DD2B8_04(void *, float, float, void *, int);
extern void ref_L00_003DD2B8_05(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern char ref_L00_003DD2B8_06[] __attribute__((sda));
extern void ref_L00_003DD2B8_07(void *);
extern void ref_L00_003DD2B8_08(void *, void *);
extern void ref_L00_003DD2B8_09(void *, void *, void *);
extern void ref_L00_003DD2B8_10(void *, void *, void *);
extern int ref_L00_003DD2B8_11(void *, float, int, void *);
extern void ref_L00_003DD2B8_12(void *, void *, float);
extern char ref_L00_003DD2B8_13[];
extern float ref_L00_003DD2B8_14(void *);
extern float ref_L00_003DD2B8_15(void *, void *);
extern void ref_L00_003DD2B8_16(void *, void *, void *);
extern void ref_L00_003DD2B8_17(void *, void *, void *);
extern void ref_L00_003DD2B8_18(void *, void *, float);
extern void ref_L00_003DD2B8_19(void *, void *);
extern void ref_L00_003DD2B8_20(void *, void *);

extern void ref_L00_003DC3E0_00(int, int, char *);
extern void ref_L00_003DC3E0_01(float *, char *, float);
extern void ref_L00_003DC3E0_02(float *, char *, char *);
extern void ref_L00_003DC3E0_03(float *, char *, float *);
extern void ref_L00_003DC3E0_04(float *, char *, float);
extern struct C3PairGlobal { int x[2]; } ref_L00_003DC3E0_05;
extern void ref_L00_003DC3E0_06(float *, float *, char *, float);
extern int ref_L00_003DC3E0_07(void);
extern unsigned char *ref_L00_003DC3E0_08(float *, float *, int, int, float);
extern float ref_L00_003DC3E0_09(float, float);
extern float ref_L00_003DC3E0_10(int);
extern int ref_L00_003DC3E0_11(int, int);
extern unsigned char *ref_L00_003DC3E0_12(char *, float *, float, int, int);

extern void ref_L00_003E2E80_00(void *, int, int, int);
extern void ref_L00_003E2E80_01(void *, void *, void *);
extern void ref_L00_003E2E80_02(void *, void *, void *);
extern void ref_L00_003E2E80_03(void *, void *, float);
extern void ref_L00_003E2E80_04(void *, void *, void *);
extern void ref_L00_003E2E80_05(void *, void *, float);
extern float ref_L00_003E2E80_06(int);
extern int ref_L00_003E2E80_07(float);
extern void ref_L00_003E2E80_08(void *, int, int);
extern float D_L00_001B8DC0[];



extern void func_L00_003D6FB8_1(char *p);
extern long long func_002E67A0_2(int id);
extern float func_0031A888_1(void);
extern void func_002EE178_1(char *dst, char *src, float scale);


extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_L00_003DC820_1(char *pkt);

extern long long func_0027C878_1(char *p);

extern float func_00283248_3(float x, float y);

extern float func_00282E20_2(char *p);

extern void func_00283410_3(float *matrix, float *quat);

extern void func_00282F20_3(float *off, char *src, float scale);

extern void func_L00_003DC8A8_1(char *pkt, float angle);

extern void func_00280B90_1(char *pkt, float *matrix, int mode);

extern void ref_L00_003E0F58_00(char *);

extern void ref_L00_003E0F58_01(char *, float);

extern void func_L00_003E0CE8_1(char *pkt);

extern void func_L00_003E0D70_1(char *pkt, float angle);

extern long long func_002E67A0_1(char *p);

extern float func_802EE7A8_1(float x, float y);

extern float func_802EE2E8_1(char *p, float *v);

extern void func_802EE970_1(float *matrix, float *quat);

extern void func_802EE138_1(float *off, float *v, char *p);

extern void func_802EE3D0_1(float *dst, float *src, float angle);

extern void func_802EAC30_1(char *pkt, float *matrix, int mode);

extern void func_L00_003DFF98_1(char *p);

extern void func_L00_003E0020_1(char *p, float scale);

/* The vector the aim helpers read, at 0x001B8C80. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

extern L00AimVector D_L00_001B8C80;

/* func_L00_003D37E8 lives in L00_003D37E8-ribbon-g8.c. */

/* func_L00_003D3DE0 lives in L00_003D3DE0-g16.c. */


/* func_L00_003D3FB0 lives in L00_003D3FB0-g8.c. */

/* func_L00_003D40D8 lives in L00_003D40D8-g8.c. */

/* func_L00_003D4548 is defined in L00_003D4548-g8.c. */





/* shared native body of family a04928c6 */
void func_L00_003D6FB8(char *p)
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
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

void func_L00_003D7250(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_L00_003D6FB8_1(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_002E67A0_2(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = D_L00_001B8C80.x_140 - *(float *)pos;
    dy = D_L00_001B8C80.y_144 - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_802EE7A8_1(dx, dy);
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                              D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = func_0031A888_1();
    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_002EE178_1(pkt, pkt, scale);
    func_002EE178_1(pkt + 16, pkt + 16, scale);
    func_002EE178_1(pkt + 32, pkt + 32, scale);
    func_002EE178_1(pkt + 48, pkt + 48, scale);
    func_802EAC30_1(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_002EE178_1(pkt, pkt, 0.5f);
    func_002EE178_1(pkt + 16, pkt + 16, 0.5f);
    func_002EE178_1(pkt + 32, pkt + 32, 0.5f);
    func_002EE178_1(pkt + 48, pkt + 48, 0.5f);
    func_802EAC30_1(pkt, m, 0);
}

/* shared native body of family a04928c6 */
void func_L00_003DA2B0(char *p)
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
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}




/* func_L00_003DBF50 lives in L00_003D37E8-g8.c. */



void func_L00_003DC3E0(char *object, int unused, char *pos, char *direction)
{
    float a[4], b[4], c[4], d[4];
    struct C3PairGlobal colors;
    float e[4];
    char *state = *(char **)(object + 0x68);
    float angle, scale;
    int i;
    ref_L00_003DC3E0_00(0, 0, object);
    ref_L00_003DC3E0_01(a, direction, 2.0f);
    ref_L00_003DC3E0_02(a, a, pos);
    ref_L00_003DC3E0_03(d, pos, a);
    ref_L00_003DC3E0_01(b, direction, 0.15f);
    ref_L00_003DC3E0_02(b, pos, b);
    ref_L00_003DC3E0_01(d, d, 1.0f);
    ref_L00_003DC3E0_04(c, direction, 0.0009765625f);
    ref_L00_003DC3E0_01(c, c, 1.0f);
    colors = ref_L00_003DC3E0_05;
    angle = func_0031A888_1();
    i = 23;
    do {
        ref_L00_003DC3E0_06(e, d, direction, angle);
        --i;
        ref_L00_003DC3E0_08(b, e, colors.x[ref_L00_003DC3E0_07() % 2], 20, 1.0f / 24.0f);
        angle = ref_L00_003DC3E0_09(angle, 0.2731819748878479f);
    } while (i >= 0);
    for (i = 0; i < 24; i++) {
        scale = ref_L00_003DC3E0_10(i) * 0.06521739065647125f;
        {
            int *color = &colors.x[ref_L00_003DC3E0_07() % 2];
            int n = ref_L00_003DC3E0_11(30, 50);
            ref_L00_003DC3E0_12(pos, c, scale, *color, n);
        }
    }
    qcopy(state, c);
}

typedef int Quad640 __attribute__((mode(TI)));

extern void func_L00_003DCC48(float f12, float f13, float f14, void *pos, char *a1, int a2, int a3);
extern int func_0031A768_1(int lo, int hi);
extern void func_L00_003DC910(char *pos, int a1, float fA, int a2, float fB, char *a3, int t0, float fC);
extern void func_L00_003DCAC8(char *pos, int a1, int a2, float f12, float f13, char *a3, int t0,
                              char *src);

/* Effect update by state: 1 starts the burst (one random-angle puff), 2 counts the timer down and draws the two fade rings. */
void func_L00_003DC640(char *obj)
{
    char *s = *(char **)(obj + 0x68);
    Quad640 pos;
    float zero, scale;
    int n;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 1:
        pos = *(Quad640 *)(obj + 0x10);
        func_L00_003DCC48(0.0f, 0.85f, 0.25f, &pos, s + 0x10, 0x103080, 4);
        scale = *(float *)(obj + 0x2C) * 95.0f;
        n = func_0031A768_1(0x5F, 0x6F) >> 2;
        func_L00_003DC910(obj + 0x10, 0x103080, scale, n, func_0031A888_1(), (char *)0xB, 2, -1.0f);
        break;
    case 2:
        if (--*(int *)(s + 0x6C) <= 0)
            *(int *)(s + 0x6C) = 0;
        zero = 0.0f;
        pos = *(Quad640 *)(obj + 0x10);
        func_L00_003DCC48(zero, 0.85f, 0.25f, &pos, s + 0x10, 0x103080, 4);
        if (*(int *)(s + 0x7C) == 0) {
            func_L00_003DCAC8(obj + 0x10, 0x103080, *(int *)(s + 0x6C),
                              *(float *)(obj + 0x2C) * 45.0f, zero, (char *)0xB, 2, s + 0x50);
            func_L00_003DCAC8(obj + 0x10, 0x3F3F3F, *(int *)(s + 0x6C),
                              *(float *)(obj + 0x2C) * 33.75f, zero, (char *)0xB, 2, s + 0x50);
        }
        break;
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003DC820(char *p)
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

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003DC8A8(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003DC910(char *pos, int a1, float fA, int a2, float fB, char *a3, int t0, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DC820_1(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003DC8A8_1(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}

/* Builds a 144-byte packet, derives a quaternion from source floats through four float helpers, writes the last matrix row from a source point plus a computed offset, then dispatches the packet. */
void func_L00_003DCAC8(char *pos, int a1, int a2, float f12, float f13, char *a3, int t0,
                       char *src)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DC820_1(pkt);
    r = func_0027C878_1(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = func_00283248_3(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -func_00283248_3(func_00282E20_2(src), *(float *)(src + 8));
    quat[0] = f13;

    func_00283410_3(m, quat);
    func_00282F20_3(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003DC8A8_1(pkt, f12);
    func_00280B90_1(pkt, m, 0);
}


/* The moving part of a bouncing object: phase, flags and a pointer to its motion state. */
typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char phase;
    char pad21[2];
    unsigned char fade;
    char pad24[0x10];
    unsigned short flags;
    char pad36[0x32];
    struct BounceState *state;
    char pad6C[0x54];
    float orientation[4];
} BounceObject;

/* Motion state of a BounceObject: velocity, spin, pivot and the bounce timer. */
typedef struct BounceState {
    float velocity[4];
    float spin[4];
    float pivot[3];
    float radius;
    int timer;
    int flags;
    float gravity;
} BounceState;

/* Per-frame update of a bouncing object: runs its timed phases, then moves and bounces it. */
void func_L00_003DD2B8(BounceObject *object)
{
    float point[4];
    float rotation[12];
    float after[4], delta[4], probe[4];
    float matrix[16], normalStep[4], axis[4];
    BounceState *state = object->state;
    float radius, length, projection;
    switch (object->phase) {
    case 0:
        ref_L00_003DD2B8_07(object);
        return;
    case 1:
        if (ref_L00_003DD2B8_00(&state->timer)) {
            object->phase = 3;
            state->timer = ref_L00_003DD2B8_01(10.0f);
            object->flags |= 0x2000;
            return;
        }
        break;
    case 2:
        ref_L00_003DD2B8_02(point, state->pivot, object->orientation);
        ref_L00_003DD2B8_03(point, point, object->position);
        if (state->flags & 2) {
            ref_L00_003DD2B8_04(object, 0.3f, 10.0f, point, -1);
        } else {
            ref_L00_003DD2B8_05(object, ref_L00_003DD2B8_06, point, 0.0f, 0.0f,
                5, 3, 5, 1.0f, 0.5f, 9.0f, 0.3330000042915344f, -1, 0.0f, 0, 0, -1, 0, 0x810001);
        }
        ref_L00_003DD2B8_07(object);
        return;
    case 3:
        if (ref_L00_003DD2B8_00(&state->timer)) {
            ref_L00_003DD2B8_07(object);
            return;
        }
        object->fade = ref_L00_003DD2B8_01((float)state->timer * 12.8f);
        break;
    }
    ref_L00_003DD2B8_08(rotation, state->spin);
    ref_L00_003DD2B8_02(point, state->pivot, object->orientation);
    ref_L00_003DD2B8_09(object->orientation, rotation, object->orientation);
    ref_L00_003DD2B8_02(after, state->pivot, object->orientation);
    ref_L00_003DD2B8_10(delta, after, point);
    ref_L00_003DD2B8_10(object->position, object->position, delta);
    ref_L00_003DD2B8_03(object->position, object->position, state->velocity);
    radius = state->radius;
    state->velocity[2] -= state->gravity;
    ref_L00_003DD2B8_02(probe, state->pivot, object->orientation);
    ref_L00_003DD2B8_03(probe, probe, object->position);
    if (ref_L00_003DD2B8_11(probe, radius, 0, object)) {
        ref_L00_003DD2B8_12(ref_L00_003DD2B8_13, ref_L00_003DD2B8_13, 1.0f);
        length = ref_L00_003DD2B8_14(state->velocity);
        projection = ref_L00_003DD2B8_15(state->velocity, ref_L00_003DD2B8_13);
        if (projection < 0.0f) {
            ref_L00_003DD2B8_16(state->velocity, state->velocity, ref_L00_003DD2B8_13);
            ref_L00_003DD2B8_12(normalStep, ref_L00_003DD2B8_13, projection * 0.5f);
            ref_L00_003DD2B8_03(state->velocity, state->velocity, normalStep);
            ref_L00_003DD2B8_12(state->velocity, state->velocity, length);
            ref_L00_003DD2B8_17(axis, ref_L00_003DD2B8_13, state->velocity);
            ref_L00_003DD2B8_12(axis, axis, 1.0f);
            ref_L00_003DD2B8_18(axis, axis, ref_L00_003DD2B8_14(state->spin));
            ref_L00_003DD2B8_19(axis, matrix);
            ref_L00_003DD2B8_20(matrix, state->spin);
        }
    }
}

void func_L00_003DD680(char *p)
{
    if (*(unsigned char *)(p + 0x20) == 0) {
        *(unsigned short *)(p + 0x34) |= 0x800;
        *(unsigned char *)(p + 0x20) = 1;
    }
}

/* func_L00_003DD6A8 lives in L00_003DD6A8-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003DDEC8);

/* func_L00_003DE088 lives in L00_003DE088-g8.c. */


/* func_L00_003DE490 is defined in L00_003DE490-basis-g8.c. */

/* func_L00_003DE950 lives in L00_003DE950-g8.c. */


INCLUDE_ASM("asm/levels", func_L00_003DF710);


/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003DFF98(char *p)
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

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003E0020(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003E0088(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003DFF98_1(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003E0020_1(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003E0CE8(char *p)
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

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003E0D70(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Builds a 144-byte packet, derives a quaternion from source floats through four float helpers, writes the last matrix row from a source point plus a computed offset, then dispatches the packet. */
void func_L00_003E0DD8(char *pos, int a1, int a2, char *a3, int t0,
                                        char *src, float f12, float f13)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    func_L00_003E0CE8_1(pkt);
    r = func_0027C878_1(a3);

    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;

    quat[3] = 0.0f;
    quat[2] = func_00283248_3(*(float *)(src + 0), *(float *)(src + 4));
    quat[1] = -func_00283248_3(func_00282E20_2(src), *(float *)(src + 8));
    quat[0] = f13;

    func_00283410_3(m, quat);
    func_00282F20_3(off, src, 0.025f);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    func_L00_003E0D70_1(pkt, f12);
    func_00280B90_1(pkt, m, 0);
}

/* Builds a 144-byte packet, aims a quaternion at the shared 0x001B8C80 vector from pos through three float helpers, derives an offset basis by a fourth, writes the last matrix row from pos plus that offset, then dispatches the packet. */
void func_L00_003E0F58(char *pos, int a1, int a2, char *a3, int t0,
                       float fA, float fB, float fC)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;

    ref_L00_003E0F58_00(pkt);
    r = func_002E67A0_1(a3);

    *(long long *)(pkt + 136) = ((long long)t0 << 2) | 0x8000000040LL;
    *(long long *)(pkt + 128) = 280993940374112LL;
    *(int *)(pkt + 76) = a1 + (a2 << 24);
    *(int *)(pkt + 72) = a1 + (a2 << 24);
    *(int *)(pkt + 68) = a1 + (a2 << 24);
    *(int *)(pkt + 64) = a1 + (a2 << 24);
    *(long long *)(pkt + 112) = 0LL;
    *(long long *)(pkt + 120) = r;

    quat[3] = 0.0f;
    quat[2] = func_802EE7A8_1(D_L00_001B8C80.x_140 - *(float *)(pos + 0),
                              D_L00_001B8C80.y_144 - *(float *)(pos + 4));
    quat[1] = -func_802EE7A8_1(func_802EE2E8_1(pos, &D_L00_001B8C80.x_140),
                               D_L00_001B8C80.z_148 - *(float *)(pos + 8));
    quat[0] = fB;

    func_802EE970_1(m, quat);
    func_802EE138_1(off, &D_L00_001B8C80.x_140, pos);
    func_802EE3D0_1(off, off, fC);

    m[12] = *(float *)(pos + 0) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;

    ref_L00_003E0F58_01(pkt, fA);
    func_802EAC30_1(pkt, m, 0);
}


INCLUDE_ASM("asm/levels", func_L00_003E2510);


/* A trail quad packet: four vertices, their colors and UVs, then the GS words. */
typedef struct {
    float vertex[4][4];
    unsigned int color[4];
    float uv[8];
    long long primitive;
    long long texture;
    long long mode;
    long long flags;
} __attribute__((aligned(16))) TrailPacket;

/* Draws a two-layer trail along a chain of points, fading its alpha toward the end. */
void func_L00_003E2E80(float *points, int tex1, int tex2, int count,
                       unsigned int color1, unsigned int color2,
                       float unused, float scale, float scroll)
{
    TrailPacket core;
    TrailPacket outer;
    float cross[4], offset[4], ray[4], tangent[4];
    TrailPacket *outerPtr;
    int alpha1 = color1 >> 24, alpha2 = color2 >> 24;
    float *next = points + 4;
    int i;
    float zero;

    ref_L00_003E2E80_00(&core, tex1, 1, 128);
    outerPtr = &outer; /* a real pointer local, as in retail's stack layout */
    *(int *)&core.uv[0] = 0;
    zero = core.uv[0];
    core.color[3] = color1;
    core.color[2] = color1;
    core.color[1] = color1;
    core.color[0] = color1;
    *(int *)&core.uv[1] = 0;
    core.uv[3] = 1;
    *(int *)&core.uv[5] = 0;
    core.uv[7] = 1;
    core.uv[2] = scroll;
    core.uv[0] = scroll;
    core.uv[6] = scroll + 1;
    core.uv[4] = scroll + 1;

    ref_L00_003E2E80_00(&outer, tex2, 1, 128);
    outer.color[3] = color2;
    outer.color[2] = color2;
    outer.color[1] = color2;
    outer.color[0] = color2;
    outer.uv[1] = zero;
    outer.uv[3] = 1;
    outer.uv[7] = 1;
    outer.uv[5] = zero;
    outer.uv[2] = scroll;
    outer.uv[6] = scroll + 1;
    outer.uv[0] = scroll;
    outer.uv[4] = scroll + 1;

    ref_L00_003E2E80_01(ray, points, D_L00_001B8DC0);
    ref_L00_003E2E80_01(tangent, next, points);
    ref_L00_003E2E80_02(cross, tangent, ray);
    ref_L00_003E2E80_03(offset, cross, points[3]);
    ref_L00_003E2E80_04(&core.vertex[0], points, offset);
    ref_L00_003E2E80_01(&core.vertex[1], points, offset);
    ref_L00_003E2E80_05(offset, offset, scale);
    ref_L00_003E2E80_04(outerPtr->vertex[0], points, offset);
    ref_L00_003E2E80_01(&outer.vertex[1], points, offset);

    for (i = 1; i < count; i++) {
        float *point = points + i * 4;

        ref_L00_003E2E80_01(ray, point, D_L00_001B8DC0);
        ref_L00_003E2E80_01(tangent, point, points + (i - 1) * 4);
        ref_L00_003E2E80_02(cross, tangent, ray);
        ref_L00_003E2E80_03(offset, cross, point[3]);
        ref_L00_003E2E80_04(&core.vertex[2], point, offset);
        ref_L00_003E2E80_01(&core.vertex[3], point, offset);
        ref_L00_003E2E80_05(offset, offset, scale);
        ref_L00_003E2E80_04(&outer.vertex[2], point, offset);
        ref_L00_003E2E80_01(&outer.vertex[3], point, offset);

        core.color[2] = core.color[3] = (color1 & 0xFFFFFF) |
            (ref_L00_003E2E80_07(ref_L00_003E2E80_06(alpha1) * (1 - ref_L00_003E2E80_06(i) / ref_L00_003E2E80_06(count))) << 24);
        outer.color[2] = outer.color[3] = (color2 & 0xFFFFFF) |
            (ref_L00_003E2E80_07(ref_L00_003E2E80_06(alpha2) * (1 - ref_L00_003E2E80_06(i) / ref_L00_003E2E80_06(count))) << 24);

        ref_L00_003E2E80_08(&core, 0, 0);
        ref_L00_003E2E80_08(&outer, 0, 0);

        qcopy(&core.vertex[0], &core.vertex[2]);
        qcopy(&core.vertex[1], &core.vertex[3]);
        qcopy(&outer.vertex[0], &outer.vertex[2]);
        qcopy(&outer.vertex[1], &outer.vertex[3]);
        core.color[0] = core.color[2];
        core.color[1] = core.color[3];
        outer.color[0] = outer.color[2];
        outer.color[1] = outer.color[3];
    }
}
