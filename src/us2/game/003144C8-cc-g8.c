/* func_US2_003144C8, the USA v2.00 copy of func_003136D0: the same C, where rename func_0029B720 becomes func_US2_0029C510. */
#include "common.h"

/*
 * func_US2_003144C8, the nanotech ball update (RAC1 nanotech_ball_update). It has a unit of its own
 * because PAL and USA v2.00 have func_003146C0 but not this function, and its jump table must not
 * reach their .rodata.
 *
 * Eight initial values below are overwritten before they are read: both `c = m`, `i = 0` in the
 * state 2 block, `n = 5`, `e = 0`, `p = 0`, `old_health = 0` and `n = 0` in the fly-in arm. Each is
 * a value that local really holds at some point. They bring the function to 1024 RTL insns at gcse,
 * which sizes the PRE hash table at 513: that is what puts the four PRE registers of &v10, &v20,
 * &d->v20 and &m->rot_row2 into retail's spill slots 0x7C-0x88. 988-1003 or 1024-1039 insns all fit.
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
extern Vec D_L00_0023A670[], D_L00_0023A6F0[];
extern float D_001AF180_gp[] SDATA(D_001AF180);
extern char g_camera_l00_position[];
extern Moby *D_L00_001B1AEC;
extern int D_001A7A00;
extern unsigned char D_001A7A44[] MACRO_ADDR;
extern unsigned char D_001A7A0A;
extern int D_001AD7EC, g_game_time;
extern int D_001AF11C __attribute__((sda)), D_001AF1A0 __attribute__((sda));
extern int moby_transform_point_by_attachment(void *,void *,void *,void *);
extern int moby_is_state_six(void *), moby_is_in_selected_zone(void *);
extern void moby_set_state(void *,int,int), func_US2_0029C510(int);
extern float D_001AF130 __attribute__((sda));
extern float D_001AF178 __attribute__((sda));
extern unsigned short D_001AF174 __attribute__((sda));
extern float D_001AF170 __attribute__((sda));
extern float D_001AF16C __attribute__((sda));
extern int D_001AF164 __attribute__((sda));
extern int D_001AF160 __attribute__((sda));
extern int D_001AF15C __attribute__((sda));
extern unsigned short D_001AF158 __attribute__((sda));
extern float D_001AF128 __attribute__((sda));
extern int D_001AF118 __attribute__((sda));
extern float D_001AF114 __attribute__((sda));
extern float D_001AF110 __attribute__((sda));
extern unsigned char D_001AF10C __attribute__((sda));
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);

extern float D_001AF12C __attribute__((sda));
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

void func_US2_003144C8(Moby *m) {
    V_2D9EA0 v0, v10, v20, v30, v40, v50, v60;
    D_2D9EA0 *d = (D_2D9EA0 *)m->pvars;

    switch (m->state) {
    case 0: {
        Moby *c = m;
        int i;
        m->state = 1;
        m->flags |= 0x41;
        m->collision = 0;
        m->command = 0;
        c = m->owner;
        qcopy_nc(&m->pos, &c->pos);
        qcopy_nc(&m->rot, &c->rot);
        vec_scale_to_length(&d->pos, &m->rot_row2, 0.5f);
        FastVecAdd(&d->pos, &d->pos, &m->pos);
        *(int *)&d->f0 = 0;
        d->h8 = 0;
        d->f4 = math_random_float_range(d->f0, 3.1415927f);
        d->h56 = 0;
        d->owner = 0;
        for (i = 0; i < 4; i++) d->f60[i] = (float)math_random_int_below(0xFF);
        for (i = 0; i < 4; i++) d->h58[i] = D_001AF174;
        for (i = 0; i < 8; i++) d->slots[i] = 0;
        if (D_L00_001B1AEC == 0) {
            euler_rotation_basis(&m->rot_row0, &m->rot);
            D_L00_001B1AEC = m;
            m->update_dist = 0xFF;
            d->pending = 0;
            vec_scale_to_length(&D_L00_0023A670[0], &m->rot_row0, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[0], &m->rot_row2);
            vec_scale_to_length(&D_L00_0023A670[1], &m->rot_row1, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[1], &m->rot_row0);
            vec_scale_to_length(&D_L00_0023A670[2], &m->rot_row2, D_001AF130);
            qcopy_nc(&D_L00_0023A6F0[2], &m->rot_row1);
            FastVecAdd(&D_L00_0023A670[3], &m->rot_row0, &m->rot_row2);
            vec_scale_to_length(&D_L00_0023A670[3], &D_L00_0023A670[3], D_001AF130);
            FastVecCross(&D_L00_0023A6F0[3], &D_L00_0023A670[3], &m->rot_row1);
            FastVecAdd(&D_L00_0023A670[4], &m->rot_row0, &m->rot_row1);
            vec_scale_to_length(&D_L00_0023A670[4], &D_L00_0023A670[4], D_001AF130);
            FastVecCross(&D_L00_0023A6F0[4], &D_L00_0023A670[4], &m->rot_row2);
            FastVecSub(&D_L00_0023A670[5], &m->rot_row1, &m->rot_row2);
            vec_scale_to_length(&D_L00_0023A670[5], &D_L00_0023A670[5], D_001AF130);
            FastVecCross(&D_L00_0023A6F0[5], &D_L00_0023A670[5], &m->rot_row0);
            FastVecSub(&D_L00_0023A670[6], &m->rot_row0, &m->rot_row2);
            vec_scale_to_length(&D_L00_0023A670[6], &D_L00_0023A670[6], D_001AF130);
            FastVecCross(&D_L00_0023A6F0[6], &D_L00_0023A670[6], &m->rot_row1);
            FastVecSub(&D_L00_0023A670[7], &m->rot_row0, &m->rot_row1);
            vec_scale_to_length(&D_L00_0023A670[7], &D_L00_0023A670[7], D_001AF130);
            FastVecCross(&D_L00_0023A6F0[7], &D_L00_0023A670[7], &m->rot_row2);
        }
        {
            float a;
            a = math_random_float_range(0.0f, 6.2831855f);
            vec_build_spherical_offset(&d->v20, 1.0f, a, math_random_float_range(-1.5707964f, 1.5707964f));
        }
        d->v20.w = math_random_signed_float_range(0.785398006f, 1.5707964f);
    }
    case 1: {
        Moby *c = m;
        qcopy_nc(&m->pos, &m->owner->pos);
        qcopy_nc(&d->pos, &m->owner->pos);
        gravity_offset_position(&m->pos, &d->pos, &d->pos, -0.5f);
        c = m->owner;
        if ((signed char)c->state < 0 || moby_is_state_six(c) || c == m) {
            m->state = 2;
            d->f50 = 0;
        }
    }
    case 2:
        if (m->state == 2) {
            int i = 0;
            qcopy_nc(&d->pos, &m->pos);
            gravity_offset_position(&m->pos, &d->pos, &d->pos, -0.5f);
            moby_ground_snapped_update(m);
            for (i = 0; i < 8; i++) {
                if (d->slots[i] != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
                    x->u.s.scale = D_001AF178 * math_fast_sin_or_cos_b(x->u.s.ang) + D_001AF130;
                    x->u.s.ang = FastAddRotations(x->u.s.ang, D_001AF180_gp[i]);
                }
            }
        }
        {
            Hero *g = (Hero *)g_hero_state;
            int lim = D_001A7A00;
            if (g->vehicle_mode == 1) lim = 4;
            if (m->state != 1 && D_L00_001B1AEC != 0 && (D_2D9EA0 *)D_L00_001B1AEC->pvars != 0 && g->health.hp != 0
                && (g->health.hp + ((D_2D9EA0 *)D_L00_001B1AEC->pvars)->pending < lim || (D_001A7A44[2] != 0 && g->invulnerable_frames == 0))
                && (d->slots[0] || d->slots[1] || d->slots[2] || d->slots[3] || d->slots[4] || d->slots[5] || d->slots[6] || d->slots[7])
                && fast_vec_dist(&m->pos, g_hero_position) < 10.0f
                && is_nanotech_ball_target_line_clear(m)) {
                int i;
                m->state = 3;
                ((D_2D9EA0 *)D_L00_001B1AEC->pvars)->pending++;
                if (D_001A7A44[2] != 0) *(short *)(g_hero_position + 0x15C) = 0x258;
                d->h54 = D_001AF158;
                FastVecScale(&v30, g_hero_position + 0x240, -D_001AF170);
                FastVecAdd(&v30, g_hero_position, &v30);
                FastVecScale(&v0, g_hero_position + 0x240, -D_001AF16C);
                FastVecSub(&v20, &v30, &m->pos);
                gravity_offset_position(&m->pos, &v20, &v20, 0.5f);
                FastVecCross(&v40, &v20, &v0);
                FastVecCross(&v0, &v40, &v20);
                math_apply_axis_rotation_to_quat(&v0, &v0, -1.5707964f, &v20);
                vec_scale_to_length(&v0, &v0, D_001AF16C);
                FastVecScale(&v50, &v20, 0.5f);
                for (i = 0; i < 8; i++) {
                    if (d->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
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
                            V3_2D9EA0 *src = (V3_2D9EA0 *)&d->slots[i]->pos;
                            dst->x = src->x;
                            dst->y = src->y;
                            dst->z = src->z;
                        }
                        x->h1E = x->h1C = math_random_int_range(D_001AF160, D_001AF164);
                    }
                }
            }
        }
        d->f0 = D_001AF12C * math_fast_sin_or_cos_b(d->f4);
        d->f4 = FastAddRotations(d->f4, D_001AF128);
        if (D_L00_001B1AEC == m) update_nanotech_ball_slot_offsets();
        qcopy(&v0, &m->pos);
        gravity_offset_position(&m->pos, &v0, &v0, -0.5f);
        v0.w = 1.0f;
        if (math_fast_helper_a(&v0, 64.0f) >= 0) {
            int i;
            int n = 5;
            gfx_register_world_draw_callback(draw_nanotech_ball, m);
            if (10.0f < vec_distance_xy(&m->pos, g_camera_l00_position)) n = 5;
            else n = 40;
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = 0;
                Part_2D9EA0 *p = 0;
                emitter_get_slot_position(m, &v10, i);
                e = part_spawn_bluish_fade(&v10, n, 2, 0);
                if (e != 0) {
                    Ext_2D9EA0 *x = (Ext_2D9EA0 *)(e + 1);
                    qcopy(&v20, &m->pos);
                    qzero_nc(&v30);
                    if (m->state == 1) moby_transform_point_by_attachment(m, m->owner, &m->pos, &v30);
                    else if (d->owner) {
                        moby_transform_point_by_attachment(m, d->owner, &m->pos, &v30);
                        FastVecSub(&v20, &v20, &v30);
                    }
                    FastVecAdd(&v10, &v10, &v30);
                    x->b.x = e->pos.x - v20.x;
                    x->b.y = e->pos.y - v20.y;
                    x->b.z = e->pos.z - v20.z;
                    if (m->state == 2) x->u.s.owner = m;
                    else x->u.s.owner = m->owner;
                    if (d->special) e->f4 = D_001AF11C;
                    else e->f4 = D_001AF118;
                    e->fC = D_001AF110;
                }
                p = d->slots[i];
                if (p == 0) {
                    d->slots[i] = part_spawn_bluish_fade(&v10, 0, 1, 0);
                    if (d->slots[i] != 0) {
                        Ext_2D9EA0 *x = (Ext_2D9EA0 *)(d->slots[i] + 1);
                        x->u.s.scale = D_001AF130;
                        x->u.s.ang = 0.0f;
                        d->slots[i]->fC = D_001AF114;
                        if (d->special) d->slots[i]->f4 = D_001AF11C;
                        else d->slots[i]->f4 = D_001AF118;
                    }
                } else {
                    qcopy_nc(&p->pos, &v10);
                    p->b8 += D_001AF10C;
                }
            }
        } else if (D_001AD7EC || d->owner) {
            int i;
            for (i = 0; i < 8; i++) if (d->slots[i]) qcopy_nc(&d->slots[i]->pos, &m->pos);
        }
        break;
    case 3:
        if (D_L00_001B1AEC == m) update_nanotech_ball_slot_offsets();
        if (d->h56 != 0) {
            FastVecScale(&m->pos, g_hero_state + 0x2C0, -D_001AF170);
            FastVecAdd(&m->pos, g_hero_state + 0x80, &m->pos);
            m->rot.w = 0.523598849773407f;
            if (EmitFourTimedParticlePairs(m) != 0 && math_random_int_below(5) == 0) part_spawn_sparkles(m);
        }
        {
            Hero *g = (Hero *)g_hero_state;
            int lim = D_001A7A00;
            if (g->vehicle_mode == 1) lim = 4;
            if (g->health.hp == lim && g->invulnerable_frames != 0 && D_001A7A44[2] != 0) {
                int r = D_001AF15C;
                if (d->h54 < r) {
                    int i;
                    d->h54 = r;
                    for (i = 0; i < 4; i++) d->h58[i]++;
                }
            }
        }
        if (FastDecTimer(&d->h54)) {
            int i;
            for (i = 0; i < 8; i++) {
                if (d->slots[i] != 0) {
                    part_kill(d->slots[i]);
                    d->slots[i] = 0;
                }
            }
            if (D_L00_001B1AEC == m) m->state = 4;
            else moby_mark_spawned(m);
        } else {
            int i;
            FastVecScale(&v20, g_hero_state + 0x2C0, -D_001AF170);
            FastVecAdd(&v20, g_hero_state + 0x80, &v20);
            for (i = 0; i < 8; i++) {
                Part_2D9EA0 *e = d->slots[i];
                Ext_2D9EA0 *x;
                if (e == 0) continue;
                x = (Ext_2D9EA0 *)(e + 1);
                if (FastDecTimer(&x->h1E)) {
                    if (d->h56 == 0) {
                        Hero *g = (Hero *)g_hero_state;
                        int lim = D_001A7A00;
                        int old_health = 0;
                        if (g->vehicle_mode == 1) lim = 4;
                        old_health = g->health.hp;
                        if (g->health.hp != 0) {
                            int amount = 1;
                            if (D_001A7A0A) amount = D_001AF1A0;
                            if (d->special) {
                                int t = g->health.hp + amount * 4;
                                g->health.hp = (lim < t) ? lim : t;
                            } else {
                                int t = g->health.hp + amount;
                                g->health.hp = (lim < t) ? lim : t;
                            }
                            if (old_health != ((Hero *)g_hero_state)->health.hp) func_US2_0029C510(0x168);
                        }
                        {
                            D_2D9EA0 *o = (D_2D9EA0 *)D_L00_001B1AEC->pvars;
                            o->pending--;
                            if ((signed char)o->pending < 0) o->pending = 0;
                        }
                        if (d->special) snd_play_from_class_bank(1, 0x20, m, 0x200);
                        else snd_play_from_class_bank(1, 0x20, m, 0x1F5);
                        d->h56 = 1;
                    }
                    part_kill(e);
                    d->slots[i] = 0;
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
                    n = part_spawn_bluish_fade(&v50, 0x14, 0, 0);
                    if (n != 0) {
                        if (d->special) n->f4 = D_001AF11C;
                        else n->f4 = D_001AF118;
                        n->fC = D_001AF110;
                    }
                    FastVecAdd(&v40, &e->pos, &v40);
                    FastVecScale(&v40, &v40, 0.5f);
                    v50.x = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.x;
                    v50.y = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.y;
                    v50.z = math_random_signed_float_range(0.0f, 0.00999999978f) + v40.z;
                    n = part_spawn_bluish_fade(&v50, 0x14, 0, 0);
                    if (n != 0) {
                        if (d->special) n->f4 = D_001AF11C;
                        else n->f4 = D_001AF118;
                        n->fC = D_001AF110;
                    }
                }
            }
        }
        break;
    case 4:
        if (D_L00_001B1AEC == m) update_nanotech_ball_slot_offsets();
        break;
    case 5:
        if ((g_game_time & 1) && moby_is_in_selected_zone(&m->pos)) moby_set_state(m, 2, -1);
        break;
    }
}
