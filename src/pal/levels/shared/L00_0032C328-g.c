#include "include_asm.h"

#include "common.h"
typedef int V4TI_F36d8a248 __attribute__((mode(TI)));
typedef union { float f[4]; V4TI_F36d8a248 q; } B1320Vec;
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00283698(void *, void *);
extern void func_PAL_L00_003281C0(void *, int, float);
extern void func_0029F648(void *, void *, void *);
extern void func_002E5CF8(int, int, void *);
extern float func_002A7878(float, float);
extern char *func_PAL_002735D0(void *, int, int, int, void *, void *, void *, int, float, float);
extern void func_002830C0(void *, void *, void *);
extern void func_L00_002EE078(void *, void *, void *);
extern void func_L00_002EE058(void *, void *, void *);

/* Transform and scatter the pieces of an object, remapping their positions into a box. */
void func_PAL_L00_0032C600(char *object, float *box, float *speed, float *spread,
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
    func_00282D30(&scaled, object, 1.0f / 1024.0f);
    func_00283698(inverse, object + 0xC0);
    *(short *)(object + 0x7C) = 0;
    *(int *)(object + 0x98) = 0;
    if ((flags ^ 1) & 1) func_PAL_L00_003281C0(object, 1, 0.0f);
    if (flags & 16) func_PAL_L00_003281C0(object, 9, 0.0f);
    func_0029F648(object, &first, &count);
    if (event != -1) func_002E5CF8(event, 0, object);
    for (i = 0; i < count; ++i) {
        piece = &storage.pieces[i];
        *piece = 0;
        if (skip == i || (((mask >> i) ^ 1) & 1)) continue;
        a = func_002A7878(spread[0], spread[1]);
        b = func_002A7878(speed[0], speed[1]);
        if ((types >> i) & 1)
            *piece = func_PAL_002735D0(object, 2, *(short *)(object + 0xAA), i, object + 0x10,
                                   object + 0xF0, &position, selector, b, a);
        else
            *piece = func_PAL_002735D0(object, 1, *(short *)(object + 0xAA), i, object + 0x10,
                                   object + 0xF0, &position, selector, b, a);
        if (owner) *(void **)((*piece) + 0x64) = owner;
        state = *(char **)((*piece) + 0x68);
        func_00282CC0(&delta, state + 0x20, (*piece) + 0x10);
        func_00282CF0(&position, &delta, &scaled);
        if (!(flags & 8)) func_002830C0(&position, &position, inverse);
        func_L00_002EE078(&low, &low, &position);
        func_L00_002EE058(&high, &high, &position);
    }
    for (i = 0; i < count; ++i) {
        char *current = storage.pieces[i];
        if (!current) continue;
        state = *(char **)(current + 0x68);
        func_00282CC0(&delta, state + 0x20, current + 0x10);
        func_00282CF0(&position, &delta, &scaled);
        func_002830C0(&position, &position, inverse);
        position.f[0] = (box[0] + (position.f[0] - low.f[0]) / (high.f[0] - low.f[0]) * (box[4] - box[0])) * (0.020000001f);
        position.f[1] = (box[1] + (position.f[1] - low.f[1]) / (high.f[1] - low.f[1]) * (box[5] - box[1])) * (0.020000001f);
        position.f[2] = (box[2] + (position.f[2] - low.f[2]) / (high.f[2] - low.f[2]) * (box[6] - box[2])) * (0.020000001f);
        if (!(flags & 8)) func_00283098(&position, &position, object + 0xC0);
        a = func_002A7878(0.25f, 1.0f);
        func_00282D30(&position, &position, a);
        qcopy(state, &position);
    }
}
