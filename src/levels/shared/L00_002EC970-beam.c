/* func_L00_002EC970 (DrawTaperedBeam): draws two beams of quads, an inner and an outer one, along a
 * path of points, narrowing by 0.75 per segment. A unit of its own for -frac2-zero-ti-por.
 *
 * Two source details decide the four spill slots 0x19C..0x1A8, which gcse's PRE numbers in hash
 * bucket order (bucket = hash % (insn count / 2 | 1)):
 * - the parameter is the loop index and `count` keeps its value, so count has a later pseudo;
 * - inside the loop the beams are reached through `b` and `c`, so the copies that shift the
 *   points take them without an extra register copy.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
typedef struct {
    Vector4 point[4];
    unsigned int color[4];
    float uv[8];
    unsigned long tag, tex, alpha, test;
} Beam;

extern void func_00281DE8(void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern float func_00283CE0(int);
extern void func_00280B90(void *, void *, int);
extern char D_L00_001B8DC0[];

void func_L00_002EC970(Vector4 *start, Vector4 *points, unsigned int color, int i, float u0, float du)
{
    int count = i;
    Vector4 origin;
    Vector4 *pos = &origin;
    Beam first, second;
    Vector4 basis[4], nearSize, farSize;
    float width;

    pos->bits = start->bits;
    func_00281DE8(&first, 23, 1, 0x80);
    func_00281DE8(&second, 23, 1, 0x80);
    nearSize.bits = 0;
    farSize.bits = 0;
    first.color[0] = first.color[1] = color | 0x7F000000;
    second.color[0] = second.color[1] = color | 0x3F000000;
    nearSize.f[3] = 1;
    farSize.f[3] = 1;
    width = func_002A7878(0.2f, 0.45f);
    nearSize.f[2] = width;
    farSize.f[2] = width * 1.5f;
    if (!(func_001163B0() & 1)) {
        first.uv[0] = u0; first.uv[1] = 0; first.uv[2] = u0; first.uv[3] = 1;
        first.uv[4] = du + u0; first.uv[5] = 0; first.uv[6] = du + u0; first.uv[7] = 1;
        second.uv[0] = u0; second.uv[1] = 0; second.uv[2] = u0; second.uv[3] = 1;
        second.uv[4] = du + u0; second.uv[5] = 0; second.uv[6] = du + u0; second.uv[7] = 1;
    } else {
        first.uv[0] = u0; first.uv[1] = 1; first.uv[2] = u0; first.uv[3] = 0;
        first.uv[4] = du + u0; first.uv[5] = 1; first.uv[6] = du + u0; first.uv[7] = 0;
        second.uv[0] = u0; second.uv[1] = 1; second.uv[2] = u0; second.uv[3] = 0;
        second.uv[4] = du + u0; second.uv[5] = 1; second.uv[6] = du + u0; second.uv[7] = 0;
    }
    func_00282CF0(&basis[0], points, pos); func_00282F20(&basis[0], &basis[0], 1);
    func_00282CF0(&basis[1], D_L00_001B8DC0, pos); func_00282DD8(&basis[2], &basis[1], &basis[0]);
    func_00282F20(&basis[2], &basis[2], 1); func_00282DD8(&basis[1], &basis[0], &basis[2]);
    qcopy(&basis[3], pos);
    qcopy(&first.point[0], &nearSize); qcopy(&second.point[0], &farSize);
    func_00282D30(&first.point[1], &first, -1); func_00282D30(&second.point[1], &second, -1);
    func_002830C0(&first, &first, basis); func_002830C0(&first.point[1], &first.point[1], basis);
    func_002830C0(&second, &second, basis); func_002830C0(&second.point[1], &second.point[1], basis);
    for (i = 0; i < count - 1; i++) {
        float u, v;
        Vector4 *to = &points[i + 1], *from = &points[i];
        Beam *b = &first, *c = &second;
        func_00282CF0(&basis[0], to, from); func_00282F20(&basis[0], &basis[0], 1);
        func_00282CF0(&basis[1], D_L00_001B8DC0, from); func_00282DD8(&basis[2], &basis[1], &basis[0]);
        func_00282F20(&basis[2], &basis[2], 1); func_00282DD8(&basis[1], &basis[0], &basis[2]);
        qcopy(&basis[3], from);
        nearSize.f[2] *= 0.75f; farSize.f[2] = nearSize.f[2] * 1.5f;
        qcopy(&b->point[2], &nearSize); qcopy(&c->point[2], &farSize);
        func_00282D30(&b->point[3], &b->point[2], -1);
        func_00282D30(&c->point[3], &c->point[2], -1);
        func_002830C0(&b->point[2], &b->point[2], basis); func_002830C0(&b->point[3], &b->point[3], basis);
        func_002830C0(&c->point[2], &c->point[2], basis); func_002830C0(&c->point[3], &c->point[3], basis);
        first.color[2] = first.color[3] = color | 0x7F000000;
        second.color[2] = second.color[3] = color | 0x3F000000;
        u = du * func_00283CE0(i + 1);
        v = u + du;
        if (u >= 1.0f) { u -= 1.0f; v -= 1.0f; }
        first.uv[0] = u + u0; first.uv[2] = u + u0; first.uv[4] = v + u0; first.uv[6] = v + u0;
        second.uv[0] = u + u0; second.uv[4] = v + u0;
        second.uv[2] = u + u0; second.uv[6] = v + u0;
        func_00280B90(b, 0, 0); func_00280B90(c, 0, 0);
        qcopy(&b->point[0], &b->point[2]); qcopy(&b->point[1], &b->point[3]);
        qcopy(&c->point[0], &c->point[2]); qcopy(&c->point[1], &c->point[3]);
    }
    {
        float u, v;
        qcopy(&basis[3], &points[count - 1]);
        nearSize.f[2] *= 0.75f; farSize.f[2] = nearSize.f[2] * 1.5f;
        qcopy(&first.point[2], &nearSize); qcopy(&second.point[2], &farSize);
        func_00282D30(&first.point[3], &first.point[2], -1); func_00282D30(&second.point[3], &second.point[2], -1);
        func_002830C0(&first.point[2], &first.point[2], basis); func_002830C0(&first.point[3], &first.point[3], basis);
        func_002830C0(&second.point[2], &second.point[2], basis); func_002830C0(&second.point[3], &second.point[3], basis);
        second.color[2] = second.color[3] = first.color[2] = first.color[3] = color;
        u = du * func_00283CE0(i + 1);
        v = u + du;
        if (u >= 1.0f) { u -= 1.0f; v -= 1.0f; }
        first.uv[0] = u + u0; first.uv[2] = u + u0; first.uv[4] = v + u0; first.uv[6] = v + u0;
        second.uv[0] = u + u0; second.uv[4] = v + u0;
        second.uv[6] = v + u0; second.uv[2] = u + u0;
        func_00280B90(&first, 0, 0); func_00280B90(&second, 0, 0);
    }
}

