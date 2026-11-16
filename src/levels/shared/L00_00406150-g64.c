/* Lightning-arc effect update: 12 segments of 20 points and three travelling sparks.
 * Twin of func_L00_003C6B98 (same instructions, its own data).
 * Spill slots follow gcse's expression-table order, which depends on the insn count
 * at gcse; the locals' initialisers are part of that. The spawn copies use qcopy_nc:
 * the call that follows reads the copied vector itself. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float dot[4]; } Vec;
typedef struct {
    unsigned char b0, b1, b2, b3;
} Particle;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; Vec normal; char rest[0x30]; } Collision;
typedef struct { unsigned char pad[0x2290]; char *object; } PlayerView;
typedef struct { int c[5]; } Colors;

extern Colors g_sheepinator_beam_colors NOT_SDA;

extern PlayerView g_hero_state;
extern char g_hero_state_block[];
extern Collision g_collision_result;
extern float g_default_vector;
extern unsigned char *g_lightning_particle_bytes[];
extern signed char g_sheepinator_beam_byte_param;

extern float g_sheepinator_beam_range __attribute__((sda));
extern float g_sheepinator_beam_step_scale __attribute__((sda));
extern float g_sheepinator_beam_twist_rate __attribute__((sda));
extern float g_sheepinator_beam_twist_step __attribute__((sda));
extern float g_sheepinator_beam_sample_angle __attribute__((sda));
extern float g_sheepinator_beam_side_start __attribute__((sda));
extern float g_sheepinator_beam_side_end __attribute__((sda));
extern float g_sheepinator_beam_radius_start __attribute__((sda));
extern float g_sheepinator_beam_radius_end __attribute__((sda));
extern float g_sheepinator_beam_segment_length __attribute__((sda));
extern float g_sheepinator_beam_jitter __attribute__((sda));
extern float g_sheepinator_beam_offset_length __attribute__((sda));
extern int g_sheepinator_beam_min_segments __attribute__((sda));
extern int g_sheepinator_beam_particle_init __attribute__((sda));
extern int g_sheepinator_beam_particle_life __attribute__((sda));
extern int g_sheepinator_beam_fade_threshold __attribute__((sda));
extern float g_sheepinator_beam_particle_speed __attribute__((sda));
extern float g_sheepinator_beam_size_end __attribute__((sda));
extern float g_sheepinator_beam_size_start __attribute__((sda));
extern float g_sheepinator_beam_fade_step __attribute__((sda));

extern float g_sheepinator_segment_length;
extern float g_sheepinator_spin_angle;
extern Vec g_sheepinator_spark_positions[3];
extern Vec g_sheepinator_spark_directions[3];
extern int g_sheepinator_spark_timers[3];
extern float g_sheepinator_spark_alphas[3];
extern float g_sheepinator_spark_ages[3];
extern float g_sheepinator_spark_sizes[3];
extern int g_sheepinator_spark_active[3];
extern int g_sheepinator_spark_cooldown;

extern Vec g_sheepinator_beam_points[];
extern Vec g_sheepinator_ribbon_inner_points[];
extern Vec g_sheepinator_ribbon_outer_points[];
extern Vec g_sheepinator_ribbon_surface_a[][20];

extern void sheepinator_reset_beam(char *);
extern void DrawScrollingRingMesh();
extern void ref_L00_00406150_00(void *, void *);
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

/* Moves and bends the Sheepinator beam toward its target, adds sparks along it, and moves three travelling sparks. */
void sheepinator_update_beam_shape(char *object)
{
    float sag[4], segment[4], ring_offset[4], beam_end[4], temp[4];
    char *disabled[128];
    float edge[4], side[4];
    char *obj;
    char *def = 0;
    float dist, progress = 0.0f, pull, radius, angle, dot, len = 0.0f, scale;
    int n, tries, j = 0, k = 0, kk = 0, q = 0, sign = 0, seg = 0;
    Particle *p = 0;

    ring_offset[3] = 1.0f;
    obj = *(char **)(object + 0x68);
    *(int *)ring_offset = 0;
    sheepinator_reset_beam(object);
    g_sheepinator_spin_angle = math_wrap_angle_to_pi(g_sheepinator_spin_angle + g_sheepinator_beam_twist_rate);
    FastVecScale(sag, object + 0xD0, -g_sheepinator_segment_length);
    if (*(char **)(obj + 0x10) != 0 && (def = moby_get_private_value_0(*(char **)(obj + 0x10))) != 0) {
        FastVecScale(temp, *(char **)(obj + 0x10) + 0xE0, *(float *)(def + 0x10));
        FastVecAdd(beam_end, *(char **)(obj + 0x10) + 0x10, temp);
    } else {
        float x = *(float *)(obj + 0x48), y = *(float *)(obj + 0x4C);
        vec_build_spherical_offset(beam_end, g_sheepinator_beam_range, x, y);
        FastVecAdd(beam_end, beam_end, obj);
    }
    n = 0;
    dist = g_sheepinator_beam_range;
    tries = 0;
    if (*(char **)(obj + 0x10) == 0) {
        qcopy(temp, obj);
        while (CollLine(temp, beam_end, 0x14, g_hero_state.object, 0)) {
            Collision *col;
            char *hit;
            if (++tries >= 7) break;
            col = &g_collision_result;
            if (g_collision_result.hit != 0 && (*(short *)(g_collision_result.hit + 0xAA) == 0xE7D || *(short *)(g_collision_result.hit + 0xAA) == 0xEB0)) {
                disabled[n++] = g_collision_result.hit;
                *(int *)(g_collision_result.hit + 0x98) = 0;
                if (n < 128) {
                    qcopy(temp, &g_collision_result.point);
                    continue;
                }
            }
            {
                float sample[4];
                FastVecSub(edge, obj, &g_collision_result.point);
                dot = FastVecDot(g_hero_state.object + 0xE0, edge);
                FastVecScale(side, g_hero_state.object + 0xE0, dot);
                FastVecSub(sample, edge, side);
                dist = FastVecLength(sample);
            }
            break;
        }
        for (q = 0; q < n; q++) {
            *(int *)(disabled[q] + 0x98) = *(int *)(*(char **)(disabled[q] + 0x24) + 0x10);
        }
    } else {
        FastVecSub(temp, obj, *(char **)(obj + 0x10) + 0x10);
        dot = FastVecDot(g_hero_state.object + 0xE0, temp);
        FastVecScale(edge, g_hero_state.object + 0xE0, dot);
        FastVecSub(side, temp, edge);
        dist = FastVecLength(side);
    }
    g_sheepinator_segment_length = dist * g_sheepinator_beam_step_scale;
    qcopy(&g_sheepinator_beam_points[0], obj);
    qcopy(&g_sheepinator_ribbon_inner_points[0], obj);
    qcopy(&g_sheepinator_ribbon_outer_points[0], obj);
    {
    int i;
    for (i = 1; i < 12; i++) {
        vec_transform_or_copy(&g_sheepinator_beam_points[i], &g_sheepinator_beam_points[i]);
        FastVecSub(segment, &g_sheepinator_beam_points[i], &g_sheepinator_beam_points[i - 1]);
        progress = IntToFloat(i) * g_sheepinator_beam_step_scale;
        pull = progress * -0.49999997f + 0.9f;
        if (g_sheepinator_beam_min_segments < i && *(char **)(obj + 0x10) != 0) {
            FastVecSub(temp, *(char **)(obj + 0x10) + 0x10, &g_sheepinator_beam_points[i]);
            vec_scale_to_length(temp, temp, g_sheepinator_segment_length);
            lerp_vector(sag, sag, temp, 0.2f);
        }
        lerp_vector(temp, segment, sag, pull);
        len = FastVecLength(temp);
        if (len == 0.0f) {
            qcopy(&g_sheepinator_beam_points[i], &g_sheepinator_beam_points[i - 1]);
        } else {
            FastVecScale(temp, temp, g_sheepinator_segment_length / len);
            FastVecAdd(&g_sheepinator_beam_points[i], &g_sheepinator_beam_points[i - 1], temp);
        }
        FastVecSub(edge, &g_sheepinator_beam_points[i], &g_sheepinator_beam_points[i - 1]);
        FastVecCross(side, edge, g_hero_state_block);
        vec_scale_to_length(side, side, g_sheepinator_beam_side_start + (g_sheepinator_beam_side_end - g_sheepinator_beam_side_start) * progress);
        {
        float sample[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            math_apply_axis_rotation_to_quat(sample, side, edge, (float)j * g_sheepinator_beam_sample_angle);
            FastVecAdd(&g_sheepinator_ribbon_surface_a[i][j], sample, &g_sheepinator_beam_points[i]);
        }
        qcopy(m[3], &g_sheepinator_beam_points[i]);
        vec_scale_to_length(m[0], edge, 1.0f);
        vec_scale_to_length(m[1], side, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        radius = g_sheepinator_beam_radius_start + (g_sheepinator_beam_radius_end - g_sheepinator_beam_radius_start) * progress;
        angle = math_wrap_angle_to_pi(g_sheepinator_spin_angle + g_sheepinator_beam_twist_step * IntToFloat(i));
        ring_offset[1] = radius * math_fast_sin_or_cos_b(angle);
        ring_offset[2] = radius * math_fast_sin_or_cos_a(angle);
        transform_vector(&g_sheepinator_ribbon_inner_points[i], ring_offset, m);
        ring_offset[2] = -ring_offset[2];
        transform_vector(&g_sheepinator_ribbon_outer_points[i], ring_offset, m);
        }
    }
    }
    ref_L00_00406150_00(DrawScrollingRingMesh, object);
    scale = math_random_float_range(0.1f, 1.7f);
    sign = math_random_int_below(2);
    if (sign == 0) sign = sign - 1;
    if (math_random_int_below(2) == 0) {
        qcopy_nc(temp, &g_sheepinator_ribbon_inner_points[11]);
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.1f, scale, 0x7F103FFF, 0, sign, &g_default_vector, 0.003f, 1);
        if (p) p->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &g_default_vector, 0.003f, 1);
        if (p) p->b2 = g_lightning_particle_bytes[0][7];
    }
    if (math_random_int_below(2) == 0) {
        qcopy_nc(temp, &g_sheepinator_ribbon_outer_points[11]);
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.1f, scale, 0x80FF4F10, 0, sign, &g_default_vector, 0.003f, 1);
        if (p) p->b2 = g_lightning_particle_bytes[0][7];
        sign = -sign;
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &g_default_vector, 0.003f, 1);
        if (p) p->b2 = g_lightning_particle_bytes[0][7];
    }
    FastVecSub(edge, &g_sheepinator_beam_points[1], &g_sheepinator_beam_points[0]);
    vec_scale_to_length(edge, edge, g_sheepinator_beam_segment_length);
    if (math_random_int_below(2) == 0) {
        vec_scale_to_length(side, object + 0xD0, g_sheepinator_beam_offset_length);
        FastVecAdd(temp, &g_sheepinator_beam_points[0], side);
        {
            Colors colors = g_sheepinator_beam_colors;
            float up[4], side[4];
            int color, count;
            float a, b;
        color = colors.c[math_random_int_below(5)];
        a = math_random_signed_float_range(0.0f, g_sheepinator_beam_jitter);
        b = math_random_signed_float_range(0.0f, g_sheepinator_beam_jitter);
        math_apply_axis_rotation_to_quat(up, edge, g_hero_state_block, b);
        FastVecCross(side, edge, g_hero_state_block);
        math_apply_axis_rotation_to_quat(up, up, side, a);
        count = FloatToInt(dist * 1.2f / g_sheepinator_beam_segment_length);
        if (*(char **)(obj + 0x10) != 0) count *= 3;
        p = part_spawn_owned_particle(scale * 0.1f, scale, temp, count, color, 0, sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = g_lightning_particle_bytes[0][6];
        p = part_spawn_owned_particle(scale * 0.07f, scale * 0.7f, temp, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = g_lightning_particle_bytes[0][6];
        }
    }
    if (math_fast_float_d(&g_sheepinator_spark_cooldown)) {
        g_sheepinator_spark_cooldown = g_sheepinator_beam_particle_init;
        for (k = 0; k < 3; k++) {
            if (g_sheepinator_spark_active[k] == 0) {
                g_sheepinator_spark_active[k] = 1;
                g_sheepinator_spark_timers[k] = g_sheepinator_beam_particle_life;
                g_sheepinator_spark_ages[k] = 0;
                g_sheepinator_spark_sizes[k] = g_sheepinator_beam_size_start;
                g_sheepinator_spark_alphas[k] = IntToFloat(g_sheepinator_beam_byte_param);
                qcopy(&g_sheepinator_spark_positions[k], obj);
                FastVecSub(side, &g_sheepinator_beam_points[1], &g_sheepinator_beam_points[0]);
                vec_scale_to_length(&g_sheepinator_spark_directions[k], side, 1.0f);
                break;
            }
        }
    }
    {
    for (kk = 0; kk < 3; kk++) {
        if (g_sheepinator_spark_active[kk] != 0) {
            if (math_fast_float_d(&g_sheepinator_spark_timers[kk]) != 0) {
                g_sheepinator_spark_active[kk] = 0;
            } else {
                float step, u, rem, inv;
                float sample[4];
                if (g_sheepinator_spark_timers[kk] < g_sheepinator_beam_fade_threshold) g_sheepinator_spark_alphas[kk] -= g_sheepinator_beam_fade_step;
                step = g_sheepinator_beam_particle_speed * 0.016666668f;
                g_sheepinator_spark_ages[kk] += step;
                u = g_sheepinator_spark_ages[kk] / g_sheepinator_beam_range;
                if (u > 1.0f) u = 1.0f;
                g_sheepinator_spark_sizes[kk] = g_sheepinator_beam_size_start + (g_sheepinator_beam_size_end - g_sheepinator_beam_size_start) * u;
                if (g_sheepinator_spark_ages[kk] >= g_sheepinator_beam_range) {
                    FastVecScale(side, &g_sheepinator_spark_directions[kk], step);
                    FastVecAdd(&g_sheepinator_spark_positions[kk], &g_sheepinator_spark_positions[kk], side);
                } else {
                    seg = FloatToInt(g_sheepinator_spark_ages[kk] / g_sheepinator_segment_length);
                    rem = g_sheepinator_spark_ages[kk] - IntToFloat(seg) * g_sheepinator_segment_length;
                    qcopy(&g_sheepinator_spark_positions[kk], &g_sheepinator_beam_points[seg]);
                    if (seg == 11) FastVecSub(side, &g_sheepinator_beam_points[seg], &g_sheepinator_beam_points[seg + -1]);
                    else FastVecSub(side, &g_sheepinator_beam_points[seg + 1], &g_sheepinator_beam_points[seg]);
                    inv = FastVecLength(side);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(sample, side, rem * inv);
                        FastVecAdd(&g_sheepinator_spark_positions[kk], &g_sheepinator_spark_positions[kk], sample);
                        vec_scale_to_length(sample, side, inv);
                        lerp_vector(&g_sheepinator_spark_directions[kk], &g_sheepinator_spark_directions[kk], sample, 0.1f);
                        vec_scale_to_length(&g_sheepinator_spark_directions[kk], &g_sheepinator_spark_directions[kk], 1.0f);
                    }
                }
            }
        }
    }
    }
}
