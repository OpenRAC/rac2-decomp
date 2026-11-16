/* func_PAL_L00_00405F98, the PAL copy of func_L00_00401668: the same C. */
#include "common.h"

/* func_PAL_L00_00405F98 needs -g (the division keeps its line label, retail's nop
   pair) on top of the -G8 small data, so it has a unit of its own. */

/* Retail copies the eight probe indices from this table into its stack frame.
   Referring to the table directly avoids creating a duplicate scalar pool. */
typedef struct { int index[8]; } ProbeOrder;
extern ProbeOrder ref_L00_00401668_00;

extern float g_spider_ground_probe_offsets[8][4];
extern float g_spider_ground_probe_points[8][4];
extern float g_global_object_vector[4] __attribute__((sda));
extern float g_hero_l00_position[4];
extern float g_hero_l00_velocity[4] __attribute__((sda));
extern int g_global_object_flag;
extern float g_spider_bot_probe_distance __attribute__((sda));
extern float g_spider_bot_angle_scale __attribute__((sda));
extern float g_spider_bot_ground_lerp_rate __attribute__((sda));
extern void vec_clear_128(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern int weapon_get_group(int);
extern int subtract_integer_with_clamp(int);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float), math_fast_sin_or_cos_a(float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);

/* Casts the eight ground probes in a fixed order. A hit on a surface that
   func_00300540 accepts sets states 9/10 instead; otherwise the hit point
   (D_L00_001BF220) is kept when its normal (D_L00_001BF240) passes the slope test
   or D_L00_001B2C14 is set. Then turns the orientation matrix (+0xC0) so its
   third row (+0xE0) follows the mean normal of the kept points and eases
   the position (+0x10) toward their centre along D_L00_001B2C00. Without any
   hit it sets state 4 and a velocity along the first row. */
void align_vehicle_to_ground_probes_pal(char *object)
{
    float (*probes)[4] = g_spider_ground_probe_offsets;
    float edges[8][4];
    float offset[4], center[4], normal[4];
    char *state = *(char **)(object + 0x68);
    ProbeOrder order = ref_L00_00401668_00;
    float a[4], b[4], c[4], axis[4], matrix[12];
    float target[4];
    int count, hit, i;
    float (*points)[4];
    float (*out)[4];
    float inv, angle;
    char *vehicle = object;

    vec_clear_128(center);
    hit = 0;
    vec_clear_128(normal);
    vec_scale_to_length(offset, g_global_object_vector, g_spider_bot_probe_distance + g_spider_bot_probe_distance);
    points = g_spider_ground_probe_points;
    out = points;
    count = 0;
    for (i = 0; i < 8; i++) {
        float *probe = probes[order.index[i]];
        FastVecAdd(a, probe, offset);
        if (CollLine(probe, a, 18, object, 0)) {
            hit = 1;
            if (weapon_get_group(GetCollHitMaterial())) {
                object[0x20] = 9;
                *(int *)(state + 0x60) = 8;
                continue;
            }
            FastVecScale(b, g_hero_l00_velocity, 0.0009765625f);
            vec_scale_to_length(b, b, 1.0f);
            vec_scale_to_length(c, g_global_object_vector, -1.0f);
            if (subtract_integer_with_clamp(FastVecDot(b, c) > 0.5f) || g_global_object_flag) {
                qcopy(out, g_hero_l00_position);
                ++out;
                FastVecAdd(center, center, g_hero_l00_position);
                ++count;
            }
        }
    }

    /* The settling step reads its inputs through local copies. GCSE copy
       propagation goes one copy deep per pass, so PRE still sees moby's
       offsets based on vehicle, and the copies set the size of PRE's hash
       table; together they give the order of the registers PRE creates, which
       is the order of the six spill slots at 0x158..0x16C. */
    {
        char *moby = vehicle;
        char *vars = state;
        float (*hits)[4] = points;
        int grounded = hit;

        if (count) {
            inv = 1.0f / IntToFloat(count);
            for (i = 0; i < count; ++i) {
                FastVecSub(a, hits[i], moby + 0x10);
                FastVecSub(b, hits[i + 1 == count ? 0 : i + 1], moby + 0x10);
                vec_scale_to_length(a, a, 1.0f);
                vec_scale_to_length(b, b, 1.0f);
                FastVecCross(edges[i], b, a);
                vec_scale_to_length(edges[i], edges[i], 1.0f);
                FastVecAdd(normal, normal, edges[i]);
            }
            FastVecScale(normal, normal, inv);
            vec_scale_to_length(a, normal, 1.0f);
            vec_scale_to_length(c, moby + 0xE0, 1.0f);
            vec_scale_to_length(b, a, 1.0f);
            FastVecCross(axis, c, b);
            angle = FastVecDot(c, b) * (g_spider_bot_angle_scale * 0.5f);
            FastVecScale(b, axis, math_fast_sin_or_cos_b(angle));
            b[3] = math_fast_sin_or_cos_a(angle);
            quaternion_to_rotation_basis(b, matrix);
            multiply_matrix3x3(moby + 0xC0, matrix, moby + 0xC0);
            FastVecScale(center, center, inv);
            FastVecSub(target, center, moby + 0x10);
            FastVecScale(target, g_global_object_vector, FastVecDot(target, g_global_object_vector));
            FastVecAdd(target, target, moby + 0x10);
            lerp_vector(moby + 0x10, moby + 0x10, target, g_spider_bot_ground_lerp_rate);
        }
        vec_scale_to_length(a, moby + 0xE0, 0.15f);
        FastVecAdd(a, moby + 0x10, a);
        if (!grounded) {
            moby[0x20] = 4;
            vec_scale_to_length(vars, moby + 0xC0, *(float *)(vars + 0x58));
        }
    }
}
