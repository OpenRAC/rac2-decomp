/*
 * func_PAL_L08_0030A2B8, the PAL copy of func_L08_00308888: the same C at 50 Hz, with a
 * test of D_001A79F0 added to the first loop's last call.
 * Scripted level effects, one phase per D_L08_001BD800.phase.
 * Built with -G64 and gcse left on: the per-phase lui of the scene is reload
 * rematerializing PRE's spilled reaching register for %hi(D_L08_001BD800).
 * The unit adds -fcall-used-hi1 -fcall-used-lo1 -fcall-used-accum1 (the per-unit opt-out of
 * patch 0055): they restore loop.c's hoisting threshold from 61 to 64. Retail hoists the 0xFA0
 * compare in the first loop and the 20 of j*20 in the colour loop, which needs a threshold of
 * 63 to 65 (measured from this unit's -dL dump).
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
extern int g_current_map_index MACRO_ADDR;
extern int D_L08_001A9420 __attribute__((sda));
extern int D_L08_001B2508 MACRO_ADDR;
extern float D_L08_001B2820[4] MACRO_ADDR;
extern float D_L08_001A9490 __attribute__((sda));
extern float D_L08_001A9494, D_L08_001A9498, D_L08_001A949C;
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(void *);
extern void math_store_angle_update_result(void *, void *, int, int, float);
extern void moby_copy_group_word_to_members(void);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern void matrix_mul_vec3(void *, void *, void *);
extern void euler_rotation_basis(void *, void *);
extern float FastAddRotations(float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern float math_fabs(float);
extern int FastTweenColor(int, int, float);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern float math_random_signed_float_range(float, float);
extern void vec_random_direction(void *, float, float);
extern void vec_add_random_offset(void *, float);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern TaboraParticle *func_PAL_002BE9A8(void *, float, float, float, int, void *, int, float, int);
extern void func_PAL_L00_00328480(int, void *, int, int, void *, int, int, float, float, float, float);
extern char *part_spawn_fading_drift(void *, void *, int, int, int, int, int, int, float, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, int, int, int, float);
extern unsigned char *part_spawn_fading(void *, int, int, int, int, int, int, float);

void func_PAL_L08_0030A2B8(void) {
    float v[4] __attribute__((aligned(16)));
    float w[4] __attribute__((aligned(16)));
    /* Adjacent in the frame: func_002833F0 fills all three as rows of one matrix. */
    float matrix[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float forward[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float end[4] __attribute__((aligned(16)));
    anim_start_startup_animations();
    {
        int j = 0;
        TaboraObject *p;
        for (; j < D_L08_001BD800.count; ++j) {
            p = D_L08_001BD800.objects[j];
            if (p && p->classId==0xE29) p->flags |= 0x800;
            if (p->classId==0xD54) func_PAL_002E7270(p);
            if (p && p->classId==0xFA0 && g_current_map_index!=0x33 && p->vars)
                math_store_angle_update_result(p,p->vars+12,0x80AAAAD2,0x80396464,0.07330384f);
        }
    }
    if (g_current_map_index != 8) return;
    {
        if (D_L08_001BD800.phase==0) {
            int j;
            moby_copy_group_word_to_members();
            for (j=0;j<4;++j) {
                TaboraEffectEntry *entry=&D_L08_00288D10[j];
                if (D_L08_001BD800.frame==(((int)(entry->frame) * 5 + 2) / 6)) {
                    *(u128 *)v=*(u128 *)entry->position;
                    FastVecAdd(v,v,D_L08_001A9430);
                    func_PAL_L00_003FB330(v,0,25,20,20,20,45,1,1,1,0,0,entry->radius,20.0f);
                    if (entry->shake>0.0f) {
                        D_L08_001B99C0.duration0=46;
                        D_L08_001B99C0.duration2=58;
                        D_L08_001B99C0.delay=0;
                        D_L08_001B99C0.amount2=D_L08_001B99C0.amount0=entry->shake*0.08f;
                    }
                }
            }
        }
    }
    {
        if (D_L08_001BD800.phase==1) moby_copy_group_word_to_members();
        if (D_L08_001BD800.phase==2) {
            TaboraObject *p;
            int n;
            int i;
            int colour, life, alpha, spin, packed;
            TaboraParticle *r;
            float scale, size, angle, frameStep;
            p=0;
            moby_copy_group_word_to_members();
            n=0;
            scale=1.0f;
            if (D_L08_001BD800.frame==44) {p=D_L08_001BD800.objects[1];scale=0.7f;n=30;}
            else if (D_L08_001BD800.frame==48) {p=D_L08_001BD800.objects[0];n=50;}
            if (p) {
                *(u128 *)v = 0;
                v[2]=0.01f;
                v[3]=1.0f;
                frameStep=0.010000001f;
                for (i=0;i<n;++i) {
                    life=math_random_int_range(75,97);
                    qzero(w);
                    vec_add_random_offset(w,scale*0.7f);
                    w[2]*=0.3f;
                    FastVecAdd(w,w,p->position);
                    alpha=math_random_int_range(64,112);
                    colour=math_random_int_range(64,127);
                    packed=(alpha<<24)|(FloatToInt((float)colour*0.3f)<<16);
                    packed|=colour<<8;
                    colour|=packed;
                    angle=math_random_float_range(1.0f,1.013f);
                    spin=math_random_int_range(-2,2);
                    size=math_random_float_range(0.1f,0.3f);
                    v[0]=math_random_signed_float_range(0.0f,0.014f);
                    v[1]=math_random_signed_float_range(0.0f,0.014f);
                    v[2]=math_random_float_range(frameStep*0.1f,0.010000001f);
                    FastVecScale(v,v,scale);
                    r=func_PAL_002BE9A8(w,0.1f,1.0f,angle,spin,v,colour,size*210000.0f,0);
                    if (r) {
                        TaboraParticleData *particleData=&r->data;
                        if (math_random_int_below(2)) r->kind=0x44;
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
    if (D_L08_001BD800.phase==3 && D_L08_001BD800.frame==(((int)(D_L08_001A9420) * 5 + 2) / 6)) {
        TaboraObject *first=D_L08_001BD800.objects[1];
        TaboraObject *second=D_L08_001BD800.objects[2];
        qcopy(v,second->position);
        v[2]+=0.8f;
        FastVecSub(w,first->position,second->position);
        vec_scale_to_length(w,w,0.042f);
        w[2]=0.050000004f;
        func_PAL_L00_00328480(0,v,40,0,w,0x39969696,0,0.75f,1.3f,0.2f,0.37f);
        D_L08_001B99C0.amount2=0.047f;
        D_L08_001B99C0.duration2=29;
        D_L08_001B99C0.amount0=0.037f;
        D_L08_001B99C0.duration0=25;
        D_L08_001B99C0.amount1=0.04f;
        D_L08_001B99C0.duration1=17;
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
    if ((unsigned)(D_L08_001BD800.frame-351)>=147) return;
    *(u128 *)v=*(u128 *)D_L08_001BD800.objects[3]->position;
    v[2]+=0.5f;
    if (D_L08_001BD800.frame<473) {
        int j;
        int spin;
        float size;
        D_L08_001B2820[0]=FastAddRotations(D_L08_001B2820[0],D_L08_001A9490*0.0003490659f);
        D_L08_001B2820[1]=FastAddRotations(D_L08_001B2820[1],D_L08_001A9494*0.0003490659f);
        D_L08_001B2820[2]=FastAddRotations(D_L08_001B2820[2],D_L08_001A9498*0.0003490659f);
        D_L08_001B2820[3]=FastAddRotations(D_L08_001B2820[3],D_L08_001A949C*0.0003490659f);
        euler_rotation_basis(matrix,D_L08_001B2820);
        for(j=0;j<4;++j) {
            FastVecSub(start,D_L08_001B9B00,v);
            vec_scale_to_length(start,start,5.0f);
            FastVecAdd(end,start,v);
            end[2]+=0.5f;
            spin=FloatToInt(math_random_signed_float_range(2.0f,5.0f));
            matrix_mul_vec3(direction,D_L08_001A9450[j],matrix);
            vec_scale_to_length(direction,direction,3.5f);
            FastVecAdd(direction,direction,end);
            FastVecSub(w,end,direction);
            vec_scale_to_length(w,w,0.07000001f);
            size=math_random_float_range(0.2f,0.32f);
            part_spawn_fading_drift(direction,w,50,0x804080,spin,0,63,6,size*210000.0f,147000.0f,0.0f);
        }
    }
    if (D_L08_001BD800.frame<=400) return;
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
        if (math_random_int_below(4)==0) {
            FastVecSub(forward,D_L08_001B9B00,w);
            timeScale=0.020000001f;
            frameStep=0.010000001f;
            vec_scale_to_length(forward,forward,5.0f);
            FastVecAdd(w,forward,w);
            vec_random_direction(matrix,rate,rate);
            size=(D_L08_001BD800.frame-480);
            size*=0.080000006f;
            alpha=math_random_int_below(255)&255;
            duration=60;
            lifeStep=0;
            part_spawn_hero_relative(w,matrix,0x50804080,duration,alpha,0,size);
            for (j=0;j<1;++j) {
                t=rate*timeScale;
                vec_random_direction(offset,t,t);
                FastVecAdd(matrix,matrix,offset);
                t=0.0f; /* Second set in the loop: keeps rate*timeScale from being hoisted and folded. */
                scale=amount*frameStep*(D_L08_001BD800.frame-480);
                alpha=math_random_int_below(255)&255;
                part_spawn_hero_relative(w,matrix,0x40804080,duration,alpha,0,scale);
                duration+=lifeStep;
            }
        }
    }
    vec_scale_to_length(direction,forward,0.1f);
    {
        int j, alpha, colour, value;
        float size;
        j=0;
        for (;j<=0;++j) {
            size=IntToFloat(212-((((D_L08_001B2508+j*20)&255) * 5 + 2) / 6));
            size=math_fabs(0.5f-size*0.004716981f);
            colour=FastTweenColor(0x40FF40FF,0x10FF40FF,size);
            alpha=(unsigned char)D_L08_001B2508;
            if(j&2) alpha<<=1;
            if(j&1) alpha=255-alpha;
            value=alpha&255;
            size=(IntToFloat(j)+5.0f)*0.010000001f;
            size*=(D_L08_001BD800.frame-480);
            part_spawn_fading(forward,colour,value,53,1,2,0,size);
            FastVecAdd(forward,forward,direction);
        }
    }
}
