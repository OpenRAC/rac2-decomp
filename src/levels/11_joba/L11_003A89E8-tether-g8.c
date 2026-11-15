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
extern Slot D_L11_00279BA0[];
extern Cam g_hero_state;
extern char D_0018A560[];
extern int D_L11_001A8FF0;
extern float D_L11_001A8F20[] MACRO_ADDR;
extern int D_L11_001B3E40;
extern short D_L11_001B3E48[] MACRO_ADDR;
extern short D_L11_001B3E50[] MACRO_ADDR;
extern short D_L11_001B3E58[] MACRO_ADDR;
extern short D_L11_001B3E60[] MACRO_ADDR;
extern float D_L11_001BA780[];
extern char D_L11_001BA8C0[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L11_001C0D18;
extern Tgt *D_L11_001FC7E0[];
extern float D_L11_0023B430[][4], D_L11_0023B440[][4];
extern Vec D_L11_0023B450[2][20];
extern V4 D_L11_0023B580;
extern float D_L11_0023B6D0[];
extern Vec D_L11_0023B720[];
extern float D_L11_0023B860[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L11_0023B8A0[];
extern Node5 D_L11_0023B8B0[];

extern float D_L11_001AF164 __attribute__((sda));
extern float D_L11_001AF168 __attribute__((sda));
extern float D_L11_001AF16C __attribute__((sda));
extern float D_L11_001AF170 __attribute__((sda));
extern float D_L11_001AF174 __attribute__((sda));
extern float D_L11_001AF178 __attribute__((sda));
extern float D_L11_001AF17C __attribute__((sda));
extern float D_L11_001AF180 __attribute__((sda));
extern float D_L11_001AF184 __attribute__((sda));
extern float D_L11_001AF188 __attribute__((sda));
extern float D_L11_001AF18C __attribute__((sda));
extern float D_L11_001AF190 __attribute__((sda));
extern float D_L11_001AF194 __attribute__((sda));
extern float D_L11_001AF198 __attribute__((sda));
extern float D_L11_001AF19C __attribute__((sda));
extern float D_L11_001AF1A0 __attribute__((sda));
extern float D_L11_001AF1B4 __attribute__((sda));
extern float D_L11_001AF1B8 __attribute__((sda));
extern float D_L11_001AF1F8 __attribute__((sda));
extern float D_L11_001AF1FC __attribute__((sda));
extern int D_L11_001AF1C8 __attribute__((sda));

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

/* Updates the lock-on tether. It picks up to two targets, bends a chain of twenty points
   from the player's hand to them, and spawns sparks. */
void gadget_l11_update_lock_on_tether(Moby *self)
{
    int locked = D_L11_00279BA0[g_item_slot_to_record.cur].on != 0;
    float reach = D_L11_001AF164 * 0.05f;
    Rope *st = self->rope;
    float lock_point_a[4] __attribute__((aligned(16)));
    float va[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float chain_direction[4] __attribute__((aligned(16)));
    float segment_delta[4] __attribute__((aligned(16)));
    float segment_step[4] __attribute__((aligned(16)));
    float pull_vector[4] __attribute__((aligned(16)));
    float spark_offset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float temp_vector[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hb __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int got, nheld;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *candidate;
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

    D_L11_001AF17C = FastAddRotations(D_L11_001AF17C, D_L11_001AF180);
    D_L11_001AF184 = fast_subtract_rotations(D_L11_001AF184, D_L11_001AF188);
    D_L11_001AF198 = FastAddRotations(D_L11_001AF198, D_L11_001AF19C);

    if (st->lockA == 0 || (locked && st->lockB == 0)) {
        if (st->lockB != 0) {
            st->lockA = st->lockB;
            st->u.s.h40 = st->u.s.h42;
            st->lockB = 0;
            st->u.s.h42 = 0;
        } else {
            sn = 0;
            for (candidate = D_L11_001FC7E0[0]; candidate != 0; candidate = D_L11_001FC7E0[++sn]) {
                if (candidate != st->lockA && candidate != st->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (moby_get_private_value_0(candidate) != 0) {
                                FastVecSub(lock_point_a, candidate->pos, st);
                                if (D_L11_001A8FF0 != 0) {
                                    proj = FastVecDot(lock_point_a, g_hero_state.ent + 0xE0);
                                    FastVecScale(va, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(vb, lock_point_a, va);
                                    dist = FastVecLength(vb);
                                } else {
                                    dist = vec_length_xy(lock_point_a);
                                }
                                if (!(D_L11_001AF164 < dist)) {
                                    ang = FastDiffRots(D_L11_001BA780[0x158 / 4], mat_fast_helper_a(candidate->pos[0] - D_L11_001BA780[0x140 / 4], candidate->pos[1] - D_L11_001BA780[0x144 / 4]));
                                    if (!(D_L11_001AF16C < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_L11_001A8FF0 != 0) {
                                            FastVecSub(va, candidate->pos, &g_hero_state.x);
                                            proj2 = FastVecDot(va, g_hero_state.ent + 0xE0);
                                            FastVecScale(vb, g_hero_state.ent + 0xE0, proj2);
                                            FastVecSub(va, va, vb);
                                            cs = FastVecDot(va, g_hero_state.ent + 0xC0);
                                            sm = FastVecLength(va);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - math_fast_angle_helper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(mat_fast_helper_a(candidate->pos[0] - g_hero_state.x, candidate->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(D_L11_001AF168 < sa2)) {
                                                fa = (D_L11_001AF16C - ang) / D_L11_001AF16C;
                                                fb = (D_L11_001AF164 - dist) / D_L11_001AF164;
                                                score = fa * D_L11_001AF1FC + fb;
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
            if (math_fast_float_d(&D_L11_001B3E40) != 0)
                D_L11_001B3E40 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(st, best->pos);
        if (d0 < D_L11_001AF164 && d0 + fast_vec_dist(best->pos, second->pos) < D_L11_001AF164) {
            st->u.s.h42 = 0;
            st->lockB = second;
        }
    }
    len = 0.0f;
    if (st->lockA != 0) {
        ia = moby_get_private_value_0(st->lockA);
        ta = st->lockA;
        qcopy(lock_point_a, ta->pos);
        FastVecScale(va, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(lock_point_a, lock_point_a, va);
        len = fast_vec_dist(st, lock_point_a);
        reach = len * 0.05f;
    }
    if (st->lockB != 0) {
        ib = moby_get_private_value_0(st->lockB);
        tb = st->lockB;
        qcopy(va, tb->pos);
        FastVecScale(vb, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(va, va, vb);
        reach = (fast_vec_dist(lock_point_a, va) + len) * 0.05f;
    }
    if (locked)
        D_L11_001AF1C8 = 0x207F20;
    else
        D_L11_001AF1C8 = 0x7F2020;
    vec_clear_128(vb);
    make_hit_descriptor(&hit1, self, 0x210000, vb, (&D_L11_00279BA0[g_item_slot_to_record.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    st->count = 0x14;
    coll_process_hit(st, 0x10, g_hero_state.ent, &hit1, 0.3f);
    FastVecSub(chain_direction, st->b, st);
    vec_scale_to_length(chain_direction, chain_direction, 1.0f);
    if (st->lockA != 0 || st->lockB != 0) {
        FastVecCross(segment_delta, chain_direction, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(chain_direction, chain_direction, segment_delta, 0.17453295f);
    }
    got = 0;
    FastVecScale(pull_vector, chain_direction, reach);
    nheld = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = st->a;
        qcopy(&D_L11_0023B450[0][0], anchor);
    }
    {
        float *anchor = st->a;
        qcopy(&D_L11_0023B450[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L11_001AF174 + (D_L11_001AF178 - D_L11_001AF174) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L11_001AF17C + (float)i * D_L11_001AF170));
        height += math_random_signed_float_range(D_L11_001AF1B4, D_L11_001AF1B8);
        old = D_L11_0023B6D0[i];
        D_L11_0023B6D0[i] = height;
        D_L11_0023B450[0][i].f[2] = D_L11_0023B450[0][i].f[2] - old;
        vec_transform_or_copy(&D_L11_0023B450[0][i], &D_L11_0023B450[0][i]);
        FastVecSub(segment_delta, &D_L11_0023B450[0][i], D_L11_0023B440[i]);
        lerp_vector(segment_step, segment_delta, pull_vector, 0.85f);
        {
            float cm = FastVecLength(segment_step);
            if (cm == 0.0f) {
                prev = &D_L11_0023B450[0][i - 1];
                qcopy(&D_L11_0023B450[0][i], prev);
            } else {
                FastVecScale(segment_step, segment_step, reach / cm);
                FastVecAdd(&D_L11_0023B450[0][i], D_L11_0023B440[i], segment_step);
                qcopy(pull_vector, segment_step);
            }
        }
        D_L11_0023B450[0][i].f[2] = D_L11_0023B450[0][i].f[2] + height;
        FastVecSub(segment_delta, &D_L11_0023B450[0][i], D_L11_0023B440[i]);
        if (st->lockA != 0) {
            if (!locked || st->lockB == 0) {
                FastVecSub(temp_vector, lock_point_a, &D_L11_0023B450[0][i]);
                length = FastVecLength(temp_vector);
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
                    FastVecScale(temp_vector, temp_vector, reach / length);
                    lerp_vector(pull_vector, pull_vector, temp_vector, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(temp_vector, va, &D_L11_0023B450[0][i]);
                else
                    FastVecSub(temp_vector, lock_point_a, &D_L11_0023B450[0][i]);
                length = FastVecLength(temp_vector);
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
                    FastVecScale(temp_vector, temp_vector, reach / length);
                    lerp_vector(pull_vector, pull_vector, temp_vector, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(D_L11_001AF184 + (float)i * D_L11_001AF18C);
            amp = D_L11_001AF190 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L11_001AF198 + (float)i * D_L11_001AF1A0));
            qcopy(&D_L11_0023B450[1][i], &D_L11_0023B450[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            D_L11_0023B860[i] = height;
            D_L11_0023B450[1][i].f[2] = D_L11_0023B450[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(segment_delta[0], segment_delta[1]), 1.5707965f);
                {
                    float radial = D_L11_001AF194 * math_fast_sin_or_cos_a(angle);
                    spark_offset[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    spark_offset[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    spark_offset[2] = 0.0f;
                    qcopy_nc(&D_L11_0023B720[i], spark_offset);
                }
            }
            FastVecAdd(&D_L11_0023B450[1][i], &D_L11_0023B450[1][i], spark_offset);
        } else {
            fa2 = 0x15 - i;
            qcopy(&D_L11_0023B450[1][i], &D_L11_0023B450[0][i]);
            D_L11_0023B450[1][i].f[2] = D_L11_0023B450[1][i].f[2] + D_L11_0023B860[fa2];
            FastVecAdd(&D_L11_0023B450[1][i], &D_L11_0023B450[1][i], &D_L11_0023B720[fa2]);
            qcopy(spark_offset, &D_L11_0023B720[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vb, &D_L11_0023B450[0][i], D_L11_001BA8C0);
            if (D_L11_001A8FF0 != 0) {
                float cpj = FastVecDot(vb, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(temp_vector, ax, cpj);
                    FastVecSub(vb, vb, temp_vector);
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
            got = CollLine(D_L11_0023B430[i], &D_L11_0023B450[0][i], 0x10, self, 0);
            if (got != 0) {
                ht = D_L11_001C0D18.hit;
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
                    qcopy(&D_L11_0023B450[0][i], D_L11_001C0D18.pos);
                    {
                        short last = i;
                        st->count = last;
                    }
                    qcopy(st->b, D_L11_001C0D18.pos);
                    if (D_L11_001C0D18.hit == 0) {
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
        qcopy(st->b, &D_L11_0023B580);
    if (st->lockA != 0 && (st->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hb.q;
        FastVecSub(temp_vector, st->lockA->pos, D_L11_001BA8C0);
        if (D_L11_001A8FF0 != 0) {
            apj = FastVecDot(temp_vector, g_hero_state.ent + 0xE0);
            FastVecScale(tv, g_hero_state.ent + 0xE0, apj);
            FastVecSub(temp_vector, temp_vector, tv);
        } else {
            *(int *)&temp_vector[2] = 0;
        }
        vec_scale_to_length(temp_vector, temp_vector, 1.0f);
        temp_vector[3] = 5627.925f;
        make_hit_descriptor(&hb.a.r, self, 0x210000, temp_vector, (&D_L11_00279BA0[g_item_slot_to_record.cur])->f70);
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
            short result = an;
            st->u.s.h44 = result;
        }
    }
    if (st->lockB != 0 && (st->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(temp_vector, st->lockB->pos, D_L11_001BA8C0);
        if (D_L11_001A8FF0 != 0) {
            bpj = FastVecDot(temp_vector, g_hero_state.ent + 0xE0);
            FastVecScale(hb.q, g_hero_state.ent + 0xE0, bpj);
            FastVecSub(temp_vector, temp_vector, hb.q);
        } else {
            *(int *)&temp_vector[2] = 0;
        }
        vec_scale_to_length(temp_vector, temp_vector, 1.0f);
        temp_vector[3] = 5627.925f;
        make_hit_descriptor(&hb.b.r, self, 0x210000, temp_vector, (&D_L11_00279BA0[g_item_slot_to_record.cur])->f70);
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
            short result = bn;
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
        if (FastDecTimer(&D_L11_001B3E48[k]) != 0) {
            D_L11_001B3E48[k] = D_L11_001B3E58[k];
            D_L11_001B3E50[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(temp_vector, chain_direction, ksize);
            math_apply_axis_rotation_to_quat(temp_vector, temp_vector, D_0018A560, angle1);
            math_apply_axis_rotation_to_quat(temp_vector, temp_vector, D_0018A560 + 0x10, angle0);
            qcopy(&D_L11_0023B8B0[k].v[0], hb.q);
            ks = 1.0f;
            FastVecAdd(&D_L11_0023B8B0[k].v[1], hb.q, temp_vector);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hb.q + 4, &D_L11_0023B8A0[k].p[j1 - 1], D_L11_001BA8C0);
                kf = math_random_float_range(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                math_apply_axis_rotation_to_quat(temp_vector, temp_vector, hb.q + 4, kf);
                FastVecAdd(D_L11_0023B8B0[k].v + j1, &D_L11_0023B8A0[k].p[j1 - 1], temp_vector);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, D_L11_0023B8B0[k].v + j2, &D_L11_0023B8A0[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_L11_0023B8B0[k].v[0], hb.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_L11_0023B8B0[k].v + j2, &D_L11_0023B8A0[k].p[j2 - 1], tmp[j2]);
            {
                int x = D_L11_001B3E60[k];
                int y = D_L11_001B3E48[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_L11_001B3E50[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(temp_vector, chain_direction, D_L11_001AF1F8);
        math_apply_axis_rotation_to_quat(temp_vector, temp_vector, D_0018A560, angle1);
        math_apply_axis_rotation_to_quat(temp_vector, temp_vector, D_0018A560 + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(st, 0xF, tsize * 0.3f, tsize, D_L11_001AF1C8 | 0x7F000000, 0, spin, temp_vector, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(st, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, temp_vector, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(st->b, 0xC, tsize * 0.1f, tsize, D_L11_001AF1C8 | 0x7F000000, 0, spin, D_L11_001A8F20, 1, 0.0f);
    }
}
