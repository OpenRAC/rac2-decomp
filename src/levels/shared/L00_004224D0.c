#include "include_asm.h"
#include "common.h"

#ifndef RAC2_T_V4_F0FBA48D3
#define RAC2_T_V4_F0FBA48D3
typedef int V4_F0fba48d3 __attribute__((mode(TI)));
#endif

extern void func_00282CF0_2(void *b, void *c, void *d);

extern void func_00282F20(void *dst, void *src, float x);

extern void func_00282CC0(void *c, void *c2, void *s);

extern void func_00282CF0_2(void *b, void *c, void *p);

extern void func_00282F20(void *dst, void *src, float y);

extern void func_00282CC0(void *b, void *p, void *s);

extern void func_00282CF0_2(void *b, void *s, void *e);

extern char D_L00_001BF220_1[];

extern void func_00282CF0_7(char *local, char *data);

extern float func_00282DB0_1(char *local, char *p);

extern float D_L00_001A8900 __attribute__((sda));

extern void func_00282CF0_4(float *out, char *a, char *b);

extern void func_00282D08(float *out, char *a, char *b, float k);

extern float func_00282DF0(void *v);

extern void func_00282F20_3(float *out, float *in, float k);

extern char *D_L00_001BB040;

extern void func_00282CF0_8(char *dst, char *a, char *b);

extern void func_L00_00424EB0(char *a0, char *a1, float t);

extern float func_L00_00424C90(char *a0, char *a1, float t);

INCLUDE_ASM("asm/levels", func_L00_004224D0);

typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector row[3]; } Matrix;
typedef struct {
    Vector up, scaled, delta, endpoint, transformed, offset;
    Matrix basis;
    Vector difference;
} CameraScratch;
extern char *D_L00_001B8E10;
extern char D_00189E20[];
extern int D_L00_001B184C MACRO_ADDR;
extern Vector D_L00_001BF220;
extern Vector D_L00_001B8E50;
extern void func_00283678(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_002761F8(void *, void *, unsigned int, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

void func_L00_00423038(int reposition)
{
    CameraScratch scratch;
    char *object = D_L00_001B8E10;
    char *state = *(char **)(object + 0x70);
    char *movement = state + 0x160;
    char *transform = state + 0x60;
    char *position;
    char *target;
    float length;
    if (reposition) {
        scratch.offset.x = -*(float *)(movement + 0x2C);
        scratch.offset.y = 0.0f;
        scratch.offset.z = *(float *)(movement + 0x30);
        scratch.offset.w = 0.0f;
        func_00283678(&scratch.basis, D_00189E20);
        func_00283098(&scratch.transformed, &scratch.offset, *(char **)(transform + 0xC0) + 0xC0);
        target = object + 0x30;
        func_00282CC0(target, transform, &scratch.transformed);
        func_00282D30(&scratch.scaled, *(char **)(transform + 0xC0) + 0xE0, *(float *)(transform + 0xB0));
        func_00282CC0(&scratch.endpoint, transform, &scratch.scaled);
        if (func_002761F8(&scratch.endpoint, target, D_L00_001B184C, *(char **)(D_00189E20 + 0x2290), 0)) {
            func_00282CF0(&scratch.difference, &D_L00_001BF220, &scratch.endpoint);
            length = func_00282DF0(&scratch.difference);
            if (length == 0.0f) {
                qcopy(target, &scratch.endpoint);
            } else {
                func_00282D30(&scratch.difference, &scratch.difference, (length - 0.5f) / length);
                func_00282CC0(target, &scratch.endpoint, &scratch.difference);
            }
        }
    }
    position = object + 0x30;
    {
        float *previous = (float *)(object + 0x64);
        previous[0] = *(float *)position;
        previous[1] = *(float *)(position + 4);
        previous[2] = *(float *)(position + 8);
    }
    qcopy(&scratch.up, &D_L00_001B8E50);
    func_00282F20(&scratch.scaled, &scratch.up, *(float *)(transform + 0xB0));
    func_00282CC0(&scratch.endpoint, &scratch.scaled, transform);
    func_00282CF0(&scratch.delta, &scratch.endpoint, position);
    func_00282F20(object, &scratch.delta, 1.0f);
    qcopy(object + 0x20, &scratch.up);
    func_00282DD8(object + 0x10, object, object + 0x20);
    func_00282F20(object + 0x10, object + 0x10, 1.0f);
    func_00282DD8(object + 0x20, object + 0x10, object);
    qcopy(object + 0x40, object);
}

/* func_L00_00423038 is in a separate compilation unit. */

INCLUDE_ASM("asm/levels", func_L00_00423290);

/* func_L00_004233F8 is in L00_004233F8-g8.c. */


/* func_L00_004237C8 is in a separate compilation unit. */

/* func_L00_004239A8 is in L00_004239A8-g8.c. */

int func_L00_00423BB0(void)
{
    char buf[80];

    return 0;
}

/* reads a pointer from the field at +112 of the first argument, advances it by 176, then runs three 16-byte records and two float parameters through a fixed sequence of seven calls that alternate between three helpers */
void func_L00_00423BC0(char *a0, void *a1, void *a2, void *a3,
                                      void *a4, float t0, float t1)
{
    V4_F0fba48d3 b0, b1, b2, b3;
    void *p = (void *)(*(int *)(a0 + 112));

    p = (void *)((int)p + 176);

    func_00282CF0_2(&b0, a2, a3);
    func_00282F20(&b1, &b0, t0);
    func_00282CC0(a2, a2, &b1);
    func_00282CF0_2(&b2, a2, p);
    func_00282F20(&b2, &b2, t1);
    func_00282CC0(&b3, p, &b2);
    func_00282CF0_2(a1, &b3, a4);
}

/* func_L00_00423CA8 is in L00_00423CA8-g8.c. */

/* Returns 0 unless the second argument equals 1; then it takes a pointer out of the first argument's field at +112, adds 352 to it, passes a 16-byte stack buffer and a data symbol to one routine, passes the same buffer and the shifted pointer to a second routine that returns a float, and returns 1 only when that float is below zero. */
int func_L00_00424070(int a0, int a1)
{
    char local[16];
    int s0;
    int r;

    if (a1 != 1) {
        r = 0;
    } else {
        s0 = *(int *)(a0 + 112) + 352;
        func_00282CF0_7(local, D_L00_001BF220_1);
        r = func_00282DB0_1(local, (char *)s0) < 0.0f ? 1 : 0;
    }
    return r;
}

/* func_L00_004240D8 is in L00_004240D8-g8-dbg.c. */

INCLUDE_ASM("asm/levels", func_L00_004243C0);

extern char *D_L00_001B8E10;

int func_L00_00424940(int a0)
{
    char *p = D_L00_001B8E10;
    char *q;

    if (*(short *)(p + 134) != 0) {
        return -1;
    }
    q = *(char **)(p + 112);
    if (*(int *)(q + 576) == a0) {
        *(int *)(q + 576) = 0;
        return 1;
    }
    return 0;
}

/* func_L00_00424978 is matched in L00_00424978.c (built with -mno-split-addresses). */

void func_L00_00424A08(int a0, float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 352;

        *(short *)(r + 60) = 1;
        *(float *)(r + 72) = b;
        *(float *)(r + 64) = a;
        if (a0) {
            *(float *)(r + 88) = a;
        }
    }
}

/* Stores the two incoming floats and a flag into the block at +352 of the owner object. */
void func_L00_00424A50(float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 352;

        *(short *)(r + 62) = 1;
        *(float *)(r + 76) = a;
        *(float *)(r + 84) = b;
    }
}

