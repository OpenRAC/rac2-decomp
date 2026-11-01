#include "include_asm.h"

typedef struct {
    int a;
    int b;
} L02Pair;
typedef struct {
    float f[2];
} L02Pair2;
extern L02Pair2 D_L02_001AFE20;
extern L02Pair D_L02_001AFE28;
extern L02Pair D_L02_001AFE30;
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
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
void func_PAL_L02_003C8A18(L02Owner *self)
{
    char *state = self->state;
    L02Pair2 turn = D_L02_001AFE20;
    L02Pair low = D_L02_001AFE28;
    L02Pair high = D_L02_001AFE30;
    float *angle = (float *)(state + 0x128);
    float *step = turn.f;
    int i;
    int j;
    float a;
    float b;
    float t;

    for (i = 1; i >= 0; i--) {
        *angle = func_00283B98(*angle, *step * 0.0003490659f);
        angle++;
        step++;
    }
    if (self->kind == 5) {
        t = func_00283198(*(float *)(state + 0x128));
        t = t + func_00283198(*(float *)(state + 0x12C));
        t = t * 0.25f;
        self->tint = func_00283D38(high.a, high.b, t + 0.5f);
    } else {
        a = func_00283198(*(float *)(state + 0x128)) * 0.5f + 0.5f;
        b = func_00283198(*(float *)(state + 0x12C)) * 0.5f + 0.5f;
        if (a < b)
            a = b;
        {
            float u = a;
            for (j = 2; j >= 0; j--)
                u = u * a;
            self->tint = func_00283D38(low.a, low.b, u);
        }
    }
}
