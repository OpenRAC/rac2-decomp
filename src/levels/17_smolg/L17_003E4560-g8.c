#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
extern float D_L17_001B0CA8 __attribute__((sda));
typedef struct { char pad[0x18]; void *object; } Contact;
extern Contact D_L17_001C0000;
extern char D_L17_001C0040[];
extern float func_00283248(float,float), func_00283B98(float,float);
extern int func_00283CF0(float), func_002AD0B0(void *);
extern void func_002A7CA0(void *,void *,float,float,float,float), func_L04_0033D0C0(void *,void *), func_002C9218(int,void *,void *,float);
extern float func_002A89A8(void *,int,float);
extern void func_002AD0E0(void *,void *,void *,void *,void *,void *), func_L04_00344568(void *,void *,float);

/* Turns the creature toward its target and lets gravity pull it down onto the ground (or
   onto a moving object it lands on). */
void func_L17_003E4560(char *obj) {
    float tmp[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    char *state=*(char **)(obj+0x68);
    char *target;
    float ground, angle, frame;
    int frames;
    if(B(obj,0x20)==4 && B(obj,0x42)==9) {
        target=*(char **)(state+0x408);
        angle=FastMatrixHelperA(F(target,0x10)-F(obj,0x10),F(target,0x14)-F(obj,0x14));
        angle=FastAddRotations(angle,F(state,0x414));
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.10471977f);
        frames=FloatToInt(D_L17_001B0CA8*1024.0f);
        frame=D_L17_001B0CA8;
        I(state,0x140)=frames;
        F(state,0x144)=frame;
        ProbeAheadOfObject(obj,state+0x140);
        if(I(state,0x444)!=-1) PushPointAwayFromPath(I(state,0x444),obj+0x10,obj+0x10,D_L17_001B0CA8);
    } else if(B(obj,0x20)==5) {
        target=*(char **)(state+0x408);
        angle=FastMatrixHelperA(F(target,0x10)-F(obj,0x10),F(target,0x14)-F(obj,0x14));
        angle=FastAddRotations(angle,F(state,0x414));
        MobySpringTurn(obj,state+0x410,angle,0.05f,0.3f,0.10471977f);
    }
    if(I(state,0x420)) {
        *(Quad *)tmp=0;
        TransformPointAndRotationByParent(obj,*(void **)(state+0x420),obj+0x10,obj+0xf0,obj+0x10,tmp);
        F(obj,0xf8)=tmp[2];
    }
    F(state,0x424)+=0.0055555557f;
    F(obj,0x18)-=F(state,0x424)-2.0f;
    ground=ProbeGroundHeightBelow(obj+0x10,0,0.5f);
    F(obj,0x18)-=2.0f;
    if(F(obj,0x18)<ground) {
        if(D_L17_001C0000.object && GetMobyPrivateValue2(D_L17_001C0000.object)) I(state,0x420)=(int)D_L17_001C0000.object;
        else if(I(state,0x420)) I(state,0x420)=0;
        F(obj,0x18)=ground; F(state,0x424)=0;
        if(I(state,0x420)) {
            *(Quad *)rot=*(Quad *)(obj+0xf0); *(Quad *)tmp=*(Quad *)(D_L17_001C0040);
            BuildAxisAngleRotation(tmp,rot,F(obj,0xf8));
        }
    }
}
