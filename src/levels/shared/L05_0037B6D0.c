#include "common.h"

extern float func_332BB0(float, float);
extern int func_307778(float);
extern int func_332AF8(int, int);
extern void func_332C60(void *, float, float);
extern char *func_352B28(void *, void *, int, int, int, int, int, int, float, float, float);
extern float func_306CD0(float, float);
extern float func_307620(float, float);
extern char *func_347040(void *, int, void *, int, float, float, float, float, int);
extern float func_307768(int);
typedef struct {
    char pad[0x140];
    float pos[4];
} ParticleCamera99268;
extern ParticleCamera99268 D_L05_001B9580;
extern unsigned char *D_L05_001FF240[];
typedef struct {
    int v[2];
} __attribute__((packed)) ParticleColors99268;
extern ParticleColors99268 D_L05_001AEC00;
extern void func_33B330(void *, float, float, float);

extern int D_L05_00221D3C;
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern char *D_L05_001BFB18;
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_00283DB8(void *, float);

extern int func_002ED688(char *);

extern void func_002EE678(char *, int);

extern int func_002A7820_1(int, int);

extern int func_001163B0(void);

extern int D_L05_00221D10[];

extern int D_L05_00221D28;

extern void func_L05_0037BB28(char *);

extern void func_L05_0037BD40(char *);

extern void func_L05_0037BC08(char *);

extern void func_L05_0037BF48(char *);

extern float func_332B50(float, float);

extern char *func_379CA0(char *);

extern void func_379FA0(char *, int, int, int, float, float, float, float, int, int, int);

extern int func_332AB8(int);

extern void func_3719A8(int, int, char *, int);

extern void func_306AD8(void *, void *, void *);

extern void func_306630(void *, void *, void *);

typedef struct {
    float f[38];
    int timer;
    char *owner;
    int active;
    int pad;
    int dying;
    int pad2;
} Record233560;
extern Record233560 D_L05_00233560[24];
extern void func_L00_003F26C8(char *, char *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);

