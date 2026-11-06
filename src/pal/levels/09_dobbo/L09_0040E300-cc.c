/* func_PAL_L09_0040E300, the PAL copy of func_L09_00409308: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L09_004091C8 becomes func_PAL_L09_0040E1C0; wrap func_002A7878(1200.0f,2400.0f) (({e}) * 5.0f + 2.0f) * ; wrap func_002A7878(1200.0f,2400.0f) (({e}) * 5.0f + 2.0f) * ; wrap func_002A7878(180.0f,300.0f) (({e}) * 5.0f + 2.0f) * 0.. */
#include "common.h"
typedef int Quad_Dobbo __attribute__((mode(TI)));
typedef struct DobboPlayer {
    char pad0[0x80];
    float position[4];
    char pad90[0x50];
    float aim[4];
    char padf0[0x20];
    float velocity[4];
    char pad120[0x1710];
    char *target;
    char pad1834[0xa60];
    int mode;
} DobboPlayer;
extern DobboPlayer D_00189E20;
typedef struct DobboAnimation {
    char pad[0x43];
    unsigned char animation;
} DobboAnimation;
extern float func_002A7878(float, float);
extern void func_002A7750(char *, int, int);
extern int func_00282948(void *);
extern void func_PAL_L09_0040E1C0(char *);

typedef struct DobboPath {
    int count;
    char pad[12];
    float points[0][4];
} DobboPath;
extern DobboPath *D_L09_001FE6C0[];
typedef struct DobboPathEffect {
    float dimensions[3];
    int flags;
    float position[4];
} DobboPathEffect;
extern DobboPathEffect D_L09_001C7B80[];
extern float func_00282E48(void *, void *);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_00282DF0(void *);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
void func_PAL_L09_0040E300(char *obj)
{
    char *d = *(char **)(obj+0x68);
    char *r;
    float distance, angle, inverse;
    Quad_Dobbo target;
    switch (B(obj,0x20)) {
    case 0: {
        DobboPath *path;
        path = D_L09_001FE6C0[I(d,0x260)];
        I(d,0x268)=0;
        *(DobboPath **)(d+0x26c)=path;
        distance = func_00282E48(path->points[0],path->points[1]);
        inverse = 1.0f / distance;
        F(d,0x29c)=(inverse*0.020000001f)*F(d,0x264);
        I(d,0x274)=func_L00_002FCF18(obj+0x10,F(d,0x278),F(d,0x288),F(d,0x27c),F(d,0x280),F(d,0x284));
        func_002A7750(obj,2,-1);
        break;
    }
    case 2:
        if (D_00189E20.mode==0x31) {
            r=D_00189E20.target;
            if(r && *(short *)(r+0xaa)==0x905 && B(r,0x20)!=0xfe && B(r,0x20)!=0xfd) {
                B(obj,0x30)=0xff; *(short *)(obj+0x32)=0x3ff; I(d,0x268)=0;
                if(((DobboAnimation *)obj)->animation!=4) func_PAL_002A7E68(obj,4,0,10);
                func_002A7750(obj,1,-1);
            }
        }
    case 3:
        if(((DobboAnimation *)obj)->animation==0 && func_00282948(d+0x298)) {
                I(d,0x298)=func_00283CF0(((func_002A7878(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
                { int state=(func_001163B0()&1)+1;
                  if(((DobboAnimation *)obj)->animation!=state) func_PAL_002A7E68(obj,state,0,8); }
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=0) func_PAL_002A7E68(obj,0,0,8);
        }
        angle=func_00283248(D_00189E20.position[0]-F(obj,0x10),D_00189E20.position[1]-F(obj,0x14));
        F(obj,0xf8)=func_00283B98(F(obj,0xf8),func_00283BE0(angle,F(obj,0xf8))*0.01f);
        break;
    case 1: {
        DobboPath *path;
        DobboPathEffect *effect;
        if(((DobboAnimation *)obj)->animation==4 && func_00282948(d+0x298)) {
                I(d,0x298)=func_00283CF0(((func_002A7878(1200.0f,2400.0f)) * 5.0f + 2.0f) * 0.16666667f);
                if(((DobboAnimation *)obj)->animation!=2) func_PAL_002A7E68(obj,2,0,8);
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=4) func_PAL_002A7E68(obj,4,0,10);
        }
        path=*(DobboPath **)(d+0x26c);
        func_002C9828(path,1,obj+0x10,obj+0xf0,0,F(d,0x268));
        distance=func_00282E48(obj+0x10,D_00189E20.position);
        if(distance<10.0f) F(d,0x29c)*=1.01f;
        else if(distance>30.0f) F(d,0x29c)*=0.99f;
        else {
            path=*(DobboPath **)(d+0x26c);
            distance = func_00282E48(path->points[0],path->points[1]);
            inverse = 1.0f / distance;
            F(d,0x29c)+=((inverse*0.020000001f)*F(d,0x264)-F(d,0x29c))*0.05f;
        }
        F(d,0x268)+=F(d,0x29c);
        effect=&D_L09_001C7B80[I(d,0x274)];
        qcopy(effect->position,obj+0x10);
        effect->position[3]=F(d,0x278);
        effect->dimensions[0]=F(d,0x27c);
        effect->dimensions[1]=F(d,0x280);
        effect->dimensions[2]=F(d,0x284);
        effect->flags=0;
        if(func_00283CF0(F(d,0x268))+2>=(*(DobboPath **)(d+0x26c))->count) B(obj,0xbc)=1;
        break;
    }
    }
    if(((DobboAnimation *)obj)->animation==0) {
        if(func_00282E80(obj+0x10,D_00189E20.position)<8.0f &&
           func_00283C80(F(obj,0xf8),func_00283248(D_00189E20.aim[0]-F(obj,0x10),D_00189E20.aim[1]-F(obj,0x14)))<1.5707965f) {
            if(func_00282DF0(D_00189E20.velocity)>0.01f) I(d,0x290)=100;
            else func_00282948(d+0x290);
        } else if(I(d,0x290)) { I(d,0x290)=0; qcopy(d+0x250,D_00189E20.aim); }
        if(func_00282948(d+0x294)) {
            I(d,0x294)=func_00283CF0(((func_002A7878(180.0f,300.0f)) * 5.0f + 2.0f) * 0.16666667f);
            angle=func_00283B98(F(obj,0xf8),func_002A7878(-90.0f,90.0f)*0.017453294f);
            distance=func_002A7878(0.0f,30.0f)*0.017453294f;
            func_002AF000(d+0x250,6.0f,angle,distance);
            func_00282CC0(d+0x250,d+0x250,obj+0x10);
        }
        if (I(d,0x290))
            qcopy(&target,D_00189E20.aim);
        else
            qcopy(&target,d+0x250);
    }
    if(B(obj,0xbc)) { func_00291450(I(d,0x274)); func_0029F338(obj); }
    else func_PAL_L09_0040E1C0(obj);
}
#undef F
#undef I
#undef B
