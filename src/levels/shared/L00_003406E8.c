#include "include_asm.h"
#include "names.h"

extern float func_00283CE0(int a);
extern int func_00283CF0_2(float f);
extern int func_00283D38_1(float, int, int);
extern float func_002A7798(float f);
extern float func_002A7790(float f);
extern void func_00282D30_13(char *a, char *b, float f);
extern void func_00282CC0_13(char *a, char *b, char *c);
extern void func_00300190_1(char *a, char *b);
extern int func_00282978_3(char *p);
extern void func_002B9180_6(char *p);

/* Hand-adapted from func_002C8880. */
/* Updates a puff particle each frame: it moves, fades and grows, then is removed when its time runs out. */
void func_L00_003406E8(char *particle) {
    float step[4];
    float velocity[4];
    char *motion = particle + 0x20;
    float timeLeft, alphaDrop, alphaStart, progress;
    int color;

    velocity[0] = *(float *)(particle + 0x20);
    velocity[1] = *(float *)(motion + 4);
    velocity[2] = *(float *)(motion + 8);
    velocity[3] = 0;
    func_00300190_1(particle + 0x10, particle + 0x10);
    timeLeft = IntToFloat(*(short *)(particle + 0xA)) / IntToFloat(*(unsigned char *)(motion + 0x11));
    progress = 1.0f - timeLeft;
    if (*(unsigned char *)(motion + 0x13) == 0) {
        color = func_00283D38_1(progress, 0x103080, *(int *)(motion + 0xC));
        *(int *)(particle + 4) = color | (*(unsigned char *)(motion + 0x12) << 24);
        *(float *)(particle + 0xC) = *(float *)(motion + 0x14) + (*(float *)(motion + 0x18) - *(float *)(motion + 0x14)) * progress;
        func_00282D30_13(step, velocity, *(float *)(motion + 0x1C) * EaseOutQuad(progress));
    } else {
        alphaStart = IntToFloat(*(unsigned char *)(motion + 0x12));
        alphaDrop = IntToFloat(*(unsigned char *)(motion + 0x12));
        alphaDrop = alphaDrop * Square(progress);
        *(int *)(particle + 4) = *(int *)(motion + 0xC) | (func_00283CF0_2(alphaStart - alphaDrop) << 24);
        func_00282D30_13(step, velocity, *(float *)(motion + 0x1C));
    }
    func_00282CC0_13(particle + 0x10, step, particle + 0x10);
    *(unsigned char *)(particle + 8) = *(unsigned char *)(particle + 8) + *(unsigned char *)(motion + 0x10);
    if (func_00282978_3(particle + 0xA) != 0) {
        if (*(unsigned char *)(motion + 0x13) == 0) {
            *(unsigned char *)(motion + 0x13) = 1;
            *(unsigned char *)(motion + 0x11) = 0x14;
            *(short *)(particle + 0xA) = 0x14;
        } else {
            func_002B9180_6(particle);
        }
    }
}
