/* func_L00_0042A908 - 564 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft.c is a full src/levels/shared/L00_0042A908-g8.c; needs cflags line
   `src/levels/shared/L00_0042A908-g8.c   -O2 -G8 -ffunction-sections
   -frac2-qcopy`; marker removed from L00_00426340.c. Level data at 0x1BF220
   (L00) is ref_L00_0042A908_00.
   560 vs 564 B; same instruction mix, differing in allocation: retail keeps n
   (D_001B2668) in $fp, hi (D_001B2664) in $f24, lo in $f22, the &w vec
   (sp+0x10) spilled at 0x68($sp); mine puts &w in $fp, n spilled, hi in $f20.
   Retail prologue also loads D_001B1844 first (`lui v1; lw v1,0x1844(v1)`)
   and stores obj->p to 0x64($sp) as a spill.
   Semantics: lerp points between a and b over n steps (t=i/(n-1)*0.9+0.1),
   probe func_00277258, then a short clip/refine block; qcopy(out,b) in the
   hit branch.
   Tried: array vs scalar D_001B1844. */

#include "include_asm.h"
#include "common.h"

extern char *D_001B1844 __attribute__((nosda));
extern float D_001B2660 __attribute__((sda));
extern float D_001B2664 __attribute__((sda));
extern int D_001B2668 __attribute__((sda));
extern char ref_L00_0042A908_00[];

extern float func_00282DF0(void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *, void *, void *, float);
extern int func_00277258(void *, int, void *, float);
extern float func_L00_0031BDC0(void *, void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);

void func_L00_0042A908(char *obj, void *out, void *a, void *b) {
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    float x[4] __attribute__((aligned(16)));
    float y[4] __attribute__((aligned(16)));
    float z[4] __attribute__((aligned(16)));
    float u[4] __attribute__((aligned(16)));
    char *p;
    float lo, hi, len, t, k, d;
    int i, n;

    lo = D_001B2660;
    hi = D_001B2664;
    n = D_001B2668;
    p = *(char **)(D_001B1844 + *(short *)(obj + 0x84) * 32 + 0x1C);
    qcopy(out, b);
    v[0] = *(float *)(p + 0x30);
    v[1] = 0.0f;
    v[2] = *(float *)(p + 0x34);
    v[3] = 0.0f;
    len = func_00282DF0(v);
    for (i = 0; i < n; i++) {
        k = hi - lo;
        t = func_00283CE0(i) / func_00283CE0(n - 1);
        t = t * 0.9f + 0.1f;
        func_00282D08(w, a, b, t);
        t = k * t;
        if (func_00277258(w, 16, *(void **)(p + 0x20), lo + t)) {
            d = func_L00_0031BDC0(z, a, b, ref_L00_0042A908_00);
            func_00282CF0(u, z, ref_L00_0042A908_00);
            d = lo + k * d;
            if (func_00282DF0(u) <= d) {
                func_00282F20(u, u, d);
                func_00282CC0(u, ref_L00_0042A908_00, u);
                func_00282CF0(x, u, a);
                func_00282F20(y, x, len);
                func_00282CC0(b, a, y);
                qcopy(out, b);
            }
        }
    }
}
