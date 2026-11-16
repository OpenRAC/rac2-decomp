/* Per-frame update of the hero-steered bot (class 0x81E): flight, collision, attachment,
   idle effects and self-destruct burst. Own unit: it reaches the level's globals through $gp. */
#include "common.h"

typedef int TI128_AE900 __attribute__((mode(TI)));
typedef union { TI128_AE900 q; float f[4]; int i[4]; } VecAE900;

/* One frame at 60 Hz, and degrees to radians, as the retail constants fold. */
#define FRAME_AE900 0.016666668f
#define DEG_AE900 0.017453294f
#define PI_AE900 3.1415927f

struct VarsAE900;

typedef struct MobyAE900 {
    char pad00[0x10];
    VecAE900 pos;                 /* 0x10 */
    unsigned char state;          /* 0x20 */
    char pad21[3];
    char *pClass;                 /* 0x24 */
    char pad28[0xC];
    unsigned short flags;         /* 0x34 */
    char pad36[0xC];
    unsigned char b42;            /* 0x42 */
    unsigned char b43;            /* 0x43 */
    char pad44[0x1C];
    unsigned char b60;            /* 0x60 */
    char pad61[7];
    struct VarsAE900 *vars;       /* 0x68 */
    char pad6C[0x2C];
    int collData;                 /* 0x98 */
    char pad9C[0xC];
    unsigned char bA8;            /* 0xA8 */
    char padA9;
    short oClass;                 /* 0xAA */
    char padAC[0x10];
    unsigned char bBC;            /* 0xBC */
    char padBD[3];
    char matrix[0x30];            /* 0xC0 */
    float rot[4];                 /* 0xF0 */
} MobyAE900;

typedef struct VarsAE900 {
    VecAE900 vel;                 /* 0x00: vel.f[2] is the vertical speed */
    char pad10[0x20];
    MobyAE900 *owner;             /* 0x30 */
    short timer34;                /* 0x34 */
    short s36;                    /* 0x36 */
    char pad38[8];
    float pull;                   /* 0x40 */
    char pad44[4];
    short timer48;                /* 0x48 */
    char pad4A[2];
    MobyAE900 *ground;            /* 0x4C */
    short inWater;                /* 0x50 */
    short bob;                    /* 0x52 */
    MobyAE900 *target;            /* 0x54 */
    int timer58;                  /* 0x58 */
    int i5C;                      /* 0x5C */
    float f60;                    /* 0x60 */
    float f64;                    /* 0x64 */
    int sound;                    /* 0x68 */
    float amp;                    /* 0x6C */
    float phase;                  /* 0x70 */
    int frame;                    /* 0x74 */
    int i78;                      /* 0x78 */
} VarsAE900;

typedef struct {
    char pad00[0x88];
    float z;                      /* 0x88 */
    char pad8C[0x33C - 0x8C];
    MobyAE900 *standing;          /* 0x33C */
    char pad340[0x1220 - 0x340];
    MobyAE900 *held;              /* 0x1220 */
    char pad1224[0x2290 - 0x1224];
    MobyAE900 *moby;              /* 0x2290 */
    char pad2294[0x22B4 - 0x2294];
    unsigned char b22B4;
    unsigned char b22B5;
    char pad22B6[9];
    unsigned char b22BF;
} HeroAE900;

typedef struct {
    char pad00[0x18];
    MobyAE900 *hit;               /* 0x18 */
    int count;                    /* 0x1C */
    VecAE900 point;               /* 0x20 */
    VecAE900 p30;                 /* 0x30 */
    VecAE900 normal;              /* 0x40 */
} CollAE900;

/* The record handed to the collision test (its fifth argument). */
typedef struct {
    VecAE900 dir;                 /* 0x00 */
    MobyAE900 *owner;             /* 0x10 */
    int flags;                    /* 0x14 */
    unsigned char b18;
    unsigned char b19;
    unsigned short oClass;        /* 0x1A */
    float damage;                 /* 0x1C */
    int i20;                      /* 0x20 */
} HitAE900;

/* 0xE0-byte weapon record: +4 upgraded flag, +0x70 a rate. */
typedef struct { char pad00[4]; unsigned char upgraded; char pad05[0x6B]; float rate; char pad74[0x6C]; } WeaponAE900 __attribute__((aligned(16)));

/* Sound state has a 0x70-byte header followed by 52 0x70-byte voices. */
typedef struct {
    unsigned int handle;
    unsigned char active;
    char unknown05[0x13];
    MobyAE900 *owner;
    char unknown1C[0x54];
} SlotAE900 __attribute__((aligned(16)));
typedef struct { char header[0x70]; SlotAE900 slots[52]; } SoundAE900;
#define SLOT_AE900(i) (D_00188660.slots[(i)])

