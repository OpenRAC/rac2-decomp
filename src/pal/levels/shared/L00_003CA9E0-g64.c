#include "names.h"
/* func_PAL_L00_003CA9E0, the PAL copy of func_L00_003C6B98: the same C, where the spark timers get
 * the 50 Hz scale, the spawn step and its reach are scaled by 1.2f, the spawn lifetime drops from 30
 * to 25 and the per-frame 1/60 becomes 1/50. Spill slots follow gcse's expression-table order, which
 * depends on the insn count at gcse and on i's pseudo number: the locals' initialisers and the
 * function-scope declarations of color, count, a and b are part of that. The spawn copies use
 * qcopy_nc: the call that follows reads the copied vector itself. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char b0, b1, b2, b3;
} Particle;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; Vec normal; char rest[0x30]; } Collision;
typedef struct { unsigned char pad[0x2290]; char *object; } PlayerView;
typedef struct { int c[5]; } Colors;

extern Colors g_lightning_beam_colors NOT_SDA;

extern PlayerView g_hero_state;
extern char g_hero_state_block[];
extern Collision g_collision_result;
extern float g_default_vector;
extern unsigned char *g_lightning_particle_bytes[];
extern signed char g_lightning_spark_alpha;

extern float g_aim_target_range __attribute__((sda));
extern float g_lightning_beam_step __attribute__((sda));
extern float g_lightning_beam_angle_step __attribute__((sda));
extern float g_lightning_beam_segment_angle __attribute__((sda));
extern float g_lightning_beam_roll_step __attribute__((sda));
extern float g_lightning_beam_radius_start __attribute__((sda));
extern float g_lightning_beam_radius_end __attribute__((sda));
extern float g_lightning_spark_radius_start __attribute__((sda));
extern float g_lightning_spark_radius_end __attribute__((sda));
extern float g_lightning_l00_segment_length __attribute__((sda));
extern float g_lightning_jitter_range __attribute__((sda));
extern float g_lightning_sideways_length __attribute__((sda));
extern int g_lightning_beam_segment_limit __attribute__((sda));
extern int g_lightning_beam_flag_value __attribute__((sda));
extern int g_lightning_spark_lifetime __attribute__((sda));
extern int g_lightning_spark_fade_time __attribute__((sda));
extern float g_lightning_step_speed __attribute__((sda));
extern float g_lightning_spark_size_end __attribute__((sda));
extern float g_lightning_spark_size_start __attribute__((sda));
extern float g_lightning_spark_fade_rate __attribute__((sda));

extern float g_lightning_l00_segment_length_2;
extern float g_lightning_spin_angle;
extern Vec g_lightning_spark_positions[3];
extern Vec g_lightning_spark_directions[3];
extern int g_lightning_spark_timers[3];
extern float g_lightning_spark_alphas[3];
extern float g_lightning_spark_ages[3];
extern float g_lightning_spark_sizes[3];
extern int g_lightning_spark_active[3];
extern int g_lightning_spark_cooldown;

extern Vec g_lightning_beam_points[];
extern Vec g_lightning_ribbon_inner_points[];
extern Vec g_lightning_ribbon_outer_points[];
extern Vec g_lightning_ribbon_surface_a[][20];

extern void ResetBeamChainAndPulseState(char *);
extern void DrawBeamRingAndRailEffects_pal();
extern void ref_L00_003C6B98_00(void *, void *);
extern Particle *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, float, int);
extern Particle *part_spawn_owned_particle(float, float, void *, int, int, int, int, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern float FastVecLength(void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern float math_wrap_angle_to_pi(float);
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern void transform_vector(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern int math_fast_float_d(void *);
extern void vec_transform_or_copy(void *, void *);
extern void vec_build_spherical_offset(void *, float, float, float);
extern char *moby_get_private_value_0(char *);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern int CollLine(void *, void *, int, void *, void *);

void lightning_l00_beam_update_pal(char *moby)
{
    float pull_dir[4], seg_delta[4], spark_local[4], beam_end[4], work_vec[4];
    char *disabled[128];
    float tmp_a[4], tmp_b[4];
    char *beam_state;
    char *target_info = 0;
    float dist, t = 0.0f, w, r, ang, f, len = 0.0f, scale;
    int n, tries, j = 0, k = 0, kk = 0, q = 0, sign = 0, seg = 0;
    Particle *particle = 0;
    int color, count;
    float a, b;

    spark_local[3] = 1.0f;
    beam_state = *(char **)(moby + 0x68);
    *(int *)spark_local = 0;
    ResetBeamChainAndPulseState(moby);
    g_lightning_spin_angle = math_wrap_angle_to_pi(g_lightning_spin_angle + g_lightning_beam_angle_step);
    vec_scale_to_length(pull_dir, moby + 0xD0, -g_lightning_l00_segment_length_2);
    if (*(char **)(beam_state + 0x10) != 0 && (target_info = moby_get_private_value_0(*(char **)(beam_state + 0x10))) != 0) {
        FastVecScale(work_vec, *(char **)(beam_state + 0x10) + 0xE0, *(float *)(target_info + 0x10));
        FastVecAdd(beam_end, *(char **)(beam_state + 0x10) + 0x10, work_vec);
    } else {
        float x = *(float *)(beam_state + 0x48), y = *(float *)(beam_state + 0x4C);
        vec_build_spherical_offset(beam_end, g_aim_target_range, x, y);
        FastVecAdd(beam_end, beam_end, beam_state);
    }
    n = 0;
    dist = g_aim_target_range;
    tries = 0;
    if (*(char **)(beam_state + 0x10) == 0) {
        qcopy(work_vec, beam_state);
        while (CollLine(work_vec, beam_end, 0x14, g_hero_state.object, 0)) {
            Collision *col;
            char *hit;
            if (++tries >= 7) break;
            col = &g_collision_result;
            if (g_collision_result.hit != 0 && (*(short *)(g_collision_result.hit + 0xAA) == 0xE7D || *(short *)(g_collision_result.hit + 0xAA) == 0xEB0)) {
                disabled[n++] = g_collision_result.hit;
                *(int *)(g_collision_result.hit + 0x98) = 0;
                if (n < 128) {
                    qcopy(work_vec, &g_collision_result.point);
                    continue;
                }
            }
            {
                float tmp_c[4];
                FastVecSub(tmp_a, beam_state, &g_collision_result.point);
                f = FastVecDot(g_hero_state.object + 0xE0, tmp_a);
                FastVecScale(tmp_b, g_hero_state.object + 0xE0, f);
                FastVecSub(tmp_c, tmp_a, tmp_b);
                dist = FastVecLength(tmp_c);
            }
            break;
        }
        for (q = 0; q < n; q++) {
            *(int *)(disabled[q] + 0x98) = *(int *)(*(char **)(disabled[q] + 0x24) + 0x10);
        }
    } else {
        FastVecSub(work_vec, beam_state, *(char **)(beam_state + 0x10) + 0x10);
        f = FastVecDot(g_hero_state.object + 0xE0, work_vec);
        FastVecScale(tmp_a, g_hero_state.object + 0xE0, f);
        FastVecSub(tmp_b, work_vec, tmp_a);
        dist = FastVecLength(tmp_b);
    }
    g_lightning_l00_segment_length_2 = dist * g_lightning_beam_step;
    qcopy(&g_lightning_beam_points[0], beam_state);
    qcopy(&g_lightning_ribbon_inner_points[0], beam_state);
    qcopy(&g_lightning_ribbon_outer_points[0], beam_state);
    {
    int i;
    for (i = 1; i < 12; i++) {
        vec_transform_or_copy(&g_lightning_beam_points[i], &g_lightning_beam_points[i]);
        FastVecSub(seg_delta, &g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        t = IntToFloat(i) * g_lightning_beam_step;
        w = t * -0.49999997f + 0.9f;
        if (g_lightning_beam_segment_limit < i && *(char **)(beam_state + 0x10) != 0) {
            FastVecSub(work_vec, *(char **)(beam_state + 0x10) + 0x10, &g_lightning_beam_points[i]);
            vec_scale_to_length(work_vec, work_vec, g_lightning_l00_segment_length_2);
            lerp_vector(pull_dir, pull_dir, work_vec, 0.2f);
        }
        lerp_vector(work_vec, seg_delta, pull_dir, w);
        len = FastVecLength(work_vec);
        if (len == 0.0f) {
            qcopy(&g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        } else {
            FastVecScale(work_vec, work_vec, g_lightning_l00_segment_length_2 / len);
            FastVecAdd(&g_lightning_beam_points[i], &g_lightning_beam_points[i - 1], work_vec);
        }
        FastVecSub(tmp_a, &g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        FastVecCross(tmp_b, tmp_a, g_hero_state_block);
        vec_scale_to_length(tmp_b, tmp_b, g_lightning_beam_radius_start + (g_lightning_beam_radius_end - g_lightning_beam_radius_start) * t);
        {
        float tmp_c[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            math_apply_axis_rotation_to_quat(tmp_c, tmp_b, tmp_a, (float)j * g_lightning_beam_roll_step);
            FastVecAdd(&g_lightning_ribbon_surface_a[i][j], tmp_c, &g_lightning_beam_points[i]);
        }
        qcopy(m[3], &g_lightning_beam_points[i]);
        vec_scale_to_length(m[0], tmp_a, 1.0f);
        vec_scale_to_length(m[1], tmp_b, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        r = g_lightning_spark_radius_start + (g_lightning_spark_radius_end - g_lightning_spark_radius_start) * t;
        ang = math_wrap_angle_to_pi(g_lightning_spin_angle + g_lightning_beam_segment_angle * IntToFloat(i));
        spark_local[1] = r * math_fast_sin_or_cos_b(ang);
        spark_local[2] = r * math_fast_sin_or_cos_a(ang);
        transform_vector(&g_lightning_ribbon_inner_points[i], spark_local, m);
        spark_local[2] = -spark_local[2];
        transform_vector(&g_lightning_ribbon_outer_points[i], spark_local, m);
        }
    }
    }
    ref_L00_003C6B98_00(DrawBeamRingAndRailEffects_pal, moby);
    scale = math_random_float_range(0.1f, 1.7f);
    sign = math_random_int_below(2);
    if (sign == 0) sign = sign - 1;
    if (math_random_int_below(2) == 0) {
        qcopy_nc(work_vec, &g_lightning_ribbon_inner_points[11]);
        particle = part_spawn_ground_effect(work_vec, 0x19, scale * 0.1f, scale, 0x7F10107F, 0, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(work_vec, 0x19, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
    }
    if (math_random_int_below(2) == 0) {
        qcopy_nc(work_vec, &g_lightning_ribbon_outer_points[11]);
        particle = part_spawn_ground_effect(work_vec, 0x19, scale * 0.1f, scale, 0x7F104FFF, 0, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(work_vec, 0x19, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
    }
    FastVecSub(tmp_a, &g_lightning_beam_points[1], &g_lightning_beam_points[0]);
    vec_scale_to_length(tmp_a, tmp_a, g_lightning_l00_segment_length * 1.2f);
    if (math_random_int_below(2) == 0) {
        vec_scale_to_length(tmp_b, moby + 0xD0, g_lightning_sideways_length);
        FastVecAdd(work_vec, &g_lightning_beam_points[0], tmp_b);
        {
            Colors colors = g_lightning_beam_colors;
            float up[4], side[4];
        color = colors.c[math_random_int_below(5)];
        a = math_random_signed_float_range(0.0f, g_lightning_jitter_range);
        b = math_random_signed_float_range(0.0f, g_lightning_jitter_range);
        math_apply_axis_rotation_to_quat(up, tmp_a, g_hero_state_block, b);
        FastVecCross(side, tmp_a, g_hero_state_block);
        math_apply_axis_rotation_to_quat(up, up, side, a);
        count = FloatToInt(dist * 1.2f / (g_lightning_l00_segment_length * 1.2f));
        if (*(char **)(beam_state + 0x10) != 0) count *= 3;
        particle = part_spawn_owned_particle(scale * 0.1f, scale, work_vec, count, color, 0, sign, up, *(int *)(beam_state + 0x10));
        if (particle) particle->b2 = g_lightning_particle_bytes[0][6];
        particle = part_spawn_owned_particle(scale * 0.07f, scale * 0.7f, work_vec, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(beam_state + 0x10));
        if (particle) particle->b2 = g_lightning_particle_bytes[0][6];
        }
    }
    if (math_fast_float_d(&g_lightning_spark_cooldown)) {
        g_lightning_spark_cooldown = ((s32)(g_lightning_beam_flag_value) * 5 + 2) / 6;
        for (k = 0; k < 3; k++) {
            if (g_lightning_spark_active[k] == 0) {
                g_lightning_spark_active[k] = 1;
                g_lightning_spark_timers[k] = ((s32)(g_lightning_spark_lifetime) * 5 + 2) / 6;
                g_lightning_spark_ages[k] = 0;
                g_lightning_spark_sizes[k] = g_lightning_spark_size_start;
                g_lightning_spark_alphas[k] = IntToFloat(g_lightning_spark_alpha);
                qcopy(&g_lightning_spark_positions[k], beam_state);
                FastVecSub(tmp_b, &g_lightning_beam_points[1], &g_lightning_beam_points[0]);
                vec_scale_to_length(&g_lightning_spark_directions[k], tmp_b, 1.0f);
                break;
            }
        }
    }
    {
    for (kk = 0; kk < 3; kk++) {
        if (g_lightning_spark_active[kk] != 0) {
            if (math_fast_float_d(&g_lightning_spark_timers[kk]) != 0) {
                g_lightning_spark_active[kk] = 0;
            } else {
                float step, u, rem, inv;
                float tmp_c[4];
                if (g_lightning_spark_timers[kk] < g_lightning_spark_fade_time) g_lightning_spark_alphas[kk] -= g_lightning_spark_fade_rate;
                step = g_lightning_step_speed * 0.020000001f;
                g_lightning_spark_ages[kk] += step;
                u = g_lightning_spark_ages[kk] / g_aim_target_range;
                if (u > 1.0f) u = 1.0f;
                g_lightning_spark_sizes[kk] = g_lightning_spark_size_start + (g_lightning_spark_size_end - g_lightning_spark_size_start) * u;
                if (g_lightning_spark_ages[kk] >= g_aim_target_range) {
                    FastVecScale(tmp_b, &g_lightning_spark_directions[kk], step);
                    FastVecAdd(&g_lightning_spark_positions[kk], &g_lightning_spark_positions[kk], tmp_b);
                } else {
                    seg = FloatToInt(g_lightning_spark_ages[kk] / g_lightning_l00_segment_length_2);
                    rem = g_lightning_spark_ages[kk] - IntToFloat(seg) * g_lightning_l00_segment_length_2;
                    qcopy(&g_lightning_spark_positions[kk], &g_lightning_beam_points[seg]);
                    if (seg == 11) FastVecSub(tmp_b, &g_lightning_beam_points[seg], &g_lightning_beam_points[seg + -1]);
                    else FastVecSub(tmp_b, &g_lightning_beam_points[seg + 1], &g_lightning_beam_points[seg]);
                    inv = FastVecLength(tmp_b);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(tmp_c, tmp_b, rem * inv);
                        FastVecAdd(&g_lightning_spark_positions[kk], &g_lightning_spark_positions[kk], tmp_c);
                        vec_scale_to_length(tmp_c, tmp_b, inv);
                        lerp_vector(&g_lightning_spark_directions[kk], &g_lightning_spark_directions[kk], tmp_c, 0.1f);
                        vec_scale_to_length(&g_lightning_spark_directions[kk], &g_lightning_spark_directions[kk], 1.0f);
                    }
                }
            }
        }
    }
    }
}