extern void func_00282CC0(void *, void *, void *);
extern float func_00283B98(float, float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00282948(void *);

typedef unsigned int Quad37DA58 __attribute__((mode(TI)));
extern char D_L05_001B96C0[];
extern void func_00282F20(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern char *func_002C2210(void *, int, float, float, int, int, int, void *, int, float);
extern float func_002A78D8(float, float);
extern int func_002A77E0(int);
extern int func_00283CF0(float);

/* looks up an object, then sets flags, arms a stored value and calls one of two helper pairs before building a timer */
void func_L05_0037B6D0(char *obj)
{
    char *s;

    s = (char *)func_002ED688(obj);
    if (s == 0)
        return;
    if (*(int *)(s + 288) == 0)
        return;
    if (*(int *)(s + 284) != 0) {
        int *p = D_L05_00221D10;
        int one = 1;

        *(int *)(s + 280) = one;
        p[3] += one;
        if (func_L05_0037CEB8(obj) != 5) {
            func_002EE678(obj, 4);
            *(float *)(s + 120) = (func_001163B0() & 1) ? -1.0f : 1.0f;
            if (func_001163B0() & 1)
                *(float *)(s + 116) = -1.0f;
            else
                *(float *)(s + 116) = 1.0f;
            *(int *)(s + 252) = one;
            *(int *)(s + 112) = 0;
            *(int *)(s + 124) = 0;
        } else {
            func_002EE678(obj, 7);
        }
        *(int *)(s + 304) = func_002A7820_1(120, 500);
    } else {
        int *p = D_L05_00221D10;

        *(int *)(s + 280) = 1;
        p[3] += 1;
        if (func_L05_0037CEB8(obj) != 5)
            func_002EE678(obj, 4);
        else
            func_002EE678(obj, 7);
        *(int *)(s + 304) = func_002A7820_1(120, 500);
        *(int *)(s + 252) = 0;
    }
}





void func_L05_0037B948(char *obj, int check, float range)
{
    float angles[4];
    float matrix[16];
    float sphere[4];
    char *s = (char *)func_002ED688(obj);
    float angle;
    float elevation;
    float limit;
    if (!s)
        return;
    if (!*(char **)(s + 0x120))
        return;
    *(int *)(s + 0x104) = 0;
    *(int *)(s + 0x108) = 0;
    limit = 0.7068582773f;
    if (D_L05_00221D3C == 1)
        return;
    if (func_00282E48(*(char **)(s + 0x120) + 0x10, obj + 0x10) > range)
        return;
    if (func_002761F8(obj + 0x10, *(char **)(s + 0x120) + 0x10, 0, obj, 0)) {
        if (!D_L05_001BFB18)
            return;
        if (*(short *)(D_L05_001BFB18 + 0xAA) != *(short *)(*(char **)(s + 0x120) + 0xAA))
            return;
    }
    func_00283658(matrix, obj + 0xC0);
    func_002AB6D8(matrix, angles);
    angle = func_00283C80(func_00283248(
        *(float *)(*(char **)(s + 0x120) + 0x10) - *(float *)(obj + 0x10),
        *(float *)(*(char **)(s + 0x120) + 0x14) - *(float *)(obj + 0x14)), angles[2]);
    elevation = func_00282E80(*(char **)(s + 0x120) + 0x10, obj + 0x10);
    elevation = func_00283C80(func_00283248(elevation,
        *(float *)(*(char **)(s + 0x120) + 0x18) - *(float *)(obj + 0x18)), 0.0f);
    if (angle <= limit && elevation <= limit)
        *(int *)(s + 0x104) = 1;
    if (check) {
        qcopy(sphere, obj + 0x10);
        sphere[3] = 0.1f;
        if (func_00283DB8(sphere, 256.0f) == -1)
            return;
    }
    *(int *)(s + 0x108) = 1;
}

extern void func_3065F8(int);

struct S_L05_0037BB28 {
    char pad0[0x10];
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
};

void func_L05_0037BB28(char *object)
{
    struct S_L05_0037BB28 *p = (struct S_L05_0037BB28 *)func_379CA0(object);

    if (p == 0)
        return;
    func_3065F8((int)p);
    p->f20 = -1;
    p->f1C = -1;
    p->f14 = 0;
    p->f18 = -1;
    p->f10 = 0;
}

INCLUDE_ASM("asm/levels", func_L05_0037BB78);

int func_L05_0037BB90(char *obj)
{
    int *p = (int *)func_002ED688(obj);

    if (p == 0)
        return 0;
    return p[5];
}

int func_L05_0037BBB8(char *obj)
{
    int *p = (int *)func_002ED688(obj);

    if (p == 0)
        return 0;
    if (p[5] == 0 && p[4] == 0)
        return 0;
    return 1;
}

void func_L05_0037BE98(char *obj)
{
    int *p = (int *)func_002ED688(obj);
    char *child;
    int *q;

    if (p == 0)
        return;
    if (func_L05_0037BB90(obj) != 0)
        func_L05_0037BD40(obj);
    child = (char *)p[4];
    q = (int *)func_002ED688(child);
    q[6] = q[6] - 1;
    func_L05_0037BB28(obj);
    if (q[6] < D_L05_00221D28)
        func_L05_0037BC08(child);
    else
        func_L05_0037BF48(child);
}

/* func_L05_0037BF48 is in L05_0037BF48.c. */

/* func_L05_0037C160 is in L05_0037C160.c. */

void func_L05_0037CDD8(char *obj, int value)
{
    int *p = (int *)func_002ED688(obj);

    if (p != 0)
        *(int *)((char *)p + 0x114) = value;
}


int func_L05_0037CEB8(char *obj)
{
    int *p = (int *)func_002ED688(obj);

    if (p == 0)
        return 0;
    return *(int *)((char *)p + 0x114);
}

/* func_L05_0037CEE0 is in L05_0037CEE0-g8.c. */


struct S_L05_002A1800 {
    char pad0[0xC];
    int f0C;
    int f10;
    int f14;
    char pad1[0x10];
};

extern struct S_L05_002A1800 D_L05_002A1800[];

extern int func_002ED8A0(int);

void func_L05_0037D6E8(void)
{
    int i;

    for (i = 0; i < 15; i++)
        D_L05_002A1800[i].f14 = D_L05_002A1800[i].f0C;
    D_L05_002A1800[7].f14 = D_L05_002A1800[7].f0C;
    D_L05_002A1800[13].f14 = D_L05_002A1800[13].f0C;
    i = func_002ED8A0(6);
    D_L05_002A1800[i].f14 = D_L05_002A1800[i].f10;
}



/* Emits count pairs of particles at position, jittering it each time; each pair drifts at a random
   angle around the flattened direction from position to the camera, and rises at a random speed. */
void func_L05_0037DA58(float *position, int count, int color, int duration)
{
    float velocity[4], point[4], direction[4], axis[4], half[4];
    float size, angle;
    int sign, i;
    char *particle;
    *(Quad37DA58 *)axis = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    func_00282CF0(direction, D_L05_001B96C0, position);
    func_00282F20(half, direction, 0.5f);
    direction[2] = 0;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (!sign) --sign;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        func_00282F20(velocity, velocity, func_002A7878(0.05f, 3.0f) * (1.0f/60.0f));
        velocity[2] = func_002A7878(1.0f, 5.0f) * (1.0f/60.0f);
        func_00282CC0(point, position, half);
        position[0] += func_002A78D8(0, 0.15f);
        position[1] += func_002A78D8(0, 0.15f);
        position[2] += func_002A78D8(0, 0.15f);
        particle = func_002C2210(position, duration, size * 0.1f, size, color, 0, sign, velocity, 0, 0.002f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
        particle = func_002C2210(position, duration, size * 0.07f, size * 0.7f, 0x7f7f7f7f, 1, -sign, velocity, 0, 0.002f);
        if (particle) {
            particle[2] = D_L05_001FF240[0x61][6];
            particle[9] = func_00283CF0(4.0f) + 0x70;
        }
    }
}

/* func_L05_003979B0 is in L05_003979B0-g8.c. */

/* func_L05_00397B30 is in L05_0037B6D0-g8.c. */

/* func_L05_00397F48 is in L05_00397F48-g8.c. */

/* Walks the twenty-four records, and for each one the object owns updates it and, while it is
   not active, lays the three colours over its vector. */
void func_L05_00398018(char *arg0)
{
    int i;
    for (i = 0; i < 24; i++) {
        Record233560 *rec = &D_L05_00233560[i];
        float *pos = &rec->f[12];
        if (rec->owner == arg0) {
            func_L00_003F26C8(arg0, (char *)rec);
            if (rec->active == 0) {
                func_00281EB8(pos, 0x31, 0x3F0000FF, 1, func_002A7878(0.065f, 0.1f) * 5.0f, 1.25f, 0.0f);
                func_00281EB8(pos, 0x31, 0x5F7F7F7F, 1, func_002A7878(0.0325f, 0.06f) * 5.0f, 1.24f, 0.0f);
                func_00281EB8(pos, 0xB, 0x1000003F, 1, func_002A7878(0.07f, 0.15f) * 5.0f, 1.23f, 0.0f);
            }
        }
    }
}


/* Walks the twenty-four records: for each one the object owns, jitters its position, moves it to
   the object carrying its offset along, steps its six angles (faster while active), rebuilds its two
   vectors and interpolates between position and end; both timers then retire the record. */
void func_L05_00398618(char *obj)
{
    float delta[4] __attribute__((aligned(16)));
    int i;
    char *state = *(char **)(obj + 0x68);
    for (i = 0; i < 24; i++) {
        Record233560 *r = &D_L05_00233560[i];
        if (r->owner == obj) {
            Record233560 *p = r;
            float *end = &p->f[16];
            float *pos = &p->f[8];
            p->f[8] += func_002A7878(-0.1f, 0.1f);
            p->f[9] += func_002A7878(-0.1f, 0.1f);
            p->f[10] += func_002A7878(-0.1f, 0.1f);
            func_00282CF0(delta, end, pos);
            qcopy(pos, obj + 0x10);
            func_00282CC0(end, pos, delta);
            if (p->active) {
                p->f[20] = func_00283B98(p->f[20], p->f[23] * 100.0f);
                p->f[21] = func_00283B98(p->f[21], p->f[24] * 100.0f);
                p->f[22] = func_00283B98(p->f[22], p->f[25] * 100.0f);
                p->f[29] = func_00283B98(p->f[29], p->f[32] * 100.0f);
                p->f[30] = func_00283B98(p->f[30], p->f[33] * 100.0f);
                p->f[31] = func_00283B98(p->f[31], p->f[34] * 100.0f);
            } else {
                p->f[20] = func_00283B98(p->f[20], p->f[23] * 50.0f);
                p->f[21] = func_00283B98(p->f[21], p->f[24] * 50.0f);
                p->f[22] = func_00283B98(p->f[22], p->f[25] * 50.0f);
                p->f[29] = func_00283B98(p->f[29], p->f[32] * 50.0f);
                p->f[30] = func_00283B98(p->f[30], p->f[33] * 50.0f);
                p->f[31] = func_00283B98(p->f[31], p->f[34] * 50.0f);
            }
            p->f[0] = func_00283180(p->f[20]) * p->f[26];
            p->f[1] = func_00283198(p->f[21]) * p->f[27];
            p->f[2] = -func_00283198(p->f[22]) * p->f[28];
            p->f[4] = func_00283180(p->f[29]) * p->f[35];
            p->f[5] = func_00283198(p->f[30]) * p->f[36];
            p->f[6] = -func_00283198(p->f[31]) * p->f[37];
            if (*(int *)(state + 0x24))
                func_00282D08(&p->f[12], &p->f[8], &p->f[16], 0.55f);
            else
                func_00282D08(&p->f[12], &p->f[8], &p->f[16], 0.4f);
            if (func_00282948(&p->active)) {
                if (p->dying == 0) p->dying = 1;
                if (func_00282948(&p->timer)) p->owner = 0;
            }
        }
    }
}

/* func_L05_00398A38 is in L05_00398A38.c. */

/* func_L05_00398F18 is in L05_00398F18.c. */

void func_L05_00399268(char *obj)
{
    float pos[4];
    float vel[4];
    ParticleColors99268 colors;
    char *s = *(char **)(obj + 0x68);
    int i, j, k, sign;
    float angle;
    char *p, *d;

    for (i = 0; i < *(int *)(s + 0x20); i++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.6f, 1.0f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.06f, 0.1f);
        func_352B28(pos, vel, life, 0x102FFF, type, 255, 0, 1, scale * 210000.0f, scale * 105000.0f, 0.0019444444915279746f);
    }

    for (j = 0; j < *(int *)(s + 0x24); j++) {
        int type, life;
        float scale;

        type = func_307778(func_332BB0(2.0f, 5.0f));
        life = func_332AF8(30, 50);
        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.1f) * *(float *)(s + 0x14);
        scale = func_332B50(0.75f, 1.5f) * *(float *)(s + 0x14);
        func_332C60(vel, 0.5f, 0.8f);
        func_352B28(pos, vel, life, 0x8FFF, type, 127, 127, 5, scale * 210000.0f, *(float *)(s + 0x14) * 2100.0f, 0.004055555909872055f);
    }

    angle = func_306CD0(D_L05_001B9580.pos[0] - *(float *)(obj + 0x10), D_L05_001B9580.pos[1] - *(float *)(obj + 0x14));
    sign = 1;
    for (k = 0; (float)k < (float)*(int *)(s + 0x2C) * 3.0f + (float)(*(int *)(s + 0x3C) * 10); k++) {
        float scale, a, b;

        pos[0] = *(float *)(obj + 0x10) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        sign = -sign;
        pos[1] = *(float *)(obj + 0x14) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        pos[2] = *(float *)(obj + 0x18) + func_332BB0(0.0f, 0.5f) * *(float *)(s + 0x14);
        scale = func_332B50(0.01666666753590107f, 0.02500000223517418f) * *(float *)(s + 0x14);
        a = func_332BB0(0.0f, 1.396263599395752f);
        b = func_332BB0(0.0f, 1.5707964897155762f);
        func_33B330(vel, scale, func_307620(angle, b), a);
        p = func_347040(pos, sign, vel, *(int *)(s + 0x3C) ? 0xD10572 : 0x5A182, 0.0f, 1.0f, 1.01f, *(float *)(s + 0x14) * 31500.001953125f, 0);
        colors = D_L05_001AEC00;
        if (p) {
            d = p + 0x20;
            {
                int index = func_001163B0() % 2;
                p[3] = colors.v[index];
            }
            if (*(int *)(s + 0x3C))
                *(short *)(p + 0xA) = func_332AF8(120, 150);
            else
                *(short *)(p + 0xA) = func_332AF8(90, 120);
            p[9] = func_307778(4.0f) + 64;
            *(int *)(d + 4) = 3;
            *(float *)(d + 0x1C) = func_307768(func_332AF8(1, 10));
            d[0xA] = func_332AF8(64, 128);
            d[0xB] = p[0xA];
            if (func_332AB8(4) != 0)
                p[2] = D_L05_001FF240[34][0];
            else
                p[2] = D_L05_001FF240[105][0];
        }
    }
}

