#include "common.h"

typedef int VectorBits __attribute__((mode(TI)));
typedef union { VectorBits bits; float f[4]; } __attribute__((aligned(16))) BeamVector;
typedef float Vector[4] __attribute__((aligned(16)));
typedef struct { float vertices[4][4]; unsigned int colors[4]; float uv[4][2]; u64 registers[4]; } __attribute__((aligned(16))) BeamQuad;
extern void func_L00_003EA050(char *);
extern void func_00282D30(void *, void *, float);
extern float func_00283CE0(int);


#define RAC2_T_VEC16_FC936841D

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

typedef struct {
    void *object;
    int index;
    int unused0;
    float scale;
    int unused1[4];
} Entry_24efc0;

extern char *D_L00_001B2B54 __attribute__((sda));

extern void func_002833F0_1(char *a, char *b);

extern float func_00283198_1(float value);

extern void func_00282D30_3(char *a, char *b, float value);

extern float func_00283B98_3(float value, float scale);

extern int func_002ABB78(char *object);

extern float *func_002AB1F0(char *object);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern float func_00283B98_2(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern int func_002A7820_2(int, int);

extern float func_002A7878_5(float, float);

extern float func_002A7940_2(void);

extern void func_00281EB8(char *, int, int, int, float, float, float);

extern void ref_L00_003E4948_00(void);

extern int D_L00_001B05DC_2 __attribute__((sda));

extern int D_L00_001B2B50_1 __attribute__((sda));

extern int D_L00_001B05DC_1 __attribute__((sda));

extern int func_002B4038(short id, int mode);

extern int func_00283DB8(Vec16_Fc936841d *v, float scale);

extern void func_0029F338(char *object);

extern void func_L00_003E5710(char *object);

extern void func_L00_003E5978(char *object);

extern void func_L00_003E55B0(char *object);

extern void func_L00_003E5BD8(char *object);

extern void func_L00_003E6030(char *object);

extern void func_L00_003E6710(char *object);

extern int func_00282948(void *p);

extern int func_001163B0(void);

extern void func_L00_003E6778(char *rec, int a, float b, float c, int d);

extern void func_L00_003E6C10(char *rec);

extern void func_L00_003E6F48(char *object);

extern int func_00283CF0(float value);

extern int func_00283D38(char *object, int index, float scale);

extern void func_002A0488(int handle, int a, int b, int c);

extern Entry_24efc0 D_L00_0024EFC0[];

#ifndef RAC2_T_VEC16_FC936841D
#endif

extern char D_0018A0E0[];
extern unsigned char *D_L00_001FEA14;
extern char D_L00_001B8DC0[];
extern char D_L00_001A8F20_1[] __attribute__((sda));
extern void func_00282CF0(char *, char *, char *);
extern float func_00283248(float, float);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_00283B98(float, float);
extern void func_002AF000(float *, float, float, float);
extern int func_002A77E0(int);
extern char *func_002BDCE8(float *, float, float, int, float *, float, float, unsigned, int);
extern char *func_002C16C0_1(float *, float *, int, int, unsigned, int, float, float, float, float, float);
/* Emit twenty paired particles around a position, optionally adding two final flashes. */
void func_L00_003E3258(float *pos, int unused, int extra)
{
    float v[4], dir[4], out[4];
    float angle, speed, scale, mag, direction;
    int id, i, n;
    char *p, *d;
    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)pos);
    angle = func_00283248(v[0], v[1]);
    for (i = 19; i >= 0; i--) {
        func_00282D30(dir, D_0018A0E0, -(func_002A7878(0.2f, 3.0f) * 0.01666666753590107f));
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        speed = func_002A7878(0.3f, 0.75f) * 210000.0f;
        out[0] = pos[0] + func_002A78D8(0.0f, 0.2f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.2f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.2f);
        p = func_002BDCE8(out, 0.0f, 1.0f, id, dir, 1.01f, speed, 0x7F202020, 1);
        if (p) {
            p[3] = 68;
            *(short *)(p + 10) = 90;
            d = p + 32;
            p[9] = func_00283CF0(4.0f) + 64;
            *(float *)(d + 28) = func_00283CE0(5);
            *(int *)(d + 4) = 3;
            d[10] = 48;
            d[11] = p[10];
        }
        scale = func_002A7878(1.0f, 2.0f);
        mag = func_002A7878(0.0f, 1.396263599395752f);
        direction = func_00283B98(angle, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.01666666753590107f, direction, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.1f);
        func_002C16C0_1(out, dir, 30, 127, 0x7F7F7F, id,
            func_002A7878(0.1f, 0.5f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    }
    if (extra == 1) {
        char *last;
        speed = 525000.0f;
        n = func_002A77E0(255);
        last = func_002C16C0_1(pos, (float *)D_L00_001A8F20_1, 5, 127, 0x207080, n, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
        last = func_002C16C0_1(pos, (float *)D_L00_001A8F20_1, 5, 127, 0x207080, (n + 128) & 255, speed, 0.0f, 1.0f, 0.0f, 1.0f);
        if (last) last[2] = *D_L00_001FEA14;
    }
}

extern char D_L00_001B8DC0[];

extern void func_00282CF0(char *dst, char *src, char *arg);

extern float func_00283248(float, float);

extern float func_002A7878(float, float);

extern float func_002A78D8(float, float);

extern float func_00283B98(float, float);

extern void func_002AF000(float *, float, float, float);

extern void func_002C16C0(float *, float *, int, int, unsigned int, int,
                          float, float, float, float, float);

/* Twenty rounds that spawn a particle at the point: each round draws a step and a random
   magnitude, jitters the point on each axis and hands the result to the spawn helper with
   210000.0f, 500.0f, 1.0f, 0.0f and 1.0f; the original game role is unknown. */
void func_L00_003E3668(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float ang;
    float angle;
    float scale;
    float mag;
    float speed;
    int id;
    int i;

    func_00282CF0((char *)v, D_L00_001B8DC0, (char *)pos);
    ang = func_00283248(v[0], v[1]);

    for (i = 19; i >= 0; i--) {
        scale = func_002A7878(0.25f, 0.5f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        func_002A7878(0.05f, 0.2f);
        speed = 210000.0f;
        mag = func_002A7878(0.0f, 1.396263599395752f);
        angle = func_00283B98(ang, func_002A78D8(0.0f, 1.396263599395752f));
        func_002AF000(dir, scale * 0.01666666753590107f, angle, mag);
        out[0] = pos[0] + func_002A78D8(0.0f, 0.075f);
        out[1] = pos[1] + func_002A78D8(0.0f, 0.075f);
        out[2] = pos[2] + func_002A78D8(0.0f, 0.075f);
        func_002C16C0(out, dir, 15, 127, 0x007F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * speed, 500.0f, 1.0f, 0.0f, 1.0f);
    }
}

/* Family 40487154aa250cc8: fixed-field addend writes into one resource record. */
void func_L00_003E3890(char *object)
{
    char *data;
    float x;
    float y;
    float z;

    data = *(char **)(object + 104);
    func_002833F0_1(object + 192, object + 240);
    x = func_00283198_1(*(float *)(data + 4)) * 0.15f + 0.35000002f;
    y = func_00283198_1(*(float *)(data + 8)) * 0.15f + 0.35000002f;
    z = func_00283198_1(*(float *)(data + 12)) * 0.15f + 0.35000002f;
    func_00282D30_3(object + 192, object + 192, x);
    func_00282D30_3(object + 208, object + 208, y);
    func_00282D30_3(object + 224, object + 224, z);
    *(float *)(data + 4) = func_00283B98_3(*(float *)(data + 4), 0.5f);
    *(float *)(data + 8) = func_00283B98_3(*(float *)(data + 8), 0.5f);
    *(float *)(data + 12) = func_00283B98_3(*(float *)(data + 12), 0.5f);
}

/* calls two guards and returns 1 only when both succeed and the object's float field is not positive */
int func_L00_003E39B8(char *object)
{
    float *p;

    if (func_002ABB78(object) != 0)
        return 0;
    p = func_002AB1F0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}

/* func_L00_003E4508 is defined in L00_003E4508-g8.c. */

void func_L00_003E4948(void)
{
    ref_L00_003E4948_00();
}

extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern void *func_002C65A0(void *, void *, int, unsigned int, int, int, int, float, float, float, int);
extern char D_L00_001FE940[];
extern char D_L00_001A8F20[] __attribute__((sda));
void func_L00_003E4968(char *a0) {
    float a[4];
    float b[4];
    float c[4];
    float d[4];
    char *tbl;
    int n;
    char *r;
    char *v;
    float big;
    int i;

    v = *(char **)(a0 + 0x68);
    { float *p = (float *)(v + 0x14);
    a[0] = p[0];
    a[1] = p[1];
    a[2] = p[2]; }
    a[3] = 0.0f;
    func_00282D30(b, a0 + 0xD0, -0.1f);
    func_00282CC0(a, a, b);
    func_00282D30(c, a0 + 0xE0, 0.15f);
    func_00282CC0(a, a, c);
    func_00282D30(c, a0 + 0xE0, -0.033333335f);
    tbl = D_L00_001FE940;
    for (i = 8; i >= 0; i--) {
        d[0] = a[0] + func_002A78D8(0.0f, 0.1f);
        d[1] = a[1] + func_002A78D8(0.0f, 0.1f);
        d[2] = a[2] + func_002A78D8(0.0f, 0.1f);
        n = func_002A77E0(0xFF);
        big = 42000.0f;
        func_002C65A0(d, D_L00_001A8F20, 4, 0x808080, n, 0x7F, 0x7F, big, big, 0.0f, 1);
        big = 273000.0f;
        r = func_002C65A0(a, D_L00_001A8F20, 4, 0x406080, n, 0x10, 0x10, big, big, 0.0f, 1);
        if (r != 0)
            *(unsigned char *)(r + 2) = *(unsigned char *)(*(unsigned *)(tbl + 0xD4));
        func_00282CC0(a, a, c);
    }
}

/* func_L00_003E4B80 is defined in L00_003E4B80-g.c. */


/* func_L00_003E51C0 is defined in L00_003E51C0-g8.c. */

void func_L00_003E5328(void)
{
    D_L00_001B05DC_2 = 0;
}

/* clears two words of the shared state block; the second store reaches through
   $gp because it lands in the return delay slot */
void func_L00_003E5330(void)
{
    D_L00_001B2B50_1 = 0;
    D_L00_001B05DC_1 = 0;
}

extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282FB8(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern void ref_L00_003E5340_00(float *, float *, int, int, int);

/* Emits ten particles at POSITION: one thrown towards D_L00_001B8DC0 with a random spread, then
   nine at random upward angles turned by the object's matrix, about a third of them (rand() % 3
   == 0) in mode 1. */
void func_L00_003E5340(char *object, float *position)
{
    Vector delta, velocity, random;
    float distance;
    int divisor = 3;
    int i = 8;
    int mode;

    func_00282CF0((char *)delta, D_L00_001B8DC0, (char *)position);
    distance = func_00282DF0(delta);
    *(VectorBits *)random = 0;
    random[0] = func_002A7878(-1.0f, 1.0f);
    random[1] = func_002A7878(-1.0f, 1.0f);
    random[2] = func_002A7878(-1.0f, 1.0f);
    delta[2] += distance * 0.5f;
    *(VectorBits *)velocity = *(VectorBits *)random;
    func_00282F20(velocity, velocity, distance * 0.0033333336468786f);
    func_00282F20(delta, delta, (distance + distance) * 0.01666666753590107f);
    func_00282CC0(velocity, velocity, delta);
    func_00282FB8(velocity, velocity, 0.1666666716337204f);
    ref_L00_003E5340_00(position, velocity, func_002A7820(60, 90), 0, 0);
    for (; i >= 0; i--) {
        float pitch, yaw, speed;

        mode = 0;
        pitch = func_002A7878(0.2617994248867035f, 1.3089970350265503f);
        yaw = func_002A7940();
        speed = func_002A7878(8.0f, 12.0f);
        func_002AF000(random, speed * 0.01666666753590107f, yaw, pitch);
        random[2] += 0.05000000447034836f;
        if (func_001163B0() % divisor == 0)
            mode = 1;
        func_00283098(random, random, object + 0xC0);
        ref_L00_003E5340_00(position, random, func_002A7820(60, 90), mode, 0);
    }
}

#include "common.h"

/* func_L00_003E5650 is defined in L00_003E5650-qcopy.c. */

/* func_L00_003E5710 is defined in L00_003E3258-g8.c. */

/* func_L00_003E5978 is defined in L00_003E3258-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003E5BD8);

INCLUDE_ASM("asm/levels", func_L00_003E6030);


/* Walks the shared table of 0x50-byte records and, for the one owned by OBJECT, either
   releases the owner when the record is busy, or (half of the time) runs the effect helper
   twice with a zero amount; the record is then closed. The amount is converted from an int
   so that the compiler keeps it in a saved register across the calls, as the retail code
   does. */
void func_L00_003E6628(char *object)
{
    char *rec;
    int zero = 0;
    float amount = (float)zero;
    int offset = 0;
    int i = 0;

    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2B50_1);
        if (*(int *)(rec + 0x30) == (int)object) {
            if (func_00282948(rec + 0x34) != 0) {
                if (*(int *)(rec + 0x38) == 0) {
                    *(int *)(rec + 0x30) = 0;
                }
            } else if ((func_001163B0() & 1) == 0) {
                func_L00_003E6778(rec, 0, amount, amount, 0);
                func_L00_003E6778(rec, 0, amount, amount, 0);
            }
            func_L00_003E6C10(rec);
        }
        offset += 0x50;
    } while (i >= 0);
}

void func_L00_003E6710(char *object)
{
    char *rec;
    int i;
    int offset;

    offset = 0;
    i = 0;
    do {
        i--;
        rec = (char *)(offset + (int)D_L00_001B2B50_1);
        if (*(int *)(rec + 0x30) == (int)object)
            func_L00_003E6F48(rec);
        offset += 0x50;
    } while (i >= 0);
}

/* func_L00_003E6778 is defined in L00_003E6778.c. */


extern char *D_L00_001B2BB8 __attribute__((sda));
extern void ref_L00_003E6F48_01(char *rec, float f1, int a1, int a2, int a3,
                                float f2, int a4, float f3);

/* Same body as func_L00_003F09A0, with this function's own callees. */
extern char *ref_L00_003E6F48_00 __attribute__((sda));
void func_L00_003E6F48(char *obj)
{
    char *rec;
    int i;

    for (i = 0; i < 320; i++) {
        rec = (char *)(i * 128 + (int)ref_L00_003E6F48_00);
        if (*(int *)(rec + 0x7C) == (int)obj)
            ref_L00_003E6F48_01(rec, *(float *)(rec + 0x48), *(int *)(rec + 0x68),
                                *(int *)(rec + 0x60), 46, *(float *)(rec + 0x34),
                                *(int *)(rec + 0x70), 0.25f);
    }
}

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003E6FC8(char *p)
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
void func_L00_003E7050(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* func_L00_003E70B8 is defined in L00_003E70B8.c. */

/* func_L00_003E7650 is defined in L00_003E7650-qcopy.c. */

void func_L00_003E7760(void)
{
}

INCLUDE_ASM("asm/levels", func_L00_003E7C88);

/* func_L00_003E7E40 lives in L00_003E7E40-trails.c. */

void func_L00_003E80A8(int index, char *object)
{
    int r;
    int high;

    *(char *)((char *)D_L00_0024EFC0[index].object + 0x23) =
        func_00283CF0(D_L00_0024EFC0[index].scale * 96.0f);
    r = func_00283D38(object, D_L00_0024EFC0[index].index,
                      D_L00_0024EFC0[index].scale);
    high = (r >> 16) & 0xFF;
    func_002A0488((int)D_L00_0024EFC0[index].object, r & 0xFF, (r >> 8) & 0xFF,
                  high);
}

/* func_L00_003E8180 uses small data in L00_003E8180-g8.c. */

/* func_L00_003E9490 is defined in L00_003E9490-qcopy.c. */

/* Component-wise cubic interpolation, with exact endpoint vector copies. */
void func_L00_003E9540(float *out, float *b, float *c, float *a, float *d, float t)
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

/* Shared native body; original game role is unknown. */
void func_L00_003E9660(int unused, float *p, int n)
{
    float *v;
    int count;
    if (n <= 0)
        return;
    v = p;
    count = n;
    do {
        v[0] = func_00283B98_2(v[0], v[3]);
        v[1] = func_00283B98_2(v[1], v[4]);
        v[2] = func_00283B98_2(v[2], v[5]);
        v[9] = func_00283B98_2(v[9], v[12]);
        v[10] = func_00283B98_2(v[10], v[13]);
        v[11] = func_00283B98_2(v[11], v[14]);
        v[20] = func_00283180(v[0]) * v[6];
        v[21] = func_00283198(v[1]) * v[7];
        v[22] = -func_00283198(v[2]) * v[8];
        v[24] = func_00283180(v[9]) * v[15];
        v[25] = func_00283198(v[10]) * v[16];
        v[26] = -func_00283198(v[11]) * v[17];
        v += 32;
    } while (--count != 0);
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_003E9A98(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

/* Derives a value from half of one argument, merges a helper's low byte into a packed word, then scales an input float, doubles a second helper's result and dispatches a seven-argument spawn. */
void func_L00_003E9B00(int p0, int p1, int p2, int p3, float v)
{
    int r;
    float s;
    float t;

    r = func_002A7820_2(p3 >> 1, p3);
    p2 = p2 | (r << 24);
    s = func_002A7878_5(v * 0.75f, v);
    s = s + s;
    t = func_002A7940_2();
    func_00281EB8((char *)p1, 44, p2, 1, s, 0.08f, t);
}

/* Draw a two-layer ribbon along a sequence of sampled beam points. */
/* func_L00_003E9B90 is defined in L00_003E9B90-ribbon.c. */


/* straight-line constant-store body (no calls, no branches, no loads) */
void func_L00_003EA050(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 88) = 0;
    *(float *)(p + 96) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(int *)(p + 84) = 0;
    *(float *)(p + 92) = 1.0f;
    *(int *)(p + 100) = 0;
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
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}
