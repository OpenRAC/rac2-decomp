#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } UpdateVector;
typedef struct UpdateContext {
    int field0;
    short timer4, timer6, timer8, timerA;
    float rotC, rot10;
    int timer14;
    char pad18[8];
    UpdateVector saved, velocity;
} UpdateContext;
typedef struct UpdateObject {
    char pad0[0x10];
    UpdateVector position;
    unsigned char state;
    char pad21[0x34-0x21];
    unsigned short flags;
    char pad36[0x68-0x36];
    UpdateContext *context;
    char pad6C[0xAA-0x6C];
    short classId;
    char padAC[0xF0-0xAC];
    float rotX, rotY;
} UpdateObject;
typedef struct HeroView {
char pad0[4640];
UpdateObject * field1220;
char pad1224[4204];
unsigned char * field2290;
char pad2294[32];
unsigned char field22b4;
unsigned char field22b5;
char pad22b6[9];
unsigned char field22bf;
} HeroView;
extern HeroView g_hero_state;
extern float g_orb_gravity __attribute__((sda));
extern int g_orb_transition_frames __attribute__((sda));
extern int g_effect_lifetime_frames __attribute__((sda));
extern int g_active_orb __attribute__((sda));
extern unsigned short g_orb_duration_frames __attribute__((sda));
extern float g_orb_hit_radius_max __attribute__((sda));
extern float g_orb_hit_radius_min __attribute__((sda));
extern float g_default_vector[4] MACRO_ADDR;
extern Quad g_collision_position;
extern void FastVecAdd(void *,void *,void *),gravity_offset_position(void *,void *,void *,float);
extern float FastAddRotations(float,float),FastVecDot(void *,void *),IntToFloat(int);
extern int FastDecTimer(short *),math_fast_float_d(int *);
extern void lerp_vector(void *,void *,void *,float),ref_L00_003B3450_00(void (*)(void *),void *);
extern int coll_test_point(void *,int,void *,float);
extern void moby_mark_spawned(void *);
extern void coll_object_with_walls(void *),jitter_trail_reset_slots(void *),UpdateJitterTrails(void *),DrawTimedQuadEffects(void *),part_l00_spawn_spark_ring(void *),UpdateTimedEvents(void *),part_spawn_spark_burst_away_from_camera(void *),blast_broadcast_area_message(void *);
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
/* Updates the glowing orb weapon: it flies out, slows down, then hovers and pulses with rings and sparks, and finally bursts. It goes away at once if the weapon is no longer held. */
void glowing_orb_update(UpdateObject *object)
{
    Quad previous;
    UpdateContext *ctx=object->context;
    UpdateObject *hero_object=g_hero_state.field1220;
    float fraction;
    if((!hero_object || hero_object->classId!=MOBY_CLASS_BOMB_GLOVE) && !object->state) { moby_mark_spawned(object); return; }
    if(g_hero_state.field22b4 && !object->state) { moby_mark_spawned(object); return; }
    if((g_hero_state.field22b5 || g_hero_state.field22bf) && !object->state) object->flags|=0x41;
    else object->flags&=~0x41;
    switch(object->state) {
    case 1:
        qcopy(&previous,&object->position);
        FastVecAdd(&object->position,&object->position,&ctx->velocity);
        gravity_offset_position(&object->position,&ctx->velocity,&ctx->velocity,g_orb_gravity*0.00027777778f);
        object->rotX=FastAddRotations(object->rotX,ctx->rotC);
        object->rotY=FastAddRotations(object->rotY,ctx->rot10);
        coll_object_with_walls(object);
        if(FastDecTimer(&ctx->timer4)) { moby_mark_spawned(object); return; }
        if(object->position.f[0]<2.0f || object->position.f[0]>1021.0f || object->position.f[1]<2.0f || object->position.f[1]>1021.0f || object->position.f[2]<2.0f || object->position.f[2]>1021.0f) { moby_mark_spawned(object); return; }
        if(FastVecDot((char *)&g_hero_state+0x2C0,&ctx->velocity)>0.0f && FastDecTimer(&ctx->timer6)) {
            object->state=2;
            {
                unsigned short duration = g_orb_duration_frames;
                unsigned short transition = *(unsigned short *)&g_orb_transition_frames;
                ctx->timer8 = duration;
                ctx->timerA = transition;
            }
            qcopy(&ctx->saved,&ctx->velocity);
            jitter_trail_reset_slots(object);
        }
        return;
    case 2: {
        float duration;
        fraction=IntToFloat(ctx->timerA);
        duration=IntToFloat(g_orb_transition_frames);
        fraction/=duration;
        lerp_vector(&ctx->velocity,g_default_vector,&ctx->saved,fraction);
        FastVecAdd(&object->position,&object->position,&ctx->velocity);
        object->rotX=FastAddRotations(object->rotX,ctx->rotC);
        object->rotY=FastAddRotations(object->rotY,ctx->rot10);
        UpdateJitterTrails(object);
        ref_L00_003B3450_00(DrawTimedQuadEffects,object);
        if(coll_test_point(&object->position,0,g_hero_state.field2290,0.25f)) qcopy(&object->position,&g_collision_position);
        if(object->position.f[0]<2.0f || object->position.f[0]>1021.0f || object->position.f[1]<2.0f || object->position.f[1]>1021.0f || object->position.f[2]<2.0f || object->position.f[2]>1021.0f) {
        moby_mark_spawned(object);return;
        }
        if(FastDecTimer(&ctx->timerA) && !g_active_orb) {
            object->state=3;ctx->timer14=g_effect_lifetime_frames;
            g_active_orb=(int)object;part_l00_spawn_spark_ring(object);
        }
        return;
    }
    case 3:
        object->rotX=FastAddRotations(object->rotX,ctx->rotC);
        object->rotY=FastAddRotations(object->rotY,ctx->rot10);
        UpdateJitterTrails(object);UpdateTimedEvents(object);
        if(ctx->timer8>=60) part_spawn_spark_burst_away_from_camera(object);
        ref_L00_003B3450_00(DrawTimedQuadEffects,object);
        math_fast_float_d(&ctx->timer14);
        if(ctx->timer14) {
            fraction=IntToFloat(ctx->timer14);fraction/=IntToFloat(g_effect_lifetime_frames);
            if(coll_test_point(&object->position,2,g_hero_state.field2290,g_orb_hit_radius_min+(g_orb_hit_radius_max-g_orb_hit_radius_min)*fraction)) qcopy(&object->position,&g_collision_position);
        }
        blast_broadcast_area_message(object);
        if(FastDecTimer(&ctx->timer8)) {
            qzero_nc(&previous);
            SpawnExplosionEffects(object,&previous,&object->position,0.0f,0.0f,5,2,4,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,5,-1,0,0x810001);
            g_active_orb=0;object->state=90;
        }
        return;
    case 90:
        moby_mark_spawned(object);
    }
}
