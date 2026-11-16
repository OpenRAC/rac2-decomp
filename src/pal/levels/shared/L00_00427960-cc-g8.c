/* func_PAL_L00_00427960, the PAL copy of func_L00_004224D0: the same C. */
#include "common.h"
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
    int moveState;
    char pad22a0[0x22b4-0x22a0];
    unsigned char b22b4;
    char pad22b5[0x24a0-0x22b5];
    int i24a0;
} HeroCameraSource;
extern HeroCameraSource g_hero_state;
typedef struct CameraInput {
    char pad0[0x100];
    float stickX, stickY;
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
    int targetTicks;
    char pad28c[0x3a0-0x28c];
    CameraHooks hooks;
    char pad3b4[0x404-0x3b4];
    int state;
} FollowCameraGlobal;
extern FollowCameraGlobal g_scalar_transition_state;
typedef struct CameraInputSamples {
    char pad0[0xac];
    float samples[5];
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

/* Per-frame update of the follow camera: applies the hero state's distance, height and aim overrides,
   eases toward a locked target, tracks the stick and checks the area for hits on the camera. */
void cam_follow_update_pal(CameraMoby *moby)
{
    float local[4];
    CameraVars *cam_vars=moby->vars;
    int *state=cam_vars->state;
    CameraRates *base_rates=&cam_vars->rates;
    CameraOffsets *offsets=&cam_vars->offsets;
    int special=0, mode=cam_update_overrides(), i, count;
    float a,b;
    if (g_hero_state.state==124 || g_hero_state.state==120) base_rates->h4e=1;
    if (!g_hero_state.i340 || offsets->ticks) {
        float a=offsets->fF0;
        if (a>2.0f) a=2.0f;
        offsets->weight=(g_camera_default_view_y-0.002f)*(a*0.5f)+0.002f;
        if (g_hero_state.i340) math_fast_float_d(&offsets->ticks);
        else offsets->ticks=12;
    }
    if (g_hero_state.moveState==30) {
        moby->vars->offsets.distance=0.75f;
        ref_L00_004224D0_00(0.04f,0.2f);
    }
    if (g_current_map_index==1 && g_hero_state.state==48 && g_hero_state.position[2]>75.0f && g_hero_state.position[2]<105.0f) {
        cam_set_tuning_value(0.8726646900177002f);
        cam_set_input_flags();
    }
    if (g_hero_state.i24a0==13 && g_hero_state.h21a) {
        a=FastAddRotations(g_hero_state.f574,3.1415929794311523f);
        local[0]=math_fast_sin_or_cos_a(a);
        local[1]=math_fast_sin_or_cos_b(a);
        local[2]=0;
        cam_set_strength_and_steer((char *)local,0.20943953f,local[2]);
        cam_set_lock_flag();
    }
    if (g_hero_state.moveState==17) {
        moby->vars->offsets.distance=0.25f;
        follow_camera_set_height(0.5f,0.003f);
    }
    if (g_hero_state.moveState==5 && !g_hero_locked_flag) {
        CameraOffsets *special_vars=&moby->vars->offsets; special=1;
        if (g_hero_state.b22b4==1 && mode==-1) {
            special_vars->distance=0.25f;
            follow_camera_set_height(1.5f,0.003f);
        } else {
            special_vars->distance=0.25f;
            follow_camera_set_height(2.5f,0.003f);
        }
    }
    if (g_hero_state.moveState==16) moby->vars->offsets.distance=0.25f;
    if (g_hero_state.b22b4==1) {
        if (!state[0] && mode==-1) {
            CameraOffsets *follow_vars=&moby->vars->offsets;
            follow_camera_set_distance(1,3.0f,0.003f);
            if (!special) { follow_vars->distance=1.0f;follow_camera_set_height(1.0f,0.003f); }
        }
        moby->vars->rates.f3c=0.6f;
    }
    if (g_hero_state.b22b4==2) {
        if (state[4]<2) {
            cam_set_aim_offset_target(0,g_cam_follow_aim_distance,0.005f);
            follow_camera_set_distance(1,g_cam_follow_distance_target,0.003f);
            follow_camera_set_height(g_cam_follow_height_target,0.003f);
            if (g_scalar_transition_state.state<2) {
                CameraVars *base=moby->vars;
                FollowParameters *follow=&base->follow;
                float *pos=moby->position,*dir=g_hero_state.position,*aim=offsets->vector50;
                follow->distance=g_cam_follow_distance_target;
                follow->height=g_cam_follow_height_target;
                offsets->distance=g_cam_follow_aim_distance;
                cam_follow_update_orientation(1);
                {
                CameraRates *rates=&moby->vars->rates;
                CameraVars *vars=moby->vars;
                CameraParams *params=&vars->params;
                FastVecScale(local,g_hero_state.direction,-follow->height);
                FastVecAdd(aim,dir,local);
                FastVecSub(follow,pos,aim);
                qcopy(base->follow.copy,follow->vector);
                FastVecScale(local,g_hero_state.direction,-offsets->distance);
                FastVecAdd(offsets->vector40,dir,local);
                qcopy(offsets->vector90,offsets->vector40);
                qcopy(offsets->position,dir);
                qcopy(offsets->vector60,offsets->position);
                qcopy(vars,pos);
                qcopy((char *)vars+0x210,pos);
                rates->i30=0;params->f14=0.0f;
                params->distance=offsets->distance;
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
        {
            CameraRates *rates=&moby->vars->rates;
            rates->f3c=g_cam_follow_rate_a;
            rates->f44=g_cam_follow_rate_b;
        }
    }
    {
    CameraHooks *hooks=&g_scalar_transition_state.hooks;
    FollowCameraGlobal *camera;
    char *target;
    if (hooks->update) hooks->update();
    camera=(FollowCameraGlobal *)((char *)hooks-0x3a0);
    target=camera->target;
    if (target && state[4]<2) {
        int target_state=B(target,0x20);
        if (target_state==254) camera->target=0;
        else if (target_state==253) camera->target=0;
        else {
            if (math_fabs(g_pad_state.stickX)>=0.3f || math_fabs(g_pad_state.stickY)>=0.3f) camera->targetTicks=533;
            if (g_scalar_transition_state.targetTicks>333) {
                math_fast_float_d(&g_scalar_transition_state.targetTicks);
                if (g_scalar_transition_state.targetTicks<334) g_scalar_transition_state.targetTicks=0;
            } else {
                g_scalar_transition_state.targetTicks++;
                if (g_scalar_transition_state.targetTicks>333) g_scalar_transition_state.targetTicks=333;
                a=IntToFloat(g_scalar_transition_state.targetTicks);a/=IntToFloat(333);
                cam_set_strength_and_steer_target(g_scalar_transition_state.target+0x10,a*1.5707964897155762f,0.0f);
                cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
            }
        }
    }
    }
    if (g_hero_state.p1450 && *(signed char *)(g_hero_state.p1450+0x20)>=0) {
        g_scalar_transition_state.targetTicks++;
        if (g_scalar_transition_state.targetTicks>333) g_scalar_transition_state.targetTicks=333;
        a=IntToFloat(g_scalar_transition_state.targetTicks);a/=IntToFloat(333);
        cam_set_strength_and_steer_target(g_hero_state.p1450+0x10,a*1.5707964897155762f,0.0f);
        cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
    }
    if (!g_scalar_transition_state.target && !g_hero_state.p1450) g_scalar_transition_state.targetTicks=0;
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
        reset_vars=moby->vars;reset_vars->timer16=0;reset_vars->timer12=0;reset_vars->timer14=0;
    } else if (g_cam_follow_mode_flag) {
        CameraVars *timer_vars=moby->vars;a=0;
        for(i=0;i<4;i++) { local[i]=FastDiffRots(g_camera_move_state.samples[i],g_camera_move_state.samples[i+1]);a+=local[i]; }
        b=5.0f;a*=0.25f;b=a*b;if(b>1)b=1;b=1-b;
        if (b<g_cam_follow_timer_threshold) timer_vars->timer12=27;
        if (timer_vars->timer12) {
            if (FastDecTimer(&timer_vars->timer12)) timer_vars->timer14=37;
            cam_set_lock_flag();timer_vars->timer16++;
            if (timer_vars->timer16>25) timer_vars->timer16=25;
            a=IntToFloat(timer_vars->timer16);a/=IntToFloat(25);
            cam_set_speeds_if_nonzero((g_cam_follow_speed_max-0.015f)*a+0.015f,0.2f);
            g_follow_cam_lerp_factor=0;
        } else {
            if (timer_vars->timer14) {
                FastDecTimer(&timer_vars->timer14);
                a=IntToFloat(timer_vars->timer14);a/=IntToFloat(37);
                a*=-0.85f;
                a+=0.85f;
                g_follow_cam_lerp_factor=a;
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
