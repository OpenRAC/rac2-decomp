#include "common.h"

extern void vec_transform_or_copy(void *, void *);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int FastTweenColor(float, int, int);
extern float math_ease_out_quad(float);
extern float math_square(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int FastDecTimer(void *);
extern void part_kill(void *);

/* Updates a flying particle: it changes colour and speed over its life, then fades out over 20 more frames and is removed. */
void part_update_flying(char *particle) {
    float change[4];
    float direction[4];
    char *params = particle + 0x20;
    float lifeLeft, fade, startAlpha, progress;
    int color;

    direction[0] = *(float *)(particle + 0x20);
    direction[1] = *(float *)(params + 4);
    direction[2] = *(float *)(params + 8);
    direction[3] = 0;
    vec_transform_or_copy(particle + 0x10, particle + 0x10);
    lifeLeft = IntToFloat(*(short *)(particle + 0xA)) / IntToFloat(*(unsigned char *)(params + 0x11));
    progress = 1.0f - lifeLeft;
    if (*(unsigned char *)(params + 0x13) == 0) {
        color = FastTweenColor(progress, 0x103080, *(int *)(params + 0xC));
        *(int *)(particle + 4) = color | (*(unsigned char *)(params + 0x12) << 24);
        *(float *)(particle + 0xC) = *(float *)(params + 0x14) + (*(float *)(params + 0x18) - *(float *)(params + 0x14)) * progress;
        FastVecScale(change, direction, *(float *)(params + 0x1C) * math_ease_out_quad(progress));
    } else {
        startAlpha = IntToFloat(*(unsigned char *)(params + 0x12));
        fade = IntToFloat(*(unsigned char *)(params + 0x12));
        fade = fade * math_square(progress);
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
            part_kill(particle);
        }
    }
}
