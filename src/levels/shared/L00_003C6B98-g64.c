/* Lightning-arc effect update: 12 segments of 20 points and three travelling sparks.
 * Twin of func_L00_00406150 (same instructions, its own data).
 * Spill slots follow gcse's expression-table order, which depends on the insn count
 * at gcse; the locals' initialisers are part of that. The spawn copies use qcopy_nc:
 * the call that follows reads the copied vector itself. */
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
extern void DrawBeamRingAndRailEffects();
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

/* Per-frame update of the lightning beam weapon. It finds where the beam ends, bends a chain of 12 points toward it, builds the glowing ribbon around each point, spawns sparks, and moves three travelling light pulses along the chain. */
void lightning_l00_beam_update(char *owner)
{
    float pull[4], segment[4], spin[4], end_point[4], scratch[4];
    char *disabled[128];
    float delta[4], sideways[4];
    char *vars;
    char *target_info = 0;
    float dist, fraction = 0.0f, blend, radius, angle, along, seg_length = 0.0f, scale;
    int disabled_count, tries, j = 0, spark_slot = 0, spark_index = 0, index = 0, sign = 0, segment_index = 0;
    Particle *particle = 0;

    spin[3] = 1.0f;
    vars = *(char **)(owner + 0x68);
    *(int *)spin = 0;
    ResetBeamChainAndPulseState(owner);
    g_lightning_spin_angle = math_wrap_angle_to_pi(g_lightning_spin_angle + g_lightning_beam_angle_step);
    vec_scale_to_length(pull, owner + 0xD0, -g_lightning_l00_segment_length_2);
    if (*(char **)(vars + 0x10) != 0 && (target_info = moby_get_private_value_0(*(char **)(vars + 0x10))) != 0) {
        FastVecScale(scratch, *(char **)(vars + 0x10) + 0xE0, *(float *)(target_info + 0x10));
        FastVecAdd(end_point, *(char **)(vars + 0x10) + 0x10, scratch);
    } else {
        float x = *(float *)(vars + 0x48), y = *(float *)(vars + 0x4C);
        vec_build_spherical_offset(end_point, g_aim_target_range, x, y);
        FastVecAdd(end_point, end_point, vars);
    }
    disabled_count = 0;
    dist = g_aim_target_range;
    tries = 0;
    if (*(char **)(vars + 0x10) == 0) {
        qcopy(scratch, vars);
        while (CollLine(scratch, end_point, 0x14, g_hero_state.object, 0)) {
            Collision *col;
            char *hit;
            if (++tries >= 7) break;
            col = &g_collision_result;
            if (g_collision_result.hit != 0 && (*(short *)(g_collision_result.hit + 0xAA) == MOBY_CLASS_SHEEP || *(short *)(g_collision_result.hit + 0xAA) == MOBY_CLASS_DARK_SHEEP)) {
                disabled[disabled_count++] = g_collision_result.hit;
                *(int *)(g_collision_result.hit + 0x98) = 0;
                if (disabled_count < 128) {
                    qcopy(scratch, &g_collision_result.point);
                    continue;
                }
            }
            {
                float offset[4];
                FastVecSub(delta, vars, &g_collision_result.point);
                along = FastVecDot(g_hero_state.object + 0xE0, delta);
                FastVecScale(sideways, g_hero_state.object + 0xE0, along);
                FastVecSub(offset, delta, sideways);
                dist = FastVecLength(offset);
            }
            break;
        }
        for (index = 0; index < disabled_count; index++) {
            *(int *)(disabled[index] + 0x98) = *(int *)(*(char **)(disabled[index] + 0x24) + 0x10);
        }
    } else {
        FastVecSub(scratch, vars, *(char **)(vars + 0x10) + 0x10);
        along = FastVecDot(g_hero_state.object + 0xE0, scratch);
        FastVecScale(delta, g_hero_state.object + 0xE0, along);
        FastVecSub(sideways, scratch, delta);
        dist = FastVecLength(sideways);
    }
    g_lightning_l00_segment_length_2 = dist * g_lightning_beam_step;
    qcopy(&g_lightning_beam_points[0], vars);
    qcopy(&g_lightning_ribbon_inner_points[0], vars);
    qcopy(&g_lightning_ribbon_outer_points[0], vars);
    {
    int i;
    for (i = 1; i < 12; i++) {
        vec_transform_or_copy(&g_lightning_beam_points[i], &g_lightning_beam_points[i]);
        FastVecSub(segment, &g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        fraction = IntToFloat(i) * g_lightning_beam_step;
        blend = fraction * -0.49999997f + 0.9f;
        if (g_lightning_beam_segment_limit < i && *(char **)(vars + 0x10) != 0) {
            FastVecSub(scratch, *(char **)(vars + 0x10) + 0x10, &g_lightning_beam_points[i]);
            vec_scale_to_length(scratch, scratch, g_lightning_l00_segment_length_2);
            lerp_vector(pull, pull, scratch, 0.2f);
        }
        lerp_vector(scratch, segment, pull, blend);
        seg_length = FastVecLength(scratch);
        if (seg_length == 0.0f) {
            qcopy(&g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        } else {
            FastVecScale(scratch, scratch, g_lightning_l00_segment_length_2 / seg_length);
            FastVecAdd(&g_lightning_beam_points[i], &g_lightning_beam_points[i - 1], scratch);
        }
        FastVecSub(delta, &g_lightning_beam_points[i], &g_lightning_beam_points[i - 1]);
        FastVecCross(sideways, delta, g_hero_state_block);
        vec_scale_to_length(sideways, sideways, g_lightning_beam_radius_start + (g_lightning_beam_radius_end - g_lightning_beam_radius_start) * fraction);
        {
        float offset[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            math_apply_axis_rotation_to_quat(offset, sideways, delta, (float)j * g_lightning_beam_roll_step);
            FastVecAdd(&g_lightning_ribbon_surface_a[i][j], offset, &g_lightning_beam_points[i]);
        }
        qcopy(m[3], &g_lightning_beam_points[i]);
        vec_scale_to_length(m[0], delta, 1.0f);
        vec_scale_to_length(m[1], sideways, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        radius = g_lightning_spark_radius_start + (g_lightning_spark_radius_end - g_lightning_spark_radius_start) * fraction;
        angle = math_wrap_angle_to_pi(g_lightning_spin_angle + g_lightning_beam_segment_angle * IntToFloat(i));
        spin[1] = radius * math_fast_sin_or_cos_b(angle);
        spin[2] = radius * math_fast_sin_or_cos_a(angle);
        transform_vector(&g_lightning_ribbon_inner_points[i], spin, m);
        spin[2] = -spin[2];
        transform_vector(&g_lightning_ribbon_outer_points[i], spin, m);
        }
    }
    }
    ref_L00_003C6B98_00(DrawBeamRingAndRailEffects, owner);
    scale = math_random_float_range(0.1f, 1.7f);
    sign = math_random_int_below(2);
    if (sign == 0) sign = sign - 1;
    if (math_random_int_below(2) == 0) {
        qcopy_nc(scratch, &g_lightning_ribbon_inner_points[11]);
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.1f, scale, 0x7F10107F, 0, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
    }
    if (math_random_int_below(2) == 0) {
        qcopy_nc(scratch, &g_lightning_ribbon_outer_points[11]);
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.1f, scale, 0x7F104FFF, 0, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &g_default_vector, 0.003f, 1);
        if (particle) particle->b2 = g_lightning_particle_bytes[0][7];
    }
    FastVecSub(delta, &g_lightning_beam_points[1], &g_lightning_beam_points[0]);
    vec_scale_to_length(delta, delta, g_lightning_l00_segment_length);
    if (math_random_int_below(2) == 0) {
        vec_scale_to_length(sideways, owner + 0xD0, g_lightning_sideways_length);
        FastVecAdd(scratch, &g_lightning_beam_points[0], sideways);
        {
            Colors colors = g_lightning_beam_colors;
            float up[4], side[4];
            int color, count;
            float a, b;
        color = colors.c[math_random_int_below(5)];
        a = math_random_signed_float_range(0.0f, g_lightning_jitter_range);
        b = math_random_signed_float_range(0.0f, g_lightning_jitter_range);
        math_apply_axis_rotation_to_quat(up, delta, g_hero_state_block, b);
        FastVecCross(side, delta, g_hero_state_block);
        math_apply_axis_rotation_to_quat(up, up, side, a);
        count = FloatToInt(dist * 1.2f / g_lightning_l00_segment_length);
        if (*(char **)(vars + 0x10) != 0) count *= 3;
        particle = part_spawn_owned_particle(scale * 0.1f, scale, scratch, count, color, 0, sign, up, *(int *)(vars + 0x10));
        if (particle) particle->b2 = g_lightning_particle_bytes[0][6];
        particle = part_spawn_owned_particle(scale * 0.07f, scale * 0.7f, scratch, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(vars + 0x10));
        if (particle) particle->b2 = g_lightning_particle_bytes[0][6];
        }
    }
    if (math_fast_float_d(&g_lightning_spark_cooldown)) {
        g_lightning_spark_cooldown = g_lightning_beam_flag_value;
        for (spark_slot = 0; spark_slot < 3; spark_slot++) {
            if (g_lightning_spark_active[spark_slot] == 0) {
                g_lightning_spark_active[spark_slot] = 1;
                g_lightning_spark_timers[spark_slot] = g_lightning_spark_lifetime;
                g_lightning_spark_ages[spark_slot] = 0;
                g_lightning_spark_sizes[spark_slot] = g_lightning_spark_size_start;
                g_lightning_spark_alphas[spark_slot] = IntToFloat(g_lightning_spark_alpha);
                qcopy(&g_lightning_spark_positions[spark_slot], vars);
                FastVecSub(sideways, &g_lightning_beam_points[1], &g_lightning_beam_points[0]);
                vec_scale_to_length(&g_lightning_spark_directions[spark_slot], sideways, 1.0f);
                break;
            }
        }
    }
    {
    for (spark_index = 0; spark_index < 3; spark_index++) {
        if (g_lightning_spark_active[spark_index] != 0) {
            if (math_fast_float_d(&g_lightning_spark_timers[spark_index]) != 0) {
                g_lightning_spark_active[spark_index] = 0;
            } else {
                float step, u, rem, inv;
                float offset[4];
                if (g_lightning_spark_timers[spark_index] < g_lightning_spark_fade_time) g_lightning_spark_alphas[spark_index] -= g_lightning_spark_fade_rate;
                step = g_lightning_step_speed * 0.016666668f;
                g_lightning_spark_ages[spark_index] += step;
                u = g_lightning_spark_ages[spark_index] / g_aim_target_range;
                if (u > 1.0f) u = 1.0f;
                g_lightning_spark_sizes[spark_index] = g_lightning_spark_size_start + (g_lightning_spark_size_end - g_lightning_spark_size_start) * u;
                if (g_lightning_spark_ages[spark_index] >= g_aim_target_range) {
                    FastVecScale(sideways, &g_lightning_spark_directions[spark_index], step);
                    FastVecAdd(&g_lightning_spark_positions[spark_index], &g_lightning_spark_positions[spark_index], sideways);
                } else {
                    segment_index = FloatToInt(g_lightning_spark_ages[spark_index] / g_lightning_l00_segment_length_2);
                    rem = g_lightning_spark_ages[spark_index] - IntToFloat(segment_index) * g_lightning_l00_segment_length_2;
                    qcopy(&g_lightning_spark_positions[spark_index], &g_lightning_beam_points[segment_index]);
                    if (segment_index == 11) FastVecSub(sideways, &g_lightning_beam_points[segment_index], &g_lightning_beam_points[segment_index + -1]);
                    else FastVecSub(sideways, &g_lightning_beam_points[segment_index + 1], &g_lightning_beam_points[segment_index]);
                    inv = FastVecLength(sideways);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(offset, sideways, rem * inv);
                        FastVecAdd(&g_lightning_spark_positions[spark_index], &g_lightning_spark_positions[spark_index], offset);
                        vec_scale_to_length(offset, sideways, inv);
                        lerp_vector(&g_lightning_spark_directions[spark_index], &g_lightning_spark_directions[spark_index], offset, 0.1f);
                        vec_scale_to_length(&g_lightning_spark_directions[spark_index], &g_lightning_spark_directions[spark_index], 1.0f);
                    }
                }
            }
        }
    }
    }
}
