#include "include_asm.h"
#include "names.h"

/* func_0031E560 in its own -g unit: the angle division carries the
   statement-boundary padding. */

typedef struct {
    float base[4];
    char *owner;
    float scale;
    int step;
    int steps;
    float size;
    float angle;
    char pad28[8];
} Ring_0031E560;

extern Ring_0031E560 *D_001B2754[] __attribute__((sda));
extern float IntToFloat(int);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
extern float math_fast_sin_or_cos_a(float);
extern int FloatToInt(float);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_draw_two_strip_beam(void *, void *, int, int, int, int, float, float, float);

/* For every ring entry of the object (64 slots), steps its angle round the full
   turn and emits one spark at the entry's offset with a pulsing brightness. */
void glow_ring_emit_beams(char *object)
{
    float v[4] __attribute__((aligned(16)));
    Ring_0031E560 *e;
    char *vars;
    float k;
    int n;
    int i;

    for (i = 0; i < 64; i++) {
        e = (Ring_0031E560 *)(i * 0x30 + (int)D_001B2754[0]);
        if (e->owner != object)
            continue;
        e->angle = 6.2831855f - IntToFloat(e->step) * 6.2831855f / IntToFloat(e->steps - 1);
        vec_scale_to_length(v, e, e->scale);
        k = IntToFloat(math_random_int_range(0x30, 0x50));
        n = FloatToInt(math_fast_sin_or_cos_a(e->angle - 3.1415927f) * (k * 0.5f) + k * 0.5f);
        vars = *(char **)(object + 0x68);
        FastVecAdd(v, v, object + 0x10);
        gfx_draw_two_strip_beam(object + 0x10, v, 0x800000, n, 0x2F, 2, *(float *)(vars + 0x18) * 0.25f, 0.0f,
                      e->size);
    }
}
