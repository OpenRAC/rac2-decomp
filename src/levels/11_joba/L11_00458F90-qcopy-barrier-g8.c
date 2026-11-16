#include "include_asm.h"
#include "names.h"


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
u8 *joba_spark_create(u8 *position, int owner, u8 *direction, float speed) {
    u8 *moby = CreateMoby(0xE2D /* moby class 3629 */);
    u8 *vars;
    int frameCount;
    float frameTime;

    if (moby != 0) {
        *(u8 *)(moby + 0x20) = 0;
        *(u8 *)(moby + 0x30) = 0xFF;
        frameTime = g_spark_frame_time_scale * 0.016666668f;
        vars = *(u8 **)(moby + 0x68);
        *(float *)(vars + 0x64) = speed;
        vec_scale_to_length(vars + 0x40, direction, frameTime);
        *(TI128 *)(moby + 0x10) = *(TI128 *)position;
        *(TI128 *)(moby + 0xC0) = *(TI128 *)(vars + 0x40);
        FastVecCross(moby + 0xD0, moby + 0xC0, g_hero_state_block);
        vec_scale_to_length(moby + 0xD0, moby + 0xD0, -1.0f);
        FastVecCross(moby + 0xE0, moby + 0xD0, moby + 0xC0);
        frameTime = g_spark_frame_time_scale * 0.016666668f;
        frameCount = FloatToInt(g_spark_duration / frameTime);
        *(int *)(vars + 0x58) = frameCount;
        *(float *)(vars + 0x5C) = 1.0f / IntToFloat(frameCount);
        *(int *)(vars + 0x50) = owner;
        *(u8 *)(moby + 0x20) = 0;
        *(float *)(vars + 0x60) = g_spark_create_speed;
        moby_rebuild_frame_from_transform(moby);
    }
    return moby;
}
