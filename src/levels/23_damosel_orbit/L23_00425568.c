#include "include_asm.h"
#include "names.h"

/* func_L23_00425568 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. */

typedef unsigned char u8;

typedef int s32;

typedef int TI16 __attribute__((mode(TI)));

extern void func_00282CF0(float *, float *, float *);

extern float func_00282DF0(float *);

extern void func_L00_0031AA28(TI16 *out, float *a, float *b, TI16 *c, TI16 *d, float t);

extern void func_L23_004260F0(u8 *obj, float *dst, TI16 *src1, TI16 *src2, float scale);

/* Blends the object's position toward its target: two control points, then five curve samples
   written to the state's table at +0x30 (the last sample is the target itself).
   Spelling: `out` is set once, before the loops (it is hoisted to $s4 either way, and fewer
   weighted references than the object pointer keep the two in retail's $s3/$s4); each control
   point is copied through a local of its own, so only the sample copies are grouped `lq`/`sq`
   pairs; and the sample is stored once after the if/else, which leaves the `b` slot empty. */
/* Builds the curved path a trail follows from the object to its target, stored as five
   points. */
void func_L23_00425568(u8 *obj) {
    TI16 loc[5];
    TI16 va;
    TI16 vb;
    TI16 vc;
    TI16 vd;
    TI16 *out;
    TI16 *p;
    u8 *vars;
    float spread;
    s32 i;
    s32 j;
    s32 next;

    i = 0;
    vars = *(u8 **)(obj + 0x68);
    out = &loc[3];
    do {
        FastVecSub((float *)&loc[0], *(float **)(vars + 0x20), (float *)(obj + 0x10));
        next = i + 1;
        j = 0;
        p = (TI16 *)(vars + 0x30);
        spread = FastVecLength((float *)&loc[0]) * *(float *)(vars + 0x1C);
        vb = *(TI16 *)(obj + 0x10);
        va = **(TI16 **)(vars + 0x20);
        loc[4] = vb;
        loc[3] = va;
        ComputeCurveControlPoint(obj, (float *)&loc[1], &loc[3], &loc[4], spread);
        vc = *(TI16 *)(obj + 0x10);
        loc[3] = vc;
        vd = **(TI16 **)(vars + 0x20);
        loc[4] = vd;
        ComputeCurveControlPoint(obj, (float *)&loc[2], &loc[3], &loc[4], spread);
        do {
            float f = (float)j * 0.2f;

            if (j == 4) {
                *out = **(TI16 **)(vars + 0x20);
            } else {
                InterpolateCubicVector_L00(out, (float *)(obj + 0x10), *(float **)(vars + 0x20), &loc[1], &loc[2], f);
            }
            *p = *out;
            j++;
            p++;
        } while (j < 5);
        i = next;
    } while (i <= 0);
}
