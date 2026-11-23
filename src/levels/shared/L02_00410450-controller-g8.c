#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct {
    int primary,secondary,key,secondaryKey,reserved10;
    u8 *children[3];
    float orbitA,orbitB,rateA,rateB;
    int reserved30;
    float timer;
    int handle;
    float opacity;
    int variant;
} OrbitState;
typedef void (*DrawCallback)(void *);
extern void SpawnOrbitingChildren(u8 *);
extern void teleporter_update_orbiting_children(u8 *);
extern void hud_show_message_for_state(u8 *);
extern void DrawAnimatedEffectQuads(u8 *);
extern void math_store_clamped_complement(u8 *);
extern int PlayMobySound(int,int,char *);
extern void hero_start_target_state(Quad *,int,float);
extern int coll_sweep_from_object(void *,float,float *,int,float,float,int,int,int);
extern int hero_get_target_state_kind(void);
extern int hero_l00_set_move_state(int,int);
extern void gfx_add_draw_callback_first(DrawCallback,void *);
extern void gfx_add_draw_callback_third(DrawCallback,void *);
extern float ApproachValue(float *,float,float);
extern void moby_set_state(u8 *,int,int);
extern void hero_reset_position_and_direction(void *,void *,int,int);
extern int flag_set_first_pending(u8 *);
extern float math_step_value_toward_target(float *,float *,float,float,float,float);
extern void hero_start_loader_state(int);
extern void load_scene_chunk(int,int);
extern int g_current_map_index MACRO_ADDR;
extern u8 g_moby_group_flags[];
typedef struct {
    u8 reserved0[0x33C];
    u8 *selected;
    u8 reserved340[0xE];
    short busy;
    u8 reserved350[0x1F65];
    u8 active;
} Resident;
extern Resident g_hero_state;
extern u32 g_pad_held_flags NOT_SDA;
extern int g_teleporter_state __attribute__((sda));
extern u8 *g_moby_l02_pool MACRO_ADDR;
extern float g_teleporter_orbit_speed __attribute__((sda));
extern float g_teleporter_orbit_accel __attribute__((sda));
extern float g_teleporter_orbit_rate_limit __attribute__((sda));

