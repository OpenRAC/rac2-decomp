#include "common.h"
typedef int EffectQuad __attribute__((mode(TI)));
extern char D_L00_00189F00[];
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char g_ring_pieces[];
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern void lerp_vector(void *, void *, void *, float);
extern int math_fast_float_d(int *);

/* Updates the spinning pieces of an owner: they turn, blend from one position to another, and are freed when their time is over. */
void part_update_ring_pieces(char *owner)
{
    float delta[4];
    int i;
    char *table = g_ring_pieces;
    char *origin = D_L00_00189F00;
    for (i = 0; i < 12; i++) {
        char *piece = table + i * 0xB0;
        float ratio;
        if (*(char **)(piece + 0x9C) != owner) continue;
        FastVecSub(delta, (float *)(piece + 0x40), piece + 0x20);
        *(EffectQuad *)(piece + 0x20) = *(EffectQuad *)origin;
        FastVecAdd(piece + 0x40, piece + 0x20, delta);
        if (*(int *)(piece + 0xA0)) {
            *(float *)(piece + 0x50) = FastAddRotations(*(float *)(piece + 0x50), *(float *)(piece + 0x5C) * 100.0f);
            *(float *)(piece + 0x54) = FastAddRotations(*(float *)(piece + 0x54), *(float *)(piece + 0x60) * 100.0f);
            *(float *)(piece + 0x58) = FastAddRotations(*(float *)(piece + 0x58), *(float *)(piece + 0x64) * 100.0f);
            *(float *)(piece + 0x74) = FastAddRotations(*(float *)(piece + 0x74), *(float *)(piece + 0x80) * 100.0f);
            *(float *)(piece + 0x78) = FastAddRotations(*(float *)(piece + 0x78), *(float *)(piece + 0x84) * 100.0f);
            *(float *)(piece + 0x7C) = FastAddRotations(*(float *)(piece + 0x7C), *(float *)(piece + 0x88) * 100.0f);
        } else {
            *(float *)(piece + 0x50) = FastAddRotations(*(float *)(piece + 0x50), *(float *)(piece + 0x5C) * 50.0f);
            *(float *)(piece + 0x54) = FastAddRotations(*(float *)(piece + 0x54), *(float *)(piece + 0x60) * 50.0f);
            *(float *)(piece + 0x58) = FastAddRotations(*(float *)(piece + 0x58), *(float *)(piece + 0x64) * 50.0f);
            *(float *)(piece + 0x74) = FastAddRotations(*(float *)(piece + 0x74), *(float *)(piece + 0x80) * 50.0f);
            *(float *)(piece + 0x78) = FastAddRotations(*(float *)(piece + 0x78), *(float *)(piece + 0x84) * 50.0f);
            *(float *)(piece + 0x7C) = FastAddRotations(*(float *)(piece + 0x7C), *(float *)(piece + 0x88) * 50.0f);
        }
        *(float *)(piece + 0) = math_fast_sin_or_cos_a(*(float *)(piece + 0x50)) * *(float *)(piece + 0x68);
        *(float *)(piece + 4) = math_fast_sin_or_cos_b(*(float *)(piece + 0x54)) * *(float *)(piece + 0x6C);
        *(float *)(piece + 8) = -math_fast_sin_or_cos_b(*(float *)(piece + 0x58)) * *(float *)(piece + 0x70);
        *(float *)(piece + 0x10) = math_fast_sin_or_cos_a(*(float *)(piece + 0x74)) * *(float *)(piece + 0x8C);
        *(float *)(piece + 0x14) = math_fast_sin_or_cos_b(*(float *)(piece + 0x78)) * *(float *)(piece + 0x90);
        *(float *)(piece + 0x18) = -math_fast_sin_or_cos_b(*(float *)(piece + 0x7C)) * *(float *)(piece + 0x94);
        ratio = IntToFloat(*(int *)(piece + 0xA0));
        ratio /= IntToFloat(*(int *)(piece + 0xA4));
        lerp_vector(piece + 0x30, piece + 0x20, piece + 0x40, 1.0f - ratio);
        if (math_fast_float_d((int *)(piece + 0xA0))) {
            if (*(int *)(piece + 0xA8) == 0) *(int *)(piece + 0xA8) = 1;
            if (math_fast_float_d((int *)(piece + 0x98))) *(int *)(piece + 0x9C) = 0;
        }
    }
}
