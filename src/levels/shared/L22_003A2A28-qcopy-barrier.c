#include "include_asm.h"
#include "names.h"


typedef int s32;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern float func_00282E48(char *, char *);
extern char D_00189EA0[];
extern int *D_L23_001FF300[];

/* Same body as func_L23_00418DC0, with this function's own callees. */
/* Finds the lane point nearest to just ahead of the ship and stores that lane and point as the ship's current spot. */
void func_L22_003A2A28(char *moby, s32 pickBest) {
    extern void func_L22_003A2E10();
    struct {
        TI128 a;
        float b[4];
    } loc;
    char *src = moby + 0x10;
    char *state;
    char *slots;
    float best;
    s32 i;

    state = *(char **)(moby + 0x68);
    loc.a = *(TI128 *)src;
    FastVecSub(loc.b, (float *)src, (float *)gHeroPosition);
    slots = state + 0x2A0;
    best = 30000.0f;
    vec_scale_to_length((char *)loc.b, (char *)loc.b, 4.0f);
    FastVecAdd((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < 0x20; i++) {
        int *obj;
        s32 k;

        if (pickBest != 0 && IsKeyMissingFromList(i) == 0)
            continue;
        obj = gPathLists[*(int *)(slots + (i << 2))];
        for (k = 0; k < *obj; k++) {
            float d = fast_vec_dist((char *)obj + 0x10 + k * 0x10, (char *)&loc.a);

            if (d < best) {
                best = d;
                RememberChosenLane(moby, i);
                *(s16 *)(state + 0x356) = k;
            }
        }
    }
}
