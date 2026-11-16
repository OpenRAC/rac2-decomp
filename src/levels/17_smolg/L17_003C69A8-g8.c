#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *g_path_l17_table[];
extern float g_platform_move_speed __attribute__((sda));
extern float g_platform_deceleration __attribute__((sda));
extern float g_platform_stop_angle_rate __attribute__((sda));
extern float g_platform_yaw_rate __attribute__((sda));
extern float g_platform_turn_rate __attribute__((sda));
extern float g_platform_turn_scale __attribute__((sda));
/* Incomplete view, reading only the measured sound-bank byte at [0]. */
extern unsigned char g_platform_l17_sound_flag_2[];
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
/* Same target: p,q,mode in the integer bank; four floats in the FP bank. */
extern float func_002AAA00_yaw(void *,float,void *,float,float,float,int) __asm__("func_002AAA00");
extern int snd_is_voice_playing_for_owner(void *,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void snd_stop_voice(int);

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int ride_platform_move_along_path(char *object,int pathIndex,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&g_path_l17_table[pathIndex];
    int complete=0;
    float speedSquared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(g_platform_move_speed*0.016666668f)*2.0f) {
        (*(int *)(state+0x94))++;
        complete=*(int *)(state+0x94)==*(int *)*path;
    }
    distance=fast_vec_dist(object+16,*path+*(int *)*path*16);
    deceleration=g_platform_deceleration*0.0002777777845f;
    speedSquared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speedSquared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speedSquared/(distance*2.0f));
    else ApproachValue(state+0x90,g_platform_move_speed*0.016666668f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-mat_fast_helper_a(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    math_approach_target_with_direction_mode(object+0xf4,pitch,state+0x9c,0,g_platform_stop_angle_rate*0.00000484813743f,g_platform_stop_angle_rate*0.00000484813743f,0.209439546f);
    func_002AAA00_yaw(object+0xf8,mat_fast_helper_a(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,g_platform_yaw_rate*0.00000484813743f,g_platform_yaw_rate*0.00000484813743f,0.209439546f,0);
    math_approach_target_with_direction_mode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*g_platform_turn_scale,state+0xa0,0,g_platform_turn_rate*0.00000484813743f,g_platform_turn_rate*0.00000484813743f,0.209439546f);
    if(!complete) {
        if(!snd_is_voice_playing_for_owner(object,*sound) && g_platform_l17_sound_flag_2[0]!=255)
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
