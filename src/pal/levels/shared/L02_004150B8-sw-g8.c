#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    int primary,secondary,key,secondaryKey,reserved10;
    u8 *children[3];
    float orbitA,orbitB,rateA,rateB;
    int reserved30;
    float timer;
    int handle;
    float opacity;
    int variant;
} OrbitState;
typedef void (*DrawCallback)(void *);
extern void func_L02_00410E58(u8 *);
extern void func_L02_00410D00(u8 *);
extern void func_PAL_L02_00416108(u8 *);
extern void func_PAL_L02_00415BD0(u8 *);
extern void func_L02_00411530(u8 *);
extern int func_002E5CF8(int,int,char *);
extern void func_L00_002D40A0(Quad *,int,float);
extern int func_002A8C28(void *,float,float *,int,float,float,int,int,int);
extern int func_L00_002D40F0(void);
extern int func_PAL_L00_002C4480(int,int);
extern void func_L00_002E6CF0(DrawCallback,void *);
extern void func_L00_002E6EF8(DrawCallback,void *);
extern float func_002AA2E8(float *,float,float);
extern void func_002A7750(u8 *,int,int);
extern void func_PAL_L00_002B9CD8(void *,void *,int,int);
extern int func_002B3868(u8 *);
extern float func_002AA548(float *,float *,float,float,float,float);
extern void func_L00_002C8BA8(int);
extern void func_PAL_L00_00305110(int,int);
extern int D_001A79F0 MACRO_ADDR;
extern u8 D_0019B2E8[];
typedef struct {
    u8 reserved0[0x33C];
    u8 *selected;
    u8 reserved340[0xE];
    short busy;
    u8 reserved350[0x1F65];
    u8 active;
} Resident;
extern Resident D_00189E20;
extern u32 D_00138324 NOT_SDA;
extern int D_L02_001A8FB4 __attribute__((sda));
extern u8 *D_L02_001B359C MACRO_ADDR;
extern float D_L02_001B1A58 __attribute__((sda));
extern float D_L02_001B1A5C __attribute__((sda));
extern float D_L02_001B1A60 __attribute__((sda));

