#include "common.h"
typedef struct { char pad[0x10]; int collision; } GateClass;
typedef struct { int child[4]; int destroy_on_child; int close_volume; int block_volume; int group; } GateContext;
typedef struct {
    char pad00[0x10]; float position[4]; u8 state;
    char pad21[3]; GateClass *object_class; char pad28[0xC]; u16 flags;
    char pad36[0xD]; u8 animation; char pad44[0x1C]; u8 anim_flags;
    char pad61[7]; GateContext *context; char pad6c[0xC]; int render_flags;
    char pad7c[0x19]; u8 destroyed; char pad96[2]; int collision;
    char pad9c[0x5C]; float angle; char padfc[4];
} GateObject;
extern short *D_L00_001FA920[];
extern GateObject *D_L00_001B1E9C;
extern char D_00189EA0[];
extern char D_L00_001A8F20[] MACRO_ADDR;
extern int func_002A8508(int,int);
extern float func_00282E80(void *,void *);
extern int func_002ACBC8(void *,int);
extern void func_002A7470(void *,int,int,int);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00277258(void *,float,int,void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern void func_0029F338(void *);
/* Updates a gate: opens when the player is near, closes again, and breaks if a linked object is destroyed. */
void func_L00_003CED50(GateObject *gate)
{
    GateContext *context=gate->context;
    int i;
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    if(gate->state==0) {
        if(D_L00_001FA920[context->group] && CountMobysInGroupNotInState(context->group,-1)>=2) {
            GateObject *base=D_L00_001B1E9C;
            short *p=D_L00_001FA920[context->group];
            do {
                GateObject *o=base+(*p&0x7fff);
                o->flags|=0x43;
                o->collision=0;
            } while(*p++>=0);
        }
        if(vec_distance_xy(gate->position,gHeroPosition)<6.0f &&
           !IsPointInCuboid(gHeroPosition,context->close_volume) &&
           !IsPointInCuboid(gHeroPosition,context->block_volume)) {
            gate->state=1; gate->render_flags=0x24c102;
            if(gate->animation!=1) StartAnimationBlended(gate,1,0,0);
            gate->collision=0;
            if(D_L00_001FA920[context->group] && CountMobysInGroupNotInState(context->group,-1)>=2) {
                GateObject *base=D_L00_001B1E9C;
                short *p=D_L00_001FA920[context->group];
                do {
                    GateObject *o=base+(*p&0x7fff);
                    o->flags&=0xffbc;
                    o->collision=o->object_class->collision;
                } while(*p++>=0);
            }
        } else if(IsPointInCuboid(gHeroPosition,context->close_volume)) gate->state=5;
        for(i=0;i<4;i++) {
            if(context->child[i]!=-1) {
                GateObject *o=D_L00_001B1E9C+context->child[i];
                if(o->destroyed || (s8)o->state<0) {
                    if(context->destroy_on_child) {
                        {
    gate->state=12;
    qcopy(v,gate->position);v[2]+=1.0f;
    PlayMobySound(2,0,gate);
    a[0]=FastSinOrCosA(gate->angle-1.5707964897155762f)*0.3f;
    a[1]=FastSinOrCosB(gate->angle-1.5707964897155762f)*0.3f;a[2]=0;
    SpawnExplosionEffects(gate,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    SpawnDebrisForMaskedParts(gate,255,a,3,6,3,6,255);

    MarkMobySpawned(gate);return;
}
                    }
                    gate->state=1;
                    if(gate->animation!=1)StartAnimationBlended(gate,1,0,0);
                    gate->collision=0;
                }
            }
        }
    }
    if(gate->state==1 && (gate->anim_flags&2)) {
        gate->state=3;gate->render_flags=0x224c1;
        if(gate->animation!=2)StartAnimationBlended(gate,2,0,0);
    }
    if(gate->state==2) {
        v[0]=FastSinOrCosA(gate->angle-1.5707964897155762f)*0.3f;
        v[1]=FastSinOrCosB(gate->angle-1.5707964897155762f)*0.3f;v[2]=0;
        FastVecAdd(gate->position,gate->position,v);
        qcopy(a,gate->position);qcopy(b,gate->position);qcopy(c,gate->position);
        a[2]+=0.75f;b[2]+=0.75f;c[2]+=0.75f;
        v[0]=FastSinOrCosA(gate->angle)*0.8f;
        v[1]=FastSinOrCosB(gate->angle)*0.8f;v[2]=0;
        v[0]=FastSinOrCosA(gate->angle+3.1415929794311523f)*0.8f;
        v[1]=FastSinOrCosB(gate->angle+3.1415929794311523f)*0.8f;v[2]=0;
        FastVecAdd(b,b,vb);FastVecAdd(c,c,vc);
        if(TestPointAgainstCollision(a,0.6f,0,gate) || TestPointAgainstCollision(b,0.68f,0,gate) || TestPointAgainstCollision(c,0.68f,0,gate)) {
            PlayMobySound(2,0,gate);
            SpawnExplosionEffects(gate,D_L00_001A8F20,a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            {
    MarkMobySpawned(gate);return;
}
        }
    }
    goto closing;
    gate->state=12;
    qcopy(v,gate->position);v[2]+=1.0f;
    PlayMobySound(2,0,gate);
    a[0]=FastSinOrCosA(gate->angle-1.5707964897155762f)*0.3f;
    a[1]=FastSinOrCosB(gate->angle-1.5707964897155762f)*0.3f;a[2]=0;
    SpawnExplosionEffects(gate,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    SpawnDebrisForMaskedParts(gate,255,a,3,6,3,6,255);
    MarkMobySpawned(gate);return;
closing:
    if(gate->state==3 && IsPointInCuboid(gHeroPosition,context->close_volume)) {
        gate->state=4;
        if(gate->animation!=3)StartAnimationBlended(gate,3,0,0);
    }
    if(gate->state==4 && (gate->anim_flags&2)) {
        gate->state=5;gate->collision=gate->object_class->collision;
        if(gate->animation!=0)StartAnimationBlended(gate,0,0,0);
    }
}
