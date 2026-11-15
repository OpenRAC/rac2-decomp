#include "common.h"
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
extern char D_00189F00[], D_L06_001BFA40[], D_L06_001B0B80[];
typedef struct { char pad0[0x80]; float position[4]; char pad90[0x50]; float vector_e0[4]; } PlayerView;
extern PlayerView g_hero_state;
#define PLAYER_POSITION ((char *)&D_00189E20.position)
extern unsigned char D_001A7BCF, D_001A7C8F, D_001A7A40;
extern unsigned char D_001395CD NOT_SDA;
extern int D_001397B0 NOT_SDA, D_00138324 NOT_SDA, D_L06_001A8F00;
extern int g_player_bolts MACRO_ADDR;
/* Only +4 is accessed; the object's real base is not known. */
extern struct { int pad; int flag; } D_L06_001B2564 MACRO_ADDR;
extern struct { int normal, challenge; } D_L06_002958D0 NOT_SDA;
extern char *D_L06_001B281C;
extern int func_360F58(char *,int);
extern void func_35C8F8(char *), func_36F678(char *), func_3335E0(char *,int), func_333728(char *);
extern void func_35A550(char *,int,int), func_34BC10(int), func_36F4F8(int,int,int);
extern int func_3B1C70(void), func_36F588(char *,int,float);
extern void func_2F94E0(void *,void *,int,int), func_35B810(int,int), func_2E3EF0(char *);
extern void func_3623D0(int), func_364178(int), func_34B958(int,int), func_350388(char *);
extern int func_32D268(char *),func_32D238(char *),func_35A660(int,int),func_32E728(float);
extern float func_35A6B8(float,float),func_32D7C0(char *,char *),func_32DC80(float,float),func_32E6B8(float,float),func_32D710(char *),func_32E5D0(float,float),func_32E618(float,float),func_32D740(char *);
extern void func_35A270(char *,int,int,int),func_364090(char *,float,float,float),func_32D5C8(char *,char *,char *),func_32D5F8(char *,char *,char *),func_363CD8(char *,char *,int,float,float);
static __inline__ void joint_step(char *obj,char *joint,int index,float speed,float limit)
{
    func_363CD8(obj,joint,index,speed,limit);
}

