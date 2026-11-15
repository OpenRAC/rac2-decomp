#include "common.h"

#define W(p,o) (*(s32 *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(f32 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 D_00189EA0[] NOT_SDA;
extern u8 D_0013962A NOT_SDA;
extern u8 D_L07_001BF400[] NOT_SDA;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 rest[0x40]; } PathRec;
extern PathRec *D_L07_001B23CC[] __attribute__((sda));
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern f32 D_L07_001B2CB8;
extern s32 D_L07_001B104C;
extern s32 D_L07_001B1044;
extern s32 D_L07_001A8F00;
extern f32 D_0018C2C4 NOT_SDA;
extern s32 D_0018C0BC NOT_SDA;
extern void func_L07_003F7BF0(u8 *);
extern void func_L07_003F8780(u8 *);
extern void func_L00_002D7140(u8 *);
extern s32 func_002ACBC8(void *,s32);
extern s32 func_00288AA0(void *,s32);
extern void func_00288BE8(void *);
extern void func_002A7750(u8 *,s32,s32);
extern void func_L07_003F7968(u8 *,s32,s32);
extern void func_L01_00323310(s32,s32);
extern s32 func_002F5D10(void);
extern void func_00282F20(void *,void *,f32);
extern void func_00282CC0(void *,void *,void *);
extern f32 func_00283248(f32,f32);
extern void func_L00_002B9D60(void *,void *,s32,s32);
extern void func_L07_003F80B8(u8 *,f32);
extern s32 func_002B3868(u8 *);
extern void func_L07_003F9028(u8 *);
extern s32 func_L07_003F8908(u8 *);
extern void func_L07_003EF1E0(u8 *,s32,s32);
extern void func_L07_003F8828(u8 *,void *);
extern s32 func_00283CF0(f32);
extern void func_002E5CF8(s32,s32,u8 *);
extern void func_L07_003F9088(u8 *);
extern s32 func_002AEB60(u8 *,f32);
extern void func_L07_003F8AB0(u8 *);
extern void func_L07_003F8BB0(u8 *);
extern void func_L07_003F8C38(u8 *);
extern void func_L07_003F8CD0(u8 *);
extern s32 func_00282948(void *);
extern void func_002A7470(u8 *,s32,s32,s32);
extern f32 func_002AA2E8(f32 *,f32,f32);
extern void func_L07_003F78F8(u8 *);
extern void func_002A6C58(u8 *,s32,s32);
extern s32 func_002A8C28(u8 *,void *,s32,f32,f32,f32,s32,s32,s32);
extern void func_L07_003EECE0(u8 *);
extern void func_002AD7B8(s32);
extern void func_00288CB0(s32,s32);
extern void func_L07_003F8D90(u8 *);

