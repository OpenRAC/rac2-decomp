#include "common.h"

typedef struct { u8 pad0[0x20]; f32 f20; u16 f24; u8 pad26[0xA]; f32 f30;
    u8 pad34[0x1C]; f32 f50, f54, f58, f5c, f60;
    u8 pad64[0x1C]; f32 f80, f84; s32 f88; u8 pad8c[0x10]; void *f9c;
} L12PathState;

#define SI(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define SF(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define SH(p,o) (*(u16 *)((u8 *)(p)+(o)))
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0, D_L12_0021E180;
extern u8 D_0019B4A8[], D_0019B2E8[], D_L12_001B9E00[], D_L12_001C0270[];
extern u8 D_L12_001B2CE0[] __attribute__((sda));
typedef struct { u8 pad[0x80]; f32 pos[4]; u8 pad90[0x530]; u8 *target; } PlayerState;
extern PlayerState D_00189E20;
extern s32 D_001A79F0 MACRO_ADDR;
extern s32 D_001A79F0_gp SDATA(D_001A79F0);
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern s32 *D_L12_001FEAC0[];
extern s32 D_L12_001B29C8 MACRO_ADDR;
extern s32 D_L12_001B29C8_gp SDATA(D_L12_001B29C8);
extern f32 D_L12_001B20A0 __attribute__((sda)), D_L12_001B20A4 __attribute__((sda)), D_L12_001B20A8 __attribute__((sda)), D_L12_001B20AC __attribute__((sda));
extern f32 D_L12_001B20B0 __attribute__((sda)), D_L12_001B20C8 __attribute__((sda));
extern s32 D_L12_001B20B8[] __attribute__((sda));
extern void func_0029F338(void *), func_L12_0041BDA8(void *), func_L12_0041BDF8(void *);
extern s32 func_L12_0041BE60(void *);
extern f32 func_00282E48(void *, void *), func_00282E80(void *, void *);
extern void func_002A93B0(void *), func_002A7750(void *,s32,s32);
extern void func_002A7470(void *,s32,s32,s32);
extern s32 func_002A77E0(s32), func_002B3868(void *), func_002B38B8(void *);
extern f32 func_002AA340(s32 *,s32,s32);
extern void func_002B60B0(void *,f32,f32,f32,f32);
extern s32 func_L01_00321178(void *,void *), func_L12_00425178(void *,s32), func_L12_00425070(void *);
extern void func_L12_00425448(void *), func_L12_00425348(void *);
extern s32 func_002761F8(void *,void *,s32,void *,s32);
extern f32 func_00282DB0(void *,void *), func_00283248(f32,f32);
extern s32 func_L01_00322288(void *,f32);
extern void func_L01_0031AB20(void *,void *,f32,f32,f32,s32);
extern u8 *func_0029EFD0(s32);
extern s32 func_L02_003272D8(void *), func_002ACBC8(void *,s32);
extern void func_00282CC0(void *,void *,void *), func_00282F70(void *,void *,f32);
extern f32 func_00282E20(void *);
extern s32 func_00277258(void *,s32,void *,f32);
extern void func_00282F20(void *,void *,f32), func_00283028(void *,void *,void *), func_00282D30(void *,void *,f32), func_00282C88(void *);
extern f32 func_00283B98(f32,f32);
extern s32 func_L01_0031BC68(s32,s32,f32);
extern void func_002B0990(void *,f32 *,f32,s32,s32);