/* func_L05_003CD1A8 is in L05_003CD1A8-g8.c. */


void func_L05_003CD4C0(char *object)
{
    char *state = *(char **)(object + 0x68);
    float *f = (float *)state;
    int *w;
    int i;
    int j;
    int v;

    for (i = 3; i >= 0; i--)
        *f++ = (float)func_332AB8(0xFF);
    *(float *)(state + 0x10) = -1.0f;
    *(float *)(state + 0x14) = -2.25f;
    *(float *)(state + 0x18) = 1.25f;
    *(float *)(state + 0x1C) = 2.5f;
    j = 3;
    w = (int *)(state + 0x2C);
    v = 0xFF;
    for (; j >= 0; j--) {
        *w = v;
        w = (int *)((char *)w - 4);
        v -= 0x40;
    }
    *(float *)(state + 0x30) = 2.8f;
    *(float *)(state + 0x34) = 3.5f;
    *(float *)(state + 0x3C) = 2.8f;
    *(float *)(state + 0x38) = 3.5f;
}


/* func_L05_003CEFA0 is in L05_003CEFA0.c. */

/* func_L05_003CF040 is in L05_003CF040-g8.c. */

/* func_L05_003CF350 is in L05_003CF350-g8.c. */

/* func_L05_003CFAB8 is in L05_0037B6D0-g8.c. */

