#include "include_asm.h"
#include "names.h"

extern char g_hero_state[];

extern void FastVecScale(char *dst, char *src, float k);

extern void FastVecAdd(void *out, void *in, void *m);

extern float coll_probe_ground_height_below(char *a, int b, float f);

extern float math_fabs(float);

extern void hero_start_target_state(char *a, int b, float f);

#ifndef RAC2_T_V4_5098
#define RAC2_T_V4_5098
typedef int V4_5098 __attribute__((mode(TI)));
#endif

/* Builds a 16-byte probe at a stack local from the shared block and its +0x80 matrix,
   raises the third word by 0.5f, calls the level's float selector with that same 0.5f and
   stores its answer back into the third word, then compares the block's +0x88 against the
   probe: when the difference is not greater than 0.3f the level's own setter runs and the
   probe is copied over the block's +0x80. */
/* Checks that a probe point ahead of the hero has about the same height as the hero. If so it starts a move and stores the point. */
void hero_try_start_probe_move(void)
{
    char *heroBase = g_hero_state;
    char *matrixPtr = heroBase + 0x80;
    V4_5098 probe;
    float heightDiff;

    FastVecScale((char *)&probe, heroBase, -0.75f);
    FastVecAdd(&probe, &probe, matrixPtr);
    *(float *)((char *)&probe + 8) = *(float *)((char *)&probe + 8) + 0.5f;
    *(float *)((char *)&probe + 8) = coll_probe_ground_height_below((char *)&probe, 0, 0.5f);
    heightDiff = math_fabs(*(float *)(heroBase + 0x88) - *(float *)((char *)&probe + 8));
    if (0.3f < heightDiff)
        return;
    hero_start_target_state(matrixPtr, 1, *(float *)(heroBase + 0x98));
    *(V4_5098 *)matrixPtr = probe;
}
