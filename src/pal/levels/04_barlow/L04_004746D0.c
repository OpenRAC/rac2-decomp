#include "include_asm.h"

#include "common.h"
extern float g_tether_zero_vec[4];
extern unsigned char *g_ambient_sound_table __attribute__((sda));
extern unsigned char *g_moby_l04_pool __attribute__((sda));
extern unsigned char g_sound_state[];
extern void FastVecSub(float *, float *, void *);
extern void matrix_mul_vec3(float *, float *, void *);
extern float FastVecLength(float *);
extern float math_fabs(float);
extern int snd_compute_falloff(void *, float, float, float);
extern float IntToFloat(int);
extern int FloatToInt(float);
extern int math_fast_float_d(int *);
extern int snd_start_from_table_entry(int,int,void *,int);
extern int math_random_int_below(int);
extern int snd_set_slot_field(int,int);
extern void FastVecAdd(float *,float *,void *);
extern void snd_stop_voice(int);
typedef struct { int sound, minTime, maxTime, timer, handle, target; float start, end; } AmbientState;

/* Updates an ambient sound inside a transformed volume, including its voice position. */
void snd_update_ambient_volume_pal(unsigned char *moby)
{
    float pos[4], scale[4], delta[4], extent[4];
    AmbientState *ambient = *(AmbientState **)(moby+8);
    float outer, distance, time, edge;
    int volume, flags;
    unsigned char *slot;
    scale[2] = scale[1] = scale[0] = *(float *)(moby+12);
    FastVecSub(pos,g_tether_zero_vec,moby+0x40);
    pos[3] = 0;
    matrix_mul_vec3(delta,pos,moby+0x50);
    matrix_mul_vec3(extent,scale,moby+0x50);
    outer = FastVecLength(extent);
    distance = FastVecLength(delta);
    if (distance < outer) {
        flags = 16;
        if (math_fabs(delta[0]) <= 1.0f && math_fabs(delta[1]) <= 1.0f && math_fabs(delta[2]) <= 1.0f) {
            volume = *(int *)(g_ambient_sound_table+ambient->sound*32+12);
        } else {
            if(delta[0]>1.0f) delta[0]=1.0f; else if(delta[0]<-1.0f) delta[0]=-1.0f;
            if(delta[1]>1.0f) delta[1]=1.0f; else if(delta[1]<-1.0f) delta[1]=-1.0f;
            if(delta[2]>1.0f) delta[2]=1.0f; else if(delta[2]<-1.0f) delta[2]=-1.0f;
            edge=FastVecLength(delta);
            volume=snd_compute_falloff(g_ambient_sound_table+ambient->sound*32,distance,edge,outer);
        }
        if(ambient->target!=-1) {
            unsigned char *target=g_moby_l04_pool+ambient->target*256;
            if(*(short *)(target+0xAA)==3004) {
                unsigned char *vars=*(unsigned char **)(target+0x68);
                int cap;
                time=*(float *)(vars+0x30C)+*(float *)(vars+0x27C);
                if(ambient->end*(0.020000001f)<time) time=ambient->end*(0.020000001f);
                time-=ambient->start*(0.020000001f);
                if(time<0) time=0;
                cap=FloatToInt(IntToFloat(1024)*(time/((ambient->end-ambient->start)*(0.020000001f))));
                if(cap<volume) volume=cap;
            }
        }
        slot=g_sound_state+ambient->handle*0x70;
        if(g_ambient_sound_table[ambient->sound*32+24]) flags=20;
        if(*(unsigned char **)(slot+0x8C)!=moby || !slot[0x74]) {
            if(math_fast_float_d(&ambient->timer)) {
                ambient->handle=snd_start_from_table_entry(ambient->sound,flags,moby,volume);
                if(ambient->maxTime>0) ambient->timer=(ambient->minTime+math_random_int_below(ambient->maxTime-ambient->minTime))*5e+01f;
            } else ambient->handle=-1;
        }
        if(ambient->handle!=-1) {
            snd_set_slot_field(ambient->handle,volume);
            matrix_mul_vec3(pos,delta,moby+0x10);
            FastVecAdd(pos,pos,moby+0x40);
            qcopy(g_sound_state+ambient->handle*0x70+0x90,pos);
        }
    } else {
        if(ambient->handle!=-1) {
            unsigned char *old_slot=g_sound_state+ambient->handle*0x70;
            if(*(unsigned char **)(old_slot+0x8C)==moby && old_slot[0x74]) snd_stop_voice(ambient->handle);
        }
        ambient->handle=-1;
    }
}

