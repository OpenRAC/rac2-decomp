#include "include_asm.h"

#include "common.h"
typedef int BarlowEffectQuad __attribute__((mode(TI)));
typedef union { BarlowEffectQuad q; float f[4]; } BarlowEffectVector;
extern void FastVecScale(void *, void *, float);
extern char *part_spawn_object_following_effect(void *, void *, unsigned int, int, int, int, int, int, float, float);
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern void part_explode_object_into_pieces_pal(void *, void *, void *, void *, int, int, int, int, int, unsigned char, void *);
extern void part_spawn_particle_burst_l03_pal(void *, void *, void *, void *, void *, int, unsigned char);
extern void vec_local_offset_to_world(void *, void *, float, float, float);
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void moby_mark_spawned(void *);
extern float g_barlow_emitter_pieces_a[] SDATA(D_L04_001B1830);
extern float g_barlow_emitter_pieces_b[] SDATA(D_L04_001B1828);
extern float g_barlow_emitter_pieces_c[] SDATA(D_L04_001B1820);
extern int g_barlow_emitter_pieces_param SDATA(D_L04_001B1850);

/* Launches a burst of effects from the object: it spawns a stream, waits, then fires the main burst and removes itself (PAL). */
void barlow_effect_emitter_update_pal(unsigned char *moby)
{
    BarlowEffectVector velocity, lower, upper, min_offset, max_offset;
    char *vars = *(char **)(moby + 0x68);
    velocity.q = 0;
    velocity.f[0] = -21.5f;
    switch (moby[0x20]) {
    case 0:
        FastVecScale(&velocity, &velocity, *(float *)(moby + 0x2c));
        *(char **)(vars + 4) = part_spawn_object_following_effect(&velocity, moby, 0x40208080, -1, 1, -1, 0, -1,
                                                *(float *)(moby + 0x2c) * 5250000.0f, *(float *)(moby + 0x2c) * 15.0f);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && !*(int *)vars) moby_set_state(moby, 2, -1);
        moby[0xa8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby, g_barlow_emitter_pieces_a, g_barlow_emitter_pieces_b, g_barlow_emitter_pieces_c, 65535, 0, g_barlow_emitter_pieces_param, 8, 65535, 255, 0);
        min_offset.q = 0;
        max_offset.q = 0;
        lower.q = 0;
        upper.q = 0;
        upper.f[0] = lower.f[0] = -15.0f;
        min_offset.f[0] = -10.0f;
        min_offset.f[2] = min_offset.f[1] = -4.0f;
        max_offset.f[0] = -3.0f;
        max_offset.f[1] = 5.0f;
        max_offset.f[2] = 4.0f;
        part_spawn_particle_burst_l03_pal(moby, &lower, &upper, &min_offset, &max_offset, 45, 0);
        vec_local_offset_to_world(moby, &velocity, -21.5f, 0.0f, 0.0f);
        SpawnExplosion_pal(moby + 0x10, 0, 25, 20, 20, 20, 45, 1,
                     *(float *)(moby + 0x2c) * 5.0f, 20.0f, 1, 1, 0, 0);
        moby_mark_spawned(moby);
        break;
    }
}

