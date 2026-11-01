#include "include_asm.h"

#include "common.h"
extern int D_0018C0B4 NOT_SDA;
extern int D_L19_001B1D20 __attribute__((sda));
extern int D_L19_001B1D24 __attribute__((sda));
extern char *D_L19_001B2A1C __attribute__((sda));
extern void *D_L19_001FB5A0[];
extern int func_002ACD38(void *);
extern int func_L19_0041BFD0(void *);
extern void func_0029F338(void *);
extern int func_002A8508(int,int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern int func_00282948(void *);
extern int func_002A7820(int,int);
extern int func_002B3890(void *);
extern int func_002B3868(void *);
extern int func_002B1C20(void *,void *);
extern void func_US2_002A7AA8(void *,int,int);
extern void func_L01_003E9CF8(void *,int,void *);
extern int func_002A77E0(int);
extern float func_002A7878(float,float);
extern float func_002A7940(void);
extern void func_002AF000(void *,float,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002B60B0(void *,float,float,float,float);
extern int func_L01_00321178(void *,void *);
extern float func_00282E80(void *,void *);
extern float func_00283248(float,float);
extern int func_L01_00322288(void *,float);
extern int func_US2_002AF9C8(void *,float);
extern float func_00283C80(float,float);
extern void func_002B4FF0(void *,void *,float);
extern float func_0029F530(void *);
extern int func_002A8D70(float,float,float,void *,int,int,int,int,int);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern int func_L02_00331440(void *,void *,int,float,float,float);
extern void func_L19_0041C2B8(void *);
#define I(p,n) (*(int *)((p)+(n)))
#define F(p,n) (*(float *)((p)+(n)))
#define B(p,n) (*(u8 *)((p)+(n)))
typedef struct { char pad[0x34]; u16 flags; } GrelbinObjectFlags;
#define H(p) (((GrelbinObjectFlags *)(p))->flags)
#define ANIM(n,a,t) if(B(obj,0x43)!=(n)) func_002A7470(obj,n,a,t)
#define SOLID() H(obj)=(H(obj)&0xFFBE)|0x1000; I(obj,0x98)=I(*(char **)(obj+0x24),0x10)
#define HIDE() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); H(obj)|=0x1000; }
#define PICK_FLEE_TARGET() { \
    qcopy(data+0x290,data+0x210); \
    distance=func_002A7878(6.0f,8.0f); \
    angle=func_002A7940(); \
    func_002AF000(vec,distance,angle,0.0f); \
    func_00282CC0(data+0x290,data+0x290,vec); \
    { int timer=func_002A7820(580,600); int active=D_L19_001B1D20; \
      I(data,0x230)=timer; D_L19_001B1D20=active-1; } }
#define DISABLE_COLLISION() { B(obj,0x31)=1; H(obj)&=0xFFFE; I(obj,0x98)=I(*(char **)(obj+0x24),0x10); SOLID(); }

void func_US2_L19_0041C3A8(char *obj)
{
    char *data;
    char *entity;
    float vec[4] __attribute__((aligned(16)));
    float distance, angle;
    int mode, result;
    if (!func_002ACD38(obj+0x10) || D_0018C0B4==111) return;
    data=*(char **)(obj+0x68);
    if (func_L19_0041BFD0(obj)) { func_0029F338(obj); return; }
    if(B(obj,0x20)==1) H(obj)&=0xEFFF;
    mode=B(obj,0x95);
    switch(mode) {
    case 0:
        if(I(data,0x278)==1 && I(data,0x26C)==0 && D_L19_001B1D20<D_L19_001B1D24) {
            if(I(data,0x264)==-1) {
                if(I(data,0x250)==255 || !D_L19_001FB5A0[I(data,0x250)]) {
                    HIDE(); func_002A7750(obj,10,2); ANIM(0,0,10); D_L19_001B1D20++;
                } else if(!func_002A8508(I(data,0x250),-1)) {
                    HIDE(); func_002A7750(obj,10,2); ANIM(0,0,10); D_L19_001B1D20++;
                }
            } else {
                entity=D_L19_001B2A1C+(I(data,0x264)<<8);
                if(!entity || B(entity,0x20)==254 || B(entity,0x20)==253) {
                    HIDE(); func_002A7750(obj,10,2); ANIM(0,0,10); D_L19_001B1D20++;
                }
            }
        } else if(I(data,0x240) && func_00282948(data+0x238)) {
            I(data,0x240)=0;
            if(I(data,0x230)<300) I(data,0x230)=func_002A7820(480,600);
        }
        break;
    case 1:
        if ((I(data,0x278)==1 || I(data,0x27C)==1) && D_L19_001B1D20<D_L19_001B1D24) {
            ANIM(3,0,10); func_002A7750(obj,14,2); D_L19_001B1D20++;
        }
        break;
    case 2:
        if(func_002B3890(obj)) {
            DISABLE_COLLISION();
        }
        if(I(data,0x278)!=1 && I(data,0x27C)!=1 && B(obj,0x20)!=15 && B(obj,0x20)!=16) {
            func_002A7750(obj,7,1); ANIM(7,0,10);
            if(!func_002A77E0(3)) { ANIM(6,0,10); }
            else if(func_002A77E0(2)) {
                ANIM(13,0,10);
            }
            PICK_FLEE_TARGET();
        } else { DISABLE_COLLISION(); }
        break;
    case 3:
        result=func_002B1C20(obj,data+0x140);
        if(result&1) {
            func_US2_002A7AA8(obj,0,3); func_L01_003E9CF8(obj,0,0); D_L19_001B1D20--;
        } else if(result&2) {
            if(I(data,0x204)==1 && D_L19_001B1D20<=D_L19_001B1D24) {
                ANIM(3,0,10); func_002A7750(obj,14,2);
            } else {
                func_002A7750(obj,8,1);
                ANIM(2,0,10);
                PICK_FLEE_TARGET();
            }
        }
        break;
    }
    switch(B(obj,0x20)) {
    case 1:
    case 2:
        break;
    case 7:
        if(B(obj,0x60)&2) {func_002A7750(obj,8,-1); ANIM(2,0,13);}
        break;
    case 8:
        if(func_002B3868(obj)) func_002B60B0(obj,0.0016666667f,0.050000004f,0.0069813179f,0.8377582f);
        func_L01_00321178(obj,data+0x290);
        if(func_00282E80(obj+0x10,data+0x290)<0.5f) {func_002A7750(obj,3,-1); ANIM(1,0,10);}
        break;
    case 3:
        if(B(obj,0x60)&2) {
            ANIM(12,0,10);func_002A7750(obj,1,0);
            B(obj,0x31)=0; I(obj,0x98)=0;H(obj)=(H(obj)|1)&0xEFFF;
        }
        break;
    case 10:
        entity=*(char **)(data+0x200);
        func_L01_00322288(obj,func_00283248(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(func_US2_002AF9C8(obj,23.0f)) {
            ANIM(7,1,2);
            if(func_002A77E0(2)) {ANIM(6,0,2);}
            func_002A7750(obj,11,-1);
            if(I(data,0x274) || !func_002A77E0(2)) { ANIM(3,0,6);func_002A7750(obj,14,-1); }
        }
        break;
    case 11:
        entity=*(char **)(data+0x200);
        func_L01_00322288(obj,func_00283248(F(entity,0x10)-F(obj,0x10),F(entity,0x14)-F(obj,0x14)));
        if(B(obj,0x60)&2) { ANIM(3,0,10);func_002A7750(obj,14,-1); }
        break;
    case 14:
        if(func_002B3868(obj)) {
            func_002B60B0(obj,0.0033333334f,0.10000001f,0.0069813179f,0.8377582f); SOLID();
        }
        if(func_00282E80(obj+0x10,*(char **)(data+0x200)+0x10)<7.0f && func_00282E80(obj+0x10,*(char **)(data+0x200)+0x10)>4.0f &&
            func_00283C80(F(obj,0xF8),func_00283248(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            func_002B60B0(obj,0.02f,0.6f,0.0069813179f,0.8377582f);ANIM(4,0,10);func_002A7750(obj,15,-1);
        } else if(func_00282E80(obj+0x10,*(char **)(data+0x200)+0x10)<=3.0f &&
            func_00283C80(F(obj,0xF8),func_00283248(F(data,0x1F0)-F(obj,0x10),F(data,0x1F4)-F(obj,0x14)))<0.52359885f) {
            ANIM(10,0,10);func_002A7750(obj,16,-1);
        } else func_002B4FF0(obj,data+0x1F0,F(data,0x270));
        break;
    case 15: {
        float attackDistance;
        if(func_002B3868(obj)) { SOLID(); }
        attackDistance=func_0029F530(obj);
        if(attackDistance>4.0f && attackDistance<15.0f) func_L01_00321178(obj,data+0x1F0);
        if(func_US2_002AF9C8(obj,30.0f)) {
            ANIM(7,0,10);func_002A7750(obj,24,-1);
            if(func_002A77E0(3)) {ANIM(6,0,10);} else if(func_002A77E0(2)) {ANIM(13,41,10);}
            if(func_002A77E0(5)) { ANIM(5,0,10);func_002A7750(obj,17,-1); }
        }
        if(attackDistance<19.0f) {
            func_002A8D70(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    }
    case 16:
        if(func_002B3868(obj)) {SOLID();}
        if(func_US2_002AF9C8(obj,25.0f)) {
            ANIM(7,0,10);func_002A7750(obj,24,-1);
            if(func_002A77E0(3)) {ANIM(6,0,10);} else if(func_002A77E0(2)) {ANIM(13,41,10);}
            if(func_002A77E0(3)) {ANIM(5,0,10);func_002A7750(obj,17,-1);}
        }
        if(func_0029F530(obj)<14.0f) {
            func_002A8D70(0.75f,(float)B(data,0x34),1.0f,obj,0,1,0,1,0);
        }
        break;
    case 17: {
        char *target;
        if(func_002B3868(obj)) {
            vec[0]=func_00283180(func_00283B98(F(obj,0xF8),3.141593f))*18.0f;
            vec[1]=func_00283198(func_00283B98(F(obj,0xF8),3.141593f))*18.0f;
            vec[2]=0.0f;
            func_00282CC0(data+0x280,vec,obj+0x10);
            func_002B60B0(obj,0.023333333f,0.8000001f,0.0069813179f,0.8377582f);
        }
        { float range=func_0029F530(obj);
        if(range>4.0f && range<14.0f) {
            target=data+0x280;
            { float dx=F(data,0x280)-F(obj,0x10); float dy=F(data,0x284)-F(obj,0x14);
            angle=func_00283248(dx,dy); }
            func_L02_00331440(obj,target,16,angle,-1.0f,-1.0f);
        }}
        if(func_US2_002AF9C8(obj,21.0f)) {
            ANIM(7,0,10);func_002A7750(obj,24,-1);
            if(func_002A77E0(3)) {ANIM(6,0,10);} else if(func_002A77E0(2)) {ANIM(13,41,10);}
        }
        break;
    }
    case 24:
        if(B(obj,0x60)&2) {ANIM(3,0,10);func_002A7750(obj,14,-1);}
        break;
    }
    func_L19_0041C2B8(obj);
}
