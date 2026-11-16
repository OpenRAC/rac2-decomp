#include "include_asm.h"

#include "common.h"
#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)
extern float ref_L01_002E1680_00(float, float);
extern int ref_L01_002E1680_01(int, int, float);
extern void ref_L01_002E1680_02(float *, float, float);
extern void ref_L01_002E1680_03(float *, float *, float *);
extern char *ref_L01_002E1680_04(float, float *, float, float, float, int, float *, int, int);

/* Spawns count short-lived sparks at a position, each with a random spread, a direction from the matrix and a tint taken from the colour; optionally marks them with effect type 0x44. */
void part_l01_spawn_spark_burst_pal(float *position, float *matrix, int count, int color, int flag, float g, float h, float k) {
    float direction[4];
    float spread;
    int tint;
    char *spark;
    char *spark_data;
    int i;

    for (i = 0; i < count; i++) {
        spread = h * ref_L01_002E1680_00(70000.0f, 150000.0f);
        tint = ref_L01_002E1680_01(0, color, ref_L01_002E1680_00(0.2f, 1.0f));
        ref_L01_002E1680_02(direction, 0.0f, g);
        ref_L01_002E1680_03(direction, direction, matrix);
        spark = ref_L01_002E1680_04(h * 0.5f, position, 1.0f, k, spread, 0, direction, color, 0);
        if (spark != 0) {
            FLD(spark, s16, 0xA) = 0x64;
            spark_data = spark + 0x20;
            FLD(spark_data, int, 4) = 2;
            FLD(spark_data, u8, 0xA) = tint >> 24;
            FLD(spark_data, u8, 0xB) = FLD(spark, u8, 0xA);
            if (flag != 0) {
                FLD(spark, u8, 3) = 0x44;
            }
        }
    }
}

