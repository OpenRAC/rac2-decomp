#include "include_asm.h"
#include "names.h"

typedef int V4_L00_004170A8 __attribute__((mode(TI)));
extern char g_spark_l00_records[];
extern V4_L00_004170A8 g_hero_l00_position;
extern int math_fast_float_d(void *);
extern void part_emit_spark_burst_at_moby_pal(char *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void spark_record_claim_pal(char *, void *, int);
extern void spark_records_update(char *);
extern void part_spawn_drifting_particles_pal(char *);
extern void beam_glow_sprites_update_owned_pal(char *);
extern void moby_mark_spawned(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);

/* Updates the spark effect object (moby class 5022). Each frame it picks a random spot nearby for a new spark, and when its time is up it frees all the sparks and removes itself. */
void spark_l00_effect_update_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    V4_L00_004170A8 end_point;
    float azimuth, elevation;
    int i;
    char *record;
    if (math_fast_float_d(state) == 0) {
        if (*(int *)(state + 4) == 0)
            part_emit_spark_burst_at_moby_pal(object);
        if (*(int *)(state + 4) == 0) {
            azimuth = math_random_angle();
            elevation = math_random_angle();
            vec_build_spherical_offset(&end_point, 7.0f, azimuth, elevation);
        } else {
            azimuth = math_random_angle();
            elevation = math_random_angle();
            vec_build_spherical_offset(&end_point, 5.0f, azimuth, elevation);
        }
        FastVecAdd(&end_point, &end_point, object + 0x10);
        if (CollLine(object + 0x10, &end_point, 0, object, 0) != 0)
            end_point = g_hero_l00_position;
        spark_record_claim_pal(object, &end_point, 17);
        spark_records_update(object);
        ref_L00_004170A8_00(beam_glow_sprites_update_owned_pal, object);
    } else {
        record = g_spark_l00_records;
        record += 0x106C;
        for (i = 23; i >= 0; --i, record -= 0xB0)
            *(int *)record = 0;
        if (*(int *)(state + 4) == 0)
            part_spawn_drifting_particles_pal(object);
        moby_mark_spawned(object);
    }
}

typedef int CurveWord128 __attribute__((mode(TI)));
typedef union { CurveWord128 word; float values[4]; } CurveVector;
extern float IntToFloat(int);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_range(int, int);
extern void ref_L00_00417868_00(void *, void *, void *, void *, void *, float);
extern void ref_L00_00417868_01(void *, int, void *, int);

/* Builds a jagged lightning bolt of 25 points between two ends, with small random wobble, and draws it (PAL: lower threshold, 8). */
void lightning_bolt_build_jittered_b_pal(char *object, char *state) {
    CurveVector points[25];
    CurveVector start, end, jitter;
    int i;
    float t;
    for (i = 0; i < 24; i++) {
        t = IntToFloat(i) / IntToFloat(23);
        start.word = *(CurveWord128 *)state;
        end.word = *(CurveWord128 *)(state + 0x10);
        FastVecAdd(&start, &start, state + 0x20);
        FastVecAdd(&end, &end, state + 0x30);
        ref_L00_00417868_00(&points[i], state + 0x20, state + 0x30, &start, &end, t);
        jitter.values[3] = 0;
        jitter.values[0] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[1] = math_random_float_range(-1.0f, 1.0f);
        jitter.values[2] = math_random_float_range(-1.0f, 1.0f);
        vec_scale_to_length(&jitter, &jitter, 0.075f);
        FastVecAdd(&points[i], &points[i], &jitter);
    }
    if (*(int *)(state + 0x98) >= 8)
        ref_L00_00417868_01(object, math_random_int_range(0x40, 0x80), points, 25);
    else
        ref_L00_00417868_01(object, math_random_int_range(0, 0x40), points, 25);
}
