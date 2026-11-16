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
extern Slot g_item_l24_material_table[];
extern Cam g_hero_state;
extern char g_tether_axis_vectors[];
extern int g_tether_l24_disabled_flag;
extern float g_ground_l24_effect_vec[] MACRO_ADDR;
extern int g_tether_l24_spark_timer;
extern short g_tether_l24_segment_timers[] MACRO_ADDR;
extern short g_tether_l24_segment_fades[] MACRO_ADDR;
extern short g_tether_l24_segment_timer_resets[] MACRO_ADDR;
extern short g_tether_l24_segment_offsets[] MACRO_ADDR;
extern float g_hero_object_ref[];
extern char g_tether_l24_origin_vec[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult g_tether_l24_hit_result;
extern Tgt *g_target_l24_list[];
extern float g_tether_l24_ray_starts[][4], g_tether_l24_pull_offsets[][4];
extern Vec g_tether_l24_rope_points[2][20];
extern V4 g_tether_l24_end_vec;
extern float g_tether_l24_prev_heights[];
extern Vec g_tether_l24_sway_vecs[];
extern float g_tether_l24_heights[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 g_tether_l24_hit_headers[];
extern Node5 g_tether_l24_hit_nodes[];

extern float g_tether_l24_reach_distance __attribute__((sda));
extern float g_tether_l24_camera_angle_limit __attribute__((sda));
extern float g_tether_l24_angle_limit __attribute__((sda));
extern float g_tether_l24_wave_height_spacing __attribute__((sda));
extern float g_tether_l24_wave_amp_start __attribute__((sda));
extern float g_tether_l24_wave_amp_end __attribute__((sda));
extern float g_tether_l24_wave_height_phase __attribute__((sda));
extern float g_tether_l24_wave_height_speed __attribute__((sda));
extern float g_tether_l24_wave_side_phase __attribute__((sda));
extern float g_tether_l24_wave_side_speed __attribute__((sda));
extern float g_tether_l24_wave_side_spacing __attribute__((sda));
extern float g_tether_l24_wave_amp_scale __attribute__((sda));
extern float g_tether_l24_radial_scale __attribute__((sda));
extern float g_tether_l24_wave_amp_phase __attribute__((sda));
extern float g_tether_l24_wave_amp_speed __attribute__((sda));
extern float g_tether_l24_wave_amp_spacing __attribute__((sda));
extern float g_tether_l24_height_jitter_min __attribute__((sda));
extern float g_tether_l24_height_jitter_max __attribute__((sda));
extern float g_tether_l24_dir_scale __attribute__((sda));
extern float g_tether_l24_score_scale __attribute__((sda));
extern int g_tether_l24_glow_color __attribute__((sda));

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

/* Updates the lock-on tether: picks up to two targets, bends the chain of points from the hand toward them, and makes the glow spots and sparks. */
void hero_l24_update_lock_on_tether(Moby *self)
{
    int locked = g_item_l24_material_table[g_item_slot_to_record.cur].on != 0;
    float reach = g_tether_l24_reach_distance * 0.05f;
    Rope *rope = self->rope;
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    float vec_c[4] __attribute__((aligned(16)));
    Hit first_hit __attribute__((aligned(16)));
    float aim_dir[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float pull[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    float sway[4] __attribute__((aligned(16)));
    Tgt *disabled_targets[128];
    float scratch[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *best_target = 0, *second_target = 0;
    int hit_something, held_count;
    float bestScore = 0.0f, secondScore = 0.0f;
    float lock_a_length;
    float angle0, angle1;
    int n;
    Tgt *target;
    int target_index;
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

    g_tether_l24_wave_height_phase = FastAddRotations(g_tether_l24_wave_height_phase, g_tether_l24_wave_height_speed);
    g_tether_l24_wave_side_phase = fast_subtract_rotations(g_tether_l24_wave_side_phase, g_tether_l24_wave_side_speed);
    g_tether_l24_wave_amp_phase = FastAddRotations(g_tether_l24_wave_amp_phase, g_tether_l24_wave_amp_speed);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            target_index = 0;
            for (target = g_target_l24_list[0]; target != 0; target = g_target_l24_list[++target_index]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (moby_get_private_value_0(target) != 0) {
                                FastVecSub(vec_a, target->pos, rope);
                                if (g_tether_l24_disabled_flag != 0) {
                                    proj = FastVecDot(vec_a, g_hero_state.ent + 0xE0);
                                    FastVecScale(vec_b, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(vec_c, vec_a, vec_b);
                                    dist = FastVecLength(vec_c);
                                } else {
                                    dist = vec_length_xy(vec_a);
                                }
                                if (!(g_tether_l24_reach_distance < dist)) {
                                    ang = FastDiffRots(g_hero_object_ref[0x158 / 4], mat_fast_helper_a(target->pos[0] - g_hero_object_ref[0x140 / 4], target->pos[1] - g_hero_object_ref[0x144 / 4]));
                                    if (!(g_tether_l24_angle_limit < ang)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `sm` test below ($f21, c.eq.s). */
                                        sa2 = 0.0f;
                                        if (g_tether_l24_disabled_flag != 0) {
                                            FastVecSub(vec_b, target->pos, &g_hero_state.x);
                                            proj2 = FastVecDot(vec_b, g_hero_state.ent + 0xE0);
                                            FastVecScale(vec_c, g_hero_state.ent + 0xE0, proj2);
                                            FastVecSub(vec_b, vec_b, vec_c);
                                            cs = FastVecDot(vec_b, g_hero_state.ent + 0xC0);
                                            sm = FastVecLength(vec_b);
                                            if (sm == 0.0f)
                                                continue;
                                            sa2 = 1.5707964f - math_fast_angle_helper(cs / sm);
                                        } else {
                                            sa2 = FastDiffRots(mat_fast_helper_a(target->pos[0] - g_hero_state.x, target->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(g_tether_l24_camera_angle_limit < sa2)) {
                                                fa = (g_tether_l24_angle_limit - ang) / g_tether_l24_angle_limit;
                                                fb = (g_tether_l24_reach_distance - dist) / g_tether_l24_reach_distance;
                                                score = fa * g_tether_l24_score_scale + fb;
                                                if (bestScore < score) {
                                                    secondScore = bestScore;
                                                    bestScore = score;
                                                    second_target = best_target;
                                                    best_target = target;
                                                } else if (secondScore < score) {
                                                    second_target = target;
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

    if (best_target != 0) {
        if (rope->lockA != 0) {
            second_target = best_target;
        } else {
            rope->lockA = best_target;
            rope->u.s.h40 = 0;
            if (math_fast_float_d(&g_tether_l24_spark_timer) != 0)
                g_tether_l24_spark_timer = 0xA;
        }
    }
    if (second_target != 0 && locked) {
        d0 = fast_vec_dist(rope, best_target->pos);
        if (d0 < g_tether_l24_reach_distance && d0 + fast_vec_dist(best_target->pos, second_target->pos) < g_tether_l24_reach_distance) {
            rope->u.s.h42 = 0;
            rope->lockB = second_target;
        }
    }
    lock_a_length = 0.0f;
    if (rope->lockA != 0) {
        ia = moby_get_private_value_0(rope->lockA);
        ta = rope->lockA;
        qcopy(vec_a, ta->pos);
        FastVecScale(vec_b, (char *)ta + 0xE0, ia[4]);
        FastVecAdd(vec_a, vec_a, vec_b);
        lock_a_length = fast_vec_dist(rope, vec_a);
        reach = lock_a_length * 0.05f;
    }
    if (rope->lockB != 0) {
        ib = moby_get_private_value_0(rope->lockB);
        tb = rope->lockB;
        qcopy(vec_b, tb->pos);
        FastVecScale(vec_c, (char *)tb + 0xE0, ib[4]);
        FastVecAdd(vec_b, vec_b, vec_c);
        reach = (fast_vec_dist(vec_a, vec_b) + lock_a_length) * 0.05f;
    }
    if (locked)
        g_tether_l24_glow_color = 0x207F20;
    else
        g_tether_l24_glow_color = 0x7F2020;
    vec_clear_128(vec_c);
    make_hit_descriptor(&first_hit, self, 0x210000, vec_c, (&g_item_l24_material_table[g_item_slot_to_record.cur])->f70);
    first_hit.kind = 5;
    first_hit.flag = 1;
    first_hit.tag = self->tag;
    rope->count = 0x14;
    coll_process_hit(rope, 0x10, g_hero_state.ent, &first_hit, 0.3f);
    FastVecSub(aim_dir, rope->b, rope);
    vec_scale_to_length(aim_dir, aim_dir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(offset, aim_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(aim_dir, aim_dir, offset, 0.17453295f);
    }
    hit_something = 0;
    FastVecScale(drift, aim_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l24_rope_points[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l24_rope_points[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = g_tether_l24_wave_amp_start + (g_tether_l24_wave_amp_end - g_tether_l24_wave_amp_start) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l24_wave_height_phase + (float)i * g_tether_l24_wave_height_spacing));
        height += math_random_signed_float_range(g_tether_l24_height_jitter_min, g_tether_l24_height_jitter_max);
        old = g_tether_l24_prev_heights[i];
        g_tether_l24_prev_heights[i] = height;
        g_tether_l24_rope_points[0][i].f[2] = g_tether_l24_rope_points[0][i].f[2] - old;
        vec_transform_or_copy(&g_tether_l24_rope_points[0][i], &g_tether_l24_rope_points[0][i]);
        FastVecSub(offset, &g_tether_l24_rope_points[0][i], g_tether_l24_pull_offsets[i]);
        lerp_vector(pull, offset, drift, 0.85f);
        {
            float cm = FastVecLength(pull);
            if (cm == 0.0f) {
                prev = &g_tether_l24_rope_points[0][i - 1];
                qcopy(&g_tether_l24_rope_points[0][i], prev);
            } else {
                FastVecScale(pull, pull, reach / cm);
                FastVecAdd(&g_tether_l24_rope_points[0][i], g_tether_l24_pull_offsets[i], pull);
                qcopy(drift, pull);
            }
        }
        g_tether_l24_rope_points[0][i].f[2] = g_tether_l24_rope_points[0][i].f[2] + height;
        FastVecSub(offset, &g_tether_l24_rope_points[0][i], g_tether_l24_pull_offsets[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(scratch, vec_a, &g_tether_l24_rope_points[0][i]);
                length = FastVecLength(scratch);
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
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratch, vec_b, &g_tether_l24_rope_points[0][i]);
                else
                    FastVecSub(scratch, vec_a, &g_tether_l24_rope_points[0][i]);
                length = FastVecLength(scratch);
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
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(drift, drift, scratch, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(g_tether_l24_wave_side_phase + (float)i * g_tether_l24_wave_side_spacing);
            amp = g_tether_l24_wave_amp_scale * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l24_wave_amp_phase + (float)i * g_tether_l24_wave_amp_spacing));
            qcopy(&g_tether_l24_rope_points[1][i], &g_tether_l24_rope_points[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            g_tether_l24_heights[i] = height;
            g_tether_l24_rope_points[1][i].f[2] = g_tether_l24_rope_points[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(offset[0], offset[1]), 1.5707965f);
                {
                    float radial = g_tether_l24_radial_scale * math_fast_sin_or_cos_a(angle);
                    sway[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    sway[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    sway[2] = 0.0f;
                    qcopy_nc(&g_tether_l24_sway_vecs[i], sway);
                }
            }
            FastVecAdd(&g_tether_l24_rope_points[1][i], &g_tether_l24_rope_points[1][i], sway);
        } else {
            fa2 = 0x15 - i;
            qcopy(&g_tether_l24_rope_points[1][i], &g_tether_l24_rope_points[0][i]);
            g_tether_l24_rope_points[1][i].f[2] = g_tether_l24_rope_points[1][i].f[2] + g_tether_l24_heights[fa2];
            FastVecAdd(&g_tether_l24_rope_points[1][i], &g_tether_l24_rope_points[1][i], &g_tether_l24_sway_vecs[fa2]);
            qcopy(sway, &g_tether_l24_sway_vecs[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vec_c, &g_tether_l24_rope_points[0][i], g_tether_l24_origin_vec);
            if (g_tether_l24_disabled_flag != 0) {
                float cpj = FastVecDot(vec_c, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(scratch, ax, cpj);
                    FastVecSub(vec_c, vec_c, scratch);
                }
            } else {
                *(int *)&vec_c[2] = 0;
            }
            cm2 = FastVecLength(vec_c);
            if (cm2 == 0.0f)
                vec_c[2] = 1.0f;
            else
                FastVecScale(vec_c, vec_c, 1.0f / cm2);
            vec_c[3] = 5627.925f;
            qcopy(&first_hit, vec_c);
            hit_something = CollLine(g_tether_l24_ray_starts[i], &g_tether_l24_rope_points[0][i], 0x10, self, 0);
            if (hit_something != 0) {
                ht = g_tether_l24_hit_result.hit;
                if (ht != 0) {
                    hinfo = moby_get_private_value_0(ht);
                    if (hinfo == 0) {
                        QueueMobyImpact(ht, &first_hit);
                    } else if (ht->cls == 0 || ht->cls->id != 5) {
                        QueueMobyImpact(ht, &first_hit);
                    } else {
                        hit_something = 0;
                        disabled_targets[held_count++] = ht;
                        ht->f98 = 0;
                    }
                }
                if (hit_something != 0) {
                    qcopy(&g_tether_l24_rope_points[0][i], g_tether_l24_hit_result.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, g_tether_l24_hit_result.pos);
                    if (g_tether_l24_hit_result.hit == 0) {
                        rope->lockA = 0;
                        rope->u.s.h40 = 0;
                    }
                    break;
                }
            }
        }
    }
    }
    for (n = 0; n < held_count; n++)
        disabled_targets[n]->f98 = disabled_targets[n]->cls->f10;
    if (hit_something == 0)
        qcopy(rope->b, &g_tether_l24_end_vec);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        tv = hit_buf.q;
        FastVecSub(scratch, rope->lockA->pos, g_tether_l24_origin_vec);
        if (g_tether_l24_disabled_flag != 0) {
            apj = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(tv, g_hero_state.ent + 0xE0, apj);
            FastVecSub(scratch, scratch, tv);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.a.r, self, 0x210000, scratch, (&g_item_l24_material_table[g_item_slot_to_record.cur])->f70);
        hit_buf.a.r.kind = 5;
        hit_buf.a.r.flag = 3;
        hit_buf.a.r.tag = self->tag;
        an = 5;
        QueueMobyImpact(rope->lockA, &hit_buf.a.r);
        ainfo = moby_get_private_value_0(rope->lockA);
        if (ainfo != 0) {
            if (((short *)ainfo)[2] == 1)
                an = 1;
        }
        {
            short result = an;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratch, rope->lockB->pos, g_tether_l24_origin_vec);
        if (g_tether_l24_disabled_flag != 0) {
            bpj = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buf.q, g_hero_state.ent + 0xE0, bpj);
            FastVecSub(scratch, scratch, hit_buf.q);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.b.r, self, 0x210000, scratch, (&g_item_l24_material_table[g_item_slot_to_record.cur])->f70);
        hit_buf.b.r.kind = 5;
        hit_buf.b.r.flag = 3;
        hit_buf.b.r.tag = self->tag;
        bn = 5;
        QueueMobyImpact(rope->lockB, &hit_buf.b.r);
        binfo = moby_get_private_value_0(rope->lockB);
        if (binfo != 0) {
            if (((short *)binfo)[2] == 1)
                bn = 1;
        }
        {
            short result = bn;
            rope->u.s.h46 = result;
        }
    }
    for (k = 0; k < 4; k++) {
        if (k < 2) {
            {
                float *from = rope->a;
                qcopy(hit_buf.q, from);
            }
            ksize = 0.4f;
        } else {
            qcopy(hit_buf.q, rope->b);
            ksize = 0.5f;
        }
        if (FastDecTimer(&g_tether_l24_segment_timers[k]) != 0) {
            g_tether_l24_segment_timers[k] = g_tether_l24_segment_timer_resets[k];
            g_tether_l24_segment_fades[k] = 0;
            angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle1 = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(scratch, aim_dir, ksize);
            math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors, angle1);
            math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors + 0x10, angle0);
            qcopy(&g_tether_l24_hit_nodes[k].v[0], hit_buf.q);
            ks = 1.0f;
            FastVecAdd(&g_tether_l24_hit_nodes[k].v[1], hit_buf.q, scratch);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hit_buf.q + 4, &g_tether_l24_hit_headers[k].p[j1 - 1], g_tether_l24_origin_vec);
                kf = math_random_float_range(0.17453295f, 0.9599312f) * ks;
                ks = -ks;
                math_apply_axis_rotation_to_quat(scratch, scratch, hit_buf.q + 4, kf);
                FastVecAdd(g_tether_l24_hit_nodes[k].v + j1, &g_tether_l24_hit_headers[k].p[j1 - 1], scratch);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter[j2];
                FastVecSub(q, g_tether_l24_hit_nodes[k].v + j2, &g_tether_l24_hit_headers[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_tether_l24_hit_nodes[k].v[0], hit_buf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(g_tether_l24_hit_nodes[k].v + j2, &g_tether_l24_hit_headers[k].p[j2 - 1], jitter[j2]);
            {
                int x = g_tether_l24_segment_offsets[k];
                int y = g_tether_l24_segment_timers[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                kf = IntToFloat(x);
                kf = kf / IntToFloat(0xF);
            }
            {
                fade = FloatToInt((1.0f - kf) * 32.0f);
                g_tether_l24_segment_fades[k] = fade;
            }
        }
    }
    {
        angle0 = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle1 = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(scratch, aim_dir, g_tether_l24_dir_scale);
        math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors, angle1);
        math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors + 0x10, angle0);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(rope, 0xF, tsize * 0.3f, tsize, g_tether_l24_glow_color | 0x7F000000, 0, spin, scratch, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(rope, 0xF, tsize * 0.15f, tsize * 0.5f, 0x307F7F7F, 0, spin, scratch, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        tsize = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(rope->b, 0xC, tsize * 0.1f, tsize, g_tether_l24_glow_color | 0x7F000000, 0, spin, g_ground_l24_effect_vec, 1, 0.0f);
    }
}
