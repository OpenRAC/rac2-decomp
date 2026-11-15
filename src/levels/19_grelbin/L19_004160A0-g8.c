#include "include_asm.h"
#include "common.h"

#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define H(p,o) (*(u16 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define W(p,o) (*(s32 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
typedef struct {
    char pad0[0x80];
    float position[4];
    char pad90[0x40];
    float savedPosition[4];
    char padE0[0x21B0];
    char *target;
    int mode;
} GrelbinContext;
extern char D_00189E20[];
extern char D_L19_001A8F20[] MACRO_ADDR;
extern char D_L19_001BFEA0[], D_L19_001B9900[];
extern char D_L19_001FF5C0[];
typedef struct { char pad[0x464]; u8 entries[1]; } ActorFlags;
extern ActorFlags D_L19_0021EA30;
extern char *D_L19_001FB5A0[];
extern char *D_L19_001B2A1C __attribute__((sda));
extern void func_00310C88(void *);
extern int D_L19_001B1BF8 __attribute__((sda));
extern int D_L19_001B1D20 __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern unsigned char D_0019B4A8[];
extern int func_002ACD38(void *);
extern int func_00283CF0(float);
extern void func_L00_002D7140(void *);
extern int func_L19_004170D8(void *);
extern int func_002A8508(int,int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_00282978(void *);
extern int func_002A7820(int,int);
extern float func_00283248(float,float);
extern int func_L01_00322288(void *,float);
extern char *func_L00_002D70A0(int);
extern void func_002AA548(void *,void *,float,float,float,float);
extern float func_00282E80(void *,void *);
extern void func_002A6C58(void *,int,int);
extern void func_0029F338(void *);
extern int func_002AEB60(void *,float);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_002AB650(void *);
extern float func_0029F530(void *);
extern void func_002A7A00(void *,float,float);
extern float func_00282C48(float);
extern void func_00282CC0(void *,void *,void *);
extern char *func_00273730(void *,int,int,int,void *,void *,void *,int,float,float);
extern void func_002B37E8(void *,void *);
extern int func_002A77E0(int);
extern void func_002E5CF8(int,int,void *);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern void func_L19_00417A58(void *), func_L19_00417CA0(void *), func_L19_00417F88(void *);
extern void func_002A7988(void *,float,float);
extern float func_002A78D8(float,float), func_002A7878(float,float);
extern char *func_002C7970(void *,void *,int,int,int,int,int,float,float,float,int);
extern void func_002A8C00(void *,void *,int,void *,float);
extern void func_0029FC20(void *,int,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CF0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_L19_00417A00(void *);

/* Updates the Arctic Leviathan every frame. It turns toward its target, walks, fires and bursts in turn, and blows apart when it is destroyed. */
void func_L19_004160A0(char *moby)
{
    float burstVel[4] __attribute__((aligned(16)));
    float particleVel[4] __attribute__((aligned(16)));
    char hitMatrix[0x30] __attribute__((aligned(16)));
    char bodyMatrix[0x40] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    char *oldChild;
    char *vars;
    char *spawnedActor=0;
    int canAct,i=0,count=0;
    float sizeScale=0.0f;
    u16 flags;

    if (((GrelbinContext *)gHeroState)->mode == 0x6F) return;
    if (!IsObjectInSelectedZone(moby+0x10)) {
        B(moby,0x30)=FloatToInt((float)S(moby,0x32)+15.0f);
        return;
    }
    vars=P(moby,0x68);
    if (H(moby,0x34)&0x80) {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)|=0x80;
    } else {
        char *child=P(vars,0x2F0);
        if (child) H(child,0x34)&=0xFF7F;
    }
    if ((unsigned)(B(moby,0x95)-2)>=2 || ((GrelbinContext *)gHeroState)->mode==0x31 || F(vars,0x20)<=0.0f) {
        if (W(vars,0x310)) { EndCameraOverride(P(vars,0x314)); W(vars,0x310)=0; }
    }
    if (UpdateLeviathanHelperObject(moby)) {
        if (W(vars,0x310)) {EndCameraOverride(P(vars,0x314)); W(vars,0x310)=0;}
        MarkMobySpawned(moby);
        return;
    }
    switch (B(moby,0x95)) {
    case 0:
    {
        char *idleTarget;
        canAct=1;
        if (B(moby,0x21)!=0xFF && D_L19_001FB5A0[B(moby,0x21)]) {
            if (CountMobysInGroupNotInState(W(vars,0x308),-1)) canAct=0;
        }
        if (W(vars,0x30C)!=-1) {
            idleTarget=gMobyArray_L19+(W(vars,0x30C)<<8);
            if (idleTarget && B(idleTarget,0x20)!=0xFE && B(idleTarget,0x20)!=0xFD) canAct=0;
        }
        if (canAct) {
            if (W(vars,0x2FC)==1) {
                SetMobyState(moby,4,2);
                if (B(moby,0x43)) StartAnimationBlended(moby,0,0,10);
            } else if (W(vars,0x220) && FastDecTimer(vars+0x21E)) {
                SetMobyState(moby,2,1);
                W(vars,0x220)=0;
                if (W(vars,0x218)<300) W(vars,0x218)=RandomIntRange(480,600);
            }
        }
        idleTarget=P(vars,0x200);
        StartMobyEffectFromEntry(moby,FastMatrixHelperA(F(idleTarget,0x10)-F(moby,0x10),F(idleTarget,0x14)-F(moby,0x14)));
        break;
    }
    case 1:
        if ((W(vars,0x2FC)==1 || W(vars,0x2F8)==1) && B(moby,0x20)!=11) {
            SetMobyState(moby,7,2);
            if (B(moby,0x43)!=2) StartAnimationBlended(moby,2,0,10);
        }
        break;
    case 2:
    {
        char *attackTarget;
        if (!W(vars,0x310) && ((GrelbinContext *)gHeroState)->mode!=0x31) {
            P(vars,0x314)=AllocCameraOverrideSlot(5);
            F(P(vars,0x314),0)=10.0f;
            F(P(vars,0x314),4)=0.1f;
            W(P(vars,0x314),0xC)=0;
            W(vars,0x310)=1;
        }
        attackTarget=P(vars,0x200);
        StartMobyEffectFromEntry(moby,FastMatrixHelperA(F(attackTarget,0x10)-F(moby,0x10),F(attackTarget,0x14)-F(moby,0x14)));
        if (B(moby,0x20)!=4) StepValueTowardTarget(moby+0x18,vars+0x2D4,F(vars,0x2D0),0.003888888983f,0.003888888983f,0.7000000477f);
        if (B(moby,0x20)!=4 && B(moby,0x20)!=11) {
            if (vec_distance_xy(moby+0x10,((GrelbinContext *)gHeroState)->position)<12.0f) F(vars,0x2D0)=F(vars,0x2D8)-10.0f;
            else if (vec_distance_xy(moby+0x10,((GrelbinContext *)gHeroState)->position)<26.0f) F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            else F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
        }
        if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1 && B(moby,0x20)!=4 && B(moby,0x20)!=7 && B(moby,0x20)!=8 && B(moby,0x20)!=9 && B(moby,0x20)!=11) {
            SetMobyState(moby,2,1);
            if (B(moby,0x43)!=1) StartAnimationBlended(moby,1,0,10);
        }
        break;
    }
    case 4:
    {
        char *dyingTarget;
        dyingTarget=P(vars,0x200);
        StartMobyEffectFromEntry(moby,FastMatrixHelperA(F(dyingTarget,0x10)-F(moby,0x10),F(dyingTarget,0x14)-F(moby,0x14)));
        if (B(moby,0x20)!=4) StepValueTowardTarget(moby+0x18,vars+0x2D4,F(vars,0x2D0),0.3888888955f,0.3888888955f,0.7000000477f);
        /* fall through */
    }
    case 3:
        if (B(moby,0x60)&2) {SetDeathBits(moby,0,3);MarkMobySpawned(moby);return;}
    {
    char *childState;
    if (F(vars,0x20)<=0.0f && IsValueWithinStepOfThreshold(moby,45.0f) && !(D_L19_0021EA30.entries[(s16)(flags=H(moby,0xB2))])) {
        int counts=D_0019B4A8[((s16)flags>>1)+(gCurrentMapIndex<<10)];
        if (!((flags&1) ? (counts>>4)&7 : counts&7)) {
            spawnedActor=CreateMoby(0x1266 /* moby class 4710 */);
            if (spawnedActor) {
                u16 id=H(moby,0xB2);
                if (id&1) {
                    u8 *marks=D_0019B4A8+(((s16)id>>1)+(gCurrentMapIndex<<10));
                    if (((*marks>>4)&7)!=7) *marks+=0x10;
                } else {
                    u8 *marks=D_0019B4A8+(((s16)id>>1)+(gCurrentMapIndex<<10));
                    if ((*marks&7)!=7) *marks+=1;
                }
                B(spawnedActor,0x23)=0x50;
                H(spawnedActor,0x34)|=0x800;
                B(spawnedActor,0x30)=0xFF; H(spawnedActor,0x32)=0xFF; B(spawnedActor,0x31)=1;
                B(spawnedActor,0x20)=0; B(spawnedActor,0xBC)=0;
                qcopy(spawnedActor+0x10,P(vars,0x2F0)+0x10);
                F(spawnedActor,0x18)+=1.0f;
                func_002A0F48(spawnedActor);CopyHeroField38ToMoby(spawnedActor);
                childState=P(spawnedActor,0x68); F(childState,0)=0.1f;
                StartAnimationBlended(spawnedActor,1,0,20);
                F(spawnedActor,0x48)=F(childState,0)+F(childState,0);B(spawnedActor,0x20)=2;
            }
        }
    }
    }
        break;
    }
    switch (B(moby,0x20)) {
    case 4:
    {
        char *newActor;
        if (GetMobyAnimationValue(moby)>=4.0f && !W(vars,0x304) && !B(moby,0x42)) {
            char *shake=D_L19_001B9900;
            int j;
            F(shake,0x160)=0.25f;
            W(shake,0x168)=0x26;W(shake,0x16C)=0;
            H(moby,0x34)=(H(moby,0x34)&0xFFBE)|0x1000;
            W(moby,0x98)=W(P(moby,0x24),0x10);W(vars,0x304)=1;
            for (j=0;j<5;j++) {
                char *effect,*src;
                RandomDirectionVector(burstVel,0.2833333611f,0.3500000238f);
                burstVel[2]=FloatAbs(burstVel[2])*6.5f;
                if (burstVel[2]>1.2500001192f) burstVel[2]=1.2500001192f;
                FastVecAdd(burstVel,burstVel,D_L19_001A8F20);
                src=P(vars,0x2F0);
                effect=CreateCameraMoby(src,1,S(src,0xAA),j,src+0x10,src+0xF0,burstVel,0xFF,180.0f,45.0f);
                P(effect,0x64)=(char *)UpdateFadeOutMoby;
            }
            newActor=CreateMoby(0x1208 /* moby class 4616 */);
            if (newActor) {
                InitChildObjectFromParent(newActor,P(vars,0x2F0));
                H(newActor,0x32)=H(moby,0x32);B(newActor,0x30)=B(moby,0x30);
                oldChild=P(vars,0x2F0);
                {
                    int row;
                    for (row=0;row<4;row++) qcopy_nc(newActor+0xC0+row*16,oldChild+0xC0+row*16);
                }
                MarkMobySpawned(P(vars,0x2F0));P(vars,0x2F0)=newActor;
            }
        }
        if (B(moby,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-7.0f;
            SetMobyState(moby,7,-1);
            if (B(moby,0x43)!=2) StartAnimationBlended(moby,2,0,10);
        }
        break;
    }
    case 2:
        if (B(moby,0x60)&2) {
            count=B(moby,0x43);
            if (count!=RandomIntBelow(2)+3) StartAnimationBlended(moby,RandomIntBelow(2)+3,0,2);
            SetMobyState(moby,3,-1);
        }
        break;
    case 3:
        if (B(moby,0x60)&2) {
            if (B(moby,0x43)!=1) StartAnimationBlended(moby,1,0,4);
            SetMobyState(moby,2,-1);
        }
        break;
    case 5:
        if (B(moby,0x60)&2) {
            SetMobyState(moby,7,-1);
            if (B(moby,0x43)!=2) StartAnimationBlended(moby,2,0,6);
        }
        break;
    case 7:
        if (IsValueWithinStepOfThreshold(moby,13.0f)) PlayMobySound(4,0,moby);
        if (GetMobyAnimationValue(moby)>17.0f && B(moby,0x42)==2) {
            F(moby,0x48)=0.5f;AddDrawCallbackToList1(DrawLeviathanChargeFlash,moby);
            if (B(moby,0x60)&2) {
                qcopy(vars+0x2E0,vars+0x1F0);
                SetMobyState(moby,8,-1);
                if (B(moby,0x43)!=4) StartAnimationBlended(moby,4,20,20);
            }
        }
        break;
    case 8:
        AddDrawCallbackToList1(EmitBeamMuzzleGlow,moby);
        if (F(vars,0x22C)>=1.0f) {PlayMobySound(3,0,moby);SetMobyState(moby,9,-1);}
        break;
    case 9:
    {
        char *particle;
        AddDrawCallbackToList1(DrawGrelbinBeamEffect,moby);
        qcopy(burstVel,D_L19_001BFEA0);
        for (i=9;i>=0;i--) {
            SpawnRandomDirectionEffect(particleVel,0.2333333492f,0.2666666806f);
            if (particleVel[2]<0.0f) particleVel[2]=-particleVel[2];
            count=FloatToInt(RandomSignedFloatRange(2.0f,5.0f));
            sizeScale=RandomFloatRange(0.6f,1.0f);
            SpawnFadingDriftParticle(vars+0x2C0,particleVel,20,0x804020,count,127,127,210000.0f*sizeScale,2100.0f,0.00405555591f,D_L19_001B1BF8);
            count=FloatToInt(RandomSignedFloatRange(2.0f,5.0f));
            sizeScale=RandomFloatRange(0.6f,1.0f);
            particle=SpawnFadingDriftParticle(vars+0x2C0,particleVel,20,0x804040,count,48,48,630000.0f*sizeScale,4200.0f,0.00405555591f,0);
            if (particle) {
                char *g=D_L19_001FF5C0;
                B(particle,2)=B(P(g,0xD4),0);
            }
        }
        make_hit_descriptor(hitMatrix,moby,0x10001,D_L19_001A8F20,(float)B(vars,0x34));
        TransformMobyJointPoint(moby,0,bodyMatrix);
        qcopy(particleVel,bodyMatrix+0x30);
        vec_scale_to_length(offset,bodyMatrix,0.25f);
        FastVecAdd(particleVel,particleVel,offset);
        FastVecSub(delta,vars+0x2E0,particleVel);
        vec_scale_to_length(delta,delta,F(vars,0x238)*60.0f);
        FastVecAdd(delta,delta,particleVel);
        CollLine(particleVel,delta,0,moby,hitMatrix);
        if (H(moby,0x96)>40) {
            F(vars,0x234)-=0.05f;
            if (F(vars,0x234)<=0.0f) {
                F(vars,0x22C)=0.0f;F(vars,0x230)=1.0f;F(vars,0x228)=0.1f;F(vars,0x234)=0.1f;F(vars,0x238)=0.1f;
                SetMobyState(moby,10,-1);
                if (B(moby,0x43)!=3) StartAnimationBlended(moby,3,0,10);
            }
        } else {
            F(vars,0x234)+=0.1f;if (F(vars,0x234)>1.0f) F(vars,0x234)=1.0f;
            F(vars,0x238)+=0.2f;if (F(vars,0x238)>1.0f) F(vars,0x238)=1.0f;
        }
        break;
    }
    case 10:
        if (B(moby,0x60)&2) {
            SetMobyState(moby,7,-1);
            if (B(moby,0x43)!=2) StartAnimationBlended(moby,2,0,10);
        }
        break;
    case 11:
    {
        char *finalTarget;
        finalTarget=P(vars,0x200);
        if (finalTarget && S(finalTarget,0xAA)==0x10D0 /* Y.E.T.I. */) StartMobyEffectFromEntry(P(vars,0x200),FastMatrixHelperA(F(moby,0x10)-F(finalTarget,0x10),F(moby,0x14)-F(finalTarget,0x14)));
        if (B(moby,0x60)&2) {
            F(vars,0x2D0)=F(vars,0x2D8)-4.0f;
            if (W(vars,0x2FC)!=1 && W(vars,0x2F8)!=1) {
                SetMobyState(moby,7,2);
                if (B(moby,0x43)!=2) StartAnimationBlended(moby,2,0,10);
            } else {
                SetMobyState(moby,2,1);
                if (B(moby,0x43)!=1) StartAnimationBlended(moby,1,0,10);
            }
        }
        if (IsValueWithinStepOfThreshold(moby,11.0f) && B(moby,0x42)==6) {
            GrelbinContext *ctx;
            char *next;
            char *dead=P(vars,0x200);
            --gActiveYetiCount;
            MarkMobySpawned(dead);
            ctx=(GrelbinContext *)gHeroState;
            next=ctx->target;
            W(vars,0x204)=1;
            P(vars,0x200)=next;
            qcopy(vars+0x1F0,ctx->savedPosition);
        }
        break;
    }
    }
    TickMobyTimersAndAge(moby);
}
