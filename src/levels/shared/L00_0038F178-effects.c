#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern int D_L00_001B19C8 MACRO_ADDR;
extern void func_00282D30(void *, void *, float);
extern void func_002A7A00(float *, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(Quad *);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float), func_00283CF0(float);
extern void func_002B00D8(void *, float *, float *, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
/* Emits a short-lived particle every eighth frame using the actor's local vector. */
void func_L00_0038F178(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float offset[4], velocity[4], jitter[4];
    float *jitterPoint, *velocityPoint;
    int firstColor, lastColor, kind, duration, size, count;
    if (D_L00_001B19C8 & 7) return;
    jitterPoint = jitter;
    velocityPoint = velocity;
    count = 0;
    do {
        count--;
        FastVecScale(offset, state, 0.5f);
        func_002A7A00(jitterPoint, 0.0f, 0.016666668f);
        FastVecAdd(offset, jitterPoint, offset);
        func_00282C88((Quad *)velocityPoint);
        offset[3] = func_002A7878(0.25f, 0.15f);
        velocity[3] = func_002A7878(0.15f, 0.05f);
        firstColor = FastTweenColor(0x804080FF, 0x8040FFFF, func_002A7878(0.0f, 1.0f));
        lastColor = FastTweenColor(0x80104040, 0x80002080, func_002A7878(0.0f, 1.0f));
        kind = FloatToInt(func_002A7878(0.0f, 1.0f) + 1.0f);
        duration = FloatToInt((func_002A7878(-0.5f, 0.5f) + 1.0f) * 30.0f);
        size = FloatToInt((func_002A7878(-0.5f, 0.5f) + 1.0f) * 10.0f);
        func_002B00D8(actor + 0x10, velocityPoint, velocityPoint, (float)duration * 0.0011111111f);
        func_002BAA28(actor + 0x10, offset, velocityPoint, firstColor, lastColor, kind, duration, size, 0x10019);
    } while (count >= 0);
}
