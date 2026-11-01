#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define INT(p,o) (*(int *)((char *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define HALF(p,o) (*(short *)((char *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((char *)(p)+(o)))
typedef struct { u8 pad0[0xAA]; s16 oclass; u8 padAC[0xF8 - 0xAC]; float rotz; u8 padFC[0x100 - 0xFC]; } Moby;
extern int D_L04_001C9C00[];
extern int D_001A79F0 __attribute__((sda));
extern char *D_L04_001B24DC[] __attribute__((sda));
extern float D_L04_001B1874 __attribute__((sda)), D_L04_001B1878 __attribute__((sda));
extern void func_L04_0044D0C0(char *);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern void func_002A7398(char *,int,int);
extern int func_00282948(int *);
extern int func_00282978(short *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_002A7878(float,float);
extern int func_00283CF0(float);
extern unsigned int func_002B1C20(void *,void *);
extern void func_US2_002A7AA8(void *,int,int);
extern void func_L01_003E9CF8(void *,int,int);
extern float func_002AA2E8(float *,float,float);
extern float func_002AE8C0(void *,void *,float,float);
extern float func_00283248(float,float);
extern float func_00283B98(float,float);
extern float func_002A7CA0(void *,float,float *,float,float,float);
extern float func_00282E80(void *,void *);
extern int func_US2_002AF9C8(char *,float);
extern int func_002E5CF8(int,int,char *);
extern int func_002A8D70(float,float,float,void *,int,int,int,int,int);
extern float func_00283180(float), func_00283198(float);
extern void func_00282CD8(void *,void *,void *);
extern int func_L04_0044D860(char *);
extern void func_L04_0044D428(char *);
extern void func_L04_0044D6A0(u8 *);
extern void func_0029F338(void *);

void func_US2_L04_0044DD48(u8 *object)
{
    char *vars;
    u8 *other;
    union { Quad q; float f[4]; } movement, position;
    unsigned int flags;
    int kind, choice, state;
    float delay;
    if (D_L04_001C9C00[0]) return;
    vars=*(char **)(object+0x68);
    func_L04_0044D0C0(object);
    kind=(u8)object[0x95];
    switch(kind) {
    case 0:
        if(INT(vars,0x328)==-1 || INT(vars,0x32c)==-1 || (other=(u8 *)D_L04_001B24DC[0]+INT(vars,0x32c)*256)==object ||
            !other || other[0x20]==254 || other[0x20]==253) {
            func_00282948((int *)(vars+0x31c));
            if(INT(vars,0x254)==1) {
                if(INT(vars,0x328)!=-1) {
                    Moby *pool=(Moby *)D_L04_001B24DC[0];
                    UHALF(object,0x34)&=0xffbe;
                    INT(object,0x98)=INT(*(char **)(object+0x24),0x10);
                    if(pool[INT(vars,0x328)].oclass==0x929) {
                        func_002A7750(object,7,3); func_002A7398(object,7,0);
                        FLOAT(object,0xf8)=FLOAT(D_L04_001B24DC[0]+INT(vars,0x328)*256,0xf8);
                        INT(vars,0x328)=-1;
                        goto heightCheck;
                    }
                    INT(vars,0x328)=-1;
                    func_002A7750(object,4,2);
                    if(object[0x43]!=7) func_002A7470(object,7,0,14);
                } else {
                    if(func_002A77E0(9)==0) {
                        if(func_002A77E0(2)!=0) {
                            func_002A7750(object,3,2);
                            if(object[0x43]!=3) func_002A7470(object,3,0,14);
                            if(func_002A77E0(2)==1 && object[0x43]!=4) func_002A7470(object,4,0,14);
                        } else {
                            func_002A7750(object,4,2);
                            if(object[0x43]!=7) func_002A7470(object,7,0,14);
                        }
                    }
                }
                UHALF(object,0x34)&=0xffbe;
                INT(object,0x98)=INT(*(char **)(object+0x24),0x10);
            } else if(HALF(vars,0x306)!=0) {
                func_002A7750(object,2,1);
                HALF(vars,0x306)=0;
                INT(vars,0x2fc)=func_00283CF0(func_002A7878(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=0;
            }
        }

        break;
    case 1:
        if(INT(vars,0x254)==1) {
            func_002A7750(object,4,2);
            if(object[0x43]!=7) func_002A7470(object,7,0,14);
        } else if(INT(vars,0x2fc)==0) {
            func_002A7750(object,1,0);
            if(object[0x43]!=2) func_002A7470(object,2,0,12);
        }

        break;
    case 2:
        if(INT(vars,0x254)!=1 && func_002A77E0(19)==0) {
            func_002A7750(object,2,1);
            INT(vars,0x2fc)=func_00283CF0(func_002A7878(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
            HALF(vars,0x300)=0;
        }

        break;
    case 3:
        if(object[0x20]!=7) {
        flags=func_002B1C20(object,vars+0x60);
        if(flags&1) { HALF(vars,0x98)=0; func_US2_002A7AA8(object,0,3); func_L01_003E9CF8(object,0,0); return; }
        if(flags&2) {
            if(INT(vars,0x254)==1) {
                func_002A7750(object,4,2);
                if(object[0x43]!=7) func_002A7470(object,7,0,14);
            } else {
                func_002A7750(object,2,1);
                INT(vars,0x2fc)=func_00283CF0(func_002A7878(FLOAT(vars,0x2f8)*0.8f,FLOAT(vars,0x2f8)*1.2f)*60.0f);
                HALF(vars,0x300)=func_002A7820(120,700);
            }
        }

        }
        break;
    }
heightCheck:
    if(FLOAT(object,0x18)-FLOAT(vars,0x2e8)>10.0f || FLOAT(object,0x18)<10.0f) {
        HALF(vars,0x98)=0; qzero(object+0xf0);
        func_US2_002A7AA8(object,0,3); func_0029F338(object); return;
    }
    if(FLOAT(object,0x18)<75.0f && D_001A79F0==11) {
        HALF(vars,0x98)=0; qzero(object+0xf0);
        func_US2_002A7AA8(object,0,3); func_0029F338(object); return;
    }
    state=(u8)object[0x20];
    switch(state) {
    case 1:
        func_00282978((short *)(vars+0x300));
        if(object[0x43]==0 && HALF(vars,0x300)) func_002A7470(object,7,0,14);
        if (HALF(vars,0x300)>=21)
            func_002AA2E8((float *)(vars+0x124),D_L04_001B1878*0.01666666753590107f,0.0019444444915279746f);
        else
            func_002AA2E8((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(object[0x43]==7) {
            FLOAT(object,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(object[0x43]!=func_002A77E0(3)) {
                    choice=func_002A77E0(3)+(0);
                    func_002A7470(object,choice,0,12);
                }
            }
            func_002AE8C0(object,vars+0x110,0.35f,0.25f);
        } else if(((u8)object[0x43]<=2) && (object[0x60]&2)) {
            HALF(vars,0x300)=func_002A7820(120,500);
            if(object[0x43]!=7) func_002A7470(object,7,0,12);
        }
        break;
    case 2:
        func_00282978((short *)(vars+0x300));
        if(object[0x43]==0 && HALF(vars,0x300)) func_002A7470(object,7,0,14);
        if (HALF(vars,0x300)>=21)
            func_002AA2E8((float *)(vars+0x124),D_L04_001B1878*0.01666666753590107f,0.0019444444915279746f);
        else
            func_002AA2E8((float *)(vars+0x124),0.0f,0.0019444444915279746f);
        if(object[0x43]==7) {
            FLOAT(object,0x48)=0.8f;
            if(HALF(vars,0x300)==0) {
                if(object[0x43]!=func_002A77E0(2)+5) {
                    choice=func_002A77E0(2)+(5);
                    func_002A7470(object,choice,0,12);
                }
            }
            func_002AE8C0(object,vars+0x110,0.35f,0.25f);
        } else if(((u8)(object[0x43]-5)<2) && (object[0x60]&2)) {
            HALF(vars,0x300)=func_002A7820(120,500);
            if(object[0x43]!=7) func_002A7470(object,7,0,12);
        }
        FLOAT(object,0x48)=1.0f;
        break;
    case 4:
        FLOAT(object,0x48)=1.0f;
        if(func_00282E80(object+0x10,vars+0x240)<=D_L04_001B1874) {
            func_002A7750(object,5,2);
            if(object[0x43]!=8) func_002A7470(object,8,2,6);
            FLOAT(vars,0x314)=0.0f;
        } else if(func_00282948((int *)(vars+0x318))) {
            delay=func_002A7878(0.2617994248867035f,0.523598849773407f);
            if(func_002A77E0(2)==0) delay=-delay;
            FLOAT(vars,0x314)=delay;
            INT(vars,0x318)=func_002A7820(45,60);
        }
        break;
    case 5:
        if(object[0x42]!=8) break;
        if(func_US2_002AF9C8(object,8.0f)) func_002E5CF8(3,0,object);
        if(object[0x42]!=8) break;
        if(func_US2_002AF9C8(object,10.0f)) {
            func_002A8D70(0.75f,FLOAT(vars,0x330),1.0f,object,0,0x4000001,0,1,0);
            break;
        }
        if(object[0x42]!=8) break;
        if((object[0x60]&2) && func_00282E80(object+0x10,vars+0x240)>D_L04_001B1874) {
            func_002A7750(object,4,2);
            if(object[0x43]!=7) func_002A7470(object,7,0,6);
        }
        break;
    case 7:
        movement.f[0]=func_00283180(FLOAT(object,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[1]=func_00283198(FLOAT(object,0xf8))*0.01666666753590107f*(FLOAT(vars,0x30c)+FLOAT(vars,0x30c));
        movement.f[2]=0.0f;
        func_00282CD8(&position,object+0x10,&movement);
        if(func_00282E80(object+0x10,vars+0x2e0)>6.0f) func_002A7750(object,4,2);
        break;
    case 3:
        delay=func_00283248(FLOAT(vars,0x240)-FLOAT(object,0x10),FLOAT(vars,0x244)-FLOAT(object,0x14));
        delay=func_00283B98(delay,FLOAT(vars,0x314));
        func_002A7CA0(object,delay,(float *)(vars+0x310),0.05f,0.3f,0.10471977293491364f);
        if(object[0x60]&2) {
            func_002A7750(object,4,-1);
            if(object[0x43]!=7) func_002A7470(object,7,0,15);
        }
        break;
    case 8:
        if(func_L04_0044D860(object)) {
            func_US2_002A7AA8(object,0,3); func_0029F338(object); return;
        }
        break;
    }
    if((unsigned)((u8)object[0x20]-7)>1) func_L04_0044D428(object);
    func_L04_0044D6A0((u8 *)object);
    return;
}
