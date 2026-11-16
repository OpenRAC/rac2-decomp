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

/* Spawns a blue and a red sparkle at each of the 50 trail points and pushes each point back along the hero target
   facing (PAL: 50 points). */
void part_init_trail_sparkle_pairs_pal(void) {
    s8 zero[16];
    s8 direction[16];
    s32 i;
    s32 color_alpha;
    s8 *point;
    s8 *sparkle;
    s8 *hero;
    f32 red_size;

    i = 0;
    vec_clear_128(zero);
    do {
        color_alpha = math_random_int_range(0, 0x6F) << 24;
        point = g_trail_sparkle_points + i * 16;
        sparkle = part_spawn_ground_effect(point, 0xA, color_alpha | 0x7F2020, 0, 1, zero, 0, g_trail_sparkle_size * 0.5f, g_trail_sparkle_size, 0.0f);
        if (sparkle != NULL) {
            *(s8 *)(sparkle + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        red_size = g_trail_sparkle_red_size;
        sparkle = part_spawn_ground_effect(point, 0xA, color_alpha | 0xFF4040, 1, 1, zero, 0, red_size * 0.5f, red_size, 0.0f);
        if (sparkle != NULL) {
            *(s8 *)(sparkle + 9) = (s8)(FloatToInt(4.0f) + 0x70);
        }
        i += 1;
        hero = g_hero_state;
        moby_get_facing_direction(*(s32 *)(hero + 0x2290) + 0x10, direction);
        vec_scale_to_length(direction, direction, -0.004f);
        FastVecAdd(point, point, direction);
    } while (i < 0x32);
}
