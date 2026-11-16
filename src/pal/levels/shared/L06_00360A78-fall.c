#include "include_asm.h"

#include "common.h"
typedef union { int hit_prev __attribute__((mode(TI))); float f[4]; } Vec4;
extern void part_spawn_sparks_around_moby_pal(void *, void *, void *);
extern float vec_length_xy(void *);
extern f32 ApproachValue(float *, float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float coll_probe_ground_height_below(void *, int, float);
extern int GetCollHitMaterial(void);
extern void *moby_spawn_scaled_effect(void *, float);
extern float coll_get_ground_height_under_object(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int math_solve_quadratic(float *, float *, float, float, float);
extern float MobySpringTurn(void *, void *, float, float, float, float);
extern int coll_process_hit(float, void *, int, void *, void *);
extern float IntToFloat(int);
extern int moby_is_in_special_class_range(void *);
extern void part_queue_impact_effect(void *, float, int, int, void *, void *);
extern float FastVecLength(void *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_test_point(void *, float, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern int *g_candidate_list[];
extern Vec4 g_trace_start_pos, g_trace_hit_info;

/* Adapted from OpenRAC/rac1-decomp (GPL-3.0),
 * src/overlays/shared/moby_ground_collision.c, mine_fall.
 * Applies gravity, friction and ground and wall collision to a falling moby and
 * returns its status flags. */
int mine_fall_pal(char *moby, char *fall) {
    float start_pos[4];
    float probe_pos[4];
    float new_pos[4];
    float target_pos[4];
    float hit_normal[4];
    float push_vec[4];
    float speed_xy, root1, root2, slide_speed;

    Vec4 *hit_info;
    char *hit_prev;
    int flags = 0;

    float grid_step, ground_height, fall_time, tmp_val, rate, unit_len;
    int hit_count, i;

    *(float *)(fall + 0x8) = *(float *)(fall + 0x8) - *(float *)(fall + 0x10);
    if (*(unsigned char *)(fall + 0x2E) == 1) {
        if (*(unsigned char *)(fall + 0x2F) != 0) {
            part_spawn_sparks_around_moby_pal(moby, fall, (void *)(int)*(unsigned char *)(fall + 0x2F));
        }
    }

    speed_xy = vec_length_xy(fall);
    tmp_val = (*(short *)(fall + 0x3E) == 2) ? 0.0f : *(float *)(fall + 0x4C);
    ApproachValue(&speed_xy, tmp_val, *(float *)(fall + 0x14));
    vec_fast_normalize_helper((float *)fall, (float *)fall, speed_xy);
    if (*(float *)(fall + 0x1C) < *(float *)(fall + 0x8)) {
        *(float *)(fall + 0x8) = *(float *)(fall + 0x1C);
    }

    qcopy(probe_pos, moby + 0x10);
    probe_pos[2] = probe_pos[2] + *(float *)(fall + 0x28);
    ground_height = coll_probe_ground_height_below(probe_pos, 0, 0.5f);
    if (GetCollHitMaterial() == 0) {
        if (*(float *)(fall + 0x5C) == 0.0f && ground_height <= probe_pos[2] && probe_pos[2] + *(float *)(fall + 0x8) < ground_height) {
            *(float *)(fall + 0x5C) = 1.0f;
            probe_pos[2] = ground_height;
            moby_spawn_scaled_effect(probe_pos, 3.0f);
        }
        ground_height = coll_get_ground_height_under_object((moby + 0x10));
    } else {
        if ((*(int *)(fall + 0x24) & 0x10) || *(short *)(fall + 0x3E) == 2) {
            FastVecAdd(new_pos, (moby + 0x10), fall);
            if (coll_get_ground_height_under_object(new_pos) < ground_height - 0.25f) {
                vec_fast_normalize_helper((float *)fall, (float *)fall, 0.0f);
            }
        }
    }

    if (*(float *)(fall + 0x5C) != 0.0f) {
        if (*(float *)(fall + 0x5C) < 4.0f) {
            FastVecScale(fall, fall, 0.7f);
        }
        if (*(float *)(fall + 0x5C) < 7.0f) {
            *(float *)(fall + 0x5C) = *(float *)(fall + 0x5C) + 1.0f;
            *(float *)(fall + 0x10) = *(float *)(fall + 0x10) * 0.75f;
        }
    }
    if (*(float *)(moby + 0x10) < 2.0f || 1021.0f < *(float *)(moby + 0x10)
        || *(float *)(moby + 0x14) < 2.0f || 1021.0f < *(float *)(moby + 0x14)
        || *(float *)(moby + 0x18) < 2.0f || 1021.0f < *(float *)(moby + 0x18)) {
        flags = 0x100;
    }

    if (*(float *)(fall + 0x54) != -1.0f && *(float *)(fall + 0x50) != -1.0f) {
        switch (*(short *)(fall + 0x3E)) {
        case 0: {
            float s0;
            float numerator0;
            s0 = math_fabs(*(float *)(fall + 0x8) / *(float *)(fall + 0x10));
            if (2.0f < s0) {
                tmp_val = moby_get_anim_value(moby);
                numerator0 = *(float *)(fall + 0x50) - tmp_val;
                rate = numerator0 / s0;
                if (0.0f < rate) {
                    ApproachValue((float *)(moby + 0x48), rate, 0.120000005f);
                }
            }
            break;
        }
        case 1:
            tmp_val = moby_get_anim_value(moby);
            if (*(float *)(fall + 0x54) <= tmp_val) {
                *(int *)(moby + 0x48) = 0;
            } else {
                float numerator1;
                float h = *(float *)(fall + 0x10) * -0.5f;
                fall_time = 60.0f;
                hit_count = math_solve_quadratic(&root1, &root2, h, *(float *)(fall + 0x8) - h, *(float *)(moby + 0x18) - ground_height);
                if (hit_count > 0 && 0.0f < root1 && root1 < fall_time) {
                    fall_time = root1;
                }
                if (fall_time < 0.0001f) {
                    fall_time = 0.0001f;
                }
                tmp_val = moby_get_anim_value(moby);
                numerator1 = *(float *)(fall + 0x54) - tmp_val;
                rate = numerator1 / fall_time;
                if (2.0f < rate) {
                    rate = 2.0f;
                } else if (rate < 0.0f) {
                    rate = 0.0f;
                }
                ApproachValue((float *)(moby + 0x48), rate, 0.120000005f);
            }
            break;
        case 2:
            *(float *)(moby + 0x48) = 1.0f;
            break;
        }
    }

    if (*(unsigned char *)(moby + 0x60) & 2) {
        flags |= 0x40;
    }
    if (!(*(int *)(fall + 0x24) & 4)) {
        MobySpringTurn(moby, (float *)(fall + 0x44), *(float *)(fall + 0x40), 0.02f, 0.3f, *(float *)(fall + 0x48));
    }

    i = 0;
    qcopy(start_pos, (moby + 0x10));
    start_pos[2] = start_pos[2] + *(float *)(fall + 0x28);
    FastVecAdd((moby + 0x10), (moby + 0x10), fall);
    qcopy(new_pos, (moby + 0x10));
    new_pos[2] = new_pos[2] + *(float *)(fall + 0x28);
    FastVecAdd(target_pos, new_pos, fall);
    hit_count = coll_process_hit(IntToFloat(*(int *)(fall + 0x20)) * 0.0010742187732830644f, target_pos, 16, moby, 0);
    if (i < hit_count) {
        int **pp = g_candidate_list;
        int k = hit_count;
        do {
            if (moby_is_in_special_class_range(*pp) != 0) {
                part_queue_impact_effect((char *)*pp, 1.0f, (int)moby, 0x10000, (moby + 0x10), fall);
            }
            pp++;
        } while (--k != 0);
    }

    grid_step = 0.0009765625f;
    tmp_val = FastVecLength(fall);
    if ((float)*(int *)(fall + 0x20) * grid_step < tmp_val) {
        CollLine(start_pos, new_pos, 36, moby, 0);
        qcopy(new_pos, &g_trace_start_pos);
    }
    if (coll_test_point(new_pos, IntToFloat(*(int *)(fall + 0x20)) * grid_step, 36, moby) != 0) {
        flags |= 2;
        hit_info = &g_trace_hit_info;
        qcopy((moby + 0x10), hit_info);
        unit_len = 1.0f;
        *(float *)(moby + 0x18) = *(float *)(moby + 0x18) - *(float *)(fall + 0x28);
        vec_scale_to_length(hit_normal, (char *)hit_info + 0x10, unit_len);
        if (0.7070000171661377f <= hit_normal[2]) {
            float e = FastVecDot(fall, hit_normal);
            if (e < 0.0f) {
                hit_prev = (char *)hit_info - 0x30;
                if (*(int *)(hit_prev + 0x18) == 0 || *(int *)(hit_prev + 0x1C) > 0) {
                    flags |= 1;
                    *(short *)(fall + 0x3E) = 2;
                }
                vec_scale_to_length(push_vec, hit_normal, e);
                FastVecSub(fall, fall, push_vec);
                if (*(short *)(fall + 0x3E) == 2) {
                    slide_speed = FastVecLength(fall);
                    ApproachValue(&slide_speed, 0.0f, *(float *)(fall + 0x10));
                    vec_scale_to_length(fall, fall, slide_speed);
                }
            }
        } else {
            float d = FastVecDot(fall, hit_normal);
            if (d < 0.0f) {
                d = d * -(*(float *)(fall + 0x30) + unit_len);
                vec_scale_to_length(push_vec, hit_normal, d);
                FastVecAdd(fall, fall, push_vec);
            }
        }
    }
    if (*(short *)(fall + 0x3E) == 0) {
        if (*(float *)(fall + 0x8) < 0.0f) {
            *(short *)(fall + 0x3E) = 1;
        }
    }
    return flags;
}
