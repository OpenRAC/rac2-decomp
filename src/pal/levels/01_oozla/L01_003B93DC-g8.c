/* func_PAL_L01_003B93DC, the PAL copy of func_L01_003B5878: a creature's per-frame state machine on object[0x95] (idle, waiting, airborne
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

extern void func_PAL_L01_003B8F28(u8 *);
extern void func_PAL_L01_003B8798(u8 *);
extern float func_002AA2E8(float *,float,float);
extern int func_00282948(int *);
extern int func_002A7820(int,int);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(u8 *,int,int,int);
extern void func_002A7750(u8 *,int,int);
extern void func_PAL_L01_003B8518(u8 *,void *);
extern int func_PAL_L01_003B8610(u8 *,void *,float *);
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
extern void func_PAL_002B5E10(char *);
extern void func_PAL_002B5E30(u8 *,float);
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
extern void func_PAL_L01_003B7FC0(u8 *);
extern int func_00278E78(void);
extern void func_L01_003B5290(u8 *);
extern void func_PAL_002A7650(u8 *,int,int);
/* Called with a null callback; a callback would receive the object. */
extern void func_L01_003E9CF8(u8 *,int,void (*)(u8 *));
extern void func_00283410(void *,void *);
extern void func_00283698(void *,void *);
extern int func_L00_0031BE88(char *);
extern void func_00283098(void *,void *,void *);
extern void func_PAL_L01_003B8E50(u8 *);
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
void func_PAL_L01_003B93DC(u8 *object)
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
    if (object[0x95]) func_PAL_L01_003B8F28(object);
    phase=object[0x95];
    if (phase<8) goto *phases[phase];
    goto phase_done;

phase_idle:
    func_PAL_L01_003B8798(object);
    goto phase_done;

phase_wait:
    switch (object[0x20]) {
    case 0:
        if (STATE_INT(0x32C)>=18)
            func_002AA2E8((float *)(state+0x214),0.040000003f,0.0016000001f);
        else func_002AA2E8((float *)(state+0x214),0.0f,0.0016000001f);
        if (func_00282948((int *)(state+0x32C))) {
            if (object[0x43]!=4) func_PAL_002A7E68(object,4,0,func_002A7820(18,24));
            func_002A7750(object,1,-1);
        }
        if (STATE_INT(0x308)!=-1) func_PAL_L01_003B8518(object,state+0x200);
        break;
    case 1:
        if (object[0x60]&2) {
            STATE_INT(0x32C)=func_002A7820(100,333);
            if (object[0x43]!=4) func_PAL_002A7E68(object,4,0,func_002A7820(20,30));
            func_002A7750(object,0,-1);
        }
        break;
    case 2:
        qcopy(state+0x2E0, state+0x2D0);
        break;
    case 3:
        if (func_00282948((int *)(state+0x360))) {
            func_L01_003B57A8(object,&local.target);
            func_00282CF0(&local.delta,&local.target,object+0x10);
            if (func_00282DF0(&local.delta)*0.03333333507180214f < 0.16000001f)
                speed=func_00282DF0(&local.delta)*0.03333333507180214f;
            else speed=0.16000001f;
            func_00282F20(&local.delta,&local.delta,speed);
            duration=0.0f;
            ((float *)&local.delta)[2]=func_L00_0031CDD0(object+0x10,&local.target,&duration,speed,-0.0072000003f);
            qcopy(state+0x2F0, &local.delta);
            qcopy(state+0x2E0, &local.target);
            func_002E5CF8(5,0,(char *)object);
            if (object[0x43]!=3) func_PAL_002A7E68(object,3,0,10);
            if (duration>0.0f) *(float *)(object+0x48)=38.0f/duration;
            func_002A7750(object,1,2);
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
            func_002A7750(object,3,1);
        }
    }
    goto phase_done;

