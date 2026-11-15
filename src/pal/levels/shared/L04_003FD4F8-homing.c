#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *CreateMoby(void *);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern void vec_scale_to_length(char *, char *, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern int math_fast_float_d(void *);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[];
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecLength(void *);
extern int math_random_int_range(int, int);
extern void part_spawn_velocity_particle(void *, void *, unsigned int, int, float);
extern void SpawnJointFollowParticle(void *, unsigned int, int, int, float);
extern unsigned char *part_spawn_random_effect_record(void *, void *, int, float);
extern void moby_destroy_effects_with_burst(void *, int);
extern void moby_mark_spawned(void *);
extern float cubic_hermite_scalar(float, float, float, float, float);
extern char D_L04_001B0448[];
extern char D_L04_001B9680[];
extern char D_L04_001B98D0[];
extern float vec_distance_xy(void *, void *);
extern int GetCollHitMaterial(void);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
typedef struct __attribute__((packed, aligned(4))) { long a; int b; } TurnRecord;

/* Moves a homing shot with its trail of followers; breaks up on contact, on timeout or out of bounds. */
void func_PAL_L04_003FD8F0(unsigned char *m)
{
    float old[4];
    TurnRecord turn = *(TurnRecord *)D_L04_001B0448;
    SweepProbe probe;
    float delta[4], random[4], spark[4], velocity[4];
    unsigned char *v = *(unsigned char **)(m + 0x68), *particle;
    int i, count, age;
    unsigned char **trail;
    float scale, length;
    qcopy(old, (m + 0x10));
    FastVecAdd(m + 0x10, m + 0x10, v);
    if (*(float *)(m + 0x10) < 0 || *(float *)(m + 0x14) < 0 ||
        *(float *)(m + 0x18) < 0 || 64.0f < vec_distance_xy(m + 0x10, D_L04_001B9680)) {
        moby_destroy_effects_with_burst(m, 0);
        moby_mark_spawned(m);
        return;
    }
    probe.owner = *(void **)(v + 0x18);
    probe.flags = 0x30000;
    probe.radius = 13;
    probe.active = 1;
    *(QuadWord *)probe.v = *(QuadWord *)v;
    vec_fast_normalize_helper(&probe, &probe, 1);
    probe.v[2] = 1;
    probe.v[3] = 5627.9248046875f;
    probe.mode = 1;
    probe.enabled = 1;
    probe.kind = *(unsigned short *)(m + 0xAA);
    if (math_fast_float_d(v + 0x10)) {
        moby_destroy_effects_with_burst(m, 0);
        moby_mark_spawned(m);
        return;
    }
    if (CollLine(old, m + 0x10, 0, *(void **)(v + 0x18), &probe)) {
        if (!GetCollHitMaterial()) {
            if (*(int *)(v + 0x10) >= 3) *(int *)(v + 0x10) = 2;
        } else {
            qcopy((m + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = math_random_float_range(-1, 1);
                random[1] = math_random_float_range(-1, 1);
                random[2] = math_random_float_range(-1, 1);
                *(QuadWord *)delta = *(QuadWord *)random;
                vec_fast_normalize(random, v, D_L04_001BFB00);
                vec_scale_to_length((char *)delta, (char *)delta, FastVecLength(random) * 0.5f);
                FastVecAdd(random, random, delta);
                vec_scale_to_length((char *)random, (char *)random, math_random_float_range(0.060000002f, 0.120000005f));
                part_spawn_velocity_particle(m + 0x10, random, 0x7F2F4F6F, math_random_int_range(8, 12), 30000);
            }
            moby_destroy_effects_with_burst(m, 0);
            moby_mark_spawned(m);
            return;
        }
    }
    *(float *)(m + 0xF4) = FastAddRotations(*(float *)(m + 0xF4), ((float *)&turn)[1]);
    age = *(int *)(v + 0x14) - *(int *)(v + 0x10);
    if (age < 11) scale = (IntToFloat(age) / IntToFloat(11)) * 0.15f;
    else scale = 0.15f;
    FastVecSub(delta, old, m + 0x10);
    vec_scale_to_length((char *)delta, (char *)delta, scale);
    qcopy(random, (m + 0x10));
    { unsigned char *head = *(unsigned char **)(v + 0x1C);
      if (head) qcopy(head + 0x10, random); }
    for (count = 0; count < 16; count++) {
        particle = ((unsigned char **)(v + 0x20))[count];
        if (particle) {
            FastVecAdd(particle + 0x10, random, delta);
            qcopy(random, (particle + 0x10));
            *(float *)(particle + 0x10) += math_random_signed_float_range(0, 0.075f);
            *(float *)(particle + 0x14) += math_random_signed_float_range(0, 0.075f);
            *(float *)(particle + 0x18) += math_random_signed_float_range(0, 0.075f);
            FastVecScale(delta, delta, 0.85f);
        }
    }
    if (math_random_int_below(5) == 0) {
        FastVecCross(spark, delta, D_L04_001B98D0);
        math_apply_axis_rotation_to_quat(spark, spark, delta, math_random_signed_float_range(0, 3.1415927f));
        length = FastVecLength(spark);
        if (length != 0) {
            FastVecScale(velocity, spark, math_random_float_range(0.010000001f, 0.040000003f) / length);
            part_spawn_velocity_particle(m + 0x10, velocity, 0x7F2F4F6F, math_random_int_range(8, 12), 30000);
        }
    }
}
