#include "include_asm.h"
#include "names.h"

extern float IntToFloat(int a);
extern void FastVecAdd(char *p, char *q, char *r);
extern int FastTweenColor(int, int, float);
extern unsigned char *g_color_blend_textures;

/* blends a sub-object into a position, adds a float field, stores an interpolated value in the
   word at +4 and scales the frame count into a byte table at +2 */
void part_update_color_blend_pal(char *particle)
{
    char *p = particle;
    char *state = particle + 32;
    unsigned int color;
    float duration;

    FastVecAdd(p + 16, p + 16, state);
    if (FastDecTimer(p + 10) != 0) {
        part_kill(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + *(float *)(state + 0x1C);
    duration = IntToFloat(*(int *)(state + 0x18));
    color = FastTweenColor(*(int *)(state + 0x14), *(int *)(state + 0x10),
                      (float)*(short *)(p + 0xA) / duration);
    *(int *)(p + 4) = color;
    if (*(short *)(p + 0xA) < 5) {
        *(int *)(p + 4) = (color & 0xFFFFFF) | (((int)(*(short *)(p + 0xA) * (color >> 24))) / 5 << 24);
    }
    *(unsigned char *)(p + 2) = g_color_blend_textures[((*(int *)(state + 0x18) - *(short *)(p + 0xA)) * 10) / *(int *)(state + 0x18)];
}



#include "common.h"
extern int FastDecTimer(char *p);
extern void part_kill(char *p);
extern int FloatToInt(float f);
extern void FastVecAdd(char *a, char *b, char *c);
extern void FastVecScale(char *a, char *b, float f);

/* decays a float field by 0.04 with a saturating early-out that consults a helper and returns; otherwise adds 12000 to a second field, nudges a third by 0.0484 while it stays below 0.225, merges two 255-scaled byte lanes into a header word, hands a sub-object to two helpers and decrements a byte counter */
void part_update_sparkle_pal(char *p)
{
    char *q = p + 32;
    float v;
    int a, b;
    int h;

    v = *(float *)(q + 28) + (-0.048f);
    *(float *)(q + 28) = v;
    if (v <= 0.0f || FastDecTimer(p + 10) != 0) {
        part_kill(p);
        return;
    }
    *(float *)(p + 12) = *(float *)(p + 12) + 14400.001f;
    if (*(float *)(q + 24) < 0.225f) {
        *(float *)(q + 24) = *(float *)(q + 24) + 0.058080003f;
    }
    a = FloatToInt(*(float *)(q + 24) * 255.0f) & 0xff;
    b = FloatToInt(*(float *)(q + 28) * 255.0f);
    h = *(unsigned short *)(p + 4);
    *(int *)(p + 4) = h | (a << 16) | (b << 24);
    FastVecAdd(p + 16, p + 16, q);
    FastVecScale(q, q, 0.88f);
    *(char *)(p + 8) = *(unsigned char *)(p + 8) - 1;
}

