/* func_PAL_L06_003E93C8, the PAL copy of func_L06_003E5D30: the same C, where expr 0.016666668f becomes 0.020000001f. */
#include "common.h"
typedef struct { float f[4]; } __attribute__((aligned(16))) L06GridVector;
typedef struct {
    L06GridVector point[4][30][20];
    L06GridVector velocity[4][30][20];
    int timer[4][30];
    float phase;
} L06Grid;
extern int g_current_map_index;
extern u8 g_screen_mode_flag[] NOT_SDA;
extern int g_ripple_grid_duration;
extern int g_ripple_grid_fade_start;
extern float g_ripple_phase_speed __attribute__((sda));
extern float g_ripple_grid_size __attribute__((sda));
extern float g_ripple_random_speed __attribute__((sda));
extern void moby_mark_spawned(void *);
extern int math_fast_float_d(int *);
extern void vec_clear_128(void *);
extern void vec_random_direction(void *, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);

void func_PAL_L06_003E93C8(u8 *moby)
{
    L06Grid *st = *(L06Grid **)(moby + 0x68);
    L06GridVector temporary[20][10];

    switch (moby[0x20]) {
    case 0:
        if (g_current_map_index == 10 && g_screen_mode_flag[0] == 1) {
            moby_mark_spawned(moby);
            break;
        }
        g_ripple_grid_fade_start = 22;
        g_ripple_grid_duration = 45;
        {
            int i;
            for (i = 0; i < 10; i++) {
                int delay = i * g_ripple_grid_duration / 10;
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

        st->phase += g_ripple_phase_speed * (0.020000001f);
        if (st->phase > 1.0f) st->phase -= 1.0f;
        for (group = 0; group < 4; group++) {
            for (col = 0; col < 10; col++) {
                int hit = math_fast_float_d(&st->timer[group][col]);
                int base = group * 0x2580;
                L06GridVector (*points)[20] = (L06GridVector (*)[20])((char *)st + base);
                L06GridVector (*velocities)[20] = (L06GridVector (*)[20])((char *)st + (base + 0x9600));
                if (hit) {
                    for (row = 0; row < 20; row++) {
                        vec_clear_128(&points[row][col]);
                        ((L06GridVector *)((char *)st + (row * 0x140 + (col * 16 + base))))->f[1] = row * 0.05f * g_ripple_grid_size - g_ripple_grid_size * 0.5f;
                        ((L06GridVector *)((char *)st + (row * 0x140 + (col * 16 + base))))->f[3] = 1.0f;
                        vec_random_direction(&temporary[row][col], 0.0f, g_ripple_random_speed * (0.020000001f));
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
                            FastVecAdd(&velocities[k][col], (L06GridVector *)(before + k * 160), (L06GridVector *)(first + k * 160));
                            FastVecAdd(&velocities[k][col], &velocities[k][col], column[k + 1]);
                            FastVecScale(&velocities[k][col], &velocities[k][col], 0.333f);
                        }
                    }
                    st->timer[group][col] = g_ripple_grid_duration;
                } else {
                    int k;
                    for (k = 1; k < 19; k++) {
                        FastVecAdd(&points[k][col], &points[k][col], &velocities[k][col]);
                    }
                }
            }
        }
        break;
    }
    }
}
