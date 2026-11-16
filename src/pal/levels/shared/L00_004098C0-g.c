#include "names.h"
/* func_PAL_L00_004098C0, the PAL copy of func_L00_00404ED8: the same C, with the
   per-frame float rates and the puff's life range at 50 Hz, and the particle's
   life scaled as it is passed. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float math_random_float_range(float lo, float hi);
extern float math_random_signed_float_range(float a, float b);
extern int math_random_int_range(int lo, int hi);
extern void FastVecSub(void *out, void *a, void *b);
extern void FastVecAdd(void *out, void *a, void *b);
extern void vec_scale_to_length(void *out, void *a, float scale);

typedef union { TI128 q; float f[4]; } Vec;
extern float FastVecLength(void *v);
extern float IntToFloat(int n);
extern int FloatToInt(float f);
extern int func_001163B0(void);
extern int math_random_int_below(int n);
extern void FastVecScale(void *out, void *v, float scale);
extern void vec_add_random_offset(void *v, float f);
extern char *func_PAL_002C23B8(void *pos, void *vel, int life, int alpha, unsigned int colour, int n,
                           float a, float b, float c, float d, float e);
extern char *func_PAL_002BD790(void *pos, void *vel, unsigned int colour, int a, int life, int b, int c,
                           int d, int e, float f);
extern Vec g_hero_state_block;
extern char g_effect_definitions[];

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
    length = FastVecLength(ctx);
    count = FloatToInt(length * 10.0f);
    qcopy(&point, to);
    FastVecSub(&step, from, to);
    scale = IntToFloat(count);
    vec_scale_to_length(&step, &step, length / scale);
    tbl = g_effect_definitions;
    if (count > 0) do {
        n = FloatToInt(math_random_signed_float_range(1.0f, 3.0f));
        drift = -(math_random_float_range(0.1f, 0.2f) * 0.020000001f);
        FastVecScale(&vel, &g_hero_state_block, drift);
        life = math_random_int_range(30, 45);
        speed = -math_random_float_range(500.0f, 1000.0f);
        pickSegmentAlpha(&alpha);
        particle = func_PAL_002C23B8(&point, &vel, (life * 5 + 2) / 6, alpha, 0x407fff, n, 42000.0f, speed, 1.0f, 0.0f, 0.0f);
        FastVecAdd(&point, &point, &step);
        if (particle) {
            particle[2] = **(unsigned char **)(tbl + 92);
            if (alpha == 64)
                particle[3] = 72;
            else
                particle[3] = 68;
        }
    } while (--count);
    if (math_random_int_below(4) == 0) {
        char *puff;

        FastVecScale(&extra, ctx, -0.040000003f);
        vec_add_random_offset(&extra, 0.020000001f);
        extra.f[2] += 0.030000001f;
        life = math_random_int_range(25, 37);
        puff = func_PAL_002BD790(obj + 16, &extra, 0x7f407fff, 255, life, 0, -1, -1, 0, 31500.002f);
        if (puff) {
            *(float *)(puff + 44) = 0.0024f;
            puff[2] = **(unsigned char **)(g_effect_definitions + 212);
        }
    }
}
