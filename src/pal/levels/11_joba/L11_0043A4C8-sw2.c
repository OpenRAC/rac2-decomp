#include "include_asm.h"

#include "common.h"
struct AnimationView { char pad[0x43]; unsigned char animation; };
#define ANIM(p) (((struct AnimationView *)(p))->animation)
typedef int Quad __attribute__((mode(TI)));
#define COPY(d,s) (*(Quad *)(d)=*(Quad *)(s))
#define B(p,n) (*(unsigned char *)((char *)(p)+(n)))
#define H(p,n) (*(short *)((char *)(p)+(n)))
#define U(p,n) (*(unsigned short *)((char *)(p)+(n)))
#define I(p,n) (*(int *)((char *)(p)+(n)))
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
extern int D_L11_001A8FF4 __attribute__((sda));
extern char D_00189EA0[];
extern char *D_L11_001C0D18 NOT_SDA;
extern char *D_0018C2BC NOT_SDA;
extern void func_PAL_L11_0043B8D0(char *),func_L11_00436768(char *),func_PAL_L11_0043BFF8(char *);
extern void func_L11_00436B78(char *,char *);
extern int func_PAL_L11_0043C288(char *,void *);
extern char *func_L11_004417E8(char *);
extern int func_L11_00441808(char *,void *);
extern void func_PAL_L02_004009A0(char *,int,int);
extern void func_002A7750(void *,int,int),func_PAL_002A7E68(void *,int,int,int);
extern int func_002A77E0(int),func_002B3890(void *),func_002B3868(void *),func_002B1C20(void *,void *);
extern float func_002B04E0(void *,void *,void *),func_00283248(float,float),func_00283C80(float,float),func_00282E48(void *,void *),func_00282E80(void *,void *),func_0029F530(void *),func_002A7878(float,float);
extern void func_00282CF0(void *,void *,void *),func_00282CC0(void *,void *,void *),func_00282F20(void *,void *,float),func_00282D30(void *,void *,float),func_002833F0(void *,void *),func_002AB6D8(void *,void *);
extern void func_002B60B0(void *,float,float,float,float),func_PAL_L01_00323068(void *,void *),func_PAL_L02_00335630(void *,void *),func_PAL_002B5BA8(void *,void *,float),func_PAL_002B5C98(void *,void *,float),func_PAL_002B5E30(void *,float),func_L07_00321D68(void *,void *),func_002B4090(void *,void *,float,float,float);
extern int func_00277258(void *,int,void *,float);
extern void func_002A8D70(void *,int,int,int,int,int,float,float,float);
static __inline__ void SetAnimation(char *p, int animation, int mode, int blend)
{
    if (ANIM(p) != animation) func_PAL_002A7E68(p, animation, mode, blend);
}
/* Flies to one point from afar and another up close; case 7 uses one point for both. */
static __inline__ void FlyByDistance(char *p, float *farPoint, float *nearPoint, float distance)
{
    if (distance>3.0f) func_PAL_L02_00335630(p,farPoint);
    else func_PAL_L02_00335630(p,nearPoint);
}