phase_airborne:
    if (object[0x42]!=3) goto phase_done;
    frame=func_0029F530((char *)object);
    if (!(frame>5.0f)) goto phase_done;
    func_00282CC0(object+0x10,object+0x10,state+0x2F0);
    angle=func_00283248(STATE_FLOAT(0x2E0)-*(float *)(object+0x10),STATE_FLOAT(0x2E4)-*(float *)(object+0x14));
    func_002A7CA0(object,angle,STATE_FLOAT(0x124)*10.0f,STATE_FLOAT(0x134)*10.0f,STATE_FLOAT(0x12C)*10.0f,
                  state+0x1C4);
    STATE_FLOAT(0x2F8)-=0.0072000003f;
    if (!(STATE_FLOAT(0x2F8)<0.0f)) goto phase_done;
    if (!(func_00282C48(*(float *)(object+0x18)-STATE_FLOAT(0x2E8)) < -STATE_FLOAT(0x2F8))) goto phase_done;
    *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
    STATE_UINT(0x14C)=STATE_UINT(0x30C);
    qcopy(state+0x200, object+0x10);
    object[0xBC]=1;
    STATE_INT(0x330)=200;
    func_002B6318(object);
    if (object[0x43]!=8) func_PAL_002A7E68(object,8,0,10);
    goto finish_attack;

phase_pursuit:
    action=object[0x20];
    if (action<8) goto *actions[action];
    goto pursuit_done;
pursuit_idle:
    if (STATE_INT(0x32C)>=18)
        func_002AA2E8((float *)(state+0x214),0.040000003f,0.0016000001f);
    else func_002AA2E8((float *)(state+0x214),0.0f,0.0016000001f);
    if (func_00282948((int *)(state+0x32C))) {
        if (!object[0xBC]) {
            STATE_INT(0x32C)=150;
            animation=object[0x43];
            if (animation!=(func_001163B0()&1)) {
                animation=func_001163B0()&1;
                first=func_002A7820(30,40);
                func_PAL_002A7E68(object,animation,0,first);
            }
        } else {
            STATE_INT(0x32C)=100;
            animation=object[0x43];
            if (animation!=(func_001163B0()&1)+6)
                func_PAL_002A7E68(object,(func_001163B0()&1)+6,0,func_002A7820(30,40));
        }
        func_002A7750(object,1,-1);
    }
    func_PAL_L01_003B8518(object,state+0x200);
    func_L01_003B50C8((char *)object,1,-1.0f);
    goto pursuit_done;
pursuit_wait:
    if (!func_002A77E0(7)) func_PAL_002B5E10((char *)object);
    if (func_00282948((int *)(state+0x32C)) && (object[0x60]&2)) {
        STATE_INT(0x32C)=func_002A7820(100,333);
        animation=19;
        if (*(u16 *)(object+0xB2)&1) animation=8;
        func_PAL_002A7E68(object,animation,0,func_002A7820(25,35));
        func_002A7750(object,0,-1);
    }
    goto pursuit_done;
