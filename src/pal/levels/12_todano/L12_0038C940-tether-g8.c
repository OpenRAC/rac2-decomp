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
extern Slot g_item_l12_material_table[];
extern Cam g_hero_state;
extern char g_tether_axis_vectors[];
extern int g_hero_l12_lock_flag;
extern float g_zero_l12_vec[] MACRO_ADDR;
extern int g_tether_l12_timer;
extern short g_tether_l12_segment_timers[] MACRO_ADDR;
extern short g_tether_l12_segment_fades[] MACRO_ADDR;
extern short g_tether_segment_timer_reset[] MACRO_ADDR;
extern short g_tether_l12_segment_x_offsets[] MACRO_ADDR;
extern float g_hero_state_copy_a[];
extern char g_hero_prev_position[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult g_hit_l12_result;
extern Tgt *g_aim_target_list[];
extern float g_tether_l12_start_points[][4], g_tether_l12_offsets[][4];
extern Vec g_tether_l12_rope_points[2][20];
extern V4 g_tether_l12_end_point;
extern float g_tether_l12_point_heights[];
extern Vec g_tether_point_velocities[];
extern float g_tether_l12_height_offsets[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 g_tether_l12_hit_headers[];
extern Node5 g_tether_l12_nodes[];

extern float g_tether_reach_range __attribute__((sda));
extern float g_tether_max_side_angle __attribute__((sda));
extern float g_tether_l12_max_angle __attribute__((sda));
extern float g_tether_l12_wave_spacing __attribute__((sda));
extern float g_tether_l12_amp_start __attribute__((sda));
extern float g_tether_l12_amp_end __attribute__((sda));
extern float g_tether_l12_wave_phase __attribute__((sda));
extern float g_tether_l12_wave_speed __attribute__((sda));
extern float g_tether_l12_swirl_phase __attribute__((sda));
extern float g_tether_l12_swirl_speed __attribute__((sda));
extern float g_tether_l12_swirl_spacing __attribute__((sda));
extern float g_tether_l12_amp_scale __attribute__((sda));
extern float g_tether_l12_radial_scale __attribute__((sda));
extern float g_tether_l12_amp_phase __attribute__((sda));
extern float g_tether_l12_amp_phase_speed __attribute__((sda));
extern float g_tether_l12_amp_phase_spacing __attribute__((sda));
extern float g_tether_l12_jitter_min __attribute__((sda));
extern float g_tether_l12_jitter_max __attribute__((sda));
extern float g_tether_l12_vec_scale __attribute__((sda));
extern float g_tether_l12_score_weight __attribute__((sda));
extern int g_tether_l12_color __attribute__((sda));

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

/* Updates the lock-on tether each frame: picks up to two locked targets, bends the twenty rope points toward them, collides the rope and queues hits on the targets, and spawns the glow spots and sparks (PAL: 50 Hz timers). */
void lock_on_tether_update_todano_pal(Moby *self)
{
    int locked = g_item_l12_material_table[g_item_slot_to_record.cur].on != 0;
    float reach = g_tether_reach_range * 0.05f;
    Rope *rope = self->rope;
    float lock_a_point[4] __attribute__((aligned(16)));
    float tmp_a[4] __attribute__((aligned(16)));
    float tmp_b[4] __attribute__((aligned(16)));
    Hit hit1 __attribute__((aligned(16)));
    float rope_dir[4] __attribute__((aligned(16)));
    float seg_delta[4] __attribute__((aligned(16)));
    float seg_step[4] __attribute__((aligned(16)));
    float steer[4] __attribute__((aligned(16)));
    float swirl_offset[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float scratch[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buf __attribute__((aligned(16)));
    float jitter_points[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hit_found, held_count;
    float best_score = 0.0f, second_score = 0.0f;
    float len;
    float angle_yaw, angle_pitch;
    int n;
    Tgt *target;
    int scan_index;
    float lock_dist, heading_diff, side_angle, side_cos, side_len, lock_score, axis_proj, angle_factor, reach_factor;
    float dist_best;
    float *info_a, *info_b;
    Tgt *target_a, *target_b;
    float length, blend;
    float amp, height, angle, old, countdown;
    int mirror_index;
    Tgt *hit_target;
    float *hit_info;
    float *axis_buf, axis_proj_a, *impact_info_a;
    int damage_a;
    float axis_proj_b, *impact_info_b;
    int damage_b;
    float spark_size, spark_angle, spark_sign;
    int j1, j2;
    float *q;
    int spin;
    float glow_size, countdown_b;
    Vec *prev_point;
    float axis_proj2, hit_dir_len;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    g_tether_l12_wave_phase = FastAddRotations(g_tether_l12_wave_phase, g_tether_l12_wave_speed);
    g_tether_l12_swirl_phase = fast_subtract_rotations(g_tether_l12_swirl_phase, g_tether_l12_swirl_speed);
    g_tether_l12_amp_phase = FastAddRotations(g_tether_l12_amp_phase, g_tether_l12_amp_phase_speed);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            scan_index = 0;
            for (target = g_aim_target_list[0]; target != 0; target = g_aim_target_list[++scan_index]) {
                if (target != rope->lockA && target != rope->lockB) {
                    if (target != 0 && target->cls != 0 && target->cls->id == 5) {
                        if (target->kind != 0xFE) {
                        if (target->kind != 0xFD) {
                            if (moby_get_private_value_0(target) != 0) {
                                FastVecSub(lock_a_point, target->pos, rope);
                                if (g_hero_l12_lock_flag != 0) {
                                    axis_proj = FastVecDot(lock_a_point, g_hero_state.ent + 0xE0);
                                    FastVecScale(tmp_a, g_hero_state.ent + 0xE0, axis_proj);
                                    FastVecSub(tmp_b, lock_a_point, tmp_a);
                                    lock_dist = FastVecLength(tmp_b);
                                } else {
                                    lock_dist = vec_length_xy(lock_a_point);
                                }
                                if (!(g_tether_reach_range < lock_dist)) {
                                    heading_diff = FastDiffRots(g_hero_state_copy_a[0x158 / 4], mat_fast_helper_a(target->pos[0] - g_hero_state_copy_a[0x140 / 4], target->pos[1] - g_hero_state_copy_a[0x144 / 4]));
                                    if (!(g_tether_l12_max_angle < heading_diff)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `side_len` test below ($f21, c.eq.s). */
                                        side_angle = 0.0f;
                                        if (g_hero_l12_lock_flag != 0) {
                                            FastVecSub(tmp_a, target->pos, &g_hero_state.x);
                                            axis_proj2 = FastVecDot(tmp_a, g_hero_state.ent + 0xE0);
                                            FastVecScale(tmp_b, g_hero_state.ent + 0xE0, axis_proj2);
                                            FastVecSub(tmp_a, tmp_a, tmp_b);
                                            side_cos = FastVecDot(tmp_a, g_hero_state.ent + 0xC0);
                                            side_len = FastVecLength(tmp_a);
                                            if (side_len == 0.0f)
                                                continue;
                                            side_angle = 1.5707964f - math_fast_angle_helper(side_cos / side_len);
                                        } else {
                                            side_angle = FastDiffRots(mat_fast_helper_a(target->pos[0] - g_hero_state.x, target->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(g_tether_max_side_angle < side_angle)) {
                                                angle_factor = (g_tether_l12_max_angle - heading_diff) / g_tether_l12_max_angle;
                                                reach_factor = (g_tether_reach_range - lock_dist) / g_tether_reach_range;
                                                lock_score = angle_factor * g_tether_l12_score_weight + reach_factor;
                                                if (best_score < lock_score) {
                                                    second_score = best_score;
                                                    best_score = lock_score;
                                                    second = best;
                                                    best = target;
                                                } else if (second_score < lock_score) {
                                                    second = target;
                                                    second_score = lock_score;
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
            if (math_fast_float_d(&g_tether_l12_timer) != 0)
                g_tether_l12_timer = 8;
        }
    }
    if (second != 0 && locked) {
        dist_best = fast_vec_dist(rope, best->pos);
        if (dist_best < g_tether_reach_range && dist_best + fast_vec_dist(best->pos, second->pos) < g_tether_reach_range) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    len = 0.0f;
    if (rope->lockA != 0) {
        info_a = moby_get_private_value_0(rope->lockA);
        target_a = rope->lockA;
        qcopy(lock_a_point, target_a->pos);
        FastVecScale(tmp_a, (char *)target_a + 0xE0, info_a[4]);
        FastVecAdd(lock_a_point, lock_a_point, tmp_a);
        len = fast_vec_dist(rope, lock_a_point);
        reach = len * 0.05f;
    }
    if (rope->lockB != 0) {
        info_b = moby_get_private_value_0(rope->lockB);
        target_b = rope->lockB;
        qcopy(tmp_a, target_b->pos);
        FastVecScale(tmp_b, (char *)target_b + 0xE0, info_b[4]);
        FastVecAdd(tmp_a, tmp_a, tmp_b);
        reach = (fast_vec_dist(lock_a_point, tmp_a) + len) * 0.05f;
    }
    if (locked)
        g_tether_l12_color = 0x207F20;
    else
        g_tether_l12_color = 0x7F2020;
    vec_clear_128(tmp_b);
    make_hit_descriptor(&hit1, self, 0x210000, tmp_b, (&g_item_l12_material_table[g_item_slot_to_record.cur])->f70);
    hit1.kind = 5;
    hit1.flag = 1;
    hit1.tag = self->tag;
    rope->count = 0x14;
    coll_process_hit(rope, 0x10, g_hero_state.ent, &hit1, 0.3f);
    FastVecSub(rope_dir, rope->b, rope);
    vec_scale_to_length(rope_dir, rope_dir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(seg_delta, rope_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(rope_dir, rope_dir, seg_delta, 0.17453295f);
    }
    hit_found = 0;
    FastVecScale(steer, rope_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l12_rope_points[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l12_rope_points[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = g_tether_l12_amp_start + (g_tether_l12_amp_end - g_tether_l12_amp_start) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l12_wave_phase + (float)i * g_tether_l12_wave_spacing));
        height += math_random_signed_float_range(g_tether_l12_jitter_min, g_tether_l12_jitter_max);
        old = g_tether_l12_point_heights[i];
        g_tether_l12_point_heights[i] = height;
        g_tether_l12_rope_points[0][i].f[2] = g_tether_l12_rope_points[0][i].f[2] - old;
        vec_transform_or_copy(&g_tether_l12_rope_points[0][i], &g_tether_l12_rope_points[0][i]);
        FastVecSub(seg_delta, &g_tether_l12_rope_points[0][i], g_tether_l12_offsets[i]);
        lerp_vector(seg_step, seg_delta, steer, 0.85f);
        {
            float cm = FastVecLength(seg_step);
            if (cm == 0.0f) {
                prev_point = &g_tether_l12_rope_points[0][i - 1];
                qcopy(&g_tether_l12_rope_points[0][i], prev_point);
            } else {
                FastVecScale(seg_step, seg_step, reach / cm);
                FastVecAdd(&g_tether_l12_rope_points[0][i], g_tether_l12_offsets[i], seg_step);
                qcopy(steer, seg_step);
            }
        }
        g_tether_l12_rope_points[0][i].f[2] = g_tether_l12_rope_points[0][i].f[2] + height;
        FastVecSub(seg_delta, &g_tether_l12_rope_points[0][i], g_tether_l12_offsets[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(scratch, lock_a_point, &g_tether_l12_rope_points[0][i]);
                length = FastVecLength(scratch);
                if (length != 0.0f) {
                    if (i == 0x13) {
                        blend = 0.5f;
                        reach = length;
                    } else if (i >= 0x10) {
                        blend = 0.5f;
                        countdown = IntToFloat(0x13 - i);
                        reach = length / countdown;
                    } else {
                        blend = 0.1f;
                    }
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(steer, steer, scratch, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(scratch, tmp_a, &g_tether_l12_rope_points[0][i]);
                else
                    FastVecSub(scratch, lock_a_point, &g_tether_l12_rope_points[0][i]);
                length = FastVecLength(scratch);
                if (length != 0.0f) {
                    if (i == 9 || i == 0x13) {
                        blend = 0.7f;
                        reach = length;
                    } else if (i >= 5 && i < 10) {
                        blend = 0.7f;
                        countdown = IntToFloat(9 - i);
                        reach = length / countdown;
                    } else if (i >= 0xF) {
                        blend = 0.7f;
                        countdown_b = IntToFloat(0x13 - i);
                        reach = length / countdown_b;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(scratch, scratch, reach / length);
                    lerp_vector(steer, steer, scratch, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(g_tether_l12_swirl_phase + (float)i * g_tether_l12_swirl_spacing);
            amp = g_tether_l12_amp_scale * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l12_amp_phase + (float)i * g_tether_l12_amp_phase_spacing));
            qcopy(&g_tether_l12_rope_points[1][i], &g_tether_l12_rope_points[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            g_tether_l12_height_offsets[i] = height;
            g_tether_l12_rope_points[1][i].f[2] = g_tether_l12_rope_points[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(seg_delta[0], seg_delta[1]), 1.5707965f);
                {
                    float radial = g_tether_l12_radial_scale * math_fast_sin_or_cos_a(angle);
                    swirl_offset[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    swirl_offset[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    swirl_offset[2] = 0.0f;
                    qcopy_nc(&g_tether_point_velocities[i], swirl_offset);
                }
            }
            FastVecAdd(&g_tether_l12_rope_points[1][i], &g_tether_l12_rope_points[1][i], swirl_offset);
        } else {
            mirror_index = 0x15 - i;
            qcopy(&g_tether_l12_rope_points[1][i], &g_tether_l12_rope_points[0][i]);
            g_tether_l12_rope_points[1][i].f[2] = g_tether_l12_rope_points[1][i].f[2] + g_tether_l12_height_offsets[mirror_index];
            FastVecAdd(&g_tether_l12_rope_points[1][i], &g_tether_l12_rope_points[1][i], &g_tether_point_velocities[mirror_index]);
            qcopy(swirl_offset, &g_tether_point_velocities[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(tmp_b, &g_tether_l12_rope_points[0][i], g_hero_prev_position);
            if (g_hero_l12_lock_flag != 0) {
                float cpj = FastVecDot(tmp_b, g_hero_state.ent + 0xE0);
                {
                    char *ax = g_hero_state.ent + 0xE0;
                    FastVecScale(scratch, ax, cpj);
                    FastVecSub(tmp_b, tmp_b, scratch);
                }
            } else {
                *(int *)&tmp_b[2] = 0;
            }
            hit_dir_len = FastVecLength(tmp_b);
            if (hit_dir_len == 0.0f)
                tmp_b[2] = 1.0f;
            else
                FastVecScale(tmp_b, tmp_b, 1.0f / hit_dir_len);
            tmp_b[3] = 5627.925f;
            qcopy(&hit1, tmp_b);
            hit_found = CollLine(g_tether_l12_start_points[i], &g_tether_l12_rope_points[0][i], 0x10, self, 0);
            if (hit_found != 0) {
                hit_target = g_hit_l12_result.hit;
                if (hit_target != 0) {
                    hit_info = moby_get_private_value_0(hit_target);
                    if (hit_info == 0) {
                        QueueMobyImpact(hit_target, &hit1);
                    } else if (hit_target->cls == 0 || hit_target->cls->id != 5) {
                        QueueMobyImpact(hit_target, &hit1);
                    } else {
                        hit_found = 0;
                        held[held_count++] = hit_target;
                        hit_target->f98 = 0;
                    }
                }
                if (hit_found != 0) {
                    qcopy(&g_tether_l12_rope_points[0][i], g_hit_l12_result.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, g_hit_l12_result.pos);
                    if (g_hit_l12_result.hit == 0) {
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
        held[n]->f98 = held[n]->cls->f10;
    if (hit_found == 0)
        qcopy(rope->b, &g_tether_l12_end_point);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        axis_buf = hit_buf.q;
        FastVecSub(scratch, rope->lockA->pos, g_hero_prev_position);
        if (g_hero_l12_lock_flag != 0) {
            axis_proj_a = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(axis_buf, g_hero_state.ent + 0xE0, axis_proj_a);
            FastVecSub(scratch, scratch, axis_buf);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.a.r, self, 0x210000, scratch, (&g_item_l12_material_table[g_item_slot_to_record.cur])->f70);
        hit_buf.a.r.kind = 5;
        hit_buf.a.r.flag = 3;
        hit_buf.a.r.tag = self->tag;
        damage_a = 5;
        QueueMobyImpact(rope->lockA, &hit_buf.a.r);
        impact_info_a = moby_get_private_value_0(rope->lockA);
        if (impact_info_a != 0) {
            if (((short *)impact_info_a)[2] == 1)
                damage_a = 1;
        }
        {
            short result = ((s32)(damage_a) * 5 + 2) / 6;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(scratch, rope->lockB->pos, g_hero_prev_position);
        if (g_hero_l12_lock_flag != 0) {
            axis_proj_b = FastVecDot(scratch, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buf.q, g_hero_state.ent + 0xE0, axis_proj_b);
            FastVecSub(scratch, scratch, hit_buf.q);
        } else {
            *(int *)&scratch[2] = 0;
        }
        vec_scale_to_length(scratch, scratch, 1.0f);
        scratch[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.b.r, self, 0x210000, scratch, (&g_item_l12_material_table[g_item_slot_to_record.cur])->f70);
        hit_buf.b.r.kind = 5;
        hit_buf.b.r.flag = 3;
        hit_buf.b.r.tag = self->tag;
        damage_b = 5;
        QueueMobyImpact(rope->lockB, &hit_buf.b.r);
        impact_info_b = moby_get_private_value_0(rope->lockB);
        if (impact_info_b != 0) {
            if (((short *)impact_info_b)[2] == 1)
                damage_b = 1;
        }
        {
            short result = ((s32)(damage_b) * 5 + 2) / 6;
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
        if (FastDecTimer(&g_tether_l12_segment_timers[k]) != 0) {
            g_tether_l12_segment_timers[k] = ((s32)g_tether_segment_timer_reset[k] * 5 + 2) / 6;
            g_tether_l12_segment_fades[k] = 0;
            angle_yaw = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle_pitch = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(scratch, rope_dir, spark_size);
            math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors, angle_pitch);
            math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors + 0x10, angle_yaw);
            qcopy(&g_tether_l12_nodes[k].v[0], hit_buf.q);
            spark_sign = 1.0f;
            FastVecAdd(&g_tether_l12_nodes[k].v[1], hit_buf.q, scratch);
            for (j1 = 2; j1 < 5; j1++) {
                FastVecSub(hit_buf.q + 4, &g_tether_l12_hit_headers[k].p[j1 - 1], g_hero_prev_position);
                spark_angle = math_random_float_range(0.17453295f, 0.9599312f) * spark_sign;
                spark_sign = -spark_sign;
                math_apply_axis_rotation_to_quat(scratch, scratch, hit_buf.q + 4, spark_angle);
                FastVecAdd(g_tether_l12_nodes[k].v + j1, &g_tether_l12_hit_headers[k].p[j1 - 1], scratch);
            }
        } else {
            for (j2 = 1; j2 < 5; j2++) {
                q = jitter_points[j2];
                FastVecSub(q, g_tether_l12_nodes[k].v + j2, &g_tether_l12_hit_headers[k].p[j2 - 1]);
                q[0] = q[0] + math_random_signed_float_range(0.0f, 0.1f);
                q[1] = q[1] + math_random_signed_float_range(0.0f, 0.1f);
                q[2] = q[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_tether_l12_nodes[k].v[0], hit_buf.q);
            for (j2 = 1; j2 < 5; j2++)
                FastVecAdd(g_tether_l12_nodes[k].v + j2, &g_tether_l12_hit_headers[k].p[j2 - 1], jitter_points[j2]);
            {
                int x = g_tether_l12_segment_x_offsets[k];
                int y = g_tether_l12_segment_timers[k];
                if (x < y)
                    x = y - x;
                else
                    x = x - y;
                spark_angle = IntToFloat(x);
                spark_angle = spark_angle / IntToFloat(0xC);
            }
            {
                fade = FloatToInt((1.0f - spark_angle) * 32.0f);
                g_tether_l12_segment_fades[k] = fade;
            }
        }
    }
    {
        angle_yaw = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle_pitch = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(scratch, rope_dir, g_tether_l12_vec_scale * 1.2f);
        math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors, angle_pitch);
        math_apply_axis_rotation_to_quat(scratch, scratch, g_tether_axis_vectors + 0x10, angle_yaw);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        glow_size = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(rope, 0xC, glow_size * 0.3f, glow_size, g_tether_l12_color | 0x7F000000, 0, spin, scratch, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(rope, 0xC, glow_size * 0.15f, glow_size * 0.5f, 0x307F7F7F, 0, spin, scratch, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        glow_size = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(rope->b, 0xA, glow_size * 0.1f, glow_size, g_tether_l12_color | 0x7F000000, 0, spin, g_zero_l12_vec, 1, 0.0f);
    }
}
