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

extern Colors D_L00_001B0EC8 NOT_SDA;

extern PlayerView g_hero_state;
extern char D_0018A0E0[];
extern Collision g_collision_result;
extern float D_L00_001A8F20;
extern unsigned char *D_L00_001FEAC4[];
extern signed char D_L00_001B0EBF;

extern float D_L00_001B0E38 __attribute__((sda));
extern float D_L00_001B0E4C __attribute__((sda));
extern float D_L00_001B0E54 __attribute__((sda));
extern float D_L00_001B0E58 __attribute__((sda));
extern float D_L00_001B0E60 __attribute__((sda));
extern float D_L00_001B0E64 __attribute__((sda));
extern float D_L00_001B0E68 __attribute__((sda));
extern float D_L00_001B0E88 __attribute__((sda));
extern float D_L00_001B0E8C __attribute__((sda));
extern float D_L00_001B0E90 __attribute__((sda));
extern float D_L00_001B0E98 __attribute__((sda));
extern float D_L00_001B0E9C __attribute__((sda));
extern int D_L00_001B0E50 __attribute__((sda));
extern int D_L00_001B0EA0 __attribute__((sda));
extern int D_L00_001B0EA8 __attribute__((sda));
extern int D_L00_001B0EAC __attribute__((sda));
extern float D_L00_001B0EA4 __attribute__((sda));
extern float D_L00_001B0EB4 __attribute__((sda));
extern float D_L00_001B0EB8 __attribute__((sda));
extern float D_L00_001B0EC4 __attribute__((sda));

extern float D_L00_001B2C80;
extern float D_L00_001B2C84;
extern Vec D_L00_001B2C90[3];
extern Vec D_L00_001B2CC0[3];
extern int D_L00_001B2CF0[3];
extern float D_L00_001B2D00[3];
extern float D_L00_001B2D10[3];
extern float D_L00_001B2D20[3];
extern int D_L00_001B2D30[3];
extern int D_L00_001B2D3C;

