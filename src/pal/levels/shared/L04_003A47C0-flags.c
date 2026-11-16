#include "include_asm.h"

#include "common.h"
extern float g_water_tile_half_x MACRO_ADDR, g_water_tile_half_y MACRO_ADDR;
extern unsigned char g_contact_hit_flag MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
typedef struct {
    u8 pad00[0x7A8];
    f32 unk_7A8, unk_7AC, unk_7B0, unk_7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 unk_2290, unk_2294, unk_2298, unk_229C;
} RippleHero;
#define RIPPLE_HERO (*(RippleHero *)&D_00189E20)
extern void STUB_printf(void *, int, int, int, int);
extern void water_select_table_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void func_002FD1B8_ripple(void *, int, int, float, float, float, float) __asm__("func_002FD1B8");
extern int point_in_path_xy(void *, void *, int);
extern float FastAddRotations(float, float);
extern int math_random_int_below(int);
extern char g_str_water_controller_fmt[];
extern char *g_route_path_table[];
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
#define WINT(p,o) (*(int *)((char *)(p)+(o)))
#define WFLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define WPTR(p,o) (*(char **)((char *)(p)+(o)))
extern u32 FastDecTimer(u8 *);
extern int FloatToInt(float);
extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern int g_hero_height_zone_active MACRO_ADDR;
extern float g_hero_airborne_speed_limit MACRO_ADDR;
extern f32 math_approach_with_velocity(f32 *position, f32 target, f32 *velocity,
                         f32 acceleration, f32 damping, f32 limit, s32 direction);
typedef struct {
    u8 pad00[0x7A8];
    f32 unk_7A8;
    f32 unk_7AC;
    f32 unk_7B0;
    f32 unk_7B4;
    u8 pad7B8[0x2290 - 0x7B8];
    u32 unk_2290;
    u32 unk_2294;
} D00189E20;
extern D00189E20 g_hero_state;
extern s32 FloatToInt(f32 value);
extern s32 math_random_int_below(s32 limit);
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

/* Toggle the water controller, animate its height, and disturb its ripple tiles. */
void water_update_controller_pal(char *moby) {
    char *vars = WPTR(WPTR(moby, 0x28), 0x68);
    float x, y, half, jitter;

    if (WBYTE(WPTR(moby, 0x28), 0xBC) >= WBYTE(vars, 0x15)) {
        STUB_printf(g_str_water_controller_fmt, WSHORT(WPTR(moby, 0x28), 0xB2),
                      WSHORT(WPTR(moby, 0x28), 0xAA), WBYTE(WPTR(moby, 0x28), 0xBC),
                      WBYTE(vars, 0x15));
        WBYTE(WPTR(moby, 0x28), 0x20) = 2;
        WBYTE(WPTR(moby, 0x28), 0xBC) = 0;
        WSHORT(vars, 0x16) = 50;
        WBYTE(vars, 0x14) ^= 1;
        water_select_table_slot(WPTR(moby, 0x28), WINT(moby, 0x1C), WINT(moby, 0x18));
        if (WINT(vars, 0x10) >= 0 && !WBYTE(vars, 0x14)) {
            int i;
            for (i = WINT(vars, 0x10); i < WINT(moby, 4); i++) {
                jitter = math_random_float_range(-4.0f, 4.0f);
                x = WFLOAT(WPTR(moby, 8) + i * 0x1190, 0);
                x += jitter;
                y = WFLOAT(WPTR(moby, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
                func_002FD1B8_ripple(WPTR(moby, 8) + i * 0x1190, 1, 1,
                                     x, y, 1.0f, -0.05f);
            }
        }
    }
    if (WBYTE(vars, 0x14)) return;
    if (WINT(vars, 0x20) != -1) {
        char *path = g_route_path_table[WINT(vars, 0x20)];
        if (point_in_path_xy((char *)&g_hero_state + 0x80, path + 0x10, WINT(path, 0)))
            WFLOAT(&g_hero_state, 0x330) = WFLOAT(WPTR(moby, 0x28), 0x18);
    }
    half = (WFLOAT(vars, 0) - WFLOAT(vars, 4)) * 0.5f;
    WFLOAT(WPTR(moby, 0x28), 0x18) =
        WFLOAT(vars, 4) + (math_fast_sin_or_cos_a(WFLOAT(vars, 8)) * half + half);
    if (RIPPLE_HERO.unk_229C != 20 && RIPPLE_HERO.unk_229C != 25 &&
        RIPPLE_HERO.unk_2294 != 0x39 && RIPPLE_HERO.unk_2294 != 0x78 &&
        RIPPLE_HERO.unk_2294 != 0x79)
        WFLOAT(vars, 8) = FastAddRotations(WFLOAT(vars, 8), WFLOAT(vars, 0xC));
    if (WINT(vars, 0x10) >= 0 && !math_random_int_below(200)) {
        int i;
        for (i = WINT(vars, 0x10); i < WINT(moby, 4); i++) {
            jitter = math_random_float_range(-4.0f, 4.0f);
            x = WFLOAT(WPTR(moby, 8) + i * 0x1190, 0);
            x += jitter;
            y = WFLOAT(WPTR(moby, 8) + i * 0x1190, 4) + math_random_float_range(-4.0f, 4.0f);
            func_002FD1B8_ripple(WPTR(moby, 8) + i * 0x1190, 1, 1,
                                 x, y, 1.0f, -0.05f);
        }
    }
}
