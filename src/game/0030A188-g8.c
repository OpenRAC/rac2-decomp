#include "common.h"

/* Adapted from RAC1 initialize_electric_water_bolt_effect (OpenRAC, GPL-3.0). */
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
extern short g_tether_param_b[] MACRO_ADDR;
extern short g_tether_param_c[] MACRO_ADDR;
extern short g_tether_param_f[] MACRO_ADDR;
extern short g_tether_reset_times[] MACRO_ADDR;
extern short g_tether_x_offsets[] MACRO_ADDR;
extern short g_tether_param_a[] MACRO_ADDR;
extern short g_tether_param_d[] MACRO_ADDR;
extern short g_tether_param_e[] MACRO_ADDR;
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), vec_clear_128(void *);
extern int g_tether_reset_flag __attribute__((sda));
extern float g_tether_reach __attribute__((sda));
extern int g_tether_copy_value __attribute__((sda));
extern int g_beam_halo_color __attribute__((sda));
extern int g_tether_height_phase __attribute__((sda));
extern int g_tether_angle_phase __attribute__((sda));
extern int g_tether_wave_phase __attribute__((sda));
extern int g_tether_flag __attribute__((sda));
extern int g_tether_state_word;
extern short g_tether_slot_timers[4];
extern Vec g_tether_chain_steps[];
extern Vec g_tether_chain_positions[];
extern Vec g_tether_chain_offsets[];
extern int g_tether_chain_heights[];
extern int g_tether_chain_mirror_heights[];
/* Resets the twenty beam chain points to a straight line when the beam starts. */
void InitializeElectricWaterBoltEffect(char *moby) {
    Vec delta, step;
    Vec *vars = *(Vec **)(moby + 0x68);
    int i;
    if (g_tether_reset_flag) {
        g_tether_state_word = g_tether_copy_value;
        g_beam_halo_color = 0x7F2020;
        g_tether_reset_flag = 0;
        g_tether_flag = 0;
        FastVecSub(&delta, vars + 1, vars);
        vec_scale_to_length(&step, &delta, g_tether_reach * 0.05f);
        qcopy(&g_tether_chain_positions[0], vars);
        for (i = 1; i < 20; i++) {
            FastVecAdd(&g_tether_chain_positions[i], &g_tether_chain_steps[i], &step);
            g_tether_chain_heights[i] = 0;
            vec_clear_128(&g_tether_chain_offsets[i]);
            g_tether_chain_mirror_heights[i] = 0;
        }
        { int j; for (j = 0; j < 4; j++) g_tether_slot_timers[j] = -1; }
        g_tether_reset_times[0] = 8;
        g_tether_x_offsets[0] = 4;
        g_tether_param_a[0] = 4;
        g_tether_param_d[0] = 2;
        g_tether_param_e[0] = 4;
        g_tether_param_b[0] = 8;
        g_tether_param_c[0] = 4;
        g_tether_param_f[0] = 2;
        g_tether_height_phase = 0;
        g_tether_angle_phase = 0;
        g_tether_wave_phase = 0;
    }
}
