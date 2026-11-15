#include "include_asm.h"
#include "names.h"
typedef int V4_L00_004170A8 __attribute__((mode(TI)));
extern char g_spark_l00_records[];
extern V4_L00_004170A8 D_L00_001BF220;
extern int math_fast_float_d(void *);
extern void part_emit_spark_burst_at_moby(char *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern void spark_record_claim(char *, void *, int);
extern void spark_records_update(char *);
extern void part_spawn_drifting_particles(char *);
extern void beam_glow_sprites_update_owned(char *);
extern void moby_mark_spawned(char *);
extern void ref_L00_004170A8_00(void (*)(char *), char *);

/* Updates the spark effect object (moby class 5022). Each frame it picks a random spot nearby for a new spark, and when its time is up it frees all the sparks and removes itself. */
void spark_l00_effect_update(char *object)
{
    char *state = *(char **)(object + 0x68);
    V4_L00_004170A8 target;
    float randA, randB;
    int i;
    char *record;
    if (math_fast_float_d(state) == 0) {
        if (*(int *)(state + 4) == 0)
            part_emit_spark_burst_at_moby(object);
        if (*(int *)(state + 4) == 0) {
            randA = math_random_angle();
            randB = math_random_angle();
            vec_build_spherical_offset(&target, 7.0f, randA, randB);
        } else {
            randA = math_random_angle();
            randB = math_random_angle();
            vec_build_spherical_offset(&target, 5.0f, randA, randB);
        }
        FastVecAdd(&target, &target, object + 0x10);
        if (CollLine(object + 0x10, &target, 0, object, 0) != 0)
            target = D_L00_001BF220;
        spark_record_claim(object, &target, 20);
        spark_records_update(object);
        ref_L00_004170A8_00(beam_glow_sprites_update_owned, object);
    } else {
        record = g_spark_l00_records;
        record += 0x106C;
        for (i = 23; i >= 0; --i, record -= 0xB0)
            *(int *)record = 0;
        if (*(int *)(state + 4) == 0)
            part_spawn_drifting_particles(object);
        moby_mark_spawned(object);
    }
}
