#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef float f32;
extern s32 D_L08_001B29DC __attribute__((sda));
extern f32 math_random_float_range(f32, f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern char g_hero_position[];
extern void FastVecSub(void *, void *, void *);
extern f32 FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void moby_update_ground_probe(char *);
extern int func_PAL_002B1A50(char *, char *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern char g_hero_position[];
extern s32 g_beam_slot_state[];
extern s32 D_L08_001B39E0[];
extern s32 D_L08_001B39F0[];
extern s32 g_beam_slot_key[];

/* The record's whole per-frame pass: the sibling step, the aim vector copied out of the
   sub-object, the shared sprite pass, then the dispatch the shared tag call returns. */
void func_PAL_L08_0042B610(char *a0) {
    char *q = *(char **)(a0 + 0x68);
    int r;

    moby_update_ground_probe(a0);
    *(f32 *)(a0 + 0x2C) = *(f32 *)(*(char **)(a0 + 0x24) + 0x24);
    moby_halve_linked_scale(a0);
    r = func_PAL_002B1A50(a0, q + 0x50, 0);
    if (r == 0) {
        return;
    }
    if (r == 1) {
        float v[4];

        FastVecSub(v, a0 + 0x10, g_hero_position);
        vec_scale_to_length(q + 0x1A0, v, 0.20000002f);
    } else {
        if (r == 4) {
            *(unsigned char *)(q + 0xC6) = 0;
            *(s32 *)(q + 0xCC) = -1;
        }
        group_advance_turn(a0);
    }
    creature_release_sounds(a0);
}


