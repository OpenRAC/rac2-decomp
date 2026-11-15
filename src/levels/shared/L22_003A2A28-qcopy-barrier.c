#include "include_asm.h"
#include "names.h"


typedef int s32;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern float fast_vec_dist(char *, char *);
extern char g_hero_position[];
extern int *g_path_lists[];

/* Same body as func_L23_00418DC0, with this function's own callees. */
/* Finds the lane point nearest to just ahead of the ship and stores that lane and point as the ship's current spot. */
void lane_store_nearest_point_as_current(char *moby, s32 pickBest) {
    extern void lane_remember_chosen();
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
    FastVecSub(loc.b, (float *)src, (float *)g_hero_position);
    slots = state + 0x2A0;
    best = 30000.0f;
    vec_scale_to_length((char *)loc.b, (char *)loc.b, 4.0f);
    FastVecAdd((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < 0x20; i++) {
        int *obj;
        s32 k;

        if (pickBest != 0 && list_is_key_missing(i) == 0)
            continue;
        obj = g_path_lists[*(int *)(slots + (i << 2))];
        for (k = 0; k < *obj; k++) {
            float d = fast_vec_dist((char *)obj + 0x10 + k * 0x10, (char *)&loc.a);

            if (d < best) {
                best = d;
                lane_remember_chosen(moby, i);
                *(s16 *)(state + 0x356) = k;
            }
        }
    }
}
