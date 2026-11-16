#include "include_asm.h"
#include "common.h"

typedef float V4_L11_447018[4] __attribute__((aligned(16)));

typedef struct {
    float head[2];
    s32 flag;
    s32 pad;
    V4_L11_447018 pos;
} L11_447018_Spark;

extern char *arena_get_center_point(char *);
extern void vec_add_random_offset(void *, float);
extern void vec_clear_128(void *);
extern float math_random_float_range(float, float);
extern s32 math_random_int_below(s32);
extern s32 math_random_int_range(s32, s32);
extern void *enemy_spawn_record(void *, void *, void *, s32, s32);

extern s32 g_object_spark_chance __attribute__((sda));
extern s32 g_object_spark_type_min __attribute__((sda));
extern s32 g_object_spark_type_max __attribute__((sda));
extern float g_object_spark_speed_min __attribute__((sda));
extern float g_object_spark_speed_max __attribute__((sda));
extern float g_object_spark_pos_jitter __attribute__((sda));
extern float g_object_spark_height_offset __attribute__((sda));
extern char g_object_spark_record_name[8] __attribute__((sda));

/* Emits count sparks at the object, then one more unless the chance roll says no. */
void part_emit_object_sparks(char *obj, s32 count)
{
    L11_447018_Spark spark;
    s32 i;

    for (i = 0; i < count; i++) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, g_object_spark_pos_jitter);
        spark.pos[2] += g_object_spark_height_offset;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(g_object_spark_speed_min, g_object_spark_speed_max) * 0.016666668f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, g_object_spark_record_name, math_random_int_below(2), math_random_int_range(g_object_spark_type_min, g_object_spark_type_max));
    }
    if (math_random_int_below(g_object_spark_chance) == 0) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, g_object_spark_pos_jitter);
        spark.pos[2] += g_object_spark_height_offset;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(g_object_spark_speed_min, g_object_spark_speed_max) * 0.016666668f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, g_object_spark_record_name, math_random_int_below(2), math_random_int_range(g_object_spark_type_min, g_object_spark_type_max));
    }
}
