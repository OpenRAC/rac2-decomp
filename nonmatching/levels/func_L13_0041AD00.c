/* 6 November 2026, round 10b: no gain (101 words, ~45 runs). Branch row b keeps 16-17 refs and outranks side; the i-loop copy takes $s0 only inside a group, which splits row and quotient; six index-test spellings and five flags give no slti/bnel; spill slots follow pseudo number and the uv base comes first here. */
/* 6 November 2026, round 10: 1376/1376 bytes, 0/2, 101 differing words excluding
 * relocation fields (was 279), first +0xa0. Profile adds -fno-sched-interblock
 * (stops arg moves above the j&1 test; v now lands in a0). Changes: branch-loop args
 * as ((ADVector (*)[4])(s+0x420))[k]+branch (keeps s in $s7, frame 0x320);
 * vertex v = (ADVector *)(j*16 + (int)q); setup chains q[0]=q[1]=q[2] and a forward
 * n loop (setup now matches); i-loop rows b = i*16 + s; a = b; b += 0x30;
 * a += 0x20 with no group (copy kept, quotient spilled, one subu tail); branch
 * rows the same with a do { b = ... } while (0) group (gives s one more weighted
 * ref so s beats &previous for $s7). Remaining: branch row b (17 refs) outranks
 * the uv giv and side, so side lands in $s5 not $s4 and k in $s4 not $s3; i-loop
 * copy gets $s5 not $s0; index tests give beql/bltz, retail beqz/slti/bnel;
 * spill-slot order differs. */
/* 6 November 2026, round 9: the func_L13_0041AB30 idiom (p = s + i*16; r = p;
 * do { r += 0x20; } while (0); p += 0x30; same for the 0x420/0x460 branch rows)
 * stays at 1420/1376 bytes, 0/2, 281 rows (279 before); -g and
 * -frac2-sticky-volatile-refs tie. The blocker is still allocation: the state pointer
 * spills to 0x280 and (i/4)*4 holds $fp, while retail keeps s in $s7, &previous in
 * $fp and spills the quotient (so one subu, not one per tail). Original C retained. */
