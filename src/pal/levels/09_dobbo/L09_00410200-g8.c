#include "include_asm.h"

#include "common.h"
extern u8 *D_L09_001B285C_1;
extern u16 *g_track_entry_table[];
extern int math_random_int_below(int a);
extern int math_random_int_range(int a, int b);
extern void moby_set_light_color(char *moby, int a1);
extern float FastAddRotations(float a, float b);
extern float math_fast_sin_or_cos_a(float a);
extern float math_fast_sin_or_cos_b(float a);
extern int FloatToInt(float a);
extern void vec_scale_to_length(float f12, void *moby, void *a1);
extern int g_dobbo_spin_anim_id __attribute__((sda));
extern int D_L09_001B15B8_4[] MACRO_ADDR;
extern float g_dobbo_spin_turn_rate __attribute__((sda));
extern float g_dobbo_spin_radius __attribute__((sda));
extern int g_dobbo_spin_scale __attribute__((sda));
extern u8 g_dobbo_spin_angle_base __attribute__((sda));
extern u8 g_moby_nibble_table[];
extern u8 g_level_progress_flags[];
extern u8 g_collection_progress_flags[] __attribute__((sda));

/* Update for the Giant Clank Pad (moby class 3712): it picks a light colour and turns its spinning light (PAL: 50 Hz rates). */
void giant_l09_clank_pad_update_pal(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    char *basis;
    float spin_vec[3];
    int n;
    float count;
    int light_id;
    if (math_random_int_below(7)) {
        light_id = g_dobbo_spin_anim_id;
    } else {
        light_id = D_L09_001B15B8_4[1];
    }
    moby_set_light_color(moby, light_id);
    basis = moby + 0xC0;
    *(float *)(vars + 0x10) = FastAddRotations(*(float *)(vars + 0x10), g_dobbo_spin_turn_rate * 0.0003490659f);
    spin_vec[0] = math_fast_sin_or_cos_a(*(float *)(vars + 0x10)) * g_dobbo_spin_radius;
    spin_vec[1] = math_fast_sin_or_cos_b(*(float *)(vars + 0x10)) * g_dobbo_spin_radius;
    spin_vec[2] = 0;
    count = (float)g_dobbo_spin_scale;
    *(float *)(moby + 0xF0) = spin_vec[0];
    *(float *)(moby + 0xF4) = spin_vec[1];
    n = FloatToInt(count * (*(float *)vars + *(float *)(vars + 4)) * 0.5f);
    *(u8 *)(moby + 0x23) = g_dobbo_spin_angle_base + n + math_random_int_range(-9, 9);
    *(u16 *)(moby + 0x34) |= 0x800;
    euler_rotation_basis(basis, moby + 0xF0);
    vec_scale_to_length(*(float *)vars, basis, basis);
    vec_scale_to_length(*(float *)(vars + 4), moby + 0xD0, moby + 0xD0);
}
