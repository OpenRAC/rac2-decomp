#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
extern u8 g_barlow_trigger_started;
extern u8 g_barlow_start_trigger_data;
extern u8 g_inventory_have_flags[] __attribute__((sda));
extern u8 g_game_flag_table[];
extern s32 g_game_tick_counter[] __attribute__((sda));
extern u8 *g_linked_record_table[] __attribute__((sda));
extern u8 g_hero_position[];
extern s32 func_342228(void *moby, void *a1);
extern s32 req_push_queue(u8 *moby, s32 a1);
extern s32 req_launch_queued(void *moby);
extern float math_spring_float_to_goal(float *moby, float *a1, float f12, float f13, float f14, float f15);
extern int PlayMobySound(s32 moby, s32 a1, char *a2);
extern u8 g_moby_group_flags[];
extern u8 g_request_l04_queue[];
extern u8 g_tether_zero_vec[];
extern f32 fast_vec_dist(void *, void *);
extern f32 IntToFloat(int);
extern f32 math_fabs(f32);
extern u8 g_hero_position[];
extern u8 g_str_linked_groups_debug_a[];
extern u8 g_str_linked_groups_debug_b[];
extern u8 g_barlow_l04_path_points_a[] __attribute__((sda));
extern u8 g_barlow_l04_path_points_b[] __attribute__((sda));
extern u8 g_barlow_path_points_c[] __attribute__((sda));
extern u8 g_barlow_path_points_d[] __attribute__((sda));
extern u8 g_barlow_path_points_e[] __attribute__((sda));
extern u8 g_barlow_l04_path_vectors_b[] __attribute__((sda));
extern u8 g_barlow_l04_path_vectors_d[] __attribute__((sda));
extern u8 g_barlow_path_vectors_e[] __attribute__((sda));
extern u8 g_barlow_path_lengths_a[] __attribute__((sda));
extern u8 g_barlow_path_lengths_b[] __attribute__((sda));
extern u8 g_barlow_path_lengths_c[] __attribute__((sda));
extern u8 g_barlow_path_lengths_d[] __attribute__((sda));
extern u8 g_barlow_path_lengths_e[] __attribute__((sda));
extern u8 g_barlow_path_lengths_f[] __attribute__((sda));
extern u8 g_barlow_path_lengths_g[] __attribute__((sda));
extern u8 g_barlow_path_starts_a[] __attribute__((sda));
extern u8 g_barlow_path_starts_b[] __attribute__((sda));
extern u8 g_barlow_path_starts_c[] __attribute__((sda));
extern u8 g_barlow_path_starts_d[] __attribute__((sda));
extern u8 g_barlow_path_starts_e[] __attribute__((sda));
extern u8 g_barlow_path_starts_f[] __attribute__((sda));
extern u8 g_barlow_path_starts_g[] __attribute__((sda));
extern u8 g_barlow_path_total_a[] __attribute__((sda));
extern u8 g_barlow_path_total_b[] __attribute__((sda));
extern u8 g_barlow_path_total_c[] __attribute__((sda));
extern u8 g_barlow_path_total_d[] __attribute__((sda));
extern u8 g_barlow_path_total_e[] __attribute__((sda));
extern u8 g_barlow_path_total_f[] __attribute__((sda));
extern u8 g_barlow_path_total_g[] __attribute__((sda));
extern u8 g_barlow_path_vectors_a[];
extern u8 g_barlow_l04_path_vectors_b_2[];
extern u8 g_barlow_path_vectors_c[];
extern u8 g_barlow_l04_path_vectors_d_2[];
extern u8 g_barlow_l04_path_points_a_2[];
extern u8 g_barlow_l04_path_points_b_2[];
extern f32 func_30F468(f32 a, f32 b);
extern f32 func_30FE88(f32 a, f32 b);
extern f32 func_30FE40(f32 a, f32 b);
extern f32 FastDiffRots(f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);

/* func_L04_00423258 is in L04_00423258-g8.c. */
/* Counts the object's state up, easing its timer down while it is over the
   limit, and hands the level's recorder the object's channel when it runs out. */
void barlow_lift_update_pal(u8 *moby) {
    u32 *vars = *(u32 **)(moby + 0x68);

    if (moby[0x20] == 0)
        moby[0x20] = 1;
    if (moby[0x20] == 2) {
        f32 height = *(f32 *)(moby + 0x18);
        if (height >= 3e+01f)
            *(f32 *)(moby + 0x18) = height - 0.34000003f;
        if (*(f32 *)(moby + 0x18) < 3e+01f)
            moby[0x20] = 4;
    }
    if (moby[0x20] == 3) {
        math_spring_float_to_goal((f32 *)(moby + 0x18), (f32 *)vars, 55.0f,
                      0.012f, 0.020000001f,
                      0.54f);
        if (55.0f <= *(f32 *)(moby + 0x18)) {
            PlayMobySound(0, 0, (char *)moby);
            vars[1] = 0;
            moby[0x20] = 1;
        }
    }
}

