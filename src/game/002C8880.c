#include "common.h"

extern void func_00300190(void *, void *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00283D38(float, int, int);
extern float func_002A7798(float);
extern float func_002A7790(float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282978(void *);
extern void func_002B9180(void *);

/* Updates a flying particle: it changes colour and speed over its life, then fades out over 20 more frames and is removed. */
void func_002C8880(char *particle) {
    float change[4];
    float direction[4];
    char *params = particle + 0x20;
    float lifeLeft, fade, startAlpha, progress;
    int color;

    direction[0] = *(float *)(particle + 0x20);
    direction[1] = *(float *)(params + 4);
    direction[2] = *(float *)(params + 8);
    direction[3] = 0;
    TransformVectorOrCopy(particle + 0x10, particle + 0x10);
    lifeLeft = IntToFloat(*(short *)(particle + 0xA)) / IntToFloat(*(unsigned char *)(params + 0x11));
    progress = 1.0f - lifeLeft;
    if (*(unsigned char *)(params + 0x13) == 0) {
        color = FastTweenColor(progress, 0x103080, *(int *)(params + 0xC));
        *(int *)(particle + 4) = color | (*(unsigned char *)(params + 0x12) << 24);
        *(float *)(particle + 0xC) = *(float *)(params + 0x14) + (*(float *)(params + 0x18) - *(float *)(params + 0x14)) * progress;
        FastVecScale(change, direction, *(float *)(params + 0x1C) * EaseOutQuad(progress));
    } else {
        startAlpha = IntToFloat(*(unsigned char *)(params + 0x12));
        fade = IntToFloat(*(unsigned char *)(params + 0x12));
        fade = fade * Square(progress);
        *(int *)(particle + 4) = *(int *)(params + 0xC) | (FloatToInt(startAlpha - fade) << 24);
        FastVecScale(change, direction, *(float *)(params + 0x1C));
    }
    FastVecAdd(particle + 0x10, change, particle + 0x10);
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + *(unsigned char *)(params + 0x10);
    if (FastDecTimer(particle + 0xA) != 0) {
        if (*(unsigned char *)(params + 0x13) == 0) {
            *(unsigned char *)(params + 0x13) = 1;
            *(unsigned char *)(params + 0x11) = 0x14;
            *(short *)(particle + 0xA) = 0x14;
        } else {
            KillParticle(particle);
        }
    }
}
