#include "include_asm.h"

#include "common.h"
extern void vec_scale_to_length(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern u8 *g_hero_moby;
extern u8 g_unused_level_byte __attribute__((sda));
extern f32 func_2F4AD0(f32, f32);
typedef struct {
    float vel[4];
    int life;
    int f14;
    int f18;
    float scale;
} TrailVars0040DE00;
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 flag20;
    u8 pad21[0xF];
    u8 alpha;
    u8 pad31;
    short colour;
    u8 pad34[0x34];
    TrailVars0040DE00 *vars;
    u8 pad6C[0x54];
    float p0[4];
    float p1[4];
    float p2[4];
} TrailMoby0040DE00;
extern void cam_compute_view_direction(void *, void *, int);
extern TrailMoby0040DE00 *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern u8 *g_space_ship_owner_moby[] __attribute__((sda));
extern f32 g_space_ship_param_y __attribute__((sda));
extern void vec_scale_to_length(void *, void *, f32);
extern u8 *g_hero_moby;
extern void vec_scale_to_length(void *, void *, f32);

TrailMoby0040DE00 *part_spawn_trail_effect_pal(float *pos, float *vel, float *scale)
{
    float ref[4];
    float scaled[4];
    TrailMoby0040DE00 *moby;
    TrailVars0040DE00 *vars;

    cam_compute_view_direction(pos, ref, 1);
    moby = CreateMoby(0xF5D);
    if (moby != 0) {
        vars = moby->vars;
        vars->scale = *scale;
        vars->life = 0x43;
        moby->alpha = 0xFF;
        moby->colour = 0xFF;
        moby->flag20 = 0;
        qcopy(moby->pos, pos);
        qcopy(vars->vel, vel);
        vars->f18 = 0;
        vars->f14 = 0;
        vec_scale_to_length(scaled, vel, 1.0f);
        qcopy(moby->p0, scaled);
        FastVecCross(moby->p1, moby->p0, ref);
        vec_scale_to_length(moby->p1, moby->p1, 1.0f);
        FastVecCross(moby->p2, moby->p1, moby->p0);
        moby->p0[3] = moby->p1[3] = moby->p2[3] = 0.0f;
    }
    return moby;
}


extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern int math_random_int_below(int);
extern int CollLine(void *, void *, int, void *, int);
extern void QueueMobyImpact(void *, void *);
extern s32 g_trigger_event_list_head __attribute__((sda));
extern s32 g_trigger_event_flag __attribute__((sda));
extern s32 g_unused_l22_level_word __attribute__((sda));
extern s32 func_2F36F0(s32);
typedef struct { u8 pad[0x18]; u8 *target; } G1C00C0;
extern G1C00C0 g_projectile_hit_info;
extern int CollLine(void *, void *, int, void *, int);
extern void make_hit_descriptor(void *, void *, int, void *, f32);
extern void QueueMobyImpact(void *, void *);
extern void part_start_random_scale_effect_pal(void *, s32, s32);

void projectile_check_hit_explode_pal(u8 *a0, u8 *a1) {
    u8 *s0 = *(u8 **)(a0 + 0x68);
    u8 vec[16] __attribute__((aligned(16)));
    u8 ev[0x30] __attribute__((aligned(16)));
    u8 buf[16] __attribute__((aligned(16)));
    u8 *target;

    if (CollLine(a1, a0 + 0x10, 0, a0, 0) == 0) {
        return;
    }
    target = g_projectile_hit_info.target;
    if (target == 0) {
        return;
    }
    if (*(s16 *)(target + 0xAA) == 0xEDD || *(s16 *)(target + 0xAA) == 0xE0B) {
        return;
    }
    if (target == g_hero_moby && !(*(f32 *)(s0 + 0x1C) < 50.0f)) {
        return;
    }
    if (*(f32 *)(s0 + 0x1C) >= 50.0f) {
        *(f32 *)(s0 + 0x1C) = 50.1f;
    }
    vec_scale_to_length(vec, s0, 1.0f);
    make_hit_descriptor(ev, a0, 0x8B0003, vec, *(f32 *)(s0 + 0x1C));
    ev[0x18] = 5;
    ev[0x19] = 3;
    *(u16 *)(ev + 0x1A) = *(u16 *)(a0 + 0xAA);
    QueueMobyImpact(g_projectile_hit_info.target, ev);
    part_start_random_scale_effect_pal(a0 + 0x10, 10, 1);
    if (g_projectile_hit_info.target == 0) {
        qcopy(buf, a0 + 0x10);
        part_start_random_scale_effect_pal(buf, 15, 0);
    }
    a0[0x20] = 2;
}