typedef int Quad __attribute__((mode(TI)));
#define I(vars,o) (*(int *)((u8 *)(vars)+(o)))
#define H(vars,o) (*(short *)((u8 *)(vars)+(o)))
#define F(vars,o) (*(float *)((u8 *)(vars)+(o)))
extern u8 *g_moby_l04_pool __attribute__((sda));
extern float g_barlow_enemy_move_time __attribute__((sda));
extern u8 g_barlow_enemy_data_block[8] __attribute__((sda));
extern u8 g_tether_zero_vec[];
extern float coll_probe_ground_height_below(void *, int, float);
extern int FloatToInt(float);
extern void MoveCtl_Init(void *);
extern int math_random_int_range(int, int);
extern void hero_copy_field_to_moby(void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void moby_update_ground_check(void *);
extern int moby_apply_damage_to_object_pal(void *, void *, int);
extern void gadgetron_hound_flag_group(void *);
extern int weapon_select_aim_target(void *, int, void *, int, float, float);
typedef struct {
    s32 i00;
    f32 f04;
    f32 f08;
    f32 f0C;
    u8 pad10[0x14];
    f32 f24;
    u8 pad28[8];
} D0C0Timer;
typedef struct {
    u8 pad000[0x28];
    u8 b28;
    u8 b29;
    u8 pad02A[6];
    f32 f30;
    u8 b34;
    u8 pad035[0x13];
    u8 b48;
    u8 pad049;
    u8 b4A;
    u8 pad04B[0x15];
    u8 ai[0x10];
    u8 b70;
    u8 b71;
    u8 b72;
    u8 pad073[3];
    u8 b76;
    u8 b77;
    u8 pad078[4];
    f32 f7C;
    f32 f80;
    f32 f84;
    f32 f88;
    f32 f8C;
    f32 f90;
    f32 f94;
    u8 pad098[4];
    f32 f9C;
    u8 pad0A0[8];
    s32 iA8;
    u8 pad0AC[0x20];
    u8 bCC;
    u8 bCD;
    u8 bCE;
    u8 bCF;
    u8 pad0D0[2];
    u8 bD2;
    u8 bD3;
    u8 pad0D4[0x1C];
    s32 iF0;
    f32 fF4;
    u8 pad0F8[0x18];
    Quad v110;
    f32 f120;
    u8 pad124[0x1C];
    D0C0Timer t140;
    u8 pad170[0x90];
    u8 *p200;
    u8 pad204[0x1C];
    f32 f220;
    u8 pad224[0xC];
    f32 f230;
    u8 pad234[0xAC];
    union { Quad q; f32 f[4]; } v2E0;
    u8 pad2F0[4];
    f32 f2F4;
    u8 pad2F8[8];
    s16 h300;
    u8 pad302[0xA];
    f32 f30C;
    u8 pad310[8];
    s32 i318;
    s32 i31C;
    s32 i320;
    s32 i324;
    s32 i328;
    u8 pad32C[4];
    f32 f330;
} D0C0Vars;

/* Sets the vars record up on the first update (ground height, spawn-point height,
   tuning block, timer, home position), then runs its distance, collision and
   func_PAL_002B1A50 checks on every update. */
void barlow_enemy_update_common_pal(u8 *moby)
{
    D0C0Vars *vars = *(D0C0Vars **)(moby + 0x68);
    u8 *hit;
    int result;

    moby[0x23] = 128;
    if (moby[0x20] == 0) {
        F(moby, 0x18) = coll_probe_ground_height_below(moby + 0x10, 0, 0.5f);
        qzero_nc(moby + 0xF0);
        if (vars->i328 != -1) {
            F(moby, 0x18) = F(g_moby_l04_pool + vars->i328 * 256, 0x18) + 1.4f;
            H(moby, 0x34) |= 0x41;
            I(moby, 0x98) = 0;
        }
        vars->i320 = 0;
        vars->i324 = 0;
        vars->b48 = FloatToInt(15.0f);
        vars->b4A = FloatToInt(4.0f);
        vars->b29 = 1;
        vars->b70 = 6;
        vars->iA8 = 3;
        vars->b71 = 9;
        vars->b72 = 9;
        vars->b76 = 10;
        vars->b77 = 11;
        vars->f7C = 0.120000005f;
        vars->f80 = 0.060000002f;
        vars->f84 = 0.0044f;
        vars->f88 = 0.0044f;
        vars->f8C = 0.00080000004f;
        vars->f90 = 0.35f;
        vars->f94 = 0.35f;
        vars->f9C = 0.4f;
        vars->bCC = 6;
        vars->bCD = 11;
        vars->bCE = 6;
        vars->bCF = 11;
        vars->bD2 = 6;
        vars->bD3 = 11;
        MoveCtl_Init(&vars->t140);
        vars->t140.f0C = 2.5f;
        vars->t140.f08 = 2.0f;
        vars->t140.i00 = FloatToInt(g_barlow_enemy_move_time * 1024.0f);
        vars->t140.f04 = g_barlow_enemy_move_time;
        vars->t140.f24 = vars->f30C * (0.020000001f);
        if (vars->v2E0.f[3] != 12439.4f) {
            vars->v2E0.q = *(Quad *)(moby + 0x10);
            vars->v2E0.f[3] = 12439.4f;
        }
        qcopy(&vars->v110, &vars->v2E0);
        vars->f120 = 0.5f;
        vars->h300 = math_random_int_range(100, 583);
        vars->i31C = 0;
        hero_copy_field_to_moby(moby);
        vars->f230 = F(moby, 0x2C);
        vars->f220 = vars->f30;
        vars->b28 = 0;
        vars->i318 = 0;
        vars->p200 = g_barlow_enemy_data_block;
        vars->f330 = (float)vars->b34;
        moby_set_state(moby, 1, 0);
        if (moby[0x43])
            anim_start_blended_pal(moby, 0, 0, 0);
    }
    if (moby[0x31] && fast_vec_dist(moby + 0x10, g_tether_zero_vec) < 24.0f) {
        moby_update_ground_check(moby);
        moby[0x6F] = 22;
    }
    hit = (u8 *)part_find_owned_effect_slot(moby, 0x230000, 0);
    if (hit && hit[0x28] == 8) {
        moby[0x20] = 8;
        moby[0xBC] = 4;
    }
    result = moby_apply_damage_to_object_pal(moby, vars->ai, 0);
    if (result) {
        if (result == 5) {
            vars->iF0 = 0;
            vars->fF4 = 1.0053098f;
        }
        gadgetron_hound_flag_group(moby);
    }
    weapon_select_aim_target(moby, -1, &vars->v2E0, 0, vars->f2F4, 10.0f);
}
