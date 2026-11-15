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
extern void func_L09_004091C8(char *);

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
extern void func_002A7470(void *, int, int, int);
extern void func_002C9828(void *, int, void *, void *, int, float);
extern void func_002AF000(void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00291450(int);
extern void func_0029F338(void *);
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
/* Per-frame update of a guide creature (moby class 3610): it rides along a path once the hero gets on a glider, looks at the hero and watches where he aims. */
void func_L09_00409308(char *obj)
{
    char *vars = *(char **)(obj+0x68);
    char *glider;
    float distance, angle, inverse;
    Quad_Dobbo target;
    switch (B(obj,0x20)) {
    case 0: {
        DobboPath *path;
        path = D_L09_001FE6C0[I(vars,0x260)];
        I(vars,0x268)=0;
        *(DobboPath **)(vars+0x26c)=path;
        distance = fast_vec_dist(path->points[0],path->points[1]);
        inverse = 1.0f / distance;
        F(vars,0x29c)=(inverse*0.0166666675f)*F(vars,0x264);
        I(vars,0x274)=AllocateEffectSlot_L00_2(obj+0x10,F(vars,0x278),F(vars,0x288),F(vars,0x27c),F(vars,0x280),F(vars,0x284));
        SetMobyState(obj,2,-1);
        break;
    }
    case 2:
        if (gHeroState.mode==0x31) {
            glider=gHeroState.target;
            if(glider && *(short *)(glider+0xaa)==0x905 /* Glider */ && B(glider,0x20)!=0xfe && B(glider,0x20)!=0xfd) {
                B(obj,0x30)=0xff; *(short *)(obj+0x32)=0x3ff; I(vars,0x268)=0;
                if(((DobboAnimation *)obj)->animation!=4) StartAnimationBlended(obj,4,0,10);
                SetMobyState(obj,1,-1);
            }
        }
    case 3:
        if(((DobboAnimation *)obj)->animation==0 && FastFloatHelperD(vars+0x298)) {
                I(vars,0x298)=FloatToInt(RandomFloatRange(1200.0f,2400.0f));
                { int state=(Rand()&1)+1;
                  if(((DobboAnimation *)obj)->animation!=state) StartAnimationBlended(obj,state,0,10); }
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=0) StartAnimationBlended(obj,0,0,10);
        }
        angle=FastMatrixHelperA(gHeroState.position[0]-F(obj,0x10),gHeroState.position[1]-F(obj,0x14));
        F(obj,0xf8)=FastAddRotations(F(obj,0xf8),fast_subtract_rotations(angle,F(obj,0xf8))*0.01f);
        break;
    case 1: {
        DobboPath *path;
        DobboPathEffect *effect;
        if(((DobboAnimation *)obj)->animation==4 && FastFloatHelperD(vars+0x298)) {
                I(vars,0x298)=FloatToInt(RandomFloatRange(1200.0f,2400.0f));
                if(((DobboAnimation *)obj)->animation!=2) StartAnimationBlended(obj,2,0,10);
        } else if(B(obj,0x60)&2) {
            if(((DobboAnimation *)obj)->animation!=4) StartAnimationBlended(obj,4,0,10);
        }
        path=*(DobboPath **)(vars+0x26c);
        SamplePathPosition(path,1,obj+0x10,obj+0xf0,0,F(vars,0x268));
        distance=fast_vec_dist(obj+0x10,gHeroState.position);
        if(distance<10.0f) F(vars,0x29c)*=1.01f;
        else if(distance>30.0f) F(vars,0x29c)*=0.99f;
        else {
            path=*(DobboPath **)(vars+0x26c);
            distance = fast_vec_dist(path->points[0],path->points[1]);
            inverse = 1.0f / distance;
            F(vars,0x29c)+=((inverse*0.0166666675f)*F(vars,0x264)-F(vars,0x29c))*0.05f;
        }
        F(vars,0x268)+=F(vars,0x29c);
        effect=&D_L09_001C7B80[I(vars,0x274)];
        qcopy(effect->position,obj+0x10);
        effect->position[3]=F(vars,0x278);
        effect->dimensions[0]=F(vars,0x27c);
        effect->dimensions[1]=F(vars,0x280);
        effect->dimensions[2]=F(vars,0x284);
        effect->flags=0;
        if(FloatToInt(F(vars,0x268))+2>=(*(DobboPath **)(vars+0x26c))->count) B(obj,0xbc)=1;
        break;
    }
    }
    if(((DobboAnimation *)obj)->animation==0) {
        if(vec_distance_xy(obj+0x10,gHeroState.position)<8.0f &&
           FastDiffRots(F(obj,0xf8),FastMatrixHelperA(gHeroState.aim[0]-F(obj,0x10),gHeroState.aim[1]-F(obj,0x14)))<1.5707965f) {
            if(FastVecLength(gHeroState.velocity)>0.01f) I(vars,0x290)=120;
            else FastFloatHelperD(vars+0x290);
        } else if(I(vars,0x290)) { I(vars,0x290)=0; qcopy(vars+0x250,gHeroState.aim); }
        if(FastFloatHelperD(vars+0x294)) {
            I(vars,0x294)=FloatToInt(RandomFloatRange(180.0f,300.0f));
            angle=FastAddRotations(F(obj,0xf8),RandomFloatRange(-90.0f,90.0f)*0.017453294f);
            distance=RandomFloatRange(0.0f,30.0f)*0.017453294f;
            BuildSphericalOffset(vars+0x250,6.0f,angle,distance);
            FastVecAdd(vars+0x250,vars+0x250,obj+0x10);
        }
        if (I(vars,0x290))
            qcopy(&target,gHeroState.aim);
        else
            qcopy(&target,vars+0x250);
    }
    if(B(obj,0xbc)) { FreePointLight(I(vars,0x274)); MarkMobySpawned(obj); }
    else SpawnDeathSparkParticles(obj);
}
#undef F
#undef I
#undef B