/* Run the control's activation, orbit and captured-object transition states. */
void func_PAL_L02_004150B8(u8 *object)
{
    OrbitState *state=*(OrbitState **)(object+0x68);
    u8 **slot;
    int left,answer;
    Vector position;
    switch(object[0x20]) {
    case 0:
        object[0x30]=0xFF;object[0x20]=1;
        func_L02_00410E58(object);
        func_L02_00410D00(object);
        break;
    case 1:
        if(state->key>=0 && !(D_0019B2E8[state->key+D_001A79F0*16]&0x80)) {
            *(int *)(object+0x98)=0;
            *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)|0x41)&0xEFFF;
            slot=state->children;left=2;
            do {
                *(u16 *)(*slot+0x34)|=0x41;
                *(u16 *)(*slot+0x34)&=0xEFFF;
                *(int *)(*slot+0x98)=0;
                slot++;
            } while(--left>=0);
            break;
        }
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;
            *(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);
            slot++;
        } while(--left>=0);
        if(state->primary!=-1 && D_00189E20.selected==object) {
            if(D_00189E20.busy) goto propagate;
            func_PAL_L02_00416108(object);
            if((D_00138324&0x10) && D_L02_001A8FB4==11) {
                func_002E5CF8(0,0,(char *)object);
                object[0x20]=2;state->rateA=0;state->rateB=0;
                func_L00_002D40A0((Quad *)(object+0x10),0,*(float *)(object+0xF8));
                func_002A8C28(object,1.5f,(float *)(object+0x10),0x10000,20.0f,1.0f,0,1,0);
            }
        }
        break;
    case 2:
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        answer=func_L00_002D40F0();
        if(state->orbitA<1.0f) {
            func_002AA548(&state->orbitA,&state->rateA,1.0f,D_L02_001B1A58*0.00040000002f,D_L02_001B1A5C*0.00040000002f,D_L02_001B1A60*0.020000001f);
        } else if(state->orbitB<1.0f) {
            func_002AA548(&state->orbitB,&state->rateB,1.0f,D_L02_001B1A58*0.00040000002f,D_L02_001B1A5C*0.00040000002f,D_L02_001B1A60*0.020000001f);
        } else if(D_L02_001A8FB4!=11 || !(state->orbitA>0.25f)) {
            if(answer==2) {func_PAL_L00_002C4480(0x6F,1);state->timer=1.95f;object[0x20]=3;}
            else if(answer==0) object[0x20]=4;
        }
        func_L02_00410D00(object);
        break;
    case 3: {
        u8 *data;
        u8 *actor;
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        if(state->timer!=0.0f) {
            func_L00_002E6CF0((DrawCallback)func_PAL_L02_00415BD0,object);
            func_002AA2E8(&state->timer,0,0.080000006f);
            break;
        }
            D_00189E20.active=1;
            if(state->handle>=0) {func_002A7750(object,5,-1);break;}
            {
                actor=D_L02_001B359C+state->primary*0x100;
                if(state->secondary!=-1 && (D_0019B2E8[state->secondaryKey+D_001A79F0*16]&0x80)) actor=D_L02_001B359C+state->secondary*0x100;
                data=*(u8 **)(actor+0x68);
                qcopy(&position,actor+0x10);position.f[2]+=0.2f;
                func_PAL_L00_002B9CD8(&position,actor+0xF0,0,1);
                actor[0x20]=4;
                *(float *)(data+0x34)=0;*(float *)(data+0x28)=0;*(float *)(data+0x2C)=0;
                *(float *)(data+0x20)=1;*(float *)(data+0x24)=1;
                func_002E5CF8(1,0,(char *)actor);
                object[0x20]=1;state->orbitA=0;state->orbitB=0;state->rateA=0;state->rateB=0;state->timer=1.95f;
                func_L02_00410D00(object);
            }
        break;
    }
    case 4:
        func_002B3868(object);
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        if(state->timer<1.95f) {
            func_L00_002E6CF0((DrawCallback)func_PAL_L02_00415BD0,object);
            func_002AA2E8(&state->timer,1.95f,0.080000006f);
        } else {
            if(state->orbitB>0.0f) {
                func_002AA548(&state->orbitB,&state->rateA,0.0f,D_L02_001B1A58*0.00040000002f,D_L02_001B1A5C*0.00040000002f,D_L02_001B1A60*0.020000001f);
            } else if(state->orbitA>0.0f) {
                func_002AA548(&state->orbitA,&state->rateB,0.0f,D_L02_001B1A58*0.00040000002f,D_L02_001B1A5C*0.00040000002f,D_L02_001B1A60*0.020000001f);
            } else object[0x20]=1;
        }
        func_L02_00410D00(object);
        break;
    case 6:
        if(func_002B3868(object)) {
            state->orbitB=1;state->orbitA=1;func_L02_00410D00(object);state->opacity=0;
        }
        state->opacity+=0.02f;D_00189E20.active=1;
        if(state->opacity>=1.2f) {
            func_L00_002C8BA8(0);object[0x20]=4;
            state->rateA=0;state->rateB=0;state->timer=0;state->orbitA=1;state->orbitB=1;
            func_002E5CF8(1,0,(char *)object);
        }
        func_L00_002E6EF8((DrawCallback)func_L02_00411530,object);
        break;
    case 5: {
        u8 *actor;
        if(func_002B3868(object)) state->opacity=1;
        state->opacity-=0.02f;D_00189E20.active=1;
        if(state->opacity<=-0.2f) {
            actor=D_L02_001B359C+state->primary*0x100;
            actor[0x20]=6;object[0x20]=1;state->timer=1.95f;
            state->orbitA=0;state->orbitB=0;state->rateA=0;state->rateB=0;
            if(state->variant>=0) func_PAL_L00_00305110(state->handle,state->variant);
            else func_PAL_L00_00305110(state->handle,0);
            qcopy(&position,actor+0x10);position.f[2]+=0.2f;
            func_PAL_L00_002B9CD8(&position,actor+0xF0,0x6F,1);
            func_L02_00410D00(object);
            func_002A7750(object,1,-1);
        }
        func_L00_002E6EF8((DrawCallback)func_L02_00411530,object);
        break;
    }
    }
propagate: {
    u8 **child=state->children;
    int count=2;
    do {
        if(*child) {
            int flags=*(u16 *)(*child+0x34);
            int inherited=*(u16 *)(object+0x34)&0x80;
            flags &= 0xFF7F;
            *(u16 *)(*child+0x34)=flags+inherited;
        }
        child++;
    } while(--count>=0);
}
}