int func_L05_003CFC28(int a0)
{
    if (a0 == 0x971)
        return 4;
    return a0 - 0x953;
}

/* func_L05_003CFC48 is in L05_003CFC48-g8.c. */

/* func_L05_003CFCF0 is in L05_003CFCF0-g8.c. */

/* func_L05_003CFF90 is in L05_003CFF90.c. */

extern int D_L05_00221D10[];

extern char *D_L05_001B2614 __attribute__((sda));

extern void func_37AEC0(char *, int);

extern float func_332C18(void);

extern void func_33B330(void *, float, float, float);

/* Gives the object its reach: the table's entry for the object's id picks the record, and
 * the record takes the cone the object was given. */
void func_L05_003D0320(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 1;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(int *)(sub + 0x1BC) = -1;
    *(int *)(sub + 0x1C0) = -1;
    *(float *)(sub + 0x180) = 1.0f;
    *(int *)(sub + 0x1B8) = 0;
    *(float *)(obj + 0x2C) = 0.06f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}


/* func_L05_003D0728 is in the sibling unit L05_003D0728-g8.c. */

void func_L05_003D08C0(float *a0, char *a1)
{
    a0[0] = func_332B50(-1.0f, 1.0f);
    a0[1] = func_332B50(-1.0f, 1.0f);
    a0[2] = func_332B50(-1.0f, 1.0f);
    a0[3] = 1.0f;
    func_306AD8(a0, a0, a1);
    func_306630(a0, a0, a1 + 0x30);
}

