#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *g_path_l17_table[];
extern float D_L17_001B0344 __attribute__((sda));
extern float D_L17_001B0348 __attribute__((sda));
extern float D_L17_001B034C __attribute__((sda));
extern float D_L17_001B0350 __attribute__((sda));
extern float D_L17_001B0354 __attribute__((sda));
extern float D_L17_001B0358 __attribute__((sda));
extern unsigned char D_L17_001DBF82[];
extern unsigned char g_sound_state[];
extern void FastVecSub(void *,void *,void *);
extern float FastVecLength(void *);
extern float fast_vec_dist(void *,void *);
extern float vec_length_xy(void *);
extern float ApproachValue(void *,float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float mat_fast_helper_a(float,float);
extern float math_approach_target_with_direction_mode(void *,float,void *,int,float,float,float);
extern float func_002AAA00_yaw(void *,float,void *,float,float,float,int) __asm__("func_002AAA00");
extern int snd_is_voice_playing_for_owner(void *,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void snd_stop_voice(int);

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int func_PAL_L17_003CAA80(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&g_path_l17_table[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(D_L17_001B0344*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))++;
        complete=*(int *)(state+0x94)==*(int *)*path;
    }
    distance=fast_vec_dist(object+16,*path+*(int *)*path*16);
    deceleration=D_L17_001B0348*0.00040000002f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else ApproachValue(state+0x90,D_L17_001B0344*0.020000001f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-mat_fast_helper_a(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    math_approach_target_with_direction_mode(object+0xf4,pitch,state+0x9c,0,D_L17_001B034C*6.981318e-06f,D_L17_001B034C*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,mat_fast_helper_a(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,D_L17_001B0350*6.981318e-06f,D_L17_001B0350*6.981318e-06f,0.25132746f,0);
    math_approach_target_with_direction_mode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*D_L17_001B0358,state+0xa0,0,D_L17_001B0354*6.981318e-06f,D_L17_001B0354*6.981318e-06f,0.25132746f);
    if(!complete) {
        if(!snd_is_voice_playing_for_owner(object,*sound) && D_L17_001DBF82[0]!=255)
            *sound=snd_play_from_class_bank(0,4,object,0x922);
    } else {
        if(*sound!=-1) {
            char *voice=(char *)g_sound_state+*sound*0x70;
            if(*(char **)(voice+0x88)==object && ((u8 *)voice)[0x74]) snd_stop_voice(*sound);
        }
        *sound=-1;
    }
    return complete;
}

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int func_PAL_L17_003CADC0(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&g_path_l17_table[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(D_L17_001B0344*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))--;
        complete=*(int *)(state+0x94)==-1;
    }
    distance=fast_vec_dist(object+16,*path+16);
    deceleration=D_L17_001B0348*0.00040000002f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else ApproachValue(state+0x90,D_L17_001B0344*0.020000001f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-mat_fast_helper_a(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    math_approach_target_with_direction_mode(object+0xf4,pitch,state+0x9c,0,D_L17_001B034C*6.981318e-06f,D_L17_001B034C*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,mat_fast_helper_a(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,D_L17_001B0350*6.981318e-06f,D_L17_001B0350*6.981318e-06f,0.25132746f,0);
    math_approach_target_with_direction_mode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*D_L17_001B0358,state+0xa0,0,D_L17_001B0354*6.981318e-06f,D_L17_001B0354*6.981318e-06f,0.25132746f);
    if(!complete) {
        if(!snd_is_voice_playing_for_owner(object,*sound) && D_L17_001DBF82[0]!=255)
            *sound=snd_play_from_class_bank(0,4,object,0x922);
    } else {
        if(*sound!=-1) {
            char *voice=(char *)g_sound_state+*sound*0x70;
            if(*(char **)(voice+0x88)==object && ((u8 *)voice)[0x74]) snd_stop_voice(*sound);
        }
        *sound=-1;
    }
    return complete;
}

extern float D_L17_001B032C __attribute__((sda));
extern float D_L17_001B0330 __attribute__((sda));
extern float D_L17_001B0334 __attribute__((sda));
extern float D_L17_001B0338 __attribute__((sda));
extern float D_L17_001B033C __attribute__((sda));
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);

/* Re-aims one record's two angle pairs from the level's shared angle words: the 0x118/0x11C
   pair takes 0.000290888245f (arcseconds to radians) times the shared 0x1B0330 word, with the
   record's own 0x12C float as the third argument in the type-3 arm and -1.0f otherwise; the
   0x120/0x124 pair then takes the other two scaled words. */
void func_PAL_L17_003CB0F0(char *arg0)
{
    char *state = *(char **)(arg0 + 0x68);

    if (*(u8 *)(arg0 + 0x20) == 3) {
        math_update_wrapped_angle_offset(arg0, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.0003490659f,
                      *(f32 *)(state + 0x12C));
    } else {
        math_update_wrapped_angle_offset(arg0, state + 0x11C, state + 0x118, D_L17_001B032C,
                      D_L17_001B0330 * 0.0003490659f, -1.0f);
    }
    moby_scale_owner_words_by_angles(arg0, state + 0x120, state + 0x124, D_L17_001B0334,
                  D_L17_001B0338 * 0.0003490659f,
                  D_L17_001B033C * 0.0003490659f);
}
