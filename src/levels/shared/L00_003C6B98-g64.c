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

extern Colors D_L00_001B0048 NOT_SDA;

extern PlayerView g_hero_state;
extern char D_0018A0E0[];
extern Collision g_collision_result;
extern float D_L00_001A8F20;
extern unsigned char *D_L00_001FEAC4[];
extern signed char D_L00_001B003F;

extern float D_L00_001AFFA4 __attribute__((sda));
extern float D_L00_001AFFCC __attribute__((sda));
extern float D_L00_001AFFD4 __attribute__((sda));
extern float D_L00_001AFFD8 __attribute__((sda));
extern float D_L00_001AFFE0 __attribute__((sda));
extern float D_L00_001AFFE4 __attribute__((sda));
extern float D_L00_001AFFE8 __attribute__((sda));
extern float D_L00_001B0008 __attribute__((sda));
extern float D_L00_001B000C __attribute__((sda));
extern float D_L00_001B0010 __attribute__((sda));
extern float D_L00_001B0018 __attribute__((sda));
extern float D_L00_001B001C __attribute__((sda));
extern int D_L00_001AFFD0 __attribute__((sda));
extern int D_L00_001B0020 __attribute__((sda));
extern int D_L00_001B0028 __attribute__((sda));
extern int D_L00_001B002C __attribute__((sda));
extern float D_L00_001B0024 __attribute__((sda));
extern float D_L00_001B0034 __attribute__((sda));
extern float D_L00_001B0038 __attribute__((sda));
extern float D_L00_001B0044 __attribute__((sda));

extern float D_L00_001B2A10;
extern float D_L00_001B2A14;
extern Vec D_L00_001B2A20[3];
extern Vec D_L00_001B2A50[3];
extern int D_L00_001B2A80[3];
extern float D_L00_001B2A90[3];
extern float D_L00_001B2AA0[3];
extern float D_L00_001B2AB0[3];
extern int D_L00_001B2AC0[3];
extern int D_L00_001B2ACC;

