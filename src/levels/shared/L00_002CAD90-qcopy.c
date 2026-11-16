#include "include_asm.h"
#include "names.h"
typedef int Position __attribute__((mode(TI)));
extern char g_hero_state[];
extern float g_hero_ground_height;
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int CollLine(void *, void *, int, void *, int);
/* Checks whether there is a ledge or step just in front of the hero that it can step onto. */
int hero_check_step_ahead(void)
{
    char *base = g_hero_state;
    float first[4], second[4];
    float t;
    if ((unsigned char)base[0x22C3] == 2) return 0;
    if (*(float *)(base + 0x174) < *(float *)(base + 0x264) * 0.05f) return 0;
    t = FastDiffRots(mat_fast_helper_a(*(float *)(base + 0x110), *(float *)(base + 0x114)), *(float *)(base + 0x98));
    if (0.5235988497734069824f < t) return 0;
    *(Position *)first = *(Position *)(base + 0x80);
    first[0] += math_fast_sin_or_cos_a(*(float *)(base + 0x98)) * *(float *)(base + 0x264) * 0.75f;
    first[1] += math_fast_sin_or_cos_b(*(float *)(base + 0x98)) * *(float *)(base + 0x264) * 0.75f;
    *(Position *)second = *(Position *)first;
    first[2] += 0.47f;
    second[2] -= 1.0f;
    if (!CollLine(first, second, 2, *(void **)(base + 0x2290), 0)) return 0;
    t = g_hero_ground_height - *(float *)(base + 0x88);
    if (t < 0.37f) {
        if (-1.0f < t) return 1;
        else return 0;
    }
    return 0;
}