pursuit_weave:
    weave=func_00283198(func_002ABB18(func_00283CE0(D_L01_001B2088)*0.013962637f))*0.8726646900177002f;
    if (func_00282E80(object+0x10,state+0x230)<4.75f) weave=0.0f;
    func_PAL_L01_003B8610(object,state+0x2E0,&weave);
    func_L01_003B50C8((char *)object,1,-1.0f);
    if (func_00282E80(object+0x10,STATE_POINTER(0x240)+0x10)<3.75f) {
        if (func_00282C48(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=func_00283248(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            if (func_00283C80(*(float *)(object+0xF8),angle)<0.174532949924469f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (object[0x43]!=10) func_PAL_002A7E68(object,10,D_L01_001AFDB0,func_002A7820(16,22));
                func_002A7750(object,1,4);
            }
        }
    }
    goto pursuit_done;
pursuit_straight:
    {
        int destination=STATE_INT(0x310);
        straight=0.0f;
        if (destination==-1) func_PAL_L01_003B8610(object,state+0x2D0,&straight);
        else func_PAL_L01_003B8610(object,D_L01_001B264C[destination].position,&straight);
    }
    func_L01_003B50C8((char *)object,1,-1.0f);
    if ((object[0x60]&2) && (*(u64 *)(state+0x1A0)&0x18000000000ULL)!=0x10000000000ULL) {
        animation=object[0x43];
        if (animation!=(func_001163B0()&1)) {
            animation=func_001163B0()&1;
            first=func_002A7820(30,40);
            func_PAL_002A7E68(object,animation,0,first);
        }
        func_002A7750(object,1,-1);
    }
    goto pursuit_done;
pursuit_group:
    STATE_UINT(0x398)=STATE_UINT(0x390);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    func_PAL_L01_003B8518(object,state+0x200);
    func_L01_003B50C8((char *)object,1,-1.0f);
    if (STATE_INT(0x244)==1 && (STATE_INT(0x38C)==-1 ||
        D_L01_001B255C[STATE_INT(0x38C)*256+0xBC])) func_002A7750(object,7,-1);
    goto pursuit_done;
pursuit_leave:
    pursuit=func_00283198(func_002ABB18(func_00283CE0(D_L01_001B2088)*0.013962637f))*0.8726646900177002f;
    qcopy(state+0x2E0, D_L01_001B264C[STATE_INT(0x380)].position);
    func_PAL_L01_003B8610(object,state+0x2E0,&pursuit);
    func_L01_003B50C8((char *)object,1,-1.0f);
    if ((STATE_UINT(0x1A4)&0x80) && !object[0x31]) {
        func_0029F338(object);
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
        if (!(func_00282C48(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<1.0f)) goto cancel_pursuit;
        STATE_INT(0x330)=200;
        object[0xBC]=1;
        STATE_UINT(0x14C)=STATE_UINT(0x30C);
        if (object[0x20]==2) goto copy_pursuit_target;
        if (object[0x21]!=255 && **(int **)(state+0x33C)>1) goto pursuit_distance;
        if (STATE_INT(0x334)) goto pursuit_distance;
        if (!(func_00282E80(object+0x10,STATE_POINTER(0x240)+0x10)<14.0f)) goto pursuit_distance;
        qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
        animation=19;
        if (*(u16 *)(object+0xB2)&1) animation=8;
        func_PAL_002A7E68(object,animation,0,func_002A7820(20,30));
        func_L01_003B4C20(object);
        func_002A7750(object,2,-1);
        goto pursuit_distance;
    }
copy_pursuit_target:
    qcopy(state+0x2E0, STATE_POINTER(0x240)+0x10);
    goto pursuit_distance;
cancel_pursuit:
    if (object[0x20]==2) {
        func_L01_003B4BD8(object);
        object[0xBC]=0;
        animation=object[0x43];
        if (animation!=(func_001163B0()&1)) {
            animation=func_001163B0()&1;
            first=func_002A7820(30,40);
            func_PAL_002A7E68(object,animation,0,first);
        }
        func_002A7750(object,1,-1);
    }
    goto pursuit_distance;
mirror_hero:
    if (STATE_POINTER(0x240)==HERO_TARGET->object)
        qcopy(state+0x2E0, HERO_TARGET->position);
pursuit_distance:
    if (func_00282E80(object+0x10,STATE_POINTER(0x240)+0x10)<3.5f) {
        if (func_00282C48(*(float *)(object+0x18)-*(float *)(STATE_POINTER(0x240)+0x18))<0.5f) {
            angle=func_00283248(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            if (func_00283C80(*(float *)(object+0xF8),angle)<0.523598849773407f) {
                qzero(state+0x1B0);
                state[0x35C]=0;
                if (object[0x43]!=10) func_PAL_002A7E68(object,10,D_L01_001AFDB0,func_002A7820(8,12));
                func_002A7750(object,1,4);
            } else {
                float *heading=(float *)(object+0xF8);
                angle=func_00283248(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
                func_002AAA00(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
            }
        }
    }
    goto phase_done;

phase_attack:
    if (STATE_POINTER(0x240)) {
        if (!func_002A77E0(7)) {
            angle=func_00283248(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            func_PAL_002B5E30(object,angle);
        } else {
            float *heading=(float *)(object+0xF8);
            angle=func_00283248(*(float *)(STATE_POINTER(0x240)+0x10)-*(float *)(object+0x10),*(float *)(STATE_POINTER(0x240)+0x14)-*(float *)(object+0x14));
            func_002AAA00(heading,angle,STATE_FLOAT(0x124),STATE_FLOAT(0x128),STATE_FLOAT(0x12C),state+0x1C4,0);
        }
    } else if (!func_002A77E0(7)) func_PAL_002B5E10((char *)object);
    frame=func_0029F530((char *)object);
    if (object[0x42]==10 && frame>=18.0f && frame<=25.0f) {
        for (i=0;i<5;i++) {
            if (func_002A8D70(0.5f,(float)state[0x34],1.0f,object,i,0x4000001,0,1,0) &&
                COLLISION_QUERY->object==HERO_TARGET->object) state[0x35C]=1;
        }
    }
    if (!(frame>30.0f) && (object[0x42]==10 || object[0x43]==10)) goto phase_done;
    if (state[0x35C]) {
        STATE_INT(0x334)=83;
        if (object[0x43]!=11) func_PAL_002A7E68(object,11,0,func_002A7820(25,30));
    } else {
        STATE_INT(0x334)=33;
        if (object[0x43]!=8) func_PAL_002A7E68(object,8,0,func_002A7820(25,30));
    }
    state[0x35C]=0;
    func_L01_003B4BD8(object);
finish_attack:
    STATE_UINT(0x398)=STATE_UINT(0x394);
    STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
    func_002A7750(object,1,3);
    goto phase_done;

phase_dispatch:
    flags=func_002B1C20(object,(DispatchContext *)(state+0x60));
    if ((flags&1UL)==1UL) func_002A7750(object,0,7);
    else if ((flags&2UL)==2UL) {
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        func_PAL_L01_003B7FC0(object);
        func_L01_003B4BD8(object);
        if (func_00278E78()==3) {
            if (object[0x43]!=4) func_PAL_002A7E68(object,4,0,110);
            func_002A7750(object,0,6);
        } else {
            STATE_INT(0x384)=-1;
            STATE_UINT(0x398)=STATE_UINT(0x394);
            STATE_FLOAT(0x39C)=STATE_FLOAT(0x388);
            animation=19;
            if (*(u16 *)(object+0xB2)&1) animation=8;
            func_PAL_002A7E68(object,animation,0,func_002A7820(18,24));
            if (!func_002B6318(object)) func_002A7750(object,4,3);
            else func_002A7750(object,1,3);
        }
    }
    goto phase_done;

phase_removed:
    func_L01_003B5290(object);
    func_PAL_002A7650(object,0,3);
    func_PAL_L01_003B7FC0(object);
    func_L01_003B50C8((char *)object,5,-1.0f);
    func_L01_003B4BD8(object);
    func_L01_003E9CF8(object,0,0);

phase_done:
    if ((unsigned int)(object[0x95]-3)<2) {
        local.target=0;
        ((float *)&local.target)[2]=*(float *)(object+0xF8);
        local.delta=local.target;
        func_00283410(local.rotation,&local.delta);
        func_00283698(local.inverse,local.rotation);
        func_00283698(local.object_inverse,object+0xC0);
        {
            Quadword *v;
            u8 *target = STATE_POINTER(0x198);

            if (target && !func_L00_0031BE88((char *)target)) {
                v = &local.target;
                qcopy(v, D_L01_001AC5A0);
            } else
                func_00282F20(&local.target,state+0x160,1.0f);
            v = &local.target;
            func_00283098(v,v,local.inverse);
        }
        yaw=func_00283248(((float *)&local.target)[2],((float *)&local.target)[0]);
        pitch=-func_00283248(((float *)&local.target)[2],((float *)&local.target)[1]);
        if (yaw>0.698131799697876f) yaw=0.698131799697876f;
        else if (yaw<-0.698131799697876f) yaw=-0.698131799697876f;
        if (pitch>0.698131799697876f) pitch=0.698131799697876f;
        else if (pitch<-0.698131799697876f) pitch=-0.698131799697876f;
        func_002AAA00(object+0xF4,yaw,0.0025132746f,0.0025132746f,0.12566373f,state+0x358,0);
        func_002AAA00(object+0xF0,pitch,0.0025132746f,0.0025132746f,0.12566373f,state+0x354,0);
    }
    func_PAL_L01_003B8E50(object);
}
