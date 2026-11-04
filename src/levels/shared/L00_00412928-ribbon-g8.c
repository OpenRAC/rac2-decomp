#include "common.h"

/* func_L00_00413918 reads its ribbon colour and widths through $gp, hence -G8; it is built
 * with -g like the original, whose line notes give the two nops before the division. */

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;

/* A textured quad as func_00280B90 draws it. */
typedef struct {
    Vec v[4];
    unsigned color[4];
    float uv[4][2];
    long tag0, texture, tag2, tag3;
} QuadPacket;

typedef struct { Vec row[3], pos; } Frame;

extern unsigned D_L00_001B1380 __attribute__((sda));
extern float D_L00_001B1384 __attribute__((sda));
extern float D_L00_001B1388 __attribute__((sda));
extern float D_L00_001B138C __attribute__((sda));
extern int D_L00_001B13D0 __attribute__((sda));
extern char D_L00_001B8C80[];

extern long func_0027C878(int id);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float length);
extern void func_00282DD8(void *dst, void *a, void *b);
extern void func_00282D30(void *dst, void *src, float scale);
extern void func_002830C0(void *dst, void *src, void *frame);
extern void func_00280B90(void *packet, int a, int b);
extern float func_00283CE0(int value);
extern float func_002A7AA8(float a, float b, float c, float d, float t);

