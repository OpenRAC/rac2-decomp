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
extern Slot g_weapon_table[];
extern Cam g_hero_state;
extern char D_0018A560[];
extern int D_001A8CA0;
extern float D_001A8BD0[] MACRO_ADDR;
extern int D_001B23E0;
extern short D_001B23E8[] MACRO_ADDR;
extern short D_001B23F0[] MACRO_ADDR;
extern short D_001B23F8[] MACRO_ADDR;
extern short D_001B2400[] MACRO_ADDR;
extern float g_active_camera[];
extern char g_camera_eye_state[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_001BAF98;
extern Tgt *D_001EE960[];
extern float D_00229150[][4], D_00229160[][4];
extern Vec D_00229170[2][20];
extern V4 D_002292A0;
extern float D_002293F0[];
extern Vec D_00229440[];
extern float D_00229580[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_002295C0[];
extern Node5 D_002295D0[];

extern float D_001AEDF4 __attribute__((sda));
extern float D_001AEDF8 __attribute__((sda));
extern float D_001AEDFC __attribute__((sda));
extern float D_001AEE00 __attribute__((sda));
extern float D_001AEE04 __attribute__((sda));
extern float D_001AEE08 __attribute__((sda));
extern float D_001AEE0C __attribute__((sda));
extern float D_001AEE10 __attribute__((sda));
extern float D_001AEE14 __attribute__((sda));
extern float D_001AEE18 __attribute__((sda));
extern float D_001AEE1C __attribute__((sda));
extern float D_001AEE20 __attribute__((sda));
extern float D_001AEE24 __attribute__((sda));
extern float D_001AEE28 __attribute__((sda));
extern float D_001AEE2C __attribute__((sda));
extern float D_001AEE30 __attribute__((sda));
extern float D_001AEE44 __attribute__((sda));
extern float D_001AEE48 __attribute__((sda));
extern float D_001AEE88 __attribute__((sda));
extern float D_001AEE8C __attribute__((sda));
extern int D_001AEE58 __attribute__((sda));

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

/* Moves the tether chain from the player's hand to the best locked-on target, or two targets. Also updates the glow spots and sparks. */
void lock_on_update_tether_chain(Moby *self)
{
    int locked = g_weapon_table[g_item_slot_to_record.cur].on != 0;
    float reach = D_001AEDF4 * 0.05f;
    Rope *chain = self->rope;
    float lock_point_a[4] __attribute__((aligned(16)));
    float lock_point_b[4] __attribute__((aligned(16)));
    float scratch_b[4] __attribute__((aligned(16)));
    Hit hit_info __attribute__((aligned(16)));
    float tether_dir[4] __attribute__((aligned(16)));
    float segment_delta[4] __attribute__((aligned(16)));
    float step_vec[4] __attribute__((aligned(16)));
    float last_step[4] __attribute__((aligned(16)));
    float radial_offset[4] __attribute__((aligned(16)));
    Tgt *held_targets[128];
    float scratch_a[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buffer __attribute__((aligned(16)));
    float tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hit_something, held_count;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int n;
    Tgt *candidate;
    int scan_index;
    float dist, ang, sa2, cs, sm, score, proj, angle_score, distance_score;
    float d0;
    float *info_a, *info_b;
    Tgt *target_a, *target_b;
    float length, blend;
    float amp, height, angle, old, cd;
    int mirror_index;
    Tgt *hit_target;
    float *hit_target_info;
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

    D_001AEE0C = FastAddRotations(D_001AEE0C, D_001AEE10);
    D_001AEE14 = fast_subtract_rotations(D_001AEE14, D_001AEE18);
    D_001AEE28 = FastAddRotations(D_001AEE28, D_001AEE2C);

    if (chain->lockA == 0 || (locked && chain->lockB == 0)) {
        if (chain->lockB != 0) {
            chain->lockA = chain->lockB;
            chain->u.s.h40 = chain->u.s.h42;
            chain->lockB = 0;
            chain->u.s.h42 = 0;
        } else {
            scan_index = 0;
            for (candidate = D_001EE960[0]; candidate != 0; candidate = D_001EE960[++scan_index]) {
                if (candidate != chain->lockA && candidate != chain->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (moby_get_private_value_0(candidate) != 0) {
                                FastVecSub(lock_point_a, candidate->pos, chain);
                                if (D_001A8CA0 != 0) {
                                    proj = FastVecDot(lock_point_a, g_hero_state.ent + 0xE0);
                                    FastVecScale(lock_point_b, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(scratch_b, lock_point_a, lock_point_b);
                                    dist = FastVecLength(scratch_b);
                                } else {
                                    dist = vec_length_xy(lock_point_a);
                                }
                                if (!(D_001AEDF4 < dist)) {
                                    ang = FastDiffRots(g_active_camera[0x158 / 4], mat_fast_helper_a(candidate->pos[0] - g_active_camera[0x140 / 4], candidate->pos[1] - g_active_camera[0x144 / 4]));
                                    if (!(D_001AEDFC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (D_001A8CA0 != 0) {
                                            FastVecSub(lock_point_b, candidate->pos, &g_hero_state.x);
                                            proj2 = FastVecDot(lock_point_b, g_hero_state.ent + 0xE0);
                                            FastVecScale(scratch_b, g_hero_state.ent + 0xE0, proj2);
                                            FastVecSub(lock_point_b, lock_point_b, scratch_b);
                                            cs = FastVecDot(lock_point_b, g_hero_state.ent + 0xC0);
                                            sm = FastVecLength(lock_point_b);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - math_fast_angle_helper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(mat_fast_helper_a(candidate->pos[0] - g_hero_state.x, candidate->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(D_001AEDF8 < sa2)) {
                                                angle_score = (D_001AEDFC - ang) / D_001AEDFC;
                                                distance_score = (D_001AEDF4 - dist) / D_001AEDF4;
                                                score = angle_score * D_001AEE8C + distance_score;
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
        if (chain->lockA != 0) {
            second = best;
        } else {
            chain->lockA = best;
            chain->u.s.h40 = 0;
            if (math_fast_float_d(&D_001B23E0) != 0)
                D_001B23E0 = 0xA;
        }
    }
    if (second != 0 && locked) {
        d0 = fast_vec_dist(chain, best->pos);
        if (d0 < D_001AEDF4 && d0 + fast_vec_dist(best->pos, second->pos) < D_001AEDF4) {
            chain->u.s.h42 = 0;
            chain->lockB = second;
        }
    }
    len = 0.0f;
    if (chain->lockA != 0) {
        info_a = moby_get_private_value_0(chain->lockA);
        target_a = chain->lockA;
        qcopy(lock_point_a, target_a->pos);
        FastVecScale(lock_point_b, (char *)target_a + 0xE0, info_a[4]);
        FastVecAdd(lock_point_a, lock_point_a, lock_point_b);
        len = fast_vec_dist(chain, lock_point_a);
        reach = len * 0.05f;
    }
    if (chain->lockB != 0) {
        info_b = moby_get_private_value_0(chain->lockB);
        target_b = chain->lockB;
        qcopy(lock_point_b, target_b->pos);
        FastVecScale(scratch_b, (char *)target_b + 0xE0, info_b[4]);
        FastVecAdd(lock_point_b, lock_point_b, scratch_b);
        reach = (fast_vec_dist(lock_point_a, lock_point_b) + len) * 0.05f;
    }
    if (locked)
        D_001AEE58 = 0x207F20;
    else
        D_001AEE58 = 0x7F2020;
    vec_clear_128(scratch_b);
    make_hit_descriptor(&hit_info, self, 0x210000, scratch_b, (&g_weapon_table[g_item_slot_to_record.cur])->f70);
    hit_info.kind = 5;
    hit_info.flag = 1;
    hit_info.tag = self->tag;
    chain->count = 0x14;
    coll_process_hit(chain, 0x10, g_hero_state.ent, &hit_info, 0.3f);
    FastVecSub(tether_dir, chain->b, chain);
    vec_scale_to_length(tether_dir, tether_dir, 1.0f);
    if (chain->lockA != 0 || chain->lockB != 0) {
        FastVecCross(segment_delta, tether_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(tether_dir, tether_dir, segment_delta, 0.17453295f);
    }
    hit_something = 0;
    FastVecScale(last_step, tether_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = chain->a;
        qcopy(&D_00229170[0][0], anchor);
    }
    {
        float *anchor = chain->a;
        qcopy(&D_00229170[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_001AEE04 + (D_001AEE08 - D_001AEE04) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_001AEE0C + (float)i * D_001AEE00));
        height += math_random_signed_float_range(D_001AEE44, D_001AEE48);
        old = D_002293F0[i];
        D_002293F0[i] = height;
        D_00229170[0][i].f[2] = D_00229170[0][i].f[2] - old;
        vec_transform_or_copy(&D_00229170[0][i], &D_00229170[0][i]);
        FastVecSub(segment_delta, &D_00229170[0][i], D_00229160[i]);
        lerp_vector(step_vec, segment_delta, last_step, 0.85f);
        {
            float cm = FastVecLength(step_vec);
            if (cm == 0.0f) {
                prev = &D_00229170[0][i - 1];
                qcopy(&D_00229170[0][i], prev);
            } else {
                FastVecScale(step_vec, step_vec, reach / cm);
                FastVecAdd(&D_00229170[0][i], D_00229160[i], step_vec);
                qcopy(last_step, step_vec);
            }
        }
        D_00229170[0][i].f[2] = D_00229170[0][i].f[2] + height;
        FastVecSub(segment_delta, &D_00229170[0][i], D_00229160[i]);
        if (chain->lockA != 0) {
            if (!locked || chain->lockB == 0) {
                FastVecSub(scratch_a, lock_point_a, &D_00229170[0][i]);
                length = FastVecLength(scratch_a);
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
                    FastVecScale(scratch_a, scratch_a, reach / length);
                    lerp_vector(last_step, last_step, scratch_a, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratch_a, lock_point_b, &D_00229170[0][i]);
                else
                    FastVecSub(scratch_a, lock_point_a, &D_00229170[0][i]);
                length = FastVecLength(scratch_a);
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
                    FastVecScale(scratch_a, scratch_a, reach / length);
                    lerp_vector(last_step, last_step, scratch_a, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(D_001AEE14 + (float)i * D_001AEE1C);
            amp = D_001AEE20 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_001AEE28 + (float)i * D_001AEE30));
            qcopy(&D_00229170[1][i], &D_00229170[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            D_00229580[i] = height;
            D_00229170[1][i].f[2] = D_00229170[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(segment_delta[0], segment_delta[1]), 1.5707965f);
                {
                    float radial = D_001AEE24 * math_fast_sin_or_cos_a(angle);
                    radial_offset[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    radial_offset[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    radial_offset[2] = 0.0f;
                    qcopy_nc(&D_00229440[i], radial_offset);
                }
            }
            FastVecAdd(&D_00229170[1][i], &D_00229170[1][i], radial_offset);
        } else {
            mirror_index = 0x15 - i;
            qcopy(&D_00229170[1][i], &D_00229170[0][i]);
            D_00229170[1][i].f[2] = D_00229170[1][i].f[2] + D_00229580[mirror_index];
            FastVecAdd(&D_00229170[1][i], &D_00229170[1][i], &D_00229440[mirror_index]);
            qcopy(radial_offset, &D_00229440[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratch_b, &D_00229170[0][i], g_camera_eye_state);
            if (D_001A8CA0 != 0) {
                float cpj = FastVecDot(scratch_b, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(scratch_a, ax, cpj);
                    FastVecSub(scratch_b, scratch_b, scratch_a);
                }
            } else {
                *(int *)&scratch_b[2] = 0;
            }
            cm2 = FastVecLength(scratch_b);
            if (cm2 == 0.0f)
                scratch_b[2] = 1.0f;
            else
                FastVecScale(scratch_b, scratch_b, 1.0f / cm2);
            scratch_b[3] = 5627.925f;
            qcopy(&hit_info, scratch_b);
            hit_something = CollLine(D_00229150[i], &D_00229170[0][i], 0x10, self, 0);
            if (hit_something != 0) {
                hit_target = D_001BAF98.hit;
                if (hit_target != 0) {
                    hit_target_info = moby_get_private_value_0(hit_target);
                    if (hit_target_info == 0) {
                        QueueMobyImpact(hit_target, &hit_info);
                    } else if (hit_target->cls == 0 || hit_target->cls->id != 5) {
                        QueueMobyImpact(hit_target, &hit_info);
                    } else {
                        hit_something = 0;
                        held_targets[held_count++] = hit_target;
                        hit_target->f98 = 0;
                    }
                }
                if (hit_something != 0) {
                    qcopy(&D_00229170[0][i], D_001BAF98.pos);
                    {
                        short last = i;
                        chain->count = last;
                    }
                    qcopy(chain->b, D_001BAF98.pos);
                    if (D_001BAF98.hit == 0) {
                        chain->lockA = 0;
                        chain->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < held_count; n++)
        held_targets[n]->f98 = held_targets[n]->cls->f10;
    if (hit_something == 0)
        qcopy(chain->b, &D_002292A0);
    if (chain->lockA != 0 && (chain->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hit_buffer.q;
        FastVecSub(scratch_a, chain->lockA->pos, g_camera_eye_state);
        if (D_001A8CA0 != 0) {
            apj = FastVecDot(scratch_a, g_hero_state.ent + 0xE0);
            FastVecScale(tv, g_hero_state.ent + 0xE0, apj);
            FastVecSub(scratch_a, scratch_a, tv);
        } else {
            *(int *)&scratch_a[2] = 0;
        }
        vec_scale_to_length(scratch_a, scratch_a, 1.0f);
        scratch_a[3] = 5627.925f;
        make_hit_descriptor(&hit_buffer.a.r, self, 0x210000, scratch_a, (&g_weapon_table[g_item_slot_to_record.cur])->f70);
        hit_buffer.a.r.kind = 5;
        hit_buffer.a.r.flag = 3;
        hit_buffer.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(chain->lockA, &hit_buffer.a.r);
        ainfo = moby_get_private_value_0(chain->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = an;
            chain->u.s.h44 = result;
        }
    }
    if (chain->lockB != 0 && (chain->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratch_a, chain->lockB->pos, g_camera_eye_state);
        if (D_001A8CA0 != 0) {
            bpj = FastVecDot(scratch_a, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buffer.q, g_hero_state.ent + 0xE0, bpj);
            FastVecSub(scratch_a, scratch_a, hit_buffer.q);
        } else {
            *(int *)&scratch_a[2] = 0;
        }
        vec_scale_to_length(scratch_a, scratch_a, 1.0f);
        scratch_a[3] = 5627.925f;
        make_hit_descriptor(&hit_buffer.b.r, self, 0x210000, scratch_a, (&g_weapon_table[g_item_slot_to_record.cur])->f70);
        hit_buffer.b.r.kind = 5;
        hit_buffer.b.r.flag = 3;
        hit_buffer.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(chain->lockB, &hit_buffer.b.r);
        binfo = moby_get_private_value_0(chain->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = bn;
            chain->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = chain->a;
                qcopy(hit_buffer.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hit_buffer.q, chain->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&D_001B23E8[k]) != 0) {
            D_001B23E8[k] = D_001B23F8[k];
            D_001B23F0[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(scratch_a, tether_dir, ksize);
            math_apply_axis_rotation_to_quat(scratch_a, scratch_a, D_0018A560, angle1);
            math_apply_axis_rotation_to_quat(scratch_a, scratch_a, D_0018A560 + 0x10, angle0);
            qcopy(&D_002295D0[k].v[0], hit_buffer.q);
            ks = 1.0f;
            FastVecAdd(&D_002295D0[k].v[1], hit_buffer.q, scratch_a);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hit_buffer.q + 4, &D_002295C0[k].p[j1 - 1], g_camera_eye_state);
                kf = math_random_float_range(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                math_apply_axis_rotation_to_quat(scratch_a, scratch_a, hit_buffer.q + 4, kf);
                FastVecAdd(D_002295D0[k].v + j1, &D_002295C0[k].p[j1 - 1], scratch_a);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = tmp[j2];
                FastVecSub(q, D_002295D0[k].v + j2, &D_002295C0[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_002295D0[k].v[0], hit_buffer.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(D_002295D0[k].v + j2, &D_002295C0[k].p[j2 - 1], tmp[j2]);
            {
                int x = D_001B2400[k];
                int y = D_001B23E8[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                D_001B23F0[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(scratch_a, tether_dir, D_001AEE88);
        math_apply_axis_rotation_to_quat(scratch_a, scratch_a, D_0018A560, angle1);
        math_apply_axis_rotation_to_quat(scratch_a, scratch_a, D_0018A560 + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(chain, 0xF, tsize * 0.3f, tsize, D_001AEE58 | 0x7F000000, 0, spin, scratch_a, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(chain, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, scratch_a, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(chain->b, 0xC, tsize * 0.1f, tsize, D_001AEE58 | 0x7F000000, 0, spin, D_001A8BD0, 1, 0.0f);
    }
}
