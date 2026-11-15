#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword q; float f[4]; } Vector;
typedef struct { u8 prefix[0x30]; int field30,field34,field38,field3c,field40,field44; } L19UtilityQueueView;
extern int D_L19_001B2508[] __attribute__((sda));
extern int D_L19_001B2724[4] __attribute__((sda));
extern int D_L19_001A8F00 __attribute__((sda));
extern u8 *D_L19_001B2A1C __attribute__((sda));
extern u8 D_001A7A40[] __attribute__((sda));
extern u32 D_00139800;
extern L19UtilityQueueView D_L19_001BFC40;
typedef union { u8 b[0x2600]; s32 i[0x980]; f32 f[0x980]; Quadword q[0x260]; } Hero;
extern u8 D_00189E20[];
extern void func_L19_0042A8B8(void);
extern int func_L19_0042A860(void);
extern void func_0029F338(void *);
extern void func_002A7750(u8 *,u8,int);
extern void func_L01_003128C0(char *);
extern int func_L01_003245E0(u8 *,int,float);
extern void func_L01_003246D0(u8 *);
extern int func_00288AA0(u8 *,int);
extern int func_00288BE8(L19UtilityQueueView *);
extern int func_002F5D10(void);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern void func_002A7470(u8 *,int,int,int);
extern float func_00282E80(void *,void *);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_00282DF0(void *);
extern float func_00283B98(float,float);
extern void func_002AF000(float *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern float func_00283BE0(float,float);
extern float func_00282E20(void *);
extern void func_002AEC48(void *,void *,int,float,float);

/* Runs a talking character. It shows a short scripted message, then turns its head and body to look at the player or at random spots. */
void func_L19_0042A9A0(u8 *moby)
{
    Vector target, origin, direction;
    u8 *vars = *(u8 **)(moby + 0x68);
    float rate, yaw, pitch, rotation, radians;
    int aiming;
    float blend = 0.3f;

    GlowAllMystics();
    if (gFrameCounter_L19[0] == 5) SumThreeCounts();
    switch (moby[0x20]) {
    case 0:
        SumThreeCounts();
        if (D_00139800 & 0x4000000) {
            if (*(int *)(vars+0x124) != -1)
                MarkMobySpawned(gMobyArray_L19 + *(int *)(vars+0x124)*0x100);
            *(int *)(vars+0x124) = -1;
            MarkMobySpawned(moby);
            return;
        }
        if (D_00139800 & 0x1000000) {
            MarkMobySpawned(moby);
            return;
        }
        SetMobyState(moby,1,-1);
        ResetMobyVarsDefaults((char *)moby);
        break;
    case 1:
        if (IsHeroReachableForCount(moby,10,2.5f)) {
            ApplyIndexForKey(moby);
            if (PushRequestQueue((u8 *)&D_L19_001BFC40,0x98)) {
                LaunchQueuedRequest(&D_L19_001BFC40);
                SetMobyState(moby,2,-1);
            }
        }
        break;
    case 2:
        D_L19_001B2724[1] = 1;
        if (D_L19_001A8F00 == 2) {
            moby[0x31]=0;
            *(u16 *)(moby+0x34) |= 1;
        }
        if (!IsEitherModeTwo()) {
            D_L19_001B2724[1] = 0;
            moby[0x31] = 1;
            *(u16 *)(moby+0x34) &= 0xfffe;
            MarkMobySpawned(moby);
            return;
        }
        break;
    }
    if (moby[0x20]) {
        if (moby[0x43] == 1 && FastDecTimer(vars+0x11e)) {
            *(short *)(vars+0x11e) = FloatToInt(RandomFloatRange(1200.0f,2400.0f));
            if (moby[0x43] != 2) StartAnimationBlended(moby,2,0,10);
        } else if (moby[0x60] & 2) {
            if (moby[0x43] != 1) StartAnimationBlended(moby,1,0,10);
        }
    }
    aiming = 0;
    rate = 0.02f;
    if (moby[0x43] == 1) {
        aiming = 1;
        if (vec_distance_xy(moby+0x10,&((Hero *)gHeroState)->q[8]) < 8.0f &&
            FastDiffRots(*(float *)(moby+0xf8),
                FastMatrixHelperA(((Hero *)gHeroState)->f[0xe0 / 4]-*(float *)(moby+0x10),
                             ((Hero *)gHeroState)->f[0xe4 / 4]-*(float *)(moby+0x14))) < 1.5707965f) {
            if (FastVecLength(&((Hero *)gHeroState)->q[0x110 / 16])>0.01f) *(int *)(vars+0x114)=120;
            else FastFloatHelperD(vars+0x114);
        } else if (*(int *)(vars+0x114)) {
            *(int *)(vars+0x114)=0;
            qcopy(vars+0x100, &((Hero *)gHeroState)->q[0xe0 / 16]);
        }
        if (FastFloatHelperD(vars+0x118)) {
            radians=0.017453294f;
            *(int *)(vars+0x118)=FloatToInt(RandomFloatRange(180.0f,300.0f));
            rotation=FastAddRotations(*(float *)(moby+0xf8),RandomFloatRange(-90.0f,90.0f)*radians);
            BuildSphericalOffset((float *)(vars+0x100),6.0f,rotation,RandomFloatRange(0.0f,30.0f)*radians);
            FastVecAdd(vars+0x100,vars+0x100,moby+0x10);
        }
        if (*(int *)(vars+0x114)) {
            qcopy(&target, &((Hero *)gHeroState)->q[0xe0 / 16]);
            rate=0.04f;
        } else qcopy(&target, vars+0x100);
    }
    if (aiming) {
        qcopy(&origin, moby+0x10);
        origin.f[2]+=2.0f;
        FastVecSub(&direction,&target,&origin);
        yaw=fast_subtract_rotations(FastMatrixHelperA(direction.f[0],direction.f[1]),*(float *)(moby+0xf8));
        pitch=-FastMatrixHelperA(vec_length_xy(&direction),direction.f[2]);
        if (yaw>1.5707965f) yaw=1.5707965f;
        else if (yaw< -1.5707965f) yaw= -1.5707965f;
        if (pitch>0.52359885f) pitch=0.52359885f;
        else if (pitch< -0.52359885f) pitch= -0.52359885f;
        *(float *)(vars+0x64)=pitch;
        *(float *)(vars+0x68)=yaw*0.6f;
        *(float *)(vars+0xe8)=yaw*0.4f;
    }
    if (D_001A7A40[0]) *(float *)(vars+0x70)=1.9f;
    UpdateEasedNode(moby,vars,0,rate,blend);
    UpdateEasedNode(moby,vars+0x80,1,rate,blend);
}
