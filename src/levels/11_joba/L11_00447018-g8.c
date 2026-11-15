#include "include_asm.h"
#include "common.h"

typedef float V4_L11_447018[4] __attribute__((aligned(16)));

typedef struct {
    float head[2];
    s32 flag;
    s32 pad;
    V4_L11_447018 pos;
} L11_447018_Spark;

extern char *func_L11_004417E8(char *);
extern void func_002ACB48(void *, float);
extern void func_00282C88(void *);
extern float func_002A7878(float, float);
extern s32 func_002A77E0(s32);
extern s32 func_002A7820(s32, s32);
extern void func_L02_003449D8(void *, void *, void *, s32, s32);

extern s32 D_L11_001B1950 __attribute__((sda));
extern s32 D_L11_001B1954 __attribute__((sda));
extern s32 D_L11_001B1958 __attribute__((sda));
extern float D_L11_001B195C __attribute__((sda));
extern float D_L11_001B1960 __attribute__((sda));
extern float D_L11_001B1964 __attribute__((sda));
extern float D_L11_001B1968 __attribute__((sda));
extern char D_L11_001B1990[8] __attribute__((sda));

/* Emits count sparks at the object, then one more unless the chance roll says no. */
void func_L11_00447018(char *obj, s32 count)
{
    L11_447018_Spark spark;
    s32 i;

    for (i = 0; i < count; i++) {
        qcopy(spark.pos, GetArenaCenterPoint(obj));
        AddRandomOffsetToVector(spark.pos, D_L11_001B1964);
        spark.pos[2] += D_L11_001B1968;
        ClearVector128(&spark);
        AddRandomOffsetToVector(&spark, RandomFloatRange(D_L11_001B195C, D_L11_001B1960) * 0.016666668f);
        spark.flag = 0;
        SpawnEnemyRecord(spark.pos, &spark, D_L11_001B1990, RandomIntBelow(2), RandomIntRange(D_L11_001B1954, D_L11_001B1958));
    }
    if (RandomIntBelow(D_L11_001B1950) == 0) {
        qcopy(spark.pos, GetArenaCenterPoint(obj));
        AddRandomOffsetToVector(spark.pos, D_L11_001B1964);
        spark.pos[2] += D_L11_001B1968;
        ClearVector128(&spark);
        AddRandomOffsetToVector(&spark, RandomFloatRange(D_L11_001B195C, D_L11_001B1960) * 0.016666668f);
        spark.flag = 0;
        SpawnEnemyRecord(spark.pos, &spark, D_L11_001B1990, RandomIntBelow(2), RandomIntRange(D_L11_001B1954, D_L11_001B1958));
    }
}