/* Sets a flag and a value on the block at +96; the value is offset by a shared float when a0 is set. */
void func_L00_00424A88(int a0, float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 0x60;

        *(short *)(r + 0xDA) = 1;
        *(float *)(r + 0xB8) = b;
        if (a0) {
            *(float *)(r + 0xB4) = *(float *)(D_L00_001BB040 + 0x110) + a;
        } else {
            *(float *)(r + 0xB4) = a;
        }
    }
}

/* Stores one float and two scaled by an arcsecond-sized constant into the block at +32. */
void func_L00_00424AD8(float a, float b, float c)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 32;

        *(float *)(r + 44) = a;
        *(float *)(r + 52) = b * 4.848137450608192e-06f;
        *(float *)(r + 56) = c * 4.848137450608192e-06f;
    }
}

void func_L00_00424B20(float t)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        *(float *)(q + 484) = t;
    }
}

void func_L00_00424B48(int t)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        *(short *)(q + 16) = (short)t;
    }
}

/* Stores each incoming float only when it is not zero. */
void func_L00_00424B70(float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 0x60;

        if (a != 0.0f) {
            *(float *)(r + 0xDC) = a;
        }
        if (b != 0.0f) {
            *(float *)(r + 0xE0) = b;
        }
    }
}

INCLUDE_ASM("asm/levels", func_L00_00424BB8);

void func_L00_00424C00(void)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        *(short *)(q + 582) = 1;
    }
}

void func_L00_00424C28(void)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        *(char *)(q + 310) = 1;
    }
}

void func_L00_00424C60(void)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);
        char *r = q + 448;

        *(int *)(r + 16) |= 3;
    }
}

extern char D_L00_001B8E20[];
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_002831B0(float);
extern float func_00283BE0(float, float);
extern float func_00282C48(float);
extern float func_002A7AA8(float, float, float, float, float);

