#include "include_asm.h"

typedef short s16;
extern int D_001A79F0[] __attribute__((sda));
extern int D_L04_001A8FE4[] __attribute__((sda));
typedef struct {
    char pad000[0x274];
    s16 f274;
    char pad276[6];
    float f27C;
    char pad280[0x298 - 0x280];
    float targetHeight;
    char pad29C[0x2A8 - 0x29C];
    float baseHeight;
    char pad2AC[0x314 - 0x2AC];
    int f314;
    int animFrame;
    char pad31C[0x34C - 0x31C];
    int f34C;
} HeightState;

/* Computes the target height offset from the base height, scaled by how far height is above or below base. */
void func_PAL_L04_00417310(void *object, HeightState *state, float height, float base,
                       float factor, float speed, float margin)
{
    float t, extra;

    if (state->f34C >= 7) {
        state->targetHeight = state->baseHeight + speed * 0.00040000002f;
        return;
    }

    if (margin + base < height) {
        if (D_001A79F0[0] == 4 && state->f274 != 0 &&
            state->f314 == -1 && state->animFrame >= 476) {
            t = state->f27C * 8.333333f;
            if (t > 1.0f)
                t = 1.0f;
            else if (t < 0.0f)
                t = 0.0f;
            if (D_L04_001A8FE4[0] >= 2)
                extra = t * 7.0f + 3.5f;
            else
                extra = t * 3.0f + 1.5f;
        } else {
            extra = 0.0f;
        }

        t = (height - base + margin) / (base + margin);
        if (t > 1.0f)
            t = 1.0f;
        if (t < 0.0f)
            t = 0.0f;
        state->targetHeight = state->baseHeight - (speed + extra) * t * 0.00040000002f;
    } else {
        t = (base - height + margin) / base;
        if (t > 1.0f)
            t = 1.0f;
        if (t < 0.0f)
            t = 0.0f;
        t = t * factor;
        state->targetHeight = state->baseHeight + speed * t * 0.00040000002f;
    }
}
