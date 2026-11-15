/* Updates the path-constrained position only inside the measured distance gate.
 * The two-dimensional limiter consumes the threshold in the floating argument bank. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L20_001B2AC8 __attribute__((sda));
extern float D_L20_001B23F0 __attribute__((sda));
extern char *D_L20_001C4480[] __attribute__((nosda));

extern int coll_process_hit(float f, char *a, int b, char *c, int d);
extern void moby_vanish_with_effect(char *);
extern void moby_local_to_world_point(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern float vec_length_xy(void *vec);
extern void vec_fast_normalize_helper(void *out, void *in, float magnitude);
extern void FastVecAdd(void *, void *, void *);
extern int path_push_point_away(int index, void *point, void *out, float radius);

/* Pulls the object along its path, and pops it if an object of moby class 4576 is touching it. */
void path_follow_pop_on_touch(char *moby) {
    char *state = *(char **)(moby + 0x68);
    int count;
    int i;

    if (*(int *)(state + 0xAC) != 0) {
        if ((D_L20_001B2AC8 & 7) == (((int)moby >> 8) & 7)) {
            count = coll_process_hit(1.5f, moby + 0x10, 0, moby, 0);
            for (i = 0; i < count; i++) {
                if (*(short *)(D_L20_001C4480[i] + 0xAA) == 0x11E0 /* moby class 4576 */) {
                    moby_vanish_with_effect(moby);
                    return;
                }
            }
        }
    }
    {
        TI128 path_point;
        TI128 offset;
        char *pos = moby + 0x10;

        moby_local_to_world_point(*(char **)(state + 0xA4), (char *)&path_point);
        FastVecSub(&offset, pos, (char *)&path_point);
        if (vec_length_xy(&offset) < D_L20_001B23F0) {
            vec_fast_normalize_helper(&offset, &offset, D_L20_001B23F0);
            FastVecAdd(pos, &offset, &path_point);
            qcopy(state + 0x60, pos);
            path_push_point_away(*(int *)(state + 0xA0), pos, pos, 0.5f);
        }
    }
}
