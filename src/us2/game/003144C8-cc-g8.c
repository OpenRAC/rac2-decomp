/* func_US2_003144C8, the USA v2.00 copy of func_003136D0: the same C, where rename func_0029B720 becomes func_US2_0029C510. */
#include "common.h"

/*
 * func_US2_003144C8, the nanotech ball update (RAC1 nanotech_ball_update). It has a unit of its own
 * because PAL and USA v2.00 have func_003146C0 but not this function, and its jump table must not
 * reach their .rodata.
 *
 * Eight initial values below are overwritten before they are read: both `owner = moby`, `i = 0` in the
 * state 2 block, `spawn_rate = 5`, `part = 0`, `slot_part = 0`, `old_health = 0` and `effect = 0` in the fly-in arm. Each is
 * a value that local really holds at some point. They bring the function to 1024 RTL insns at gcse,
 * which sizes the PRE hash table at 513: that is what puts the four PRE registers of &vec_b, &vec_c,
 * &vars->v20 and &moby->rot_row2 into retail's spill slots 0x7C-0x88. 988-1003 or 1024-1039 insns all fit.
 * Without them the code is the same apart from those four slots.
 */
/* Adapted from RAC1 nanotech_ball_update (OpenRAC/rac1-decomp, GPL-3.0). */
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) Vec;
typedef struct Moby { char pad0[16]; Vec pos; unsigned char state; char pad21[15]; unsigned char update_dist; char pad31[3]; unsigned short flags; char pad36[0x32]; void *pvars; char pad6c[0x2c]; int collision; char pad9c[0x1c]; struct Moby *owner; unsigned char command; char padbd[3]; Vec rot_row0,rot_row1,rot_row2,rot; } Moby;
typedef struct { char pad0[0x80]; struct { Vec pos; } motion; char pad90[0x14c]; short invulnerable_frames; char pad1de[0xe2]; Vec gravity_dir; char pad2d0[0x1fe4]; unsigned char vehicle_mode; char pad22b5[0x217]; struct { int hp; } health; } Hero;
typedef struct { float x, y, z, w; } __attribute__((aligned(16))) V_2D9EA0;
typedef struct { float x, y, z; } V3_2D9EA0;
typedef struct Part_2D9EA0 {
    int f0;
    int f4;
    unsigned char b8;
    char p9[3];
    float fC;
    V_2D9EA0 pos;
} Part_2D9EA0;
typedef struct Ext_2D9EA0 {
    int f0;
    union {
        struct { struct Moby *owner; float scale; float ang; } s;
        V3_2D9EA0 a;
    } u;
    V3_2D9EA0 b;
    short h1C;
    short h1E;
} Ext_2D9EA0;
typedef struct D_2D9EA0 {
    float f0;
    float f4;
    short h8;
    unsigned char hA;
    unsigned char pending;
    struct Moby *owner;
    V_2D9EA0 pos;
    V_2D9EA0 v20;
    Part_2D9EA0 *slots[8];
    int f50;
    short h54;
    unsigned char h56;
    unsigned char special;
    short h58[4];
    float f60[4];
    char p70[0xC];
    int f7C;
} D_2D9EA0;
extern char g_hero_state[], g_hero_position[];
extern Vec g_nanotech_ball_axes[], g_nanotech_ball_basis_vectors[];
extern float D_001AF180_gp[] SDATA(D_001AF180);
extern char g_camera_l00_position[];
extern Moby *g_nanotech_ball_moby;
extern int g_player_stats;
extern unsigned char g_cheat_flags[] MACRO_ADDR;
extern unsigned char g_extras_unlocked_flag;
extern int g_turret_target_moby, g_game_time;
extern int g_nanotech_special_phase __attribute__((sda)), g_nanotech_amount_alt __attribute__((sda));
extern int moby_transform_point_by_attachment(void *,void *,void *,void *);
extern int moby_is_state_six(void *), moby_is_in_selected_zone(void *);
extern void moby_set_state(void *,int,int), level_forward_value_b_us2(int);
extern float g_nanotech_base_length __attribute__((sda));
extern float g_nanotech_scale_wobble __attribute__((sda));
extern unsigned short g_nanotech_duration __attribute__((sda));
extern float g_nanotech_hero_offset __attribute__((sda));
extern float g_nanotech_hero_push __attribute__((sda));
extern int g_nanotech_life_max __attribute__((sda));
extern int g_nanotech_life_min __attribute__((sda));
extern int g_nanotech_random_value __attribute__((sda));
extern unsigned short g_nanotech_timer_init __attribute__((sda));
extern float g_nanotech_spin_step __attribute__((sda));
extern int g_nanotech_slot_phase __attribute__((sda));
extern float g_nanotech_slot_scale_alt __attribute__((sda));
extern float g_nanotech_slot_scale __attribute__((sda));
extern unsigned char g_nanotech_phase_step __attribute__((sda));
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);

