/* func_L02_002EFB60: needs -frac2-sticky-volatile-refs (reorg stops at the copy's volatile asm); see docs/build/compiler-notes.md. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vec4;
extern int D_L02_001A8D68 __attribute__((sda));
extern float D_L02_001A8D78[] SDATA(D_L02_001A8D78) __attribute__((nosda));
extern int D_L02_001A8D58 __attribute__((sda));
extern int D_L02_001A8D50 __attribute__((sda));
extern float D_L02_001A8D7C __attribute__((nosda));
extern int D_L02_001A8D5C __attribute__((nosda));
extern int D_L02_001A8D60 __attribute__((nosda));
extern int D_L02_001A8D64 __attribute__((nosda));
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282C88(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

/* Throws a burst of colored sparks along a line between two points. Each spark gets a random brightness, position on the line and speed. */
void func_L02_002EFB60(void *owner, void *from, void *to, int count, int *colour, float speed) {
    Vec4 direction;
    Vec4 position;
    Vec4 velocity;
    float gravity = speed * 0.00027777778f;
    float brightness, blend;
    int red, green, blue, firstSprite, secondSprite, i;
    int *rgb = &D_L02_001A8D68;
    if (colour) rgb = colour;
    for (i = 0; i < count; i++) {
        brightness = RandomFloatRange(0.7f, 1.3f);
        red = FloatToInt((float)rgb[0] * brightness);
        green = FloatToInt((float)rgb[1] * brightness);
        blue = FloatToInt((float)rgb[2] * brightness);
        lerp_vector(&direction, from, to, RandomFloatRange(0.0f, 1.0f));
        qcopy(&position, &direction);
        position.f[3] = RandomFloatRange(D_L02_001A8D78[0], D_L02_001A8D7C);
        ClearVector128(&velocity);
        velocity.f[2] = -gravity * (float)(red + green + blue);
        FastVecAdd(&velocity, &velocity, &direction);
        velocity.f[3] = position.f[3];
        blend = RandomFloatRange(0.0f, 1.0f);
        firstSprite = FastTweenColor(D_L02_001A8D58, D_L02_001A8D5C, blend);
        blend = RandomFloatRange(0.0f, 1.0f);
        secondSprite = FastTweenColor(D_L02_001A8D60, D_L02_001A8D64, blend);
        SpawnTrailParticle_002BAA28(owner, &position, &velocity, firstSprite, secondSprite, red, green, blue, D_L02_001A8D50);
    }
}
