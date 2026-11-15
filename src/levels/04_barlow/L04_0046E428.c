#include "common.h"
extern float D_L04_001B9680[4];
extern unsigned char *D_L04_001B202C __attribute__((sda));
extern unsigned char *D_L04_001B24DC __attribute__((sda));
extern unsigned char D_00188660[];
extern void func_00282CF0(float *, float *, void *);
extern void func_00283098(float *, float *, void *);
extern float func_00282DF0(float *);
extern float func_00282C48(float);
extern int func_002E45C8(void *, float, float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00282948(int *);
extern int func_L00_0035F640(int,int,void *,int);
extern int func_002A77E0(int);
extern void func_L01_00355BA0(int,int);
extern void func_00282CC0(float *,float *,void *);
extern void func_002E59F8(int);
typedef struct { int sound, minTime, maxTime, timer, handle, target; float start, end; } AmbientState;
/* Updates an ambient sound inside a transformed volume, including its voice position. */
void func_L04_0046E428(unsigned char *obj)
{
    float pos[4], scale[4], delta[4], extent[4];
    AmbientState *ambient = *(AmbientState **)(obj+8);
    float outer, distance, time, edge;
    int volume, flags;
    unsigned char *slot;
    scale[2] = scale[1] = scale[0] = *(float *)(obj+12);
    FastVecSub(pos,D_L04_001B9680,obj+0x40);
    pos[3] = 0;
    matrix_mul_vec3(delta,pos,obj+0x50);
    matrix_mul_vec3(extent,scale,obj+0x50);
    outer = FastVecLength(extent);
    distance = FastVecLength(delta);
    if (distance < outer) {
        flags = 16;
        if (FloatAbs(delta[0]) <= 1.0f && FloatAbs(delta[1]) <= 1.0f && FloatAbs(delta[2]) <= 1.0f) {
            volume = *(int *)(D_L04_001B202C+ambient->sound*32+12);
        } else {
            if(delta[0]>1.0f) delta[0]=1.0f; else if(delta[0]<-1.0f) delta[0]=-1.0f;
            if(delta[1]>1.0f) delta[1]=1.0f; else if(delta[1]<-1.0f) delta[1]=-1.0f;
            if(delta[2]>1.0f) delta[2]=1.0f; else if(delta[2]<-1.0f) delta[2]=-1.0f;
            edge=FastVecLength(delta);
            volume=ComputeSoundFalloff(D_L04_001B202C+ambient->sound*32,distance,edge,outer);
        }
        if(ambient->target!=-1) {
            unsigned char *target=gMobyPool_L04+ambient->target*256;
            if(*(short *)(target+0xAA)==3004 /* moby class 3004 */) {
                unsigned char *vars=*(unsigned char **)(target+0x68);
                int cap;
                time=*(float *)(vars+0x30C)+*(float *)(vars+0x27C);
                if(ambient->end*(1.0f/60.0f)<time) time=ambient->end*(1.0f/60.0f);
                time-=ambient->start*(1.0f/60.0f);
                if(time<0) time=0;
                cap=FloatToInt(IntToFloat(1024)*(time/((ambient->end-ambient->start)*(1.0f/60.0f))));
                if(cap<volume) volume=cap;
            }
        }
        slot=gSoundState+ambient->handle*0x70;
        if(D_L04_001B202C[ambient->sound*32+24]) flags=20;
        if(*(unsigned char **)(slot+0x8C)!=obj || !slot[0x74]) {
            if(FastFloatHelperD(&ambient->timer)) {
                ambient->handle=StartEffectFromTableEntry(ambient->sound,flags,obj,volume);
                if(ambient->maxTime>0) ambient->timer=(ambient->minTime+RandomIntBelow(ambient->maxTime-ambient->minTime))*60.0f;
            } else ambient->handle=-1;
        }
        if(ambient->handle!=-1) {
            SetSoundSlotField(ambient->handle,volume);
            matrix_mul_vec3(pos,delta,obj+0x10);
            FastVecAdd(pos,pos,obj+0x40);
            qcopy(gSoundState+ambient->handle*0x70+0x90,pos);
        }
    } else {
        if(ambient->handle!=-1) {
            unsigned char *oldSlot=gSoundState+ambient->handle*0x70;
            if(*(unsigned char **)(oldSlot+0x8C)==obj && oldSlot[0x74]) StopSoundVoice(ambient->handle);
        }
        ambient->handle=-1;
    }
}
