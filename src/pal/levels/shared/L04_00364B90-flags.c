#include "include_asm.h"

#include "common.h"
extern float g_water_tile_half_x MACRO_ADDR, g_water_tile_half_y MACRO_ADDR;
extern unsigned char g_contact_hit_flag MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
extern void FastVecSub(f32 *,f32 *,f32 *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern u32 FastDecTimer(u8 *);
extern int FloatToInt(float);
extern void vec_scale_to_length(float *, float *, float);
extern float FastVecDot(void *, void *);
extern int g_hero_height_zone_active MACRO_ADDR;
extern float g_hero_airborne_speed_limit MACRO_ADDR;
extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef int L04Quad __attribute__((mode(TI)));
typedef struct {
    u8  unk_00;
    u8  unk_01;
    u8  unk_02;
    u8  unk_03;
    u32 unk_04;
    u8  unk_08;
    u8  unk_09;
    u16 unk_0A;
    u32 unk_0C;
    L04Quad unk_10;
    u8  pad20[0xC];
    f32 unk_2C;
    L04Quad unk_30;
} L04Spawned;
typedef struct {
    L04Quad v;
} L04Vector;
extern void *part_alloc(s32 kind);
extern s32 FloatToInt(f32 value);
extern s32 math_random_int_below(s32 limit);
extern void vec_scale_to_length(f32 *dst, f32 *a, f32 len);
extern void FastVecSub(f32 *dst, f32 *a, f32 *b);
extern u32 ref_L04_00362768_00;
extern u32 ref_L04_00362940_00;
extern s32 GetFirstMobyInGroup(u32 *out, s32 kind, s32 arg2, s32 arg3);
extern s32 GetNextMobyInGroup(u32 *out, u32 value, s32 arg2, s32 arg3);
extern f32 FastVecDot(void *a, void *b);
extern f32 square_root(f32 x);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern s32 func_001163B0(void);
extern u8 *ref_L04_00358868_00[];
extern s32 FloatToInt(f32);
extern f32 math_random_float_range(f32, f32);
extern s32 math_random_int_below(s32);
extern f32 g_water_texture_coords[];
extern f32 g_water_base_texture_coords[];
extern s32 g_water_scroll_flags[];
extern f32 func_30F3A0(f32 x);
extern f32 func_30F3B8(f32 x);
extern f32 func_30FE40(f32 a, f32 b);
extern u32 FastDecTimer(u8 *ptr);
extern f32 g_particle_speeds[];
extern f32 g_particle_sizes[];
extern f32 g_particle_uv_offsets[];
extern f32 g_particle_life_rates[];
extern u8 g_particle_sprite_flags[];
extern u16 g_particle_fade_in_timers[];
extern u16 g_particle_fade_out_timers[];
extern u16 g_particle_delay_timers[];
#define MACRO_ADDR __attribute__((section(".sdata")))
extern s32 g_particle_life_step MACRO_ADDR;
extern u16 g_particle_life_reload MACRO_ADDR;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern f32 g_particle_speeds[];
extern f32 g_particle_sizes[];
extern f32 g_particle_uv_offsets[];
extern f32 g_particle_life_rates[];
extern u8 g_particle_sprite_flags[];
extern u16 g_particle_fade_in_timers[];
extern u16 g_particle_fade_out_timers[];
extern u16 g_particle_delay_timers[];
extern s32 g_particle_life_step;
extern u16 g_particle_life_reload;
extern f32 math_random_signed_float_range(f32 a0, f32 a1);
extern f32 math_random_float_range(f32 a0, f32 a1);
extern u32 g_running_total __attribute__((sda));

/* Spawns a streak particle (record kind 0x5F) that trails back from a position along a direction (PAL). */
void *part_spawn_streak_pal(void *position, void *direction, u32 duration, f32 width) {
    L04Spawned *particle = (L04Spawned *)(u32)part_alloc(0x5F);
    L04Vector *streak;
    f32 trail[4];

    if ((u32)particle != 0) {
        particle->unk_04 = 0x7F003CFF;
        particle->unk_0C = 0x7F003CFF;
        particle->unk_09 = (u8)(FloatToInt(2.0f) + 0x20);
        particle->unk_03 = 0x48;
        particle->unk_01 = 3;
        streak = (L04Vector *)((u8 *)particle + 0x30);
        particle->unk_02 = *(u8 *)ref_L04_00362940_00;
        streak->v = *(L04Quad *)direction;
        *(f32 *)((u8 *)streak + 0xC) = width;
        particle->unk_10 = *(L04Quad *)position;
        vec_scale_to_length(trail, (f32 *)streak, 0.5f);
        FastVecSub((f32 *)((u8 *)particle + 0x20), (f32 *)position, trail);
        particle->unk_0A = (u16)duration;
        *(f32 *)((u8 *)particle + 0x1C) = 0.005f;
        particle->unk_08 = (u8)(*(u8 *)&particle->unk_0A - 4);
        particle->unk_2C = 1.0f;
    }
    return (u32)particle;
}