extern float g_nanotech_pulse_amp __attribute__((sda));
extern void gravity_offset_position(void *, void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern float math_random_signed_float_range(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float, float);
extern float fast_vec_dist(void *, void *);
extern int is_nanotech_ball_target_line_clear(void *);
extern void FastVecScale(void *, void *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, float, void *);
extern int math_random_int_range(int, int);
extern void update_nanotech_ball_slot_offsets(void);
extern int math_fast_helper_a(void *, float);
extern void gfx_register_world_draw_callback(void (*)(unsigned char *), Moby *);
extern void draw_nanotech_ball(unsigned char *);
extern float vec_distance_xy(void *, void *);
extern void emitter_get_slot_position(void *, void *, int);
extern Part_2D9EA0 *part_spawn_bluish_fade(void *, int, int, int);
extern void part_spawn_sparkles(void *);
extern int EmitFourTimedParticlePairs(void *);
extern void moby_ground_snapped_update(void *);
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern float IntToFloat(int);
extern float cubic_hermite_scalar(float, float, float, float, float);

/* Updates a nanotech ball: it follows its owner, keeps its glowing particle slots moving, and when the hero needs health it flies in and heals (v2.00 copy). */
void nanotech_ball_update_us2(Moby *moby) {
    V_2D9EA0 vec_a, vec_b, vec_c, vec_d, vec_e, vec_f, vec_g;
    D_2D9EA0 *vars = (D_2D9EA0 *)moby->pvars;

    switch (moby->state) {
    case 0: {
        Moby *owner = moby;
        int i;
        moby->state = 1;
        moby->flags |= 0x41;
        moby->collision = 0;
        moby->command = 0;
        owner = moby->owner;
        qcopy_nc(&moby->pos, &owner->pos);
        qcopy_nc(&moby->rot, &owner->rot);
        vec_scale_to_length(&vars->pos, &moby->rot_row2, 0.5f);
        FastVecAdd(&vars->pos, &vars->pos, &moby->pos);
        *(int *)&vars->f0 = 0;
        vars->h8 = 0;
        vars->f4 = math_random_float_range(vars->f0, 3.1415927f);
        vars->h56 = 0;
        vars->owner = 0;
        for (i = 0; i < 4; i++) vars->f60[i] = (float)math_random_int_below(0xFF);
        for (i = 0; i < 4; i++) vars->h58[i] = g_nanotech_duration;
        for (i = 0; i < 8; i++) vars->slots[i] = 0;
        if (g_nanotech_ball_moby == 0) {
            euler_rotation_basis(&moby->rot_row0, &moby->rot);
            g_nanotech_ball_moby = moby;
            moby->update_dist = 0xFF;
            vars->pending = 0;
            vec_scale_to_length(&g_nanotech_ball_axes[0], &moby->rot_row0, g_nanotech_base_length);
            qcopy_nc(&g_nanotech_ball_basis_vectors[0], &moby->rot_row2);
            vec_scale_to_length(&g_nanotech_ball_axes[1], &moby->rot_row1, g_nanotech_base_length);
            qcopy_nc(&g_nanotech_ball_basis_vectors[1], &moby->rot_row0);
            vec_scale_to_length(&g_nanotech_ball_axes[2], &moby->rot_row2, g_nanotech_base_length);
            qcopy_nc(&g_nanotech_ball_basis_vectors[2], &moby->rot_row1);
            FastVecAdd(&g_nanotech_ball_axes[3], &moby->rot_row0, &moby->rot_row2);
            vec_scale_to_length(&g_nanotech_ball_axes[3], &g_nanotech_ball_axes[3], g_nanotech_base_length);
            FastVecCross(&g_nanotech_ball_basis_vectors[3], &g_nanotech_ball_axes[3], &moby->rot_row1);
            FastVecAdd(&g_nanotech_ball_axes[4], &moby->rot_row0, &moby->rot_row1);
            vec_scale_to_length(&g_nanotech_ball_axes[4], &g_nanotech_ball_axes[4], g_nanotech_base_length);
            FastVecCross(&g_nanotech_ball_basis_vectors[4], &g_nanotech_ball_axes[4], &moby->rot_row2);
            FastVecSub(&g_nanotech_ball_axes[5], &moby->rot_row1, &moby->rot_row2);
            vec_scale_to_length(&g_nanotech_ball_axes[5], &g_nanotech_ball_axes[5], g_nanotech_base_length);
            FastVecCross(&g_nanotech_ball_basis_vectors[5], &g_nanotech_ball_axes[5], &moby->rot_row0);
            FastVecSub(&g_nanotech_ball_axes[6], &moby->rot_row0, &moby->rot_row2);
            vec_scale_to_length(&g_nanotech_ball_axes[6], &g_nanotech_ball_axes[6], g_nanotech_base_length);
            FastVecCross(&g_nanotech_ball_basis_vectors[6], &g_nanotech_ball_axes[6], &moby->rot_row1);
            FastVecSub(&g_nanotech_ball_axes[7], &moby->rot_row0, &moby->rot_row1);
            vec_scale_to_length(&g_nanotech_ball_axes[7], &g_nanotech_ball_axes[7], g_nanotech_base_length);
            FastVecCross(&g_nanotech_ball_basis_vectors[7], &g_nanotech_ball_axes[7], &moby->rot_row2);
        }
        {
            float angle;
            angle = math_random_float_range(0.0f, 6.2831855f);
            vec_build_spherical_offset(&vars->v20, 1.0f, angle, math_random_float_range(-1.5707964f, 1.5707964f));
        }
        vars->v20.w = math_random_signed_float_range(0.785398006f, 1.5707964f);
    }
    case 1: {
        Moby *owner = moby;
        qcopy_nc(&moby->pos, &moby->owner->pos);
        qcopy_nc(&vars->pos, &moby->owner->pos);
        gravity_offset_position(&moby->pos, &vars->pos, &vars->pos, -0.5f);
        owner = moby->owner;
        if ((signed char)owner->state < 0 || moby_is_state_six(owner) || owner == moby) {
            moby->state = 2;
            vars->f50 = 0;
        }
    }
    case 2:
        if (moby->state == 2) {
            int i = 0;
            qcopy_nc(&vars->pos, &moby->pos);
            gravity_offset_position(&moby->pos, &vars->pos, &vars->pos, -0.5f);
            moby_ground_snapped_update(moby);
            for (i = 0; i < 8; i++) {
                if (vars->slots[i] != 0) {
                    Ext_2D9EA0 *ext = (Ext_2D9EA0 *)(vars->slots[i] + 1);
                    ext->u.s.scale = g_nanotech_scale_wobble * math_fast_sin_or_cos_b(ext->u.s.ang) + g_nanotech_base_length;
                    ext->u.s.ang = FastAddRotations(ext->u.s.ang, D_001AF180_gp[i]);
                }
            }
        }
        {
            Hero *hero = (Hero *)g_hero_state;
            int max_health = g_player_stats;
            if (hero->vehicle_mode == 1) max_health = 4;
            if (moby->state != 1 && g_nanotech_ball_moby != 0 && (D_2D9EA0 *)g_nanotech_ball_moby->pvars != 0 && hero->health.hp != 0
                && (hero->health.hp + ((D_2D9EA0 *)g_nanotech_ball_moby->pvars)->pending < max_health || (g_cheat_flags[2] != 0 && hero->invulnerable_frames == 0))
                && (vars->slots[0] || vars->slots[1] || vars->slots[2] || vars->slots[3] || vars->slots[4] || vars->slots[5] || vars->slots[6] || vars->slots[7])
                && fast_vec_dist(&moby->pos, g_hero_position) < 10.0f
                && is_nanotech_ball_target_line_clear(moby)) {
                int i;
                moby->state = 3;
                ((D_2D9EA0 *)g_nanotech_ball_moby->pvars)->pending++;
                if (g_cheat_flags[2] != 0) *(short *)(g_hero_position + 0x15C) = 0x258;
                vars->h54 = g_nanotech_timer_init;
                FastVecScale(&vec_d, g_hero_position + 0x240, -g_nanotech_hero_offset);
                FastVecAdd(&vec_d, g_hero_position, &vec_d);
                FastVecScale(&vec_a, g_hero_position + 0x240, -g_nanotech_hero_push);
                FastVecSub(&vec_c, &vec_d, &moby->pos);
                gravity_offset_position(&moby->pos, &vec_c, &vec_c, 0.5f);
                FastVecCross(&vec_e, &vec_c, &vec_a);
                FastVecCross(&vec_a, &vec_e, &vec_c);
                math_apply_axis_rotation_to_quat(&vec_a, &vec_a, -1.5707964f, &vec_c);
                vec_scale_to_length(&vec_a, &vec_a, g_nanotech_hero_push);
                FastVecScale(&vec_f, &vec_c, 0.5f);
                for (i = 0; i < 8; i++) {
                    if (vars->slots[i] != 0) {
                        Ext_2D9EA0 *ext = (Ext_2D9EA0 *)(vars->slots[i] + 1);
                        math_apply_axis_rotation_to_quat(&vec_b, &vec_a, (float)i * 0.44854968786239624f, &vec_c);
                        FastVecAdd(&vec_g, &vec_f, &vec_b);
                        {
                            V3_2D9EA0 *dst = &ext->u.a;
                            dst->x = vec_g.x;
                            dst->y = vec_g.y;
                            dst->z = vec_g.z;
                        }
                        {
                            V3_2D9EA0 *dst = &ext->b;
                            V3_2D9EA0 *src = (V3_2D9EA0 *)&vars->slots[i]->pos;
                            dst->x = src->x;
                            dst->y = src->y;
                            dst->z = src->z;
                        }
                        ext->h1E = ext->h1C = math_random_int_range(g_nanotech_life_min, g_nanotech_life_max);
                    }
                }
            }
        }
        vars->f0 = g_nanotech_pulse_amp * math_fast_sin_or_cos_b(vars->f4);
        vars->f4 = FastAddRotations(vars->f4, g_nanotech_spin_step);
        if (g_nanotech_ball_moby == moby) update_nanotech_ball_slot_offsets();
        qcopy(&vec_a, &moby->pos);
        gravity_offset_position(&moby->pos, &vec_a, &vec_a, -0.5f);
        vec_a.w = 1.0f;
        if (math_fast_helper_a(&vec_a, 64.0f) >= 0) {
            int i;
            int spawn_rate = 5;
            gfx_register_world_draw_callback(draw_nanotech_ball, moby);
            if (10.0f < vec_distance_xy(&moby->pos, g_camera_l00_position)) spawn_rate = 5;
            else spawn_rate = 40;
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *part = 0;
                Part_2D9EA0 *slot_part = 0;
                emitter_get_slot_position(moby, &vec_b, i);
                part = part_spawn_bluish_fade(&vec_b, spawn_rate, 2, 0);
                if (part != 0) {
                    Ext_2D9EA0 *ext = (Ext_2D9EA0 *)(part + 1);
                    qcopy(&vec_c, &moby->pos);
                    qzero_nc(&vec_d);
                    if (moby->state == 1) moby_transform_point_by_attachment(moby, moby->owner, &moby->pos, &vec_d);
                    else if (vars->owner) {
                        moby_transform_point_by_attachment(moby, vars->owner, &moby->pos, &vec_d);
                        FastVecSub(&vec_c, &vec_c, &vec_d);
                    }
                    FastVecAdd(&vec_b, &vec_b, &vec_d);
                    ext->b.x = part->pos.x - vec_c.x;
                    ext->b.y = part->pos.y - vec_c.y;
                    ext->b.z = part->pos.z - vec_c.z;
                    if (moby->state == 2) ext->u.s.owner = moby;
                    else ext->u.s.owner = moby->owner;
                    if (vars->special) part->f4 = g_nanotech_special_phase;
                    else part->f4 = g_nanotech_slot_phase;
                    part->fC = g_nanotech_slot_scale;
                }
                slot_part = vars->slots[i];
                if (slot_part == 0) {
                    vars->slots[i] = part_spawn_bluish_fade(&vec_b, 0, 1, 0);
                    if (vars->slots[i] != 0) {
                        Ext_2D9EA0 *ext = (Ext_2D9EA0 *)(vars->slots[i] + 1);
                        ext->u.s.scale = g_nanotech_base_length;
                        ext->u.s.ang = 0.0f;
                        vars->slots[i]->fC = g_nanotech_slot_scale_alt;
                        if (vars->special) vars->slots[i]->f4 = g_nanotech_special_phase;
                        else vars->slots[i]->f4 = g_nanotech_slot_phase;
                    }
                } else {
                    qcopy_nc(&slot_part->pos, &vec_b);
                    slot_part->b8 += g_nanotech_phase_step;
                }
            }
        } else if (g_turret_target_moby || vars->owner) {
            int i;
            for (i = 0; i < 8; i++) if (vars->slots[i]) qcopy_nc(&vars->slots[i]->pos, &moby->pos);
        }
        break;
    case 3:
        if (g_nanotech_ball_moby == moby) update_nanotech_ball_slot_offsets();
        if (vars->h56 != 0) {
            FastVecScale(&moby->pos, g_hero_state + 0x2C0, -g_nanotech_hero_offset);
            FastVecAdd(&moby->pos, g_hero_state + 0x80, &moby->pos);
            moby->rot.w = 0.523598849773407f;
            if (EmitFourTimedParticlePairs(moby) != 0 && math_random_int_below(5) == 0) part_spawn_sparkles(moby);
        }
        {
            Hero *hero = (Hero *)g_hero_state;
            int max_health = g_player_stats;
            if (hero->vehicle_mode == 1) max_health = 4;
            if (hero->health.hp == max_health && hero->invulnerable_frames != 0 && g_cheat_flags[2] != 0) {
                int random_value = g_nanotech_random_value;
                if (vars->h54 < random_value) {
                    int i;
                    vars->h54 = random_value;
                    for (i = 0; i < 4; i++) vars->h58[i]++;
                }
            }
        }
        if (FastDecTimer(&vars->h54)) {
            int i;
            for (i = 0; i < 8; i++) {
                if (vars->slots[i] != 0) {
                    part_kill(vars->slots[i]);
                    vars->slots[i] = 0;
                }
            }
            if (g_nanotech_ball_moby == moby) moby->state = 4;
            else moby_mark_spawned(moby);
        } else {
            int i;
            FastVecScale(&vec_c, g_hero_state + 0x2C0, -g_nanotech_hero_offset);
            FastVecAdd(&vec_c, g_hero_state + 0x80, &vec_c);
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *part = vars->slots[i];
                Ext_2D9EA0 *ext;
                if (part == 0) continue;
                ext = (Ext_2D9EA0 *)(part + 1);
                if (FastDecTimer(&ext->h1E)) {
                    if (vars->h56 == 0) {
                        Hero *hero = (Hero *)g_hero_state;
                        int max_health = g_player_stats;
                        int old_health = 0;
                        if (hero->vehicle_mode == 1) max_health = 4;
                        old_health = hero->health.hp;
                        if (hero->health.hp != 0) {
                            int amount = 1;
                            if (g_extras_unlocked_flag) amount = g_nanotech_amount_alt;
                            if (vars->special) {
                                int new_health = hero->health.hp + amount * 4;
                                hero->health.hp = (max_health < new_health) ? max_health : new_health;
                            } else {
                                int new_health = hero->health.hp + amount;
                                hero->health.hp = (max_health < new_health) ? max_health : new_health;
                            }
                            if (old_health != ((Hero *)g_hero_state)->health.hp) level_forward_value_b_us2(0x168);
                        }
                        {
                            D_2D9EA0 *ball_vars = (D_2D9EA0 *)g_nanotech_ball_moby->pvars;
                            ball_vars->pending--;
                            if ((signed char)ball_vars->pending < 0) ball_vars->pending = 0;
                        }
                        if (vars->special) snd_play_from_class_bank(1, 0x20, moby, 0x200);
                        else snd_play_from_class_bank(1, 0x20, moby, 0x1F5);
                        vars->h56 = 1;
                    }
                    part_kill(part);
                    vars->slots[i] = 0;
                } else {
                    float inv_k;
                    float ratio;
                    Part_2D9EA0 *effect = 0;
                    V_2D9EA0 *mid = &vec_e;
                    {
                        qcopy(mid, &part->pos);
                    }
                    ratio = IntToFloat(ext->h1C);
                    ratio = (float)ext->h1E / ratio;
                    {
                        V3_2D9EA0 *src = &ext->b;
                        vec_b.x = src->x;
                        vec_b.y = src->y;
                        vec_b.z = src->z;
                    }
                    vec_b.w = 0.0f;
                    inv_k = 1.0f - ratio;
                    vec_a.x = vec_b.x - ext->u.a.x;
                    vec_a.y = vec_b.y - ext->u.a.y;
                    vec_a.z = vec_b.z - ext->u.a.z;
                    vec_d.x = vec_c.x - ext->u.a.x;
                    vec_d.y = vec_c.y - ext->u.a.y;
                    vec_d.z = vec_c.z - ext->u.a.z;
                    part->pos.x = cubic_hermite_scalar(vec_a.x, vec_b.x, vec_c.x, vec_d.x, inv_k);
                    part->pos.y = cubic_hermite_scalar(vec_a.y, vec_b.y, vec_c.y, vec_d.y, inv_k);
                    part->pos.z = cubic_hermite_scalar(vec_a.z, vec_b.z, vec_c.z, vec_d.z, inv_k);
                    vec_f.x = math_random_signed_float_range(0.0f, 0.00999999978f) + part->pos.x;
                    vec_f.y = math_random_signed_float_range(0.0f, 0.00999999978f) + part->pos.y;
                    vec_f.z = math_random_signed_float_range(0.0f, 0.00999999978f) + part->pos.z;
                    effect = part_spawn_bluish_fade(&vec_f, 0x14, 0, 0);
                    if (effect != 0) {
                        if (vars->special) effect->f4 = g_nanotech_special_phase;
                        else effect->f4 = g_nanotech_slot_phase;
                        effect->fC = g_nanotech_slot_scale;
                    }
                    FastVecAdd(&vec_e, &part->pos, &vec_e);
                    FastVecScale(&vec_e, &vec_e, 0.5f);
                    vec_f.x = math_random_signed_float_range(0.0f, 0.00999999978f) + vec_e.x;
                    vec_f.y = math_random_signed_float_range(0.0f, 0.00999999978f) + vec_e.y;
                    vec_f.z = math_random_signed_float_range(0.0f, 0.00999999978f) + vec_e.z;
                    effect = part_spawn_bluish_fade(&vec_f, 0x14, 0, 0);
                    if (effect != 0) {
                        if (vars->special) effect->f4 = g_nanotech_special_phase;
                        else effect->f4 = g_nanotech_slot_phase;
                        effect->fC = g_nanotech_slot_scale;
                    }
                }
            }
        }
        break;
    case 4:
        if (g_nanotech_ball_moby == moby) update_nanotech_ball_slot_offsets();
        break;
    case 5:
        if ((g_game_time & 1) && moby_is_in_selected_zone(&moby->pos)) moby_set_state(moby, 2, -1);
        break;
    }
}
