/* func_PAL_L06_003E93C8, the PAL copy of func_L06_003E5D30: the same C, where expr 0.016666668f becomes 0.020000001f. */
#include "common.h"
typedef struct { float f[4]; } __attribute__((aligned(16))) L06GridVector;
typedef struct {
    L06GridVector point[4][30][20];
    L06GridVector velocity[4][30][20];
    int timer[4][30];
    float phase;
} L06Grid;
extern int D_001A79F0;
extern u8 D_0018C0D4[] NOT_SDA;
extern int D_L06_001B31B0;
extern int D_L06_001B31B4;
extern float D_L06_001AF718 __attribute__((sda));
extern float D_L06_001AF714 __attribute__((sda));
extern float D_L06_001AF710 __attribute__((sda));
extern void func_0029F338(void *);
extern int func_00282948(int *);
extern void func_00282C88(void *);
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);

void func_PAL_L06_003E93C8(u8 *moby)
{
    L06Grid *st = *(L06Grid **)(moby + 0x68);
    L06GridVector temporary[20][10];

    switch (moby[0x20]) {
    case 0:
        if (D_001A79F0 == 10 && D_0018C0D4[0] == 1) {
            func_0029F338(moby);
            break;
        }
        D_L06_001B31B4 = 22;
        D_L06_001B31B0 = 45;
        {
            int i;
            for (i = 0; i < 10; i++) {
                int delay = i * D_L06_001B31B0 / 10;
                st->timer[0][i] = delay;
                st->timer[1][i] = delay + 11;
                st->timer[2][i] = delay + 23;
                st->timer[3][i] = delay + 34;
            }
        }
        moby[0x20] = 1;
        break;
    case 1: {
        int group, col, row;

        st->phase += D_L06_001AF718 * (0.020000001f);
        if (st->phase > 1.0f) st->phase -= 1.0f;
        for (group = 0; group < 4; group++) {
            for (col = 0; col < 10; col++) {
                int hit = func_00282948(&st->timer[group][col]);
                int base = group * 0x2580;
                L06GridVector (*points)[20] = (L06GridVector (*)[20])((char *)st + base);
                L06GridVector (*velocities)[20] = (L06GridVector (*)[20])((char *)st + (base + 0x9600));
                if (hit) {
                    for (row = 0; row < 20; row++) {
                        func_00282C88(&points[row][col]);
                        ((L06GridVector *)((char *)st + (row * 0x140 + (col * 16 + base))))->f[1] = row * 0.05f * D_L06_001AF714 - D_L06_001AF714 * 0.5f;
                        ((L06GridVector *)((char *)st + (row * 0x140 + (col * 16 + base))))->f[3] = 1.0f;
                        func_002A7A00(&temporary[row][col], 0.0f, D_L06_001AF710 * (0.020000001f));
                    }
                    {
                        int k;
                        /* The three cursors start from separate col * 16 + temporary sums, as
                           retail's do: cse2 must not merge them, combine reduces mirror and
                           offset, and reload_cse joins the two sums with the same operand order. */
                        int mirror = -(col * 16);
                        int offset = col * 16 - 160;
                        L06GridVector (*column)[10] = (L06GridVector (*)[10])(col * 16 + (int)temporary);
                        int first = (int)temporary - mirror;
                        int before = offset + (int)temporary;
                        for (k = 1; k < 19; k++) {
                            func_00282CC0(&velocities[k][col], (L06GridVector *)(before + k * 160), (L06GridVector *)(first + k * 160));
                            func_00282CC0(&velocities[k][col], &velocities[k][col], column[k + 1]);
                            func_00282D30(&velocities[k][col], &velocities[k][col], 0.333f);
                        }
                    }
                    st->timer[group][col] = D_L06_001B31B0;
                } else {
                    int k;
                    for (k = 1; k < 19; k++) {
                        func_00282CC0(&points[k][col], &points[k][col], &velocities[k][col]);
                    }
                }
            }
        }
        break;
    }
    }
}