/* 0x50-byte effect template copied to the stack for func_00312B70. */
typedef struct { VecAE900 v; char rest[0x40]; } TemplateAE900;

/* Four per-kind rates, 4-byte aligned: copied with unaligned doubleword moves. */
typedef struct { float v[4]; } RatesAE900;

/* Camera shake record: +0x160 amount, +0x168 frames, +0x16C counter. */
typedef struct { char pad000[0x160]; float amount; char pad164[4]; int frames; int counter; } ShakeAE900;


extern HeroAE900 g_hero_state;
extern unsigned char g_item_slot_to_record[];
extern WeaponAE900 g_weapon_table_2[];
extern SoundAE900 g_sound_state;
extern CollAE900 g_collision_result;
extern TemplateAE900 g_small_effect_template;
extern TemplateAE900 g_big_effect_template;
extern RatesAE900 g_effect_default_rates;
extern int g_frame_l00_counter MACRO_ADDR;
extern float g_effect_duration_frames __attribute__((sda));
extern int g_effect_skip_flag __attribute__((sda));
extern int g_ripple_object __attribute__((sda));
extern int g_ripple_param __attribute__((sda));
extern VecAE900 g_camera_l00_position;
extern ShakeAE900 g_scalar_transition_state;
extern char g_area_hit_targets[];
extern MobyAE900 *g_target_l00_list[];
extern char g_moby_index_list_head[];
extern char g_effect_definitions[];

