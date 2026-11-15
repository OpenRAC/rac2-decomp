#include "include_asm.h"
#include "names.h"

/* func_L02_003D5CF0 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void FastVecSub(void *, void *, void *);

extern float FastVecLength(void *);

extern void vec_scale_to_length(char *, char *, float);

extern void FastVecAdd(void *, void *, void *);

extern char *part_spawn_chain_link(void *, char *, int, float);

/* Lays a line of effect nodes from a start point to an end point, one every step, and returns the first node. */
char *chainblade_spawn_effect_trail(char *start, char *end, float step) {
    float v[4];
    float diff[4];
    char *first = 0;
    char *node = 0;
    float len;
    float t;

    FastVecSub(diff, end, start);
    len = FastVecLength(diff);
    vec_scale_to_length((char *)diff, (char *)diff, step);
    *(TI128 *)v = *(TI128 *)start;
    for (t = 0.0f; t < len; t += step) {
        node = part_spawn_chain_link(v, node, 0, step * 1.3f);
        if (node != 0) {
            if (first == 0) first = node;
        }
        FastVecAdd(v, v, diff);
    }
    return first;
}
