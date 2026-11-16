#include "include_asm.h"
#include "names.h"

typedef struct {
    int a;
    int b;
} L02Pair;

typedef struct {
    float f[2];
} L02Pair2;

extern L02Pair2 g_glow_turn_pair;
extern L02Pair g_glow_low_pair;
extern L02Pair g_glow_high_pair;

extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);

typedef struct {
    char pad0[0x20];
    unsigned char kind;
    char pad1[0x68 - 0x21];
    char *state;
    char pad2[0x78 - 0x6C];
    int tint;
} L02Owner;

/* Turns the two angles at state +0x128 towards the pair at D_L02_001AFE20, then tints the
   owner: kind 5 blends from the mean of both angles' sines, any other kind from the larger of
   the two, to the fourth power. */
void part_update_pulsing_glow_tint(L02Owner *self)
{
    char *state = self->state;
    L02Pair2 turn = g_glow_turn_pair;
    L02Pair low = g_glow_low_pair;
    L02Pair high = g_glow_high_pair;
    float *angle = (float *)(state + 0x128);
    float *step = turn.f;
    int i;
    int j;
    float a;
    float b;
    float t;

    for (i = 1; i >= 0; i--) {
        *angle = FastAddRotations(*angle, *step * 0.00029088824f);
        angle++;
        step++;
    }
    if (self->kind == 5) {
        t = math_fast_sin_or_cos_b(*(float *)(state + 0x128));
        t = t + math_fast_sin_or_cos_b(*(float *)(state + 0x12C));
        t = t * 0.25f;
        self->tint = FastTweenColor(high.a, high.b, t + 0.5f);
    } else {
        a = math_fast_sin_or_cos_b(*(float *)(state + 0x128)) * 0.5f + 0.5f;
        b = math_fast_sin_or_cos_b(*(float *)(state + 0x12C)) * 0.5f + 0.5f;
        if (a < b)
            a = b;
        {
            float u = a;
            for (j = 2; j >= 0; j--)
                u = u * a;
            self->tint = FastTweenColor(low.a, low.b, u);
        }
    }
}