extern void UpdateMobyLinks(void);
extern int PredictMineImpact(VarsAE900 *, MobyAE900 *, int);
extern float math_clamp_angle_step(float, float, float);
extern void *SpawnDistanceFadedParticle(void *, void *, unsigned int, float, float, int, float, int, int);
extern int math_lerp_int_fraction(int, int, float);
extern float FastVecLength(void *);
extern char *moby_get_private_value_2(void *);
extern void euler_to_matrix(void *, void *);
extern void copy_matrix_rotation(void *, void *);
extern void multiply_matrix(void *, void *, void *);
extern void copy_matrix3x4(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int math_random_int_below(int);
extern float coll_get_ground_height_at_position(void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_random_float_range(float, float);
extern void * part_spawn_bubble(void *, void *, float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern void vec_clear_128(void *);
extern char *moby_spawn_scaled_effect(void *, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern void * part_spawn_spark_2(void *, void *, int, int);
extern int moby_is_in_special_class_range(void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern float math_fabs(float);
extern float square_root(float);
extern float mat_fast_helper_a(float, float);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void snd_stop_voice(int);
extern void anim_start_blended(void *, int, int, int);
extern int snd_is_voice_playing_for_owner(void *, int);
extern int PlayMobySound(int, int, void *);
extern int FastDecTimer(void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern int coll_test_point(void *, int, void *, float);
extern int math_fast_float_d(void *);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern char *part_find_owned_effect_slot(void *, unsigned int, int);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern int moby_move_over_ground(void *, void *, void *, float, float, float, float, int);
extern void part_spawn_explosion_with_sparks(void *, void *, int, float, float);
extern void RemoveMobyFromIndexList(void *, void *);
extern void moby_mark_spawned(void *);
extern float FastAddRotations(float, float);
extern void moby_queue_knockback_for_nodes(void *, void *, void *, int, int, int, int, int, float, float, float);
extern float coll_get_ground_height_under_object(void *);
extern int gfx_swap_packed_color_channels(unsigned int, int);
extern char *part_spawn_spark(void *, void *, int, int, float, int, int, int, int, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern int FloatToInt(float);
extern char *part_spawn_falling_drop(void *, void *, int, int, float, int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void * moby_spawn_template_effect(void *, void *, int, int);
extern void part_queue_ground_shadow(void *, float);

/* Leaves the current state: stops the owned sound and resets the fall. */
#define DETACH_AE900() \
    { \
        int sound; \
        moby->state = 0; \
        sound = vars->sound; \
        if (sound != -1) { \
            if (SLOT_AE900(sound).owner == moby && SLOT_AE900(sound).active) \
                func_002E59F8(sound); \
        } \
        vars->sound = -1; \
        vars->timer34 = 0x78; \
        vars->vel.f[2] = 0.0f; \
    }

/* Rotation matrix for half a turn about X. */
static __inline__ void HalfTurnAE900(VecAE900 *m)
{
    VecAE900 turn;

    turn.q = 0;
    turn.f[0] = PI_AE900;
    euler_to_matrix(m, &turn);
}

/* Copies the owner's matrix into dst. */
static __inline__ void OwnerMatrixAE900(VecAE900 *dst, MobyAE900 *owner)
{
    copy_matrix_rotation(dst, owner->matrix);
}

/* While held (state 1): the bot's matrix is its owner's, turned half a turn about X. */
static __inline__ void AlignToOwnerAE900(MobyAE900 *moby, VarsAE900 *vars)
{
    VecAE900 m1[4];
    VecAE900 m2[4];
    VecAE900 *rot = m1;
    VecAE900 *own;

    HalfTurnAE900(rot);
    own = m2;
    OwnerMatrixAE900(own, vars->owner);
    multiply_matrix(rot, own, rot);
    copy_matrix3x4(moby->matrix, rot);
}

/* Updates the bot the hero can pick up and carry: it flies, lands, gets held, and blows up when its time runs out. */
void UpdateHeldBot(MobyAE900 *moby)
{
    TemplateAE900 small;
    TemplateAE900 big;
    VecAE900 impulse;
    VecAE900 prev;
    VecAE900 up;
    VarsAE900 *vars;
    char *landed;
    MobyAE900 *owner;

    small = g_small_effect_template;
    big = g_big_effect_template;
    landed = 0;
    impulse.q = 0;
    impulse.f[2] = 2.0f * FRAME_AE900;
    up.q = 0;
    up.f[2] = 1.0f;
    vars = moby->vars;
    UpdateMobyLinks();

    if ((g_hero_state.b22B5 != 0 || g_hero_state.b22BF != 0) && moby->state == 1)
        moby->flags |= 0x41;
    else
        moby->flags &= ~0x41;

    if (g_hero_state.held == 0 || g_hero_state.held->oClass != 0x81E) {
        if (moby->state == 1) {
            moby_mark_spawned(moby);
            return;
        }
    }
    if (g_hero_state.b22B4 != 0) {
        if (moby->state == 1) {
            moby_mark_spawned(moby);
            return;
        }
    }

    owner = vars->owner;
    if (owner != 0)
        if (owner->state != 0xFE)
            if (owner->state != 0xFD)
                if (owner->oClass == 0x81E && vars->s36 == 0 && FastVecLength(vars) > 0.0f) {
                    if (g_hero_state.standing == 0 || moby_get_private_value_2(g_hero_state.standing) == 0) {
                        PredictMineImpact(vars, moby, 1);
                    } else {
                        if (PredictMineImpact(vars, moby, 0) == 0)
                            PredictMineImpact(vars, moby, 2);
                    }
                }

    if (moby->state == 1) {
        if (g_hero_state.held == 0 || g_hero_state.held->oClass != 0x81E) {
            moby_mark_spawned(moby);
            return;
        }
        AlignToOwnerAE900(moby, vars);
        moby->collData = 0;
        moby->flags |= 0x100;
        return;
    } else {
        HitAE900 hit;
        VecAE900 t120;
        VecAE900 t130;
        VecAE900 t140;
        VecAE900 t150;
        VecAE900 t160;
        VecAE900 t170;
        VecAE900 t180;
        float t;
        float dist;
        float water;
        MobyAE900 *target;

        moby->flags &= ~0x100;
        qcopy_nc(&prev, &moby->pos);
        if (!(moby->state & 4)) {
            FastVecAdd(&moby->pos, &moby->pos, &vars->vel);
            if (vars->inWater == 0) {
                vars->vel.f[2] -= 9.8f / 60.0f / 60.0f;
            } else {
                vars->vel.f[2] -= 0.98f / 60.0f / 60.0f;
                if (math_random_int_below(5) == 0) {
                    float height = coll_get_ground_height_at_position(&moby->pos, &hit.dir);
                    FastVecScale(&hit.dir, &vars->vel, 0.25f);
                    part_spawn_bubble(&moby->pos, &hit.dir, math_random_float_range(0.05f, 0.1f) * 210000.0f, height);
                }
            }
        }
        hit.owner = moby;
        hit.flags = 0x830000;
        hit.i20 = 1;
        hit.damage = (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).rate;
        qcopy(&hit.dir, &vars->vel);
        vec_fast_normalize_helper(&hit.dir, &hit.dir, 1.0f);
        hit.b18 = 2;
        hit.dir.f[3] = 5627.925f;
        hit.b19 = 1;
        hit.oClass = moby->oClass;
        hit.dir.f[2] = 1.0f;
        moby->pos.f[2] -= 0.4f;
        t = IntToFloat(g_frame_l00_counter - vars->frame) / g_effect_duration_frames;
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        moby->pos.f[2] -= vars->amp * math_fast_sin_or_cos_b(vars->phase) * t;

        if (!(moby->state & 4) && CollLine(&prev, &moby->pos, 0x10, moby, &hit)) {
            if (vars->inWater == 0 && GetCollHitMaterial() == 0 && vars->vel.f[2] < 0.0f) {
                char *splash;
                int i;

                RippleDisturb(g_ripple_object, g_ripple_param, 1, moby->pos.f[0], moby->pos.f[1], 0.5f, -0.35f);
                vars->inWater = 1;
                vec_clear_128(vars);
                vars->vel.f[2] = -1.5f * FRAME_AE900;
                t120.f[0] = moby->pos.f[0];
                t120.f[1] = moby->pos.f[1];
                t120.f[2] = g_collision_result.point.f[2];
                splash = moby_spawn_scaled_effect(&t120, 2.0f);
                if (splash)
                    splash[0x23] = 0x70;
                for (i = 0; i < 16; i++) {
                    float a = math_random_angle();
                    float r = math_random_float_range(0.0f, 3.0f * FRAME_AE900);
                    int life;

                    t130.f[0] = math_fast_sin_or_cos_a(a) * r;
                    t130.f[1] = math_fast_sin_or_cos_b(a) * r;
                    t130.f[2] = math_random_float_range(3.0f * FRAME_AE900, 6.5f * FRAME_AE900);
                    life = math_random_int_range(90, 120);
                    part_spawn_spark_2(&t120, &t130, math_random_int_below(2), life);
                }
            } else if (vars->inWater != 0 || GetCollHitMaterial() != 0) {
                if (g_collision_result.hit) {
                    if (moby_is_in_special_class_range(g_collision_result.hit) || (g_collision_result.hit->flags & 0x1000)) {
                        if (g_collision_result.hit->oClass != moby->oClass && g_collision_result.hit != g_hero_state.moby
                            && g_collision_result.hit != vars->owner) {
                            moby->bBC = 1;
                            if (moby->state != 1) {
                                qcopy(&moby->pos, &g_collision_result.point);
                                moby->pos.f[2] = coll_probe_ground_height_below(&moby->pos, 0, 0.5f);
                            }
                            goto settled;
                        }
                    }
                }
                if (g_collision_result.hit && g_collision_result.hit->oClass == moby->oClass) {
                    FastVecSub(&g_collision_result.normal, &moby->pos, &g_collision_result.hit->pos);
                    if (vars->vel.f[2] < -9.8f * FRAME_AE900) {
                        moby->bBC = 1;
                        qcopy(&moby->pos, &g_collision_result.point);
                        vec_fast_normalize(&impulse, &vars->vel, &g_collision_result.normal);
                        vec_scale_to_length(&impulse, &impulse, 2.0f * FRAME_AE900);
                        vec_scale_to_length(&up, &g_collision_result.normal, 1.0f);
                    } else {
                        qcopy(&moby->pos, &g_collision_result.point);
                        vec_scale_to_length(&t120, &g_collision_result.normal, 9.7f / 3600.0f);
                        FastVecAdd(&moby->pos, &moby->pos, &t120);
                        vec_fast_normalize(&vars->vel, &vars->vel, &g_collision_result.normal);
                        FastVecScale(&vars->vel, &vars->vel, 0.4f);
                        vec_scale_to_length(&t120, &g_collision_result.normal, 1.0f);
                        FastVecDot(&t120, &up);
                        qcopy(&t130, &g_collision_result.normal);
                        goto align;
                    }
                } else if ((g_collision_result.hit && g_collision_result.hit != g_hero_state.moby && g_collision_result.hit != vars->owner) || g_collision_result.count > 0) {
                    if (vars->inWater != 0 || GetCollHitMaterial() == 0 || vars->vel.f[2] < -9.8f * FRAME_AE900) {
                        moby->bBC = 1;
                        qcopy(&moby->pos, &g_collision_result.point);
                        vec_fast_normalize(&impulse, &vars->vel, &g_collision_result.normal);
                        vec_scale_to_length(&impulse, &impulse, 2.0f * FRAME_AE900);
                        vec_scale_to_length(&up, &g_collision_result.normal, 1.0f);
                    } else {
                        MobyAE900 *under = g_collision_result.hit;

                        if (under)
                            landed = moby_get_private_value_2(under);
                        qcopy(&moby->pos, &g_collision_result.point);
                        vec_scale_to_length(&t120, &g_collision_result.normal, 9.7f / 3600.0f);
                        FastVecAdd(&moby->pos, &moby->pos, &t120);
                        t150.q = vars->vel.q;
                        vec_fast_normalize(&vars->vel, &vars->vel, &g_collision_result.normal);
                        FastVecScale(&vars->vel, &vars->vel, 0.6f);
                        vars->vel.f[2] *= 0.5f;
                        if (vars->amp == 0.0f) {
                            float ph;

                            vars->amp = math_fabs(t150.f[2]) * 2.0f;
                            ph = -2.3561947f;
                            if (0.0f < t150.f[2]) {
                                ph = 0.78539824f;
                            }
                            vars->frame = g_frame_l00_counter;
                            vars->phase = ph;
                        }
                        vec_scale_to_length(&t120, &g_collision_result.normal, 1.0f);
                        if (FastVecDot(&t120, &up) > 0.707f) {
                            if (t150.f[2] < 0.0f) {
                                float floor = coll_probe_ground_height_below(&moby->pos, 0, 0.5f);

                                if (moby->pos.f[2] < floor)
                                    moby->pos.f[2] = floor;
                                vars->vel.f[2] = -vars->vel.f[2];
                                if (FastVecLength(vars) < 0.5f * FRAME_AE900 || landed) {
                                    vec_clear_128(vars);
                                    moby->state |= 4;
                                    moby->collData = *(int *)(moby->pClass + 0x10);
                                    if (g_collision_result.hit && landed)
                                        vars->ground = g_collision_result.hit;
                                }
                            }
                        }
                        qcopy(&t130, &g_collision_result.normal);
                    align:
                        t140.f[0] = t130.f[0] * math_fast_sin_or_cos_a(moby->rot[2]) + t130.f[1] * math_fast_sin_or_cos_b(moby->rot[2]);
                        t140.f[1] = t130.f[1] * math_fast_sin_or_cos_a(moby->rot[2]) - t130.f[0] * math_fast_sin_or_cos_b(moby->rot[2]);
                        t140.f[2] = t130.f[2];
                        moby->rot[0] = math_clamp_angle_step(moby->rot[0],
                            -mat_fast_helper_a(square_root(t140.f[0] * t140.f[0] + t140.f[2] * t140.f[2]), t140.f[1]),
                            PI_AE900 * FRAME_AE900);
                        moby->rot[1] = math_clamp_angle_step(moby->rot[1], mat_fast_helper_a(t140.f[2], t140.f[0]), PI_AE900 * FRAME_AE900);
                    }
                }
            }
        } else if (moby->state & 4) {
            float floor = coll_probe_ground_height_below(&moby->pos, 0, 0.5f);

            if (vars->ground) {
                if (vars->ground->state != 0xFE)
                    if (vars->ground->state != 0xFD)
                        goto alive;
                moby->bBC = 1;
                vars->ground = 0;
                goto check;
            alive:
                if (g_collision_result.hit) {
                    landed = moby_get_private_value_2(g_collision_result.hit);
                    if (landed)
                        moby_transform_point_and_rotation_by_parent(moby, vars->ground, &moby->pos, moby->rot, &moby->pos, moby->rot);
                }
            check:
                if (!landed) {
                    DETACH_AE900();
                    vars->ground = 0;
                }
            } else if (!(moby->state & 8)) {
                if (moby->pos.f[2] - floor < 1.0f / 90.0f) {
                    moby->pos.f[2] = floor;
                    vars->timer34 = 0;
                    if (g_collision_result.hit && moby_get_private_value_2(g_collision_result.hit))
                        vars->ground = g_collision_result.hit;
                } else {
                    DETACH_AE900();
                }
            }
            target = vars->target;
            if (target == 0)
                goto lost;
            if (target->state == 0xFE)
                goto lost;
            if (target->state == 0xFD)
                goto lost;
            if (target->flags & 0x1000)
                goto kept;
        lost:
            if (moby->state & 8) {
                DETACH_AE900();
                vars->target = 0;
                if (moby->b43)
                    anim_start_blended(moby, 0, 0, 10);
            }
        kept:
            if (vars->target != 0 && (moby->state & 8)) {
                t130.q = moby->pos.q;
                if (moby->b60 & 2) {
                    if (moby->b42 == 1 && moby->b43 != 2)
                        anim_start_blended(moby, 2, 0, 10);
                }
                if (!snd_is_voice_playing_for_owner(moby, vars->sound))
                    vars->sound = PlayMobySound(1, 4, moby);
                vars->pull += 0.25f * FRAME_AE900;
                if (vars->pull > 16.0f * FRAME_AE900)
                    vars->pull = 16.0f * FRAME_AE900;
                if (vars->bob == 1) {
                    moby->pos.f[2] += 0.05f;
                    if (FastDecTimer(&vars->timer48)) {
                        vars->timer48 = 7;
                        vars->bob = 2;
                    }
                } else if (vars->bob == 2) {
                    moby->pos.f[2] -= 0.05f;
                    if (FastDecTimer(&vars->timer48))
                        vars->bob = 0;
                }
                FastVecSub(&t120, &vars->target->pos, &moby->pos);
                vec_scale_to_length(&t120, &t120, vars->pull);
                FastVecAdd(&moby->pos, &moby->pos, &t120);
                make_hit_descriptor(&t140, moby, 0x10000, &t120, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).rate);
                qcopy(&t170, &moby->pos);
                t170.f[2] += 0.35f;
                if (coll_process_hit(&t170, 0x10, moby, &t140, 0.35f)) {
                    MobyAE900 *blocker = g_collision_result.hit;

                    if (blocker && blocker->oClass != 0x363 && blocker->oClass != 0x81F && blocker->oClass != 0x458
                        && blocker->oClass != 0x365 && blocker->oClass != 0x367)
                        moby->bBC = 1;
                }
                qcopy(&t170, &moby->pos);
                t170.f[2] += 0.25f;
                if (coll_test_point(&t170, 0, moby, 0.25f)) {
                    FastVecSub(&t180, &g_collision_result.p30, &t170);
                    FastVecAdd(&moby->pos, &moby->pos, &t180);
                }
                if (math_fast_float_d(&vars->timer58))
                    moby->bBC = 1;
            }
            moby_scale_owner_words_by_angles(moby, &vars->f60, &vars->f64, 30.0f * DEG_AE900, 30.0f * DEG_AE900 * FRAME_AE900,
                          17.0f * DEG_AE900 * FRAME_AE900);
            if (moby->state & 4) {
                FastVecSub(&t120, &moby->pos, &prev);
                vars->vel.q = t120.q;
            }
        }
    settled:
        if (!(moby->state & 2)) {
            if (FastDecTimer(&vars->timer34)) {
                moby->state |= 2;
                vars->target = 0;
            }
        }
        {
            char *link = part_find_owned_effect_slot(moby, 0x830000, 0);

            if (link && *(MobyAE900 **)(link + 0x20) && (*(MobyAE900 **)(link + 0x20))->oClass != moby->oClass)
                moby->bBC = 1;
        }
        moby->bA8 = 0xFF;
        if (moby->state & 2) {
            if (!(moby->state & 4)
                || (vec_distance_xy(&g_hero_state.moby->pos, &moby->pos) < 0.75f
                    && math_fabs(moby->pos.f[2] - g_hero_state.z) < 0.25f && (moby->state & 8))) {
                moby->bBC = 1;
            } else if (fast_vec_dist(&g_hero_state.moby->pos, &moby->pos) < 0.75f) {
                FastVecSub(&t140, &moby->pos, &g_hero_state.moby->pos);
                t120.q = t140.q;
                vec_scale_to_length(&t120, &t120, 0.75f);
                FastVecAdd(&t140, &g_hero_state.moby->pos, &t120);
                t130.q = t140.q;
                moby_move_over_ground(moby, &moby->pos, &t130, 0.4f, 0.25f, 0.25f, 30.0f * DEG_AE900, 0);
            } else {
                int i = 0;
                MobyAE900 *other = g_target_l00_list[0];

                while (other) {
                    if (!(fast_vec_dist(&moby->pos, &other->pos) > 30.0f)) {
                        if (fast_vec_dist(&moby->pos, &other->pos) < 0.75f) {
                            moby->bBC = 1;
                            break;
                        }
                    }
                    i++;
                    other = g_target_l00_list[i];
                }
            }
        }
        vars->i78 = 0;
        if (vars->i5C < 0 || g_effect_skip_flag != 0) {
            part_spawn_explosion_with_sparks(moby, &moby->pos, -1, 0.33f, 13.0f);
            RemoveMobyFromIndexList(moby, g_moby_index_list_head);
            moby_mark_spawned(moby);
        }
        if (vars->amp > 0.05f) {
            vars->amp *= 0.988f;
            if (vars->amp < 0.05f)
                vars->amp = 0.05f;
        }
        t = IntToFloat(g_frame_l00_counter - vars->frame) / g_effect_duration_frames;
        if (t > 1.0f)
            t = 1.0f;
        else if (t < 0.0f)
            t = 0.0f;
        vars->phase = FastAddRotations(vars->phase, 360.0f * DEG_AE900 * FRAME_AE900);
        moby->pos.f[2] = moby->pos.f[2] + vars->amp * math_fast_sin_or_cos_b(vars->phase) * t + 0.4f;
        if (moby->bBC) {
            dist = vec_distance_xy(&moby->pos, &g_camera_l00_position);
            if (vars->inWater == 0) {
                float radius = 2.0f;
                int count;

                if ((*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded)
                    radius = 3.0f;
                count = coll_process_hit(&moby->pos, 0x10, moby, 0, radius);
                t120.q = moby->pos.q;
                moby_queue_knockback_for_nodes(moby, &t120, g_area_hit_targets, count, 0, 0x810000, 4, 1, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).rate, 0.25f, 1.5f);
            }
            water = coll_get_ground_height_under_object(&moby->pos);
            if (vars->inWater != 0) {
                float surface;
                int i;
                int j;
                int l;
                int cb;
                int cg;
                int cr;
                int c;

                t120.q = moby->pos.q;
                t120.f[2] += 3.5f;
                surface = coll_probe_ground_height_below(&t120, 0, 0.5f);
                for (i = 0; i < 150; i++) {
                    t140.q = 0;
                    t140.f[0] = math_random_float_range(-1.0f, 1.0f);
                    t140.f[1] = math_random_float_range(-1.0f, 1.0f);
                    t140.f[2] = math_random_float_range(-0.5f, -2.0f);
                    t130.q = t140.q;
                    vec_scale_to_length(&t130, &t130, math_random_float_range(4.0f * FRAME_AE900, 8.0f * FRAME_AE900));
                    part_spawn_bubble(&moby->pos, &t130, math_random_float_range(0.05f, 0.1f) * 210000.0f, surface);
                }
                cr = 0x60;
                cg = 0x60;
                cb = 0x7F;
                for (j = 0; j < 150; j++) {
                    float rr;
                    float ang;
                    float half;
                    int c1;
                    int c2;

                    t140.q = 0;
                    t140.f[0] = math_random_float_range(-0.75f * FRAME_AE900, 0.75f * FRAME_AE900);
                    t140.f[1] = math_random_float_range(-0.75f * FRAME_AE900, 0.75f * FRAME_AE900);
                    t140.f[2] = math_random_float_range(4.0f * FRAME_AE900, 16.0f * FRAME_AE900);
                    t130.q = t140.q;
                    rr = math_random_float_range(0.0f, 0.35f);
                    half = 0.5f;
                    ang = math_random_angle();
                    t140.f[0] = math_fast_sin_or_cos_a(ang) * rr;
                    t140.f[1] = math_fast_sin_or_cos_b(ang) * rr;
                    t140.f[2] = 0.0f;
                    FastVecAdd(&t140, &t140, &moby->pos);
                    t140.f[2] = surface + half;
                    t130.f[2] -= rr * (8.0f * FRAME_AE900);
                    c1 = (0x16 << 24) | (cb << 16) | (cg << 8);
                    c2 = (cb << 16) | (cg << 8);
                    SpawnDistanceFadedParticle(&t140, &t130, 0, math_random_float_range(0.35f, 1.25f), surface,
                                      c1 | cr, 1.0f / 180.0f, c2 | cr, 1);
                }
                c = (0x7F << 24) | (cb << 16) | (cg << 8);
                for (l = 0; l < 20; l++) {
                    int c1 = math_lerp_int_fraction(0x7F000000, c | cr, math_random_float_range(0.25f, 1.0f));
                    int c2 = math_lerp_int_fraction(0, ((cb / 2) << 16) | ((cg / 2) << 8) | (cr / 2),
                                               math_random_float_range(0.5f, 1.0f));
                    float sz;
                    int life;
                    char **defs;
                    int tex;

                    t140.f[0] = math_random_float_range(-3.0f, 3.0f);
                    t140.f[1] = math_random_float_range(-3.0f, 3.0f);
                    t140.f[2] = math_random_float_range(4.0f * FRAME_AE900, 14.0f * FRAME_AE900);
                    vec_scale_to_length(&t140, &t140, math_random_float_range(1.5f, 3.0f) * FRAME_AE900);
                    t140.f[2] = math_random_float_range(3.0f, 6.0f) * FRAME_AE900;
                    t130.q = moby->pos.q;
                    t130.f[2] = surface;
                    c1 = gfx_swap_packed_color_channels(c1, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                    c2 = gfx_swap_packed_color_channels(c2, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                    sz = math_random_float_range(0.15f * 210000.0f, 0.25f * 210000.0f);
                    life = math_random_int_range(90, 150);
                    defs = (char **)g_effect_definitions;
                    tex = *(unsigned char *)defs[11];
                    part_spawn_spark(&t130, &t140, c1, c2, sz, life, 1, tex, -1, 0);
                }
            } else if (water + 2.0f < moby->pos.f[2]) {
                vec_clear_128(&t120);
                SpawnExplosionEffects(moby, &t120, 0, 0.0f, 0.0f, 3, 3, 5, 2.0f, 1.0f, 4.0f, 1.0f, 2, 7.0f, 0, 1, -1,
                              (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0, 0x810001);
            } else {
                float scale = 1.0f;
                int count;
                int i;

                if ((*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded)
                    scale = 1.5f;
                count = FloatToInt(dist * 15.0f);
                for (i = 0; i < count; i++) {
                    int kind = math_random_int_below(4);
                    RatesAE900 *rates = (RatesAE900 *)&t120;
                    float r;
                    float a;

                    *rates = g_effect_default_rates;
                    t140.q = 0;
                    t140.f[0] = math_random_float_range(-0.5f * FRAME_AE900, 0.5f * FRAME_AE900) * scale;
                    t140.f[1] = math_random_float_range(-0.5f * FRAME_AE900, 0.5f * FRAME_AE900) * scale;
                    t140.f[2] = math_random_float_range(4.0f * FRAME_AE900, rates->v[kind]) * scale;
                    t130.q = t140.q;
                    r = math_random_float_range(0.0f, kind == 1 ? 0.5f : 0.25f) * scale;
                    a = math_random_angle();
                    t140.f[0] = math_fast_sin_or_cos_a(a) * r;
                    t140.f[1] = math_fast_sin_or_cos_b(a) * r;
                    t140.i[2] = 0;
                    FastVecAdd(&t140, &t140, &moby->pos);
                    t140.f[2] -= r * math_fast_sin_or_cos_a(0.785398f);
                    t130.f[2] -= r * (8.0f * FRAME_AE900);
                    switch (kind) {
                    case 0: {
                        int c = gfx_swap_packed_color_channels(0x1F101820, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        float f = math_random_float_range(200000.0f, 300000.0f) * scale;
                        part_spawn_falling_drop(&t140, &t130, c, 0x101010, f, math_random_int_range(180, 240), 0);
                        break;
                    }
                    case 1: {
                        int c1 = gfx_swap_packed_color_channels(0x3F081020, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        int c2 = gfx_swap_packed_color_channels(0x0F081020, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        part_spawn_falling_drop(&t140, &t130, c1, c2, math_random_float_range(50000.0f, 100000.0f) * scale, 180, 1);
                        break;
                    }
                    case 2: {
                        int color;
                        int c1;
                        int c2;
                        float f;
                        int roll = math_random_int_below(100);

                        color = 0x2F486078;
                        if (roll <= 39)
                            color = 0x5FF8F8F8;
                        c1 = gfx_swap_packed_color_channels(color, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        c2 = gfx_swap_packed_color_channels(0x0F000020, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        f = scale * 150000.0f;
                        part_spawn_falling_drop(&t140, &t130, c1, c2, f, math_random_int_range(30, 45), 2);
                        break;
                    }
                    case 3: {
                        int c1 = math_lerp_int_fraction(0x7F000000, 0x7F182030, math_random_float_range(0.25f, 1.0f));
                        int c2 = math_lerp_int_fraction(0, 0x5F5F5F, math_random_float_range(0.5f, 1.0f));
                        float f;

                        c1 = gfx_swap_packed_color_channels(c1, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        c2 = gfx_swap_packed_color_channels(c2, (*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded != 0);
                        vec_build_spherical_offset(&t130, math_random_float_range(0.0f, 1.0f) * FRAME_AE900, a, math_random_angle());
                        f = math_random_float_range(200000.0f, 300000.0f) * scale;
                        part_spawn_falling_drop(&t140, &t130, c1, c2, f, math_random_int_range(240, 300), 3);
                        break;
                    }
                    }
                }
            }
            moby->bBC = 0;
            if ((*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded)
                PlayMobySound(3, 0, moby);
            else
                PlayMobySound(2, 0, moby);
            {
                ShakeAE900 *shake = &g_scalar_transition_state;

                if (dist < 20.0f)
                    shake->amount = 0.4f - dist * 0.0175f;
                else
                    shake->amount = 0.4f - 20.0f * 0.0175f;
            }
            g_scalar_transition_state.counter = 0;
            g_scalar_transition_state.frames = 25;
            if ((*(g_weapon_table_2 + g_item_slot_to_record[0x22])).upgraded)
                moby_spawn_template_effect(&big, &moby->pos, 0, 0);
            else
                moby_spawn_template_effect(&small, &moby->pos, 0, 0);
            RemoveMobyFromIndexList(moby, g_moby_index_list_head);
            moby_mark_spawned(moby);
        } else {
            part_queue_ground_shadow(moby, 0.25f);
        }
    }
}
