/* 6 November 2026, Codex follow-up: 976/976 bytes, 0/3 USA v1.01 places,
 * own -O2 -G8 -ffunction-sections unit. Retained C improves from 137 to 112
 * differing instruction words, masking only relocation fields. check.py's
 * first difference is now +0x170; the first 368 bytes also pass derive's
 * symbol/address validation independently (a diagnostic, not a linked match).
 * New changes: separate initialization, smoothing and advance counters;
 * initialize the fade period before the lifetime; group the complete reset
 * iteration and the smoothing scale call, retaining the existing y/timer groups.
 * State still spills at 0xC80 and pos/vel use fp/s7. Remaining: strand offset
 * spills at 0xC9C instead of using s6, timer-base setup differs, reset buf
 * strength reduction is inhibited, and reset/smoothing allocation and scheduling
 * differ. The 0xD10 frame and complete initialization/phase prefix are correct.
 * New negative controls: explicit signed/unsigned shared strand offsets with
 * assignment groups, independent clear/output/noise cursors, grouped partial
 * y calculations, separate float stack grid, and four-float vector struct/array
 * views did not improve the retained result. Functional copy measured first in
 * an own unit with the actual 800-float grid (no unused padding): 928/976 bytes.
 * About 200 successful trial compiles, scored only on instruction differences;
 * invalid generated declarations/scopes were rejected, never retained. No
 * volatile, custom asm, aliases, dummy operations or extra locals are needed.
 * Next useful input: a source lifetime that keeps the shared strand offset live
 * without sacrificing the reset buffer cursor's strength reduction. No build
 * was run; final check.py reports 0 of 3 places match.
 */
/* 6 November 2026, round 6: 976/976 bytes, 0/3 USA v1.01 places, same -O2 -G8 unit.
 * Changes from the retained draft: the smoothing loop counts j = 0..17 over
 * vel[j + 1], buf[j], buf[j + 1], buf[j + 2] (retail's buf cursors start at
 * k * 16 + sp, with no hoisted sp + 0xA0); the f[1] store and the timer
 * write are each a one-pass group. The state pointer is now spilled to 0xC80
 * and reloaded as in retail, with pos in $fp and vel in $s7.
 * Left: the strand offset r * 0x2580 is a copy spilled to 0xC9C, not $s6.
 * Cause: the reset store's mult is hoisted in the second loop pass, and
 * cse2 turns it into a copy of the r-body mult. The f[1] group also stops
 * j-loop strength reduction of the buf cursor, which retail has.
 * Tried without gain: no pos/vel pointers (976, state in $s7), pos/vel at k
 * top or per branch, a walking store pointer, grouped pos/vel set-up,
 * groups on the loops, the C88 call, the buffer call or the else loop.
 */
/* 6 November 2026 recheck: retained source is 968/976 bytes, 0/3 USA v1.01
 * places, -O2 -G8 -ffunction-sections. The RAC1 donor jitter_strand_grid_update
 * (src/overlays/l10_orxon/platforms_doors_and_bombthrower.c) confirms the grid
 * shape and separate else-loop counter; transcribing those choices stays 968.
 * Regalloc's byte-identical diagnostic identifies state pseudo 85 (12 refs,
 * live 140, fp) ahead of strand-offset pseudo 159 (3 refs, live 206, spilled).
 * New one-pass groups: smoothing-call group reaches 976 but still keeps state
 * in fp; grouping the column loop or position w store gives 1000, position y
 * store gives 992, and explicit grouped strand-offset computation gives 952.
 * Equal size does not repair allocation. Retain the earlier source; reopen
 * with evidence that changes the strand-offset versus state lifetime/priority.
 */
