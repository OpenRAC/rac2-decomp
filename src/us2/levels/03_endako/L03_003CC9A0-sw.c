#include "include_asm.h"

#include "common.h"
extern void func_002A04B8(void *, int *, int *, int *);
extern void func_002A7750(void *, int, int);
extern float func_00282E80(void *, void *);
extern void func_002B0C28(int, int, int);
extern int func_L03_0032AB20(int);
extern int func_002E5CF8(int, int, void *);
extern float func_00283B98(float, float);
extern void func_L00_002D40A0(void *, int, float);
extern void func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern int func_002B38B8(void *);
extern int func_L00_002D40F0(void);
extern void func_US2_L03_002C7288(int, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_L00_002C8BA8(int);
extern int func_002B3868(void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_002A89A8(void *, int, float);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L00_0042A500(int);
extern void func_00282F20(void *, void *, float);
extern float func_002AA548(void *, void *, float, float, float, float);
extern int func_00283D38(int, int, float);
extern void func_002A0488(void *, int, int, int);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);
extern void func_00282C88(void *);
extern float func_00283CE0(int);
extern void func_00282CC0(void *, void *, void *);
extern void *func_002C3150(void *, void *, int, float, unsigned char, unsigned char, int);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L03_003CBC40(void *);
typedef struct {
    char pad00[0x80];
    float position[4];
    char pad90[0x60];
    float velocity[4];
    char pad100[0x23C];
    char *interaction;
    int interactionActive;
    char pad344[0x1CDC];
    float scale[3];
    char pad202C[0x28B];
    unsigned char interactionLock;
    char pad22B8[0x248];
    unsigned short transform;
} PlayerState;
extern PlayerState D_00189E20;
extern unsigned char D_001395C4[];
extern int D_00138324[];
extern char *D_L03_001B2B0C MACRO_ADDR;
extern float D_L03_001B03E0 __attribute__((sda));
extern float D_L03_001B03E8 __attribute__((sda));
extern float D_L03_001B03EC;
extern int D_L03_001B03F0[2];
extern int D_L03_001B03F0_0 SDATA(D_L03_001B03F0);
extern int D_L03_001B03F8 __attribute__((sda));
extern float D_L03_001B03FC __attribute__((sda));
extern float D_L03_001B0400 __attribute__((sda));
extern float D_L03_001B0404 __attribute__((sda));
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))

