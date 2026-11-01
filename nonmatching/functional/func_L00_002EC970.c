/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* Claude Opus 5.5 xhigh, v1776: 1652/1652 bytes, 0/27 USA v1.01 places; 12 instructions differ,
 * all of them spill-slot offsets. Everything else, including the prologue, is the retail's.
 * Profile: -O2 -G0 -ffunction-sections -frac2-zero-ti-por, in a unit of its own.
 * New: `Vector4 *pos = &origin;` set at entry. cse folds pos to $sp before the if/else join and
 * cannot after it, and gcse cprop does not propagate a hard register, so it stays in $s1 exactly
 * as retail does (the "origin lifetime" of the earlier drafts).
 * What still differs: slots 0x19C..0x1A8. Slots go by pseudo number, and these four pseudos are
 * gcse PRE reaching registers, numbered in hash-bucket order. Retail: count-1 0x19C, count<<4
 * 0x1A0, &second.point[3] 0x1A4, &first.point[3] 0x1A8. This draft: first.point[3], count-1,
 * count<<4, second.point[3].
 * Bucket = hash % S, S = max_cuid/2|1 (183 here, the "Expression hash table" line of the .gcse
 * dump). Hashes solved from S=181 and S=183: &first.point[3] 14094, &second.point[3] 14238,
 * count-1 14115, count<<4 14132 (count in pseudo 87; the last two move with its number).
 * Only S=155 or S=217 give retail's order with count in 87; S=181 gives it if count's pseudo is
 * 90 or later. A wording that gives S=181 (a loop-local `cur`, or inline wrappers) puts count-1
 * last, and the wrappers and `cur` also change the code.
 * Ruled out by measurement: `int last = count - 1` (count moves to $s3, 1656 B); `int n = count`
 * (cprop folds it back to 87); by-value `Vector4 start` (EABI by-reference, callee copy: $s1=$sp
 * and count in pseudo 91, but a BLKmode copy is ld/sd, retail is lq/sq); a TImode by-value struct
 * or Quadword (passed in $a0). Callers set only $a0-$a3, $f12 and $f13, so no extra parameter.
 * Next: a source shape that gives count a later pseudo, or S=217 with no code change.
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
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern float func_00283CE0(int);
extern void func_00280B90(void *, void *, int);
extern Vector4 D_L00_001B8DC0;

void func_L00_002EC970(Vector4 *start, Vector4 *points, unsigned int color, int count, float u0, float du)
{
    Vector4 origin;
    Vector4 *pos = &origin;
    Beam first, second;
    Vector4 basis[4], nearSize, farSize;
    float width;
    int i;

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
    func_00282CF0(&basis[1], &D_L00_001B8DC0, pos); func_00282DD8(&basis[2], &basis[1], &basis[0]);
    func_00282F20(&basis[2], &basis[2], 1); func_00282DD8(&basis[1], &basis[0], &basis[2]);
    qcopy(&basis[3], pos);
    qcopy(&first.point[0], &nearSize); qcopy(&second.point[0], &farSize);
    func_00282D30(&first.point[1], &first, -1); func_00282D30(&second.point[1], &second, -1);
    func_002830C0(&first, &first, basis); func_002830C0(&first.point[1], &first.point[1], basis);
    func_002830C0(&second, &second, basis); func_002830C0(&second.point[1], &second.point[1], basis);
    for (i = 0; i < count - 1; i++) {
        float u, v;
        func_00282CF0(&basis[0], &points[i + 1], &points[i]); func_00282F20(&basis[0], &basis[0], 1);
        func_00282CF0(&basis[1], &D_L00_001B8DC0, &points[i]); func_00282DD8(&basis[2], &basis[1], &basis[0]);
        func_00282F20(&basis[2], &basis[2], 1); func_00282DD8(&basis[1], &basis[0], &basis[2]);
        qcopy(&basis[3], &points[i]);
        nearSize.f[2] *= 0.75f; farSize.f[2] = nearSize.f[2] * 1.5f;
        qcopy(&first.point[2], &nearSize); qcopy(&second.point[2], &farSize);
        func_00282D30(&first.point[3], &first.point[2], -1); func_00282D30(&second.point[3], &second.point[2], -1);
        func_002830C0(&first.point[2], &first.point[2], basis); func_002830C0(&first.point[3], &first.point[3], basis);
        func_002830C0(&second.point[2], &second.point[2], basis); func_002830C0(&second.point[3], &second.point[3], basis);
        first.color[2] = first.color[3] = color | 0x7F000000;
        second.color[2] = second.color[3] = color | 0x3F000000;
        u = du * func_00283CE0(i + 1);
        v = u + du;
        if (u >= 1.0f) { u -= 1.0f; v -= 1.0f; }
        first.uv[0] = u + u0; first.uv[2] = u + u0; first.uv[4] = v + u0; first.uv[6] = v + u0;
        second.uv[0] = u + u0; second.uv[4] = v + u0;
        second.uv[2] = u + u0; second.uv[6] = v + u0;
        func_00280B90(&first, 0, 0); func_00280B90(&second, 0, 0);
        qcopy(&first.point[0], &first.point[2]); qcopy(&first.point[1], &first.point[3]);
        qcopy(&second.point[0], &second.point[2]); qcopy(&second.point[1], &second.point[3]);
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
