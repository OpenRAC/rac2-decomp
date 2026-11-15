#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec4f __attribute__((aligned(16)));

typedef struct {
    u8 pad0[0xC];
    s16 unkC;
    u8 padE[2];
    Vec4f home;
    u8 pad20[0x60 - 0x20];
    f32 unk60;
    f32 unk64;
    f32 unk68;
    s32 timer;
} GoldBoltVars;

typedef struct {
    u8 pad0[0x24];
    f32 scale;
} GoldBoltClass;

typedef struct {
    u8 pad0[0x10];
    Vec4f pos;
    u8 state;
    u8 pad21[3];
    GoldBoltClass *pclass;
    u8 pad28[4];
    f32 scale;
    u8 unk30;
    u8 visible;
    s16 unk32;
    u16 flags;
    u8 pad36[0x42 - 0x36];
    u8 seq;
    u8 prev_seq;
    u8 pad44[0x60 - 0x44];
    u8 anim_flags;
    u8 pad61[7];
    GoldBoltVars *pvars;
    u8 pad6C[0xF0 - 0x6C];
    Vec4f rot;
} GoldBoltMoby;

typedef struct {
    u8 pad0[0x80];
    Vec4f pos;
    Vec4f rot;
    u8 padA0[0xC28 - 0xA0];
    s32 anim_flags;
    u8 padC2C[0x22B4 - 0xC2C];
    u8 vehicle_mode;
    u8 pad22B5[0x22BF - 0x22B5];
    u8 unk22BF;
    u8 pad22C0[0x24CC - 0x22C0];
    s32 hp;
} GoldBoltHero;

extern GoldBoltHero g_hero_state;
extern u8 D_001A7B2A MACRO_ADDR;
extern u8 D_001A7A45 MACRO_ADDR;
extern f32 D_L01_001B1A58 __attribute__((sda));
extern f32 D_L01_001B1A68 __attribute__((sda));
extern f32 D_L01_001B1A6C __attribute__((sda));
extern f32 D_L01_001B1A70 __attribute__((sda));
extern f32 D_L01_001B1A74 __attribute__((sda));
extern s32 D_L01_001B1A98 __attribute__((sda));
extern s32 D_L01_001B21B0 MACRO_ADDR;
/* The same block src/levels/01_oozla/L01_003D2E50.c writes: a symbol-plus-offset store counts as
   two instructions, so it stays out of the jal delay slot. */
