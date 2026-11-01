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
    int r, k, j;
    float f;

    switch (obj[0x20]) {
    case 0:
        if (D_001A79F0 == 10 && D_0018C0D4 == 1) {
            func_0029F338(obj);
            return;
        }
        D_L06_001B31B0 = 0x2D;
        D_L06_001B31B4 = 0x16;
        for (k = 0; k < 10; k++) {
            int t = k * D_L06_001B31B0 / 10;

            st->timer[0][k] = t;
            st->timer[1][k] = t + 11;
            st->timer[2][k] = t + 23;
            st->timer[3][k] = t + 34;
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
                        func_00282C88(&pos[j][k]);
                        st->pos[r][j][k].f[3] = 1.0f;
                        st->pos[r][j][k].f[1] = (float)j * 0.05f * D_L06_001AF714 - D_L06_001AF714 * 0.5f;
                        func_002A7A00(&buf[j][k], 0.0f, D_L06_001AF710 * (1.0f / 60.0f));
                    }
                    for (j = 1; j < 19; j++) {
                        func_00282CC0(&vel[j][k], &buf[j - 1][k], &buf[j][k]);
                        func_00282CC0(&vel[j][k], &vel[j][k], &buf[j + 1][k]);
                        func_00282D30(&vel[j][k], &vel[j][k], 0.333f);
                    }
                    st->timer[r][k] = D_L06_001B31B0;
                } else {
                    for (j = 1; j < 19; j++)
                        func_00282CC0(&pos[j][k], &pos[j][k], &vel[j][k]);
                }
            }
        }
        break;
    }
}
