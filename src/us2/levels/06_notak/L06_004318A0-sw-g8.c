#include "include_asm.h"

#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char D_00189F00[], D_L06_001BFA40[], D_L06_001B0B80[];
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x50]; float vector_e0[4]; } PlayerView;
extern PlayerView D_00189E20;
#define PLAYER_POSITION ((char *)&D_00189E20.position)
extern unsigned char D_001A7BCF, D_001A7C8F, D_001A7A40;
extern unsigned char D_001395CD NOT_SDA;
extern int D_001397B0 NOT_SDA, D_00138324 NOT_SDA, D_L06_001A8F00;
extern int D_001A79F8 MACRO_ADDR;
extern struct { int pad; int flag; } D_L06_001B2564 MACRO_ADDR;
extern struct { int normal, challenge; } D_L06_002958D0 NOT_SDA;
extern char *D_L06_001B281C;
extern int func_002ACBC8(char *,int);
extern void func_L01_003128C0(char *), func_L01_003246D0(char *), func_00288AA0(char *,int), func_00288BE8(char *);
extern void func_002A7750(char *,int,int), func_L00_0030C710(int), func_L01_00324550(int,int,int);
extern int func_002F5D10(void), func_L01_003245E0(char *,int,float);
extern void func_L00_002B9D60(void *,void *,int,int), func_002A8598(int,int), func_0026FEB8(char *);
extern void func_002AD7B8(int), func_US2_002AFF10(int), func_0029B3E0(int,int), func_0029F338(char *);
extern int func_00282978(char *),func_00282948(char *),func_002A7820(int,int),func_00283CF0(float);
extern float func_002A7878(float,float),func_00282E80(char *,char *),func_00283248(float,float),func_00283C80(float,float),func_00282DF0(char *),func_00283B98(float,float),func_00283BE0(float,float),func_00282E20(char *);
extern void func_002A7470(char *,int,int,int),func_002AF000(char *,float,float,float),func_00282CC0(char *,char *,char *),func_00282CF0(char *,char *,char *),func_002AEC48(char *,char *,int,float,float);
static __inline__ void joint_step(char *obj,char *joint,int index,float speed,float limit)
{
    func_002AEC48(obj,joint,index,speed,limit);
}

