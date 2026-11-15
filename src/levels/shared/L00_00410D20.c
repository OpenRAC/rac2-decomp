#include "common.h"
extern void tracked_target_offsets_update(void *);
extern void ref_L00_00410D20_00(void (*)(void *), void *);
extern void tumbling_pieces_update(void *);
extern void set_moby_color(void *, int, int, int);
extern int FastTweenColor(int, int, float);
extern float math_fast_sin_or_cos_a(float);
extern void target_apply_slot_color(void *);
extern void vec_clear_128(void *);
extern void tumbling_piece_spawn(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern int coll_process_hit(void *, int, void *, int, float);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char g_hero_state[];
extern ParticleEffectSlot ref_L00_00410D20_01[];
extern char *ref_L00_00410D20_02[];

/* Keeps up to 30 tracked targets lit with colour changes and little sparks, and cleans each one up when its target is gone. Also creates extra sparks when a target touches something. */
void target_spark_effect_update(char *moby) {
    float spark_dir_a[4], spark_dir_b[4];
    int i;

    qcopy_nc(moby + 0x10, g_hero_state);
    for (i = 0; i < 30; i++) {
        char *slot;
        char *hit_moby;
        int is_dead;

        if (!ref_L00_00410D20_01[i].target)
            continue;
        slot = (char *)&ref_L00_00410D20_01[i];
        *(float *)(slot + 0xC) = FastAddRotations(*(float *)(slot + 0xC), 0.20943954586982727f);
        is_dead = 0;
        if (*(signed char *)(*(char **)(slot + 0x18) + 0x20) < 0)
            is_dead = 1;
        if (!*(int *)(*(char **)(slot + 0x18) + 0x98))
            is_dead = 1;
        if (math_fast_float_d(slot))
            is_dead = 1;
        if (vec_fast_helper_b(slot + 0x1C)) {
            int count, j;
            char *target = *(char **)(slot + 0x18);

            *(float *)(slot + 0x1C) = *(float *)(slot + 0x14);
            count = coll_process_hit(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                hit_moby = ref_L00_00410D20_02[j];
                if ((*(unsigned short *)(hit_moby + 0x34) & 0x1000) && hit_moby &&
                    *(unsigned char *)(hit_moby + 0x20) != 254 && *(unsigned char *)(hit_moby + 0x20) != 253 &&
                    *(short *)(*(char **)(hit_moby + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (func_001163B0() % 11 == 0) {
            int j, count;

            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(spark_dir_a, x, y, z);
            }
            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(slot + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(spark_dir_b, x, y, z);
            }
            j = math_random_int_range(5, 15);
            count = math_random_int_range(15, 30);
            tumbling_piece_spawn(moby, *(char **)(slot + 0x18), *(char **)(slot + 0x18), spark_dir_a, spark_dir_b, 0, j, count, slot, 0.0f);
        }
        if (is_dead) {
            target_apply_slot_color(slot);
            *(char **)(slot + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        vec_clear_128(spark_dir_a);
        tumbling_piece_spawn(moby, *(char **)(slot + 0x18), hit_moby, spark_dir_a, spark_dir_a, 1, 10, 30, slot, *(float *)(slot + 0x10));
        tumbling_piece_spawn(moby, *(char **)(slot + 0x18), hit_moby, spark_dir_a, spark_dir_a, 0, 10, 30, slot, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(slot + 0x24) == 0) {
            int color = FastTweenColor(*(int *)(slot + 4), *(int *)(slot + 8),
                                  (math_fast_sin_or_cos_a(*(float *)(slot + 0xC)) + 1.0f) * 0.5f);

            set_moby_color(*(char **)(slot + 0x18), color & 255, (color >> 8) & 255, (color >> 16) & 255);
        } else
            --*(int *)(slot + 0x24);
    }
    tumbling_pieces_update(moby);
    ref_L00_00410D20_00(tracked_target_offsets_update, moby);
}
