#include "include_asm.h"

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
void func_PAL_L04_004746D0(unsigned char *obj)
{
    float pos[4], scale[4], delta[4], extent[4];
    AmbientState *s = *(AmbientState **)(obj+8);
    float outer, distance, time, edge;
    int volume, flags;
    unsigned char *slot;
    scale[2] = scale[1] = scale[0] = *(float *)(obj+12);
    func_00282CF0(pos,D_L04_001B9680,obj+0x40);
    pos[3] = 0;
    func_00283098(delta,pos,obj+0x50);
    func_00283098(extent,scale,obj+0x50);
    outer = func_00282DF0(extent);
    distance = func_00282DF0(delta);
    if (distance < outer) {
        flags = 16;
        if (func_00282C48(delta[0]) <= 1.0f && func_00282C48(delta[1]) <= 1.0f && func_00282C48(delta[2]) <= 1.0f) {
            volume = *(int *)(D_L04_001B202C+s->sound*32+12);
        } else {
            if(delta[0]>1.0f) delta[0]=1.0f; else if(delta[0]<-1.0f) delta[0]=-1.0f;
            if(delta[1]>1.0f) delta[1]=1.0f; else if(delta[1]<-1.0f) delta[1]=-1.0f;
            if(delta[2]>1.0f) delta[2]=1.0f; else if(delta[2]<-1.0f) delta[2]=-1.0f;
            edge=func_00282DF0(delta);
            volume=func_002E45C8(D_L04_001B202C+s->sound*32,distance,edge,outer);
        }
        if(s->target!=-1) {
            unsigned char *target=D_L04_001B24DC+s->target*256;
            if(*(short *)(target+0xAA)==3004) {
                unsigned char *vars=*(unsigned char **)(target+0x68);
                int cap;
                time=*(float *)(vars+0x30C)+*(float *)(vars+0x27C);
                if(s->end*(0.020000001f)<time) time=s->end*(0.020000001f);
                time-=s->start*(0.020000001f);
                if(time<0) time=0;
                cap=func_00283CF0(func_00283CE0(1024)*(time/((s->end-s->start)*(0.020000001f))));
                if(cap<volume) volume=cap;
            }
        }
        slot=D_00188660+s->handle*0x70;
        if(D_L04_001B202C[s->sound*32+24]) flags=20;
        if(*(unsigned char **)(slot+0x8C)!=obj || !slot[0x74]) {
            if(func_00282948(&s->timer)) {
                s->handle=func_L00_0035F640(s->sound,flags,obj,volume);
                if(s->maxTime>0) s->timer=(s->minTime+func_002A77E0(s->maxTime-s->minTime))*5e+01f;
            } else s->handle=-1;
        }
        if(s->handle!=-1) {
            func_L01_00355BA0(s->handle,volume);
            func_00283098(pos,delta,obj+0x10);
            func_00282CC0(pos,pos,obj+0x40);
            qcopy(D_00188660+s->handle*0x70+0x90,pos);
        }
    } else {
        if(s->handle!=-1) {
            unsigned char *oldSlot=D_00188660+s->handle*0x70;
            if(*(unsigned char **)(oldSlot+0x8C)==obj && oldSlot[0x74]) func_002E59F8(s->handle);
        }
        s->handle=-1;
    }
}

