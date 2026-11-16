#include "include_asm.h"

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
extern short *g_turn_state_table[];
extern GateObject *g_moby_array_base;
extern char g_hero_position[];
extern char g_default_vector[] MACRO_ADDR;
extern int moby_count_group_not_in_state(int,int);
extern float vec_distance_xy(void *,void *);
extern int IsPointInCuboid(void *,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,float,int,void *);
extern int PlayMobySound(int,int,void *);
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_spawn_masked_debris_pal(void *,int,void *,float,float,float,float,int);
extern void moby_mark_spawned(void *);

/* Updates a gate: opens when the player is near, closes again, and breaks if a linked object is destroyed (PAL copy). */
void aranos_gate_update_pal(GateObject *moby)
{
    GateContext *ctx=moby->context;
    int i;
    float temp[4] __attribute__((aligned(16)));
    float point_a[4] __attribute__((aligned(16)));
    float point_b[4] __attribute__((aligned(16)));
    float point_c[4] __attribute__((aligned(16)));
    float step_b[4] __attribute__((aligned(16)));
    float step_c[4] __attribute__((aligned(16)));
    if(moby->state==0) {
        if(g_turn_state_table[ctx->group] && moby_count_group_not_in_state(ctx->group,-1)>=2) {
            GateObject *base=g_moby_array_base;
            short *ids=g_turn_state_table[ctx->group];
            do {
                GateObject *other=base+(*ids&0x7fff);
                other->flags|=0x43;
                other->collision=0;
            } while(*ids++>=0);
        }
        if(vec_distance_xy(moby->position,g_hero_position)<6.0f &&
           !IsPointInCuboid(g_hero_position,ctx->close_volume) &&
           !IsPointInCuboid(g_hero_position,ctx->block_volume)) {
            moby->state=1; moby->render_flags=0x24c102;
            if(moby->animation!=1) anim_start_blended_pal(moby,1,0,0);
            moby->collision=0;
            if(g_turn_state_table[ctx->group] && moby_count_group_not_in_state(ctx->group,-1)>=2) {
                GateObject *base=g_moby_array_base;
                short *ids=g_turn_state_table[ctx->group];
                do {
                    GateObject *other=base+(*ids&0x7fff);
                    other->flags&=0xffbc;
                    other->collision=other->object_class->collision;
                } while(*ids++>=0);
            }
        } else if(IsPointInCuboid(g_hero_position,ctx->close_volume)) moby->state=5;
        for(i=0;i<4;i++) {
            if(ctx->child[i]!=-1) {
                GateObject *other=g_moby_array_base+ctx->child[i];
                if(other->destroyed || (s8)other->state<0) {
                    if(ctx->destroy_on_child) {
                        {
    moby->state=12;
    qcopy(temp,moby->position);temp[2]+=1.0f;
    PlayMobySound(2,0,moby);
    point_a[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
    point_a[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;point_a[2]=0;
    SpawnExplosionEffects_pal(moby,g_default_vector,temp,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris_pal(moby,255,point_a,3,6,3,6,255);

    moby_mark_spawned(moby);return;
}
                    }
                    moby->state=1;
                    if(moby->animation!=1)anim_start_blended_pal(moby,1,0,0);
                    moby->collision=0;
                }
            }
        }
    }
    if(moby->state==1 && (moby->anim_flags&2)) {
        moby->state=3;moby->render_flags=0x224c1;
        if(moby->animation!=2)anim_start_blended_pal(moby,2,0,0);
    }
    if(moby->state==2) {
        temp[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
        temp[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;temp[2]=0;
        FastVecAdd(moby->position,moby->position,temp);
        qcopy(point_a,moby->position);qcopy(point_b,moby->position);qcopy(point_c,moby->position);
        point_a[2]+=0.75f;point_b[2]+=0.75f;point_c[2]+=0.75f;
        temp[0]=math_fast_sin_or_cos_a(moby->angle)*0.8f;
        temp[1]=math_fast_sin_or_cos_b(moby->angle)*0.8f;temp[2]=0;
        temp[0]=math_fast_sin_or_cos_a(moby->angle+3.1415929794311523f)*0.8f;
        temp[1]=math_fast_sin_or_cos_b(moby->angle+3.1415929794311523f)*0.8f;temp[2]=0;
        FastVecAdd(point_b,point_b,step_b);FastVecAdd(point_c,point_c,step_c);
        if(coll_test_point(point_a,0.6f,0,moby) || coll_test_point(point_b,0.68f,0,moby) || coll_test_point(point_c,0.68f,0,moby)) {
            PlayMobySound(2,0,moby);
            SpawnExplosionEffects_pal(moby,g_default_vector,point_a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            {
    moby_mark_spawned(moby);return;
}
        }
    }
    goto closing;
    moby->state=12;
    qcopy(temp,moby->position);temp[2]+=1.0f;
    PlayMobySound(2,0,moby);
    point_a[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
    point_a[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;point_a[2]=0;
    SpawnExplosionEffects_pal(moby,g_default_vector,temp,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris_pal(moby,255,point_a,3,6,3,6,255);
    moby_mark_spawned(moby);return;
closing:
    if(moby->state==3 && IsPointInCuboid(g_hero_position,ctx->close_volume)) {
        moby->state=4;
        if(moby->animation!=3)anim_start_blended_pal(moby,3,0,0);
    }
    if(moby->state==4 && (moby->anim_flags&2)) {
        moby->state=5;moby->collision=moby->object_class->collision;
        if(moby->animation!=0)anim_start_blended_pal(moby,0,0,0);
    }
}