/* Draws a two-layer ribbon through count points, one quad per segment. */
void func_L00_00413918(char *object, Vec *points, int alpha, int alpha2, int count)
{
    QuadPacket outer, inner;
    Vec size, size2, dir;
    Frame frame;
    Vec first, second;
    Frame segment;
    char *state = *(char **)(object + 0x68);
    int i;
    float t, width;

    outer.texture = func_0027C878(0x17);
    outer.tag3 = 0x8000000048ULL;
    outer.tag2 = 0xff9000000260ULL;
    outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] =
        (D_L00_001B1380 & 0xffffff) | ((unsigned)alpha << 24);
    outer.tag0 = 0;
    inner.texture = func_0027C878(0xe);
    inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] =
        (*(unsigned *)(state + 0x24) & 0xffffff) | ((unsigned)alpha2 << 24);
    inner.tag3 = outer.tag3;
    inner.tag2 = outer.tag2;
    inner.tag0 = outer.tag0;
    inner.uv[0][0] = 1;
    inner.uv[0][1] = 0;
    inner.uv[1][0] = 1;
    inner.uv[1][1] = 1;
    inner.uv[2][0] = 0;
    inner.uv[2][1] = 0;
    inner.uv[3][0] = 0;
    inner.uv[3][1] = 1;
    outer.uv[0][0] = *(float *)(state + 0x14);
    outer.uv[0][1] = 0;
    outer.uv[1][0] = *(float *)(state + 0x14);
    outer.uv[1][1] = 1;
    outer.uv[2][0] = *(float *)(state + 0x14) + 1;
    outer.uv[2][1] = 0;
    outer.uv[3][0] = *(float *)(state + 0x14) + 1;
    outer.uv[3][1] = 1;
    size.q = 0;
    size.f[3] = 1;
    size.f[2] = D_L00_001B1388;
    size2.q = 0;
    size2.f[3] = 1;
    size2.f[2] = D_L00_001B1388 * D_L00_001B138C;

    func_00282CF0(&dir, state + 0x30, object + 0x10);
    func_00282F20(&dir, &dir, 1);
    qcopy(&frame.row[0], &dir);
    func_00282DD8(&frame.row[1], &frame.row[0], object + 0xe0);
    func_00282F20(&frame.row[1], &frame.row[1], 1);
    func_00282DD8(&frame.row[2], &frame.row[1], &frame.row[0]);
    qcopy(&frame.pos, object + 0x10);

    qcopy(&outer.v[0], &size);
    func_00282D30(&outer.v[1], &outer.v[0], -1);
    qcopy(&inner.v[0], &size2);
    func_00282D30(&inner.v[1], &inner.v[0], -1);
    func_002830C0(&first, &points[0], &frame);
    func_002830C0(&second, &points[1], &frame);
    func_00282CF0(&segment.row[0], &second, &first);
    func_00282F20(&segment.row[0], &segment.row[0], 1);
    func_00282CF0(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
    func_00282DD8(&segment.row[2], &segment.row[1], &segment.row[0]);
    func_00282F20(&segment.row[2], &segment.row[2], 1);
    func_00282DD8(&segment.row[1], &segment.row[0], &segment.row[2]);
    qcopy(&segment.pos, &first);
    func_002830C0(&outer.v[0], &outer.v[0], &segment);
    func_002830C0(&outer.v[1], &outer.v[1], &segment);
    func_002830C0(&inner.v[0], &inner.v[0], &segment);
    func_002830C0(&inner.v[1], &inner.v[1], &segment);

    for (i = 1; i < count; i++) {
        qcopy(&outer.v[2], &size);
        func_00282D30(&outer.v[3], &outer.v[2], -1);
        qcopy(&inner.v[2], &size2);
        func_00282D30(&inner.v[3], &inner.v[2], -1);
        if (i == count - 1) {
            func_002830C0(&segment.pos, &points[i], &frame);
        } else {
            func_002830C0(&first, &points[i], &frame);
            func_002830C0(&second, &points[i + 1], &frame);
            func_00282CF0(&segment.row[0], &second, &first);
            func_00282F20(&segment.row[0], &segment.row[0], 1);
            func_00282CF0(&segment.row[1], D_L00_001B8C80 + 0x140, &first);
            func_00282DD8(&segment.row[2], &segment.row[1], &segment.row[0]);
            func_00282F20(&segment.row[2], &segment.row[2], 1);
            func_00282DD8(&segment.row[1], &segment.row[0], &segment.row[2]);
            qcopy(&segment.pos, &first);
        }
        func_002830C0(&outer.v[2], &outer.v[2], &segment);
        func_002830C0(&outer.v[3], &outer.v[3], &segment);
        func_002830C0(&inner.v[2], &inner.v[2], &segment);
        func_002830C0(&inner.v[3], &inner.v[3], &segment);

        if (i == 1 && D_L00_001B13D0 == alpha2) {
            /* Fade the ribbon's first edge out (alpha 0) for this draw only. */
            unsigned color, color2;

            color = outer.color[0];
            outer.color[0] = outer.color[1] = 0xffffff;
            color2 = inner.color[0];
            inner.color[0] = inner.color[1] = *(unsigned *)(state + 0x24) & 0xffffff;
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else if (i == count - 2 && D_L00_001B13D0 == alpha2) {
            /* Likewise its last edge. */
            unsigned color, color2;

            color = outer.color[2];
            outer.color[2] = outer.color[3] = 0xffffff;
            color2 = inner.color[2];
            inner.color[2] = inner.color[3] = *(unsigned *)(state + 0x24) & 0xffffff;
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
            outer.color[0] = outer.color[1] = outer.color[2] = outer.color[3] = color;
            inner.color[0] = inner.color[1] = inner.color[2] = inner.color[3] = color2;
        } else {
            func_00280B90(&outer, 0, 0);
            func_00280B90(&inner, 0, 0);
        }
        qcopy(&outer.v[0], &outer.v[2]);
        qcopy(&outer.v[1], &outer.v[3]);
        qcopy(&inner.v[0], &inner.v[2]);
        qcopy(&inner.v[1], &inner.v[3]);

        t = func_00283CE0(i);
        t /= func_00283CE0(count);
        width = func_002A7AA8(-1, 0, 1, 0, t);
        size.f[2] = D_L00_001B1388 + (D_L00_001B1384 - D_L00_001B1388) * width;
        size2.f[2] = size.f[2] * D_L00_001B138C;
        outer.uv[0][0] = *(float *)(state + 0x14);
        outer.uv[0][1] = 0;
        outer.uv[1][0] = *(float *)(state + 0x14);
        outer.uv[1][1] = 1;
        outer.uv[2][0] = *(float *)(state + 0x14) + 1;
        outer.uv[2][1] = 0;
        outer.uv[3][0] = *(float *)(state + 0x14) + 1;
        outer.uv[3][1] = 1;
    }
}
