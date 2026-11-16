#include "include_asm.h"
#include "common.h"

typedef int V4 __attribute__((mode(TI)));
typedef union { V4 q; float f[4]; } Vec;

/* The lock-on tether: a chain of twenty points that hangs from the player's hand to up to two
   locked targets, its glow spots and sparks. Only the fields this function touches are named. */
typedef struct Tgt {
    char pad0[0x10];
    float pos[4];                       /* 0x10 */
    unsigned char kind;                 /* 0x20 */
    char pad1[3];
    struct TgtClass *cls;               /* 0x24 */
    char pad2[0x98 - 0x28];
    int f98;                            /* 0x98 */
} Tgt;

typedef struct TgtClass {
    char pad0[0x10];
    int f10;                            /* 0x10 */
    char pad1[0x46 - 0x14];
    short id;                           /* 0x46 */
} TgtClass;

typedef struct Rope {
    float a[4];                         /* 0x00 */
    float b[4];                         /* 0x10 */
    Tgt *lockA;                         /* 0x20 */
    char pad1[0x38 - 0x24];
    Tgt *lockB;                         /* 0x38 */
    short pad2;
    short count;                        /* 0x3E */
    union {
        struct {
            unsigned short h40, h42, h44, h46;
        } s;
        unsigned long q;                /* 0x40 */
    } u;
} Rope;

typedef struct Moby {
    char pad0[0x68];
    Rope *rope;                         /* 0x68 */
    char pad1[0xAA - 0x6C];
    unsigned short tag;                 /* 0xAA */
} Moby;

typedef struct Hit {
    float dir[4];                       /* 0x00 */
    char pad0[0x18 - 0x10];
    unsigned char kind;                 /* 0x18 */
    unsigned char flag;                 /* 0x19 */
    unsigned short tag;                 /* 0x1A */
    char pad1[0x30 - 0x1C];
} Hit;

typedef struct Cam {
    char pad0[0x80];
    float x, y;
    char pad1[0x98 - 0x88];
    float f98;
    char pad2[0x2290 - 0x9C];
    char *ent;
} Cam;

typedef struct Level { char pad0[0x12]; unsigned char cur; } Level;
typedef struct Slot { char pad0[4]; unsigned char on; char pad1[0x70 - 5]; float f70; char pad2[0xE0 - 0x74]; } Slot;

