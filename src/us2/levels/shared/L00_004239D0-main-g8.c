/* func_US2_L00_004239D0, the USA v2.00 copy of func_L00_004224D0: the same C, where the state test reads
   D_L00_001B8E20 (+0x264) through value temp and the second-mode branch also clears +0x98 of the object at +0xC4. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define B(p,n) (*(unsigned char *)((char *)(p)+(n)))
typedef struct CameraParams {
    short h0;
    short flags;
    float distance, height, f0c, f10;
    float f14;
    float f18;
} CameraParams;
typedef struct CameraOffsets {
    float position[4];
    char pad10[0x40-0x10];
    float vector40[4], vector50[4], vector60[4];
    char pad70[0x90-0x70];
    float vector90[4];
    char pada0[0xb0-0xa0];
    float distance;
    char padb4[0xe4-0xb4];
    float weight;
    char pade8[8];
    float fF0;
    int ticks;
    char padf8[8];
} CameraOffsets;
typedef struct FollowParameters {
    float vector[4], copy[4];
    char pad20[0xc];
    float distance, height;
    char pad34[0x90-0x34];
} FollowParameters;
typedef struct CameraRates {
    char pad0[0x30];
    int i30;
    char pad34[8];
    float f3c;
    int i40;
    float f44;
    char pad48[6];
    short h4e;
} CameraRates;
typedef struct CameraVars {
    float position[4];
    short h10, timer12, timer14, timer16;
    char pad18[8];
    CameraParams params;
    char pad3c[0x60-0x3c];
    CameraOffsets offsets;
    FollowParameters follow;
    CameraRates rates;
    int state[5];
} CameraVars;
typedef struct CameraMoby {
    char pad0[0x30];
    float position[4];
    char pad40[0x70-0x40];
    CameraVars *vars;
} CameraMoby;
typedef struct HeroCameraSource {
    char pad0[0x80];
    float position[4];
    char pad90[0x21a-0x90];
    short h21a;
    char pad21c[0x2c0-0x21c];
    float direction[4];
    char pad2d0[0x340-0x2d0];
    int i340;
    char pad344[0x574-0x344];
    float f574;
    char pad578[0x1450-0x578];
    char *p1450;
    short h1454;
    char pad1456[0x2290-0x1456];
    char *p2290;
    int state;
    int i2298;
    int move_state;
    char pad22a0[0x22b4-0x22a0];
    unsigned char b22b4;
    char pad22b5[0x24a0-0x22b5];
    int i24a0;
} HeroCameraSource;
extern HeroCameraSource g_hero_state;
typedef struct CameraInput {
    char pad0[0x100];
    float stick_x, stick_y;
    char pad108[0x1a0-0x108];
    int buttons;
} CameraInput;
extern CameraInput g_pad_state;
extern int g_current_map_index MACRO_ADDR;
typedef struct CameraHooks {
    char pad0[0x10];
    void (*update)(void);
} CameraHooks;
typedef struct FollowCameraGlobal {
    char pad0[0x284];
    char *target;
    int target_ticks;
    char pad28c[0x3a0-0x28c];
    CameraHooks hooks;
    char pad3b4[0x404-0x3b4];
    int state;
} FollowCameraGlobal;
extern FollowCameraGlobal g_scalar_transition_state;
typedef struct CameraInputSamples {
    char pad0[0xac];
    float samples[5];
    char padc0[4];
    char *pC4;
    char padc8[0x264-0xc8];
    int state;
} CameraInputSamples;
extern CameraInputSamples g_camera_move_state;
extern int g_hero_locked_flag;
extern char *g_area_hit_targets[];
extern float g_camera_default_view_y __attribute__((sda)), g_cam_follow_aim_distance __attribute__((sda)), g_cam_follow_distance_target __attribute__((sda));
extern float g_cam_follow_height_target __attribute__((sda)), g_cam_follow_rate_b __attribute__((sda)), g_cam_follow_rate_a __attribute__((sda));
extern float g_cam_follow_timer_threshold __attribute__((sda)), g_cam_follow_speed_max __attribute__((sda));
extern int g_cam_follow_mode_flag __attribute__((sda));
extern float g_follow_cam_lerp_factor;
extern int cam_update_overrides(void);
extern int math_fast_float_d(int *);
extern int FastDecTimer(short *);
extern float math_fabs(float), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float,float), FastDiffRots(float,float), IntToFloat(int);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *), FastVecSub(void *,void *,void *);
extern int coll_process_hit(void *,int,int,int,float);
extern char *moby_get_private_value_0(char *);
extern void cam_follow_update_orientation(int);
/* func_L00_00424BB8 in most levels; its twin func_L16_0042FB58 in levels 16, 22, 23 and 26. */
extern void ref_L00_004224D0_00(float,float);
extern void cam_set_tuning_value(float);
extern void cam_set_input_flags(void),cam_set_lock_flag(void),cam_set_snap_flag(void);
extern void cam_set_strength_and_steer(char *,float,float),cam_set_strength_and_steer_target(char *,float,float);
extern void follow_camera_set_height(float,float),follow_camera_set_distance(int,float,float);
extern void cam_set_aim_offset_target(int,float,float),cam_set_speeds_if_nonzero(float,float);
extern void set_follow_camera_orbit_clamp_mode(int);

