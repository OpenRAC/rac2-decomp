#include "include_asm.h"
#include "names.h"

typedef float f32;
extern void moby_mark_spawned(char *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(float, int, int);
extern float IntToFloat(int);
extern void gfx_add_draw_callback_first(void *, void *);
extern void func_PAL_L20_003A21A0(char *);
extern int D_L20_001AEDA8 __attribute__((sda));
extern int D_L20_001AED90 __attribute__((sda));
extern int D_L20_001AED94;
extern int D_L20_001AED98;
extern int D_L20_001AED9C;

void func_PAL_L20_003A1CE8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (math_fast_float_d(state) != 0) {
        moby_mark_spawned(arg0);
    } else {
        f32 x = *(f32 *)(state + 0x8);
        f32 r, s;
        int v, w, lo, hi;

        if (*(int *)(state + 0xC) != 0) {
            r = FastAddRotations(x, (f32)D_L20_001AEDA8 * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = math_fast_sin_or_cos_b(r);
            v = FastTweenColor(s * 0.5f + 0.5f, D_L20_001AED90, D_L20_001AED94);
        } else {
            r = FastAddRotations(x, (f32)D_L20_001AEDA8 * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = math_fast_sin_or_cos_b(r);
            v = FastTweenColor(s * s * 0.5f + 0.5f, D_L20_001AED98, D_L20_001AED9C);
        }
        w = FastTweenColor(0.15f, *(int *)(state + 0x10) | *(int *)(state + 0x4), v);
        lo = w & 0xFFFFFF;
        hi = w & 0xFF000000;
        *(int *)(state + 0x10) = hi;
        *(int *)(state + 0x4) = lo;
        *(f32 *)(state + 0x14) = IntToFloat(hi >> 24) * 0.00390625f;
        gfx_add_draw_callback_first(func_PAL_L20_003A21A0, arg0);
    }
}
