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
extern char g_spark_origin_quad[];
extern char g_scratch_direction_quad[];
extern char g_effect_default_params[];
extern void vec_fast_normalize(void *, void *, void *);
extern float FastVecLength(void *);
extern int math_random_int_range(int, int);
extern u8 *part_spawn_velocity_particle(void *, void *, unsigned int, int, float);
extern void *SpawnJointFollowParticle(void *, unsigned int, int, int, float);
extern unsigned char *part_spawn_random_effect_record(void *, void *, int, float);
extern void moby_destroy_effects_with_burst(void *, int);
extern void moby_mark_spawned(void *);
extern float cubic_hermite_scalar(float, float, float, float, float);
extern char g_homing_turn_record[];
extern char g_tether_zero_vec[];
extern char g_homing_cross_vec[];
extern float vec_distance_xy(void *, void *);
extern int GetCollHitMaterial(void);
extern float FastAddRotations(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
typedef struct __attribute__((packed, aligned(4))) { long a; int b; } TurnRecord;

/* Moves a homing shot with its trail of followers; breaks up on contact, on timeout or out of bounds. */
void homing_l04_shot_update_pal(unsigned char *moby)
{
    float old[4];
    TurnRecord turn = *(TurnRecord *)g_homing_turn_record;
    SweepProbe probe;
    float delta[4], random[4], spark[4], velocity[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68), *particle;
    int i, count, age;
    unsigned char **trail;
    float scale, length;
    qcopy(old, (moby + 0x10));
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    if (*(float *)(moby + 0x10) < 0 || *(float *)(moby + 0x14) < 0 ||
        *(float *)(moby + 0x18) < 0 || 64.0f < vec_distance_xy(moby + 0x10, g_tether_zero_vec)) {
        moby_destroy_effects_with_burst(moby, 0);
        moby_mark_spawned(moby);
        return;
    }
    probe.owner = *(void **)(vars + 0x18);
    probe.flags = 0x30000;
    probe.radius = 13;
    probe.active = 1;
    *(QuadWord *)probe.v = *(QuadWord *)vars;
    vec_fast_normalize_helper(&probe, &probe, 1);
    probe.v[2] = 1;
    probe.v[3] = 5627.9248046875f;
    probe.mode = 1;
    probe.enabled = 1;
    probe.kind = *(unsigned short *)(moby + 0xAA);
    if (math_fast_float_d(vars + 0x10)) {
        moby_destroy_effects_with_burst(moby, 0);
        moby_mark_spawned(moby);
        return;
    }
    if (CollLine(old, moby + 0x10, 0, *(void **)(vars + 0x18), &probe)) {
        if (!GetCollHitMaterial()) {
            if (*(int *)(vars + 0x10) >= 3) *(int *)(vars + 0x10) = 2;
        } else {
            qcopy((moby + 0x10), g_spark_origin_quad);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = math_random_float_range(-1, 1);
                random[1] = math_random_float_range(-1, 1);
                random[2] = math_random_float_range(-1, 1);
                *(QuadWord *)delta = *(QuadWord *)random;
                vec_fast_normalize(random, vars, g_scratch_direction_quad);
                vec_scale_to_length((char *)delta, (char *)delta, FastVecLength(random) * 0.5f);
                FastVecAdd(random, random, delta);
                vec_scale_to_length((char *)random, (char *)random, math_random_float_range(0.060000002f, 0.120000005f));
                part_spawn_velocity_particle(moby + 0x10, random, 0x7F2F4F6F, math_random_int_range(8, 12), 30000);
            }
            moby_destroy_effects_with_burst(moby, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), ((float *)&turn)[1]);
    age = *(int *)(vars + 0x14) - *(int *)(vars + 0x10);
    if (age < 11) scale = (IntToFloat(age) / IntToFloat(11)) * 0.15f;
    else scale = 0.15f;
    FastVecSub(delta, old, moby + 0x10);
    vec_scale_to_length((char *)delta, (char *)delta, scale);
    qcopy(random, (moby + 0x10));
    { unsigned char *head = *(unsigned char **)(vars + 0x1C);
      if (head) qcopy(head + 0x10, random); }
    for (count = 0; count < 16; count++) {
        particle = ((unsigned char **)(vars + 0x20))[count];
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
        FastVecCross(spark, delta, g_homing_cross_vec);
        math_apply_axis_rotation_to_quat(spark, spark, delta, math_random_signed_float_range(0, 3.1415927f));
        length = FastVecLength(spark);
        if (length != 0) {
            FastVecScale(velocity, spark, math_random_float_range(0.010000001f, 0.040000003f) / length);
            part_spawn_velocity_particle(moby + 0x10, velocity, 0x7F2F4F6F, math_random_int_range(8, 12), 30000);
        }
    }
}
