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
extern Slot g_item_l26_materials[];
extern Cam g_hero_state;
extern char g_tether_axis_vectors[];
extern int g_hero_tether_enabled;
extern float g_str_ground_effect_name[] MACRO_ADDR;
extern int g_lock_l26_on_tether_timer;
extern short g_lock_l26_on_tether_respawn_timers[] MACRO_ADDR;
extern short g_lock_l26_on_tether_fades[] MACRO_ADDR;
extern short g_lock_l26_on_tether_timer_starts[] MACRO_ADDR;
extern short g_lock_l26_on_tether_x_offsets[] MACRO_ADDR;
extern float g_hero_l26_state[];
extern char g_hero_l26_origin[];
/* The collision query's result: what the segment hit, and where. */
typedef struct HitResult {
    Tgt *hit;                           /* 0x0 */
    int pad;
    float pos[4];                       /* 0x8 */
} HitResult;
extern HitResult g_tether_l26_hit_result;
extern Tgt *g_target_l26_list[];
extern float g_tether_l26_segment_starts[][4], g_tether_l26_link_offsets[][4];
extern Vec g_tether_l26_rope_points[2][20];
extern V4 g_tether_l26_anchor_vec;
extern float g_tether_l26_prev_heights[];
extern Vec g_tether_l26_node_offsets[];
extern float g_tether_l26_height_offsets[];
typedef struct { V4 v[5]; } Node5;
typedef struct { V4 hdr; V4 p[4]; } Hdr5;
extern Hdr5 g_tether_l26_segment_headers[];
extern Node5 g_tether_l26_nodes[];

extern float g_tether_l26_max_reach __attribute__((sda));
extern float g_tether_l26_second_angle_limit __attribute__((sda));
extern float g_tether_l26_angle_limit __attribute__((sda));
extern float g_tether_l26_wave_spacing_a __attribute__((sda));
extern float g_tether_l26_wave_amp_start __attribute__((sda));
extern float g_tether_l26_wave_amp_end __attribute__((sda));
extern float g_tether_l26_wave_phase_a __attribute__((sda));
extern float g_tether_l26_wave_speed_a __attribute__((sda));
extern float g_tether_l26_swirl_phase __attribute__((sda));
extern float g_tether_l26_swirl_speed __attribute__((sda));
extern float g_tether_l26_swirl_spacing __attribute__((sda));
extern float g_tether_wave_amp_b __attribute__((sda));
extern float g_tether_l26_radial_scale __attribute__((sda));
extern float g_tether_l26_wave_phase_b __attribute__((sda));
extern float g_tether_l26_wave_speed_b __attribute__((sda));
extern float g_tether_l26_wave_spacing_b __attribute__((sda));
extern float g_tether_l26_jitter_min __attribute__((sda));
extern float g_tether_l26_jitter_max __attribute__((sda));
extern float g_tether_l26_dir_scale __attribute__((sda));
extern float g_tether_l26_angle_score_weight __attribute__((sda));
extern int g_tether_l26_effect_color __attribute__((sda));

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

