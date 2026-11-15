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
extern char g_hero_position[];
extern char D_L00_001A8F20[] MACRO_ADDR;
extern int moby_count_group_not_in_state(int,int);
extern float vec_distance_xy(void *,void *);
extern int IsPointInCuboid(void *,int);
extern void anim_start_blended(void *,int,int,int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,float,int,void *);
extern int PlayMobySound(int,int,void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,int);
extern void moby_mark_spawned(void *);
/* Updates a gate: opens when the player is near, closes again, and breaks if a linked object is destroyed. */
void gate_l00_update(GateObject *gate)
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
        if(D_L00_001FA920[context->group] && moby_count_group_not_in_state(context->group,-1)>=2) {
            GateObject *base=D_L00_001B1E9C;
            short *p=D_L00_001FA920[context->group];
            do {
                GateObject *o=base+(*p&0x7fff);
                o->flags|=0x43;
                o->collision=0;
            } while(*p++>=0);
        }
        if(vec_distance_xy(gate->position,g_hero_position)<6.0f &&
           !IsPointInCuboid(g_hero_position,context->close_volume) &&
           !IsPointInCuboid(g_hero_position,context->block_volume)) {
            gate->state=1; gate->render_flags=0x24c102;
            if(gate->animation!=1) anim_start_blended(gate,1,0,0);
            gate->collision=0;
            if(D_L00_001FA920[context->group] && moby_count_group_not_in_state(context->group,-1)>=2) {
                GateObject *base=D_L00_001B1E9C;
                short *p=D_L00_001FA920[context->group];
                do {
                    GateObject *o=base+(*p&0x7fff);
                    o->flags&=0xffbc;
                    o->collision=o->object_class->collision;
                } while(*p++>=0);
            }
        } else if(IsPointInCuboid(g_hero_position,context->close_volume)) gate->state=5;
        for(i=0;i<4;i++) {
            if(context->child[i]!=-1) {
                GateObject *o=D_L00_001B1E9C+context->child[i];
                if(o->destroyed || (s8)o->state<0) {
                    if(context->destroy_on_child) {
                        {
    gate->state=12;
    qcopy(v,gate->position);v[2]+=1.0f;
    PlayMobySound(2,0,gate);
    a[0]=math_fast_sin_or_cos_a(gate->angle-1.5707964897155762f)*0.3f;
    a[1]=math_fast_sin_or_cos_b(gate->angle-1.5707964897155762f)*0.3f;a[2]=0;
    SpawnExplosionEffects(gate,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(gate,255,a,3,6,3,6,255);

    moby_mark_spawned(gate);return;
}
                    }
                    gate->state=1;
                    if(gate->animation!=1)anim_start_blended(gate,1,0,0);
                    gate->collision=0;
                }
            }
        }
    }
    if(gate->state==1 && (gate->anim_flags&2)) {
        gate->state=3;gate->render_flags=0x224c1;
        if(gate->animation!=2)anim_start_blended(gate,2,0,0);
    }
    if(gate->state==2) {
        v[0]=math_fast_sin_or_cos_a(gate->angle-1.5707964897155762f)*0.3f;
        v[1]=math_fast_sin_or_cos_b(gate->angle-1.5707964897155762f)*0.3f;v[2]=0;
        FastVecAdd(gate->position,gate->position,v);
        qcopy(a,gate->position);qcopy(b,gate->position);qcopy(c,gate->position);
        a[2]+=0.75f;b[2]+=0.75f;c[2]+=0.75f;
        v[0]=math_fast_sin_or_cos_a(gate->angle)*0.8f;
        v[1]=math_fast_sin_or_cos_b(gate->angle)*0.8f;v[2]=0;
        v[0]=math_fast_sin_or_cos_a(gate->angle+3.1415929794311523f)*0.8f;
        v[1]=math_fast_sin_or_cos_b(gate->angle+3.1415929794311523f)*0.8f;v[2]=0;
        FastVecAdd(b,b,vb);FastVecAdd(c,c,vc);
        if(coll_test_point(a,0.6f,0,gate) || coll_test_point(b,0.68f,0,gate) || coll_test_point(c,0.68f,0,gate)) {
            PlayMobySound(2,0,gate);
            SpawnExplosionEffects(gate,D_L00_001A8F20,a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            {
    moby_mark_spawned(gate);return;
}
        }
    }
    goto closing;
    gate->state=12;
    qcopy(v,gate->position);v[2]+=1.0f;
    PlayMobySound(2,0,gate);
    a[0]=math_fast_sin_or_cos_a(gate->angle-1.5707964897155762f)*0.3f;
    a[1]=math_fast_sin_or_cos_b(gate->angle-1.5707964897155762f)*0.3f;a[2]=0;
    SpawnExplosionEffects(gate,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(gate,255,a,3,6,3,6,255);
    moby_mark_spawned(gate);return;
closing:
    if(gate->state==3 && IsPointInCuboid(g_hero_position,context->close_volume)) {
        gate->state=4;
        if(gate->animation!=3)anim_start_blended(gate,3,0,0);
    }
    if(gate->state==4 && (gate->anim_flags&2)) {
        gate->state=5;gate->collision=gate->object_class->collision;
        if(gate->animation!=0)anim_start_blended(gate,0,0,0);
    }
}
