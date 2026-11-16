#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef int Quadword __attribute__((mode(TI)));
extern u8 *g_moby_l11_table;
extern int g_hero_l11_input_blocked;
extern int g_arena_progress_level;
extern int g_arena_crowd_slot_count __attribute__((sda));
extern float g_arena_crowd_level_low __attribute__((sda));
extern float g_arena_crowd_level_mid __attribute__((sda));
extern float g_arena_crowd_level_high __attribute__((sda));
extern float g_arena_crowd_facing_tolerance __attribute__((sda));
extern int moby_is_state_at_least_2(u8 *);
extern int math_fast_helper_a(float *, float);
extern void moby_start_idle_anim_variant_pal(u8 *);
extern int flag_set_first_pending(u8 *);
extern int math_random_int_below(int);
extern void anim_start_blended_pal(u8 *, int, int, int);
extern void moby_set_state(u8 *, int, int);
extern u8 *arena_get_center_point(u8 *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float FastAddRotations(float, float);

/* Updates an arena crowd member (moby class 4718): it switches between idle, cheering and clapping as the crowd excitement rises and falls (PAL version). */
void arena_crowd_update_pal(u8 *moby) {
    float bounds[4];
    float center[4];
    int *vars = *(int **)(moby + 0x68);
    u8 *target;
    float level, angle, heading, delta;
    int animation;
    if (!moby_is_state_at_least_2(g_moby_l11_table + *vars * 0x100)) return;
    *(Quadword *)center = 0;
    center[0] = *(float *)(moby + 0x10);
    center[1] = *(float *)(moby + 0x14);
    center[2] = *(float *)(moby + 0x18);
    center[3] = 5.0f;
    *(Quadword *)bounds = *(Quadword *)center;
    if (math_fast_helper_a(bounds, 255.0f) <= 0 || g_hero_l11_input_blocked) {
        *(unsigned short *)(moby + 0x32) = 0;
        return;
    }
    *(unsigned short *)(moby + 0x32) = 255;
    moby_start_idle_anim_variant_pal(moby);
    target = (u8 *)(*vars * 0x100 + (int)g_moby_l11_table);
    level = *(float *)(*(u8 **)(target + 0x68) + 0x14C);
    switch (moby[0x20]) {
    case 1:
        if (flag_set_first_pending(moby) && moby[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended_pal(moby, animation, 0, 8);
        }
        if (level > g_arena_crowd_level_high && !math_random_int_below(60)) {
            moby_set_state(moby, 2, -1);
        } else if (level < g_arena_crowd_level_low && !math_random_int_below(60)) {
            moby_set_state(moby, 3, -1);
        }
        break;
    case 2:
        if (flag_set_first_pending(moby)) {
            if (moby[0x43] != math_random_int_below(2) + 2) {
                animation = math_random_int_below(2);
                anim_start_blended_pal(moby, animation + 2, 0, 8);
            }
            return;
        }
        if (level < g_arena_crowd_level_mid && !math_random_int_below(60)) moby_set_state(moby, 1, -1);
        break;
    case 3:
        angle = ((float)(g_arena_progress_level % g_arena_crowd_slot_count) * -6.2831855f) / (float)g_arena_crowd_slot_count + 3.1415927f;
        delta = *(float *)(moby + 0x10) - *(float *)arena_get_center_point(target);
        target = arena_get_center_point(g_moby_l11_table + *vars * 0x100);
        heading = mat_fast_helper_a(delta, *(float *)(moby + 0x14) - *(float *)(target + 4));
        if (FastDiffRots(heading, angle) < g_arena_crowd_facing_tolerance ||
            FastDiffRots(heading, FastAddRotations(angle, 3.1415927f)) < g_arena_crowd_facing_tolerance) {
            if (moby[0x43] != 4) anim_start_blended_pal(moby, 4, 0, 8);
        } else if ((moby[0x60] & 2) && moby[0x43] != math_random_int_below(2)) {
            animation = math_random_int_below(2);
            anim_start_blended_pal(moby, animation, 0, 8);
        }
        if (level > g_arena_crowd_level_mid && !math_random_int_below(60)) moby_set_state(moby, 1, -1);
        break;
    }
}
