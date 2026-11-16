#include "include_asm.h"

#include "common.h"
#define NULL 0
extern s8 g_trail_sparkle_points[];
extern s8 g_hero_state[];
extern f32 g_trail_sparkle_size __attribute__((sda));
extern f32 g_trail_sparkle_red_size __attribute__((sda));
extern void vec_clear_128(void *);
extern s32 math_random_int_range(s32, s32);
extern void *part_spawn_ground_effect(void *, s32, s32, s32, s32, void *, s32, f32, f32, f32);
extern s32 FloatToInt(f32);
extern void moby_get_facing_direction(s32, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecAdd(void *, void *, void *);

void part_init_trail_sparkle_pairs_pal(void) {
    s8 sp0[16];
    s8 sp10[16];
    s32 s4;
    s32 s3;
    s8 *s1;
    s8 *s0;
    s8 *p;
    f32 t;

    s4 = 0;
    vec_clear_128(sp0);
    do {
        s3 = math_random_int_range(0, 0x6F) << 24;
        s1 = g_trail_sparkle_points + s4 * 16;
        s0 = part_spawn_ground_effect(s1, 0xA, s3 | 0x7F2020, 0, 1, sp0, 0, g_trail_sparkle_size * 0.5f, g_trail_sparkle_size, 0.0f);
        if (s0 != NULL) {
            *(s8 *)(s0 + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        t = g_trail_sparkle_red_size;
        s0 = part_spawn_ground_effect(s1, 0xA, s3 | 0xFF4040, 1, 1, sp0, 0, t * 0.5f, t, 0.0f);
        if (s0 != NULL) {
            *(s8 *)(s0 + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        s4 += 1;
        p = g_hero_state;
        moby_get_facing_direction(*(s32 *)(p + 0x2290) + 0x10, sp10);
        vec_scale_to_length(sp10, sp10, -0.004f);
        FastVecAdd(s1, s1, sp10);
    } while (s4 < 0x32);
}
