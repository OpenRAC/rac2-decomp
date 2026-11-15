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
extern u8 *part_spawn_velocity_particle(void *, void *, unsigned int, int, float);
extern void *SpawnJointFollowParticle(void *, unsigned int, int, int, float);
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
void homing_l04_shot_update(unsigned char *moby)
{
    float prev_pos[4];
    TurnRecord turn = *(TurnRecord *)D_L04_001B0448;
    SweepProbe probe;
    float delta[4], spark_dir[4], spark[4], velocity[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68), *particle;
    int i, trail_index, shot_age;
    unsigned char **trail;
    float scale, length;
    qcopy(prev_pos, (moby + 0x10));
    FastVecAdd(moby + 0x10, moby + 0x10, vars);
    if (*(float *)(moby + 0x10) < 0 || *(float *)(moby + 0x14) < 0 ||
        *(float *)(moby + 0x18) < 0 || 64.0f < vec_distance_xy(moby + 0x10, D_L04_001B9680)) {
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
    if (CollLine(prev_pos, moby + 0x10, 0, *(void **)(vars + 0x18), &probe)) {
        if (!GetCollHitMaterial()) {
            if (*(int *)(vars + 0x10) >= 4) *(int *)(vars + 0x10) = 3;
        } else {
            qcopy((moby + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)spark_dir = 0;
                spark_dir[0] = math_random_float_range(-1, 1);
                spark_dir[1] = math_random_float_range(-1, 1);
                spark_dir[2] = math_random_float_range(-1, 1);
                *(QuadWord *)delta = *(QuadWord *)spark_dir;
                vec_fast_normalize(spark_dir, vars, D_L04_001BFB00);
                vec_scale_to_length((char *)delta, (char *)delta, FastVecLength(spark_dir) * 0.5f);
                FastVecAdd(spark_dir, spark_dir, delta);
                vec_scale_to_length((char *)spark_dir, (char *)spark_dir, math_random_float_range(0.050000004f, 0.10000001f));
                part_spawn_velocity_particle(moby + 0x10, spark_dir, 0x7F2F4F6F, math_random_int_range(10, 15), 30000);
            }
            moby_destroy_effects_with_burst(moby, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    *(float *)(moby + 0xF4) = FastAddRotations(*(float *)(moby + 0xF4), ((float *)&turn)[1]);
    shot_age = *(int *)(vars + 0x14) - *(int *)(vars + 0x10);
    if (shot_age < 13) scale = (IntToFloat(shot_age) / IntToFloat(13)) * 0.15f;
    else scale = 0.15f;
    FastVecSub(delta, prev_pos, moby + 0x10);
    vec_scale_to_length((char *)delta, (char *)delta, scale);
    qcopy(spark_dir, (moby + 0x10));
    { unsigned char *head = *(unsigned char **)(vars + 0x1C);
      if (head) qcopy(head + 0x10, spark_dir); }
    for (trail_index = 0; trail_index < 16; trail_index++) {
        particle = ((unsigned char **)(vars + 0x20))[trail_index];
        if (particle) {
            FastVecAdd(particle + 0x10, spark_dir, delta);
            qcopy(spark_dir, (particle + 0x10));
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
            FastVecScale(velocity, spark, math_random_float_range(0.008333334f, 0.033333335f) / length);
            part_spawn_velocity_particle(moby + 0x10, velocity, 0x7F2F4F6F, math_random_int_range(10, 15), 30000);
        }
    }
}
