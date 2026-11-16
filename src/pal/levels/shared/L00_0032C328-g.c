#include "include_asm.h"

#include "common.h"
typedef int V4TI_F36d8a248 __attribute__((mode(TI)));
typedef union { float f[4]; V4TI_F36d8a248 q; } B1320Vec;
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void matrix_from_basis_rows(void *, void *);
extern void part_spawn_scaled_bolts_pal(void *, int, float);
extern void moby_get_anim_entry_count(void *, void *, void *);
extern int PlayMobySound(int, int, void *);
extern float math_random_float_range(float, float);
extern char *cam_moby_create_pal(void *, int, int, int, void *, void *, void *, int, float, float);
extern void transform_vector(void *, void *, void *);
extern void func_L00_002EE078(void *, void *, void *);
extern void func_L00_002EE058(void *, void *, void *);

/* Transforms and scatters the pieces of an object, remapping their positions into a box (PAL). */
void ScatterObjectPieces_pal(char *object, float *box, float *speed, float *spread,
                       int types, int event, int skip, int flags, int mask,
                       unsigned char selector, void *owner)
{
    B1320Vec scaled, delta, position, low, high;
    struct { char *pieces[16]; } storage;
    char inverse[64] __attribute__((aligned(16)));
    int first, count, i;
    char *state;
    char **piece;
    float a, b;
    low.q = 0;
    high.q = 0;
    low.f[2] = low.f[1] = low.f[0] = 10000.0f;
    high.f[2] = high.f[1] = high.f[0] = -10000.0f;
    FastVecScale(&scaled, object, 1.0f / 1024.0f);
    matrix_from_basis_rows(inverse, object + 0xC0);
    *(short *)(object + 0x7C) = 0;
    *(int *)(object + 0x98) = 0;
    if ((flags ^ 1) & 1) part_spawn_scaled_bolts_pal(object, 1, 0.0f);
    if (flags & 16) part_spawn_scaled_bolts_pal(object, 9, 0.0f);
    moby_get_anim_entry_count(object, &first, &count);
    if (event != -1) PlayMobySound(event, 0, object);
    for (i = 0; i < count; ++i) {
        piece = &storage.pieces[i];
        *piece = 0;
        if (skip == i || (((mask >> i) ^ 1) & 1)) continue;
        a = math_random_float_range(spread[0], spread[1]);
        b = math_random_float_range(speed[0], speed[1]);
        if ((types >> i) & 1)
            *piece = cam_moby_create_pal(object, 2, *(short *)(object + 0xAA), i, object + 0x10,
                                   object + 0xF0, &position, selector, b, a);
        else
            *piece = cam_moby_create_pal(object, 1, *(short *)(object + 0xAA), i, object + 0x10,
                                   object + 0xF0, &position, selector, b, a);
        if (owner) *(void **)((*piece) + 0x64) = owner;
        state = *(char **)((*piece) + 0x68);
        FastVecAdd(&delta, state + 0x20, (*piece) + 0x10);
        FastVecSub(&position, &delta, &scaled);
        if (!(flags & 8)) transform_vector(&position, &position, inverse);
        func_L00_002EE078(&low, &low, &position);
        func_L00_002EE058(&high, &high, &position);
    }
    for (i = 0; i < count; ++i) {
        char *current = storage.pieces[i];
        if (!current) continue;
        state = *(char **)(current + 0x68);
        FastVecAdd(&delta, state + 0x20, current + 0x10);
        FastVecSub(&position, &delta, &scaled);
        transform_vector(&position, &position, inverse);
        position.f[0] = (box[0] + (position.f[0] - low.f[0]) / (high.f[0] - low.f[0]) * (box[4] - box[0])) * (0.020000001f);
        position.f[1] = (box[1] + (position.f[1] - low.f[1]) / (high.f[1] - low.f[1]) * (box[5] - box[1])) * (0.020000001f);
        position.f[2] = (box[2] + (position.f[2] - low.f[2]) / (high.f[2] - low.f[2]) * (box[6] - box[2])) * (0.020000001f);
        if (!(flags & 8)) matrix_mul_vec3(&position, &position, object + 0xC0);
        a = math_random_float_range(0.25f, 1.0f);
        FastVecScale(&position, &position, a);
        qcopy(state, &position);
    }
}
