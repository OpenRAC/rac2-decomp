/* 7 November 2026: clean rewrite from matched donor func_L00_003DCC48 (src/levels/shared/L00_003DCC48.c,
 * same frame and 0.84 opcode similarity): char-array beams, offsets[2], `basis` pointer, donor order.
 * Profile -O2 -G0 -ffunction-sections (donor's). Best: 1652/1652 B, 12 rows, 0/27 places; only the
 * spill slots 0x19C..0x1A8 differ, same as the old draft (old draft kept below, rewrite under #if 0 at the end).
 * gcse dump measurements: S=183 here; with S=183 no pseudo number for count gives retail's bucket
 * order (count-1, count<<4, q+48, p+48). Count last among params (still ABI-legal) gives pseudo 89, same 12.
 * S=181 needs count in pseudo >=90 (a `char *pi = points + i*16` loop pointer gives S=181 but 7 code rows
 * and count stays 89). `int n = count` kept alive by reusing count as c2: n=92 but 240 rows. Inline
 * wrapper: S=171, code changes. With count <=89 only S in {103,147,155,217,235,239} works.
 */
/* 5 November 2026: Paired array/record owners and ABI-preserving FP-first parameters produced identical 1652-byte near-miss output. The twelve spill-offset differences remain; this is a three-way tie, not a new remedy.
 */
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

#if 0 /* 7 November 2026 donor-guided rewrite: also 12 rows, -O2 -G0 -ffunction-sections */
typedef int BeamQuad __attribute__((mode(TI)));
typedef union { BeamQuad quad; float f[4]; } BeamVector;
extern void func_00281DE8(void *, int, int, int);
extern int func_001163B0(void);
extern float func_002A7878(float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_002830C0(void *, void *, void *);
extern float func_00283CE0(int);
extern void func_00280B90(void *, void *, int);

extern float D_L00_001B8DC0[];
void func_L00_002EC970(void *start, char *points, int color, int count, float tex, float step)
{
    char origin[16] __attribute__((aligned(16)));
    char p[144] __attribute__((aligned(16)));
    char q[144] __attribute__((aligned(16)));
    float m[16];
    BeamVector offsets[2];
    int i;
    int c1, c2;
    char *basis = origin;
    float v, u, a, b, width;
    *(BeamQuad *)origin = *(BeamQuad *)start;
    func_00281DE8(p,23,1,128);
    func_00281DE8(q,23,1,128);
    offsets[0].quad=0; offsets[1].quad=0;
    *(int *)(p+64)=*(int *)(p+68)=color|0x7f000000;
    *(int *)(q+64)=*(int *)(q+68)=color|0x3f000000;
    offsets[0].f[3]=1;
    offsets[1].f[3]=1;
    width=func_002A7878(.2f,.45f);
    offsets[0].f[2]=width;
    offsets[1].f[2]=width*1.5f;
    if (!(func_001163B0()&1)) {
        *(float *)(p+80)=tex; *(float *)(p+84)=0; *(float *)(p+88)=tex; *(float *)(p+92)=1;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=0; *(float *)(p+104)=step+tex; *(float *)(p+108)=1;
        *(float *)(q+80)=tex; *(float *)(q+84)=0; *(float *)(q+88)=tex; *(float *)(q+92)=1;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=0; *(float *)(q+104)=step+tex; *(float *)(q+108)=1;
    } else {
        *(float *)(p+80)=tex; *(float *)(p+84)=1; *(float *)(p+88)=tex; *(float *)(p+92)=0;
        *(float *)(p+96)=step+tex; *(float *)(p+100)=1; *(float *)(p+104)=step+tex; *(float *)(p+108)=0;
        *(float *)(q+80)=tex; *(float *)(q+84)=1; *(float *)(q+88)=tex; *(float *)(q+92)=0;
        *(float *)(q+96)=step+tex; *(float *)(q+100)=1; *(float *)(q+104)=step+tex; *(float *)(q+108)=0;
    }
    func_00282CF0(m,points,basis); func_00282F20(m,m,1);
    func_00282CF0(m+4,D_L00_001B8DC0,basis);
    func_00282DD8(m+8,m+4,m); func_00282F20(m+8,m+8,1); func_00282DD8(m+4,m,m+8);
    qcopy(m+12,basis);
    qcopy(p,offsets); qcopy(q,offsets+1);
    func_00282D30(p+16,p,-1); func_00282D30(q+16,q,-1);
    func_002830C0(p,p,m); func_002830C0(p+16,p+16,m); func_002830C0(q,q,m); func_002830C0(q+16,q+16,m);
    for(i=0;i<count-1;i++) {
        c1=color|0x7f000000; c2=color|0x3f000000;
        basis = (char *)m;
        func_00282CF0(basis,points+(i*16+16),points+i*16); func_00282F20(basis,basis,1);
        func_00282CF0(basis+16,D_L00_001B8DC0,points+i*16);
        func_00282DD8(basis+32,basis+16,basis); func_00282F20(basis+32,basis+32,1); func_00282DD8(basis+16,basis,basis+32);
        qcopy(basis+48,points+i*16);
        offsets[0].f[2]*=.75f; offsets[1].f[2]=offsets[0].f[2]*1.5f;
        qcopy(p+32,offsets); qcopy(q+32,offsets+1);
        func_00282D30(p+48,p+32,-1); func_00282D30(q+48,q+32,-1);
        func_002830C0(p+32,p+32,basis); func_002830C0(p+48,p+48,basis); func_002830C0(q+32,q+32,basis); func_002830C0(q+48,q+48,basis);
        *(int *)(p+72)=*(int *)(p+76)=c1; *(int *)(q+72)=*(int *)(q+76)=c2;
        u=step*func_00283CE0(i+1); v=u+step; if(u>=1) {u-=1;v-=1;}
        *(float *)(p+80)=u+tex; *(float *)(p+88)=u+tex; *(float *)(p+96)=v+tex; *(float *)(p+104)=v+tex;
        *(float *)(q+80)=u+tex; *(float *)(q+96)=v+tex; *(float *)(q+88)=u+tex; *(float *)(q+104)=v+tex;
        func_00280B90(p,0,0); func_00280B90(q,0,0);
        qcopy(p,p+32);qcopy(p+16,p+48);qcopy(q,q+32);qcopy(q+16,q+48);
    }
    qcopy(m+12,points+(count-1)*16);
    offsets[0].f[2]*=.75f; offsets[1].f[2]=offsets[0].f[2]*1.5f;
    qcopy(p+32,offsets);qcopy(q+32,offsets+1);
    func_00282D30(p+48,p+32,-1);func_00282D30(q+48,q+32,-1);
    func_002830C0(p+32,p+32,m);func_002830C0(p+48,p+48,m);func_002830C0(q+32,q+32,m);func_002830C0(q+48,q+48,m);
    *(int *)(q+72)=*(int *)(q+76)=*(int *)(p+72)=*(int *)(p+76)=color;
    a=step*func_00283CE0(i+1); b=a+step; if(a>=1) {a-=1;b-=1;}
    *(float *)(p+80)=a+tex; *(float *)(p+88)=a+tex; *(float *)(p+96)=b+tex; *(float *)(p+104)=b+tex;
    *(float *)(q+80)=a+tex; *(float *)(q+96)=b+tex; *(float *)(q+104)=b+tex; *(float *)(q+88)=a+tex;
    func_00280B90(p,0,0);func_00280B90(q,0,0);
}
#endif