extern Vec D_L00_00254A60[];
extern Vec D_L00_00254B20[];
extern Vec D_L00_00254BE0[];
extern Vec D_L00_00254CA0[][20];

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
    D_L00_001B2C84 = math_wrap_angle_to_pi(D_L00_001B2C84 + D_L00_001B0E54);
    FastVecScale(sag, object + 0xD0, -D_L00_001B2C80);
    if (*(char **)(obj + 0x10) != 0 && (def = moby_get_private_value_0(*(char **)(obj + 0x10))) != 0) {
        FastVecScale(temp, *(char **)(obj + 0x10) + 0xE0, *(float *)(def + 0x10));
        FastVecAdd(beam_end, *(char **)(obj + 0x10) + 0x10, temp);
    } else {
        float x = *(float *)(obj + 0x48), y = *(float *)(obj + 0x4C);
        vec_build_spherical_offset(beam_end, D_L00_001B0E38, x, y);
        FastVecAdd(beam_end, beam_end, obj);
    }
    n = 0;
    dist = D_L00_001B0E38;
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
    D_L00_001B2C80 = dist * D_L00_001B0E4C;
    qcopy(&D_L00_00254A60[0], obj);
    qcopy(&D_L00_00254B20[0], obj);
    qcopy(&D_L00_00254BE0[0], obj);
    {
    int i;
    for (i = 1; i < 12; i++) {
        vec_transform_or_copy(&D_L00_00254A60[i], &D_L00_00254A60[i]);
        FastVecSub(segment, &D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        progress = IntToFloat(i) * D_L00_001B0E4C;
        pull = progress * -0.49999997f + 0.9f;
        if (D_L00_001B0E50 < i && *(char **)(obj + 0x10) != 0) {
            FastVecSub(temp, *(char **)(obj + 0x10) + 0x10, &D_L00_00254A60[i]);
            vec_scale_to_length(temp, temp, D_L00_001B2C80);
            lerp_vector(sag, sag, temp, 0.2f);
        }
        lerp_vector(temp, segment, sag, pull);
        len = FastVecLength(temp);
        if (len == 0.0f) {
            qcopy(&D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        } else {
            FastVecScale(temp, temp, D_L00_001B2C80 / len);
            FastVecAdd(&D_L00_00254A60[i], &D_L00_00254A60[i - 1], temp);
        }
        FastVecSub(edge, &D_L00_00254A60[i], &D_L00_00254A60[i - 1]);
        FastVecCross(side, edge, D_0018A0E0);
        vec_scale_to_length(side, side, D_L00_001B0E64 + (D_L00_001B0E68 - D_L00_001B0E64) * progress);
        {
        float sample[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            math_apply_axis_rotation_to_quat(sample, side, edge, (float)j * D_L00_001B0E60);
            FastVecAdd(&D_L00_00254CA0[i][j], sample, &D_L00_00254A60[i]);
        }
        qcopy(m[3], &D_L00_00254A60[i]);
        vec_scale_to_length(m[0], edge, 1.0f);
        vec_scale_to_length(m[1], side, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        radius = D_L00_001B0E88 + (D_L00_001B0E8C - D_L00_001B0E88) * progress;
        angle = math_wrap_angle_to_pi(D_L00_001B2C84 + D_L00_001B0E58 * IntToFloat(i));
        ring_offset[1] = radius * math_fast_sin_or_cos_b(angle);
        ring_offset[2] = radius * math_fast_sin_or_cos_a(angle);
        transform_vector(&D_L00_00254B20[i], ring_offset, m);
        ring_offset[2] = -ring_offset[2];
        transform_vector(&D_L00_00254BE0[i], ring_offset, m);
        }
    }
    }
    ref_L00_00406150_00(DrawScrollingRingMesh, object);
    scale = math_random_float_range(0.1f, 1.7f);
    sign = math_random_int_below(2);
    if (sign == 0) sign = sign - 1;
    if (math_random_int_below(2) == 0) {
        qcopy_nc(temp, &D_L00_00254B20[11]);
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.1f, scale, 0x7F103FFF, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    if (math_random_int_below(2) == 0) {
        qcopy_nc(temp, &D_L00_00254BE0[11]);
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.1f, scale, 0x80FF4F10, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        p = part_spawn_ground_effect(temp, 0x1E, scale * 0.07f, scale * 0.7f, 0x80808080, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (p) p->b2 = D_L00_001FEAC4[0][7];
    }
    FastVecSub(edge, &D_L00_00254A60[1], &D_L00_00254A60[0]);
    vec_scale_to_length(edge, edge, D_L00_001B0E90);
    if (math_random_int_below(2) == 0) {
        vec_scale_to_length(side, object + 0xD0, D_L00_001B0E9C);
        FastVecAdd(temp, &D_L00_00254A60[0], side);
        {
            Colors colors = D_L00_001B0EC8;
            float up[4], side[4];
            int color, count;
            float a, b;
        color = colors.c[math_random_int_below(5)];
        a = math_random_signed_float_range(0.0f, D_L00_001B0E98);
        b = math_random_signed_float_range(0.0f, D_L00_001B0E98);
        math_apply_axis_rotation_to_quat(up, edge, D_0018A0E0, b);
        FastVecCross(side, edge, D_0018A0E0);
        math_apply_axis_rotation_to_quat(up, up, side, a);
        count = FloatToInt(dist * 1.2f / D_L00_001B0E90);
        if (*(char **)(obj + 0x10) != 0) count *= 3;
        p = part_spawn_owned_particle(scale * 0.1f, scale, temp, count, color, 0, sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        p = part_spawn_owned_particle(scale * 0.07f, scale * 0.7f, temp, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(obj + 0x10));
        if (p) p->b2 = D_L00_001FEAC4[0][6];
        }
    }
    if (math_fast_float_d(&D_L00_001B2D3C)) {
        D_L00_001B2D3C = D_L00_001B0EA0;
        for (k = 0; k < 3; k++) {
            if (D_L00_001B2D30[k] == 0) {
                D_L00_001B2D30[k] = 1;
                D_L00_001B2CF0[k] = D_L00_001B0EA8;
                D_L00_001B2D10[k] = 0;
                D_L00_001B2D20[k] = D_L00_001B0EB8;
                D_L00_001B2D00[k] = IntToFloat(D_L00_001B0EBF);
                qcopy(&D_L00_001B2C90[k], obj);
                FastVecSub(side, &D_L00_00254A60[1], &D_L00_00254A60[0]);
                vec_scale_to_length(&D_L00_001B2CC0[k], side, 1.0f);
                break;
            }
        }
    }
    {
    for (kk = 0; kk < 3; kk++) {
        if (D_L00_001B2D30[kk] != 0) {
            if (math_fast_float_d(&D_L00_001B2CF0[kk]) != 0) {
                D_L00_001B2D30[kk] = 0;
            } else {
                float step, u, rem, inv;
                float sample[4];
                if (D_L00_001B2CF0[kk] < D_L00_001B0EAC) D_L00_001B2D00[kk] -= D_L00_001B0EC4;
                step = D_L00_001B0EA4 * 0.016666668f;
                D_L00_001B2D10[kk] += step;
                u = D_L00_001B2D10[kk] / D_L00_001B0E38;
                if (u > 1.0f) u = 1.0f;
                D_L00_001B2D20[kk] = D_L00_001B0EB8 + (D_L00_001B0EB4 - D_L00_001B0EB8) * u;
                if (D_L00_001B2D10[kk] >= D_L00_001B0E38) {
                    FastVecScale(side, &D_L00_001B2CC0[kk], step);
                    FastVecAdd(&D_L00_001B2C90[kk], &D_L00_001B2C90[kk], side);
                } else {
                    seg = FloatToInt(D_L00_001B2D10[kk] / D_L00_001B2C80);
                    rem = D_L00_001B2D10[kk] - IntToFloat(seg) * D_L00_001B2C80;
                    qcopy(&D_L00_001B2C90[kk], &D_L00_00254A60[seg]);
                    if (seg == 11) FastVecSub(side, &D_L00_00254A60[seg], &D_L00_00254A60[seg + -1]);
                    else FastVecSub(side, &D_L00_00254A60[seg + 1], &D_L00_00254A60[seg]);
                    inv = FastVecLength(side);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(sample, side, rem * inv);
                        FastVecAdd(&D_L00_001B2C90[kk], &D_L00_001B2C90[kk], sample);
                        vec_scale_to_length(sample, side, inv);
                        lerp_vector(&D_L00_001B2CC0[kk], &D_L00_001B2CC0[kk], sample, 0.1f);
                        vec_scale_to_length(&D_L00_001B2CC0[kk], &D_L00_001B2CC0[kk], 1.0f);
                    }
                }
            }
        }
    }
    }
}
