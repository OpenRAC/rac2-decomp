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

void func_L08_00308888(void) {
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    /* Adjacent in the frame: func_002833F0 fills all three as rows of one matrix. */
    float matrix[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    func_L00_002FC980();
    {
        int j = 0;
        TaboraObject *p;
        for (; j < D_L08_001BD800.count; ++j) {
            p = D_L08_001BD800.objects[j];
            if (p && p->classId==0xE29) p->flags |= 0x800;
            if (p->classId==0xD54) func_002E64A0(p);
            if (p && p->classId==0xFA0 && p->vars)
            func_L00_00326048(p,p->vars+12,0x80AAAAD2,0x80396464,0.061086535f);
        }
    }
    if (D_001A79F0 != 8) return;
    {
        if (D_L08_001BD800.phase==0) {
            int j;
            func_L08_0037E6D8();
            for (j=0;j<4;++j) {
                TaboraEffectEntry *entry=&D_L08_00288D10[j];
                if (D_L08_001BD800.frame==entry->frame) {
                    *(u128 *)v=*(u128 *)entry->position;
                    func_00282CC0(v,v,D_L08_001A9430);
                    func_0032C700(v,0,25,20,20,20,45,1,1,1,0,0,entry->radius,20.0f);
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
        if (D_L08_001BD800.phase==1) func_L08_0037E6D8();
        if (D_L08_001BD800.phase==2) {
            TaboraObject *p;
            int n;
            int i;
            int colour, life, alpha, spin, packed;
            TaboraParticle *r;
            float scale, size, angle, frameStep;
            p=0;
            func_L08_0037E6D8();
            n=0;
            scale=1.0f;
            if (D_L08_001BD800.frame==53) {p=D_L08_001BD800.objects[1];scale=0.7f;n=30;}
            else if (D_L08_001BD800.frame==58) {p=D_L08_001BD800.objects[0];n=50;}
            if (p) {
                *(u128 *)v = 0;
                v[2]=0.01f;
                v[3]=1.0f;
                frameStep=0.008333334f;
                for (i=0;i<n;++i) {
                    life=func_002A7820(90,117);
                    qzero(w);
                    func_002ACB48(w,scale*0.7f);
                    w[2]*=0.3f;
                    func_00282CC0(w,w,p->position);
                    alpha=func_002A7820(64,112);
                    colour=func_002A7820(64,127);
                    packed=(alpha<<24)|(func_00283CF0((float)colour*0.3f)<<16);
                    packed|=colour<<8;
                    colour|=packed;
                    angle=func_002A7878(1.0f,1.013f);
                    spin=func_002A7820(-2,2);
                    size=func_002A7878(0.1f,0.3f);
                    v[0]=func_002A78D8(0.0f,0.011666667f);
                    v[1]=func_002A78D8(0.0f,0.011666667f);
                    v[2]=func_002A7878(frameStep*0.1f,0.008333334f);
                    func_00282D30(v,v,scale);
                    r=func_002BDCE8(w,0.1f,1.0f,angle,spin,v,colour,size*210000.0f,0);
                    if (r) {
                        TaboraParticleData *particleData=&r->data;
                        if (func_002A77E0(2)) r->kind=0x44;
                        r->lifetime=life;
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
        qcopy(v,second->position);
        v[2]+=0.8f;
        func_00282CF0(w,first->position,second->position);
        func_00282F20(w,w,0.035f);
        w[2]=0.041666668f;
        func_L00_003263D0(0,v,40,0,w,0x39969696,0,0.75f,1.3f,0.2f,0.37f);
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
    *(u128 *)v=*(u128 *)D_L08_001BD800.objects[3]->position;
    v[2]+=0.5f;
    if (D_L08_001BD800.frame<568) {
        int j;
        int spin;
        float size;
        D_L08_001B2820[0]=func_00283B98(D_L08_001B2820[0],D_L08_001A9490*0.00029088824f);
        D_L08_001B2820[1]=func_00283B98(D_L08_001B2820[1],D_L08_001A9494*0.00029088824f);
        D_L08_001B2820[2]=func_00283B98(D_L08_001B2820[2],D_L08_001A9498*0.00029088824f);
        D_L08_001B2820[3]=func_00283B98(D_L08_001B2820[3],D_L08_001A949C*0.00029088824f);
        func_002833F0(matrix,D_L08_001B2820);
        for(j=0;j<4;++j) {
            func_00282CF0(start,D_L08_001B9B00,v);
            func_00282F20(start,start,5.0f);
            func_00282CC0(end,start,v);
            end[2]+=0.5f;
            spin=func_00283CF0(func_002A78D8(2.0f,5.0f));
            func_00283098(direction,D_L08_001A9450[j],matrix);
            func_00282F20(direction,direction,3.5f);
            func_00282CC0(direction,direction,end);
            func_00282CF0(w,end,direction);
            func_00282F20(w,w,0.058333337f);
            size=func_002A7878(0.2f,0.32f);
            func_002C7970(direction,w,60,0x804080,spin,0,63,6,size*210000.0f,147000.0f,0.0f);
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
        *(u128 *)w=*(u128 *)v;
        w[2]+=1.0f;
        if (func_002A77E0(4)==0) {
            func_00282CF0(forward,D_L08_001B9B00,w);
            timeScale=0.016666668f;
            frameStep=0.008333334f;
            func_00282F20(forward,forward,5.0f);
            func_00282CC0(w,forward,w);
            func_002A7A00(matrix,rate,rate);
            size=(D_L08_001BD800.frame-480);
            size*=0.06666667f;
            alpha=func_002A77E0(255)&255;
            duration=60;
            lifeStep=0;
            func_002C3150(w,matrix,0x50804080,duration,alpha,0,size);
            for (j=0;j<1;++j) {
                t=rate*timeScale;
                func_002A7A00(offset,t,t);
                func_00282CC0(matrix,matrix,offset);
                t=0.0f; /* Second set in the loop: keeps rate*timeScale from being hoisted and folded. */
                scale=amount*frameStep*(D_L08_001BD800.frame-480);
                alpha=func_002A77E0(255)&255;
                func_002C3150(w,matrix,0x40804080,duration,alpha,0,scale);
                duration+=lifeStep;
            }
        }
    }
    func_00282F20(direction,forward,0.1f);
    {
        int j, alpha, colour, full, value;
        float size;
        j=0;
        full=255;
        for (;j<=0;++j) {
            size=func_00283CE0(full-((D_L08_001B2508+j*20)&255));
            size=func_00282C48(0.5f-size*0.003921569f);
            colour=func_00283D38(0x40FF40FF,0x10FF40FF,size);
            alpha=(unsigned char)D_L08_001B2508;
            if(j&2) alpha<<=1;
            if(j&1) alpha=full-alpha;
            value=alpha&255;
            size=(func_00283CE0(j)+5.0f)*0.008333334f;
            size*=(D_L08_001BD800.frame-480);
            func_002C2FD8(forward,colour,value,53,1,2,0,size);
            func_00282CC0(forward,forward,direction);
        }
    }
}