void func_PAL_L11_0043AB80(char *p)
{
    float target[4],delta[4],zero[4],matrix[4][4];
    char *s=P(p,0x68), *node;
    float angle,turn,distance;
    int i,flags,clear;
    float *spin;
    if (B(p,0x20)==1) return;
    if (H(s,0x286) && !D_L11_001A8FF4 && B(p,0x20)!=11 && B(p,0x20)!=10) return;
    func_PAL_L11_0043B8D0(p);
    if (B(p,0x20)==1) return;
    if (H(s,0x286) && !D_L11_001A8FF4) return;
    if (!H(s,0x282)) {
        I(s,0x270)=0;
        if (B(p,0x95)==3) {
            func_002A7750(p,5,2);
            if (func_002A77E0(2)) {
                SetAnimation(p,1,0,8);
            } else SetAnimation(p,4,0,8);
        }
    }
    node=0;
    if (P(p,0xB8)) node=func_L11_004417E8(P(p,0xB8));
    if (I(s,0x270)) COPY(target,P(s,0x270)+0x10); else COPY(target,D_00189EA0);
    if (H(s,0x286)) {
        func_00282CF0(delta,target,p+0x10);
        angle=0;
        turn=func_002B04E0(p,delta,s+0x210);
    } else {
        angle=func_00283248(target[0]-F(p,0x10),target[1]-F(p,0x14));
        turn=func_00283C80(angle,F(p,0xF8));
    }
    distance=func_00282E48(p+0x10,target);
    if (B(p,0x95)==2) {
        if (func_002B3890(p)) {
            SetAnimation(p,6,0,8);
            B(p,0xBC)=0;
            func_002B60B0(p,0.0064000003f,0.16000001f,0.010053098f,0.25132746f);
            func_L11_00436B78(p,node);
            U(p,0x96)=10000;
        }
        if (B(p,0xBC)==1 && U(p,0x96)>=251) {
            switch (func_002A77E0(2)) {
            case 0:
                SetAnimation(p,1,0,8);
                break;
            case 1:
                SetAnimation(p,4,0,8);
                break;
            }
            U(p,0x96)=func_002A77E0(83);
        }
        if (H(s,0x282)) {
            func_002A7750(p,6,3);
            SetAnimation(p,2,0,8);
        }
        {
            char *home=s+0x250;
            if (!B(p,0xBC) && func_00282E80(p+0x10,home)<0.5f) B(p,0xBC)=1;
            else if (H(s,0x286)) func_PAL_L02_00335630(p,home);
            else func_PAL_L01_00323068(p,home);
        }
    }
    switch (B(p,0x20)) {
    case 3:
        if (func_002B3868(p)) {
            B(p,0xBC)=0;
            SetAnimation(p,1,0,0);
            U(p,0x96)=0;
        }
        if (!B(p,0xBC) && H(s,0x284)<U(p,0x96)) {
            SetAnimation(p,6,0,8);
            B(p,0xBC)=1;
        } else if (B(p,0xBC)==1) {
            if (func_L11_00441808(P(p,0xB8),p+0x10)) func_002A7750(p,5,2);
            func_PAL_L01_00323068(p,func_L11_004417E8(P(p,0xB8)));
        }
        break;
    case 4:
        if (func_002B3868(p)) {
            SetAnimation(p,6,0,8);
            U(p,0x96)=0;
        }
        func_00282F20(zero,p+0xE0,F(s,0x104)+F(s,0x100));
        func_00282CC0(delta,p+0x10,zero);
        clear=1;
        if (func_00277258(delta,5,p,F(s,0x100)) && D_L11_001C0D18 && H(D_L11_001C0D18,0xAA)==0xB3A) clear=0;
        if (clear) {
            I(p,0x98)=I(P(p,0x24),0x10);
            func_002A7750(p,5,2);
        }
        F(p,0x18)+=0.16000001f;
        break;
    case 5: break;
    case 6:
        if (B(p,0x60)&2) func_002A7750(p,7,-1);
        break;
    case 7:
        if (func_002B3868(p)) SetAnimation(p,6,0,12);
        if (B(p,0x42)==5 && distance>14.0f) {
            SetAnimation(p,6,0,3);
            func_002B60B0(p,0.0064000003f,0.16000001f,0.010053098f,0.25132746f);
        } else if (B(p,0x42)==6 && distance<9.0f) {
            SetAnimation(p,5,0,3);
            func_002B60B0(p,0.0032000002f,0.080000006f,0.010053098f,0.25132746f);
        }
        if (H(s,0x286)) {
            if (distance<3.0f && turn<0.01745329425f) {
                func_002A7750(p,9,-1);
                SetAnimation(p,3,4,2);
            } else FlyByDistance(p,target,target,distance);
        } else {
            if (distance<3.0f && turn<0.01745329425f) {
                func_002A7750(p,9,-1);
                SetAnimation(p,3,4,2);
            } else if (distance>3.0f) {
                if (!func_PAL_L11_0043C288(p,p+0x10)) func_PAL_002B5BA8(p,target,F(s,0x274));
            } else func_PAL_002B5C98(p,p+0x10,angle);
        }
        break;
    case 8:
        if (func_002B3868(p)) func_002B60B0(p,0.2f,2.0000002f,0.005026549f,0.12566373f);
        if (B(p,0x42)==7) {
            if (func_0029F530(p)<=14.0f) {
                if (H(s,0x286)) func_PAL_L02_00335630(p,target);
                else func_PAL_002B5C98(p,target,angle);
                func_002A8D70(p,0,1,0,1,0,0.4f,B(s,0x34),1.0f);
            } else {
                func_002B60B0(p,0.080000006f,0.040000003f,0.005026549f,0.12566373f);
                func_00282F20(delta,p+0xC0,-4.0f);
                func_00282CC0(delta,p+0x10,delta);
                I(s,0x138)|=0x10;
                if (H(s,0x286)) func_PAL_L02_00335630(p,delta); else func_PAL_L01_00323068(p,delta);
                I(s,0x138)&=~0x10;
                func_002A8D70(p,0,1,0,1,0,0.4f,B(s,0x34),1.0f);
            }
        }
        if (B(p,0x60)&2) {
            if (D_0018C2BC==p) {
                SetAnimation(p,2,0,8);
                func_002A7750(p,6,-1);
            } else func_002A7750(p,7,-1);
        }
        break;
    case 9:
        if (!H(s,0x286)) func_PAL_002B5E30(p,angle);
        if (B(p,0x60)&2) {
            SetAnimation(p,7,4,2);
            func_002A7750(p,8,-1);
        }
        break;
    case 10:
        flags=func_002B1C20(p,s+0x50);
        if (B(p,0x42)==8) {
            if (!func_002A77E0(30) || (flags&1)) {
                if (func_0029F530(p)<10.0f && H(s,0x286) && !func_002A77E0(2)) func_002A7750(p,11,-1);
                else { func_PAL_L02_004009A0(p,0,-1); func_PAL_L11_0043BFF8(p); }
            }
        } else if (flags&2) {
            SetAnimation(p,2,0,8);
            func_002A7750(p,6,3);
        }
        break;
    case 11:
        if (func_002B3868(p)) {
            func_00282CF0(s+0x1A0,func_L11_004417E8(P(p,0xB8)),p+0x10);
            F(s,0x1A8)=0;
            func_00282F20(s+0x1A0,s+0x1A0,func_002A7878(3.0f,5.0f)*0.020000001f);
            H(s,0x286)=0;
            spin=(float *)(s+0x260);
            for (i=0;i<3;i++) {
                spin[i]=func_002A7878(240.0f,720.0f)*0.0003490659f;
                qcopy(matrix[i],p+0xC0+i*16);
            }
            func_002AB6D8(matrix,p+0xF0);
            SetAnimation(p,9,0,25);
            U(p,0x34)&=0xEFFF;
        }
        F(s,0x1A8)-=F(s,0x12C);
        func_L07_00321D68(p,s+0x1A0);
        func_00282D30(s+0x260,s+0x260,0.98f);
        *(Quad *)zero=0;
        zero[2]=F(s,0x30);
        COPY(delta,zero);
        func_002B4090(p,delta,F(s,0x260),F(s,0x264),F(s,0x268));
        func_002833F0(p+0xC0,p+0xF0);
        if (F(p,0x18)<F(func_L11_004417E8(P(p,0xB8)),8)+5.0f || !func_002A77E0(450) || U(p,0x96)>=301) {
            func_PAL_L02_004009A0(p,0,-1);
            func_PAL_L11_0043BFF8(p);
        }
        break;
    }
    func_L11_00436768(p);
}
