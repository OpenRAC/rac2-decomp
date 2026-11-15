#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef float f32;
extern f32 math_random_float_range(f32 low, f32 high);
extern f32 FastVecDot(void *, void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern u8 D_001A63A8_4[];
extern u8 g_hero_state[];
extern f32 fast_vec_dist(void *a0, void *a1);
extern int FloatToInt(f32);
extern int math_fast_float_d(void *);
extern void moby_mark_spawned(void *);
extern int coll_sweep_from_object(void *, void *, int, f32, f32, f32, int, int, int);
extern void moby_mark_spawned(void *object);
extern f32 math_random_float_range(f32 low, f32 high);

/* Halves whatever the two floats say, doubles it back, rescales it by the
 * controller's rate, then hands the result to the placement call as the alpha;
 * the controller's counter also drives the byte at +0x23 (a 127/40 ramp). */
void func_PAL_L22_003B06CC(u8 *a0) {
    u8 *obj = a0;
    u8 *sub = *(u8 **)(obj + 0x24);
    u8 *ctl = *(u8 **)(obj + 0x68);
    u8 *resident;
    f32 v;
    int n;

    v = *(f32 *)(obj + 0x2C) / *(f32 *)(sub + 0x24) * 0.5f;
    v += *(f32 *)(ctl + 0x0);
    *(f32 *)(obj + 0x2C) = v + v;
    *(f32 *)(obj + 0x2C) = *(f32 *)(obj + 0x2C) * *(f32 *)(sub + 0x24);
    n = *(int *)(ctl + 0x8);
    if (n < 0x21) *(u8 *)(obj + 0x23) = n * 127 / 33;
    resident = g_hero_state;
    coll_sweep_from_object(*(void **)(resident + 0x2290), obj + 0x10, 0x30000, v,
                  (f32)FloatToInt(*(f32 *)(ctl + 0xC)), 1.0f, 0, 1, 0);
    if (math_fast_float_d(ctl + 0x8))
        moby_mark_spawned(obj);
}
