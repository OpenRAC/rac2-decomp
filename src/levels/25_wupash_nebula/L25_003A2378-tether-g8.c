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
extern Slot D_L25_002735F0[];
extern Cam g_hero_state;
extern char D_0018A560[];
extern int D_L25_001A8FF0;
extern float D_L25_001A8F20[] MACRO_ADDR;
extern int D_L25_001B2940;
extern short D_L25_001B2948[] MACRO_ADDR;
extern short D_L25_001B2950[] MACRO_ADDR;
extern short D_L25_001B2958[] MACRO_ADDR;
extern short D_L25_001B2960[] MACRO_ADDR;
extern float D_L25_001B90C0[];
extern char D_L25_001B9200[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult D_L25_001BF658;
extern Tgt *D_L25_001FB120[];
extern float D_L25_0023AFF0[][4], D_L25_0023B000[][4];
extern Vec D_L25_0023B010[2][20];
extern V4 D_L25_0023B140;
extern float D_L25_0023B290[];
extern Vec D_L25_0023B2E0[];
extern float D_L25_0023B420[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 D_L25_0023B460[];
extern Node5 D_L25_0023B470[];

extern float D_L25_001AEFF4 __attribute__((sda));
extern float D_L25_001AEFF8 __attribute__((sda));
extern float D_L25_001AEFFC __attribute__((sda));
extern float D_L25_001AF000 __attribute__((sda));
extern float D_L25_001AF004 __attribute__((sda));
extern float D_L25_001AF008 __attribute__((sda));
extern float D_L25_001AF00C __attribute__((sda));
extern float D_L25_001AF010 __attribute__((sda));
extern float D_L25_001AF014 __attribute__((sda));
extern float D_L25_001AF018 __attribute__((sda));
extern float D_L25_001AF01C __attribute__((sda));
extern float D_L25_001AF020 __attribute__((sda));
extern float D_L25_001AF024 __attribute__((sda));
extern float D_L25_001AF028 __attribute__((sda));
extern float D_L25_001AF02C __attribute__((sda));
extern float D_L25_001AF030 __attribute__((sda));
extern float D_L25_001AF044 __attribute__((sda));
extern float D_L25_001AF048 __attribute__((sda));
extern float D_L25_001AF088 __attribute__((sda));
extern float D_L25_001AF08C __attribute__((sda));
extern int D_L25_001AF058 __attribute__((sda));

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

/* Updates the lock-on tether: picks up to two targets, swings the chain of points toward them and spawns sparks. */
void hero_l25_update_lock_on_tether(Moby *tether_moby)
{
    int locked = D_L25_002735F0[g_item_slot_to_record.cur].on != 0;
    float reach = D_L25_001AEFF4 * 0.05f;
    Rope *rope = tether_moby->rope;
    float aim_point_a[4] __attribute__((aligned(16)));
    float aim_point_b[4] __attribute__((aligned(16)));
    float scratch_vec[4] __attribute__((aligned(16)));
    Hit hit_info __attribute__((aligned(16)));
    float rope_dir[4] __attribute__((aligned(16)));
    float link_offset[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float spark_offset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float tmp_vec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buf __attribute__((aligned(16)));
    float spark_tmp[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hit_something, held_count;
    float bestScore = 0.0f, secondScore = 0.0f;
    float len;
    float angle0, angle1;
    int held_index;
    Tgt *target;
    int target_index;
    float dist, ang, cam_angle, side_dot, flat_length, score, projection, angle_factor, dist_factor;
    float dist_to_best;
    float *info_a, *info_b;
    Tgt *target_a, *target_b;
    float length, blend;
    float amp, height, angle, old_height, divisor;
    int mirror_index;
    Tgt *hit_target;
    float *hit_info_ptr;
    float *temp_ptr, projection_a, *info_ptr_a;
    int hit_kind_a;
    float projection_b, *info_ptr_b;
    int hit_kind_b;
    float spark_size, spark_factor, spark_sign;
    int new_index, update_index;
    float *diff_vec;
    int spin_speed;
    float glow_size, divisor2;
    Vec *prev_point;
    float projection2, dir_length;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    D_L25_001AF00C = FastAddRotations(D_L25_001AF00C, D_L25_001AF010);
    D_L25_001AF014 = fast_subtract_rotations(D_L25_001AF014, D_L25_001AF018);
    D_L25_001AF028 = FastAddRotations(D_L25_001AF028, D_L25_001AF02C);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            target_index = 0;
            for (target = D_L25_001FB120[0]; target != 0; target = D_L25_001FB120[++target_index]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (moby_get_private_value_0(target) != 0) {
                                FastVecSub(aim_point_a, target->pos, rope);
                                if (D_L25_001A8FF0 != 0) {
                                    projection = FastVecDot(aim_point_a, g_hero_state.ent + 0xE0);
                                    FastVecScale(aim_point_b, g_hero_state.ent + 0xE0, projection);
                                    FastVecSub(scratch_vec, aim_point_a, aim_point_b);
                                    dist = FastVecLength(scratch_vec);
                                } else {
                                    dist = vec_length_xy(aim_point_a);
                                }
                                if (!(D_L25_001AEFF4 < dist)) {
                                    ang = FastDiffRots(D_L25_001B90C0[0x158 / 4], mat_fast_helper_a(target->pos[0] - D_L25_001B90C0[0x140 / 4], target->pos[1] - D_L25_001B90C0[0x144 / 4]));
                                    if (!(D_L25_001AEFFC < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `flatLength` test below ($f21, c.eq.s). */
                                        cam_angle = 0.0f;
                                        if (D_L25_001A8FF0 != 0) {
                                            FastVecSub(aim_point_b, target->pos, &g_hero_state.x);
                                            projection2 = FastVecDot(aim_point_b, g_hero_state.ent + 0xE0);
                                            FastVecScale(scratch_vec, g_hero_state.ent + 0xE0, projection2);
                                            FastVecSub(aim_point_b, aim_point_b, scratch_vec);
                                            side_dot = FastVecDot(aim_point_b, g_hero_state.ent + 0xC0);
                                            flat_length = FastVecLength(aim_point_b);
                                            if (flat_length == 0.0f)
                                                continue;
                                            cam_angle = 1.5707964f - math_fast_angle_helper(side_dot / flat_length);
                                        } else {
                                            cam_angle = FastDiffRots(mat_fast_helper_a(target->pos[0] - g_hero_state.x, target->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(D_L25_001AEFF8 < cam_angle)) {
                                                angle_factor = (D_L25_001AEFFC - ang) / D_L25_001AEFFC;
                                                dist_factor = (D_L25_001AEFF4 - dist) / D_L25_001AEFF4;
                                                score = angle_factor * D_L25_001AF08C + dist_factor;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second = best;
                                                    best = target;
                                                } else if (secondScore < score) {
                                                    second = target;
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
        if (rope->lockA != 0) {
            second = best;
        } else {
            rope->lockA = best;
            rope->u.s.h40 = 0;
            if (math_fast_float_d(&D_L25_001B2940) != 0)
                D_L25_001B2940 = 0xA;
        }
    }
    if (second != 0 && locked) {
        dist_to_best = fast_vec_dist(rope, best->pos);
        if (dist_to_best < D_L25_001AEFF4 && dist_to_best + fast_vec_dist(best->pos, second->pos) < D_L25_001AEFF4) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    len = 0.0f;
    if (rope->lockA != 0) {
        info_a = moby_get_private_value_0(rope->lockA);
        target_a = rope->lockA;
        qcopy(aim_point_a, target_a->pos);
        FastVecScale(aim_point_b, (char *)target_a + 0xE0, info_a[4]);
        FastVecAdd(aim_point_a, aim_point_a, aim_point_b);
        len = fast_vec_dist(rope, aim_point_a);
        reach = len * 0.05f;
    }
    if (rope->lockB != 0) {
        info_b = moby_get_private_value_0(rope->lockB);
        target_b = rope->lockB;
        qcopy(aim_point_b, target_b->pos);
        FastVecScale(scratch_vec, (char *)target_b + 0xE0, info_b[4]);
        FastVecAdd(aim_point_b, aim_point_b, scratch_vec);
        reach = (fast_vec_dist(aim_point_a, aim_point_b) + len) * 0.05f;
    }
    if (locked)
        D_L25_001AF058 = 0x207F20;
    else
        D_L25_001AF058 = 0x7F2020;
    vec_clear_128(scratch_vec);
    make_hit_descriptor(&hit_info, tether_moby, 0x210000, scratch_vec, (&D_L25_002735F0[g_item_slot_to_record.cur])->f70);
    hit_info.kind = 5;
    hit_info.flag = 1;
    hit_info.tag = tether_moby->tag;
    rope->count = 0x14;
    coll_process_hit(rope, 0x10, g_hero_state.ent, &hit_info, 0.3f);
    FastVecSub(rope_dir, rope->b, rope);
    vec_scale_to_length(rope_dir, rope_dir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(link_offset, rope_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(rope_dir, rope_dir, link_offset, 0.17453295f);
    }
    hit_something = 0;
    FastVecScale(velocity, rope_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&D_L25_0023B010[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&D_L25_0023B010[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = D_L25_001AF004 + (D_L25_001AF008 - D_L25_001AF004) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L25_001AF00C + (float)i * D_L25_001AF000));
        height += math_random_signed_float_range(D_L25_001AF044, D_L25_001AF048);
        old_height = D_L25_0023B290[i];
        D_L25_0023B290[i] = height;
        D_L25_0023B010[0][i].f[2] = D_L25_0023B010[0][i].f[2] - old_height;
        vec_transform_or_copy(&D_L25_0023B010[0][i], &D_L25_0023B010[0][i]);
        FastVecSub(link_offset, &D_L25_0023B010[0][i], D_L25_0023B000[i]);
        lerp_vector(pull, link_offset, velocity, 0.85f);
        {
            float chain_length = FastVecLength(pull);
            if (chain_length == 0.0f) {
                prev_point = &D_L25_0023B010[0][i - 1];
                qcopy(&D_L25_0023B010[0][i], prev_point);
            } else {
                FastVecScale(pull, pull, reach / chain_length);
                FastVecAdd(&D_L25_0023B010[0][i], D_L25_0023B000[i], pull);
                qcopy(velocity, pull);
            }
        }
        D_L25_0023B010[0][i].f[2] = D_L25_0023B010[0][i].f[2] + height;
        FastVecSub(link_offset, &D_L25_0023B010[0][i], D_L25_0023B000[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(tmp_vec, aim_point_a, &D_L25_0023B010[0][i]);
                length = FastVecLength(tmp_vec);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        divisor = IntToFloat(0x13 - i);
                        reach = length / divisor;
                    } else {
                        blend = 0.1f;
                    }
                    FastVecScale(tmp_vec, tmp_vec, reach / length);
                    lerp_vector(velocity, velocity, tmp_vec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(tmp_vec, aim_point_b, &D_L25_0023B010[0][i]);
                else
                    FastVecSub(tmp_vec, aim_point_a, &D_L25_0023B010[0][i]);
                length = FastVecLength(tmp_vec);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if (i >= 5 && i < 10) {
                        blend = 0.7f;
                        divisor = IntToFloat(9 - i);
                        reach = length / divisor;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        divisor2 = IntToFloat(0x13 - i);
                        reach = length / divisor2;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(tmp_vec, tmp_vec, reach / length);
                    lerp_vector(velocity, velocity, tmp_vec, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(D_L25_001AF014 + (float)i * D_L25_001AF01C);
            amp = D_L25_001AF020 * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(D_L25_001AF028 + (float)i * D_L25_001AF030));
            qcopy(&D_L25_0023B010[1][i], &D_L25_0023B010[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            D_L25_0023B420[i] = height;
            D_L25_0023B010[1][i].f[2] = D_L25_0023B010[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(link_offset[0], link_offset[1]), 1.5707965f);
                {
                    float radial = D_L25_001AF024 * math_fast_sin_or_cos_a(angle);
                    spark_offset[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    spark_offset[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    spark_offset[2] = 0.0f;
                    qcopy_nc(&D_L25_0023B2E0[i], spark_offset);
                }
            }
            FastVecAdd(&D_L25_0023B010[1][i], &D_L25_0023B010[1][i], spark_offset);
        } else {
            mirror_index = 0x15 - i;
            qcopy(&D_L25_0023B010[1][i], &D_L25_0023B010[0][i]);
            D_L25_0023B010[1][i].f[2] = D_L25_0023B010[1][i].f[2] + D_L25_0023B420[mirror_index];
            FastVecAdd(&D_L25_0023B010[1][i], &D_L25_0023B010[1][i], &D_L25_0023B2E0[mirror_index]);
            qcopy(spark_offset, &D_L25_0023B2E0[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(scratch_vec, &D_L25_0023B010[0][i], D_L25_001B9200);
            if (D_L25_001A8FF0 != 0) {
                float projection_c = FastVecDot(scratch_vec, g_hero_state.ent + 0xE0);
                {
                    char *up_axis = g_hero_state.ent + 0xE0;
                    FastVecScale(tmp_vec, up_axis, projection_c);
                    FastVecSub(scratch_vec, scratch_vec, tmp_vec);
                }
            } else {
                *(int *)&scratch_vec[2] = 0;
            }
            dir_length = FastVecLength(scratch_vec);
            if (dir_length == 0.0f)
                scratch_vec[2] = 1.0f;
            else
                FastVecScale(scratch_vec, scratch_vec, 1.0f / dir_length);
            scratch_vec[3] = 5627.925f;
            qcopy(&hit_info, scratch_vec);
            hit_something = CollLine(D_L25_0023AFF0[i], &D_L25_0023B010[0][i], 0x10, tether_moby, 0);
            if (hit_something != 0) {
                hit_target = D_L25_001BF658.hit;
                if (hit_target != 0) {
                    hit_info_ptr = moby_get_private_value_0(hit_target);
                    if (hit_info_ptr == 0) {
                        QueueMobyImpact(hit_target, &hit_info);
                    } else if (hit_target->cls == 0 || hit_target->cls->id != 5) {
                        QueueMobyImpact(hit_target, &hit_info);
                    } else {
                        hit_something = 0;
                        held[held_count++] = hit_target;
                        hit_target->f98 = 0;
                    }
                }
                if (hit_something != 0) {
                    qcopy(&D_L25_0023B010[0][i], D_L25_001BF658.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, D_L25_001BF658.pos);
                    if (D_L25_001BF658.hit == 0) {
                        rope->lockA = 0;
                        rope->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (held_index = 0; held_index < held_count; held_index++)
        held[held_index]->f98 = held[held_index]->cls->f10;
    if (hit_something == 0)
        qcopy(rope->b, &D_L25_0023B140);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        temp_ptr = hit_buf.q;
        FastVecSub(tmp_vec, rope->lockA->pos, D_L25_001B9200);
        if (D_L25_001A8FF0 != 0) {
            projection_a = FastVecDot(tmp_vec, g_hero_state.ent + 0xE0);
            FastVecScale(temp_ptr, g_hero_state.ent + 0xE0, projection_a);
            FastVecSub(tmp_vec, tmp_vec, temp_ptr);
        } else {
            *(int *)&tmp_vec[2] = 0;
        }
        vec_scale_to_length(tmp_vec, tmp_vec, 1.0f);
        tmp_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.a.r, tether_moby, 0x210000, tmp_vec, (&D_L25_002735F0[g_item_slot_to_record.cur])->f70);
        hit_buf.a.r.kind = 5;
        hit_buf.a.r.flag = 3;
        hit_buf.a.r.tag = tether_moby->tag;
        hit_kind_a = 5;
        QueueMobyImpact(rope->lockA, &hit_buf.a.r);
        info_ptr_a = moby_get_private_value_0(rope->lockA);
        if (info_ptr_a != 0) {
            if (((short *)info_ptr_a)[2] == 1)
                hit_kind_a = 1;
        }
        {
            short result = hit_kind_a;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(tmp_vec, rope->lockB->pos, D_L25_001B9200);
        if (D_L25_001A8FF0 != 0) {
            projection_b = FastVecDot(tmp_vec, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buf.q, g_hero_state.ent + 0xE0, projection_b);
            FastVecSub(tmp_vec, tmp_vec, hit_buf.q);
        } else {
            *(int *)&tmp_vec[2] = 0;
        }
        vec_scale_to_length(tmp_vec, tmp_vec, 1.0f);
        tmp_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.b.r, tether_moby, 0x210000, tmp_vec, (&D_L25_002735F0[g_item_slot_to_record.cur])->f70);
        hit_buf.b.r.kind = 5;
        hit_buf.b.r.flag = 3;
        hit_buf.b.r.tag = tether_moby->tag;
        hit_kind_b = 5;
        QueueMobyImpact(rope->lockB, &hit_buf.b.r);
        info_ptr_b = moby_get_private_value_0(rope->lockB);
        if (info_ptr_b != 0) {
            if (((short *)info_ptr_b)[2] == 1)
                hit_kind_b = 1;
        }
        {
            short result = hit_kind_b;
            rope->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = rope->a;
                qcopy(hit_buf.q, from);
            }
            spark_size = 0.4f;
        } else {
            qcopy(hit_buf.q, rope->b);
            spark_size = 0.5f;
        }
        if (FastDecTimer(&D_L25_001B2948[k]) != 0) {
            D_L25_001B2948[k] = D_L25_001B2958[k];
            D_L25_001B2950[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(tmp_vec, rope_dir, spark_size);
            math_apply_axis_rotation_to_quat(tmp_vec, tmp_vec, D_0018A560, angle1);
            math_apply_axis_rotation_to_quat(tmp_vec, tmp_vec, D_0018A560 + 0x10, angle0);
            qcopy(&D_L25_0023B470[k].v[0], hit_buf.q);
            spark_sign = 1.0f;
            FastVecAdd(&D_L25_0023B470[k].v[1], hit_buf.q, tmp_vec);
            for (new_index = 2; new_index < 5; new_index++) {
                FastVecSub(hit_buf.q + 4, &D_L25_0023B460[k].p[new_index - 1], D_L25_001B9200);
                spark_factor = math_random_float_range(0.17453295f, 0.9599312f) * spark_sign;
                spark_sign = -spark_sign;
                math_apply_axis_rotation_to_quat(tmp_vec, tmp_vec, hit_buf.q + 4, spark_factor);
                FastVecAdd(D_L25_0023B470[k].v + new_index, &D_L25_0023B460[k].p[new_index - 1], tmp_vec);
            }
        } else {
            for (update_index = 1; update_index < 5; update_index++) {
                diff_vec = spark_tmp[update_index];
                FastVecSub(diff_vec, D_L25_0023B470[k].v + update_index, &D_L25_0023B460[k].p[update_index - 1]);
                diff_vec[0] = diff_vec[0] + math_random_signed_float_range(0.0f, 0.1f);
                diff_vec[1] = diff_vec[1] + math_random_signed_float_range(0.0f, 0.1f);
                diff_vec[2] = diff_vec[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&D_L25_0023B470[k].v[0], hit_buf.q);
            for (update_index = 1; update_index < 5; update_index++)
                FastVecAdd(D_L25_0023B470[k].v + update_index, &D_L25_0023B460[k].p[update_index - 1], spark_tmp[update_index]);
            {
                int x = D_L25_001B2960[k];
                int y = D_L25_001B2948[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                spark_factor = IntToFloat(x);
                spark_factor = spark_factor / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - spark_factor) * 32.0f);
                D_L25_001B2950[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(tmp_vec, rope_dir, D_L25_001AF088);
        math_apply_axis_rotation_to_quat(tmp_vec, tmp_vec, D_0018A560, angle1);
        math_apply_axis_rotation_to_quat(tmp_vec, tmp_vec, D_0018A560 + 0x10, angle0);
        spin_speed = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin_speed = -spin_speed;
        glow_size = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(rope, 0xF, glow_size * 0.3f, glow_size, D_L25_001AF058 | 0x7F000000, 0, spin_speed, tmp_vec, 1, 0.0f);
        spin_speed = -spin_speed;
        part_spawn_ground_effect(rope, 0xF, glow_size * 0.15f, glow_size * 0.5f, 0x307F7F7F, 0, spin_speed, tmp_vec, 1, 0.0f);
        spin_speed = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin_speed = -spin_speed;
        glow_size = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(rope->b, 0xC, glow_size * 0.1f, glow_size, D_L25_001AF058 | 0x7F000000, 0, spin_speed, D_L25_001A8F20, 1, 0.0f);
    }
}
