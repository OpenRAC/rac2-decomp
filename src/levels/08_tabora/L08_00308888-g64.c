/*
 * func_L08_00308888: scripted level effects, one phase per D_L08_001BD800.phase.
 * Built with -G64 and gcse left on: the per-phase lui of the scene is reload
 * rematerializing PRE's spilled reaching register for %hi(D_L08_001BD800).
 */
#include "common.h"

typedef unsigned int u128 __attribute__((mode(TI)));

typedef struct TaboraParticleData {
    int pad00;
    int kind;
    short pad08;
    unsigned char alpha;
    unsigned char lifetime;
} TaboraParticleData;
typedef struct TaboraParticle {
    char pad00[3];
    unsigned char kind;
    char pad04[6];
    short lifetime;
    char pad0C[0x14];
    TaboraParticleData data;
} TaboraParticle;
typedef struct TaboraObject {
    char pad00[0x10];
    float position[4];
    char pad20[0x14];
    unsigned short flags;
    char pad36[0x32];
    char *vars;
    char pad6C[0x3E];
    short classId;
} TaboraObject;
typedef struct TaboraScene {
    char pad00[0x30];
    int phase;
    int frame;
    char pad38[0xC];
    short count;
    char pad46[0x146];
    TaboraObject *objects[0]; /* Variable-length actor list; only a prefix is described. */
} TaboraScene;
typedef struct TaboraEffectEntry {
    float position[4];
    int frame;
    float radius;
    float shake;
    int pad1C;
} TaboraEffectEntry;
typedef struct TaboraShake {
    char pad00[0x160];
    float amount0;
    int pad164;
    int duration0;
    int delay;
    float amount1;
    int pad174;
    int duration1;
    int pad17C;
    float amount2;
    int pad184;
    int duration2;
} TaboraShake;
extern TaboraScene D_L08_001BD800;
extern TaboraShake D_L08_001B99C0;
extern float D_L08_001B9B00[];
extern TaboraEffectEntry D_L08_00288D10[];
extern float D_L08_001A9430[4] __attribute__((sda));
extern float D_L08_001A9450[4][4] __attribute__((sda));
extern int D_001A79F0 MACRO_ADDR;
extern int D_L08_001A9420 __attribute__((sda));
extern int D_L08_001B2508 MACRO_ADDR;
extern float D_L08_001B2820[4] MACRO_ADDR;
extern float D_L08_001A9490 __attribute__((sda));
extern float D_L08_001A9494, D_L08_001A9498, D_L08_001A949C;
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, void *, int, int, float);
extern void func_L08_0037E6D8(void);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_002833F0(void *, void *);
extern float func_00283B98(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern void func_002A7A00(void *, float, float);
extern void func_002ACB48(void *, float);
extern void func_0032C700(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern TaboraParticle *func_002BDCE8(void *, float, float, float, int, void *, int, float, int);
extern void func_L00_003263D0(int, void *, int, int, void *, int, int, float, float, float, float);
extern void func_002C7970(void *, void *, int, int, int, int, int, int, float, float, float);
extern void func_002C3150(void *, void *, int, int, int, int, float);
extern void func_002C2FD8(void *, int, int, int, int, int, int, float);

/* Runs the scripted effects of the Tabora cutscene: sparks, screen shake, and glowing rings that change with each phase of the scene. */
void func_L08_00308888(void) {
    float vecA[4] __attribute__((aligned(16)));
    float vecB[4] __attribute__((aligned(16)));
    /* Adjacent in the frame: func_002833F0 fills all three as rows of one matrix. */
    float matrix[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    StartStartupAnimations();
    {
        int j = 0;
        TaboraObject *moby;
        for (; j < D_L08_001BD800.count; ++j) {
            moby = D_L08_001BD800.objects[j];
            if (moby && moby->classId==0xE29 /* moby class 3625 */) moby->flags |= 0x800;
            if (moby->classId==0xD54 /* moby class 3412 */) UpdateEquipmentPieces(moby);
            if (moby && moby->classId==0xFA0 /* TV Screens */ && moby->vars)
            StoreAngleUpdateResult(moby,moby->vars+12,0x80AAAAD2,0x80396464,0.061086535f);
        }
    }
    if (gCurrentMapIndex != 8) return;
    {
        if (D_L08_001BD800.phase==0) {
            int j;
            CopyGroupWordToMembers();
            for (j=0;j<4;++j) {
                TaboraEffectEntry *entry=&D_L08_00288D10[j];
                if (D_L08_001BD800.frame==entry->frame) {
                    *(u128 *)vecA=*(u128 *)entry->position;
                    FastVecAdd(vecA,vecA,D_L08_001A9430);
                    SpawnExplosion(vecA,0,25,20,20,20,45,1,1,1,0,0,entry->radius,20.0f);
                    if (entry->shake>0.0f) {
                        D_L08_001B99C0.duration0=55;
                        D_L08_001B99C0.duration2=70;
                        D_L08_001B99C0.delay=0;
                        D_L08_001B99C0.amount2=D_L08_001B99C0.amount0=entry->shake*0.08f;
                    }
                }
            }
        }
    }
    {
        if (D_L08_001BD800.phase==1) CopyGroupWordToMembers();
        if (D_L08_001BD800.phase==2) {
            TaboraObject *moby;
            int burstCount;
            int i;
            int colour, life, alpha, spin, packed;
            TaboraParticle *particle;
            float scale, size, angle, frameStep;
            moby=0;
            CopyGroupWordToMembers();
            burstCount=0;
            scale=1.0f;
            if (D_L08_001BD800.frame==53) {moby=D_L08_001BD800.objects[1];scale=0.7f;burstCount=30;}
            else if (D_L08_001BD800.frame==58) {moby=D_L08_001BD800.objects[0];burstCount=50;}
            if (moby) {
                *(u128 *)vecA = 0;
                vecA[2]=0.01f;
                vecA[3]=1.0f;
                frameStep=0.008333334f;
                for (i=0;i<burstCount;++i) {
                    life=RandomIntRange(90,117);
                    qzero(vecB);
                    AddRandomOffsetToVector(vecB,scale*0.7f);
                    vecB[2]*=0.3f;
                    FastVecAdd(vecB,vecB,moby->position);
                    alpha=RandomIntRange(64,112);
                    colour=RandomIntRange(64,127);
                    packed=(alpha<<24)|(FloatToInt((float)colour*0.3f)<<16);
                    packed|=colour<<8;
                    colour|=packed;
                    angle=RandomFloatRange(1.0f,1.013f);
                    spin=RandomIntRange(-2,2);
                    size=RandomFloatRange(0.1f,0.3f);
                    vecA[0]=RandomSignedFloatRange(0.0f,0.011666667f);
                    vecA[1]=RandomSignedFloatRange(0.0f,0.011666667f);
                    vecA[2]=RandomFloatRange(frameStep*0.1f,0.008333334f);
                    FastVecScale(vecA,vecA,scale);
                    particle=SpawnSpinningSparkParticle(vecB,0.1f,1.0f,angle,spin,vecA,colour,size*210000.0f,0);
                    if (particle) {
                        TaboraParticleData *particleData=&particle->data;
                        if (RandomIntBelow(2)) particle->kind=0x44;
                        particle->lifetime=life;
                        {
                            particleData->kind=2;
                            particleData->alpha=alpha;
                            particleData->lifetime=life;
                        }
                    }
                }
            }
        }
    }
    if (D_L08_001BD800.phase==3 && D_L08_001BD800.frame==D_L08_001A9420) {
        TaboraObject *first=D_L08_001BD800.objects[1];
        TaboraObject *second=D_L08_001BD800.objects[2];
        qcopy(vecA,second->position);
        vecA[2]+=0.8f;
        FastVecSub(vecB,first->position,second->position);
        vec_scale_to_length(vecB,vecB,0.035f);
        vecB[2]=0.041666668f;
        SpawnTintedEffects(0,vecA,40,0,vecB,0x39969696,0,0.75f,1.3f,0.2f,0.37f);
        D_L08_001B99C0.amount2=0.047f;
        D_L08_001B99C0.duration2=35;
        D_L08_001B99C0.amount0=0.037f;
        D_L08_001B99C0.duration0=30;
        D_L08_001B99C0.amount1=0.04f;
        D_L08_001B99C0.duration1=20;
        D_L08_001B99C0.delay=0;
    }
    if (D_L08_001BD800.phase==5) {
        D_L08_001BD800.objects[2]->flags&=0xFBFF;
        D_L08_001BD800.objects[3]->flags&=0xFBFF;
    }
    if (D_L08_001BD800.phase!=7) return;
    if (D_L08_001BD800.frame==0) {
        D_L08_001B2820[0]=0;
        D_L08_001B2820[1]=0;
        D_L08_001B2820[2]=0;
    }
    if ((unsigned)(D_L08_001BD800.frame-421)>=177) return;
    *(u128 *)vecA=*(u128 *)D_L08_001BD800.objects[3]->position;
    vecA[2]+=0.5f;
    if (D_L08_001BD800.frame<568) {
        int j;
        int spin;
        float size;
        D_L08_001B2820[0]=FastAddRotations(D_L08_001B2820[0],D_L08_001A9490*0.00029088824f);
        D_L08_001B2820[1]=FastAddRotations(D_L08_001B2820[1],D_L08_001A9494*0.00029088824f);
        D_L08_001B2820[2]=FastAddRotations(D_L08_001B2820[2],D_L08_001A9498*0.00029088824f);
        D_L08_001B2820[3]=FastAddRotations(D_L08_001B2820[3],D_L08_001A949C*0.00029088824f);
        euler_rotation_basis(matrix,D_L08_001B2820);
        for(j=0;j<4;++j) {
            FastVecSub(start,D_L08_001B9B00,vecA);
            vec_scale_to_length(start,start,5.0f);
            FastVecAdd(end,start,vecA);
            end[2]+=0.5f;
            spin=FloatToInt(RandomSignedFloatRange(2.0f,5.0f));
            matrix_mul_vec3(direction,D_L08_001A9450[j],matrix);
            vec_scale_to_length(direction,direction,3.5f);
            FastVecAdd(direction,direction,end);
            FastVecSub(vecB,end,direction);
            vec_scale_to_length(vecB,vecB,0.058333337f);
            size=RandomFloatRange(0.2f,0.32f);
            SpawnFadingDriftParticle(direction,vecB,60,0x804080,spin,0,63,6,size*210000.0f,147000.0f,0.0f);
        }
    }
    if (D_L08_001BD800.frame<=480) return;
    {
        float amount=6.0f;
        float rate=0.0f;
        float frameStep, timeScale, t, scale;
        float size;
        int alpha;
        int j;
        int duration, lifeStep;
        *(u128 *)vecB=*(u128 *)vecA;
        vecB[2]+=1.0f;
        if (RandomIntBelow(4)==0) {
            FastVecSub(forward,D_L08_001B9B00,vecB);
            timeScale=0.016666668f;
            frameStep=0.008333334f;
            vec_scale_to_length(forward,forward,5.0f);
            FastVecAdd(vecB,forward,vecB);
            RandomDirectionVector(matrix,rate,rate);
            size=(D_L08_001BD800.frame-480);
            size*=0.06666667f;
            alpha=RandomIntBelow(255)&255;
            duration=60;
            lifeStep=0;
            SpawnHeroRelativeParticle(vecB,matrix,0x50804080,duration,alpha,0,size);
            for (j=0;j<1;++j) {
                t=rate*timeScale;
                RandomDirectionVector(offset,t,t);
                FastVecAdd(matrix,matrix,offset);
                t=0.0f; /* Second set in the loop: keeps rate*timeScale from being hoisted and folded. */
                scale=amount*frameStep*(D_L08_001BD800.frame-480);
                alpha=RandomIntBelow(255)&255;
                SpawnHeroRelativeParticle(vecB,matrix,0x40804080,duration,alpha,0,scale);
                duration+=lifeStep;
            }
        }
    }
    vec_scale_to_length(direction,forward,0.1f);
    {
        int j, alpha, colour, full, value;
        float size;
        j=0;
        full=255;
        for (;j<=0;++j) {
            size=IntToFloat(full-((D_L08_001B2508+j*20)&255));
            size=FloatAbs(0.5f-size*0.003921569f);
            colour=FastTweenColor(0x40FF40FF,0x10FF40FF,size);
            alpha=(unsigned char)D_L08_001B2508;
            if(j&2) alpha<<=1;
            if(j&1) alpha=full-alpha;
            value=alpha&255;
            size=(IntToFloat(j)+5.0f)*0.008333334f;
            size*=(D_L08_001BD800.frame-480);
            SpawnFadingParticle_002C2FD8(forward,colour,value,53,1,2,0,size);
            FastVecAdd(forward,forward,direction);
        }
    }
}
