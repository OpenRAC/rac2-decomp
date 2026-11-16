#include "common.h"
extern short g_lock_on_param_c[] MACRO_ADDR;
extern short g_lock_on_param_d[] MACRO_ADDR;
extern short g_lock_on_param_h[] MACRO_ADDR;
extern short g_lock_on_param_a[] MACRO_ADDR;
extern short g_lock_on_param_e[] MACRO_ADDR;
extern short g_lock_on_param_b[] MACRO_ADDR;
extern short g_lock_on_param_f[] MACRO_ADDR;
extern short g_lock_on_param_g[] MACRO_ADDR;
typedef struct { float f[4]; } __attribute__((aligned(16))) Vec;
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float), vec_clear_128(void *);
extern int g_current_map_index, g_current_game_mode;
extern Vec g_beam_level_params_first[], g_beam_level_params_second[];
extern int g_beam_reset_flag __attribute__((sda));
extern float g_beam_reach __attribute__((sda));
extern int g_beam_copy_value __attribute__((sda));
extern int g_ribbon_halo_color __attribute__((sda));
extern int g_beam_state_word_a __attribute__((sda));
extern int g_beam_state_word_b __attribute__((sda));
extern int g_beam_state_word_c __attribute__((sda));
extern int g_lock_on_flag __attribute__((sda));
extern int g_lock_on_state_word;
extern short g_lock_on_slot_ids[4];
extern Vec g_beam_ribbon_points[];
extern Vec g_beam_ribbon_vecs[];
extern int g_beam_ribbon_ints_a[];
extern int g_beam_ribbon_ints_b[];
/* Same family as func_0030A188 (RAC1 initialize_electric_water_bolt_effect). */
/* Resets the twenty beam chain points to a straight line when the beam starts (level-specific version). */
void InitializeBoltPointChain(char *moby) {
    Vec delta, step;
    Vec *vars = *(Vec **)(moby + 0x68);
    int i;
    Vec *points;
    if (g_current_map_index == 1 && g_current_game_mode == 2) vars = g_beam_level_params_first;
    if (g_current_map_index == 20 && g_current_game_mode == 2) vars = g_beam_level_params_second;
    if (g_beam_reset_flag) {
        g_lock_on_state_word = g_beam_copy_value;
        g_beam_reset_flag = 0;
        g_lock_on_flag = 0;
        FastVecSub(&delta, vars + 1, vars);
        vec_scale_to_length(&step, &delta, g_beam_reach * 0.05f);
        points = g_beam_ribbon_points;
        qcopy(points, vars);
        for (i = 1; i < 20; i++) {
            FastVecAdd(&points[i], &points[i - 1], &step);
            g_beam_ribbon_ints_a[i] = 0;
            vec_clear_128(&g_beam_ribbon_vecs[i]);
            g_beam_ribbon_ints_b[i] = 0;
        }
        { short empty = -1; int j; for (j = 3; j >= 0; j--) g_lock_on_slot_ids[j] = empty; }
        g_lock_on_param_a[0] = 8;
        g_lock_on_param_e[0] = 4;
        g_lock_on_param_b[0] = 4;
        g_lock_on_param_f[0] = 2;
        g_lock_on_param_g[0] = 4;
        g_lock_on_param_c[0] = 8;
        g_lock_on_param_d[0] = 4;
        g_lock_on_param_h[0] = 2;
        g_beam_state_word_a = 0;
        g_beam_state_word_b = 0;
        g_beam_state_word_c = 0;
    }
}