/* Updates the lock-on tether (PAL): picks up to two lock targets, lays out the twenty rope points with their waves, hit tests them, and spawns sparks and glows. */
void hero_l26_update_lock_on_tether_pal(Moby *self)
{
    int locked = g_item_l26_materials[g_item_slot_to_record.cur].on != 0;
    float reach = g_tether_l26_max_reach * 0.05f;
    Rope *rope = self->rope;
    float first_pos[4] __attribute__((aligned(16)));
    float vec_a[4] __attribute__((aligned(16)));
    float vec_b[4] __attribute__((aligned(16)));
    Hit hit_desc __attribute__((aligned(16)));
    float tether_dir[4] __attribute__((aligned(16)));
    float side_vec[4] __attribute__((aligned(16)));
    float pull_vec[4] __attribute__((aligned(16)));
    float segment_vec[4] __attribute__((aligned(16)));
    float sway_vec[4] __attribute__((aligned(16)));
    Tgt *held[128];
    float work_vec[4] __attribute__((aligned(16)));
    union {
        float q[16];
        struct { Hit r; } b;
        struct { float pad[4]; Hit r; } a;
    } hit_buf __attribute__((aligned(16)));
    float jitter[5][4] __attribute__((aligned(16)));
    Tgt *best = 0, *second = 0;
    int hit_found, held_count;
    float best_score = 0.0f, second_score = 0.0f;
    float first_len;
    float angle_a, angle_b;
    int held_index;
    Tgt *candidate;
    int candidate_index;
    float dist, aim_angle, view_angle, dot_right, side_len, score, proj, angle_score, dist_score;
    float first_dist;
    float *grab_info_a, *grab_info_b;
    Tgt *target_a, *target_b;
    float length, blend;
    float amp, height, angle, old_height, divisor;
    int mirror_index;
    Tgt *hit_target;
    float *hit_info;
    float *temp_ptr, proj_a, *hit_info_a;
    int hit_value_a;
    float proj_b, *hit_info_b;
    int hit_value_b;
    float spark_size, spark_angle, spark_sign;
    int node_a, node_b;
    float *delta;
    int spin;
    float glow_size, divisor_b;
    Vec *prev_point;
    float proj_right, vec_len;
    /* Declared here, not in its block: k's pseudo number sets the bucket of k + 1 in the
       gcse hash, which orders the spill slots at 0x394 and 0x398. */
    short fade;
    int k;

    g_tether_l26_wave_phase_a = FastAddRotations(g_tether_l26_wave_phase_a, g_tether_l26_wave_speed_a);
    g_tether_l26_swirl_phase = fast_subtract_rotations(g_tether_l26_swirl_phase, g_tether_l26_swirl_speed);
    g_tether_l26_wave_phase_b = FastAddRotations(g_tether_l26_wave_phase_b, g_tether_l26_wave_speed_b);

    if (rope->lockA == 0 || (locked && rope->lockB == 0)) {
        if (rope->lockB != 0) {
            rope->lockA = rope->lockB;
            rope->u.s.h40 = rope->u.s.h42;
            rope->lockB = 0;
            rope->u.s.h42 = 0;
        } else {
            candidate_index = 0;
            for (candidate = g_target_l26_list[0]; candidate != 0; candidate = g_target_l26_list[++candidate_index]) {
                if (candidate != rope->lockA && candidate != rope->lockB) {
                    if (candidate != 0 && candidate->cls != 0 && candidate->cls->id == 5) {
                        if (candidate->kind != 0xFE) {
                        if (candidate->kind != 0xFD) {
                            if (moby_get_private_value_0(candidate) != 0) {
                                FastVecSub(first_pos, candidate->pos, rope);
                                if (g_hero_tether_enabled != 0) {
                                    proj = FastVecDot(first_pos, g_hero_state.ent + 0xE0);
                                    FastVecScale(vec_a, g_hero_state.ent + 0xE0, proj);
                                    FastVecSub(vec_b, first_pos, vec_a);
                                    dist = FastVecLength(vec_b);
                                } else {
                                    dist = vec_length_xy(first_pos);
                                }
                                if (!(g_tether_l26_max_reach < dist)) {
                                    aim_angle = FastDiffRots(g_hero_l26_state[0x158 / 4], mat_fast_helper_a(candidate->pos[0] - g_hero_l26_state[0x140 / 4], candidate->pos[1] - g_hero_l26_state[0x144 / 4]));
                                    if (!(g_tether_l26_angle_limit < aim_angle)) {
                                        /* Dead on every path, but retail keeps it: the zero is reused by the
                                           `side_len` test below ($f21, c.eq.s). */
                                        view_angle = 0.0f;
                                        if (g_hero_tether_enabled != 0) {
                                            FastVecSub(vec_a, candidate->pos, &g_hero_state.x);
                                            proj_right = FastVecDot(vec_a, g_hero_state.ent + 0xE0);
                                            FastVecScale(vec_b, g_hero_state.ent + 0xE0, proj_right);
                                            FastVecSub(vec_a, vec_a, vec_b);
                                            dot_right = FastVecDot(vec_a, g_hero_state.ent + 0xC0);
                                            side_len = FastVecLength(vec_a);
                                            if (side_len == 0.0f)
                                                continue;
                                            view_angle = 1.5707964f - math_fast_angle_helper(dot_right / side_len);
                                        } else {
                                            view_angle = FastDiffRots(mat_fast_helper_a(candidate->pos[0] - g_hero_state.x, candidate->pos[1] - g_hero_state.y), g_hero_state.f98);
                                        }
                                            if (!(g_tether_l26_second_angle_limit < view_angle)) {
                                                angle_score = (g_tether_l26_angle_limit - aim_angle) / g_tether_l26_angle_limit;
                                                dist_score = (g_tether_l26_max_reach - dist) / g_tether_l26_max_reach;
                                                score = angle_score * g_tether_l26_angle_score_weight + dist_score;
                                                if (best_score < score) {
                                                    second_score = best_score;
                                                    best_score = score;
                                                    second = best;
                                                    best = candidate;
                                                } else if (second_score < score) {
                                                    second = candidate;
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
        if (rope->lockA != 0) {
            second = best;
        } else {
            rope->lockA = best;
            rope->u.s.h40 = 0;
            if (math_fast_float_d(&g_lock_l26_on_tether_timer) != 0)
                g_lock_l26_on_tether_timer = 8;
        }
    }
    if (second != 0 && locked) {
        first_dist = fast_vec_dist(rope, best->pos);
        if (first_dist < g_tether_l26_max_reach && first_dist + fast_vec_dist(best->pos, second->pos) < g_tether_l26_max_reach) {
            rope->u.s.h42 = 0;
            rope->lockB = second;
        }
    }
    first_len = 0.0f;
    if (rope->lockA != 0) {
        grab_info_a = moby_get_private_value_0(rope->lockA);
        target_a = rope->lockA;
        qcopy(first_pos, target_a->pos);
        FastVecScale(vec_a, (char *)target_a + 0xE0, grab_info_a[4]);
        FastVecAdd(first_pos, first_pos, vec_a);
        first_len = fast_vec_dist(rope, first_pos);
        reach = first_len * 0.05f;
    }
    if (rope->lockB != 0) {
        grab_info_b = moby_get_private_value_0(rope->lockB);
        target_b = rope->lockB;
        qcopy(vec_a, target_b->pos);
        FastVecScale(vec_b, (char *)target_b + 0xE0, grab_info_b[4]);
        FastVecAdd(vec_a, vec_a, vec_b);
        reach = (fast_vec_dist(first_pos, vec_a) + first_len) * 0.05f;
    }
    if (locked)
        g_tether_l26_effect_color = 0x207F20;
    else
        g_tether_l26_effect_color = 0x7F2020;
    vec_clear_128(vec_b);
    make_hit_descriptor(&hit_desc, self, 0x210000, vec_b, (&g_item_l26_materials[g_item_slot_to_record.cur])->f70);
    hit_desc.kind = 5;
    hit_desc.flag = 1;
    hit_desc.tag = self->tag;
    rope->count = 0x14;
    coll_process_hit(rope, 0x10, g_hero_state.ent, &hit_desc, 0.3f);
    FastVecSub(tether_dir, rope->b, rope);
    vec_scale_to_length(tether_dir, tether_dir, 1.0f);
    if (rope->lockA != 0 || rope->lockB != 0) {
        FastVecCross(side_vec, tether_dir, (char *)&g_hero_state + 0x2C0);
        math_apply_axis_rotation_to_quat(tether_dir, tether_dir, side_vec, 0.17453295f);
    }
    hit_found = 0;
    FastVecScale(segment_vec, tether_dir, reach);
    held_count = 0;
    /* These named pointers, and the short locals below, are live but also steer: each adds
       insns that exist at gcse and die later (asm operands keep the copy; the sign extension
       dies at combine). gcse's hash needs 677 buckets, max_cuid >= 1352, for retail's spill
       slots. See F4 in docs/contributing/matching-blockers.md. */
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l26_rope_points[0][0], anchor);
    }
    {
        float *anchor = rope->a;
        qcopy(&g_tether_l26_rope_points[1][0], anchor);
    }
    {
    int i;
    for (i = 1; i < 20; i++) {
        amp = g_tether_l26_wave_amp_start + (g_tether_l26_wave_amp_end - g_tether_l26_wave_amp_start) * (IntToFloat(i) * 0.05f);
        height = amp * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l26_wave_phase_a + (float)i * g_tether_l26_wave_spacing_a));
        height += math_random_signed_float_range(g_tether_l26_jitter_min, g_tether_l26_jitter_max);
        old_height = g_tether_l26_prev_heights[i];
        g_tether_l26_prev_heights[i] = height;
        g_tether_l26_rope_points[0][i].f[2] = g_tether_l26_rope_points[0][i].f[2] - old_height;
        vec_transform_or_copy(&g_tether_l26_rope_points[0][i], &g_tether_l26_rope_points[0][i]);
        FastVecSub(side_vec, &g_tether_l26_rope_points[0][i], g_tether_l26_link_offsets[i]);
        lerp_vector(pull_vec, side_vec, segment_vec, 0.85f);
        {
            float vec_len2 = FastVecLength(pull_vec);
            if (vec_len2 == 0.0f) {
                prev_point = &g_tether_l26_rope_points[0][i - 1];
                qcopy(&g_tether_l26_rope_points[0][i], prev_point);
            } else {
                FastVecScale(pull_vec, pull_vec, reach / vec_len2);
                FastVecAdd(&g_tether_l26_rope_points[0][i], g_tether_l26_link_offsets[i], pull_vec);
                qcopy(segment_vec, pull_vec);
            }
        }
        g_tether_l26_rope_points[0][i].f[2] = g_tether_l26_rope_points[0][i].f[2] + height;
        FastVecSub(side_vec, &g_tether_l26_rope_points[0][i], g_tether_l26_link_offsets[i]);
        if (rope->lockA != 0) {
            if (!locked || rope->lockB == 0) {
                FastVecSub(work_vec, first_pos, &g_tether_l26_rope_points[0][i]);
                length = FastVecLength(work_vec);
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
                    FastVecScale(work_vec, work_vec, reach / length);
                    lerp_vector(segment_vec, segment_vec, work_vec, blend);
                }
            } else {
                if (i >= 10)
                    FastVecSub(work_vec, vec_a, &g_tether_l26_rope_points[0][i]);
                else
                    FastVecSub(work_vec, first_pos, &g_tether_l26_rope_points[0][i]);
                length = FastVecLength(work_vec);
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
                        divisor_b = IntToFloat(0x13 - i);
                        reach = length / divisor_b;
                    } else {
                        blend = 0.2f;
                    }
                    FastVecScale(work_vec, work_vec, reach / length);
                    lerp_vector(segment_vec, segment_vec, work_vec, blend);
                }
            }
        }
        if (i < 10) {
            angle = math_wrap_angle_to_pi(g_tether_l26_swirl_phase + (float)i * g_tether_l26_swirl_spacing);
            amp = g_tether_wave_amp_b * math_fast_sin_or_cos_b(math_wrap_angle_to_pi(g_tether_l26_wave_phase_b + (float)i * g_tether_l26_wave_spacing_b));
            qcopy(&g_tether_l26_rope_points[1][i], &g_tether_l26_rope_points[0][i]);
            height = amp * math_fast_sin_or_cos_b(angle) + math_random_signed_float_range(0.0f, 0.1f);
            g_tether_l26_height_offsets[i] = height;
            g_tether_l26_rope_points[1][i].f[2] = g_tether_l26_rope_points[1][i].f[2] + height;
            {
                float bearing = FastAddRotations(mat_fast_helper_a(side_vec[0], side_vec[1]), 1.5707965f);
                {
                    float radial = g_tether_l26_radial_scale * math_fast_sin_or_cos_a(angle);
                    sway_vec[0] = math_fast_sin_or_cos_a(bearing) * radial;
                    sway_vec[1] = math_fast_sin_or_cos_b(bearing) * radial;
                    sway_vec[2] = 0.0f;
                    qcopy_nc(&g_tether_l26_node_offsets[i], sway_vec);
                }
            }
            FastVecAdd(&g_tether_l26_rope_points[1][i], &g_tether_l26_rope_points[1][i], sway_vec);
        } else {
            mirror_index = 0x15 - i;
            qcopy(&g_tether_l26_rope_points[1][i], &g_tether_l26_rope_points[0][i]);
            g_tether_l26_rope_points[1][i].f[2] = g_tether_l26_rope_points[1][i].f[2] + g_tether_l26_height_offsets[mirror_index];
            FastVecAdd(&g_tether_l26_rope_points[1][i], &g_tether_l26_rope_points[1][i], &g_tether_l26_node_offsets[mirror_index]);
            qcopy(sway_vec, &g_tether_l26_node_offsets[i]);
        }
        if (i >= 2 && (i == 0x13 || !(i & 1))) {
            FastVecSub(vec_b, &g_tether_l26_rope_points[0][i], g_hero_l26_origin);
            if (g_hero_tether_enabled != 0) {
                float proj_c = FastVecDot(vec_b, g_hero_state.ent + 0xE0);
                {
                    char *axis = g_hero_state.ent + 0xE0;
                    FastVecScale(work_vec, axis, proj_c);
                    FastVecSub(vec_b, vec_b, work_vec);
                }
            } else {
                *(int *)&vec_b[2] = 0;
            }
            vec_len = FastVecLength(vec_b);
            if (vec_len == 0.0f)
                vec_b[2] = 1.0f;
            else
                FastVecScale(vec_b, vec_b, 1.0f / vec_len);
            vec_b[3] = 5627.925f;
            qcopy(&hit_desc, vec_b);
            hit_found = CollLine(g_tether_l26_segment_starts[i], &g_tether_l26_rope_points[0][i], 0x10, self, 0);
            if (hit_found != 0) {
                hit_target = g_tether_l26_hit_result.hit;
                if (hit_target != 0) {
                    hit_info = moby_get_private_value_0(hit_target);
                    if (hit_info == 0) {
                        QueueMobyImpact(hit_target, &hit_desc);
                    } else if (hit_target->cls == 0 || hit_target->cls->id != 5) {
                        QueueMobyImpact(hit_target, &hit_desc);
                    } else {
                        hit_found = 0;
                        held[held_count++] = hit_target;
                        hit_target->f98 = 0;
                    }
                }
                if (hit_found != 0) {
                    qcopy(&g_tether_l26_rope_points[0][i], g_tether_l26_hit_result.pos);
                    {
                        short last = i;
                        rope->count = last;
                    }
                    qcopy(rope->b, g_tether_l26_hit_result.pos);
                    if (g_tether_l26_hit_result.hit == 0) {
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
    if (hit_found == 0)
        qcopy(rope->b, &g_tether_l26_anchor_vec);
    if (rope->lockA != 0 && (rope->u.q & 0x0000FFFF0000FFFFUL) == 0) {
        temp_ptr = hit_buf.q;
        FastVecSub(work_vec, rope->lockA->pos, g_hero_l26_origin);
        if (g_hero_tether_enabled != 0) {
            proj_a = FastVecDot(work_vec, g_hero_state.ent + 0xE0);
            FastVecScale(temp_ptr, g_hero_state.ent + 0xE0, proj_a);
            FastVecSub(work_vec, work_vec, temp_ptr);
        } else {
            *(int *)&work_vec[2] = 0;
        }
        vec_scale_to_length(work_vec, work_vec, 1.0f);
        work_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.a.r, self, 0x210000, work_vec, (&g_item_l26_materials[g_item_slot_to_record.cur])->f70);
        hit_buf.a.r.kind = 5;
        hit_buf.a.r.flag = 3;
        hit_buf.a.r.tag = self->tag;
        hit_value_a = 5;
        QueueMobyImpact(rope->lockA, &hit_buf.a.r);
        hit_info_a = moby_get_private_value_0(rope->lockA);
        if (hit_info_a != 0) {
            if (((short *)hit_info_a)[2] == 1)
                hit_value_a = 1;
        }
        {
            short result = ((s32)(hit_value_a) * 5 + 2) / 6;
            rope->u.s.h44 = result;
        }
    }
    if (rope->lockB != 0 && (rope->u.q & 0xFFFF0000FFFF0000UL) == 0) {
        FastVecSub(work_vec, rope->lockB->pos, g_hero_l26_origin);
        if (g_hero_tether_enabled != 0) {
            proj_b = FastVecDot(work_vec, g_hero_state.ent + 0xE0);
            FastVecScale(hit_buf.q, g_hero_state.ent + 0xE0, proj_b);
            FastVecSub(work_vec, work_vec, hit_buf.q);
        } else {
            *(int *)&work_vec[2] = 0;
        }
        vec_scale_to_length(work_vec, work_vec, 1.0f);
        work_vec[3] = 5627.925f;
        make_hit_descriptor(&hit_buf.b.r, self, 0x210000, work_vec, (&g_item_l26_materials[g_item_slot_to_record.cur])->f70);
        hit_buf.b.r.kind = 5;
        hit_buf.b.r.flag = 3;
        hit_buf.b.r.tag = self->tag;
        hit_value_b = 5;
        QueueMobyImpact(rope->lockB, &hit_buf.b.r);
        hit_info_b = moby_get_private_value_0(rope->lockB);
        if (hit_info_b != 0) {
            if (((short *)hit_info_b)[2] == 1)
                hit_value_b = 1;
        }
        {
            short result = ((s32)(hit_value_b) * 5 + 2) / 6;
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
        if (FastDecTimer(&g_lock_l26_on_tether_respawn_timers[k]) != 0) {
            g_lock_l26_on_tether_respawn_timers[k] = ((s32)g_lock_l26_on_tether_timer_starts[k] * 5 + 2) / 6;
            g_lock_l26_on_tether_fades[k] = 0;
            angle_a = math_random_signed_float_range(0.52359885f, 1.0471977f);
            angle_b = math_random_float_range(-1.0471977f, 0.17453295f);
            FastVecScale(work_vec, tether_dir, spark_size);
            math_apply_axis_rotation_to_quat(work_vec, work_vec, g_tether_axis_vectors, angle_b);
            math_apply_axis_rotation_to_quat(work_vec, work_vec, g_tether_axis_vectors + 0x10, angle_a);
            qcopy(&g_tether_l26_nodes[k].v[0], hit_buf.q);
            spark_sign = 1.0f;
            FastVecAdd(&g_tether_l26_nodes[k].v[1], hit_buf.q, work_vec);
            for (node_a = 2; node_a < 5; node_a++) {
                FastVecSub(hit_buf.q + 4, &g_tether_l26_segment_headers[k].p[node_a - 1], g_hero_l26_origin);
                spark_angle = math_random_float_range(0.17453295f, 0.9599312f) * spark_sign;
                spark_sign = -spark_sign;
                math_apply_axis_rotation_to_quat(work_vec, work_vec, hit_buf.q + 4, spark_angle);
                FastVecAdd(g_tether_l26_nodes[k].v + node_a, &g_tether_l26_segment_headers[k].p[node_a - 1], work_vec);
            }
        } else {
            for (node_b = 1; node_b < 5; node_b++) {
                delta = jitter[node_b];
                FastVecSub(delta, g_tether_l26_nodes[k].v + node_b, &g_tether_l26_segment_headers[k].p[node_b - 1]);
                delta[0] = delta[0] + math_random_signed_float_range(0.0f, 0.1f);
                delta[1] = delta[1] + math_random_signed_float_range(0.0f, 0.1f);
                delta[2] = delta[2] + math_random_signed_float_range(0.0f, 0.1f);
            }
            qcopy(&g_tether_l26_nodes[k].v[0], hit_buf.q);
            for (node_b = 1; node_b < 5; node_b++)
                FastVecAdd(g_tether_l26_nodes[k].v + node_b, &g_tether_l26_segment_headers[k].p[node_b - 1], jitter[node_b]);
            {
                int seg_offset = g_lock_l26_on_tether_x_offsets[k];
                int seg_timer = g_lock_l26_on_tether_respawn_timers[k];
                if (seg_offset < seg_timer)
                    seg_offset = seg_timer - seg_offset;
                else
                    seg_offset = seg_offset - seg_timer;
                spark_angle = IntToFloat(seg_offset);
                spark_angle = spark_angle / IntToFloat(0xC);
            }
            {
                fade = FloatToInt((1.0f - spark_angle) * 32.0f);
                g_lock_l26_on_tether_fades[k] = fade;
            }
        }
    }
    {
        angle_a = math_random_signed_float_range(0.52359885f, 1.0471977f);
        angle_b = math_random_float_range(-0.52359885f, 1.0471977f);
        FastVecScale(work_vec, tether_dir, g_tether_l26_dir_scale * 1.2f);
        math_apply_axis_rotation_to_quat(work_vec, work_vec, g_tether_axis_vectors, angle_b);
        math_apply_axis_rotation_to_quat(work_vec, work_vec, g_tether_axis_vectors + 0x10, angle_a);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        glow_size = math_random_float_range(0.2f, 0.6f);
        part_spawn_ground_effect(rope, 0xC, glow_size * 0.3f, glow_size, g_tether_l26_effect_color | 0x7F000000, 0, spin, work_vec, 1, 0.0f);
        spin = -spin;
        part_spawn_ground_effect(rope, 0xC, glow_size * 0.15f, glow_size * 0.5f, 0x307F7F7F, 0, spin, work_vec, 1, 0.0f);
        spin = math_random_int_range(1, 8);
        if (math_random_int_below(2) != 0)
            spin = -spin;
        glow_size = math_random_float_range(0.15f, 3.0f);
        part_spawn_ground_effect(rope->b, 0xA, glow_size * 0.1f, glow_size, g_tether_l26_effect_color | 0x7F000000, 0, spin, g_str_ground_effect_name, 1, 0.0f);
    }
}
