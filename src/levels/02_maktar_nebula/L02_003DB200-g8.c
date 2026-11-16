#include "include_asm.h"
#include "names.h"

/* func_L02_003DB200 is a unit of its own: retail clears its first vector as plain C, with the
   zero materialised (`por $v0,$zero,$zero` ... `sq $v0,0($sp)`), which -frac2-zero-ti-por keeps
   (config/cflags.txt). */

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

/* Spawns a spray of sparks at joint 4 of the boss's part, pushed away from the hero. */
void boss_spawn_joint_sparks(char *moby) {
    float launchVelocity[4];
    float jointPos[4];
    float awayDir[4];

    *(TI128 *)launchVelocity = 0;
    moby_transform_joint_to_world((char *)(g_moby_l02_pool + (*(int *)(*(char **)(moby + 0x68) + 0x244) << 8)), 4, jointPos);
    jointPos[2] = jointPos[2] + g_boss_spark_height_offset;
    FastVecSub(awayDir, g_camera_l02_position, jointPos);
    awayDir[2] = 0.0f;
    vec_scale_to_length(awayDir, awayDir, g_boss_spark_away_speed);
    FastVecAdd(jointPos, jointPos, awayDir);
    vec_add_random_offset(jointPos, g_boss_spark_jitter);
    launchVelocity[2] = math_random_float_range(g_boss_spark_speed_min, g_boss_spark_speed_max) * 0.016666668f;
    enemy_spawn_record(jointPos, launchVelocity, &g_boss_spark_spawn_record, math_random_int_below(2), 1);
}
