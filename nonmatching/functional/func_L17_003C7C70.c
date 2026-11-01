/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * us: 17_smolg: instruction at +0x4 differs.
 * us2: 17_smolg: instruction at +0x4 differs.
 * pal: func_L17_003C7C70 is in neither catalogue of pal.
 * Complete triggered tilt/orbit/return controller and full16-byte saved position/angle
 * objects. The-g profile restores observed pre-division nop spacing to1492/1492 bytes;
 * first+0x4 differs and allocation remains unresolved. Full-image jump-table/data placement is
 * unqualified.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern float D_L17_001B03B4 __attribute__((sda));
extern float D_L17_001B03B8 __attribute__((sda));
extern float D_L17_001B03BC __attribute__((sda));
extern float D_L17_001B03C0 __attribute__((sda));
extern float D_L17_001B03C4 __attribute__((sda));
extern float D_L17_001B03C8 __attribute__((sda));
extern float D_L17_001B03CC __attribute__((sda));
extern float D_L17_001B03D0 __attribute__((sda));
extern float D_L17_001B03D4 __attribute__((sda));
extern float D_L17_001B03D8 __attribute__((sda));
extern void func_002AEE70(void *,void *,void *,float,float,float);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern int func_L00_00324120(void *),func_002B3868(void *),func_00282948(void *);
extern void func_002A7750(void *,int,int);
extern int func_002E5CF8(int,int,void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int),func_002ABB18(float),func_00283198(float),func_00283180(float),func_00283B98(float,float),func_00283C28(float);
extern void func_00282CF0(void *,void *,void *),func_002AD6F0(void *,void *,void *,void *);
/* Tilts and lowers a triggered platform around its saved anchor, then returns it. */
void func_L17_003C7C70(char *object)
{
    Vec old,delta,angles,rotation;
    char *state=P(object,0x68);
    float phase,radius,x,y,c,t;
    old.q=*(Q *)(object+16);angles.q=*(Q *)(object+0xf0);
    I(state,0x8c)|=1;*(u16 *)(state+0x3e)|=8;*(u16 *)(object+0x34)|=32;
    func_002AEE70(object,state+0xa0,state+0xa4,D_L17_001B03B8,(360.0f/D_L17_001B03B4)*0.0002908882452f,-1.0f);
    func_002AEF28(object,state+0xa8,state+0xac,D_L17_001B03BC,(360.0f/D_L17_001B03C0)*0.0002908882452f,(360.0f/D_L17_001B03C4)*0.0002908882452f);
    switch(U(object,0x20)) {
    case 0: *(Q *)(state+0x90)=old.q;U(object,0x20)=1;break;
    case 1:
        if(func_L00_00324120(object)) {func_002A7750(object,2,-1);I(state,0xb0)=func_00283CF0(D_L17_001B03C8*60.0f);}break;
    case 2:
        if(func_002B3868(object)) func_002E5CF8(0,0,object);
        if(I(state,0xb0)==60) func_002E5CF8(0,0,object);
        if(func_00282948(state+0xb0)) {I(state,0xb4)=func_00283CF0(D_L17_001B03CC*60.0f);U(object,0x20)=3;break;}
        rotation.f[0]=func_00283198(func_002ABB18(func_00283CE0(I(state,0xb0))*0.75f))*0.017453294f;
        rotation.f[1]=func_00283180(func_002ABB18(func_00283CE0(I(state,0xb0))*0.89f))*0.017453294f;
        if((float)I(state,0xb4)>D_L17_001B03C8*60.0f-30.0f) {
            t=func_00283CE0(I(state,0xb0))/(D_L17_001B03C8*60.0f-30.0f);
            F(object,0xf4)=F(object,0xf4)*t+rotation.f[1]*(1.0f-t);
            F(object,0xf0)=F(object,0xf0)*t+rotation.f[0]*(1.0f-t);
        } else {F(object,0xf4)=rotation.f[1];F(object,0xf0)=rotation.f[0];}
        break;
    case 3:
        phase=func_00283CE0(I(state,0xb4))/(D_L17_001B03CC*60.0f);
        c=1.0f-phase;radius=c*D_L17_001B03D4;
        F(object,0xf4)=0;F(object,0xf0)=c*1.5707965f;
        x=func_00283180(func_00283B98(1.5707965f,F(object,0xf8)));
        y=func_00283198(F(object,0xf0));F(object,0x10)=x*(radius*y);
        x=func_00283198(func_00283B98(1.5707965f,F(object,0xf8)));
        y=func_00283198(F(object,0xf0));F(object,0x18)=0;F(object,0x14)=x*(radius*y);
        F(object,0x10)+=F(state,0x90);F(object,0x14)+=F(state,0x94);
        F(object,0x18)=F(state,0x98)-radius*func_00283180(F(object,0xf0));
        F(object,0x18)-=func_00283180(phase*1.5707965f)*D_L17_001B03D8;
        I(state,0x8c)&=~1;*(u16 *)(state+0x3e)&=~8;*(u16 *)(object+0x34)&=~32;
        if(func_00282948(state+0xb4)) {U(object,0x20)=4;I(state,0xb8)=func_00283CF0(D_L17_001B03D0*60.0f);}break;
    case 4:
        phase=func_00283CE0(I(state,0xb8))/(D_L17_001B03D0*60.0f);
        c=1.0f-phase;rotation.q=*(Q *)(object+0xf0);
        radius=(1.0f-c)*D_L17_001B03D4;
        F(object,0xf0)=func_00283C28(rotation.f[0]*c+c*4.7123895f+1.5707965f);
        F(object,0xf4)=rotation.f[1]*c;
        x=func_00283180(func_00283B98(1.5707965f,F(object,0xf8)));
        y=func_00283198(F(object,0xf0));F(object,0x10)=x*(radius*y);
        x=func_00283198(func_00283B98(1.5707965f,F(object,0xf8)));
        y=func_00283198(F(object,0xf0));F(object,0x18)=0;F(object,0x14)=x*(radius*y);
        F(object,0x10)+=F(state,0x90);F(object,0x14)+=F(state,0x94);
        F(object,0x18)=F(state,0x98)-radius*func_00283180(F(object,0xf0));
        F(object,0x18)-=func_00283180(c*1.5707965f)*D_L17_001B03D8;
        I(state,0x8c)&=~1;*(u16 *)(state+0x3e)&=~8;*(u16 *)(object+0x34)&=~32;
        if(func_00282948(state+0xb8)) {U(object,0x20)=1;*(Q *)(object+0xf0)=rotation.q;*(Q *)(object+16)=*(Q *)(state+0x90);}break;
    }
    if(U(object,0x20)<3) {func_00282CF0(&delta,object+16,&old);func_002AD6F0(state+0x50,&delta,&angles,object+0xf0);}
}
