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
void func_PAL_L14_003E0C90(GateObject *m)
{
    GateContext *d=m->context;
    int i;
    float v[4] __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float vb[4] __attribute__((aligned(16)));
    float vc[4] __attribute__((aligned(16)));
    if(m->state==0) {
        if(D_L00_001FA920[d->group] && moby_count_group_not_in_state(d->group,-1)>=2) {
            GateObject *base=D_L00_001B1E9C;
            short *p=D_L00_001FA920[d->group];
            do {
                GateObject *o=base+(*p&0x7fff);
                o->flags|=0x43;
                o->collision=0;
            } while(*p++>=0);
        }
        if(vec_distance_xy(m->position,g_hero_position)<6.0f &&
           !IsPointInCuboid(g_hero_position,d->close_volume) &&
           !IsPointInCuboid(g_hero_position,d->block_volume)) {
            m->state=1; m->render_flags=0x24c102;
            if(m->animation!=1) anim_start_blended(m,1,0,0);
            m->collision=0;
            if(D_L00_001FA920[d->group] && moby_count_group_not_in_state(d->group,-1)>=2) {
                GateObject *base=D_L00_001B1E9C;
                short *p=D_L00_001FA920[d->group];
                do {
                    GateObject *o=base+(*p&0x7fff);
                    o->flags&=0xffbc;
                    o->collision=o->object_class->collision;
                } while(*p++>=0);
            }
        } else if(IsPointInCuboid(g_hero_position,d->close_volume)) m->state=5;
        for(i=0;i<4;i++) {
            if(d->child[i]!=-1) {
                GateObject *o=D_L00_001B1E9C+d->child[i];
                if(o->destroyed || (s8)o->state<0) {
                    if(d->destroy_on_child) {
                        {
    m->state=12;
    qcopy(v,m->position);v[2]+=1.0f;
    PlayMobySound(2,0,m);
    a[0]=math_fast_sin_or_cos_a(m->angle-1.5707964897155762f)*0.36f;
    a[1]=math_fast_sin_or_cos_b(m->angle-1.5707964897155762f)*0.36f;a[2]=0;
    SpawnExplosionEffects(m,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(m,255,a,3,6,3,6,255);

    moby_mark_spawned(m);return;
}
                    }
                    m->state=1;
                    if(m->animation!=1)anim_start_blended(m,1,0,0);
                    m->collision=0;
                }
            }
        }
    }
    if(m->state==1 && (m->anim_flags&2)) {
        m->state=3;m->render_flags=0x224c1;
        if(m->animation!=2)anim_start_blended(m,2,0,0);
    }
    if(m->state==2) {
        v[0]=math_fast_sin_or_cos_a(m->angle-1.5707964897155762f)*0.36f;
        v[1]=math_fast_sin_or_cos_b(m->angle-1.5707964897155762f)*0.36f;v[2]=0;
        FastVecAdd(m->position,m->position,v);
        qcopy(a,m->position);qcopy(b,m->position);qcopy(c,m->position);
        a[2]+=0.75f;b[2]+=0.75f;c[2]+=0.75f;
        v[0]=math_fast_sin_or_cos_a(m->angle)*0.8f;
        v[1]=math_fast_sin_or_cos_b(m->angle)*0.8f;v[2]=0;
        v[0]=math_fast_sin_or_cos_a(m->angle+3.1415929794311523f)*0.8f;
        v[1]=math_fast_sin_or_cos_b(m->angle+3.1415929794311523f)*0.8f;v[2]=0;
        FastVecAdd(b,b,vb);FastVecAdd(c,c,vc);
        if(coll_test_point(a,0.6f,0,m) || coll_test_point(b,0.68f,0,m) || coll_test_point(c,0.68f,0,m)) {
            PlayMobySound(2,0,m);
            SpawnExplosionEffects(m,D_L00_001A8F20,a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            {
    moby_mark_spawned(m);return;
}
        }
    }
    goto closing;
    m->state=12;
    qcopy(v,m->position);v[2]+=1.0f;
    PlayMobySound(2,0,m);
    a[0]=math_fast_sin_or_cos_a(m->angle-1.5707964897155762f)*0.36f;
    a[1]=math_fast_sin_or_cos_b(m->angle-1.5707964897155762f)*0.36f;a[2]=0;
    SpawnExplosionEffects(m,D_L00_001A8F20,v,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(m,255,a,3,6,3,6,255);
    moby_mark_spawned(m);return;
closing:
    if(m->state==3 && IsPointInCuboid(g_hero_position,d->close_volume)) {
        m->state=4;
        if(m->animation!=3)anim_start_blended(m,3,0,0);
    }
    if(m->state==4 && (m->anim_flags&2)) {
        m->state=5;m->collision=m->object_class->collision;
        if(m->animation!=0)anim_start_blended(m,0,0,0);
    }
}
