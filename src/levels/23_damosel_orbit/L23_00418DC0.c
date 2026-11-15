#include "include_asm.h"
#include "names.h"

/* func_L23_00418DC0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int s32;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));

extern void FastVecSub(float *, const float *, const float *);

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecAdd(char *, char *, char *);

extern float fast_vec_dist(char *, char *);

extern char g_hero_position[];

extern int *g_path_lists[];

extern s32 mothership_is_value_not_in_slots(s32 arg0);

/* Picks the nearest entry of the object each measured slot names, and stores the index found. */
void mothership_pick_nearest_path_point(char *moby, s32 onlyAllowed) {
    extern void mothership_push_path_history();
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
    slots = state + 0x230;
    best = 30000.0f;
    vec_scale_to_length((char *)loc.b, (char *)loc.b, 4.0f);
    FastVecAdd((char *)&loc.a, (char *)&loc.a, (char *)loc.b);
    for (i = 0; i < 0x2F; i++) {
        int *obj;
        s32 k;

        if (onlyAllowed != 0 && mothership_is_value_not_in_slots(i) == 0)
            continue;
        obj = g_path_lists[*(int *)(slots + (i << 2))];
        for (k = 0; k < *obj; k++) {
            float d = fast_vec_dist((char *)obj + 0x10 + k * 0x10, (char *)&loc.a);

            if (d < best) {
                best = d;
                mothership_push_path_history(moby, i);
                *(s16 *)(state + 0x396) = k;
            }
        }
    }
}