void func_US2_L06_004318A0(char *obj)
{
    float target[4], origin[4], delta[4];
    char *s=*(char **)(obj+0x68);
    float speed, yaw, pitch, angle;
    int active;
    switch(B(obj,0x20)) {
    case 0:
        if(D_001A7BCF) goto destroy;
        func_L01_003128C0(obj);
        if(I(s,0x124)) func_002A7750(obj,6,-1);
        else if(D_001397B0&0x400) func_002A7750(obj,2,-1);
        else func_002A7750(obj,1,-1);
        break;
    case 1:
        if(func_002ACBC8(PLAYER_POSITION,I(s,0x128))) {
            func_L01_003246D0(obj);
            func_00288AA0(D_L06_001BFA40,0x4a);
            func_00288BE8(D_L06_001BFA40);
            func_002A7750(obj,2,-1);
        }
        break;
    case 2: {
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(func_002F5D10()) break;
        D_L06_001B2564.flag=0;
        H(obj,0x34)&=0xfffe; B(obj,0x31)=1;
        target[0]=456.0800f;target[1]=251.2400f;target[2]=68.9200f;
        origin[2]=-2.094395399093628f;
        func_L00_002B9D60(target,origin,0,1);
        {
            int challenge = D_001A7C8F;
            int coins = D_001A79F8;
            if(challenge) {
                if(coins>=D_L06_002958D0.challenge) {func_002A7750(obj,4,-1);break;}
            } else if(coins>=D_L06_002958D0.normal) goto state4;
            func_002A7750(obj,3,-1);
            break;
        state4:
            func_002A7750(obj,4,-1);break;
        }
    }
    case 3: {
        int challenge = D_001A7C8F;
        int coins = D_001A79F8;
        if(challenge ? D_L06_002958D0.challenge<coins : D_L06_002958D0.normal<coins) {
            func_002A7750(obj,4,-1); break;
        }
        if(func_L01_003245E0(obj,10,2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x1320,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            func_L01_003246D0(obj);
        }
        break;
    }
    case 4: {
        int challenge = D_001A7C8F;
        int coins = D_001A79F8;
        if(challenge ? coins<D_L06_002958D0.challenge : coins<D_L06_002958D0.normal) {
            func_L00_0030C710(180);func_002A7750(obj,3,-1);break;
        }
        if(func_L01_003245E0(obj,10,2.5f)) {
            func_L00_0030C710(180);
            func_L01_00324550(0x1321,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            func_L01_003246D0(obj);
            if(D_00138324&0x10) {
                func_00288AA0(D_L06_001BFA40,0x4b);func_00288AA0(D_L06_001BFA40,7);func_00288AA0(D_L06_001BFA40,0x4c);func_00288BE8(D_L06_001BFA40);func_002A7750(obj,5,-1);
            }
        }
        break;
    }
    case 5:
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        if(func_002F5D10()) break;
        D_L06_001B2564.flag=0;B(obj,0x31)=1;H(obj,0x34)&=0xfffe;
        if(B(obj,0x21)!=255) func_002A8598(B(obj,0x21),1);
        func_0026FEB8(D_L06_001B0B80);
        D_001395CD=1;
        if(!D_001A7BCF) {
            func_002AD7B8(7);func_US2_002AFF10(7);
            {
                int challenge = D_001A7C8F;
                int coins = D_001A79F8;
                int left;
                if(challenge) left=coins-D_L06_002958D0.challenge;
                else left=coins-D_L06_002958D0.normal;
                D_001A79F8=left;
            }
            func_L00_0030C710(180);
        }
        if(I(s,0x120)!=-1) B(D_L06_001B281C,(I(s,0x120)<<8)+0xbc)=1;
        func_0029B3E0(0,-1);
        goto destroy;
    case 6:
        if(D_L06_001A8F00==2) {B(obj,0x31)=0;H(obj,0x34)|=1;}
        else {B(obj,0x31)=1;H(obj,0x34)&=0xfffe;}
        if(D_001A7BCF) {destroy:func_0029F338(obj);return;}
        break;
    }
    if(B(obj,0x20)) {
        if(B(obj,0x43)==2 && func_00282978(s+0x11e)) {
            H(s,0x11e)=func_00283CF0(func_002A7878(1200,2400));
            if(B(obj,0x43)!=3) func_002A7470(obj,3,0,func_002A7820(10,20));
        } else if(B(obj,0x60)&2) {
            if(B(obj,0x43)!=2) func_002A7470(obj,2,0,func_002A7820(10,20));
            F(obj,0x48)=func_002A7878(0.9f,1.1f);
        }
    }
    speed=0.02f;
    active=0;
    if(B(obj,0x43)==2) {
        active=1;
        if(func_00282E80(obj+0x10,PLAYER_POSITION)<8.0f && func_00283C80(F(obj,0xf8),func_00283248(D_00189E20.vector_e0[0]-F(obj,0x10),D_00189E20.vector_e0[1]-F(obj,0x14)))<1.5707964897155762f) {
            if(func_00282DF0(PLAYER_POSITION+0x90)>0.01f) I(s,0x114)=120;
            else func_00282948(s+0x114);
        } else if(I(s,0x114)) {I(s,0x114)=0;qcopy(s+0x100,D_00189F00);}
        if(func_00282948(s+0x118)) {
            I(s,0x118)=func_00283CF0(func_002A7878(180,300));
            angle=func_00283B98(F(obj,0xf8),func_002A7878(-90,90)*0.01745329424738884f);
            func_002AF000(s+0x100,6,angle,func_002A7878(0,30)*0.01745329424738884f);
            func_00282CC0(s+0x100,s+0x100,obj+0x10);
        }
        if(I(s,0x114)) {qcopy(target,D_00189F00);speed=0.04f;}
        else qcopy(target,s+0x100);
    }
    if(active) {
        qcopy(origin,obj+0x10);origin[2]+=2;
        func_00282CF0((char *)delta,(char *)target,(char *)origin);
        yaw=func_00283BE0(func_00283248(delta[0],delta[1]),F(obj,0xf8));
        pitch=-func_00283248(func_00282E20((char *)delta),delta[2]);
        if(yaw>1.5707964897155762f) yaw=1.5707964897155762f;
        else if(yaw< -1.5707964897155762f) yaw= -1.5707964897155762f;
        if(pitch>0.523598849773407f) pitch=0.523598849773407f;
        else if(pitch< -0.523598849773407f) pitch= -0.523598849773407f;
        F(s,0x64)=pitch;F(s,0x68)=yaw*0.6f;F(s,0xe8)=yaw*0.4f;
    }
    if(D_001A7A40) F(s,0x70)=2.75f;
    joint_step(obj,s,0,speed,0.3f);joint_step(obj,s+0x80,1,speed,0.3f);
}
