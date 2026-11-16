#include "include_asm.h"

#include "common.h"
extern void vec_clear_128(void *);
extern void vec_random_direction(void *, float, float);
extern float math_random_float_range(float, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern u8 *D_L02_001B359C_tbl[] __asm__("D_L02_001B359C") __attribute__((sda));
typedef struct {
    f32 x;
    f32 y;
} L02Pair_CF1B8;
typedef struct {
    s32 a;
    s32 b;
} L02Range_CF1B8;
extern L02Pair_CF1B8 g_puff_speed_pair;
extern L02Pair_CF1B8 g_puff_size_pair;
extern L02Range_CF1B8 g_puff_kind_range;
typedef struct {
    L02Range_CF1B8 r[2];
} L02Ranges_CF1B8;
extern L02Ranges_CF1B8 g_puff_count_ranges;
extern void vec_clear_128(void *);
extern int math_random_int_below(int);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern void vec_random_direction(void *, float, float);

void func_PAL_L02_003D31A0(u8 *self)
{
    L02Pair_CF1B8 speed = g_puff_speed_pair;
    L02Pair_CF1B8 size = g_puff_size_pair;
    L02Range_CF1B8 kind = g_puff_kind_range;
    L02Ranges_CF1B8 count = g_puff_count_ranges;
    f32 vel[4] __attribute__((aligned(16)));
    f32 pos[4] __attribute__((aligned(16)));
    s32 i;

    vec_clear_128(vel);
    part_spawn_hero_relative(self + 0x10, vel, kind.a, ((s32)(math_random_int_range(count.r[0].a, count.r[0].b)) * 5 + 2) / 6 & 0xFF,
                  math_random_int_below(0xFF) & 0xFF, 0, size.x);
    for (i = 0; i < 1; i++) {
        vec_random_direction(pos, 0.0f, 0.5f);
        FastVecAdd(pos, pos, self + 0x10);
        vel[2] = -(math_random_float_range(speed.x, speed.y) * 0.020000001f);
        part_spawn_hero_relative(pos, vel, kind.b, ((s32)(math_random_int_range(count.r[1].a, count.r[1].b)) * 5 + 2) / 6 & 0xFF,
                      math_random_int_below(0xFF) & 0xFF, 0, size.y);
    }
}

