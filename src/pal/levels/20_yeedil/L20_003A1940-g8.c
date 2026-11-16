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
extern void electric_orb_draw_pal(char *);
extern int g_electric_orb_spin_rate __attribute__((sda));
extern int g_electric_orb_color_a __attribute__((sda));
extern int g_electric_orb_color_b;
extern int g_electric_orb_color_c;
extern int g_electric_orb_color_d;

void func_PAL_L20_003A1CE8(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    if (math_fast_float_d(state) != 0) {
        moby_mark_spawned(arg0);
    } else {
        f32 x = *(f32 *)(state + 0x8);
        f32 r, s;
        int v, w, lo, hi;

        if (*(int *)(state + 0xC) != 0) {
            r = FastAddRotations(x, (f32)g_electric_orb_spin_rate * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = math_fast_sin_or_cos_b(r);
            v = FastTweenColor(s * 0.5f + 0.5f, g_electric_orb_color_a, g_electric_orb_color_b);
        } else {
            r = FastAddRotations(x, (f32)g_electric_orb_spin_rate * 0.0003490659f);
            *(f32 *)(state + 0x8) = r;
            s = math_fast_sin_or_cos_b(r);
            v = FastTweenColor(s * s * 0.5f + 0.5f, g_electric_orb_color_c, g_electric_orb_color_d);
        }
        w = FastTweenColor(0.15f, *(int *)(state + 0x10) | *(int *)(state + 0x4), v);
        lo = w & 0xFFFFFF;
        hi = w & 0xFF000000;
        *(int *)(state + 0x10) = hi;
        *(int *)(state + 0x4) = lo;
        *(f32 *)(state + 0x14) = IntToFloat(hi >> 24) * 0.00390625f;
        gfx_add_draw_callback_first(electric_orb_draw_pal, arg0);
    }
}
