#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));
extern float g_boss_spark_spawn_record __attribute__((sda));
extern float g_boss_spark_jitter __attribute__((sda));
extern float g_boss_spark_speed_min __attribute__((sda));
extern float g_boss_spark_speed_max __attribute__((sda));
extern float g_boss_spark_height_offset __attribute__((sda));
extern float g_boss_spark_away_speed __attribute__((sda));
extern int g_moby_l02_pool;
extern float g_camera_l02_position[4];
extern void moby_transform_joint_to_world(char *, int, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_add_random_offset(void *, float);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void *enemy_spawn_record(void *, void *, void *, int, int);

void boss_spawn_joint_sparks_pal(char *arg0) {
    float a[4];
    float b[4];
    float c[4];

    *(TI128 *)a = 0;
    moby_transform_joint_to_world((char *)(g_moby_l02_pool + (*(int *)(*(char **)(arg0 + 0x68) + 0x244) << 8)), 4, b);
    b[2] = b[2] + g_boss_spark_height_offset;
    FastVecSub(c, g_camera_l02_position, b);
    c[2] = 0.0f;
    vec_scale_to_length(c, c, g_boss_spark_away_speed);
    FastVecAdd(b, b, c);
    vec_add_random_offset(b, g_boss_spark_jitter);
    a[2] = math_random_float_range(g_boss_spark_speed_min, g_boss_spark_speed_max) * 0.020000001f;
    enemy_spawn_record(b, a, &g_boss_spark_spawn_record, math_random_int_below(2), 1);
}
