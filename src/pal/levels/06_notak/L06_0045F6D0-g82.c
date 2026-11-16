#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern char *part_spawn_object_following_effect(void *, void *, unsigned int, int, int, int, int, float, float, int);
extern void moby_set_state(char *, int, int);
extern void *part_find_owned_effect_slot(char *, int, int);
extern void moby_mark_spawned(char *);
extern void part_explode_object_into_pieces_pal(char *, void *, void *, void *, int, int, int, int, int, int, int);
extern void moby_compute_local_point(char *, void *, float, float, float);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void part_spawn_glow_fade_effects_pal(char *, void *, int, float, int, void *, float, unsigned int, float, float, int);
extern float g_spark_effect_param_b __attribute__((sda));
extern float g_spark_effect_param_c __attribute__((sda));
extern float g_spark_effect_param_a __attribute__((sda));
extern float g_spark_local_offset_x __attribute__((sda));
extern float g_spark_local_offset_y, g_spark_local_point_z;

/* Updates a spark effect object: once its effect ends it breaks into pieces and sparks, then removes itself. */
void spark_l06_effect_update_pal(char *moby) {
    float pos[4], vel[4];
    char *vars = *(char **)(moby + 0x68);
    int i;
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0: {
        float scale;
        *(u128 *)pos = 0;
        pos[2] = 3.75f;
        scale = *(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24);
        pos[2] *= scale;
        part_spawn_object_following_effect(pos, moby, 0x300033FF, -1, 1, -1, 0, scale * 525000.0f, 0.75f, -1);
        part_spawn_object_following_effect(pos, moby, 0x280033FF, -1, 0, -1, 0, scale * 525000.0f, 0.75f, -1);
        *(int *)(moby + 0x78) = -16192;
        moby_set_state(moby, 1, -1);
        /* fall through */
    }
    case 1:
        if (part_find_owned_effect_slot(moby, 0x4010000, 0) && *(int *)vars == 0) moby_set_state(moby, 2, -1);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        part_explode_object_into_pieces_pal(moby, &g_spark_effect_param_a, &g_spark_effect_param_b, &g_spark_effect_param_c, 0xFFFF, 0, -1, 6, 0xFF, 0xFF, 0);
        moby_compute_local_point(moby, pos, g_spark_local_offset_x, g_spark_local_offset_y, g_spark_local_point_z);
        SpawnExplosion_pal(pos, 0, 5, 5, 5, 20, 5, 0, 1, 1, 1, 0, 1.0f, 20.0f);
        for (i = 0; i < 4; i++) {
            vel[0] = (i / 2 * 2 - 1) * 0.060000002f;
            vel[1] = (i % 2 * 2 - 1) * 0.060000002f;
            vel[2] = 0.14000002f;
            matrix_mul_vec3(vel, vel, moby + 0xC0);
            part_spawn_glow_fade_effects_pal(moby, pos, 3, 0.2f, 1, vel, 5.0f, 0x7F40FFFF, 1.45f, 2.2f, 0);
        }
        moby_mark_spawned(moby);
        break;
    }
}
