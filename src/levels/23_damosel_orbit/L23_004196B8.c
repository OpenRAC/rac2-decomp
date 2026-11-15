#include "include_asm.h"
#include "names.h"

/* func_L23_004196B8 is a unit of its own: it copies 16 bytes through register addresses with
   lq/sq (-frac2-qcopy), and the copy is a scheduling barrier (-frac2-qcopy-barrier), as
   retail's copy macro was. */

typedef signed int s32;

typedef unsigned long long u64;

typedef int TI128 __attribute__((mode(TI)));

/* The level state at +0x68: the 47 list slots start at +0x230. */
typedef struct State_004196B8 {
    char pad0[0x230];
    s32 slot[0x2F]; /* 0x230 */
} State_004196B8;

/* The lists: a count word, then 16-byte points from +0x10. */
extern int *g_path_lists[];

/* Two 64-bit masks per slot. */
extern char g_path_end_masks[];

extern float fast_vec_dist(char *, char *);

/* For each pair of distinct lists among the 47 slots, measures the four distances between their
 * first and last points. A distance under 1.0 sets the pair's bit in the first list's masks
 * (the first mask for the two distances that start at the first list's first point, the second
 * for the two that start at its last point) and snaps that end point of the first list onto the
 * other list's end point. Retail's register order needs a counter of its own for the second
 * loop, and the other list's first point written out at each use: given a name, that pointer
 * lands in the third callee-saved register where retail has it in the first. */
void mothership_link_touching_path_ends(char *moby) {
    State_004196B8 *st = *(State_004196B8 **)(moby + 0x68);
    float d[4];
    s32 i, j, k, m;

    for (i = 0; i < 0x2F; i++) {
        s32 si = st->slot[i];
        int *a = g_path_lists[si];

        *(u64 *)(g_path_end_masks + (si << 4) + 8) = 0;
        *(u64 *)(g_path_end_masks + (si << 4)) = 0;
        for (j = 0; j < 0x2F; j++) {
            int *b = g_path_lists[st->slot[j]];

            if (a == b)
                continue;
            d[0] = fast_vec_dist((char *)a + 0x10, (char *)b + 0x10);
            d[1] = fast_vec_dist((char *)a + 0x10, (char *)b + (b[0] << 4));
            d[2] = fast_vec_dist((char *)a + (a[0] << 4), (char *)b + 0x10);
            d[3] = fast_vec_dist((char *)a + (a[0] << 4), (char *)b + (b[0] << 4));
            for (k = 0; k < 2; k++) {
                if (d[k] < 1.0f) {
                    *(u64 *)(g_path_end_masks + (st->slot[i] << 4)) |= (u64)1 << j;
                    if (k == 0)
                        *(TI128 *)((char *)a + 0x10) = *(TI128 *)((char *)b + 0x10);
                    else
                        *(TI128 *)((char *)a + 0x10) = *((TI128 *)b + b[0]);
                }
            }
            for (m = 2; m < 4; m++) {
                if (d[m] < 1.0f) {
                    *(u64 *)(g_path_end_masks + (st->slot[i] << 4) + 8) |= (u64)1 << j;
                    if (m == 2)
                        *((TI128 *)a + a[0]) = *(TI128 *)((char *)b + 0x10);
                    else
                        *((TI128 *)a + a[0]) = *((TI128 *)b + b[0]);
                }
            }
        }
    }
}