/* Run the control's activation, orbit and captured-object transition states. */
void teleporter_l02_update(u8 *object)
{
    OrbitState *state=*(OrbitState **)(object+0x68);
    u8 **slot;
    int left,answer;
    Vector position;
    switch(object[0x20]) {
    case 0:
        object[0x30]=0xFF;object[0x20]=1;
        SpawnOrbitingChildren(object);
        teleporter_update_orbiting_children(object);
        break;
    case 1:
        if(state->key>=0 && !(g_moby_group_flags[state->key+g_current_map_index*16]&0x80)) {
            *(int *)(object+0x98)=0;
            *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)|0x41)&0xEFFF;
            slot=state->children;left=2;
            do {
                *(u16 *)(*slot+0x34)|=0x41;
                *(u16 *)(*slot+0x34)&=0xEFFF;
                *(int *)(*slot+0x98)=0;
                slot++;
            } while(--left>=0);
            break;
        }
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;
            *(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);
            slot++;
        } while(--left>=0);
        if(state->primary!=-1 && g_hero_state.selected==object) {
            if(g_hero_state.busy) goto propagate;
            hud_show_message_for_state(object);
            if((g_pad_held_flags&0x10) && g_teleporter_state==11) {
                PlayMobySound(0,0,(char *)object);
                object[0x20]=2;state->rateA=0;state->rateB=0;
                hero_start_target_state((Quad *)(object+0x10),0,*(float *)(object+0xF8));
                coll_sweep_from_object(object,1.5f,(float *)(object+0x10),0x10000,20.0f,1.0f,0,1,0);
            }
        }
        break;
    case 2:
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        answer=hero_get_target_state_kind();
        if(state->orbitA<1.0f) {
            math_step_value_toward_target(&state->orbitA,&state->rateA,1.0f,g_teleporter_orbit_speed*0.00027777778f,g_teleporter_orbit_accel*0.00027777778f,g_teleporter_orbit_rate_limit*0.016666668f);
        } else if(state->orbitB<1.0f) {
            math_step_value_toward_target(&state->orbitB,&state->rateB,1.0f,g_teleporter_orbit_speed*0.00027777778f,g_teleporter_orbit_accel*0.00027777778f,g_teleporter_orbit_rate_limit*0.016666668f);
        } else if(g_teleporter_state!=11 || !(state->orbitA>0.25f)) {
            if(answer==2) {hero_l00_set_move_state(0x6F,1);state->timer=1.95f;object[0x20]=3;}
            else if(answer==0) object[0x20]=4;
        }
        teleporter_update_orbiting_children(object);
        break;
    case 3: {
        u8 *data;
        u8 *actor;
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        if(state->timer!=0.0f) {
            gfx_add_draw_callback_first((DrawCallback)DrawAnimatedEffectQuads,object);
            ApproachValue(&state->timer,0,0.06666667f);
            break;
        }
            g_hero_state.active=1;
            if(state->handle>=0) {moby_set_state(object,5,-1);break;}
            {
                actor=g_moby_l02_pool+state->primary*0x100;
                if(state->secondary!=-1 && (g_moby_group_flags[state->secondaryKey+g_current_map_index*16]&0x80)) actor=g_moby_l02_pool+state->secondary*0x100;
                data=*(u8 **)(actor+0x68);
                qcopy(&position,actor+0x10);position.f[2]+=0.2f;
                hero_reset_position_and_direction(&position,actor+0xF0,0,1);
                actor[0x20]=4;
                *(float *)(data+0x34)=0;*(float *)(data+0x28)=0;*(float *)(data+0x2C)=0;
                *(float *)(data+0x20)=1;*(float *)(data+0x24)=1;
                PlayMobySound(1,0,(char *)actor);
                object[0x20]=1;state->orbitA=0;state->orbitB=0;state->rateA=0;state->rateB=0;state->timer=1.95f;
                teleporter_update_orbiting_children(object);
            }
        break;
    }
    case 4:
        flag_set_first_pending(object);
        *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)&0xFFBE)|0x1000;
        *(int *)(object+0x98)=*(int *)(*(u8 **)(object+0x24)+0x10);
        slot=state->children;left=2;
        do {
            *(u16 *)(*slot+0x34)&=0xFFBE;*(u16 *)(*slot+0x34)|=0x1000;
            *(int *)(*slot+0x98)=*(int *)(*(u8 **)(*slot+0x24)+0x10);slot++;
        } while(--left>=0);
        if(state->timer<1.95f) {
            gfx_add_draw_callback_first((DrawCallback)DrawAnimatedEffectQuads,object);
            ApproachValue(&state->timer,1.95f,0.06666667f);
        } else {
            if(state->orbitB>0.0f) {
                math_step_value_toward_target(&state->orbitB,&state->rateA,0.0f,g_teleporter_orbit_speed*0.00027777778f,g_teleporter_orbit_accel*0.00027777778f,g_teleporter_orbit_rate_limit*0.016666668f);
            } else if(state->orbitA>0.0f) {
                math_step_value_toward_target(&state->orbitA,&state->rateB,0.0f,g_teleporter_orbit_speed*0.00027777778f,g_teleporter_orbit_accel*0.00027777778f,g_teleporter_orbit_rate_limit*0.016666668f);
            } else object[0x20]=1;
        }
        teleporter_update_orbiting_children(object);
        break;
    case 6:
        if(flag_set_first_pending(object)) {
            state->orbitB=1;state->orbitA=1;teleporter_update_orbiting_children(object);state->opacity=0;
        }
        state->opacity+=0.02f;g_hero_state.active=1;
        if(state->opacity>=1.2f) {
            hero_start_loader_state(0);object[0x20]=4;
            state->rateA=0;state->rateB=0;state->timer=0;state->orbitA=1;state->orbitB=1;
            PlayMobySound(1,0,(char *)object);
        }
        gfx_add_draw_callback_third((DrawCallback)math_store_clamped_complement,object);
        break;
    case 5: {
        u8 *actor;
        if(flag_set_first_pending(object)) state->opacity=1;
        state->opacity-=0.02f;g_hero_state.active=1;
        if(state->opacity<=-0.2f) {
            actor=g_moby_l02_pool+state->primary*0x100;
            actor[0x20]=6;object[0x20]=1;state->timer=1.95f;
            state->orbitA=0;state->orbitB=0;state->rateA=0;state->rateB=0;
            if(state->variant>=0) load_scene_chunk(state->handle,state->variant);
            else load_scene_chunk(state->handle,0);
            qcopy(&position,actor+0x10);position.f[2]+=0.2f;
            hero_reset_position_and_direction(&position,actor+0xF0,0x6F,1);
            teleporter_update_orbiting_children(object);
            moby_set_state(object,1,-1);
        }
        gfx_add_draw_callback_third((DrawCallback)math_store_clamped_complement,object);
        break;
    }
    }
propagate: {
    u8 **child=state->children;
    int count=2;
    do {
        if(*child) {
            int flags=*(u16 *)(*child+0x34);
            int inherited=*(u16 *)(object+0x34)&0x80;
            flags &= 0xFF7F;
            *(u16 *)(*child+0x34)=flags+inherited;
        }
        child++;
    } while(--count>=0);
}
}
