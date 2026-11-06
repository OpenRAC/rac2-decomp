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
    q[0].state=q[2].state=q[1].state=0xff9000000260UL;
    q[0].texture=q[2].texture=q[1].texture=texture;
    q[2].primitive=q[1].primitive=q[0].primitive=0;
    q[0].flags=q[2].flags=q[1].flags=flags;
    for (n=3;n>=0;n--) {
        q[2].uv[3-n][1]=q[1].uv[3-n][1]=q[0].uv[3-n][1]=D_L13_001B1660_abs[3-n][1];
        q[2].color[3-n]=q[1].color[3-n]=q[0].color[3-n]=*(int *)(s+0x14);
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
        for (j=0;j<4;j++) {
            ADVector *v;
            if (j<2) {
                v = &q[0].vertex[j];
                v->q = *(Vector128 *)(s+(0x20+i*16));
                if (j&1) func_00282CC0(v,v,&previous);
                else func_00282CF0(v,v,&previous);
            } else {
                v = &q[0].vertex[j];
                v->q = *(Vector128 *)(s+(0x30+i*16));
                if (j&1) func_00282CC0(v,v,&side);
                else func_00282CF0(v,v,&side);
            }
            q[0].uv[j][0]=D_L13_001B1660_gp[j][0]+func_00283CE0(i-(i/4)*4)*0.25f;
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
                    func_00282CF0(&segment,s+(0x420+k*64)+branch*16,s+(0x4a0+k*64)+branch*16);
                    func_00282CF0(&delta,s+(0x460+k*64)+branch*16,&camera);
                    func_00282DD8(&side,&delta,&segment);
                    func_00282F20(&side,&side,0.1f);
                } else func_00282C88(&side);
                if (!k) previous.q = side.q;
                for (j=0;j<4;j++) {
            ADVector *v;
                    if (j<2) {
                        v = &q[0].vertex[j];
                        v->q = *(Vector128 *)(s+(0x420+k*64)+branch*16);
                        if (j&1) func_00282CC0(v,v,&previous);
                        else func_00282CF0(v,v,&previous);
                    } else {
                        v = &q[0].vertex[j];
                        v->q = *(Vector128 *)(s+(0x460+k*64)+branch*16);
                        if (j&1) func_00282CC0(v,v,&side);
                        else func_00282CF0(v,v,&side);
                    }
                    q[0].uv[j][0]=D_L13_001B1660_gp[j][0]+func_00283CE0(k-(k/4)*4)*0.25f;
                }
                func_00280B90(q,matrix,0);
            }
        }
    }
}