extern Level g_item_slot_to_record;
extern Slot g_item_stage_records[];
extern Cam g_hero_state;
extern char g_tether_axis_vectors[];
extern int g_hero_l08_input_blocked;
extern float g_str_effect_name[] MACRO_ADDR;
extern int g_tether_l08_timer;
extern short g_tether_l08_segment_timers[] MACRO_ADDR;
extern short g_tether_l08_segment_fades[] MACRO_ADDR;
extern short g_tether_segment_resets[] MACRO_ADDR;
extern short g_tether_l08_segment_x[] MACRO_ADDR;
extern float g_hero_l08_extra_state[];
extern char g_hero_position_vec[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult g_hero_moby_target;
extern Tgt *g_target_l08_list[];
extern float g_tether_rope_coll_starts[][4], g_tether_rope_coll_deltas[][4];
extern Vec g_tether_l08_rope_points[2][20];
extern V4 g_tether_rope_anchor;
extern float g_tether_rope_old_heights[];
extern Vec g_tether_rope_offsets[];
extern float g_tether_rope_heights[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 g_tether_rope_headers[];
extern Node5 g_tether_l08_rope_nodes[];

extern float g_tether_rope_reach __attribute__((sda));
extern float g_tether_rope_slack_a __attribute__((sda));
extern float g_tether_rope_max_angle __attribute__((sda));
extern float g_tether_rope_wave_spacing __attribute__((sda));
extern float g_tether_rope_amp_start __attribute__((sda));
extern float g_tether_rope_amp_end __attribute__((sda));
extern float g_tether_l08_rope_wave_phase __attribute__((sda));
extern float g_tether_rope_wave_speed __attribute__((sda));
extern float g_tether_rope_twist_phase __attribute__((sda));
extern float g_tether_rope_twist_speed __attribute__((sda));
extern float g_tether_rope_wave_step __attribute__((sda));
extern float g_tether_rope_wave_amp __attribute__((sda));
extern float g_tether_rope_radial_scale __attribute__((sda));
extern float g_tether_l08_rope_wave_phase_2 __attribute__((sda));
extern float g_tether_rope_phase_speed __attribute__((sda));
extern float g_tether_rope_amp_phase_step __attribute__((sda));
extern float g_tether_rope_height_jitter_min __attribute__((sda));
extern float g_tether_rope_height_jitter_max __attribute__((sda));
extern float g_tether_rope_vec_scale __attribute__((sda));
extern float g_tether_rope_score_scale __attribute__((sda));
extern int g_tether_rope_effect_color __attribute__((sda));

extern int CollLine(void *, void *, int, void *, void *);
extern int coll_process_hit(void *, int, char *, void *, float);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern float vec_length_xy(void *);
extern float fast_vec_dist(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_angle_helper(float);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float fast_subtract_rotations(float, float);
extern float FastDiffRots(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern float *moby_get_private_value_0(void *);
extern float math_wrap_angle_to_pi(float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern void vec_transform_or_copy(void *, void *);

/* Updates the lock-on tether: a chain of twenty points hanging from the hero to up to two locked targets, with its glow spots and sparks (PAL). */
void hero_l16_lock_on_tether_update_pal(Moby *self)
{
    int locked = g_item_stage_records[g_item_slot_to_record.cur].on != 0;
    float reach = g_tether_rope_reach * 0.05f;
    Rope *st = self->rope;
    float v0[4] __attribute__((aligned(16)));
    float va[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float v60[4] __attribute__((aligned(16)));
    float v70[4] __attribute__((aligned(16)));
    float v80[4] __attribute__((aligned(16)));
    float v90[4] __attribute__((aligned(16)));
    float vA0[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float s2B0[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hb __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, nheld;
    float best_score = 0.0f, second_score = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *t;
    int sn;
    float dist, ang, sa2, cs, sm, score, proj, fa, fb;
    float d0;
    float *ia, *ib;
    Tgt *ta, *tb;
    float length, blend;
    float amp, height, angle, old, cd;
    int fa2;
    Tgt *ht;
    float *hinfo;
    float *tv, apj, *ainfo;
    int an;
    float bpj, *binfo;
    int bn;
    float ksize, kf, ks;
    int j1, j2;
    float *q;
    int spin;
    float tsize, cd2;
    Vec *prev;
    float proj2, cm2;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    g_tether_l08_rope_wave_phase = FastAddRotations(g_tether_l08_rope_wave_phase, g_tether_rope_wave_speed);
    g_tether_rope_twist_phase = fast_subtract_rotations(g_tether_rope_twist_phase, g_tether_rope_twist_speed);
    g_tether_l08_rope_wave_phase_2 = FastAddRotations(g_tether_l08_rope_wave_phase_2, g_tether_rope_phase_speed);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            sn = 0;
            for (t = g_target_l08_list[0]; t != 0; t = g_target_l08_list[++sn]) {
                if (t != st->lockA && t != st->lockB) {
                    if (t != 0 && t->cls != 0 && t->cls->id == 5) {
                        if (t->kind != 0xFE) {
                        if (t->kind != 0xFD) {
                            if (moby_get_private_value_0(t) != 0) {
                                FastVecSub(v0, t->pos, st);
                                if (g_hero_l08_input_blocked != 0) {
                                    proj = FastVecDot(v0, g_hero_state.ent + 0xE0);
                                    FastVecScale(va, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(vb, v0, va);
                                    dist = FastVecLength(vb);
                                } else {
                                    dist = vec_length_xy(v0);
                                }
                                if (!(g_tether_rope_reach < dist)) {
                                    ang = FastDiffRots(g_hero_l08_extra_state[0x158 / 4], mat_fast_helper_a(t->pos[0] - g_hero_l08_extra_state[0x140 / 4], t->pos[1] - g_hero_l08_extra_state[0x144 / 4]));
                                    if (!(g_tether_rope_max_angle < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (g_hero_l08_input_blocked != 0) {
                                            FastVecSub(va, t->pos, &g_hero_state.x);
                                            proj2 = FastVecDot(va, g_hero_state.ent + 0xE0);
                                            FastVecScale(vb, g_hero_state.ent + 0xE0, proj2);
                                            FastVecSub(va, va, vb);
                                            cs = FastVecDot(va, g_hero_state.ent + 0xC0);
                                            sm = FastVecLength(va);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - math_fast_angle_helper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(mat_fast_helper_a(t->pos[0] - g_hero_state.x, t->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(g_tether_rope_slack_a < sa2)) {
                                                fa = (g_tether_rope_max_angle - ang) / g_tether_rope_max_angle;
                                                fb = (g_tether_rope_reach - dist) / g_tether_rope_reach;
                                                score = fa * g_tether_rope_score_scale + fb;
                                                if (best_score < score) {
                                                    second_score = best_score;
                                                    best_score = score;
                                                    second = best;
                                                    best = t;
                                                } else if (second_score < score) {
                                                    second = t;
                                                    second_score = score;
                                                }
                                            }
                                    }
                                }
                            }
                        }
                        }
                    }
                }
            }
        }
    }

    if (best != 0) {
        if (st->lockA != 0) {
            second = best;
        } else {
            st->lockA = best;
            st->u.s.h40 = 0;
            if (math_fast_float_d(&g_tether_l08_timer) != 0)
                g_tether_l08_timer = 8;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(st, best->pos);
        if (d0 < g_tether_rope_reach && d0 + fast_vec_dist(best->pos, second->pos) < g_tether_rope_reach) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        ia = moby_get_private_value_0(st->lockA);
        ta = st->lockA;
        qcopy(v0, ta->pos);
        FastVecScale(va, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(v0, v0, va);
        len = fast_vec_dist(st, v0);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        ib = moby_get_private_value_0(st->lockB);
        tb = st->lockB;
        qcopy(va, tb->pos);
        FastVecScale(vb, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(va, va, vb);
        reach = (fast_vec_dist(v0, va) + len) * 0.05f;
    }
    if (locked)
        g_tether_rope_effect_color = 0x207F20;
    else
        g_tether_rope_effect_color = 0x7F2020;
    vec_clear_128(vb);
    make_hit_descriptor(&hit1, self, 0x210000, vb, (&g_item_stage_records[g_item_slot_to_record.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    st->count = 0x14;
    coll_process_hit(st, 0x10, g_hero_state.ent, &hit1, 0.3f);
    FastVecSub(v60, st->b, st);
    vec_scale_to_length(v60, v60, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(v70, v60, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(v60, v60, v70, 0.17453295f);
    }
    got = 0;
    FastVecScale(v90, v60, reach);
    nheld = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&g_tether_l08_rope_points[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&g_tether_l08_rope_points[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = g_tether_rope_amp_start + (g_tether_rope_amp_end - g_tether_rope_amp_start) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l08_rope_wave_phase + (float)i * g_tether_rope_wave_spacing));
        height += math_random_signed_float_range(g_tether_rope_height_jitter_min, g_tether_rope_height_jitter_max);
        old = g_tether_rope_old_heights[i];
        g_tether_rope_old_heights[i] = height;
        g_tether_l08_rope_points[0][i].f[2] = g_tether_l08_rope_points[0][i].f[2] - old;
        vec_transform_or_copy(&g_tether_l08_rope_points[0][i], &g_tether_l08_rope_points[0][i]);
        FastVecSub(v70, &g_tether_l08_rope_points[0][i], g_tether_rope_coll_deltas[i]);
        lerp_vector(v80, v70, v90, 0.85f);
        {
            float cm = FastVecLength(v80);
            if (cm == 0.0f) {
                prev = &g_tether_l08_rope_points[0][i - 1];
                qcopy(&g_tether_l08_rope_points[0][i], prev);
            } else {
                FastVecScale(v80, v80, reach / cm);
                FastVecAdd(&g_tether_l08_rope_points[0][i], g_tether_rope_coll_deltas[i], v80);
                qcopy(v90, v80);
            }
        }
        g_tether_l08_rope_points[0][i].f[2] = g_tether_l08_rope_points[0][i].f[2] + height;
        FastVecSub(v70, &g_tether_l08_rope_points[0][i], g_tether_rope_coll_deltas[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(s2B0, v0, &g_tether_l08_rope_points[0][i]);
                length = FastVecLength(s2B0);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        cd = IntToFloat(0x13 - i);
                        reach = length / cd;
                    } else {
                        blend = 0.1f;
                    }
                    FastVecScale(s2B0, s2B0, reach / length);
                    lerp_vector(v90, v90, s2B0, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(s2B0, va, &g_tether_l08_rope_points[0][i]);
                else
                    FastVecSub(s2B0, v0, &g_tether_l08_rope_points[0][i]);
                length = FastVecLength(s2B0);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if (i >= 5 && i < 10) {
                        blend = 0.7f;
                        cd = IntToFloat(9 - i);
                        reach = length / cd;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        cd2 = IntToFloat(0x13 - i);
                        reach = length / cd2;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(s2B0, s2B0, reach / length);
                    lerp_vector(v90, v90, s2B0, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(g_tether_rope_twist_phase + (float)i * g_tether_rope_wave_step);
            amp = g_tether_rope_wave_amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l08_rope_wave_phase_2 + (float)i * g_tether_rope_amp_phase_step));
            qcopy(&g_tether_l08_rope_points[1][i], &g_tether_l08_rope_points[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            g_tether_rope_heights[i] = height;
            g_tether_l08_rope_points[1][i].f[2] = g_tether_l08_rope_points[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(v70[0], v70[1]), 1.5707965f);
                {
                    float radial = g_tether_rope_radial_scale * math_fast_sin_or_cos_a(angle);
                    vA0[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    vA0[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    vA0[2] = 0.0f;
                    qcopy_nc(&g_tether_rope_offsets[i], vA0);
                }
            }
            FastVecAdd(&g_tether_l08_rope_points[1][i], &g_tether_l08_rope_points[1][i], vA0);
        } else {
            fa2 = 0x15 - i;
            qcopy(&g_tether_l08_rope_points[1][i], &g_tether_l08_rope_points[0][i]);
            g_tether_l08_rope_points[1][i].f[2] = g_tether_l08_rope_points[1][i].f[2] + g_tether_rope_heights[fa2];
            FastVecAdd(&g_tether_l08_rope_points[1][i], &g_tether_l08_rope_points[1][i], &g_tether_rope_offsets[fa2]);
            qcopy(vA0, &g_tether_rope_offsets[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vb, &g_tether_l08_rope_points[0][i], g_hero_position_vec);
            if (g_hero_l08_input_blocked != 0) {
                float cpj = FastVecDot(vb, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(s2B0, ax, cpj);
                    FastVecSub(vb, vb, s2B0);
                }
            } else {
                *(int *)&vb[2] = 0;
            }
            cm2 = FastVecLength(vb);
            if (cm2 == 0.0f)
                vb[2] = 1.0f;
            else
                FastVecScale(vb, vb, 1.0f / cm2);
            vb[3] = 5627.925f;
            qcopy(&hit1, vb);
            got = CollLine(g_tether_rope_coll_starts[i], &g_tether_l08_rope_points[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = g_hero_moby_target.hit;
                if (ht != 0) {
                    hinfo = moby_get_private_value_0(ht);
                    if (hinfo == 0) {
                        QueueMobyImpact(ht, &hit1);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        QueueMobyImpact(ht, &hit1);
                    } else {
                        got = 0;
                        held[nheld++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (got != 0) {
                    qcopy(&g_tether_l08_rope_points[0][i], g_hero_moby_target.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, g_hero_moby_target.pos);
                    if (g_hero_moby_target.hit == 0) {
                        st->lockA = 0;
                        st->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < nheld; n++)
        held[n]->f98 = held[n]->cls->f10;
    if (got == 0)
        qcopy(st->b, &g_tether_rope_anchor);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hb.q;
        FastVecSub(s2B0, st->lockA->pos, g_hero_position_vec);
        if (g_hero_l08_input_blocked != 0) {
            apj = FastVecDot(s2B0, g_hero_state.ent + 0xE0);
            FastVecScale(tv, g_hero_state.ent + 0xE0, apj);
            FastVecSub(s2B0, s2B0, tv);
        } else {
            *(int *)&s2B0[2] = 0;
        }
        vec_scale_to_length(s2B0, s2B0, 1.0f);
        s2B0[3] = 5627.925f;
        make_hit_descriptor(&hb.a.r, self, 0x210000, s2B0, (&g_item_stage_records[g_item_slot_to_record.cur])->f70);
        hb.a.r.kind = 5;
        hb.a.r.flag = 3;
        hb.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(st->lockA, &hb.a.r);
        ainfo = moby_get_private_value_0(st->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = ((s32)(an) * 5 + 2) / 6;
            st->u.s.h44 = result;
        }
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(s2B0, st->lockB->pos, g_hero_position_vec);
        if (g_hero_l08_input_blocked != 0) {
            bpj = FastVecDot(s2B0, g_hero_state.ent + 0xE0);
            FastVecScale(hb.q, g_hero_state.ent + 0xE0, bpj);
            FastVecSub(s2B0, s2B0, hb.q);
        } else {
            *(int *)&s2B0[2] = 0;
        }
        vec_scale_to_length(s2B0, s2B0, 1.0f);
        s2B0[3] = 5627.925f;
        make_hit_descriptor(&hb.b.r, self, 0x210000, s2B0, (&g_item_stage_records[g_item_slot_to_record.cur])->f70);
        hb.b.r.kind = 5;
        hb.b.r.flag = 3;
        hb.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(st->lockB, &hb.b.r);
        binfo = moby_get_private_value_0(st->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = ((s32)(bn) * 5 + 2) / 6;
            st->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = st->a;
                qcopy(hb.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hb.q, st->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&g_tether_l08_segment_timers[k]) != 0) {
            g_tether_l08_segment_timers[k] = ((s32)g_tether_segment_resets[k] * 5 + 2) / 6;
            g_tether_l08_segment_fades[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(s2B0, v60, ksize);
            math_apply_axis_rotation_to_quat(s2B0, s2B0, g_tether_axis_vectors, angle1);
            math_apply_axis_rotation_to_quat(s2B0, s2B0, g_tether_axis_vectors + 0x10, angle0);
            qcopy(&g_tether_l08_rope_nodes[k].v[0], hb.q);
            ks = 1.0f;
            FastVecAdd(&g_tether_l08_rope_nodes[k].v[1], hb.q, s2B0);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hb.q + 4, &g_tether_rope_headers[k].p[j1 - 1], g_hero_position_vec);
                kf = math_random_float_range(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                math_apply_axis_rotation_to_quat(s2B0, s2B0, hb.q + 4, kf);
                FastVecAdd(g_tether_l08_rope_nodes[k].v + j1, &g_tether_rope_headers[k].p[j1 - 1], s2B0);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, g_tether_l08_rope_nodes[k].v + j2, &g_tether_rope_headers[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_tether_l08_rope_nodes[k].v[0], hb.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(g_tether_l08_rope_nodes[k].v + j2, &g_tether_rope_headers[k].p[j2 - 1], tmp[j2]);
            {
                int x = g_tether_l08_segment_x[k];
                int y = g_tether_l08_segment_timers[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xC);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                g_tether_l08_segment_fades[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(s2B0, v60, g_tether_rope_vec_scale * 1.2f);
        math_apply_axis_rotation_to_quat(s2B0, s2B0, g_tether_axis_vectors, angle1);
        math_apply_axis_rotation_to_quat(s2B0, s2B0, g_tether_axis_vectors + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(st, 0xC, tsize * 0.3f, tsize, g_tether_rope_effect_color | 0x7F000000, 0, spin, s2B0, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(st, 0xC, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, s2B0, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(st->b, 0xA, tsize * 0.1f, tsize, g_tether_rope_effect_color | 0x7F000000, 0, spin, g_str_effect_name, 1, 0.0f);
    }
}