/* Updates a coin-gated door: waits for the hero, asks for payment, takes the coins and opens. */
void coin_gated_door_update(char *moby)
{
    float target[4], origin[4], delta[4];
    char *vars=*(char **)(moby+0x68);
    float speed, yaw, pitch, angle;
    int active;
    switch(B(moby,0x20)) {
    case 0:
        if(D_001A7BCF) goto destroy;
        func_35C8F8(moby);
        if(I(vars,0x124)) func_35A550(moby,6,-1);
        else if(D_001397B0&0x400) func_35A550(moby,2,-1);
        else func_35A550(moby,1,-1);
        break;
    case 1:
        if(func_360F58(PLAYER_POSITION,I(vars,0x128))) {
            func_36F678(moby);
            func_3335E0(D_L06_001BFA40,0x4a);
            func_333728(D_L06_001BFA40);
            func_35A550(moby,2,-1);
        }
        break;
    case 2: {
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(moby,0x31)=0;H(moby,0x34)|=1;}
        if(func_3B1C70()) break;
        D_L06_001B2564.flag=0;
        H(moby,0x34)&=0xfffe; B(moby,0x31)=1;
        target[0]=456.0800f;target[1]=251.2400f;target[2]=68.9200f;
        origin[2]=-2.094395399093628f;
        func_2F94E0(target,origin,0,1);
        {
            int challenge = D_001A7C8F;
            int coins = g_player_bolts;
            if(challenge) {
                if(coins>=D_L06_002958D0.challenge) {func_35A550(moby,4,-1);break;}
            } else if(coins>=D_L06_002958D0.normal) goto state4;
            func_35A550(moby,3,-1);
            break;
        state4:
            func_35A550(moby,4,-1);break;
        }
    }
    case 3: {
        int challenge = D_001A7C8F;
        int coins = g_player_bolts;
        if(challenge ? D_L06_002958D0.challenge<coins : D_L06_002958D0.normal<coins) {
            func_35A550(moby,4,-1); break;
        }
        if(func_36F588(moby,10,2.5f)) {
            func_34BC10(180);
            func_36F4F8(0x27ce,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            func_36F678(moby);
        }
        break;
    }
    case 4: {
        int challenge = D_001A7C8F;
        int coins = g_player_bolts;
        if(challenge ? coins<D_L06_002958D0.challenge : coins<D_L06_002958D0.normal) {
            func_34BC10(180);func_35A550(moby,3,-1);break;
        }
        if(func_36F588(moby,10,2.5f)) {
            func_34BC10(180);
            func_36F4F8(0x27cf,D_001A7C8F ? D_L06_002958D0.challenge : D_L06_002958D0.normal,-1);
            func_36F678(moby);
            if(D_00138324&0x10) {
                func_3335E0(D_L06_001BFA40,0x4b);func_3335E0(D_L06_001BFA40,7);func_3335E0(D_L06_001BFA40,0x4c);func_333728(D_L06_001BFA40);func_35A550(moby,5,-1);
            }
        }
        break;
    }
    case 5:
        D_L06_001B2564.flag=1;
        if(D_L06_001A8F00==2) {B(moby,0x31)=0;H(moby,0x34)|=1;}
        if(func_3B1C70()) break;
        D_L06_001B2564.flag=0;B(moby,0x31)=1;H(moby,0x34)&=0xfffe;
        if(B(moby,0x21)!=255) func_35B810(B(moby,0x21),1);
        func_2E3EF0(D_L06_001B0B80);
        D_001395CD=1;
        if(!D_001A7BCF) {
            func_3623D0(7);func_364178(7);
            {
                int challenge = D_001A7C8F;
                int coins = g_player_bolts;
                int left;
                if(challenge) left=coins-D_L06_002958D0.challenge;
                else left=coins-D_L06_002958D0.normal;
                g_player_bolts=left;
            }
            func_34BC10(180);
        }
        if(I(vars,0x120)!=-1) B(D_L06_001B281C,(I(vars,0x120)<<8)+0xbc)=1;
        func_34B958(0,-1);
        goto destroy;
    case 6:
        if(D_L06_001A8F00==2) {B(moby,0x31)=0;H(moby,0x34)|=1;}
        else {B(moby,0x31)=1;H(moby,0x34)&=0xfffe;}
        if(D_001A7BCF) {destroy:func_350388(moby);return;}
        break;
    }
    if(B(moby,0x20)) {
        if(B(moby,0x43)==2 && func_32D268(vars+0x11e)) {
            H(vars,0x11e)=func_32E728(func_35A6B8(1200,2400));
            if(B(moby,0x43)!=3) func_35A270(moby,3,0,func_35A660(10,20));
        } else if(B(moby,0x60)&2) {
            if(B(moby,0x43)!=2) func_35A270(moby,2,0,func_35A660(10,20));
            F(moby,0x48)=func_35A6B8(0.9f,1.1f);
        }
    }
    speed=0.02f;
    active=0;
    if(B(moby,0x43)==2) {
        active=1;
        if(func_32D7C0(moby+0x10,PLAYER_POSITION)<8.0f && func_32E6B8(F(moby,0xf8),func_32DC80(g_hero_state.vector_e0[0]-F(moby,0x10),g_hero_state.vector_e0[1]-F(moby,0x14)))<1.5707964897155762f) {
            if(func_32D710(PLAYER_POSITION+0x90)>0.01f) I(vars,0x114)=120;
            else func_32D238(vars+0x114);
        } else if(I(vars,0x114)) {I(vars,0x114)=0;qcopy(vars+0x100,D_00189F00);}
        if(func_32D238(vars+0x118)) {
            I(vars,0x118)=func_32E728(func_35A6B8(180,300));
            angle=func_32E5D0(F(moby,0xf8),func_35A6B8(-90,90)*0.01745329424738884f);
            func_364090(vars+0x100,6,angle,func_35A6B8(0,30)*0.01745329424738884f);
            func_32D5C8(vars+0x100,vars+0x100,moby+0x10);
        }
        if(I(vars,0x114)) {qcopy(target,D_00189F00);speed=0.04f;}
        else qcopy(target,vars+0x100);
    }
    if(active) {
        qcopy(origin,moby+0x10);origin[2]+=2;
        func_32D5F8((char *)delta,(char *)target,(char *)origin);
        yaw=func_32E618(func_32DC80(delta[0],delta[1]),F(moby,0xf8));
        pitch=-func_32DC80(func_32D740((char *)delta),delta[2]);
        if(yaw>1.5707964897155762f) yaw=1.5707964897155762f;
        else if(yaw< -1.5707964897155762f) yaw= -1.5707964897155762f;
        if(pitch>0.523598849773407f) pitch=0.523598849773407f;
        else if(pitch< -0.523598849773407f) pitch= -0.523598849773407f;
        F(vars,0x64)=pitch;F(vars,0x68)=yaw*0.6f;F(vars,0xe8)=yaw*0.4f;
    }
    if(D_001A7A40) F(vars,0x70)=2.75f;
    joint_step(moby,vars,0,speed,0.3f);joint_step(moby,vars+0x80,1,speed,0.3f);
}