extern struct {
    s16 f0, f2, f4, pad6;
    s32 busy;
} D_L01_001B22A0 MACRO_ADDR;
extern s32 D_L01_001B1FA8 MACRO_ADDR;
extern s32 D_L01_001B1FA8_gp SDATA(D_L01_001B1FA8);
extern f32 math_random_angle(void);
extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 vec_distance_xy(void *, void *);
extern f32 math_fabs(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 math_random_int_below(s32);
extern s32 math_fast_float_d(void *);
extern void gold_bolt_glow_init(void *);
extern void gfx_draw_glow_rings(void *);
extern void part_spawn_sparkle_drift(void *);
extern void gold_bolt_cam_update(void *);
extern void bobbing_l01_moby_update_2(void *);
extern void value_set_entry_by_index(s32, s32);
extern void help_unlock_entry(s32);
extern s32 PlayMobySound(s32, s32, void *);
extern void moby_mark_spawned(void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern void FadeToBlack(s32);
extern void hero_reset_for_area_start(s32);
extern void hero_reset_position_and_direction(void *, void *, s32, s32);
extern void SetCamera5Pose(void *, void *, s32, s32, s32);
extern void object_copy_vector_to_selected(void *);
extern void cam_set_state_rotation(void *);
extern void cam_set_mode_state(s32);
extern void anim_start_blended(void *, s32, s32, s32);
extern void set_hero_animation(s32, s32, f32);
extern s32 MemcardSave(s32, s32);

#define SPIN 0.0002908882452175021f

/* Gold bolt update: idle spin, hero pickup check, pickup animation and camera, removal.
 * Adapted from RAC1's gold_bolt_update (GPL-3.0). */
void GoldBoltUpdate(GoldBoltMoby *moby) {
    GoldBoltVars *vars = moby->pvars;
    GoldBoltHero *hero;
    Vec4f at, look, at2, look2;
    s32 i;

    switch (moby->state) {
    case 0:
        if (D_001A7B2A) {
            goto remove;
        }
        qcopy(&vars->home, &moby->pos);
        vars->home.w = moby->rot.z;
        moby->rot.x = math_random_angle();
        moby->rot.y = math_random_angle();
        moby->rot.z = math_random_angle();
        moby->rot.w = math_random_angle();
        vars->unk68 = D_L01_001B1A68 * SPIN;
        vars->unk64 = D_L01_001B1A6C * SPIN;
        vars->unk60 = D_L01_001B1A70 * SPIN;
        if (moby->unk32 < 0x40) {
            moby->unk32 = 0x40;
        }
        moby->state = 1;
        gold_bolt_glow_init(moby);
        break;
    case 1:
        moby->scale = moby->pclass->scale * D_L01_001B1A58;
        moby->rot.x = FastAddRotations(moby->rot.x, D_L01_001B1A68 * SPIN);
        moby->rot.y = FastAddRotations(moby->rot.y, D_L01_001B1A6C * SPIN);
        moby->rot.z = FastAddRotations(moby->rot.z, D_L01_001B1A70 * SPIN);
        moby->rot.w = FastAddRotations(moby->rot.w, D_L01_001B1A74 * SPIN);
        gfx_draw_glow_rings(moby);
        if (!math_random_int_below(D_L01_001B1A98)) {
            part_spawn_sparkle_drift(moby);
        }
        if (!(vec_distance_xy(&moby->pos, &g_hero_state.pos) < 3.0f)) {
            break;
        }
        if (!(math_fabs(moby->pos.z - g_hero_state.pos.z) < 2.0f)) {
            break;
        }
        if (g_hero_state.hp == 0) {
            break;
        }
        if (g_hero_state.vehicle_mode != 3 && g_hero_state.vehicle_mode != 0) {
            break;
        }
        if (vars->unkC != 0) {
            D_L01_001B21B0 = 180;
            value_set_entry_by_index(0xAAA, -1);
            help_unlock_entry(50);
            PlayMobySound(1, 0, moby);
        remove:
            moby_mark_spawned(moby);
            break;
        }
        at.x = math_fast_sin_or_cos_a(vars->home.w) * 2.5f;
        at.y = math_fast_sin_or_cos_b(vars->home.w) * 2.5f;
        at.z = 0.0f;
        FastVecAdd(&at, &at, &vars->home);
        vec_clear_128(&look);
        look.z = FastAddRotations(vars->home.w, 3.141593f);
        FadeToBlack(10);
        if (g_hero_state.vehicle_mode == 3) {
            hero_reset_for_area_start(0);
        }
        hero_reset_position_and_direction(&at, &look, 0x6F, 0);
        PlayMobySound(0, 0, moby);
        at2.x = math_fast_sin_or_cos_a(vars->home.w) * 1.25f;
        at2.y = math_fast_sin_or_cos_b(vars->home.w) * 1.25f;
        at2.z = 0.0f;
        at2.x += math_fast_sin_or_cos_a(FastAddRotations(vars->home.w, 1.5707965f)) * 4.0f;
        at2.y += math_fast_sin_or_cos_b(FastAddRotations(vars->home.w, 1.5707965f)) * 4.0f;
        FastVecAdd(&at2, &at2, &vars->home);
        at2.z += 1.0f;
        vec_clear_128(&look2);
        look2.z = fast_subtract_rotations(vars->home.w, 1.5707965f);
        SetCamera5Pose(&at2, &look2, 1, 0, 0);
        object_copy_vector_to_selected(&at2);
        cam_set_state_rotation(&look2);
        qcopy(&moby->pos, &g_hero_state.pos);
        qcopy(&moby->rot, &g_hero_state.rot);
        if (moby->prev_seq != 1) {
            anim_start_blended(moby, 1, 0, 0);
        }
        set_hero_animation(0x7B, 0, 0.0f);
        if (D_001A7A45) {
            moby->flags |= 0x8000;
        }
        g_hero_state.unk22BF = 1;
        D_L01_001B1FA8 = 1;
        moby->state = 2;
        vars->timer = 60;
        break;
    case 2:
        D_L01_001B22A0.busy = 1;
        gold_bolt_cam_update(moby);
        qcopy(&moby->pos, &g_hero_state.pos);
        qcopy(&moby->rot, &g_hero_state.rot);
        if (moby->seq == 1) {
            bobbing_l01_moby_update_2(moby);
            if (!math_random_int_below(10)) {
                part_spawn_sparkle_drift(moby);
            }
            if (moby->anim_flags & 2) {
                if (moby->prev_seq != 0) {
                    anim_start_blended(moby, 0, 0, 0);
                }
                moby->visible = 0;
                moby->flags |= 1;
                for (i = 0; i < 4; i++) {
                    part_spawn_sparkle_drift(moby);
                }
            }
        }
        hero = &g_hero_state;
        if (hero->anim_flags & 2) {
            set_hero_animation(0, 0, 30.0f);
        }
        if (moby->seq != 0 || !math_fast_float_d(&vars->timer)) {
            break;
        }
        D_L01_001B21B0 = 180;
        value_set_entry_by_index(0x129A, -1);
        help_unlock_entry(50);
        D_L01_001B1FA8_gp = 0;
        hero_reset_position_and_direction(&hero->pos, &hero->rot, 0, 0);
        cam_set_mode_state(0);
        MemcardSave(0, -1);
        moby_mark_spawned(moby);
        break;
    }
}