/* func_L05_003D0960 is in L05_003D0960-g8.c. */

/* func_L05_003D0B20 is in L05_003D0B20-g8.c. */

extern void func_002AFFD8(char *a0, char *a1, int a2);

extern float *func_002AB1F0(char *a0);

extern void func_00282D30(void *a0, void *a1, float a2);

extern void func_00282CC0(void *a0, void *a1, void *a2);

extern void func_L05_003D1148(void *a0, void *a1, void *a2, void *a3,
                              float f0, float f1, float f2, void *a4);

/* Builds the pair of vectors the timer wants: the object's own matrix, scaled by the value the
 * looked-up sub-object holds, and that scaled matrix combined with the sub-object's table. */
void func_L05_003D1058(char *a0, char *a1, char *a2, char *a3, float f0, float f1, float f2)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float *p;

    if (a2 == 0)
        return;
    if (*(unsigned char *)(a2 + 0x20) == 0xFE)
        return;
    if (*(unsigned char *)(a2 + 0x20) == 0xFD)
        return;
    func_002AFFD8(a0, (char *)v0, 1);
    p = func_002AB1F0(a2);
    func_00282D30(v1, v0, *(float *)((char *)p + 0x10));
    func_00282CC0(v2, (float *)(a2 + 0x10), v1);
    func_L05_003D1148(a0, a1, v2, a3, f0, f1, f2, v0);
}

