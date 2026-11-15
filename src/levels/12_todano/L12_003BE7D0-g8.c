#include "common.h"

typedef struct { float pad[32]; float x, y, z; } Target;
extern Target D_00189E20;
extern u8 D_00189EA0[];
extern u8 D_00188660[];
extern float D_L12_001AFC70 __attribute__((sda));
extern float D_L12_001AFC74 __attribute__((sda));
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern void func_L00_00326620(void *, int, int);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern int func_002A9640(void *, int, int);
extern int func_002E5CF8(int, int, void *);
extern float func_002AAA00(void *, float, void *, int, float, float, float);
extern void func_002AEC48(void *, void *, int, float, float);

/* Updates a moby of class 2154. It turns its head to follow the hero while the hero is close,
   plays a looping effect while it turns, and removes itself when hit. */
void func_L12_003BE7D0(u8 *moby) {
    u8 *vars = *(u8 **)(moby + 0x68);
    float yaw = 0, pitch = 0;
    float acceleration, damping;
    float halfPitch, halfYaw;

    *(u16 *)(moby + 0x34) |= 4;
    switch (moby[0x20]) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        yaw = 0;
        if (vec_distance_xy(moby + 0x10, gHeroPosition) < 16.0f) {
            moby[0x20] = 2;
            if (moby[0x43] != 1)
                StartAnimationBlended(moby, 1, 0, 30);
        }
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) && !*(int *)(vars + 0x110))
            SetMobyState(moby, 3, -1);
        moby[0xA8] = 255;
        break;
    case 2: {
        float *target;

        yaw = FastAddRotations(fast_subtract_rotations(FastMatrixHelperA(gHeroState.x - *(float *)(moby + 0x10), gHeroState.y - *(float *)(moby + 0x14)), *(float *)(moby + 0xF8)), 1.5707964897155762f);
        target = &gHeroState.x;
        pitch = FastMatrixHelperA(vec_distance_xy(target, moby + 0x10), *(float *)(moby + 0x18) - gHeroState.z);
        if (vec_distance_xy(moby + 0x10, target) > 20.0f) {
            moby[0x20] = 1;
            if (moby[0x43] != 0)
                StartAnimationBlended(moby, 0, 0, 30);
        }
        if (FindOwnedEffectSlot(moby, 0x4010000, 0) && !*(int *)(vars + 0x110))
            SetMobyState(moby, 3, -1);
        moby[0xA8] = 255;
        break;
    }
    case 3:
        SpawnChildMoby_L00(moby, 0x1132, moby[0x30]);
        PlayMobySound(0, 0, moby);
        {
            int effectId = *(int *)(vars + 0x114);
            u8 *effect;

            if (effectId != -1) {
                effect = gSoundState + effectId * 0x70;
                if (*(u8 **)(effect + 0x88) == moby && effect[0x74])
                    StopSoundVoice(effectId);
            }
        }
        *(int *)(vars + 0x114) = -1;
        MarkMobySpawned(moby);
        return;
    }
    if (FloatAbs(fast_subtract_rotations(yaw, *(float *)(vars + 0x100))) > D_L12_001AFC74 * 0.017453294f) {
        u8 *effect = gSoundState + *(int *)(vars + 0x114) * 0x70;

        if (*(u8 **)(effect + 0x88) != moby || !effect[0x74])
            *(int *)(vars + 0x114) = PlayMobySound(1, 4, moby);
    } else {
        int effectId = *(int *)(vars + 0x114);
        u8 *effect;

        if (effectId != -1) {
            effect = gSoundState + effectId * 0x70;
            if (*(u8 **)(effect + 0x88) == moby && effect[0x74])
                StopSoundVoice(effectId);
        }
        *(int *)(vars + 0x114) = -1;
    }
    acceleration = 0.03f;
    ApproachTargetWithDirectionMode(vars + 0x100, yaw, vars + 0x108, 0, 0.0017453295f, 0.0017453295f, 0.10471977f);
    damping = 0.3f;
    ApproachTargetWithDirectionMode(vars + 0x104, pitch, vars + 0x10C, 0, 0.0017453295f, 0.0017453295f, 0.10471977f);
    halfPitch = *(float *)(vars + 0x104) * 0.5f;
    halfYaw = *(float *)(vars + 0x100) * 0.5f;
    *(float *)(vars + 0x68) = halfYaw;
    *(float *)(vars + 0x60) = halfPitch;
    *(float *)(vars + 0xE0) = halfPitch;
    *(float *)(vars + 0xE8) = halfYaw;
    UpdateEasedNode(moby, vars, 0, acceleration, damping);
    UpdateEasedNode(moby, vars + 0x80, 1, acceleration, damping);
    func_002A0F48(moby);
    *(float *)(moby + 0xC) = D_L12_001AFC70;
}