float func_L00_00424C90(char *object, char *vector, float threshold)
{
    float temporary[4] __attribute__((aligned(16)));
    float first[4] __attribute__((aligned(16)));
    float second[4] __attribute__((aligned(16)));
    float cross[4] __attribute__((aligned(16)));
    char *state = *(char **)(object + 0x70);
    char *output = state + 0x1C0;
    char *direction = state + 0x160;
    char *camera = D_L00_001B8E20;
    char *up = camera + 0x20;
    float dot;
    float length;
    float angle;
    float signed_angle = 0.0f;
    float sign;
    float factor;
    func_00282D30(temporary, up, func_00282DB0(vector, up));
    func_00282CF0(first, vector, temporary);
    func_00282D30(temporary, up, func_00282DB0(direction, up));
    func_00282CF0(second, direction, temporary);
    dot = func_00282DB0(first, second);
    length = func_00282DF0(first);
    if (length == 0.0f) return 0.0f;
    length *= func_00282DF0(second);
    if (length == 0.0f) return 0.0f;
    angle = 1.57079632679f - func_002831B0(dot / length);
    sign = -1.0f;
    func_00282DD8(cross, first, up);
    if (func_00282DB0(cross, second) >= 0.0f) sign = 1.0f;
    signed_angle = func_00283BE0(3.14159265359f, angle);
    if (threshold != 0.0f && func_00282C48(signed_angle) > threshold) return signed_angle;
    factor = func_002A7AA8(-1.0f, 0.0f, 1.0f, 0.0f, signed_angle * 0.63661975f);
    if (factor > 1.0f) factor = 1.0f;
    *(float *)(output + 0x1C) = factor * sign;
    return signed_angle;
}

/* Builds a vector from a1 and the +96 source block, then feeds it to the inner routine. */
void func_L00_00424EB0(char *a0, char *a1, float t)
{
    char local[16];

    func_00282CF0_8(local, a1, *(char **)(a0 + 112) + 96);
    func_L00_00424C90(a0, local, t);
}

/* Stores a non-zero value, then hands it to the inner routine. */
void func_L00_00424F00(char *a0, float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0 && a != 0.0f) {
        char *q = *(char **)(p + 112);

        *(float *)(q + 468) = a;
        func_L00_00424C90(p, a0, b);
    }
}

/* Stores the value, then builds a vector and hands it to the inner routine. */
void func_L00_00424F58(char *a0, float a, float b)
{
    char *p = D_L00_001B8E10;

    if (*(short *)(p + 134) == 0) {
        char *q = *(char **)(p + 112);

        *(float *)(q + 468) = a;
        func_L00_00424EB0(p, a0, b);
    }
}

INCLUDE_ASM("asm/levels", func_L00_00424F98);

/* func_L00_00425118 is in L00_00425118-g8.c. */

/* Builds three vectors from an owner block, blends the stored value toward the closest of the sampled vector length and the stored reference gap, and writes the remaining gap back. */
void func_L00_00425490(char *obj)
{
    char *p = *(char **)(obj + 112);
    char *r = p + 496;
    char *q = p + 352;
    float buf[4];
    float a, b, c;

    if (*(short *)(p + 16) <= 0) return;
    func_00282CF0_4(buf, p, p + 176);
    func_00282D08((float *)q, q, (char *)buf, D_L00_001A8900);
    a = func_00282DF0((float *)q);
    b = *(float *)(q + 44);
    if (b < a) {
        a = b;
        func_00282F20_3((float *)q, (float *)q, a);
        c = *(float *)(q + 44);
    } else {
        float d = b - *(float *)(r + 48);
        if (a < d) {
            a = d;
            func_00282F20_3((float *)q, (float *)q, a);
        }
        c = *(float *)(q + 44);
    }
    *(float *)(r + 48) = c - a;
}

/* func_L00_00425560 is in L00_004224D0-follow-g8.c. */

/* func_L00_00425A98 is in a separate compilation unit. */

/* func_L00_00425CD0 is in L00_004224D0-g8.c (-G8). */

/* Walks the 64x64 owner table and dispatches every type-5 entry of each populated block. */
/* One 0x30-byte entry of a collision-grid cell (layout as in L00_002D7940-grid.c);
 * entries of type 5 carry an index into the 0x80-byte records at D_L00_001B1F94. */
typedef struct GridCellEntry {
    unsigned char unknown_00[16];
    int type;
    int index;
    unsigned char unknown_18[24];
} GridCellEntry;

/* The grid base pointer uses the measured absolute macro-address form. */
extern char *D_L00_001B1880[] __attribute__((sda));
extern char *D_L00_001B1F94[] __attribute__((sda));

/* Visits every cell of the 64x64 collision grid and passes each type-5 entry's record to func_00282DF0. */
void func_L00_00426248(void)
{
    int y, x, k;

    for (y = 0; y < 64; y++) {
        for (x = 0; x < 64; x++) {
            int idx = y * 64 + x;
            char *base = D_L00_001B1880[0];
            int cell = ((int *)base)[idx];

            if (cell == 0) {
                continue;
            }
            cell += (int)base;
            for (k = 0; k < *(int *)cell; k++) {
                GridCellEntry *entry = (GridCellEntry *)((char *)cell + 16) + k;

                if (entry->type == 5) {
                    func_00282DF0(D_L00_001B1F94[0] + (entry->index << 7));
                }
            }
        }
    }
}
