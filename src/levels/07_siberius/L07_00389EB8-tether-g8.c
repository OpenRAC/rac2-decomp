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
extern Slot D_L07_002628A0[];
extern Cam g_hero_state;
extern char D_0018A560[];
extern int D_L07_001A8FF0;
extern float D_L07_001A8F20[] MACRO_ADDR;
extern int D_L07_001B2BA0;
extern short D_L07_001B2BA8[] MACRO_ADDR;
extern short D_L07_001B2BB0[] MACRO_ADDR;
extern short D_L07_001B2BB8[] MACRO_ADDR;
extern short D_L07_001B2BC0[] MACRO_ADDR;
extern float D_L07_001B90C0[];
extern char D_L07_001B9200[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L07_001BF658;
extern Tgt *D_L07_001FB120[];
extern float D_L07_00239D70[][4], D_L07_00239D80[][4];
extern Vec D_L07_00239D90[2][20];
extern V4 D_L07_00239EC0;
extern float D_L07_0023A010[];
extern Vec D_L07_0023A060[];
extern float D_L07_0023A1A0[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L07_0023A1E0[];
extern Node5 D_L07_0023A1F0[];

extern float D_L07_001AF0E4 __attribute__((sda));
extern float D_L07_001AF0E8 __attribute__((sda));
extern float D_L07_001AF0EC __attribute__((sda));
extern float D_L07_001AF0F0 __attribute__((sda));
extern float D_L07_001AF0F4 __attribute__((sda));
extern float D_L07_001AF0F8 __attribute__((sda));
extern float D_L07_001AF0FC __attribute__((sda));
extern float D_L07_001AF100 __attribute__((sda));
extern float D_L07_001AF104 __attribute__((sda));
extern float D_L07_001AF108 __attribute__((sda));
extern float D_L07_001AF10C __attribute__((sda));
extern float D_L07_001AF110 __attribute__((sda));
extern float D_L07_001AF114 __attribute__((sda));
extern float D_L07_001AF118 __attribute__((sda));
extern float D_L07_001AF11C __attribute__((sda));
extern float D_L07_001AF120 __attribute__((sda));
extern float D_L07_001AF134 __attribute__((sda));
extern float D_L07_001AF138 __attribute__((sda));
extern float D_L07_001AF178 __attribute__((sda));
extern float D_L07_001AF17C __attribute__((sda));
extern int D_L07_001AF148 __attribute__((sda));

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

/* Per-frame update of the lock-on tether: picks up to two targets, lays out the twenty-point
   chain with waves and collision, and spawns sparks. */
void lock_l07_on_tether_update(Moby *self)
{
    int locked = D_L07_002628A0[g_item_slot_to_record.cur].on != 0;
    float reach = D_L07_001AF0E4 * 0.05f;
    Rope *st = self->rope;
    float target_point_a[4] __attribute__((aligned(16)));
    float target_point_b[4] __attribute__((aligned(16)));
    float scratch_vec[4] __attribute__((aligned(16)));
    Hit shot_query __attribute__((aligned(16)));
    float aim_dir[4] __attribute__((aligned(16)));
    float link_offset[4] __attribute__((aligned(16)));
    float step_vec[4] __attribute__((aligned(16)));
    float chain_dir[4] __attribute__((aligned(16)));
    float side_shift[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float temp_vec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hit_something, held_count;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int held_idx;
    Tgt *candidate;
    int scan_idx;
    float dist, ang, side_angle, cos_part, side_len, score, proj, fa, fb;
    float dist_to_best;
    float *info_a, *info_b;
    Tgt *target_a, *target_b;
    float length, blend;
    float amp, height, angle, old, cd;
    int mirror_idx;
    Tgt *hit_target;
    float *hit_info;
    float *proj_buf, proj_a, *class_info_a;
    int hit_code_a;
    float proj_b, *class_info_b;
    int hit_code_b;
    float ksize, kf, ks;
    int j1, j2;
    float *q;
    int spin;
    float tsize, cd2;
    Vec *prev;
    float proj2, ray_len;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L07_001AF0FC = FastAddRotations(D_L07_001AF0FC, D_L07_001AF100);
    D_L07_001AF104 = fast_subtract_rotations(D_L07_001AF104, D_L07_001AF108);
    D_L07_001AF118 = FastAddRotations(D_L07_001AF118, D_L07_001AF11C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            scan_idx = 0;
            for (candidate = D_L07_001FB120[0]; candidate != 0; candidate = D_L07_001FB120[++scan_idx]) {
                if (candidate != st->lockA && candidate != st->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (moby_get_private_value_0(candidate) != 0) {
                                FastVecSub(target_point_a, candidate->pos, st);
                                if (D_L07_001A8FF0 != 0) {
                                    proj = FastVecDot(target_point_a, g_hero_state.ent + 0xE0);
                                    FastVecScale(target_point_b, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(scratch_vec, target_point_a, target_point_b);
                                    dist = FastVecLength(scratch_vec);
                                } else {
                                    dist = vec_length_xy(target_point_a);
                                }
                                if (!(D_L07_001AF0E4 < dist)) {
                                    ang = FastDiffRots(D_L07_001B90C0[0x158 / 4], mat_fast_helper_a(candidate->pos[0] - D_L07_001B90C0[0x140 / 4], candidate->pos[1] - D_L07_001B90C0[0x144 / 4]));
                                    if (!(D_L07_001AF0EC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        side_angle = 0.0f;
                                        if (D_L07_001A8FF0 != 0) {
                                            FastVecSub(target_point_b, candidate->pos, &g_hero_state.x);
                                            proj2 = FastVecDot(target_point_b, g_hero_state.ent + 0xE0);
                                            FastVecScale(scratch_vec, g_hero_state.ent + 0xE0, proj2);
                                            FastVecSub(target_point_b, target_point_b, scratch_vec);
                                            cos_part = FastVecDot(target_point_b, g_hero_state.ent + 0xC0);
                                            side_len = FastVecLength(target_point_b);
                                            if (side_len == 0.0f)
                                                continue;
                                            side_angle = 1.5707964f - math_fast_angle_helper(cos_part / side_len);
                                        } else {
                                            side_angle = FastDiffRots(mat_fast_helper_a(candidate->pos[0] - g_hero_state.x, candidate->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(D_L07_001AF0E8 < side_angle)) {
                                                fa = (D_L07_001AF0EC - ang) / D_L07_001AF0EC;
                                                fb = (D_L07_001AF0E4 - dist) / D_L07_001AF0E4;
                                                score = fa * D_L07_001AF17C + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = candidate;
                                                } else if (secondScore < score) {
                                                    second = candidate;
                                                    secondScore = score;
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
            if (math_fast_float_d(&D_L07_001B2BA0) != 0)
                D_L07_001B2BA0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        dist_to_best = fast_vec_dist(st, best->pos);
        if (dist_to_best < D_L07_001AF0E4 && dist_to_best + fast_vec_dist(best->pos, second->pos) < D_L07_001AF0E4) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        info_a = moby_get_private_value_0(st->lockA);
        target_a = st->lockA;
        qcopy(target_point_a, target_a->pos);
        FastVecScale(target_point_b, (char *)target_a + 0xE0, info_a[4]);
        FastVecAdd(target_point_a, target_point_a, target_point_b);
        len = fast_vec_dist(st, target_point_a);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        info_b = moby_get_private_value_0(st->lockB);
        target_b = st->lockB;
        qcopy(target_point_b, target_b->pos);
        FastVecScale(scratch_vec, (char *)target_b + 0xE0, info_b[4]);
        FastVecAdd(target_point_b, target_point_b, scratch_vec);
        reach = (fast_vec_dist(target_point_a, target_point_b) + len) * 0.05f;
    }
    if (locked)
        D_L07_001AF148 = 0x207F20;
    else
        D_L07_001AF148 = 0x7F2020;
    vec_clear_128(scratch_vec);
    make_hit_descriptor(&shot_query, self, 0x210000, scratch_vec, (&D_L07_002628A0[g_item_slot_to_record.cur])->f70);
    shot_query.kind = 5;
    shot_query.flag = 1;
    shot_query.tag = self->tag;
    st->count = 0x14;
    coll_process_hit(st, 0x10, g_hero_state.ent, &shot_query, 0.3f);
    FastVecSub(aim_dir, st->b, st);
    vec_scale_to_length(aim_dir, aim_dir, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(link_offset, aim_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(aim_dir, aim_dir, link_offset, 0.17453295f);
    }
    hit_something = 0;
    FastVecScale(chain_dir, aim_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&D_L07_00239D90[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&D_L07_00239D90[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L07_001AF0F4 + (D_L07_001AF0F8 - D_L07_001AF0F4) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L07_001AF0FC + (float)i * D_L07_001AF0F0));
        height += math_random_signed_float_range(D_L07_001AF134, D_L07_001AF138);
        old = D_L07_0023A010[i];
        D_L07_0023A010[i] = height;
        D_L07_00239D90[0][i].f[2] = D_L07_00239D90[0][i].f[2] - old;
        vec_transform_or_copy(&D_L07_00239D90[0][i], &D_L07_00239D90[0][i]);
        FastVecSub(link_offset, &D_L07_00239D90[0][i], D_L07_00239D80[i]);
        lerp_vector(step_vec, link_offset, chain_dir, 0.85f);
        {
            float chain_len = FastVecLength(step_vec);
            if (chain_len == 0.0f) {
                prev = &D_L07_00239D90[0][i - 1];
                qcopy(&D_L07_00239D90[0][i], prev);
            } else {
                FastVecScale(step_vec, step_vec, reach / chain_len);
                FastVecAdd(&D_L07_00239D90[0][i], D_L07_00239D80[i], step_vec);
                qcopy(chain_dir, step_vec);
            }
        }
        D_L07_00239D90[0][i].f[2] = D_L07_00239D90[0][i].f[2] + height;
        FastVecSub(link_offset, &D_L07_00239D90[0][i], D_L07_00239D80[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(temp_vec, target_point_a, &D_L07_00239D90[0][i]);
                length = FastVecLength(temp_vec);
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
                    FastVecScale(temp_vec, temp_vec, reach / length);
                    lerp_vector(chain_dir, chain_dir, temp_vec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(temp_vec, target_point_b, &D_L07_00239D90[0][i]);
                else
                    FastVecSub(temp_vec, target_point_a, &D_L07_00239D90[0][i]);
                length = FastVecLength(temp_vec);
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
                    FastVecScale(temp_vec, temp_vec, reach / length);
                    lerp_vector(chain_dir, chain_dir, temp_vec, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(D_L07_001AF104 + (float)i * D_L07_001AF10C);
            amp = D_L07_001AF110 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L07_001AF118 + (float)i * D_L07_001AF120));
            qcopy(&D_L07_00239D90[1][i], &D_L07_00239D90[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            D_L07_0023A1A0[i] = height;
            D_L07_00239D90[1][i].f[2] = D_L07_00239D90[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(link_offset[0], link_offset[1]), 1.5707965f);
                {
                    float radial = D_L07_001AF114 * math_fast_sin_or_cos_a(angle);
                    side_shift[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    side_shift[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    side_shift[2] = 0.0f;
                    qcopy_nc(&D_L07_0023A060[i], side_shift);
                }
            }
            FastVecAdd(&D_L07_00239D90[1][i], &D_L07_00239D90[1][i], side_shift);
        } else {
            mirror_idx = 0x15 - i;
            qcopy(&D_L07_00239D90[1][i], &D_L07_00239D90[0][i]);
            D_L07_00239D90[1][i].f[2] = D_L07_00239D90[1][i].f[2] + D_L07_0023A1A0[mirror_idx];
            FastVecAdd(&D_L07_00239D90[1][i], &D_L07_00239D90[1][i], &D_L07_0023A060[mirror_idx]);
            qcopy(side_shift, &D_L07_0023A060[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratch_vec, &D_L07_00239D90[0][i], D_L07_001B9200);
            if (D_L07_001A8FF0 != 0) {
                float ray_proj = FastVecDot(scratch_vec, g_hero_state.ent + 0xE0);
                {
                    char *up_axis = g_hero_state.ent + 0xE0;
                    FastVecScale(temp_vec, up_axis, ray_proj);
                    FastVecSub(scratch_vec, scratch_vec, temp_vec);
                }
            } else {
                *(int *)&scratch_vec[2] = 0;
            }
            ray_len = FastVecLength(scratch_vec);
            if (ray_len == 0.0f)
                scratch_vec[2] = 1.0f;
            else
                FastVecScale(scratch_vec, scratch_vec, 1.0f / ray_len);
            scratch_vec[3] = 5627.925f;
            qcopy(&shot_query, scratch_vec);
            hit_something = CollLine(D_L07_00239D70[i], &D_L07_00239D90[0][i], 0x10, self, 0);
            if (hit_something != 0) {
                hit_target = D_L07_001BF658.hit;
                if (hit_target != 0) {
                    hit_info = moby_get_private_value_0(hit_target);
                    if (hit_info == 0) {
                        QueueMobyImpact(hit_target, &shot_query);
                    } else if (hit_target->cls == 0 || hit_target->cls->id != 5) {
                        QueueMobyImpact(hit_target, &shot_query);
                    } else {
                        hit_something = 0;
                        held[held_count++] = hit_target;
                        hit_target->f98 = 0;
                    }
                }
                if (hit_something != 0) {
                    qcopy(&D_L07_00239D90[0][i], D_L07_001BF658.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, D_L07_001BF658.pos);
                    if (D_L07_001BF658.hit == 0) {
                        st->lockA = 0;
                        st->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (held_idx = 0; held_idx < held_count; held_idx++)
        held[held_idx]->f98 = held[held_idx]->cls->f10;
    if (hit_something == 0)
        qcopy(st->b, &D_L07_00239EC0);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        proj_buf = hit_buf.q;
        FastVecSub(temp_vec, st->lockA->pos, D_L07_001B9200);
        if (D_L07_001A8FF0 != 0) {
            proj_a = FastVecDot(temp_vec, g_hero_state.ent + 0xE0);
            FastVecScale(proj_buf, g_hero_state.ent + 0xE0, proj_a);
            FastVecSub(temp_vec, temp_vec, proj_buf);
        } else {
            *(int *)&temp_vec[2] = 0;
        }
        vec_scale_to_length(temp_vec, temp_vec, 1.0f);
        temp_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.a.r, self, 0x210000, temp_vec, (&D_L07_002628A0[g_item_slot_to_record.cur])->f70);
        hit_buf.a.r.kind = 5;
        hit_buf.a.r.flag = 3;
        hit_buf.a.r.tag = self->tag;
        hit_code_a = 5;
        QueueMobyImpact(st->lockA, &hit_buf.a.r);
        class_info_a = moby_get_private_value_0(st->lockA);
        if (class_info_a != 0) {
            if (((short *)class_info_a)[2] == 1)
                hit_code_a = 1;
        }
        {
            short result = hit_code_a;
            st->u.s.h44 = result;
        }
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(temp_vec, st->lockB->pos, D_L07_001B9200);
        if (D_L07_001A8FF0 != 0) {
            proj_b = FastVecDot(temp_vec, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buf.q, g_hero_state.ent + 0xE0, proj_b);
            FastVecSub(temp_vec, temp_vec, hit_buf.q);
        } else {
            *(int *)&temp_vec[2] = 0;
        }
        vec_scale_to_length(temp_vec, temp_vec, 1.0f);
        temp_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.b.r, self, 0x210000, temp_vec, (&D_L07_002628A0[g_item_slot_to_record.cur])->f70);
        hit_buf.b.r.kind = 5;
        hit_buf.b.r.flag = 3;
        hit_buf.b.r.tag = self->tag;
        hit_code_b = 5;
        QueueMobyImpact(st->lockB, &hit_buf.b.r);
        class_info_b = moby_get_private_value_0(st->lockB);
        if (class_info_b != 0) {
            if (((short *)class_info_b)[2] == 1)
                hit_code_b = 1;
        }
        {
            short result = hit_code_b;
            st->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = st->a;
                qcopy(hit_buf.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hit_buf.q, st->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_L07_001B2BA8[k]) != 0) {
            D_L07_001B2BA8[k] = D_L07_001B2BB8[k];
            D_L07_001B2BB0[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(temp_vec, aim_dir, ksize);
            math_apply_axis_rotation_to_quat(temp_vec, temp_vec, D_0018A560, angle1);
            math_apply_axis_rotation_to_quat(temp_vec, temp_vec, D_0018A560 + 0x10, angle0);
            qcopy(&D_L07_0023A1F0[k].v[0], hit_buf.q);
            ks = 1.0f;
            FastVecAdd(&D_L07_0023A1F0[k].v[1], hit_buf.q, temp_vec);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hit_buf.q + 4, &D_L07_0023A1E0[k].p[j1 - 1], D_L07_001B9200);
                kf = math_random_float_range(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                math_apply_axis_rotation_to_quat(temp_vec, temp_vec, hit_buf.q + 4, kf);
                FastVecAdd(D_L07_0023A1F0[k].v + j1, &D_L07_0023A1E0[k].p[j1 - 1], temp_vec);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter[j2];
                FastVecSub(q, D_L07_0023A1F0[k].v + j2, &D_L07_0023A1E0[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_L07_0023A1F0[k].v[0], hit_buf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L07_0023A1F0[k].v + j2, &D_L07_0023A1E0[k].p[j2 - 1], jitter[j2]);
            {
                int x = D_L07_001B2BC0[k];
                int y = D_L07_001B2BA8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L07_001B2BB0[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(temp_vec, aim_dir, D_L07_001AF178);
        math_apply_axis_rotation_to_quat(temp_vec, temp_vec, D_0018A560, angle1);
        math_apply_axis_rotation_to_quat(temp_vec, temp_vec, D_0018A560 + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(st, 0xF, tsize * 0.3f, tsize, D_L07_001AF148 | 0x7F000000, 0, spin, temp_vec, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(st, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, temp_vec, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(st->b, 0xC, tsize * 0.1f, tsize, D_L07_001AF148 | 0x7F000000, 0, spin, D_L07_001A8F20, 1, 0.0f);
    }
}
