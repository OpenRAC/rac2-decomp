#include "include_asm.h"

#include "common.h"
typedef float VecE[4] __attribute__((aligned(16)));
extern VecE g_coll_hit_point, g_coll_hit_position;
typedef struct {
    u8 pad00[0x80]; VecE position; u8 pad90[0x50]; VecE pickup_target;
    u8 padF0[0x2290-0xF0]; void *moby;
    u8 pad2294[0x24A4-0x2294]; f32 reach_distance, reach_height;
    u8 pad24AC[0x20]; s32 health;
} AmmoHero;
extern AmmoHero g_hero_state;
typedef struct {
    u8 pad00[0x38]; s16 sound_multiple, sound_single;
    u8 pad3C[0x8E - 0x3C]; u16 max_ammo; u8 pad90[0x50];
} AmmoDef;
extern u8 g_weapon_table[];
extern u8 g_item_slot_to_record[];
extern s32 g_item_ammo_counts[];
extern void *g_hero_moby NOT_SDA;
extern s32 g_game_time[] __attribute__((sda));
extern s32 g_ammo_pickup_time[] __attribute__((sda));
extern s32 D_001B24A8_gp SDATA(D_001B24A8);
extern s32 math_fast_float_d(s32 *);
extern u32 stub_empty_8(s32, s32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern f32 ApproachValue(f32 *, f32, f32);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void value_forward_three_args_us2(s32, s32, s32);
extern void moby_mark_spawned(void *);
extern f32 FastVecLength(void *);
extern f32 math_fabs(f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 func_002A0558(void *, void *);
extern f32 fast_vec_dist(void *, void *);
extern f32 math_fast_sin_or_cos_a(f32);
extern s32 coll_test_point(void *, s32, s32, f32);
extern s32 CollLine(void *, void *, s32, s32, s32);
extern s32 FloatToInt(f32);
extern s32 subtract_integer_with_clamp(s32);
#define EF(p, n) (*(f32 *)((u8 *)(p) + (n)))
#define EI(p, n) (*(s32 *)((u8 *)(p) + (n)))


