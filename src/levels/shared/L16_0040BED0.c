/* Update the launch target, hero motion, fade state, tutorial and looping sound. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float f0,f4,f8,f12,f16,f20; u8 f24,f25; s16 f26; u8 f28,f29,f30,f31,pad32[16]; s16 f48,f50; int f52,f56,f60; } PoolRecord64;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
typedef struct { u8 pad0[0x88]; float height; u8 pad8C[0x6C]; float upward; u8 padFC[0x10]; float velocityW; u8 pad110[0x90]; float heading; u8 pad1A4[0x38]; s16 timer; u8 pad1DE[0x15E]; u8 *owner; u8 pad340[0x1F54]; int mode; } ResidentView;
extern ResidentView g_hero_state;
extern u8 g_sound_state[];
typedef struct { u16 count, pad; u32 time, levels; } SubtitleHistory;
extern SubtitleHistory g_subtitle_history[];
extern u32 g_current_map_index[] __attribute__((sda));
extern u32 level_gp SDATA(D_001A79F0);
extern u32 g_frame_counter __attribute__((sda));
extern int g_snivelak_state[] __attribute__((sda));
extern float g_hero_speed_param_a[] __attribute__((sda));
extern float launch_gp SDATA(D_L16_001A7CD8);
extern float g_hero_speed_param_b[] __attribute__((sda));
extern u32 g_frame_l16_counter __attribute__((sda));
extern u8 (*g_moby_instance_table[])[256] __attribute__((sda));
extern u8 (*objects_gp)[256] SDATA(D_L16_001B2B1C);
extern u8 (*g_beam_definition_table)[128] __attribute__((sda));
extern float g_effect_float_param __attribute__((sda));
extern float g_effect_field_a __attribute__((sda)),g_effect_field_b __attribute__((sda));
extern float g_effect_angle_degrees __attribute__((sda));
extern Quad g_effect_quad_pad __attribute__((sda));
typedef struct { s32 targetIndex, objectIndex, pad8; float rate; float velocity[4], position[4]; s32 sound, pad34, active, pad3C; PoolRecord64 *effect; } LaunchState;
extern void moby_mark_spawned(void *);
extern float mat_fast_helper_a(float,float);
extern void moby_set_state(u8 *,s32,s32);
extern void moby_get_launch_target_pos(u8 *,void *);
extern int PlayMobySound(int,int,char *);
extern float vec_distance_xy(void *,void *);
extern float vec_length_xy(void *);
extern float square_root(float);
extern void FastVecSub(void *,void *,void *);
extern void vec_fast_normalize_helper(void *,void *,float);
extern float FastVecDot(void *,void *);
extern PoolRecord64 *cam_alloc_override_slot(int);
extern void cam_end_override(u8 *);
extern void part_spawn_sparkle_in_triangle(u8 *);
extern float vec_distance_squared_xy(void *,void *);
extern int subtitle_request_voice_line(int,int);
extern void snd_stop_voice(s32);
/* Updates a launch pad (moby class 3845): it picks up the player, flings them toward a target, fades, and plays its looping sound. */
void UpdateTargetedHeroLauncher(u8 *object)
{
    float difference[4],value,distance,rate,multiplier;
    LaunchState *state=*(LaunchState **)(object+0x68);
    u8 *target;
    PoolRecord64 *effect;
    int handle;
    if (g_snivelak_state[0]==2) return;
    switch (object[0x20]) {
    case 0:
        if (level_gp==16) g_hero_speed_param_b[0]=g_effect_float_param;
        if (state->targetIndex!=-1) {
            target=(u8 *)((state->targetIndex<<7)+(u32)g_beam_definition_table);
            F(object,0xF8)=mat_fast_helper_a(F(object,0x10)-F(target,0x30),F(object,0x14)-F(target,0x34));
        } else {
            if (state->objectIndex==-1) { moby_mark_spawned(object); return; }
            target=(u8 *)((state->objectIndex<<8)+(u32)objects_gp);
            F(object,0xF8)=mat_fast_helper_a(F(object,0x10)-F(target,0x10),F(object,0x14)-F(target,0x14));
        }
        state->sound=-1;
        object[0x30]=255;
        *(u16 *)(object+0x34)|=0x2000;
        moby_set_state(object,1,-1);
        break;
    case 1:
        if (g_hero_state.owner==object) {
            moby_get_launch_target_pos(object,state->position);
            launch_gp=(state->position[2]-g_hero_state.height)*2.5f;
            if (launch_gp<37.0f) g_hero_speed_param_a[0]=37.0f;
        }
        if (g_hero_state.mode==0x81) {
            if (g_hero_state.owner==object && g_hero_state.upward>0.0f) {
                multiplier=0.5f;
                PlayMobySound(1,0,(char *)object);
                if (g_current_map_index[0]==16) multiplier=0.3f;
                distance=vec_distance_xy((u8 *)&g_hero_state+0x80,state->position);
                rate=g_hero_speed_param_b[0]*(distance*0.00027777778f)*multiplier/g_hero_speed_param_a[0];
                value=square_root((rate+rate)*distance);
                FastVecSub(difference,state->position,(u8 *)&g_hero_state+0x80);
                difference[2]=0.0f;
                vec_fast_normalize_helper(state->velocity,difference,value);
                vec_fast_normalize_helper((u8 *)&g_hero_state+0xF0,(u8 *)&g_hero_state+0xF0,0.0f);
                state->rate=rate;
                moby_set_state(object,2,-1);
            }
        } else if ((g_frame_l16_counter&15)==(((s32)object>>8)&15)) {
            if (state->objectIndex!=-1 && (*(u16 *)(objects_gp[state->objectIndex]+0x34)&1)) moby_set_state(object,3,-1);
        }
        break;
    case 2:
        if (g_hero_state.mode==0x81) {
            value=vec_length_xy(state->velocity);
            distance=vec_distance_xy((u8 *)&g_hero_state+0x80,state->position);
            if (distance<0.5f) value=0.0f;
            else if (value!=0.0f) {
                FastVecSub(difference,state->position,(u8 *)&g_hero_state+0x80);
                difference[2]=0.0f;
                if (FastVecDot(difference,state->velocity)<0.0f) value=0.0f;
            }
            value-=state->rate;
            vec_fast_normalize_helper(state->velocity,state->velocity,value);
            vec_fast_normalize_helper((u8 *)&g_hero_state+0xF0,(u8 *)&g_hero_state+0xF0,0.0f);
            qcopy((u8 *)&g_hero_state+0x100,state->velocity);
            g_hero_state.velocityW=0.0f;
            if (value!=0.0f) g_hero_state.heading=mat_fast_helper_a(state->velocity[0],state->velocity[1]);
            g_hero_state.timer=10;
            if (g_current_map_index[0]==17 && !state->active) {
                effect=cam_alloc_override_slot(5);
                state->effect=effect;
                if (effect) {
                    state->active=1;
                    qcopy(effect->pad32,&g_effect_quad_pad);
                    effect->f0=g_effect_field_a;
                    state->effect->f4=g_effect_field_b;
                    state->effect->f12=g_effect_angle_degrees*0.017453294f;
                    state->effect->f30=1;
                    state->effect->f26=1;
                }
            }
        } else {
            if (state->active) {
                state->effect->f26=0;
                cam_end_override((u8 *)state->effect);
                state->active=0;
            }
            moby_set_state(object,1,-1);
        }
        break;
    case 3: {
        u8 *fadeTarget=g_moby_instance_table[0][state->objectIndex];
        if ((*(u16 *)(fadeTarget+0x34)&1)) {
            if (object[0x23]) {
                I(object,0x98)=0;
                if (object[0x23]>3) object[0x23]-=4;
                else object[0x23]=0;
                break;
            }
        }
        if (((*(u16 *)(fadeTarget+0x34)^1)&1)) {
            if (object[0x23]<124) object[0x23]+=4;
            else {
                object[0x23]=128;
                moby_set_state(object,1,-1);
                I(object,0x98)=I(*(u8 **)(object+0x24),0x10);
            }
        }
        break;
    }
    }
    if (object[0x31] && object[0x20]!=3) part_spawn_sparkle_in_triangle(object);
    if (g_current_map_index[0]==16 && vec_distance_squared_xy((u8 *)&g_hero_state+0x80,object+0x10)<9.0f) {
        if (g_subtitle_history[99].count!=0) {
            if (g_frame_counter-g_subtitle_history[99].time>1080 || g_subtitle_history[99].time==0) subtitle_request_voice_line(0xA0C,99);
            else if (g_frame_counter>g_subtitle_history[99].time) g_subtitle_history[99].time=g_frame_counter;
        } else {
            g_subtitle_history[99].count++;
            if (g_subtitle_history[99].time<g_frame_counter) g_subtitle_history[99].time=g_frame_counter;
            g_subtitle_history[99].levels=(g_subtitle_history[99].levels|(1U<<g_current_map_index[0]))|0x80000000U;
        }
    }
    if (object[0x20]==2) g_subtitle_history[99].count=-1;
    if (((*(u16 *)(object+0x34)^1)&1) && I(object,0x98)!=0) {
        u8 *sound=state->sound*0x70+g_sound_state;
        if (*(u8 **)(sound+0x88)==object && sound[0x74]) return;
        state->sound=PlayMobySound(0,4,(char *)object);
        return;
    }
    handle=state->sound;
    if (handle!=-1) {
        u8 *sound=handle*0x70+g_sound_state;
        if (*(u8 **)(sound+0x88)==object && sound[0x74]) snd_stop_voice(handle);
    }
    state->sound=-1;
}