/* func_L06_003E5D30: near miss, 968/976 bytes, 0 of 3 places (USA v1.01, 1 November 2026).

   Profile: its own `-g8` unit, `-O2 -G8 -ffunction-sections` (the three $gp floats come out
   $gp-relative only under -G8; the level and period words take the `.sdata` macro form).

   Control flow, calls, constants, the 0xC80-byte stack buffer and the frame size follow retail;
   writing the period as `k * D_L06_001B31B0 / 10` gives retail's hoisted 45. What differs is
   allocation: retail spills the state pointer to 0xC80 at entry and keeps the strand offset
   r * 0x2580 in $s6, while here the state pointer takes $fp and the strand offset is spilled,
   so retail's reloads of the state pointer from 0xC80 are missing. Loop 3 also starts its
   buffer pointers from a hoisted sp + 0xA0 instead of retail's (k * 16 + sp) + 0xA0 / 0x140.
   Tried: per-strand pointers for pos/vel/timer, swapping which access goes through `st`,
   declaration orders, a zero-based smoothing loop (944 bytes), -g, -fno-gcse,
   -fno-strength-reduce, -frac2-keep-block-order. */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad quad; float f[4]; } VecE5D30;

/* The object's state: two grids of four strands of 20 x 10 points (30 x 20 allocated), the
   per-cell reset timers and the scroll phase. */
typedef struct {
    VecE5D30 pos[4][30][20];
    VecE5D30 vel[4][30][20];
    int timer[4][30];
    float phase;
} StateE5D30;

extern int D_001A79F0 __attribute__((section(".sdata")));
extern u8 D_0018C0D4 __attribute__((nosda));
extern int D_L06_001B31B0 __attribute__((section(".sdata")));
extern int D_L06_001B31B4 __attribute__((section(".sdata")));
extern float D_L06_001AF710 __attribute__((sda));
extern float D_L06_001AF714 __attribute__((sda));
extern float D_L06_001AF718 __attribute__((sda));
extern void func_0029F338(void *);
extern int func_00282948(int *);
extern void func_00282C88(void *);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

void func_L06_003E5D30(u8 *obj)
{
    VecE5D30 buf[20][10];
    StateE5D30 *st = *(StateE5D30 **)(obj + 0x68);
    int r, k, j, init, smooth, advance;
    float f;

    switch (obj[0x20]) {
    case 0:
        if (D_001A79F0 == 10 && D_0018C0D4 == 1) {
            func_0029F338(obj);
            return;
        }
        D_L06_001B31B4 = 0x16;
        D_L06_001B31B0 = 0x2D;
        for (init = 0; init < 10; init++) {
            int t = init * D_L06_001B31B0 / 10;

            st->timer[0][init] = t;
            st->timer[1][init] = t + 11;
            st->timer[2][init] = t + 23;
            st->timer[3][init] = t + 34;
        }
        obj[0x20] = 1;
        break;
    case 1:
        f = st->phase + D_L06_001AF718 * (1.0f / 60.0f);
        st->phase = f;
        if (f > 1.0f)
            st->phase = f - 1.0f;
        for (r = 0; r < 4; r++) {
            VecE5D30 (*pos)[20] = st->pos[r];
            VecE5D30 (*vel)[20] = st->vel[r];

            for (k = 0; k < 10; k++) {
                if (func_00282948(&st->timer[r][k])) {
                    for (j = 0; j < 20; j++) {
                        do {
                            func_00282C88(&pos[j][k]);
                            st->pos[r][j][k].f[3] = 1.0f;
                            do {
                                st->pos[r][j][k].f[1] = (float)j * 0.05f * D_L06_001AF714 - D_L06_001AF714 * 0.5f;
                            } while (0);
                            func_002A7A00(&buf[j][k], 0.0f, D_L06_001AF710 * (1.0f / 60.0f));
                        } while (0);
                    }
                    for (smooth = 0; smooth < 18; smooth++) {
                        func_00282CC0(&vel[smooth + 1][k], &buf[smooth][k], &buf[smooth + 1][k]);
                        func_00282CC0(&vel[smooth + 1][k], &vel[smooth + 1][k], &buf[smooth + 2][k]);
                        do {
                            func_00282D30(&vel[smooth + 1][k], &vel[smooth + 1][k], 0.333f);
                        } while (0);
                    }
                    do {
                        st->timer[r][k] = D_L06_001B31B0;
                    } while (0);
                } else {
                    for (advance = 1; advance < 19; advance++)
                        func_00282CC0(&pos[advance][k], &pos[advance][k], &vel[advance][k]);
                }
            }
        }
        break;
    }
}
