#include "include_asm.h"

#include "common.h"
extern float g_water_tile_half_x MACRO_ADDR, g_water_tile_half_y MACRO_ADDR;
extern int g_hero_mode_state[] __attribute__((sda));
extern unsigned char g_contact_hit_flag MACRO_ADDR;
extern unsigned char g_bolt_multiplier MACRO_ADDR;
extern char g_surface_table[];
extern float fade_get_value(void);
extern float fade_reduce_value_pal(float);
extern void hero_clear_tracked_slots(void);
extern void FastVecSub(f32 *,f32 *,f32 *);
extern void hero_build_relative_point(void *,int,float,float,float);
extern s32 hero_l04_set_move_state_pal(int,int);
extern char *part_find_owned_effect_slot(void *,int,int);
extern void AdjustPlayerHealth_pal(int);
extern int hero_play_sound(int,int);
extern void hero_flatten_push_vector(void *,int,float,float);
extern void cam_scale_view_space_height(void *,void *,float);
#define AB(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define AH(p,o) (*(short *)((char *)(p)+(o)))
#define AI(p,o) (*(int *)((char *)(p)+(o)))
#define AF(p,o) (*(float *)((char *)(p)+(o)))
#define AP(p,o) (*(char **)((char *)(p)+(o)))
typedef union {
    unsigned char b[0x2500];
    short h[0x1280];
    int i[0x940];
    float f[0x940];
    char *p[0x940];
} GroundHero;
#define GROUND_HERO (*(GroundHero *)&D_00189E20)
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern u32 FastDecTimer(u8 *);
extern void FastVecAdd(void *, void *, void *);
extern int FloatToInt(float);
extern float FastVecDot(void *, void *);
extern int g_hero_height_zone_active MACRO_ADDR;
extern float g_hero_airborne_speed_limit MACRO_ADDR;
typedef union {
    int q __attribute__((mode(TI)));
    float f[4];
} HopVector;
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
extern void FastVecAdd(void *, void *, void *);
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

/* Check the hero's surface contact and optionally apply its movement impulse. */
int hero_check_surface_contact_pal(int update) {
    char *surface_entry, *moby;
    HopVector push;
    int is_special;
    float push_scale;

    if (GROUND_HERO.i[0x229C / 4] == 20) return 0;
    if (GROUND_HERO.i[0x229C / 4] == 7) return 0;
    if (GROUND_HERO.i[0x2294 / 4] == 0x31) return 0;
    if (GROUND_HERO.h[0x1DC / 2]) return 0;
    if (g_hero_mode_state[0]) return 0;
    GROUND_HERO.i[0x249C / 4] = 0;
    moby = GROUND_HERO.p[0x2290 / 4];
    if (AB(moby, 0xA8) == 255) return 0;
    surface_entry = g_surface_table + AB(moby, 0xA8) * 64;
    if (AP(surface_entry, 0x38) != moby) return 0;
    if (!(AI(surface_entry, 0x24) & 9)) return 0;
    if (AF(surface_entry, 0x2C) != 0.0f) {
        g_contact_hit_flag = 0;
        g_bolt_multiplier = 1;
    }
    if (fade_get_value() != 0.0f && !GROUND_HERO.b[0x22B4]) {
        AF(surface_entry, 0x2C) = fade_reduce_value_pal(AF(surface_entry, 0x2C));
        if (AF(surface_entry, 0x2C) == 0.0f) return 0;
    }
    GROUND_HERO.p[0x249C / 4] = AP(surface_entry, 0x20);
    if (!update) return 1;
    hero_clear_tracked_slots();
    is_special = 0;
    if (AI(surface_entry, 0x30) & 1) {
        qcopy(&push, surface_entry + 0x10);
        if (AF(surface_entry, 0x1C) == 5627.925f) is_special = 1;
    } else if (AP(surface_entry, 0x20)) {
        FastVecSub(push.f, (float *)(GROUND_HERO.b + 0x80),
                     (float *)(AP(surface_entry, 0x20) + 0x10));
    } else {
        hero_build_relative_point(&push, 0, -1.0f, 0.0f, 0.0f);
    }
    if (!GROUND_HERO.b[0x22B4]) {
        char *moby = GROUND_HERO.p[0x249C / 4];
        if (moby && (AH(moby, 0xAA) == 0x4EB || AH(moby, 0xAA) == 0x558)) {
            hero_l04_set_move_state_pal(0x7D, 1);
            return 1;
        }
        if ((GROUND_HERO.i[0x2294 / 4] == 1 ||
             GROUND_HERO.i[0x2294 / 4] == 0x1D || GROUND_HERO.i[0x1500 / 4]) &&
            !(AI(surface_entry, 0x24) & 8)) {
            char *moby = part_find_owned_effect_slot(GROUND_HERO.p[0x2290 / 4], 1, 0);
            if (moby) AdjustPlayerHealth_pal(FloatToInt(AF(moby, 0x2C)));
            if (!GROUND_HERO.i[0x24CC / 4]) hero_l04_set_move_state_pal(0x16, 1);
            GROUND_HERO.h[0x1DC / 2] = 0x40;
            if (!GROUND_HERO.h[0x21C / 2]) GROUND_HERO.h[0x21C / 2] = 0xF;
            hero_play_sound(20, 0);
            return 0;
        }
        if (GROUND_HERO.i[0x229C / 4] == 0x12) hero_l04_set_move_state_pal(0x72, 1);
        else if (GROUND_HERO.i[0x229C / 4] == 0x11) hero_l04_set_move_state_pal(0x73, 1);
        else if (AI(surface_entry, 0x24) & 8) hero_l04_set_move_state_pal(0x8C, 1);
        else hero_l04_set_move_state_pal(0x16, 1);
        if (GROUND_HERO.i[0x2294 / 4] == 0x8C) {
            qzero(&push);
        } else {
            push_scale = 0.06600001f;
            if (GROUND_HERO.b[0x1497]) push_scale = 0.0f;
            hero_flatten_push_vector(&push, is_special, push_scale, 0.034f);
            if (is_special && AB(surface_entry, 0x28) == 4)
                cam_scale_view_space_height(&push, &push, 2.0f);
        }
    }
    FastVecAdd(GROUND_HERO.b + 0xF0, GROUND_HERO.b + 0xF0, &push);
    FastVecAdd(GROUND_HERO.b + 0x110, GROUND_HERO.b + 0x110, &push);
    return 1;
}
