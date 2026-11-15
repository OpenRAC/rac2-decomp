#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern float func_002B0178(void *, void *, void *);
extern int func_002AD0B0(void *);
extern int func_002ACBC8(void *, int);
extern int func_002B38B8(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_002A7470(void *, int, int, int);
extern int func_00282948(void *);
extern unsigned char *func_L07_003E5B70(int, int *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, float, int, void *);
extern void func_L07_003E5C78(void *, void *, void *, int);
extern int func_002E5CF8(int, int, void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283B98(float, float);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L07_003E5070(char *);
extern int func_002A77E0(int);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float);
extern int func_002A7820(int, int);
extern float func_00283CE0(int);
extern void func_002C3150(void *, void *, int, float, int, int, int);
struct Collision1310 { char pad[0x18]; void *object; };
extern struct Collision1310 D_L07_001BF640;
extern char D_00189EA0[];
extern float D_L07_001B0A50 __attribute__((sda));
extern int D_L07_001B0A48[] __attribute__((sda));
/* The first color is GP-relative; the second uses the absolute table view. */
extern int D_L07_001B0A48_gp[] SDATA(D_L07_001B0A48);
extern float D_L07_001B0A40[] __attribute__((sda));
/* Update the launcher state, dispatch its target effect and emit particles. */
/* Per-frame update for moby class 3356: it waits, then looks for a group member to send off
   while giving off sparks. */
void func_L07_003E4BD0(unsigned char *moby)
{
    float probePos[4] __attribute__((aligned(16)));
    float aimPos[4] __attribute__((aligned(16)));
    float sparkPos[4] __attribute__((aligned(16)));
    float sparkVel[4] __attribute__((aligned(16)));
    int count;
    char *vars = *(char **)(moby+0x68);
    unsigned char *target;
    float angle, size, speed;
    const float lift = 0.05f;
    const float turn = 0.0002908882457f;
    int color, life;
    switch (moby[0x20]) {
    case 0:
        D_L07_001BF640.object=0;
        GetGroundDistanceBelowPosition(moby+0x10,moby,moby+0x10);
        {
            float height = *(float *)(moby + 0x18);
            height = lift + height;
            *(float *)(moby + 0x18) = height;
        }
        *(int *)(vars+0x20)=-1;
        if (D_L07_001BF640.object && GetMobyPrivateValue2(D_L07_001BF640.object))
            *(int *)(vars+0x10)=(int)D_L07_001BF640.object;
        SetMobyState(moby,1,-1);
        break;
    case 1:
        if (IsPointInCuboid(gHeroPosition,*(int *)(vars+4)) || IsThirdPendingFlagSet(moby)) SetMobyState(moby,2,-1);
        break;
    case 2:
        if (SetFirstPendingFlag(moby) && moby[0x43]!=1) StartAnimationBlended(moby,1,0,20);
        if (FastFloatHelperD(vars+0x14)) {
            target=FindLastIdleGroupMember(*(int *)vars,&count);
            if (target) {
                *(u128 *)probePos=0;
                probePos[2]=0.7f;
                matrix_mul_vec3(probePos,probePos,moby+0xC0);
                FastVecAdd(probePos,probePos,moby+0x10);
                if (!TestPointAgainstCollision(probePos,0.5f,0,moby)) {
                    *(u128 *)aimPos=0;
                    aimPos[2]=0.5f;
                    FastVecAdd(aimPos,aimPos,moby+0x10);
                    SendEntityToPositionAndShrink(target,moby+0x10,aimPos,*(int *)(vars+0x10));
                    PlayMobySound(0,0,moby);
                    *(int *)(vars+0x14)=60;
                }
            } else if (!count) SetMobyState(moby,3,-1);
        }
        ApproachValue(vars+0x18,1.0f,0.05000000447f);
        {
            float delta = D_L07_001B0A50;
            delta = turn * delta;
            *(float *)(vars + 0x1C) = FastAddRotations(*(float *)(vars + 0x1C), delta);
        }
        AddDrawCallbackToList1(DrawEntityGlowDisc,moby);
        if (moby[0x31] && !RandomIntBelow(5)) {
            qzero_nc(aimPos); qzero_nc(probePos);
            if (*(void **)(vars+0x10)) {
                TransformPointAndRotationByParent(moby,*(void **)(vars+0x10),moby+0x10,probePos,aimPos,probePos);
                FastVecSub(aimPos,aimPos,moby+0x10);
            }
            angle=RandomAngle();
            sparkPos[0]=FastSinOrCosA(angle)*0.4f;
            sparkPos[1]=FastSinOrCosB(angle)*0.4f;
            sparkPos[2]=0;
            FastVecAdd(sparkPos,sparkPos,moby+0x10);
            size=RandomFloatRange(D_L07_001B0A40[0],D_L07_001B0A40[1]);
            color=FastTweenColor(D_L07_001B0A48_gp[0],D_L07_001B0A48[1],RandomFloatRange(0,1));
            speed=RandomFloatRange(1,2);
            life=RandomIntRange(30,60);
            qcopy(sparkVel,aimPos);
            sparkVel[2]=speed/IntToFloat(life);
            SpawnHeroRelativeParticle(sparkPos,sparkVel,color,size,(unsigned char)life,(unsigned char)RandomIntBelow(255),0);
        }
        break;
    case 3:
        if (SetFirstPendingFlag(moby) && moby[0x43]) StartAnimationBlended(moby,0,0,20);
        ApproachValue(vars+0x18,0,0.05000000447f);
        AddDrawCallbackToList1(DrawEntityGlowDisc,moby);
        if (moby[0x42]==moby[0x43] && *(float *)(vars+0x18)<=0) *(unsigned short *)(moby+0x34)|=2;
        break;
    }
}