/* Updates an enemy that wanders between path points, walks or runs to a new point, and turns to face the hero when it is targeted. */
void func_L12_00424370(u8 *self)
{
    f32 oldpos[4], from[4], to[4];
    u8 *st = *(u8 **)(self+0x68);
    s32 *path;
    s32 was0=0, was1=0;
    u16 id=SH(self,0xb2);
    if (D_L12_0021EDF0.flags[(s16)id]) { MarkMobySpawned(self); return; }
    { s32 flags=D_0019B4A8[((s16)id>>1)+(gCurrentMapIndex<<10)];
    flags = ((id & 1) ? flags >> 4 : flags) & 7;
    if(flags) { MarkMobySpawned(self); return; } }
    path=D_L12_001FEAC0[SI(st,0x298)];
    if (HasLiveHelperObject(D_L12_001B2E9C+(SI(st,0x2c4)<<8))) was0=1;
    if (HasLiveHelperObject(D_L12_001B2E9C+(SI(st,0x2c8)<<8))) was1=1;
    if (SI(st,0x2c4)!=-1) RestoreBeamChildCollision(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
    if (SI(st,0x2c8)!=-1) RestoreBeamChildCollision(D_L12_001B2E9C_gp+(SI(st,0x2c8)<<8));
    SF(self,0x2c)=SF(*(u8 **)(self+0x24),0x24)*D_L12_001B20A0;
    qcopy(oldpos,self+0x10);
    if (self[0x31] && fast_vec_dist(self+0x10,D_L12_001B9E00)<24.0f) {
        UpdateMobyGroundCheck(self); self[0x6f]=22;
    }
    if (!self[0x95]) {
        if (self==gHeroState.target) {
            SetMobyState(self,5,1); qcopy(st+0x150,self+0x10);
        } else {
            if (vec_distance_xy(self+0x10,gHeroState.pos)<SF(st,0x178)) SH(self,0x34)|=0x1000;
            else SH(self,0x34)&=0xefff;
        }
    }
    switch(self[0x20]) {
    case 0:
        ((L12PathState *)st)->f24=1;
        ((L12PathState *)st)->f20=1.0f; ((L12PathState *)st)->f30=1.5f; ((L12PathState *)st)->f84=0.05f;
        ((L12PathState *)st)->f54=0.2f; ((L12PathState *)st)->f50=0.825f; ((L12PathState *)st)->f58=0.4f; ((L12PathState *)st)->f5c=0.4f;
        ((L12PathState *)st)->f60=1.5707964897155762f; ((L12PathState *)st)->f80=0.523598849773407f;
        ((L12PathState *)st)->f88|=1; ((L12PathState *)st)->f9c=st+0x190;
        SI(st,0x2b0)=0; qcopy(self+0x10,(u8 *)path+0x10);
        self[0x20]=1; self[0x30]=128; SH(self,0x34)|=0x1000;
        break;
    case 1:
        if (SetFirstPendingFlag(self)) {
            s32 anim=self[0x43]; if(anim!=RandomIntBelow(2)) StartAnimationBlended(self,RandomIntBelow(2),0,10);
            SI(st,0x2b8)=vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>24.0f?30:180;
        }
        if (SI(st,0x2b8)<SH(self,0x96)) {
            if (SI(st,0x2b0)<SI(st,0x2b4) && vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>20.0f)
                SetMobyState(self,4,-1);
            else SetMobyState(self,2,-1);
        }
        break;
    case 4:
        if(SetFirstPendingFlag(self)) {
            if(self[0x43]!=5) StartAnimationBlended(self,5,0,20);
            StepIntTowardTarget((s32 *)(st+0x2b0),SI(st,0x2b4),1);
            { f32 speed=D_L12_001B20AC;
              SetControllerSpeedLimits(self,0.0022222223f,speed*0.016666668f,0.0034906589426100254f,0.20943955f); }
        }
        if(SI(st,0x2b0)<SI(st,0x2b4)) {
            qcopy(from,self+0x10); from[2]+=0.5f;
            qcopy(to,(SI(st,0x2b0)*16)+(u8 *)path+0x20); to[2]+=0.5f;
            if(!CollLine(from,to,2,self,0)) SI(st,0x2b0)++;
        }
        TurnMobyTowardTarget(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path);
        if(vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)<8.0f) SetMobyState(self,1,-1);
        break;
    case 2:
        if(SetFirstPendingFlag(self)) {
            if(self[0x43]!=4) StartAnimationBlended(self,4,0,20);
            { s32 next=PickRandomVisiblePathPoint(self,1);
            f32 rate=D_L12_001B20A8*0.016666668f; SI(st,0x2b0)=next;
            SetControllerSpeedLimits(self,0.0011111111380159855f,rate,0.0008726647356525064f,0.10471977f); }
            SI(st,0x2b8)=vec_distance_xy(self+0x10,(SI(st,0x2b4)*16+0x10)+(u8 *)path)>24.0f?900:300;
        }
        if((TurnMobyTowardTarget(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path)&128)||SH(self,0x96)>=300) SetMobyState(self,1,-1);
        break;
    case 3:
        if(SetFirstPendingFlag(self)) {
            if(self[0x43]!=5) StartAnimationBlended(self,5,0,20);
            { s32 next=PickRandomVisiblePathPoint(self,0);
            f32 rate=D_L12_001B20AC*0.016666668f; SI(st,0x2b0)=next;
            SetControllerSpeedLimits(self,0.003888889f,rate,0.0034906589426100254f,0.4188791f); }
        }
        if(TurnMobyTowardTarget(self,(SI(st,0x2b0)*16+0x10)+(u8 *)path)&128) SI(st,0x2b0)=PickRandomVisiblePathPoint(self,1);
        if(SH(self,0x96)>=420) SetMobyState(self,1,-1);
        break;
    case 5: {
        f32 dot;
        if(SetFirstPendingFlag(self)) {
            if(self[0x43]!=7) StartAnimationBlended(self,7,0,10);
            SI(st,0x2c0)=0;
        }
        dot=FastVecDot(self+0xc0,st+0x140);
        if(dot< -0.033333335f) { if(self[0x43]!=10) StartAnimationBlended(self,10,0,10); }
        else if(dot>0.033333335f) { if(self[0x43]!=9) StartAnimationBlended(self,9,0,10); }
        else { if(self[0x43]!=7) StartAnimationBlended(self,7,0,10); }
        StartMobyEffectFromEntry(self,FastMatrixHelperA(gHeroState.pos[0]-SF(self,0x10),gHeroState.pos[1]-SF(self,0x14)));
        if(HasLiveHelperObject(D_L12_001B2E9C+(SI(st,0x2c4)<<8))) was0=1;
        if(HasLiveHelperObject(D_L12_001B2E9C+(SI(st,0x2c8)<<8))) was1=1;
        if(SI(st,0x2c4)!=-1) RestoreBeamChildCollision(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
        if(SI(st,0x2c8)!=-1) RestoreBeamChildCollision(D_L12_001B2E9C_gp+(SI(st,0x2c8)<<8));
        UpdatePushableMoby(self,st+0x140,0.7f,0.5f,0.1f,SI(st,0x360));
        RestartSparkTimerAndSound(self);
        if(IsThirdPendingFlagSet(self)) SetMobyState(self,6,-1);
        else if(self!=gHeroState.target) { SetMobyState(self,3,0); goto choose_path; }
        break;
    }
    case 6:
        if(SetFirstPendingFlag(self)) { if(self[0x43]!=10) StartAnimationBlended(self,10,0,10); }
        StartMobyEffectFromEntry(self,FastMatrixHelperA(gHeroState.pos[0]-SF(self,0x10),gHeroState.pos[1]-SF(self,0x14)));
        RestartSparkTimerAndSound(self);
        break;
    case 8:
        if(SetFirstPendingFlag(self)) {
            u8 *p=CreateMoby(0x9bb);
            if(p) {
                u8 *ps;
                *(u8 **)(p+0xb8)=self; p[0x30]=255; qcopy(p+0x10,self+0x10);
                ps=*(u8 **)(p+0x68); *(u8 **)(ps+0x10)=self;
                SI(ps,0x20)=SH(self,0x34); SI(ps,0x30)=PackObjectHandle(self);
                SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
            }
        }
        SI(self,0x98)=0; SH(self,0x34)=(SH(self,0x34)|0x41)&0xefff;
        if(SH(self,0x96)>60) {
            D_L12_0021E180.flags[*(s16 *)(self+0xb2)]=self[0xb0]+2;
            { s32 saveid=self[0xb0];
            if(saveid==255 || (!(D_L12_001B2CE0[(u8)saveid]&128) && (D_0019B2E8[(u8)saveid+(D_001A79F0_gp<<4)]&128)))
                D_L12_0021EDF0.flags[*(s16 *)(self+0xb2)]=saveid+2; }
            MarkMobySpawned(self); return;
        }
        break;
    case 7:
        FastVecAdd(self+0x10,self+0x10,st+0x2a0);
        SF(st,0x2a8)-=D_L12_001B20A4*0.00027777778f;
        RestartSparkTimerAndSound(self);
        if(IsPointInCuboid(self+0x10,SI(st,0x29c))) {
            f32 len=vec_length_xy(st+0x2a0);
            if(len>0.016666668f) len=0.016666668f;
            FastVectorNormalizeHelper(st+0x2a0,st+0x2a0,len);
        }
        qcopy(from,self+0x10); from[2]+=0.5f;
        if(TestPointAgainstCollision(from,0,self,0.5f)) {
            qcopy(self+0x10,D_L12_001C0270); SF(self,0x18)-=0.5f;
            vec_scale_to_length(D_L12_001C0270+0x10,D_L12_001C0270+0x10,1.0f);
            if(FastVecDot(D_L12_001C0270+0x10,st+0x2a0)<0.0f) {
                FastVectorNormalize(st+0x2a0,st+0x2a0,D_L12_001C0270+0x10);
                FastVecScale(st+0x2a0,st+0x2a0,0.5f);
            }
            if(SF(D_L12_001C0270,0x18)>=0.95f) {
                SH(self,0x34)|=0x1000; SetMobyState(self,1,0);
                qcopy(st+0x150,self+0x10); ClearVector128(st+0x140);
            choose_path:
                SI(st,0x2b0)=FindVisiblePathPoint(self);
            }
        }
        break;
    }
    if(SI(st,0x2c4)!=-1 && !was0) ClearHelperObjectStates(D_L12_001B2E9C+(SI(st,0x2c4)<<8));
    if(SI(st,0x2c8)!=-1 && !was1) ClearHelperObjectStates(D_L12_001B2E9C+(SI(st,0x2c8)<<8));
    if(!(D_L12_001B29C8&15)) FindNearbyPathPointAtHeroHeight(self);
    if(self[0x31]) {
        SF(st,0x2bc)=FastAddRotations(SF(st,0x2bc),D_L12_001B20B0*0.00029088825f);
        SI(self,0x78)=PulseColor(D_L12_001B20B8[0],D_L12_001B20B8[1],SF(st,0x2bc));
    }
    SH(self,0x96)++;
    qcopy(st+0x2d0,self+0x10);
    SetValueAndStartSmoothChange(self,(f32 *)(st+0x2e0),D_L12_001B20C8,2,1);
}
