#include "names.h"
/* func_PAL_L11_0045EBA0, the PAL copy of func_L11_00458F90: the same C, where scale func_00283CF0(D_L11_001B1FDC / frame_time). */


typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));
extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void moby_rebuild_frame_from_transform(u8 *);
extern char g_hero_state_block[];
extern float g_spark_create_speed __attribute__((sda));
extern float g_spark_frame_time_scale __attribute__((sda));
extern float g_spark_duration __attribute__((sda));

/* Same body as func_L02_004216F0, minus the final call; this level's own data. */
u8 *joba_spark_create_pal(u8 *position, int owner, u8 *direction, float strength) {
    u8 *spark = CreateMoby(0xE2D);
    u8 *vars;
    int frame_count;
    float frame_time;

    if (spark != 0) {
        *(u8 *)(spark + 0x20) = 0;
        *(u8 *)(spark + 0x30) = 0xFF;
        frame_time = g_spark_frame_time_scale * 0.020000001f;
        vars = *(u8 **)(spark + 0x68);
        *(float *)(vars + 0x64) = strength;
        vec_scale_to_length(vars + 0x40, direction, frame_time);
        *(TI128 *)(spark + 0x10) = *(TI128 *)position;
        *(TI128 *)(spark + 0xC0) = *(TI128 *)(vars + 0x40);
        FastVecCross(spark + 0xD0, spark + 0xC0, g_hero_state_block);
        vec_scale_to_length(spark + 0xD0, spark + 0xD0, -1.0f);
        FastVecCross(spark + 0xE0, spark + 0xD0, spark + 0xC0);
        frame_time = g_spark_frame_time_scale * 0.020000001f;
        frame_count = (((int)(FloatToInt(g_spark_duration / frame_time)) * 5 + 2) / 6);
        *(int *)(vars + 0x58) = frame_count;
        *(float *)(vars + 0x5C) = 1.0f / IntToFloat(frame_count);
        *(int *)(vars + 0x50) = owner;
        *(u8 *)(spark + 0x20) = 0;
        *(float *)(vars + 0x60) = g_spark_create_speed;
        moby_rebuild_frame_from_transform(spark);
    }
    return spark;
}