extern void func_00282CF0(void *out, void *a, void *b);

extern float func_00282DF0(void *v);

extern void func_00282DD8(void *out, void *a, void *b);

extern float func_00282DB0(void *a, void *b);

extern void func_00282F20(void *out, void *in, float scale);

extern void func_00282D30(void *out, void *in, float scale);

extern float func_00282C48(float x);

extern float func_002831B0(float x);

extern float func_00283198(float x);

extern float func_00283180(float x);

extern void func_002ACF68(void *out, void *in, void *tmp, int mode, float value);

extern void func_002ACDE8(void *out, void *in, void *v);

extern float func_002703B0(void *obj, float p1, float p2, float p3, float p4, float p5);

/* Rotates an object onto a vector: builds the axis vectors, then hands the object a
   quaternion-like value scaled by the angle it makes with the target. */
void func_L05_003D1148(void *a0, void *a1, void *a2, void *a3,
                      float f0, float f1, float f2, void *a4)
{
    float v0[4];
    float v1[4];
    float v2[4];
    float len;
    float dot;
    float prod;
    float ang;
    float diff;
    float r;

    func_00282CF0(v0, a2, a0);
    len = func_00282DF0(v0);
    if (len == 0.0f)
        return;
    if (len < 1.5f) {
        func_002ACF68(a1, a1, v0, 0, 0.5f);
        return;
    }
    func_00282DD8(v1, v0, a1);
    dot = func_00282DB0(a1, v0);
    prod = func_00282DF0(a1) * func_00282DF0(v0);
    if (prod == 0.0f)
        return;
    ang = func_002831B0(dot / prod);
    diff = 1.5707964f - ang;
    if (func_00282C48(diff) > 2.879793643951416f) {
        func_00282DD8(v2, a1, a4);
        func_00282DD8(v1, v2, a1);
    }
    func_00282F20(v1, v1, 1.0f);
    r = func_002703B0(a3, 0.0f, diff * 0.5f, f0, f1, f2);
    func_00282D30(v1, v1, func_00283198(r));
    v1[3] = func_00283180(r);
    func_002ACDE8(a1, a1, v1);
}

/* func_L05_003D1368 is in L05_003D1368-g8.c. */

/* func_L05_003D15E8 is in L05_003D15E8.c. */

void func_L05_003D18E0(char *obj)
{
    char *sub = *(char **)(obj + 0x68);
    char *table;
    float a, b, c;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = D_L05_001B2614 + D_L05_00221D10[0] * 128;
    *(float *)(sub + 0x180) = 5.0f;
    *(int *)(sub + 0x2F0) = -1;
    *(int *)(sub + 0x2F4) = -1;
    *(int *)(sub + 0x268) = 0;
    *(float *)(obj + 0x2C) = 0.04f;
    a = func_332B50(0.0f, *(float *)table);
    b = func_332C18();
    c = func_332C18();
    func_33B330(obj + 0x10, a, b, c);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
    *(int *)(sub + 0x26C) = 0;
}



/* Spawns the object's effect after three guards, then runs the timer. */
void func_L05_003D19F0(char *object)
{
    char *s1 = *(char **)(object + 0x68);
    char *r;

    r = func_379CA0(object);
    if (r == 0)
        return;
    if (*(int *)(r + 0x120) == 0)
        return;
    if (*(int *)(s1 + 0x268) != 0)
        return;
    func_379FA0(object, 0x60000090, 1, 0, 0.6f, 2.0f, 1.0f, 1.3f, 0, -1, 0);
    if (func_332AB8(3) == 0)
        func_3719A8(0, 0, object, 0x97C);
    *(int *)(s1 + 0x268) = 0x3C;
}

/* func_L05_003D1AB8 is in L05_003D1AB8-g8.c. */



/* func_L05_003D2048 is in L05_003D2048-g8.c. */

/* func_L05_003D2618 is in L05_003D2618-g8.c. */

