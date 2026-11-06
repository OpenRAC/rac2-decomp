/* func_PAL_L00_004098C0, the PAL copy of func_L00_00404ED8: the same C, with the
   per-frame float rates and the puff's life range at 50 Hz, and the particle's
   life scaled as it is passed. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float func_002A7878(float lo, float hi);
extern float func_002A78D8(float a, float b);
extern int func_002A7820(int lo, int hi);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282CC0(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *a, float scale);

typedef union { TI128 q; float f[4]; } Vec;
extern float func_00282DF0(void *v);
extern float func_00283CE0(int n);
extern int func_00283CF0(float f);
extern int func_001163B0(void);
extern int func_002A77E0(int n);
extern void func_00282D30(void *out, void *v, float scale);
extern void func_002ACB48(void *v, float f);
extern char *func_PAL_002C23B8(void *pos, void *vel, int life, int alpha, unsigned int colour, int n,
                           float a, float b, float c, float d, float e);
extern char *func_PAL_002BD790(void *pos, void *vel, unsigned int colour, int a, int life, int b, int c,
                           int d, int e, float f);
extern Vec D_0018A0E0;
extern char D_L00_001FE940[];

/* The alpha is chosen through an out parameter: until purge_addressof the
   variable is a memory reference, so the branch survives cse1 and jump.c only
   turns it into retail's movn after the loop pass (64 stays in the loop and
   1.0f is loaded at each use). */
static inline void pickSegmentAlpha(int *alpha)
{
    if (func_001163B0() & 2)
        *alpha = 64;
    else
        *alpha = 96;
}

/* Spawns particles at steps of a tenth of a unit along the segment from a to b,
   each with a random size, drift, life and one of two alphas; one time in four
   it also spawns a slow puff at the object. */
void func_PAL_L00_004098C0(char *obj, Vec *a, Vec *b)
{
    Vec start, end, vel, point, step, extra;
    Vec *from = &start, *to = &end;
    char *ctx = *(char **)(obj + 104), *particle, *tbl;
    float length, scale, speed, drift;
    int count, alpha, life, n;

    from->q = a->q;
    to->q = b->q;
    length = func_00282DF0(ctx);
    count = func_00283CF0(length * 10.0f);
    qcopy(&point, to);
    func_00282CF0(&step, from, to);
    scale = func_00283CE0(count);
    func_00282F20(&step, &step, length / scale);
    tbl = D_L00_001FE940;
    if (count > 0) do {
        n = func_00283CF0(func_002A78D8(1.0f, 3.0f));
        drift = -(func_002A7878(0.1f, 0.2f) * 0.020000001f);
        func_00282D30(&vel, &D_0018A0E0, drift);
        life = func_002A7820(30, 45);
        speed = -func_002A7878(500.0f, 1000.0f);
        pickSegmentAlpha(&alpha);
        particle = func_PAL_002C23B8(&point, &vel, (life * 5 + 2) / 6, alpha, 0x407fff, n, 42000.0f, speed, 1.0f, 0.0f, 0.0f);
        func_00282CC0(&point, &point, &step);
        if (particle) {
            particle[2] = **(unsigned char **)(tbl + 92);
            if (alpha == 64)
                particle[3] = 72;
            else
                particle[3] = 68;
        }
    } while (--count);
    if (func_002A77E0(4) == 0) {
        char *puff;

        func_00282D30(&extra, ctx, -0.040000003f);
        func_002ACB48(&extra, 0.020000001f);
        extra.f[2] += 0.030000001f;
        life = func_002A7820(25, 37);
        puff = func_PAL_002BD790(obj + 16, &extra, 0x7f407fff, 255, life, 0, -1, -1, 0, 31500.002f);
        if (puff) {
            *(float *)(puff + 44) = 0.0024f;
            puff[2] = **(unsigned char **)(D_L00_001FE940 + 212);
        }
    }
}