void func_US2_L03_003CC9A0(char *actor)
{
    float pos[4], rot[4];
    int r,g,b;
    char *state = *(char **)(actor+0x68);
    int i, countdown, color, life, random, tint, tintB, tintG;
    float one;
    int packedGreen, packedBlue;
    unsigned int timer, oldTimer;
    unsigned char lifeByte;
    float angle, scale, alpha, speed, step, rate;
    char *p, *q, *scalePtr, *velocityPtr;
    switch (B(actor,0x20)) {
    case 0:
        func_002A04B8(actor,&r,&g,&b);
        packedGreen = (g << 8) | 0x80000000;
        packedBlue = (b << 16) | packedGreen;
        I(state,0x20) = packedBlue | r;
        if (I(state,8) && !D_001395C4[0]) {
            I(actor,0x98)=0;
            H(actor,0x34)=(H(actor,0x34)|0x41)&0xEFFF;
            func_002A7750(actor,5,-1);
            B(actor,0x30)=255;
        } else func_002A7750(actor,1,-1);
        break;
    case 1:
        if (D_00189E20.interaction==actor && D_00189E20.interactionActive
            && func_00282E80(actor+0x10,D_00189E20.position)<2.0f) {
            func_002B0C28(8,0x12FB,1);
            if (func_L03_0032AB20(8) && (D_00138324[0]&0x10)) {
                func_002E5CF8(0,0,actor);
                angle=func_00283B98(F(actor,0xF8),1.57079637f);
                func_L00_002D40A0(actor+0x10,0,angle);
                func_002A8C28(actor,actor+0x10,0x10000,0,1,0,2.5f,100.0f,1.0f);
                func_002A7750(actor,2,-1);
            }
        } else if (func_002B38B8(actor)) {
            func_002A7750(actor,5,-1);
            I(actor,0x98)=0;
            H(actor,0x34)=(H(actor,0x34)|0x41)&0xEFFF;
        }
        break;
    case 2:
        D_00189E20.interactionLock=1;
        if (func_L00_002D40F0()==2) {
            func_002A7750(actor,3,-1);
            func_US2_L03_002C7288(0x6F,1);
        } else {
            timer = H(actor,0x96);
            oldTimer = timer++;
            H(actor,0x96) = timer;
            if (oldTimer < 0xB5) break;
            func_00282CF0(pos,D_00189E20.position,actor+0x10);
            if (func_00282DB0(pos,D_00189E20.velocity)<0.0f) qzero(D_00189E20.velocity);
            if (H(actor,0x96)>=0x169) {
                func_002A7750(actor,1,-1);
                func_L00_002C8BA8(0);
            }
        }
        break;
    case 3:
        if (func_002B3868(actor)) { I(state,0x1C)=0; B(actor,0x30)=255; }
        H(actor,0x96)++;
        D_00189E20.interactionLock=1;
        func_002AA2E8(state+0x1C,1.57079649f,0.104719773f);
        D_00189E20.transform=1;
        D_00189E20.scale[0]=D_00189E20.scale[1]=1.0f-func_00283198(F(state,0x1C));
        D_00189E20.scale[2]=2.0f-func_00283180(F(state,0x1C));
        if (H(actor,0x96)==0x30) {
            qcopy(pos,D_L03_001B2B0C+I(state,0)*128+0x30);
            pos[2]=func_002A89A8(pos,0,0.5f);
            qcopy(rot,D_L03_001B2B0C+I(state,0)*128+0x70);
            func_L00_002B9D60(pos,rot,0,1);
            if (I(state,0x10)!=-1) func_L00_0042A500(I(state,0x10));
            func_002A7750(actor,4,-1);
        }
        break;
    case 4:
        if (func_002B3868(actor) && I(state,0xC)) D_001395C4[0]=1;
        func_002AA2E8(state+0x1C,0.0f,0.104719773f);
        D_00189E20.transform=1;
        D_00189E20.scale[0]=D_00189E20.scale[1]=1.0f-func_00283198(F(state,0x1C));
        D_00189E20.scale[2]=2.0f-func_00283180(F(state,0x1C));
        D_00189E20.interactionLock=1;
        if (F(state,0x1C)<=0.0f) {
            B(actor,0x30)=B(actor,0x32);
            D_00189E20.interactionLock=0;
            func_002A7750(actor,1,-1);
        }
        break;
    case 5:
        if ((!I(state,8) && !func_002B38B8(actor)) || (I(state,8) && D_001395C4[0])) {
            func_002A7750(actor,6,-1);
            H(actor,0x34)|=0x100;
            p=actor+0xC0; q=state+0x34;
            for (countdown=2;countdown>=0;countdown--) {
                F(q,0)=0.02f;
                I(state,0x18)=0;
                func_00282F20(p,p,F(q,0)); p+=0x10; q+=4;
            }
            H(actor,0x34)=(H(actor,0x34)&0xFFBE)|0x1000;
            I(actor,0x98)=I(*(char **)(actor+0x24),0x10);
        }
        break;
    case 6:
        step=D_L03_001B0400*0.000277777785f;
        rate=D_L03_001B03FC*0.0166666675f;
        if (func_002B3868(actor)) func_002E5CF8(1,0,actor);
        q=state+0x34;
        one=1.0f;
        i=0; p=actor+0xC0; velocityPtr=state+0x24; scalePtr=q;
        for (;i<3;i++,p+=16,velocityPtr+=4,scalePtr+=4,q+=4) {
            if (F(q,0)<one && (!i || F(q,-4)>D_L03_001B0404)) {
                func_002AA548(scalePtr,velocityPtr,1.0f,step,step,rate);
                if (F(q,0)>one) F(q,0)=one;
                func_00282F20(p,p,F(q,0));
            }
        }
        if (F(state,0x34)>=1.0f && F(state,0x38)>=1.0f && F(state,0x3C)>=1.0f) func_002A7750(actor,1,-1);
        tint=func_00283D38(D_L03_001B03F8,I(state,0x20),F(state,0x3C));
        tintB=(tint>>16)&255;
        tintG=(tint>>8)&255;
        func_002A0488(actor,tint&255,tintG,tintB);
        break;
    }
    if (B(actor,0x20)<5) {
        F(state,0x30)=func_00283B98(F(state,0x30),D_L03_001B03E0*0.000290888245f);
        if (F(state,0x18)<1.0f) func_002AA2E8(state+0x18,1.0f,0.0333333351f);
        if (func_002A77E0(2)) {
            angle=func_002A7940();
            pos[0]=func_00283180(angle)*0.85f;
            pos[1]=func_00283198(angle)*0.85f;
            pos[2]=0;
            func_00282CC0(pos,pos,actor+0x10);
            pos[2]+=0.1f;
            alpha=func_002A7878(D_L03_001B03E8,D_L03_001B03EC);
            scale=func_002A7878(0,1);
            color=func_00283D38(D_L03_001B03F0_0,D_L03_001B03F0[1],scale);
            speed=func_002A7878(2,3);
            life=func_002A7820(60,180);
            lifeByte = life;
            func_00282C88(rot);
            rot[2]=speed/func_00283CE0(life);
            random=func_002A77E0(255);
            func_002C3150(pos,rot,color,alpha,lifeByte,random&255,0);
        }
        func_L00_002E6CF0(func_L03_003CBC40,actor);
    }
}