/* Nonmatching C reconstruction (opus-1, v2196, USA v1.01, 2026-11-03).
 * Tier: far. Profile: -O2 -G8 -ffunction-sections -frac2-qcopy
 * -frac2-qcopy-barrier. Best cdiff: 1420 compiled bytes / 1376 retail,
 * 0 of 2 places.
 * Semantics fix over the earlier 1380-byte draft: retail's j=1 corner calls
 * func_00282CC0(v, v, &previous) (a2 = fp), not &side. Each corner is row0
 * -/+ previous (j=0,1) or row1 -/+ side (j=2,3), with the j&1 test inside
 * each arm. That gives retail's control flow: the sll is shared before the
 * j<2 branch (PRE), per-arm vertex address, CC0 tails cross-jumped.
 * The earlier draft's size was closer only because its j=1 call was wrong.
 * Testing j&1 once after the if/else (with a dir variable) gave 1364 bytes
 * and fewer copies, but lost the per-arm tests retail has.
 * The idx pointer in the branch loop reproduces retail's s+0x18 spill before
 * the i loop; nested index<31 / index>=0 tests keep retail's two slti tests.
 * Remaining: v lands in v1 (extra a0 copies) instead of a0; the state
 * pointer spills where retail keeps it in s7 (retail spills the quotient
 * and next index instead); retail copies the row (X = i*16 + s; Y = X;
 * Y += 0x20; X += 0x30), the same copy pattern as func_L13_0041AB30;
 * frame 0x310 versus 0x320.
 * All declarations are below.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef union { int q __attribute__((mode(TI))); float f[4]; } ADVector;
typedef struct { ADVector vertex[4]; unsigned int color[4]; float uv[4][2]; unsigned long primitive, texture, state, flags; } ADQuad;
extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282C88(void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern unsigned long func_0027C878(int);
extern void func_00280B90(void *, void *, int);
extern char D_L13_001B98C0[];
extern int D_L13_001B163C __attribute__((sda));
extern int D_L13_001B1640 __attribute__((sda));
extern int D_L13_001B1644 __attribute__((sda));
extern int D_L13_001B1648 __attribute__((sda));
extern int D_L13_001B164C __attribute__((sda));
extern float D_L13_001B1660_abs[4][2] __asm__("D_L13_001B1660") __attribute__((sda));
extern float D_L13_001B1660_gp[4][2] SDATA(D_L13_001B1660);
void func_L13_0041AD00(char *obj) {
    ADQuad q[3];
    ADVector matrix[4], inverse[4], camera, previous, side, delta, segment;
    char *s = *(char **)(obj + 0x68);
    unsigned long texture, flags;
    int i,j,k, index, n, branch;
    func_00283410(matrix,s+0x650);
    func_00283698(inverse,matrix);
    matrix[3].q = *(Vector128 *)(obj+0x10);
    func_00282CF0(&camera,D_L13_001B98C0,obj+0x10);
    func_00283098(&camera,&camera,inverse);
    texture=func_0027C878(D_L13_001B163C);
    flags=(long)D_L13_001B1640;
    flags |= (long)D_L13_001B1644<<2;
    flags |= (long)D_L13_001B1648<<4;
    flags |= (long)D_L13_001B164C<<6;
    flags |= 0x8000000000UL;
    q[0].state=q[1].state=q[2].state=0xff9000000260UL;
    q[0].texture=q[1].texture=q[2].texture=texture;
    q[0].primitive=q[1].primitive=q[2].primitive=0;
    q[0].flags=q[1].flags=q[2].flags=flags;
    for (n=0;n<4;n++) {
        q[0].uv[n][1]=q[1].uv[n][1]=q[2].uv[n][1]=D_L13_001B1660_abs[n][1];
        q[0].color[n]=q[1].color[n]=q[2].color[n]=*(int *)(s+0x14);
    }
    func_00282C88(&side);
    for (i=0;i<31;i++) {
        previous.q = side.q;
        if (i<30) {
            func_00282CF0(&segment,s+(0x20+i*16),s+(0x40+i*16));
            func_00282CF0(&delta,s+(0x30+i*16),&camera);
            func_00282DD8(&side,&delta,&segment);
            func_00282F20(&side,&side,0.1f);
        } else func_00282C88(&side);
        {
        char *a, *b;
        b = (char *)(i*16 + (int)s);
        a = b;
        b += 0x30;
        a += 0x20;
        for (j=0;j<4;j++) {
            ADVector *v;
            if (j<2) {
                v = (ADVector *)(j*16 + (int)q);
                v->q = *(Vector128 *)a;
                if (j&1) func_00282CC0(v,v,&previous);
                else func_00282CF0(v,v,&previous);
            } else {
                v = (ADVector *)(j*16 + (int)q);
                v->q = *(Vector128 *)b;
                if (j&1) func_00282CC0(v,v,&side);
                else func_00282CF0(v,v,&side);
            }
            q[0].uv[j][0]=D_L13_001B1660_gp[j][0]+func_00283CE0(i-(i/4)*4)*0.25f;
        }
        }
        func_00280B90(q,matrix,0);
    }
    for (branch=0;branch<4;branch++) {
        func_00282C88(&side);
        {
        unsigned char *idx = (unsigned char *)s + 0x18;
        index = idx[branch];
        }
        if (index<31) if (index>=0) {
            for (k=0;k<3;k++) {
                previous.q = side.q;
                if (k<2) {
                    func_00282CF0(&segment,((ADVector (*)[4])(s+0x420))[k]+branch,((ADVector (*)[4])(s+0x4a0))[k]+branch);
                    func_00282CF0(&delta,((ADVector (*)[4])(s+0x460))[k]+branch,&camera);
                    func_00282DD8(&side,&delta,&segment);
                    func_00282F20(&side,&side,0.1f);
                } else func_00282C88(&side);
                if (!k) previous.q = side.q;
                {
                char *a, *b;
                do { b = (char *)(((ADVector (*)[4])s)[k]+branch); } while (0);
                a = b;
                b += 0x460;
                a += 0x420;
                for (j=0;j<4;j++) {
                    ADVector *v;
                    if (j<2) {
                        v = (ADVector *)(j*16 + (int)q);
                        v->q = *(Vector128 *)a;
                        if (j&1) func_00282CC0(v,v,&previous);
                        else func_00282CF0(v,v,&previous);
                    } else {
                        v = (ADVector *)(j*16 + (int)q);
                        v->q = *(Vector128 *)b;
                        if (j&1) func_00282CC0(v,v,&side);
                        else func_00282CF0(v,v,&side);
                    }
                    q[0].uv[j][0]=D_L13_001B1660_gp[j][0]+func_00283CE0(k-(k/4)*4)*0.25f;
                }
                }
                func_00280B90(q,matrix,0);
            }
        }
    }
}
