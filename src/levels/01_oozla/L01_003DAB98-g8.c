#include "common.h"
extern f32 D_L01_001B082C __attribute__((sda));
extern f32 D_L01_001B0830 __attribute__((sda));
extern f32 D_L01_001B0834 __attribute__((sda));
extern f32 D_L01_001B0838 __attribute__((sda));
extern u8 *D_L01_001BF918 __attribute__((nosda));
typedef struct { u8 pad[0x2290]; s32 collision; } CameraAB;
extern CameraAB D_00189E20;
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_003DA740(void *);
extern void func_002A7470(void *, s32, s32, s32);
extern f32 func_L01_003BAFB0(void);
/* EE argument banks retain three integer arguments and one float argument. */
extern s32 func_00277258(void *, s32, f32, s32);
extern void func_L01_003DA3F0(void *, void *);
extern void func_L01_003120A8(s32, void *, void *, f32, f32, s32, s32, s32, s32);
extern void func_00282F20(void *, void *, f32);
extern void func_0029F338(void *);
extern void func_002A9288(void *, f32);
/* Moves a falling object each frame and removes it when it lands or leaves the level. */
void func_L01_003DAB98(u8 *obj) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 bottom[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(obj + 0x68);
    f32 height;
    *(f32 *)(obj + 0x2C) += (*(f32 *)(*(u8 **)(obj + 0x24) + 0x24) * D_L01_001B082C - *(f32 *)(obj + 0x2C)) * D_L01_001B0830;
    qcopy(pos, obj + 0x10);
    FastVecAdd(obj + 0x10, obj + 0x10, state);
    SpawnDebrisBurstParticles(obj);
    if ((obj[0x60] & 2) && obj[0x43] != 1) StartAnimationBlended(obj, 1, 0, 10);
    height = GetWaterHeight();
    if ((TestPointAgainstCollision(obj + 0x10, 0, D_L01_001B0838, *(s32 *)(state + 0x10)) &&
          (!D_L01_001BF918 || *(s16 *)(D_L01_001BF918 + 0xAA) != 0x660)) || *(f32 *)(obj + 0x18) < height) {
        SpawnExplosionParticles_L01(obj, state);
        qcopy(bottom, obj + 0x10);
        bottom[2] -= 6.0f;
        CastObjectCollisionLine(gHeroState.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        vec_scale_to_length(state, state, D_L01_001B0838);
        *(s32 *)(state + 8) = 0;
        FastVecAdd(obj + 0x10, obj + 0x10, state);
        FastVecAdd(bottom, bottom, state);
        CastObjectCollisionLine(gHeroState.collision, obj + 0x10, bottom, 0.0001f, 1.0f, 1, 0, 1, 0);
        MarkMobySpawned(obj);
    } else {
        *(f32 *)(state + 8) -= D_L01_001B0834 * 0.00027777778450399637f;
        if (*(f32 *)(obj + 0x10) < 2.0f || *(f32 *)(obj + 0x10) > 1021.0f ||
            *(f32 *)(obj + 0x14) < 2.0f || *(f32 *)(obj + 0x14) > 1021.0f ||
            *(f32 *)(obj + 0x18) < 2.0f || *(f32 *)(obj + 0x18) > 1021.0f) { MarkMobySpawned(obj); return; }
        QueueGroundShadow(obj, *(f32 *)(obj + 0x2C) / *(f32 *)(*(u8 **)(obj + 0x24) + 0x24));
    }
}
