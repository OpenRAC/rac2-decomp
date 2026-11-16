#include "common.h"

/*
 * func_PAL_00314B5C, the PAL copy of func_003136D0, the nanotech ball update (RAC1
 * nanotech_ball_update): the same C, where D_001AF174 and D_001AF158 are words (lw, not lhu),
 * the frame counts D_001AF174, D_001AF158 and D_001AF15C and the random lifetime are scaled to
 * 50 Hz, and the literals 0x258, 5, 40, 0x14 and 0x168 become 0x1F4, 4, 33, 0x11 and 0x12C.
 * It has a unit of its own for its flags and its jump table.
 *
 * Five initial values below are overwritten before they are read: `n = 5`, `e = 0`, `p = 0`,
 * `old_health = 0` and `n = 0` in the fly-in arm. Each is a value that local really holds at some
 * point. As in func_003136D0, they set the RTL insn count at gcse, which sizes the PRE hash table
 * (527 buckets in this copy): that is what puts the four PRE registers of &v10, &v20, &data->v20 and
 * &moby->rot_row2 into retail's spill slots 0x7C-0x88.
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
extern void moby_set_state(void *,int,int), level_forward_value_b_pal(int);
extern float g_nanotech_base_length __attribute__((sda));
extern float g_nanotech_scale_wobble __attribute__((sda));
extern int g_nanotech_duration __attribute__((sda));
extern float g_nanotech_hero_offset __attribute__((sda));
extern float g_nanotech_hero_push __attribute__((sda));
extern int g_nanotech_life_max __attribute__((sda));
extern int g_nanotech_life_min __attribute__((sda));
extern int g_nanotech_random_value __attribute__((sda));
extern int g_nanotech_timer_init __attribute__((sda));
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
extern void part_spawn_sparkles_pal(void *);
extern int emit_four_timed_particle_pairs_pal(void *);
extern void moby_ground_snapped_update_pal(void *);
extern int FastDecTimer(void *);
extern void part_kill(void *);
extern void moby_mark_spawned(void *);
extern int snd_play_from_class_bank(int, int, void *, int);
extern float IntToFloat(int);
extern float cubic_hermite_scalar(float, float, float, float, float);

/* Updates a nanotech ball: it flies out from its owner, spawns the nanotech slots, hovers and pulses, and shrinks away when its time runs out (PAL: 50 Hz timings). */
void nanotech_ball_update_pal(Moby *moby) {
    V_2D9EA0 v0, v10, v20, v30, v40, v50, v60;
    D_2D9EA0 *data = (D_2D9EA0 *)moby->pvars;

    switch (moby->state) {
    case 0: {
        Moby *c;
        int i;
        moby->state = 1;
        moby->flags |= 0x41;
        moby->collision = 0;
        moby->command = 0;
        c = moby->owner;
        qcopy_nc(&moby->pos, &c->pos);
        qcopy_nc(&moby->rot, &c->rot);
        vec_scale_to_length(&data->pos, &moby->rot_row2, 0.5f);
        FastVecAdd(&data->pos, &data->pos, &moby->pos);
        *(int *)&data->f0 = 0;
        data->h8 = 0;
        data->f4 = math_random_float_range(data->f0, 3.1415927f);
        data->h56 = 0;
        data->owner = 0;
        for (i = 0; i < 4; i++) data->f60[i] = (float)math_random_int_below(0xFF);
        for (i = 0; i < 4; i++) data->h58[i] = ((s32)(g_nanotech_duration) * 5 + 2) / 6;
        for (i = 0; i < 8; i++) data->slots[i] = 0;
        if (g_nanotech_ball_moby == 0) {
            euler_rotation_basis(&moby->rot_row0, &moby->rot);
            g_nanotech_ball_moby = moby;
            moby->update_dist = 0xFF;
            data->pending = 0;
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
            float a;
            a = math_random_float_range(0.0f, 6.2831855f);
            vec_build_spherical_offset(&data->v20, 1.0f, a, math_random_float_range(-1.5707964f, 1.5707964f));
        }
        data->v20.w = math_random_signed_float_range(0.785398006f, 1.5707964f);
    }
    case 1: {
        Moby *c;
        qcopy_nc(&moby->pos, &moby->owner->pos);
        qcopy_nc(&data->pos, &moby->owner->pos);
        gravity_offset_position(&moby->pos, &data->pos, &data->pos, -0.5f);
        c = moby->owner;
        if ((signed char)c->state < 0 || moby_is_state_six(c) || c == moby) {
            moby->state = 2;
            data->f50 = 0;
        }
    }
    case 2:
        if (moby->state == 2) {
            int i;
            qcopy_nc(&data->pos, &moby->pos);
            gravity_offset_position(&moby->pos, &data->pos, &data->pos, -0.5f);
            moby_ground_snapped_update_pal(moby);
            for (i = 0; i < 8; i++) {
                if (data->slots[i] != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(data->slots[i] + 1);
                    x->u.s.scale = g_nanotech_scale_wobble * math_fast_sin_or_cos_b(x->u.s.ang) + g_nanotech_base_length;
                    x->u.s.ang = FastAddRotations(x->u.s.ang, D_001AF180_gp[i]);
                }
            }
        }
        {
            Hero *g = (Hero *)g_hero_state;
            int lim = g_player_stats;
            if (g->vehicle_mode == 1) lim = 4;
            if (moby->state != 1 && g_nanotech_ball_moby != 0 && (D_2D9EA0 *)g_nanotech_ball_moby->pvars != 0 && g->health.hp != 0
                && (g->health.hp + ((D_2D9EA0 *)g_nanotech_ball_moby->pvars)->pending < lim || (g_cheat_flags[2] != 0 && g->invulnerable_frames == 0))
                && (data->slots[0] || data->slots[1] || data->slots[2] || data->slots[3] || data->slots[4] || data->slots[5] || data->slots[6] || data->slots[7])
                && fast_vec_dist(&moby->pos, g_hero_position) < 10.0f
                && is_nanotech_ball_target_line_clear(moby)) {
                int i;
                moby->state = 3;
                ((D_2D9EA0 *)g_nanotech_ball_moby->pvars)->pending++;
                if (g_cheat_flags[2] != 0) *(short *)(g_hero_position + 0x15C) = 0x1f4;
                data->h54 = ((s32)(g_nanotech_timer_init) * 5 + 2) / 6;
                FastVecScale(&v30, g_hero_position + 0x240, -g_nanotech_hero_offset);
                FastVecAdd(&v30, g_hero_position, &v30);
                FastVecScale(&v0, g_hero_position + 0x240, -g_nanotech_hero_push);
                FastVecSub(&v20, &v30, &moby->pos);
                gravity_offset_position(&moby->pos, &v20, &v20, 0.5f);
                FastVecCross(&v40, &v20, &v0);
                FastVecCross(&v0, &v40, &v20);
                math_apply_axis_rotation_to_quat(&v0, &v0, -1.5707964f, &v20);
                vec_scale_to_length(&v0, &v0, g_nanotech_hero_push);
                FastVecScale(&v50, &v20, 0.5f);
                for (i = 0; i < 8; i++) {
                    if (data->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(data->slots[i] + 1);
                        math_apply_axis_rotation_to_quat(&v10, &v0, (float)i * 0.44854968786239624f, &v20);
                        FastVecAdd(&v60, &v50, &v10);
                        {
                            V3_2D9EA0 *dst = &x->u.a;
                            dst->x = v60.x;
                            dst->y = v60.y;
                            dst->z = v60.z;
                        }
                        {
                            V3_2D9EA0 *dst = &x->b;
                            V3_2D9EA0 *src = (V3_2D9EA0 *)&data->slots[i]->pos;
                            dst->x = src->x;
                            dst->y = src->y;
                            dst->z = src->z;
                        }
                        x->h1E = x->h1C = ((s32)(math_random_int_range(g_nanotech_life_min, g_nanotech_life_max)) * 5 + 2) / 6;
                    }
                }
            }
        }
        data->f0 = g_nanotech_pulse_amp * math_fast_sin_or_cos_b(data->f4);
        data->f4 = FastAddRotations(data->f4, g_nanotech_spin_step);
        if (g_nanotech_ball_moby == moby) update_nanotech_ball_slot_offsets();
        qcopy(&v0, &moby->pos);
        gravity_offset_position(&moby->pos, &v0, &v0, -0.5f);
        v0.w = 1.0f;
        if (math_fast_helper_a(&v0, 64.0f) >= 0) {
            int i;
            int n = 5;
            gfx_register_world_draw_callback(draw_nanotech_ball, moby);
            if (10.0f < vec_distance_xy(&moby->pos, g_camera_l00_position)) n = 4;
            else n = 33;
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = 0;
                Part_2D9EA0 *p = 0;
                emitter_get_slot_position(moby, &v10, i);
                e = part_spawn_bluish_fade(&v10, n, 2, 0);
                if (e != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(e + 1);
                    qcopy(&v20, &moby->pos);
                    qzero_nc(&v30);
                    if (moby->state == 1) moby_transform_point_by_attachment(moby, moby->owner, &moby->pos, &v30);
                    else if (data->owner) {
                        moby_transform_point_by_attachment(moby, data->owner, &moby->pos, &v30);
                        FastVecSub(&v20, &v20, &v30);
                    }
                    FastVecAdd(&v10, &v10, &v30);
                    x->b.x = e->pos.x - v20.x;
                    x->b.y = e->pos.y - v20.y;
                    x->b.z = e->pos.z - v20.z;
                    if (moby->state == 2) x->u.s.owner = moby;
                    else x->u.s.owner = moby->owner;
                    if (data->special) e->f4 = g_nanotech_special_phase;
                    else e->f4 = g_nanotech_slot_phase;
                    e->fC = g_nanotech_slot_scale;
                }
                p = data->slots[i];
                if (p == 0) {
                    data->slots[i] = part_spawn_bluish_fade(&v10, 0, 1, 0);
                    if (data->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(data->slots[i] + 1);
                        x->u.s.scale = g_nanotech_base_length;
                        x->u.s.ang = 0.0f;
                        data->slots[i]->fC = g_nanotech_slot_scale_alt;
                        if (data->special) data->slots[i]->f4 = g_nanotech_special_phase;
                        else data->slots[i]->f4 = g_nanotech_slot_phase;
                    }
                } else {
                    qcopy_nc(&p->pos, &v10);
                    p->b8 += g_nanotech_phase_step;
                }
            }
        } else if (g_turret_target_moby || data->owner) {
            int i;
            for (i = 0; i < 8; i++) if (data->slots[i]) qcopy_nc(&data->slots[i]->pos, &moby->pos);
        }
        break;
    case 3:
        if (g_nanotech_ball_moby == moby) update_nanotech_ball_slot_offsets();
        if (data->h56 != 0) {
            FastVecScale(&moby->pos, g_hero_state + 0x2C0, -g_nanotech_hero_offset);
            FastVecAdd(&moby->pos, g_hero_state + 0x80, &moby->pos);
            moby->rot.w = 0.523598849773407f;
            if (emit_four_timed_particle_pairs_pal(moby) != 0 && math_random_int_below(5) == 0) part_spawn_sparkles_pal(moby);
        }
        {
            Hero *g = (Hero *)g_hero_state;
            int lim = g_player_stats;
            if (g->vehicle_mode == 1) lim = 4;
            if (g->health.hp == lim && g->invulnerable_frames != 0 && g_cheat_flags[2] != 0) {
                int r = ((s32)(g_nanotech_random_value) * 5 + 2) / 6;
                if (data->h54 < r) {
                    int i;
                    data->h54 = r;
                    for (i = 0; i < 4; i++) data->h58[i]++;
                }
            }
        }
        if (FastDecTimer(&data->h54)) {
            int i;
            for (i = 0; i < 8; i++) {
                if (data->slots[i] != 0) {
                    part_kill(data->slots[i]);
                    data->slots[i] = 0;
                }
            }
            if (g_nanotech_ball_moby == moby) moby->state = 4;
            else moby_mark_spawned(moby);
        } else {
            int i;
            FastVecScale(&v20, g_hero_state + 0x2C0, -g_nanotech_hero_offset);
            FastVecAdd(&v20, g_hero_state + 0x80, &v20);
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = data->slots[i];
                Ext_2D9EA0 *x;
                if (e == 0) continue;
                x = (Ext_2D9EA0 *)(e + 1);
                if (FastDecTimer(&x->h1E)) {
                    if (data->h56 == 0) {
                        Hero *g = (Hero *)g_hero_state;
                        int lim = g_player_stats;
                        int old_health = 0;
                        if (g->vehicle_mode == 1) lim = 4;
                        old_health = g->health.hp;
                        if (g->health.hp != 0) {
                            int amount = 1;
                            if (g_extras_unlocked_flag) amount = g_nanotech_amount_alt;
                            if (data->special) {
                                int t = g->health.hp + amount * 4;
                                g->health.hp = (lim < t) ? lim : t;
                            } else {
                                int t = g->health.hp + amount;
                                g->health.hp = (lim < t) ? lim : t;
                            }
                            if (old_health != ((Hero *)g_hero_state)->health.hp) level_forward_value_b_pal(0x12c);
                        }
                        {
                            D_2D9EA0 *o = (D_2D9EA0 *)g_nanotech_ball_moby->pvars;
                            o->pending--;
                            if ((signed char)o->pending < 0) o->pending = 0;
                        }
                        if (data->special) snd_play_from_class_bank(1, 0x20, moby, MOBY_CLASS_PURPLE_NANOTECH_CRATE);
                        else snd_play_from_class_bank(1, 0x20, moby, MOBY_CLASS_NANOTECH_CRATE);
                        data->h56 = 1;
                    }
                    part_kill(e);
                    data->slots[i] = 0;
                } else {
                    float t;
                    float k;
                    Part_2D9EA0 *n = 0;
                    V_2D9EA0 *mid = &v40;
                    {
                        qcopy(mid, &e->pos);
                    }
                    k = IntToFloat(x->h1C);
                    k = (float)x->h1E / k;
                    {
                        V3_2D9EA0 *src = &x->b;
                        v10.x = src->x;
                        v10.y = src->y;
                        v10.z = src->z;
                    }
                    v10.w = 0.0f;
                    t = 1.0f - k;
                    v0.x = v10.x - x->u.a.x;
                    v0.y = v10.y - x->u.a.y;
                    v0.z = v10.z - x->u.a.z;
                    v30.x = v20.x - x->u.a.x;
                    v30.y = v20.y - x->u.a.y;
                    v30.z = v20.z - x->u.a.z;
                    e->pos.x = cubic_hermite_scalar(v0.x, v10.x, v20.x, v30.x, t);
                    e->pos.y = cubic_hermite_scalar(v0.y, v10.y, v20.y, v30.y, t);
                    e->pos.z = cubic_hermite_scalar(v0.z, v10.z, v20.z, v30.z, t);
                    v50.x = math_random_signed_float_range(0.0f, 0.00999999978f) + e->pos.x;
                    v50.y = math_random_signed_float_range(0.0f, 0.00999999978f) + e->pos.y;
                    v50.z = math_random_signed_float_range(0.0f, 0.00999999978f) + e->pos.z;
                    n = part_spawn_bluish_fade(&v50, 0x11, 0, 0);
                    if (n != 0) {
                        if (data->special) n->f4 = g_nanotech_special_phase;
                        else n->f4 = g_nanotech_slot_phase;
                        n->fC = g_nanotech_slot_scale;
                    }
                    FastVecAdd(&v40, &e->pos, &v40);
                    FastVecScale(&v40, &v40, 0.5f);
                    v50.x = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.x;
                    v50.y = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.y;
                    v50.z = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.z;
                    n = part_spawn_bluish_fade(&v50, 0x11, 0, 0);
                    if (n != 0) {
                        if (data->special) n->f4 = g_nanotech_special_phase;
                        else n->f4 = g_nanotech_slot_phase;
                        n->fC = g_nanotech_slot_scale;
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
