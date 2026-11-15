/* func_L01_003B5878: a creature's per-frame state machine on object[0x95] (idle, waiting, airborne
 * leap, pursuit, attack, dispatch, removal), followed by the head-tracking ease of the angles at
 * +0xF4/+0xF0, each clamped to 40 degrees; same template as func_L01_003DAE58.
 * Its own unit: it needs -G8 ($gp reads) and -fno-expensive-optimizations, which keeps constant
 * call arguments out of pseudos (preserve_subexpressions_p), so they are rematerialised per call.
 * Reading the state words by index marks them as aggregate elements (MEM_IN_STRUCT_P), which lets
 * the scheduler move the 0x380 index read above the stack store of the leave weave, as retail does.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef struct {
    Quadword previous_position, delta, target;
    Quadword rotation[4], inverse[4], object_inverse[4];
} MotionWorkspace;
/* The dispatcher context is opaque here; its payload extent is not established. */
typedef struct DispatchContext DispatchContext;
typedef unsigned long DispatchFlags;

extern void func_L01_003B53C8(u8 *);
extern void func_L01_003B4C58(u8 *);
extern float func_002AA2E8(float *,float,float);
extern int func_00282948(int *);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern void func_002A7470(u8 *,int,int,int);
extern void func_002A7750(u8 *,int,int);
extern void func_L01_003B49D8(u8 *,void *);
extern int func_L01_003B4AD0(u8 *,void *,float *);
extern void func_L01_003B57A8(u8 *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern float func_L00_0031CDD0(void *,void *,float *,float,float);
extern int func_002E5CF8(int,int,char *);
extern float func_0029F530(char *);
extern float func_00283248(float,float);
extern void func_002A7CA0(void *,float,float,float,float,void *);
extern float func_00282C48(float);
extern int func_002B6318(unsigned char *);
extern int func_001163B0(void);
extern void func_L01_003B50C8(char *,int,float);
extern void func_002B5258(char *);
extern void func_002B5278(u8 *,float);
extern float func_00283CE0(int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern float func_00282E80(void *,void *);
extern float func_00283C80(float,float);
extern int func_L01_003B4C20(u8 *);
extern void func_L01_003B4BD8(u8 *);
extern float func_002AAA00(void *,float,float,float,float,void *,int);
extern int func_002A8D70(float,float,float,void *,int,int,int,int,int);
extern DispatchFlags func_002B1C20(void *,DispatchContext *);
extern void func_0029F338(void *);
extern void func_L01_003B4480(u8 *);
extern int func_00278E78(void);
extern void func_L01_003B5290(u8 *);
extern void func_002A6C58(u8 *,int,int);
/* Called with a null callback; a callback would receive the object. */
extern void func_L01_003E9CF8(u8 *,int,void (*)(u8 *));
extern void func_00283410(void *,void *);
extern void func_00283698(void *,void *);
extern int func_L00_0031BE88(char *);
extern void func_00283098(void *,void *,void *);
extern void func_L01_003B5310(u8 *);
/* Prefix views of the hero record (position, object) and of the collision query's hit object. */
typedef struct {
    u8 prefix[0x80];
    float position[4];
    u8 rest[0x2290-0x90];
    u8 *object;
} HeroTargetPrefix;
typedef struct { u8 prefix[0x18]; u8 *object; } CollisionQueryPrefix;
extern u8 D_00189E20[];
#define HERO_TARGET ((HeroTargetPrefix *)D_00189E20)
/* Mixed absolute/GP reads of the same mutable frame counter. */
extern int D_L01_001B2088 MACRO_ADDR;
extern int D_L01_001AFDB0 __attribute__((sda));
extern u8 *D_L01_001B255C __attribute__((sda));
/* 128-byte destination records with a 16-byte position at +0x30. */
typedef struct { u8 prefix[0x30]; float position[4]; u8 rest[0x40]; } DestinationRecord;
extern DestinationRecord *D_L01_001B264C MACRO_ADDR;
extern u8 D_L01_001BF900[];
#define COLLISION_QUERY ((CollisionQueryPrefix *)D_L01_001BF900)
extern u8 D_L01_001AC5A0[] MACRO_ADDR;

#define STATE_INT(o) (((int *)state)[(o)/4])
#define STATE_UINT(o) (((unsigned int *)state)[(o)/4])
#define STATE_FLOAT(o) (((float *)state)[(o)/4])
#define STATE_POINTER(o) (((u8 **)state)[(o)/4])

/* Updates this creature's idle, pursuit, airborne, attack and recovery phases. */
void func_L01_003B5878(u8 *object)
{
    /* Label tables for the phase and pursuit-action dispatches. */
    static void *const phases[8]={&&phase_idle,&&phase_wait,&&phase_airborne,&&phase_pursuit,
                           &&phase_attack,&&phase_dispatch,&&phase_removed,&&phase_removed};
    static void *const actions[8]={&&pursuit_idle,&&pursuit_wait,&&pursuit_weave,&&pursuit_done,
                            &&pursuit_straight,&&pursuit_done,&&pursuit_group,&&pursuit_leave};
    MotionWorkspace local;
    float duration, weave, straight, pursuit;
    u8 *state;
    float speed,frame,angle,pitch,yaw;
    int animation,first,i;
    unsigned int phase,action;
    /* Preserve the full dispatcher return while testing its two low status bits. */
    DispatchFlags flags;

    qcopy(&local.previous_position, object+0x10);
    state=*(u8 **)(object+0x68);
    if (object[0x95]) UpdateSwampBeastAwareness(object);
    phase=object[0x95];
    if (phase<8) goto *phases[phase];
    goto phase_done;

phase_idle:
    InitSwampBeastState(object);
    goto phase_done;

phase_wait:
    switch (object[0x20]) {
    case 0:
        if (STATE_INT(0x32C)>=21)
            ApproachValue((float *)(state+0x214),0.03333333507180214f,0.0011111111380159855f);
        else ApproachValue((float *)(state+0x214),0.0f,0.0011111111380159855f);
        if (FastFloatHelperD((int *)(state+0x32C))) {
            if (object[0x43]!=4) StartAnimationBlended(object,4,0,RandomIntRange(18,24));
            SetMobyState(object,1,-1);
        }
        if (STATE_INT(0x308)!=-1) MoveSwampBeast(object,state+0x200);
        break;
    case 1:
        if (object[0x60]&2) {
            STATE_INT(0x32C)=RandomIntRange(120,400);
            if (object[0x43]!=4) StartAnimationBlended(object,4,0,RandomIntRange(20,30));
            SetMobyState(object,0,-1);
        }
        break;
    case 2:
        qcopy(state+0x2E0, state+0x2D0);
        break;
    case 3:
        if (FastFloatHelperD((int *)(state+0x360))) {
            FindBestPatrolPosition(object,&local.target);
            FastVecSub(&local.delta,&local.target,object+0x10);
            if (FastVecLength(&local.delta)*0.03333333507180214f < 0.13333334028720856f)
                speed=FastVecLength(&local.delta)*0.03333333507180214f;
            else speed=0.13333334028720856f;
            vec_scale_to_length(&local.delta,&local.delta,speed);
            duration=0.0f;
            ((float *)&local.delta)[2]=ComputeShotLaunchSpeed(object+0x10,&local.target,&duration,speed,-0.004999999888241291f);
            qcopy(state+0x2F0, &local.delta);
            qcopy(state+0x2E0, &local.target);
            PlayMobySound(5,0,(char *)object);
            if (object[0x43]!=3) StartAnimationBlended(object,3,0,10);
            if (duration>0.0f) *(float *)(object+0x48)=38.0f/duration;
            SetMobyState(object,1,2);
        }
        break;
    }
    if (object[0x20]!=3 && STATE_INT(0x310)!=-1 && object[0x95]==1) {
        STATE_UINT(0x398)=STATE_UINT(0x390);
        STATE_INT(0x39C)=0;
        if (STATE_INT(0x244)==1 || STATE_INT(0x330)) {
            *(float *)(object+0x18)=STATE_FLOAT(0x34C);
            STATE_INT(0x39C)=0;
            STATE_UINT(0x398)=STATE_UINT(0x390);
            SetMobyState(object,3,1);
        }
    }
    goto phase_done;

phase_airborne:
    if (object[0x42]!=3) goto phase_done;
    frame=GetMobyAnimationValue((char *)object);
    if (!(frame>5.0f)) goto phase_done;
    FastVecAdd(object+0x10,object+0x10,state+0x2F0);
    angle=FastMatrixHelperA(STATE_FLOAT(0x2E0)-*(float *)(object+0x10),STATE_FLOAT(0x2E4)-*(float *)(object+0x14));
    MobySpringTurn(object,angle,STATE_FLOAT(0x124)*10.0f,STATE_FLOAT(0x134)*10.0f,STATE_FLOAT(0x12C)*10.0f,
                  state+0x1C4);
    STATE_FLOAT(0x2F8)-=0.004999999888241291f;
    if (!(STATE_FLOAT(0x2F8)<0.0f)) goto phase_done;
    if (!(FloatAbs(*(float *)(object+0x18)-STATE_FLOAT(0x2E8)) < -STATE_FLOAT(0x2F8))) goto phase_done;
    *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
    STATE_UINT(0x14C)=STATE_UINT(0x30C);
    qcopy(state+0x200, object+0x10);
    object[0xBC]=1;
    STATE_INT(0x330)=240;
    CheckObjectInsidePolygon(object);
    if (object[0x43]!=8) StartAnimationBlended(object,8,0,10);
    goto finish_attack;

phase_pursuit:
    action=object[0x20];
    if (action<8) goto *actions[action];
    goto pursuit_done;
pursuit_idle:
    if (STATE_INT(0x32C)>=21)
        ApproachValue((float *)(state+0x214),0.03333333507180214f,0.0011111111380159855f);
    else ApproachValue((float *)(state+0x214),0.0f,0.0011111111380159855f);
    if (FastFloatHelperD((int *)(state+0x32C))) {
        if (!object[0xBC]) {
            STATE_INT(0x32C)=180;
            animation=object[0x43];
            if (animation!=(Rand()&1)) {
                animation=Rand()&1;
                first=RandomIntRange(30,40);
                StartAnimationBlended(object,animation,0,first);
            }
        } else {
            STATE_INT(0x32C)=120;
            animation=object[0x43];
            if (animation!=(Rand()&1)+6)
                StartAnimationBlended(object,(Rand()&1)+6,0,RandomIntRange(30,40));
        }
        SetMobyState(object,1,-1);
    }
    MoveSwampBeast(object,state+0x200);
    SpawnSurfaceParticles((char *)object,1,-1.0f);
    goto pursuit_done;
pursuit_wait:
    if (!RandomIntBelow(7)) StepMovementAtOwnPosition((char *)object);
    if (FastFloatHelperD((int *)(state+0x32C)) && (object[0x60]&2)) {
        STATE_INT(0x32C)=RandomIntRange(120,400);
        animation=19;
        if (*(u16 *)(object+0xB2)&1) animation=8;
        StartAnimationBlended(object,animation,0,RandomIntRange(25,35));
        SetMobyState(object,0,-1);
    }
    goto pursuit_done;
pursuit_weave:
    weave=FastSinOrCosB(WrapAngleToPi(IntToFloat(D_L01_001B2088)*0.01163553074002266f))*0.8726646900177002f;
    if (vec_distance_xy(object+0x10,state+0x230)<4.75f) weave=0.0f;
    MoveSwampBeastWithSpeed(object,state+0x2E0,&weave);
    SpawnSurfaceParticles((char *)object,1,-1.0f);
    if (vec_distance_xy(object+0x10,STATE_POINTER(0x240)+0x10)<3.75f) {
        if (FloatAbs(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=FastMatrixHelperA(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            if (FastDiffRots(*(float *)(object+0xF8),angle)<0.174532949924469f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (object[0x43]!=10) StartAnimationBlended(object,10,D_L01_001AFDB0,RandomIntRange(16,22));
                SetMobyState(object,1,4);
            }
        }
    }
    goto pursuit_done;
pursuit_straight:
    {
        int destination=STATE_INT(0x310);
        straight=0.0f;
        if (destination==-1) MoveSwampBeastWithSpeed(object,state+0x2D0,&straight);
        else MoveSwampBeastWithSpeed(object,D_L01_001B264C[destination].position,&straight);
    }
    SpawnSurfaceParticles((char *)object,1,-1.0f);
    if ((object[0x60]&2) && (*(u64 *)(state+0x1A0)&0x18000000000ULL)!=0x10000000000ULL) {
        animation=object[0x43];
        if (animation!=(Rand()&1)) {
            animation=Rand()&1;
            first=RandomIntRange(30,40);
            StartAnimationBlended(object,animation,0,first);
        }
        SetMobyState(object,1,-1);
    }
    goto pursuit_done;
pursuit_group:
    STATE_UINT(0x398)=STATE_UINT(0x390);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    MoveSwampBeast(object,state+0x200);
    SpawnSurfaceParticles((char *)object,1,-1.0f);
    if (STATE_INT(0x244)==1 && (STATE_INT(0x38C)==-1 ||
        gMobyTable_L01[STATE_INT(0x38C)*256+0xBC])) SetMobyState(object,7,-1);
    goto pursuit_done;
pursuit_leave:
    pursuit=FastSinOrCosB(WrapAngleToPi(IntToFloat(D_L01_001B2088)*0.01163553074002266f))*0.8726646900177002f;
    qcopy(state+0x2E0, D_L01_001B264C[STATE_INT(0x380)].position);
    MoveSwampBeastWithSpeed(object,state+0x2E0,&pursuit);
    SpawnSurfaceParticles((char *)object,1,-1.0f);
    if ((STATE_UINT(0x1A4)&0x80) && !object[0x31]) {
        MarkMobySpawned(object);
        return;
    }

pursuit_done:
    if (object[0x95]!=3) goto mirror_hero;
    if (object[0x20]==4) goto mirror_hero;
    if (object[0x20]==7) goto mirror_hero;
    if (object[0x20]==6) goto mirror_hero;
    STATE_UINT(0x398)=STATE_UINT(0x394);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    if (STATE_INT(0x244)!=1 && !STATE_INT(0x330)) goto cancel_pursuit;
    {
        if (object[0x21]!=255 && **(int **)(state+0x36C)!=*(short *)(object+0xB2) &&
            **(int **)(state+0x370)!=*(short *)(object+0xB2)) goto cancel_pursuit;
        if (!(FloatAbs(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<1.0f)) goto cancel_pursuit;
        STATE_INT(0x330)=240;
        object[0xBC]=1;
        STATE_UINT(0x14C)=STATE_UINT(0x30C);
        if (object[0x20]==2) goto copy_pursuit_target;
        if (object[0x21]!=255 && **(int **)(state+0x33C)>1) goto pursuit_distance;
        if (STATE_INT(0x334)) goto pursuit_distance;
        if (!(vec_distance_xy(object+0x10,STATE_POINTER(0x240)+0x10)<14.0f)) goto pursuit_distance;
        qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
        animation=19;
        if (*(u16 *)(object+0xB2)&1) animation=8;
        StartAnimationBlended(object,animation,0,RandomIntRange(20,30));
        ClaimGroupSlot(object);
        SetMobyState(object,2,-1);
        goto pursuit_distance;
    }
copy_pursuit_target:
    qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
    goto pursuit_distance;
cancel_pursuit:
    if (object[0x20]==2) {
        ReleaseGroupSlot(object);
        object[0xBC]=0;
        animation=object[0x43];
        if (animation!=(Rand()&1)) {
            animation=Rand()&1;
            first=RandomIntRange(30,40);
            StartAnimationBlended(object,animation,0,first);
        }
        SetMobyState(object,1,-1);
    }
    goto pursuit_distance;
mirror_hero:
    if (STATE_POINTER(0x240)==HERO_TARGET->object)
        qcopy(state+0x2E0, HERO_TARGET->position);
pursuit_distance:
    if (vec_distance_xy(object+0x10,STATE_POINTER(0x240)+0x10)<3.5f) {
        if (FloatAbs(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=FastMatrixHelperA(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            if (FastDiffRots(*(float *)(object+0xF8),angle)<0.523598849773407f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (object[0x43]!=10) StartAnimationBlended(object,10,D_L01_001AFDB0,RandomIntRange(8,12));
                SetMobyState(object,1,4);
            } else {
                float *heading=(float *)(object+0xF8);
                angle=FastMatrixHelperA(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
                ApproachTargetWithDirectionMode(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
            }
        }
    }
    goto phase_done;

phase_attack:
    if (STATE_POINTER(0x240)) {
        if (!RandomIntBelow(7)) {
            angle=FastMatrixHelperA(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            StepMovementAtOwnPositionWithFactor(object,angle);
        } else {
            float *heading=(float *)(object+0xF8);
            angle=FastMatrixHelperA(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            ApproachTargetWithDirectionMode(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
        }
    } else if (!RandomIntBelow(7)) StepMovementAtOwnPosition((char *)object);
    frame=GetMobyAnimationValue((char *)object);
    if (object[0x42]==10 && frame>=18.0f && frame<=25.0f) {
        for (i=0;i<5;i++) {
            if (TestHitAtBone(0.5f,(float)state[0x34],1.0f,object,i,0x4000001,0,1,0) &&
                COLLISION_QUERY->object==HERO_TARGET->object) state[0x35C]=1;
        }
    }
    if (!(frame>30.0f) && (object[0x42]==10 || object[0x43]==10)) goto phase_done;
    if (state[0x35C]) {
        STATE_INT(0x334)=100;
        if (object[0x43]!=11) StartAnimationBlended(object,11,0,RandomIntRange(25,30));
    } else {
        STATE_INT(0x334)=40;
        if (object[0x43]!=8) StartAnimationBlended(object,8,0,RandomIntRange(25,30));
    }
    state[0x35C]=0;
    ReleaseGroupSlot(object);
finish_attack:
    STATE_UINT(0x398)=STATE_UINT(0x394);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    SetMobyState(object,1,3);
    goto phase_done;

phase_dispatch:
    flags=DispatchActionByKind(object,(DispatchContext *)(state+0x60));
    if ((flags&1UL)==1UL) SetMobyState(object,0,7);
    else if ((flags&2UL)==2UL) {
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        SpawnSwampBeastBubbles(object);
        ReleaseGroupSlot(object);
        if (GetCollHitMaterial()==3) {
            if (object[0x43]!=4) StartAnimationBlended(object,4,0,110);
            SetMobyState(object,0,6);
        } else {
            STATE_INT(0x384)=-1;
            STATE_UINT(0x398)=STATE_UINT(0x394);
            STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
            animation=19;
            if (*(u16 *)(object+0xB2)&1) animation=8;
            StartAnimationBlended(object,animation,0,RandomIntRange(18,24));
            if (!CheckObjectInsidePolygon(object)) SetMobyState(object,4,3);
            else SetMobyState(object,1,3);
        }
    }
    goto phase_done;

phase_removed:
    AlertSwampBeastGroup(object);
    SetDeathBits(object,0,3);
    SpawnSwampBeastBubbles(object);
    SpawnSurfaceParticles((char *)object,5,-1.0f);
    ReleaseGroupSlot(object);
    QueueMobyForGlowEffect(object,0,0);

phase_done:
    if ((unsigned int)(object[0x95]-3)<2) {
        local.target=0;
        ((float *)&local.target)[2]=*(float *)(object+0xF8);
        local.delta=local.target;
        euler_to_matrix(local.rotation,&local.delta);
        matrix_from_basis_rows(local.inverse,local.rotation);
        matrix_from_basis_rows(local.object_inverse,object+0xC0);
        {
            Quadword *v;
            u8 *target = STATE_POINTER(0x198);

            if (target && !HasPendingInnerFlag((char *)target)) {
                v = &local.target;
                qcopy(v, D_L01_001AC5A0);
            } else
                vec_scale_to_length(&local.target,state+0x160,1.0f);
            v = &local.target;
            matrix_mul_vec3(v,v,local.inverse);
        }
        yaw=FastMatrixHelperA(((float *)&local.target)[2],((float *)&local.target)[0]);
        pitch=-FastMatrixHelperA(((float *)&local.target)[2],((float *)&local.target)[1]);
        if (yaw>0.698131799697876f) yaw=0.698131799697876f;
        else if (yaw<-0.698131799697876f) yaw=-0.698131799697876f;
        if (pitch>0.698131799697876f) pitch=0.698131799697876f;
        else if (pitch<-0.698131799697876f) pitch=-0.698131799697876f;
        ApproachTargetWithDirectionMode(object+0xF4,yaw,0.0017453294713050127f,0.0017453294713050127f,0.10471977293491364f,state+0x358,0);
        ApproachTargetWithDirectionMode(object+0xF0,pitch,0.0017453294713050127f,0.0017453294713050127f,0.10471977293491364f,state+0x354,0);
    }
    UpdateSwampBeastTimers(object);
}
