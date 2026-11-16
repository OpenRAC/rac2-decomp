#include "include_asm.h"

#include "common.h"
typedef int rc2_qword __attribute__((mode(TI)));
typedef int TI __attribute__((mode(TI)));
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    s32 padC;
    TI vec_10;
} Stack_0040BED0;
extern void ref_L04_0040BED0_00(void *, void *, TI *);
extern void ref_L04_0040BED0_01(void *, s32, s32);
extern void ref_L04_0040BED0_02(TI *, TI *, f32);
extern void ref_L04_0040BED0_03(void *, void *, f32);
extern s32 ref_L04_0040BED0_04(f32);
extern s32 ref_L04_0040BED0_05(s32, s32);
extern f32 ref_L04_0040BED0_06(f32, f32);
extern f32 ref_L04_0040BED0_07(f32, f32);
extern void ref_L04_0040BED0_08(s32, void *, s32, f32, f32, s32);
extern void *ref_L04_0040BED0_09(s32, void *, s32, s32, s32);

/* Spawns a burst of sparks around a point, and unless skip_smoke is set a few smoke puffs too;
   scale sets how many (PAL: 50 Hz-tuned counts). */
void part_spawn_spark_and_smoke_burst_pal(s32 owner, rc2_qword *position, s32 skip_smoke, s32 offset, f32 scale) {
    Stack_0040BED0 spark;
    TI copy_value  = *(TI *)position;
    s32 spark_i = 0;
    s32 smoke_i;
    void *smoke;

    spark.vec_10 = copy_value;
    ref_L04_0040BED0_01(&spark, owner, offset + 0x10);
    ref_L04_0040BED0_03(&spark, &spark, 0.01f);
    while (spark_i < ref_L04_0040BED0_04(scale * 30.0f)) {
        spark_i += 1;
        spark.f0 += ref_L04_0040BED0_07(0.01f, 0.03f);
        spark.f4 += ref_L04_0040BED0_07(0.01f, 0.015f);
        spark.f8 += ref_L04_0040BED0_07(0.01f, 0.02f);
        ref_L04_0040BED0_02(&spark.vec_10, &spark.vec_10, 0.6f);
        ref_L04_0040BED0_00(&spark, &spark, &spark.vec_10);
        ref_L04_0040BED0_08(owner, &spark, 0xF, 0.004f, scale, 0x7FFFFFFF);
    }
    if (skip_smoke == 0) {
        smoke_i = 0;
        while (smoke_i < ref_L04_0040BED0_04(scale * 5.0f)) {
            smoke_i += 1;
            smoke = ref_L04_0040BED0_09(owner, &spark, ref_L04_0040BED0_05(25, 50), 0, 0);
            *(f32 *)((u8 *)smoke + 0x2C) *= ref_L04_0040BED0_06(0.2f, 0.4f);
        }
    }
}
