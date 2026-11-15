#include "common.h"
typedef struct {
    int tableIndex; u8 pad04[12]; float origin[4];
    float angle, angularSpeed; int counter, timer; u8 pad30[16];
    int flags, sound; float amount;
} ObjectState;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern u8 D_0019B2E8[];
extern u8 g_sound_state[];
extern int g_current_map_index MACRO_ADDR;
extern u16 D_0018CC7C NOT_SDA;
extern int D_L16_001A8FF0 MACRO_ADDR;
extern u8 *D_L16_001B2B1C __attribute__((sda));
extern float D_L16_001B02B0 __attribute__((sda));
extern float D_L16_001B02B8 __attribute__((sda));
extern u32 D_L16_001B02C0[] MACRO_ADDR;
extern u32 colorFirst[] SDATA(D_L16_001B02C0);
extern float D_L16_001B02BC MACRO_ADDR;

extern char D_L16_001B02D0[];
extern int D_L16_001B2648 MACRO_ADDR;
extern int D_L16_001B3814 MACRO_ADDR;
typedef struct {
    u8 pad[0x160]; float strength; int pad164;
    int duration, timer; u8 pad170[0x10];
    float damping; int pad184, lifetime;
} EffectControls;
extern EffectControls D_L16_001B99C0;
extern u8 D_L16_001A8F20[] MACRO_ADDR;
extern float D_L16_001B9B00[4];
extern void moby_set_state(u8 *,s32,s32);
extern float moby_get_linked_float(const u8 *);
extern void part_spawn_spark_side(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_sweep_from_object(u8 *,void *,int,int,int,int,float,float,float);
extern int PlayMobySound(int,int,char *);
extern void snd_stop_voice(s32);
extern int subtitle_request_voice_line(int,int);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern void DrawRotatingGroupInstances(void *);
extern void *part_find_owned_effect_slot(void *,u32,s32);
extern void FastVecSub(void *,void *,void *);
extern char *part_spawn_blast_effect_moby(void *,void *,void *,float);
extern void mat_get_euler_angles(float *,float *);
extern void part_spawn_masked_debris(char *,int,float *,u8,float,float,float,float);
extern int moby_count_group_not_in_state(int,int);
extern char *GetLocalizedString(int);
extern int sprintf(char *,char *,...);
extern int level_l00_call_module_handler_with_arg_9(char *,int);
extern int math_fast_float_d(int *);
extern void moby_mark_table_entry_flagged(unsigned int);
extern void moby_mark_spawned(void *);
extern float FastAddRotations(float,float);
extern int PulseColor(int,int,float);

/* Object state machine: it moves along its direction as the level value from
 * func_L16_003960E8 rises, bursts once that value reaches 1 (effects, shake, a
 * formatted message with a count), then deletes itself when its timer runs out.
 * The idle colour pulses while the object is visible. */
/* This is the update of the moby of class 2681. */
void moby_state_update(u8 *object)
{
    float point[4],step[4],normal[4];
    char message[128];
    ObjectState *state=*(ObjectState **)(object+0x68);
    float amount,rate;
    char *string;
    int count,i;
    u32 timer,oldTimer;
    switch (object[0x20]) {
    case 0: {
        float speed;
        if (D_0019B2E8[object[0xB0]+g_current_map_index*16]&0x80) goto remove;
        object[0x30]=255;
        *(u16 *)(object+0x32)=0x113;
        *(u16 *)(object+0x34)|=0x4000;
        qcopy_nc(state->origin,object+0x10);
        speed=D_L16_001B02B8*0.00029088825f;
        state->amount=0.0f;
        state->sound=-1;
        state->angularSpeed=speed;
        moby_set_state(object,1,-1);
        break;
    }
    case 1:
        if (!D_L16_001A8FF0) break;
        amount=moby_get_linked_float(D_L16_001B2B1C+(state->tableIndex<<8));
        if (amount!=0.0f || state->amount!=0.0f) {
            part_spawn_spark_side(object);
            vec_scale_to_length(point,object+0xE0,D_L16_001B02B0*amount*(F(object,0x2C)/F(*(u8 **)(object+0x24),0x24)));
            FastVecAdd(object+0x10,state->origin,point);
            if (amount<state->amount) coll_sweep_from_object(object,object+0x10,0x10000,0,1,0,2.1f,3.0f,1.0f);
        }
        if (amount!=state->amount && amount!=1.0f && amount!=0.0f) {
            u8 *playingSound=g_sound_state+state->sound*0x70;
            if (*(u8 **)(playingSound+0x88)!=object || !playingSound[0x74]) state->sound=PlayMobySound(2,4,(char *)object);
        } else {
            int sound=state->sound;
            if (sound!=-1) {
                u8 *stoppingSound=g_sound_state+sound*0x70;
                if (*(u8 **)(stoppingSound+0x88)==object && stoppingSound[0x74]) snd_stop_voice(sound);
            }
            state->sound=-1;
        }
        if (amount==1.0f && state->amount!=1.0f) subtitle_request_voice_line(0x9EC,67);
        state->amount=amount;
        if (D_L16_001B3814!=D_L16_001B2648) {
            D_L16_001B3814=D_L16_001B2648;
            gfx_add_draw_callback_first(DrawRotatingGroupInstances,object);
        }
        if (amount>=1.0f) {
            if (part_find_owned_effect_slot(object,0x10000,0)) {
                PlayMobySound(0,0,(char *)object);
                object[0xA8]=255;
                moby_set_state(object,2,-1);
                D_0018CC7C=65535;
            }
        } else object[0xA8]=255;
        break;
    case 2:
        timer=*(u16 *)(object+0x96);
        oldTimer=timer++;
        *(u16 *)(object+0x96)=timer;
        if (oldTimer>=60) {
            vec_scale_to_length(point,object+0xE0,-2.0f);
            vec_scale_to_length(step,object+0xE0,5.0f);
            FastVecAdd(point,point,object+0x10);
            coll_sweep_from_object(object,point,0x10000,0,1,0,6.0f,3.0f,1.0f);
            PlayMobySound(1,0,(char *)object);
            for (i=0;i<2;i++) {
                FastVecSub(normal,D_L16_001B9B00,point);
                vec_scale_to_length(normal,normal,1.0f);
                part_spawn_blast_effect_moby(object,point,normal,0.0f);
                FastVecAdd(point,point,step);
            }
            D_L16_001B99C0.damping=0.1f;
            D_L16_001B99C0.lifetime=90;
            D_L16_001B99C0.strength=0.2f;
            D_L16_001B99C0.duration=60;
            D_L16_001B99C0.timer=0;
            mat_get_euler_angles((float *)(object+0xC0),(float *)(object+0xF0));
            part_spawn_masked_debris((char *)object,0xFFF,(float *)D_L16_001A8F20,255,2.0f,4.0f,10.0f,20.0f);
            state->counter=0;
            state->timer=180;
            state->flags=0;
            I(object,0x98)=0;
            *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)|0x41)&0xEFFF;
            count=moby_count_group_not_in_state(object[0x21],-1)-1;
            if (count!=0) {
                char *format=D_L16_001B02D0;
                char *text=message;
                string=GetLocalizedString(0x2F3A);
                sprintf(text,format,string,count);
                string=text;
                moby_set_state(object,4,-1);
                level_l00_call_module_handler_with_arg_9(string,180);
            } else {
                string=GetLocalizedString(0x2F3B);
                level_l00_call_module_handler_with_arg_9(string,180);
                moby_set_state(object,5,-1);
            }
        } else {
            if (*(u16 *)(object+0x96)%20==10) PlayMobySound(3,0,(char *)object);
        }
        break;
    case 4:
        if (math_fast_float_d(&state->timer)) {
remove:
            moby_mark_spawned(object);
            return;
        }
        break;
    case 5:
        if (math_fast_float_d(&state->timer)) {
            if (object[0xB0]!=255) moby_mark_table_entry_flagged(object[0xB0]);
            moby_mark_spawned(object);
            return;
        }
        break;
    }
    if (object[0x31]) {
        if (object[0x20]==2) {
            rate=FastAddRotations(state->angle,D_L16_001B02BC*0.00029088825f);
            state->angle=rate;
            *(u32 *)(object+0x78)=PulseColor(D_L16_001B02C0[2],D_L16_001B02C0[3],rate);
        } else {
            rate=FastAddRotations(state->angle,D_L16_001B02B8*0.00029088825f);
            state->angle=rate;
            *(u32 *)(object+0x78)=PulseColor(colorFirst[0],D_L16_001B02C0[1],rate);
        }
    }
}
