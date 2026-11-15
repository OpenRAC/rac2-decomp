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

extern s32 D_L11_001B1950 __attribute__((sda));
extern s32 D_L11_001B1954 __attribute__((sda));
extern s32 D_L11_001B1958 __attribute__((sda));
extern float D_L11_001B195C __attribute__((sda));
extern float D_L11_001B1960 __attribute__((sda));
extern float D_L11_001B1964 __attribute__((sda));
extern float D_L11_001B1968 __attribute__((sda));
extern char D_L11_001B1990[8] __attribute__((sda));

/* Emits count sparks at the object, then one more unless the chance roll says no. */
void part_emit_object_sparks(char *obj, s32 count)
{
    L11_447018_Spark spark;
    s32 i;

    for (i = 0; i < count; i++) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, D_L11_001B1964);
        spark.pos[2] += D_L11_001B1968;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(D_L11_001B195C, D_L11_001B1960) * 0.016666668f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, D_L11_001B1990, math_random_int_below(2), math_random_int_range(D_L11_001B1954, D_L11_001B1958));
    }
    if (math_random_int_below(D_L11_001B1950) == 0) {
        qcopy(spark.pos, arena_get_center_point(obj));
        vec_add_random_offset(spark.pos, D_L11_001B1964);
        spark.pos[2] += D_L11_001B1968;
        vec_clear_128(&spark);
        vec_add_random_offset(&spark, math_random_float_range(D_L11_001B195C, D_L11_001B1960) * 0.016666668f);
        spark.flag = 0;
        enemy_spawn_record(spark.pos, &spark, D_L11_001B1990, math_random_int_below(2), math_random_int_range(D_L11_001B1954, D_L11_001B1958));
    }
}