/* Updates the boss. It runs the boss's states: waiting, intro, walking, several attacks, taking hits and the final death, and keeps its parts up to date every frame. */
void func_L07_003F7048(u8 *moby)
{
    f32 pos[4];
    f32 rot[4];
    u8 *vars = P(moby,0x68);
    UpdatePhasedDamageState(moby);
    switch (moby[0x95]) {
    case 0:
    case 1:
        if (moby[0x20] != 3 && moby[0x20] != 11) SetupBossScreenEffect(moby);
        if (moby[0x95] == 0) D_L07_001B2CB8 = 0.6981318f;
        break;
    case 2:
        if (P(vars,0x450)) {
            EndCameraOverride(P(vars,0x450));
            P(vars,0x450)=0;
        }
        break;
    }
    switch (moby[0x20]) {
    case 1:
        if (IsPointInCuboid(gHeroPosition,W(vars,0x170))) {
            D_L07_001B104C=1;
            if (!D_0013962A) {
                if (PushRequestQueue(D_L07_001BF400,0x4f)) {
                    LaunchQueuedRequest(D_L07_001BF400);
                    SetMobyState(moby,2,-1);
                    goto start_path;
                }
            }
            StartBossMoveTier(moby,0,2);
            qcopy_nc(vars+0x3e0,D_L07_001B23CC[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
start_path:
            QueueKeyedRequest(W(vars,0x18c),-1);
        }
        break;
    case 2:
        if (!IsEitherModeTwo()) {
            D_0013962A=1;
            vec_scale_to_length(pos,(u8 *)&D_L07_001B23CC[0][W(vars,0x174)]+0x10,8.0f);
            FastVecAdd(pos,pos,D_L07_001B23CC[0][W(vars,0x174)].pos);
            qzero_nc(rot);
            rot[2]=FastMatrixHelperA(D_L07_001B23CC[0][W(vars,0x174)].pos[0]-pos[0],D_L07_001B23CC[0][W(vars,0x174)].pos[1]-pos[1]);
            ResetHeroPositionAndDirection(pos,rot,0,1);
            StartBossMoveTier(moby,0,2);
            qcopy_nc(vars+0x3e0,D_L07_001B23CC[0][W(vars,0x174)].pos);
            F(vars,0x3e8)+=1.5f;
        }
        break;
    case 3:
        MoveBossTowardTarget(moby,-1.0f);
        if (H(moby,0x96)>=121) SetMobyState(moby,4,-1);
        break;
    case 4:
        if (SetFirstPendingFlag(moby)) {
            SelectBossIdleAnimation(moby);
            W(vars,0x42c)=60;
        }
        MoveBossTowardTarget(moby,-1.0f);
        if (!W(vars,0x42c)) {
            W(vars,0x43c)=ChooseEnemyNextAction_L07(moby);
            SetMobyState(moby,5,-1);
        }
        break;
    case 5:
        if (SetFirstPendingFlag(moby)) SelectBossIdleAnimation(moby);
        MoveBossTowardTarget(moby,-1.0f);
        if (H(moby,0x96)==W(vars,0x444)-W(vars,0x448))
            StartMobyTimerState(P(vars,0x414),W(vars,0x448),W(vars,0x448)+10);
        else if (H(moby,0x96)==W(vars,0x444)-D_L07_001B1044)
            StoreAttachedPosition(moby,vars+0x140);
        else if (W(vars,0x444)<H(moby,0x96))
            SetMobyState(moby,W(vars,0x43c),-1);
        if (W(vars,0x43c)==7) {
            s32 n = FloatToInt(45.3f);
            if (H(moby,0x96)==W(vars,0x444)-n) PlayMobySound(8,0,moby);
        }
        break;
    case 6: case 7: case 8: case 9:
        if (SetFirstPendingFlag(moby)) SelectBossAttackAnimation(moby);
        MoveBossTowardTarget(moby,-1.0f);
        if (moby[0x42]==moby[0x43]) {
            if (IsValueWithinStepOfThreshold(moby,1.0f)) {
                switch (moby[0x20]) {
                case 7: FireBeamAttack(moby); break;
                case 6: QueryJointPoseForEffect(moby); break;
                case 9: SpawnGroupMemberEffect(moby); break;
                case 8: LaunchGroupMembersAway(moby); break;
                }
            } else if (moby[0x60]&2) {
                if (FastFloatHelperD(vars+0x438)) SetMobyState(moby,4,-1);
                else SetMobyState(moby,5,-1);
            }
        }
        break;
    case 10:
        if (SetFirstPendingFlag(moby)) {
            if (moby[0x43]!=7) StartAnimationBlended(moby,7,0,20);
        }
        MoveBossTowardTarget(moby,-1.0f);
        if (moby[0x60]&2) SetMobyState(moby,11,-1);
        break;
    case 11:
        if (SetFirstPendingFlag(moby)) {
            if (moby[0x43]!=4) StartAnimationBlended(moby,4,0,20);
            F(vars,0x434)=1.0833334f;
        }
        MoveBossTowardTarget(moby,F(vars,0x434));
        ApproachValue((f32 *)(vars+0x434),0.0f,0.0055555557f);
        ApproachValue((f32 *)(vars+0x3e8),18.0f,0.033333335f);
        if (!moby[0x31]) {
            SetMobyState(moby,1,2);
            ResetBossAndChildren(moby);
        }
        break;
    case 12:
        if (SetFirstPendingFlag(moby)) {
            if (moby[0x43]!=7) StartAnimationBlended(moby,7,0,20);
            F(vars,0x3e8)+=1.0f;
            W(vars,0x440)=600;
            if (F(vars,0x20)==0.0f && !moby[0x7f]) SetDeathBits(moby,10,3);
        }
        MoveBossTowardTarget(moby,-1.0f);
        if (F(vars,0x20)<=0.0f) {
            D_0018C2C4=40.0f;
            SweepCollisionFromObject(moby,D_L07_001B23CC[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        }
        if (moby[0x60]&2) {
            if (F(vars,0x20)<=0.0f) SetMobyState(moby,13,2);
            else {
                switch(W(vars,0x420)) {
                case 3: break;
                case 4: ResetPathFollowerToPathPoint(gMobyArray_L07[0]+(W(vars,0x178)<<8)); break;
                case 5: ResetPathFollowerToPathPoint(gMobyArray_L07[0]+(W(vars,0x17c)<<8)); break;
                }
                SetMobyState(moby,4,-1);
                W(vars,0x440)=0;
            }
        }
        break;
    case 13:
        if (PushRequestQueue(D_L07_001BF400,0x50)) {
            PushRequestQueue(D_L07_001BF400,0x51);
            PushRequestQueue(D_L07_001BF400,8);
            PushRequestQueue(D_L07_001BF400,0x52);
            LaunchQueuedRequest(D_L07_001BF400);
            SetMobyState(moby,14,-1);
        }
        break;
    case 14:
        if (((H(moby,0x34)^1)&1) && D_L07_001A8F00==2) ResetBossAndChildren(moby);
        SweepCollisionFromObject(moby,D_L07_001B23CC[0][W(vars,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        if (!IsEitherModeTwo() && D_L07_001A8F00!=2 && D_L07_001A8F00!=1 && D_0018C0BC!=20) {
            MarkFlagAndAppendToList(8);
            SetSmallDataValueAndRefresh(8,1);
        }
        break;
    }
    UpdateSiberiusGunAiming(moby);
}