extern Vec D_L00_002403C0[];
extern Vec D_L00_00240480[];
extern Vec D_L00_00240540[];
extern Vec D_L00_00240600[][20];

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
    float pull[4], segment[4], spin[4], endPoint[4], scratch[4];
    char *disabled[128];
    float delta[4], sideways[4];
    char *vars;
    char *targetInfo = 0;
    float dist, fraction = 0.0f, blend, radius, angle, along, segLength = 0.0f, scale;
    int disabledCount, tries, j = 0, sparkSlot = 0, sparkIndex = 0, index = 0, sign = 0, segmentIndex = 0;
    Particle *particle = 0;

    spin[3] = 1.0f;
    vars = *(char **)(owner + 0x68);
    *(int *)spin = 0;
    ResetBeamChainAndPulseState(owner);
    D_L00_001B2A14 = math_wrap_angle_to_pi(D_L00_001B2A14 + D_L00_001AFFD4);
    vec_scale_to_length(pull, owner + 0xD0, -D_L00_001B2A10);
    if (*(char **)(vars + 0x10) != 0 && (targetInfo = moby_get_private_value_0(*(char **)(vars + 0x10))) != 0) {
        FastVecScale(scratch, *(char **)(vars + 0x10) + 0xE0, *(float *)(targetInfo + 0x10));
        FastVecAdd(endPoint, *(char **)(vars + 0x10) + 0x10, scratch);
    } else {
        float x = *(float *)(vars + 0x48), y = *(float *)(vars + 0x4C);
        vec_build_spherical_offset(endPoint, D_L00_001AFFA4, x, y);
        FastVecAdd(endPoint, endPoint, vars);
    }
    disabledCount = 0;
    dist = D_L00_001AFFA4;
    tries = 0;
    if (*(char **)(vars + 0x10) == 0) {
        qcopy(scratch, vars);
        while (CollLine(scratch, endPoint, 0x14, g_hero_state.object, 0)) {
            Collision *col;
            char *hit;
            if (++tries >= 7) break;
            col = &g_collision_result;
            if (g_collision_result.hit != 0 && (*(short *)(g_collision_result.hit + 0xAA) == 0xE7D /* Sheep */ || *(short *)(g_collision_result.hit + 0xAA) == 0xEB0 /* Dark Sheep */)) {
                disabled[disabledCount++] = g_collision_result.hit;
                *(int *)(g_collision_result.hit + 0x98) = 0;
                if (disabledCount < 128) {
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
        for (index = 0; index < disabledCount; index++) {
            *(int *)(disabled[index] + 0x98) = *(int *)(*(char **)(disabled[index] + 0x24) + 0x10);
        }
    } else {
        FastVecSub(scratch, vars, *(char **)(vars + 0x10) + 0x10);
        along = FastVecDot(g_hero_state.object + 0xE0, scratch);
        FastVecScale(delta, g_hero_state.object + 0xE0, along);
        FastVecSub(sideways, scratch, delta);
        dist = FastVecLength(sideways);
    }
    D_L00_001B2A10 = dist * D_L00_001AFFCC;
    qcopy(&D_L00_002403C0[0], vars);
    qcopy(&D_L00_00240480[0], vars);
    qcopy(&D_L00_00240540[0], vars);
    {
    int i;
    for (i = 1; i < 12; i++) {
        vec_transform_or_copy(&D_L00_002403C0[i], &D_L00_002403C0[i]);
        FastVecSub(segment, &D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        fraction = IntToFloat(i) * D_L00_001AFFCC;
        blend = fraction * -0.49999997f + 0.9f;
        if (D_L00_001AFFD0 < i && *(char **)(vars + 0x10) != 0) {
            FastVecSub(scratch, *(char **)(vars + 0x10) + 0x10, &D_L00_002403C0[i]);
            vec_scale_to_length(scratch, scratch, D_L00_001B2A10);
            lerp_vector(pull, pull, scratch, 0.2f);
        }
        lerp_vector(scratch, segment, pull, blend);
        segLength = FastVecLength(scratch);
        if (segLength == 0.0f) {
            qcopy(&D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        } else {
            FastVecScale(scratch, scratch, D_L00_001B2A10 / segLength);
            FastVecAdd(&D_L00_002403C0[i], &D_L00_002403C0[i - 1], scratch);
        }
        FastVecSub(delta, &D_L00_002403C0[i], &D_L00_002403C0[i - 1]);
        FastVecCross(sideways, delta, D_0018A0E0);
        vec_scale_to_length(sideways, sideways, D_L00_001AFFE4 + (D_L00_001AFFE8 - D_L00_001AFFE4) * fraction);
        {
        float offset[4];
        float m[4][4];
        for (j = 0; j < 20; j++) {
            math_apply_axis_rotation_to_quat(offset, sideways, delta, (float)j * D_L00_001AFFE0);
            FastVecAdd(&D_L00_00240600[i][j], offset, &D_L00_002403C0[i]);
        }
        qcopy(m[3], &D_L00_002403C0[i]);
        vec_scale_to_length(m[0], delta, 1.0f);
        vec_scale_to_length(m[1], sideways, 1.0f);
        FastVecCross(m[2], m[1], m[0]);
        radius = D_L00_001B0008 + (D_L00_001B000C - D_L00_001B0008) * fraction;
        angle = math_wrap_angle_to_pi(D_L00_001B2A14 + D_L00_001AFFD8 * IntToFloat(i));
        spin[1] = radius * math_fast_sin_or_cos_b(angle);
        spin[2] = radius * math_fast_sin_or_cos_a(angle);
        transform_vector(&D_L00_00240480[i], spin, m);
        spin[2] = -spin[2];
        transform_vector(&D_L00_00240540[i], spin, m);
        }
    }
    }
    ref_L00_003C6B98_00(DrawBeamRingAndRailEffects, owner);
    scale = math_random_float_range(0.1f, 1.7f);
    sign = math_random_int_below(2);
    if (sign == 0) sign = sign - 1;
    if (math_random_int_below(2) == 0) {
        qcopy_nc(scratch, &D_L00_00240480[11]);
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.1f, scale, 0x7F10107F, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (particle) particle->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (particle) particle->b2 = D_L00_001FEAC4[0][7];
    }
    if (math_random_int_below(2) == 0) {
        qcopy_nc(scratch, &D_L00_00240540[11]);
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.1f, scale, 0x7F104FFF, 0, sign, &D_L00_001A8F20, 0.003f, 1);
        if (particle) particle->b2 = D_L00_001FEAC4[0][7];
        sign = -sign;
        particle = part_spawn_ground_effect(scratch, 0x1E, scale * 0.07f, scale * 0.7f, 0x7F7F7F7F, 1, sign, &D_L00_001A8F20, 0.003f, 1);
        if (particle) particle->b2 = D_L00_001FEAC4[0][7];
    }
    FastVecSub(delta, &D_L00_002403C0[1], &D_L00_002403C0[0]);
    vec_scale_to_length(delta, delta, D_L00_001B0010);
    if (math_random_int_below(2) == 0) {
        vec_scale_to_length(sideways, owner + 0xD0, D_L00_001B001C);
        FastVecAdd(scratch, &D_L00_002403C0[0], sideways);
        {
            Colors colors = D_L00_001B0048;
            float up[4], side[4];
            int color, count;
            float a, b;
        color = colors.c[math_random_int_below(5)];
        a = math_random_signed_float_range(0.0f, D_L00_001B0018);
        b = math_random_signed_float_range(0.0f, D_L00_001B0018);
        math_apply_axis_rotation_to_quat(up, delta, D_0018A0E0, b);
        FastVecCross(side, delta, D_0018A0E0);
        math_apply_axis_rotation_to_quat(up, up, side, a);
        count = FloatToInt(dist * 1.2f / D_L00_001B0010);
        if (*(char **)(vars + 0x10) != 0) count *= 3;
        particle = part_spawn_owned_particle(scale * 0.1f, scale, scratch, count, color, 0, sign, up, *(int *)(vars + 0x10));
        if (particle) particle->b2 = D_L00_001FEAC4[0][6];
        particle = part_spawn_owned_particle(scale * 0.07f, scale * 0.7f, scratch, count, 0x7F7F7F7F, 1, -sign, up, *(int *)(vars + 0x10));
        if (particle) particle->b2 = D_L00_001FEAC4[0][6];
        }
    }
    if (math_fast_float_d(&D_L00_001B2ACC)) {
        D_L00_001B2ACC = D_L00_001B0020;
        for (sparkSlot = 0; sparkSlot < 3; sparkSlot++) {
            if (D_L00_001B2AC0[sparkSlot] == 0) {
                D_L00_001B2AC0[sparkSlot] = 1;
                D_L00_001B2A80[sparkSlot] = D_L00_001B0028;
                D_L00_001B2AA0[sparkSlot] = 0;
                D_L00_001B2AB0[sparkSlot] = D_L00_001B0038;
                D_L00_001B2A90[sparkSlot] = IntToFloat(D_L00_001B003F);
                qcopy(&D_L00_001B2A20[sparkSlot], vars);
                FastVecSub(sideways, &D_L00_002403C0[1], &D_L00_002403C0[0]);
                vec_scale_to_length(&D_L00_001B2A50[sparkSlot], sideways, 1.0f);
                break;
            }
        }
    }
    {
    for (sparkIndex = 0; sparkIndex < 3; sparkIndex++) {
        if (D_L00_001B2AC0[sparkIndex] != 0) {
            if (math_fast_float_d(&D_L00_001B2A80[sparkIndex]) != 0) {
                D_L00_001B2AC0[sparkIndex] = 0;
            } else {
                float step, u, rem, inv;
                float offset[4];
                if (D_L00_001B2A80[sparkIndex] < D_L00_001B002C) D_L00_001B2A90[sparkIndex] -= D_L00_001B0044;
                step = D_L00_001B0024 * 0.016666668f;
                D_L00_001B2AA0[sparkIndex] += step;
                u = D_L00_001B2AA0[sparkIndex] / D_L00_001AFFA4;
                if (u > 1.0f) u = 1.0f;
                D_L00_001B2AB0[sparkIndex] = D_L00_001B0038 + (D_L00_001B0034 - D_L00_001B0038) * u;
                if (D_L00_001B2AA0[sparkIndex] >= D_L00_001AFFA4) {
                    FastVecScale(sideways, &D_L00_001B2A50[sparkIndex], step);
                    FastVecAdd(&D_L00_001B2A20[sparkIndex], &D_L00_001B2A20[sparkIndex], sideways);
                } else {
                    segmentIndex = FloatToInt(D_L00_001B2AA0[sparkIndex] / D_L00_001B2A10);
                    rem = D_L00_001B2AA0[sparkIndex] - IntToFloat(segmentIndex) * D_L00_001B2A10;
                    qcopy(&D_L00_001B2A20[sparkIndex], &D_L00_002403C0[segmentIndex]);
                    if (segmentIndex == 11) FastVecSub(sideways, &D_L00_002403C0[segmentIndex], &D_L00_002403C0[segmentIndex + -1]);
                    else FastVecSub(sideways, &D_L00_002403C0[segmentIndex + 1], &D_L00_002403C0[segmentIndex]);
                    inv = FastVecLength(sideways);
                    if (inv != 0.0f) {
                        inv = 1.0f / inv;
                        FastVecScale(offset, sideways, rem * inv);
                        FastVecAdd(&D_L00_001B2A20[sparkIndex], &D_L00_001B2A20[sparkIndex], offset);
                        vec_scale_to_length(offset, sideways, inv);
                        lerp_vector(&D_L00_001B2A50[sparkIndex], &D_L00_001B2A50[sparkIndex], offset, 0.1f);
                        vec_scale_to_length(&D_L00_001B2A50[sparkIndex], &D_L00_001B2A50[sparkIndex], 1.0f);
                    }
                }
            }
        }
    }
    }
}
