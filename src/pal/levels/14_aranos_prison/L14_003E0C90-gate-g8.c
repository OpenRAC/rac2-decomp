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
extern void anim_start_blended(void *,int,int,int);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,float,int,void *);
extern int PlayMobySound(int,int,void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,int);
extern void moby_mark_spawned(void *);
/* Sliding gate: opens when the hero is near, slides and animates, and blows up when its linked child objects are destroyed or it hits something. */
void gate_l00_update_pal(GateObject *moby)
{
    GateContext *ctx=moby->context;
    int i;
    float offset[4] __attribute__((aligned(16)));
    float probe_a[4] __attribute__((aligned(16)));
    float probe_b[4] __attribute__((aligned(16)));
    float probe_c[4] __attribute__((aligned(16)));
    float step_b[4] __attribute__((aligned(16)));
    float step_c[4] __attribute__((aligned(16)));
    if(moby->state==0) {
        if(g_turn_state_table[ctx->group] && moby_count_group_not_in_state(ctx->group,-1)>=2) {
            GateObject *base=g_moby_array_base;
            short *list=g_turn_state_table[ctx->group];
            do {
                GateObject *member=base+(*list&0x7fff);
                member->flags|=0x43;
                member->collision=0;
            } while(*list++>=0);
        }
        if(vec_distance_xy(moby->position,g_hero_position)<6.0f &&
           !IsPointInCuboid(g_hero_position,ctx->close_volume) &&
           !IsPointInCuboid(g_hero_position,ctx->block_volume)) {
            moby->state=1; moby->render_flags=0x24c102;
            if(moby->animation!=1) anim_start_blended(moby,1,0,0);
            moby->collision=0;
            if(g_turn_state_table[ctx->group] && moby_count_group_not_in_state(ctx->group,-1)>=2) {
                GateObject *base=g_moby_array_base;
                short *list=g_turn_state_table[ctx->group];
                do {
                    GateObject *member=base+(*list&0x7fff);
                    member->flags&=0xffbc;
                    member->collision=member->object_class->collision;
                } while(*list++>=0);
            }
        } else if(IsPointInCuboid(g_hero_position,ctx->close_volume)) moby->state=5;
        for(i=0;i<4;i++) {
            if(ctx->child[i]!=-1) {
                GateObject *member=g_moby_array_base+ctx->child[i];
                if(member->destroyed || (s8)member->state<0) {
                    if(ctx->destroy_on_child) {
                        {
    moby->state=12;
    qcopy(offset,moby->position);offset[2]+=1.0f;
    PlayMobySound(2,0,moby);
    probe_a[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
    probe_a[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;probe_a[2]=0;
    SpawnExplosionEffects(moby,g_default_vector,offset,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(moby,255,probe_a,3,6,3,6,255);

    moby_mark_spawned(moby);return;
}
                    }
                    moby->state=1;
                    if(moby->animation!=1)anim_start_blended(moby,1,0,0);
                    moby->collision=0;
                }
            }
        }
    }
    if(moby->state==1 && (moby->anim_flags&2)) {
        moby->state=3;moby->render_flags=0x224c1;
        if(moby->animation!=2)anim_start_blended(moby,2,0,0);
    }
    if(moby->state==2) {
        offset[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
        offset[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;offset[2]=0;
        FastVecAdd(moby->position,moby->position,offset);
        qcopy(probe_a,moby->position);qcopy(probe_b,moby->position);qcopy(probe_c,moby->position);
        probe_a[2]+=0.75f;probe_b[2]+=0.75f;probe_c[2]+=0.75f;
        offset[0]=math_fast_sin_or_cos_a(moby->angle)*0.8f;
        offset[1]=math_fast_sin_or_cos_b(moby->angle)*0.8f;offset[2]=0;
        offset[0]=math_fast_sin_or_cos_a(moby->angle+3.1415929794311523f)*0.8f;
        offset[1]=math_fast_sin_or_cos_b(moby->angle+3.1415929794311523f)*0.8f;offset[2]=0;
        FastVecAdd(probe_b,probe_b,step_b);FastVecAdd(probe_c,probe_c,step_c);
        if(coll_test_point(probe_a,0.6f,0,moby) || coll_test_point(probe_b,0.68f,0,moby) || coll_test_point(probe_c,0.68f,0,moby)) {
            PlayMobySound(2,0,moby);
            SpawnExplosionEffects(moby,g_default_vector,probe_a,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
            {
    moby_mark_spawned(moby);return;
}
        }
    }
    goto closing;
    moby->state=12;
    qcopy(offset,moby->position);offset[2]+=1.0f;
    PlayMobySound(2,0,moby);
    probe_a[0]=math_fast_sin_or_cos_a(moby->angle-1.5707964897155762f)*0.36f;
    probe_a[1]=math_fast_sin_or_cos_b(moby->angle-1.5707964897155762f)*0.36f;probe_a[2]=0;
    SpawnExplosionEffects(moby,g_default_vector,offset,0,0,10,3,16,4,2,9,1,-1,15,0,9,-1,0,0x810001);
    part_spawn_masked_debris(moby,255,probe_a,3,6,3,6,255);
    moby_mark_spawned(moby);return;
closing:
    if(moby->state==3 && IsPointInCuboid(g_hero_position,ctx->close_volume)) {
        moby->state=4;
        if(moby->animation!=3)anim_start_blended(moby,3,0,0);
    }
    if(moby->state==4 && (moby->anim_flags&2)) {
        moby->state=5;moby->collision=moby->object_class->collision;
        if(moby->animation!=0)anim_start_blended(moby,0,0,0);
    }
}
