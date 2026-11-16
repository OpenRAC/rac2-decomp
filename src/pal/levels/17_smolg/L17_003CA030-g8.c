#include "include_asm.h"

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
extern float func_002AAA00_yaw(void *,float,void *,float,float,float,int) __asm__("func_002AAA00");
extern int snd_is_voice_playing_for_owner(void *,int);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void snd_stop_voice(int);

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int ride_platform_move_along_path_pal(char *object,int path_index,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&g_path_l17_table[path_index];
    int complete=0;
    float speed_squared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(g_platform_move_speed*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))++;
        complete=*(int *)(state+0x94)==*(int *)*path;
    }
    distance=fast_vec_dist(object+16,*path+*(int *)*path*16);
    deceleration=g_platform_deceleration*0.00040000002f;
    speed_squared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speed_squared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speed_squared/(distance*2.0f));
    else ApproachValue(state+0x90,g_platform_move_speed*0.020000001f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-mat_fast_helper_a(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    math_approach_target_with_direction_mode(object+0xf4,pitch,state+0x9c,0,g_platform_stop_angle_rate*6.981318e-06f,g_platform_stop_angle_rate*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,mat_fast_helper_a(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,g_platform_yaw_rate*6.981318e-06f,g_platform_yaw_rate*6.981318e-06f,0.25132746f,0);
    math_approach_target_with_direction_mode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*g_platform_turn_scale,state+0xa0,0,g_platform_turn_rate*6.981318e-06f,g_platform_turn_rate*6.981318e-06f,0.25132746f);
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

/* Moves along the selected path, turns smoothly, and manages its movement sound. */
int platform_move_along_path_with_sound_pal(char *object,int path_index,int *sound)
{
    Vec target,delta;
    char *state=*(char **)(object+0x68);
    char **path=&g_path_l17_table[path_index];
    int complete=0;
    float speed_squared,deceleration,distance,pitch;
    qcopy(&target,*path+16+*(int *)(state+0x94)*16);
    FastVecSub(&delta,&target,object+16);
    if(FastVecLength(&delta)<(g_platform_move_speed*0.020000001f)*2.0f) {
        (*(int *)(state+0x94))--;
        complete=*(int *)(state+0x94)==-1;
    }
    distance=fast_vec_dist(object+16,*path+16);
    deceleration=g_platform_deceleration*0.00040000002f;
    speed_squared=*(float *)(state+0x90)* *(float *)(state+0x90);
    if(distance<=speed_squared/(deceleration*2.0f))
        ApproachValue(state+0x90,0.0f,speed_squared/(distance*2.0f));
    else ApproachValue(state+0x90,g_platform_move_speed*0.020000001f,deceleration);
    vec_scale_to_length(&delta,&delta,*(float *)(state+0x90));
    FastVecAdd(object+16,&delta,object+16);
    pitch=-mat_fast_helper_a(vec_length_xy(&delta),delta.f[2]);
    if(pitch>0.261799425f) pitch=0.261799425f;
    else if(pitch< -0.261799425f) pitch= -0.261799425f;
    math_approach_target_with_direction_mode(object+0xf4,pitch,state+0x9c,0,g_platform_stop_angle_rate*6.981318e-06f,g_platform_stop_angle_rate*6.981318e-06f,0.25132746f);
    func_002AAA00_yaw(object+0xf8,mat_fast_helper_a(target.f[0]-*(float *)(object+16),target.f[1]-*(float *)(object+20)),state+0x98,g_platform_yaw_rate*6.981318e-06f,g_platform_yaw_rate*6.981318e-06f,0.25132746f,0);
    math_approach_target_with_direction_mode(object+0xf0,*(float *)(state+0x98)* *(float *)(state+0x90)*g_platform_turn_scale,state+0xa0,0,g_platform_turn_rate*6.981318e-06f,g_platform_turn_rate*6.981318e-06f,0.25132746f);
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

extern float g_platform_bob_amplitude __attribute__((sda));
extern float g_platform_bob_period __attribute__((sda));
extern float g_platform_sway_amplitude __attribute__((sda));
extern float g_platform_sway_period __attribute__((sda));
extern float g_platform_tilt_period __attribute__((sda));
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);

/* Re-aims one record's two angle pairs from the level's shared angle words: the 0x118/0x11C
   pair takes 0.000290888245f (arcseconds to radians) times the shared 0x1B0330 word, with the
   record's own 0x12C float as the third argument in the type-3 arm and -1.0f otherwise; the
   0x120/0x124 pair then takes the other two scaled words. */
void platform_update_bob_sway_pal(char *self)
{
    char *state = *(char **)(self + 0x68);

    if (*(u8 *)(self + 0x20) == 3) {
        math_update_wrapped_angle_offset(self, state + 0x11C, state + 0x118, g_platform_bob_amplitude,
                      g_platform_bob_period * 0.0003490659f,
                      *(f32 *)(state + 0x12C));
    } else {
        math_update_wrapped_angle_offset(self, state + 0x11C, state + 0x118, g_platform_bob_amplitude,
                      g_platform_bob_period * 0.0003490659f, -1.0f);
    }
    moby_scale_owner_words_by_angles(self, state + 0x120, state + 0x124, g_platform_sway_amplitude,
                  g_platform_sway_period * 0.0003490659f,
                  g_platform_tilt_period * 0.0003490659f);
}
