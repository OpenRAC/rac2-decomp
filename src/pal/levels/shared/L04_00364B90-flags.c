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
    u8  field00;
    u8  field01;
    u8  field02;
    u8  field03;
    u32 field04;
    u8  field08;
    u8  field09;
    u16 field0A;
    u32 field0C;
    L04Quad field10;
    u8  pad20[0xC];
    f32 field2C;
    L04Quad field30;
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

void *func_PAL_L04_00364D88(void *a0, void *a1, u32 a2, f32 f3) {
    L04Spawned *p = (L04Spawned *)(u32)part_alloc(0x5F);
    L04Vector *q;
    f32 v[4];

    if ((u32)p != 0) {
        p->field04 = 0x7F003CFF;
        p->field0C = 0x7F003CFF;
        p->field09 = (u8)(FloatToInt(2.0f) + 0x20);
        p->field03 = 0x48;
        p->field01 = 3;
        q = (L04Vector *)((u8 *)p + 0x30);
        p->field02 = *(u8 *)ref_L04_00362940_00;
        q->v = *(L04Quad *)a1;
        *(f32 *)((u8 *)q + 0xC) = f3;
        p->field10 = *(L04Quad *)a0;
        vec_scale_to_length(v, (f32 *)q, 0.5f);
        FastVecSub((f32 *)((u8 *)p + 0x20), (f32 *)a0, v);
        p->field0A = (u16)a2;
        *(f32 *)((u8 *)p + 0x1C) = 0.005f;
        p->field08 = (u8)(*(u8 *)&p->field0A - 4);
        p->field2C = 1.0f;
    }
    return (u32)p;
}