/* Per-frame follow camera update (US2 copy of cam_follow_update): applies the camera settings for the hero's current state, tracks the lock-on target and eases the follow speed. */
void cam_follow_update_us2(CameraMoby *camera_moby)
{
    float temp[4];
    char *target;
    CameraVars *cam_vars=camera_moby->vars;
    int *state=cam_vars->state;
    CameraRates *cam_rates=&cam_vars->rates;
    CameraOffsets *cam_offsets=&cam_vars->offsets;
    int special=0, mode=cam_update_overrides(), i, count;
    float value,ratio;
    if (g_hero_state.state==124 || g_hero_state.state==120) cam_rates->h4e=1;
    if (!g_hero_state.i340 || cam_offsets->ticks) {
        float value=cam_offsets->fF0;
        if (value>2.0f) value=2.0f;
        cam_offsets->weight=(g_camera_default_view_y-0.002f)*(value*0.5f)+0.002f;
        if (g_hero_state.i340) math_fast_float_d(&cam_offsets->ticks);
        else cam_offsets->ticks=15;
    }
    if (g_hero_state.move_state==30) {
        camera_moby->vars->offsets.distance=0.75f;
        ref_L00_004224D0_00(0.04f,0.2f);
    }
    if (g_current_map_index==1 && g_hero_state.state==48 && g_hero_state.position[2]>75.0f && g_hero_state.position[2]<105.0f) {
        cam_set_tuning_value(0.8726646900177002f);
        cam_set_input_flags();
    }
    if (g_hero_state.i24a0==13 && g_hero_state.h21a) {
        value=FastAddRotations(g_hero_state.f574,3.1415929794311523f);
        temp[0]=math_fast_sin_or_cos_a(value);
        temp[1]=math_fast_sin_or_cos_b(value);
        temp[2]=0;
        cam_set_strength_and_steer((char *)temp,0.20943953f,temp[2]);
        cam_set_lock_flag();
    }
    if (g_hero_state.move_state==17) {
        camera_moby->vars->offsets.distance=0.25f;
        follow_camera_set_height(0.5f,0.003f);
    }
    if (g_hero_state.move_state==5 && !g_hero_locked_flag) {
        CameraOffsets *special_offsets=&camera_moby->vars->offsets; special=1;
        if (g_hero_state.b22b4==1 && mode==-1) {
            special_offsets->distance=0.25f;
            follow_camera_set_height(1.5f,0.003f);
        } else {
            special_offsets->distance=0.25f;
            follow_camera_set_height(2.5f,0.003f);
        }
    }
    if (g_hero_state.move_state==16) camera_moby->vars->offsets.distance=0.25f;
    if (g_hero_state.b22b4==1) {
        if (!state[0] && mode==-1) {
            CameraOffsets *follow_offsets=&camera_moby->vars->offsets;
            follow_camera_set_distance(1,3.0f,0.003f);
            if (!special) { follow_offsets->distance=1.0f;follow_camera_set_height(1.0f,0.003f); }
        }
        camera_moby->vars->rates.f3c=0.6f;
    }
    if (g_hero_state.b22b4==2) {
        CameraInputSamples *cam=&g_camera_move_state;
        if (state[4]<2) {
            cam_set_aim_offset_target(0,g_cam_follow_aim_distance,0.005f);
            follow_camera_set_distance(1,g_cam_follow_distance_target,0.003f);
            follow_camera_set_height(g_cam_follow_height_target,0.003f);
            if (cam->state<2) {
                CameraVars *base=camera_moby->vars;
                FollowParameters *follow=&base->follow;
                float *pos=camera_moby->position,*dir=g_hero_state.position,*aim=cam_offsets->vector50;
                follow->distance=g_cam_follow_distance_target;
                follow->height=g_cam_follow_height_target;
                cam_offsets->distance=g_cam_follow_aim_distance;
                cam_follow_update_orientation(1);
                {
                CameraRates *rates=&camera_moby->vars->rates;
                CameraVars *vars=camera_moby->vars;
                CameraParams *params=&vars->params;
                FastVecScale(temp,g_hero_state.direction,-follow->height);
                FastVecAdd(aim,dir,temp);
                FastVecSub(follow,pos,aim);
                qcopy(base->follow.copy,follow->vector);
                FastVecScale(temp,g_hero_state.direction,-cam_offsets->distance);
                FastVecAdd(cam_offsets->vector40,dir,temp);
                qcopy(cam_offsets->vector90,cam_offsets->vector40);
                qcopy(cam_offsets->position,dir);
                qcopy(cam_offsets->vector60,cam_offsets->position);
                qcopy(vars,pos);
                qcopy((char *)vars+0x210,pos);
                rates->i30=0;params->f14=0.0f;
                params->distance=cam_offsets->distance;
                {
                    float zero=params->f14;
                    params->height=follow->height;
                    params->flags=0;
                    params->f18=zero;
                    params->f10=zero;
                    params->f0c=zero;
                }
                }
            }
        }
        cam_set_snap_flag();
        target=cam->pC4;
        if (target) *(int *)(target+0x98)=0;
        {
            CameraRates *rates=&camera_moby->vars->rates;
            rates->f3c=g_cam_follow_rate_a;
            rates->f44=g_cam_follow_rate_b;
        }
    }
    {
    CameraHooks *hooks=&g_scalar_transition_state.hooks;
    FollowCameraGlobal *camera;
    if (hooks->update) hooks->update();
    camera=(FollowCameraGlobal *)((char *)hooks-0x3a0);
    target=camera->target;
    if (target && state[4]<2) {
        int target_state=B(target,0x20);
        if (target_state==254) camera->target=0;
        else if (target_state==253) camera->target=0;
        else {
            if (math_fabs(g_pad_state.stick_x)>=0.3f || math_fabs(g_pad_state.stick_y)>=0.3f) camera->target_ticks=640;
            if (g_scalar_transition_state.target_ticks>400) {
                math_fast_float_d(&g_scalar_transition_state.target_ticks);
                if (g_scalar_transition_state.target_ticks<401) g_scalar_transition_state.target_ticks=0;
            } else {
                g_scalar_transition_state.target_ticks++;
                if (g_scalar_transition_state.target_ticks>400) g_scalar_transition_state.target_ticks=400;
                value=IntToFloat(g_scalar_transition_state.target_ticks);value/=IntToFloat(400);
                cam_set_strength_and_steer_target(g_scalar_transition_state.target+0x10,value*1.5707964897155762f,0.0f);
                cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
            }
        }
    }
    }
    if (g_hero_state.p1450 && *(signed char *)(g_hero_state.p1450+0x20)>=0) {
        g_scalar_transition_state.target_ticks++;
        if (g_scalar_transition_state.target_ticks>400) g_scalar_transition_state.target_ticks=400;
        value=IntToFloat(g_scalar_transition_state.target_ticks);value/=IntToFloat(400);
        cam_set_strength_and_steer_target(g_hero_state.p1450+0x10,value*1.5707964897155762f,0.0f);
        cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
    }
    if (!g_scalar_transition_state.target && !g_hero_state.p1450) g_scalar_transition_state.target_ticks=0;
    if (g_hero_state.state==129) {
        cam_set_lock_flag();cam_set_speeds_if_nonzero(1,1);
        ref_L00_004224D0_00(0.06f,0.2f);cam_set_snap_flag();
    }
    if (g_hero_state.state==123) {
        cam_set_speeds_if_nonzero(0.04f,0.2f);
        cam_set_strength_and_steer(g_hero_state.p2290+0xc0,0.7853982448577881f,0);
        follow_camera_set_distance(0,3,0.003f);cam_set_snap_flag();
    }
    if (state[4]<2 && g_hero_state.state!=129 &&
        (g_hero_state.state==126 || g_hero_state.state==130 || g_hero_state.h1454) && (g_pad_state.buttons&3)) {
        CameraVars *reset_vars;
        set_follow_camera_orbit_clamp_mode(0);cam_set_lock_flag();cam_set_speeds_if_nonzero(0.04f,0.2f);
        reset_vars=camera_moby->vars;reset_vars->timer16=0;reset_vars->timer12=0;reset_vars->timer14=0;
    } else if (g_cam_follow_mode_flag) {
        CameraVars *timer_vars=camera_moby->vars;
        CameraInputSamples *cam=&g_camera_move_state;
        value=0;
        for(i=0;i<4;i++) { temp[i]=FastDiffRots(cam->samples[i],cam->samples[i+1]);value+=temp[i]; }
        ratio=5.0f;value*=0.25f;ratio=value*ratio;if(ratio>1)ratio=1;ratio=1-ratio;
        if (ratio<g_cam_follow_timer_threshold) timer_vars->timer12=32;
        if (timer_vars->timer12) {
            if (FastDecTimer(&timer_vars->timer12)) timer_vars->timer14=45;
            cam_set_lock_flag();timer_vars->timer16++;
            if (timer_vars->timer16>30) timer_vars->timer16=30;
            value=IntToFloat(timer_vars->timer16);value/=IntToFloat(30);
            cam_set_speeds_if_nonzero((g_cam_follow_speed_max-0.015f)*value+0.015f,0.2f);
            g_follow_cam_lerp_factor=0;
        } else {
            if (timer_vars->timer14) {
                FastDecTimer(&timer_vars->timer14);
                value=IntToFloat(timer_vars->timer14);value/=IntToFloat(45);
                value*=-0.85f;
                value+=0.85f;
                g_follow_cam_lerp_factor=value;
                timer_vars->timer16=0;
            } else {
                timer_vars->timer16=0;
                g_follow_cam_lerp_factor=0.85f;
            }
        }
    }
    state[4]=0;
    count=coll_process_hit(g_hero_state.position,1,(int)g_hero_state.p2290,0,15.0f);
    if (count>0) {
    int target_index;
    for(target_index=0;target_index<count;target_index++) {
        char *candidate=moby_get_private_value_0(g_area_hit_targets[target_index]);
        if (candidate && (float)B(candidate,0xd)!=0.0f) { state[4]=1;break; }
    }
    }
}
