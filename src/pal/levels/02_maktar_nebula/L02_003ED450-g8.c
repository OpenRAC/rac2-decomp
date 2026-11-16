#include "include_asm.h"
#include "names.h"

/* func_PAL_L02_003ED450, the PAL copy of func_L02_003E9040: the same C, where the timer takes
   PAL's 50 Hz scale and is stored after the two zero stores. It is a unit of its own: it needs
   the opt-in quadword-copy profile and its scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier,
   config/cflags.txt), which give retail's grouped `lq`/`sq` with register addresses and keep the
   instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern int g_tether_strands_dirty __attribute__((sda));

extern int g_tether_reset_value __attribute__((sda));

extern float g_tether_strand_length __attribute__((sda));

extern int g_tether_l02_state_word;

extern int g_tether_state_flag;

extern float g_tether_strand_points[20][4];

extern int g_tether_strand_prev_heights[20];

extern float g_tether_strand_sideways[20][4];

extern int g_tether_strand_heights[20];

extern short g_tether_strand_ids[4];

extern short g_tether_strand_lengths[8] __attribute__((sda));

extern int g_tether_l02_height_phase __attribute__((sda));

extern int g_tether_lateral_phase __attribute__((sda));

extern int g_tether_l02_wave_phase_2 __attribute__((sda));

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern void vec_clear_128(void *);

void func_PAL_L02_003ED450(char *arg0) {
    char *state;
    float v0[4];
    float v1[4];
    int i;
    int j;
    short m1;

    state = *(char **)(arg0 + 0x68);
    if (g_tether_strands_dirty != 0) {
        g_tether_strands_dirty = 0;
        g_tether_state_flag = 0;
        g_tether_l02_state_word = (g_tether_reset_value * 5 + 2) / 6;
        FastVecSub(v0, state + 0x30, state + 0x20);
        vec_scale_to_length(v1, v0, g_tether_strand_length * 0.05f);
        *(TI128 *)g_tether_strand_points[0] = *(TI128 *)(state + 0x20);
        for (i = 1; i < 20; i++) {
            FastVecAdd(g_tether_strand_points[i], g_tether_strand_points[i - 1], v1);
            g_tether_strand_prev_heights[i] = 0;
            vec_clear_128(g_tether_strand_sideways[i]);
            g_tether_strand_heights[i] = 0;
        }
        m1 = -1;
        for (j = 3; j >= 0; j--)
            g_tether_strand_ids[j] = m1;
        g_tether_strand_lengths[0] = 8;
        g_tether_strand_lengths[4] = 4;
        g_tether_strand_lengths[1] = 4;
        g_tether_strand_lengths[2] = 8;
        g_tether_strand_lengths[5] = 2;
        g_tether_strand_lengths[6] = 4;
        g_tether_strand_lengths[3] = 4;
        g_tether_strand_lengths[7] = 2;
        g_tether_l02_height_phase = 0;
        g_tether_lateral_phase = 0;
        g_tether_l02_wave_phase_2 = 0;
    }
}
