/* func_US2_L00_004239D0, the USA v2.00 copy of func_L00_004224D0: the same C, where the state test reads
   D_L00_001B8E20 (+0x264) through a local and the second-mode branch also clears +0x98 of the object at +0xC4. */
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
extern FollowCameraGlobal D_L00_001B8C80;
typedef struct CameraInputSamples {
    char pad0[0xac];
    float samples[5];
    char padc0[4];
    char *pC4;
    char padc8[0x264-0xc8];
    int state;
} CameraInputSamples;
extern CameraInputSamples D_L00_001B8E20;
extern int D_L00_001A8FF0;
extern char *g_area_hit_targets[];
extern float D_L00_001B14A4 __attribute__((sda)), D_L00_001B1594 __attribute__((sda)), D_L00_001B1598 __attribute__((sda));
extern float D_L00_001B159C __attribute__((sda)), D_L00_001B15A0 __attribute__((sda)), D_L00_001B15A4 __attribute__((sda));
extern float D_L00_001B1578 __attribute__((sda)), D_L00_001B157C __attribute__((sda));
extern int D_L00_001B1590 __attribute__((sda));
extern float D_L00_001A8900;
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

void func_US2_L00_004239D0(CameraMoby *obj)
{
    float local[4];
    char *target;
    CameraVars *p=obj->vars;
    int *state=p->state;
    CameraRates *r=&p->rates;
    CameraOffsets *q=&p->offsets;
    int special=0, mode=cam_update_overrides(), i, count;
    float a,b;
    if (g_hero_state.state==124 || g_hero_state.state==120) r->h4e=1;
    if (!g_hero_state.i340 || q->ticks) {
        float a=q->fF0;
        if (a>2.0f) a=2.0f;
        q->weight=(D_L00_001B14A4-0.002f)*(a*0.5f)+0.002f;
        if (g_hero_state.i340) math_fast_float_d(&q->ticks);
        else q->ticks=15;
    }
    if (g_hero_state.moveState==30) {
        obj->vars->offsets.distance=0.75f;
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
        obj->vars->offsets.distance=0.25f;
        follow_camera_set_height(0.5f,0.003f);
    }
    if (g_hero_state.moveState==5 && !D_L00_001A8FF0) {
        CameraOffsets *specialVars=&obj->vars->offsets; special=1;
        if (g_hero_state.b22b4==1 && mode==-1) {
            specialVars->distance=0.25f;
            follow_camera_set_height(1.5f,0.003f);
        } else {
            specialVars->distance=0.25f;
            follow_camera_set_height(2.5f,0.003f);
        }
    }
    if (g_hero_state.moveState==16) obj->vars->offsets.distance=0.25f;
    if (g_hero_state.b22b4==1) {
        if (!state[0] && mode==-1) {
            CameraOffsets *followVars=&obj->vars->offsets;
            follow_camera_set_distance(1,3.0f,0.003f);
            if (!special) { followVars->distance=1.0f;follow_camera_set_height(1.0f,0.003f); }
        }
        obj->vars->rates.f3c=0.6f;
    }
    if (g_hero_state.b22b4==2) {
        CameraInputSamples *cam=&D_L00_001B8E20;
        if (state[4]<2) {
            cam_set_aim_offset_target(0,D_L00_001B1594,0.005f);
            follow_camera_set_distance(1,D_L00_001B1598,0.003f);
            follow_camera_set_height(D_L00_001B159C,0.003f);
            if (cam->state<2) {
                CameraVars *base=obj->vars;
                FollowParameters *follow=&base->follow;
                float *pos=obj->position,*dir=g_hero_state.position,*aim=q->vector50;
                follow->distance=D_L00_001B1598;
                follow->height=D_L00_001B159C;
                q->distance=D_L00_001B1594;
                cam_follow_update_orientation(1);
                {
                CameraRates *rates=&obj->vars->rates;
                CameraVars *vars=obj->vars;
                CameraParams *params=&vars->params;
                FastVecScale(local,g_hero_state.direction,-follow->height);
                FastVecAdd(aim,dir,local);
                FastVecSub(follow,pos,aim);
                qcopy(base->follow.copy,follow->vector);
                FastVecScale(local,g_hero_state.direction,-q->distance);
                FastVecAdd(q->vector40,dir,local);
                qcopy(q->vector90,q->vector40);
                qcopy(q->position,dir);
                qcopy(q->vector60,q->position);
                qcopy(vars,pos);
                qcopy((char *)vars+0x210,pos);
                rates->i30=0;params->f14=0.0f;
                params->distance=q->distance;
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
            CameraRates *rates=&obj->vars->rates;
            rates->f3c=D_L00_001B15A4;
            rates->f44=D_L00_001B15A0;
        }
    }
    {
    CameraHooks *hooks=&D_L00_001B8C80.hooks;
    FollowCameraGlobal *camera;
    if (hooks->update) hooks->update();
    camera=(FollowCameraGlobal *)((char *)hooks-0x3a0);
    target=camera->target;
    if (target && state[4]<2) {
        int targetState=B(target,0x20);
        if (targetState==254) camera->target=0;
        else if (targetState==253) camera->target=0;
        else {
            if (math_fabs(g_pad_state.stickX)>=0.3f || math_fabs(g_pad_state.stickY)>=0.3f) camera->targetTicks=640;
            if (D_L00_001B8C80.targetTicks>400) {
                math_fast_float_d(&D_L00_001B8C80.targetTicks);
                if (D_L00_001B8C80.targetTicks<401) D_L00_001B8C80.targetTicks=0;
            } else {
                D_L00_001B8C80.targetTicks++;
                if (D_L00_001B8C80.targetTicks>400) D_L00_001B8C80.targetTicks=400;
                a=IntToFloat(D_L00_001B8C80.targetTicks);a/=IntToFloat(400);
                cam_set_strength_and_steer_target(D_L00_001B8C80.target+0x10,a*1.5707964897155762f,0.0f);
                cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
            }
        }
    }
    }
    if (g_hero_state.p1450 && *(signed char *)(g_hero_state.p1450+0x20)>=0) {
        D_L00_001B8C80.targetTicks++;
        if (D_L00_001B8C80.targetTicks>400) D_L00_001B8C80.targetTicks=400;
        a=IntToFloat(D_L00_001B8C80.targetTicks);a/=IntToFloat(400);
        cam_set_strength_and_steer_target(g_hero_state.p1450+0x10,a*1.5707964897155762f,0.0f);
        cam_set_lock_flag();cam_set_speeds_if_nonzero(0.03f,0.2f);
    }
    if (!D_L00_001B8C80.target && !g_hero_state.p1450) D_L00_001B8C80.targetTicks=0;
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
        CameraVars *resetVars;
        set_follow_camera_orbit_clamp_mode(0);cam_set_lock_flag();cam_set_speeds_if_nonzero(0.04f,0.2f);
        resetVars=obj->vars;resetVars->timer16=0;resetVars->timer12=0;resetVars->timer14=0;
    } else if (D_L00_001B1590) {
        CameraVars *timerVars=obj->vars;
        CameraInputSamples *cam=&D_L00_001B8E20;
        a=0;
        for(i=0;i<4;i++) { local[i]=FastDiffRots(cam->samples[i],cam->samples[i+1]);a+=local[i]; }
        b=5.0f;a*=0.25f;b=a*b;if(b>1)b=1;b=1-b;
        if (b<D_L00_001B1578) timerVars->timer12=32;
        if (timerVars->timer12) {
            if (FastDecTimer(&timerVars->timer12)) timerVars->timer14=45;
            cam_set_lock_flag();timerVars->timer16++;
            if (timerVars->timer16>30) timerVars->timer16=30;
            a=IntToFloat(timerVars->timer16);a/=IntToFloat(30);
            cam_set_speeds_if_nonzero((D_L00_001B157C-0.015f)*a+0.015f,0.2f);
            D_L00_001A8900=0;
        } else {
            if (timerVars->timer14) {
                FastDecTimer(&timerVars->timer14);
                a=IntToFloat(timerVars->timer14);a/=IntToFloat(45);
                a*=-0.85f;
                a+=0.85f;
                D_L00_001A8900=a;
                timerVars->timer16=0;
            } else {
                timerVars->timer16=0;
                D_L00_001A8900=0.85f;
            }
        }
    }
    state[4]=0;
    count=coll_process_hit(g_hero_state.position,1,(int)g_hero_state.p2290,0,15.0f);
    if (count>0) {
    int targetIndex;
    for(targetIndex=0;targetIndex<count;targetIndex++) {
        char *candidate=moby_get_private_value_0(g_area_hit_targets[targetIndex]);
        if (candidate && (float)B(candidate,0xd)!=0.0f) { state[4]=1;break; }
    }
    }
}
