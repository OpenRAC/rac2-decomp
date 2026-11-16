#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern f32 math_random_signed_float_range(f32 low, f32 high);
extern f32 g_default_effect_vector[] __attribute__((sda));
typedef struct {
    TI128 position;
    int f10;
    int f14;
    int f18;
    int f1C;
    int f20;
} State_332440;
extern int part_alloc_effect_slot(void *obj, f32 x, f32 y, f32 z, void *src);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void cam_compute_view_direction(void *, void *, int);
extern char *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
typedef int L_34730TI __attribute__((mode(TI)));
extern L_34730TI hero_copy_vector_to_out(int, L_34730TI *);
typedef int TI __attribute__((mode(TI)));
extern TI hero_copy_vector_to_out(int, TI *);

char *moby_spawn_directed_pal(void *a0, void *a1, void *a2)
{
    TI128 localA;
    TI128 localB;
    char *object;
    State_332440 *state;
    int result;

    cam_compute_view_direction(a1, &localA, 1);
    object = CreateMoby(0xEAA);
    if (object != 0) {
        state = *(State_332440 **)(object + 0x68);
        state->f10 = 0x43;
        *(unsigned char *)(object + 0x30) = 0xFF;
        *(short *)(object + 0x32) = 0xFF;
        *(unsigned char *)(object + 0x20) = 0;
        qcopy(object + 0x10, a1);
        qcopy(state, a2);
        state->f18 = 0;
        state->f14 = 0;
        vec_scale_to_length(&localB, a2, 1.0f);
        qcopy(object + 0xC0, &localB);
        FastVecCross(object + 0xD0, object + 0xC0, &localA);
        vec_scale_to_length(object + 0xD0, object + 0xD0, 1.0f);
        FastVecCross(object + 0xE0, object + 0xD0, object + 0xC0);
        *(float *)(object + 0xCC) = *(float *)(object + 0xDC) = *(float *)(object + 0xEC) = 0.0f;
        result = part_alloc_effect_slot(object, 1.0f, 1.0f, 1.0f, 0);
        state->f1C = result;
        state->f20 = (int)a0;
    }
    return object;
}

