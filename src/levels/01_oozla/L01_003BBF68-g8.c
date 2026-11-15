#include "common.h"
typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x60];
    float vel[4];
    char pad100[0x10];
    float v110[4], v120[4], v130[4];
    char pad140[0xB0];
    short control;
    char pad1F2[0x12A];
    float f31C;
    char pad320[0x1C];
    char *obj;
    int active;
    char pad344[0x1F4C];
    int query;
    int action;
    char pad2298[0x1D];
    char flag;
    char pad22B6[0x216];
    int f24CC;
} L01_003BBF68_HERO;
extern L01_003BBF68_HERO D_00189E20;
extern float D_L01_001AFE2C __attribute__((sda));
extern float D_L01_001AFE28 __attribute__((sda));
extern float func_0029F530(void *);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern int func_00283CF0(float);
extern int func_L00_002D6900(int);
extern void func_L00_002D6B70(int);
extern int func_00282948(void *);
extern void func_002E5CF8(int, int, void *);
extern int func_002A77E0(int);
extern void func_L00_002B30E8(void);
extern void func_002A8BD0(void *, void *, int, float);
extern void func_002A8E20(int, void *);
extern void func_L01_002C1988(int);
extern void func_L01_002BEB90(int, int);
extern void func_L00_002D2168(int, int, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282C88(void *);

/* Updates a creature that waits for the player, grabs and holds him while it plays its animation, then lets go. The player is dragged towards it while he is held. */
void func_L01_003BBF68(char *moby)
{
    union {
        char query[0x24];
        struct { float pos[4], delta[4]; } vec;
    } scratch;
    char *vars = *(char **)(moby + 0x68);
    float frame = GetMobyAnimationValue(moby);
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        SetMobyState(moby, 1, -1);
        if (*(unsigned char *)(moby + 0x43) != 0) StartAnimationBlended(moby, 0, 0, 2);
        *(int *)(moby + 0x9C) = 3;
        *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        *(int *)(vars + 0x78) = -1;
        break;
    case 1:
        if (gHeroState.obj == moby && gHeroState.active) {
            SetMobyState(moby, 2, -1);
            *(int *)(vars + 0x60) = FloatToInt(*(float *)(vars + 0x50) * 60.0f);
            *(int *)(vars + 0x78) = QueueRecordsByIndex(7);
            if (*(unsigned char *)(moby + 0x43) != 1) StartAnimationBlended(moby, 1, 0, 10);
        }
        break;
    case 2:
        if (gHeroState.obj == moby && gHeroState.active) {
            *(int *)(vars + 0x78) = QueueRecordsByIndex(4);
        } else if (*(int *)(vars + 0x78) != -1) {
            ResetActiveSlots(*(int *)(vars + 0x78));
            *(int *)(vars + 0x78) = -1;
        }
        if (FastFloatHelperD(vars + 0x70) && FastFloatHelperD(vars + 0x60)) {
            if (*(int *)(vars + 0x78) != -1) {
                ResetActiveSlots(*(int *)(vars + 0x78));
                *(int *)(vars + 0x78) = -1;
            }
            SetMobyState(moby, 3, -1);
            PlayMobySound(0, 0, moby);
            if (*(unsigned char *)(moby + 0x43) != 2) StartAnimationBlended(moby, 2, 0, 6);
            if (gHeroState.obj == moby && gHeroState.active)
                *(int *)(vars + 0x78) = QueueRecordsByIndex(5);
            *(float *)(moby + 0x48) = D_L01_001AFE2C;
        }
        break;
    case 3:
        if (*(float *)(vars + 0x74) < 4.0f && frame > 4.0f) {
            *(unsigned short *)(moby + 0x34) |= 0x1000;
            *(int *)(vars + 0x64) = 600;
            if (gHeroState.obj == moby && gHeroState.f31C < 0.5f) {
                *(int *)(vars + 0x78) = QueueRecordsByIndex(5);
                *(int *)(vars + 0x68) = 1;
                *(int *)(moby + 0x9C) = -1;
            } else {
                if (*(int *)(vars + 0x78) != -1) {
                    ResetActiveSlots(*(int *)(vars + 0x78));
                    *(int *)(vars + 0x78) = -1;
                }
                *(int *)(moby + 0x9C) = 0x80000000;
            }
            SetMobyState(moby, 4, -1);
        }
        break;
    case 4:
        if (*(int *)(vars + 0x68) && !RandomIntBelow(11)) *(int *)(vars + 0x78) = QueueRecordsByIndex(5);
        if (*(float *)(vars + 0x74) < 46.0f && frame > 46.0f) {
            if (*(int *)(vars + 0x68)) {
                if (gHeroState.f24CC < 2) RecordHeroPlayCounters();
                else {
                    InitEffectRecord_002A8BD0(scratch.query, moby, 1, (float)*(unsigned char *)(vars + 0x34));
                    QueueMobyImpact(gHeroState.query, scratch.query);
                }
                gHeroState.flag = 0;
                StartHeroMoveStateOneOrTwo(0);
                *(int *)(vars + 0x68) = 0;
                *(int *)(vars + 0x70) = 120;
            }
            *(int *)(moby + 0x9C) = 3;
            *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        }
        if (*(unsigned char *)(moby + 0x60) & 2) {
            if (*(int *)(vars + 0x78) != -1) {
                ResetActiveSlots(*(int *)(vars + 0x78));
                *(int *)(vars + 0x78) = -1;
            }
            SetMobyState(moby, 1, -1);
            if (*(unsigned char *)(moby + 0x43) != 0) StartAnimationBlended(moby, 0, 0, 10);
        } else if (*(int *)(vars + 0x68)) {
            if (gHeroState.action != 111) {
                SetHeroMoveState(111, 1);
                set_hero_animation(10, 0, 10.0f);
            }
            gHeroState.control = 2;
            qcopy(scratch.vec.pos, moby + 0x10);
            scratch.vec.pos[2] += 2.0f;
            FastVecSub(scratch.vec.delta, scratch.vec.pos, gHeroState.pos);
            ClampVectorLength(scratch.vec.delta, 0.06666667f);
            FastVecAdd(gHeroState.pos, gHeroState.pos, scratch.vec.delta);
            ClearVector128(gHeroState.vel);
            ClearVector128(gHeroState.v110);
            ClearVector128(gHeroState.v120);
            ClearVector128(gHeroState.v130);
            if (*(int *)(vars + 0x64) > 60) *(int *)(vars + 0x64) = 60;
        }
        break;
    }
    *(float *)(moby + 0x2C) = *(float *)(*(char **)(moby + 0x24) + 0x24) * D_L01_001AFE28;
    *(unsigned char *)(moby + 0xA8) = 255;
    *(float *)(vars + 0x74) = frame;
}
