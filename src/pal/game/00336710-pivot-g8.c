/* func_PAL_00336710, the PAL copy of func_00334A88: the same C, where the camera timers 15/16 become
   12/13 and three frame counts are scaled for 50 Hz (these counts are read here as int). */
#include "common.h"
typedef int Qword_34A88 __attribute__((mode(TI)));
typedef union { Qword_34A88 q; float f[4]; } V651;
typedef struct { char p0[0x31C]; float distance; char p320[0x28]; short h348,h34A,h34C,h34E; char p350[0x14E]; unsigned char b49E; char p49F[15]; short h4AE; char p4B0[0x1DE4]; int i2294; } Hero651;
extern Hero651 g_hero_state;
extern char g_camera_follow_state[];
extern int g_ground_check_inhibit;
extern float g_cam_pivot_offset_scale __attribute__((sda));
extern int g_cam_pivot_mode_value __attribute__((sda)), g_cam_pivot_state_value_a __attribute__((sda)), g_cam_pivot_state_value_b __attribute__((sda)), g_cam_pivot_state_value_c __attribute__((sda)), g_cam_pivot_state_half __attribute__((sda));
extern float g_cam_pivot_angle_limit_a __attribute__((sda)), g_cam_pivot_angle_limit_b __attribute__((sda)), g_cam_pivot_lerp_factor __attribute__((sda));
extern float FastVecDot(void *, void *), FastVecLength(void *), IntToFloat(int), cam_compute_signed_angle_to_point(void *,float);
extern int FloatToInt(float), coll_test_point(void *,int,int,float),FastDecTimer(void *),cam_resolve_position(void *,int);
extern void FastVecScale(void *,void *,float),FastVecSub(void *,void *,void *),lerp_vector(void *,void *,void *,float);
extern void hero_copy_vector_to_out(int, Qword_34A88 *);
extern void cam_compute_offset(void *,int,float);
#define H651(p,o) (*(short *)((p)+(o)))
#define F651(p,o) (*(float *)((p)+(o)))
#define I651(p,o) (*(int *)((p)+(o)))
#define B651(p,o) (*(unsigned char *)((p)+(o)))
/* Updates the camera pivot offset for the object, blending between the camera, hero and state
 * vectors by the pivot state (PAL: 50 Hz timings). */
void cam_update_pivot_state_pal(char *obj, void *out)
{
    V651 base, temp;

    char *cam = g_camera_follow_state;
    char *state = *(char **)(obj+0x70)+0x60;
    char *axis;
    int mode, blocked;
    float factor;
    if (g_hero_state.h348 || g_ground_check_inhibit || (H651(state,0xEE) && g_hero_state.h34E)) {
        H651(state,0xEC)=12;
        B651(state,0xD6)=1;
        H651(state,0xEE)=1;
        FastVecScale(state+0x10,cam+0x30,FastVecDot(state,cam+0x30));
        qcopy(state+0x20,state+0x10);
        mode=B651(state,0xC4);
        axis=cam+0x30;
        if ((unsigned)(mode-5)<3 || mode==3)
            cam_compute_offset(state+0x30,1,g_cam_pivot_offset_scale*0.5f);
    } else {
        if (H651(state,0xEE)==1) {
            FastVecScale(state+0x10,cam+0x30,FastVecDot(state,cam+0x30));
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=cam+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                cam_compute_offset(state+0x30,1,g_cam_pivot_offset_scale*0.5f);
            factor=IntToFloat(H651(state,0xD8))/IntToFloat(12);
            H651(state,0xD8)=FloatToInt(IntToFloat(H651(state,0xEC))*factor);
            H651(state,0xEE)=2;
        } else {
            axis=cam+0x30;
            if (H651(state,0xEE)>=2) {
            factor=FastVecDot(state,axis);
            FastVecScale(state+0x10,axis,factor);
            qcopy(state+0x20,state+0x10);
            mode=B651(state,0xC4);
            axis=cam+0x30;
            if ((unsigned)(mode-5)<3 || mode==3)
                cam_compute_offset(state+0x30,1,g_cam_pivot_offset_scale*0.5f);
            if (++H651(state,0xEE)>=13) H651(state,0xEE)=0;
            }
        }
    }
    hero_copy_vector_to_out((int)obj,&base.q);
    if (g_hero_state.i2294==0x74) {
        FastVecScale(out,axis,FastVecDot(state,axis));
        FastVecSub(state,state,out);
        FastVecScale(out,axis,FastVecDot(axis,state+0x60));
        qcopy(state+0x10,out);
        if (B651(state,0xC4)!=11) {
            char *timer_state;
            B651(state,0xC4)=11;
            qcopy(obj+0x40,obj);
            timer_state=*(char **)(obj+0x70)+0x20;
            H651(timer_state,0)=((s32)(g_cam_pivot_mode_value) * 5 + 2) / 6;
            F651(timer_state,0x24)=1.0f/IntToFloat(H651(timer_state,0));
        }
        return;
    }
    switch (B651(state,0xC4)) {
    case 2: {
        float angle;
        if (g_hero_state.i2294==17 || (g_hero_state.b49E && g_hero_state.distance>0.2f && ((angle=cam_compute_signed_angle_to_point(obj,F651(state,0xB0)))<g_cam_pivot_angle_limit_b || angle>g_cam_pivot_angle_limit_a))) {
            B651(state,0xC4)=1;
            H651(state,0xC6)=g_cam_pivot_state_value_a;
            F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
        }
        blocked=0;
        if (g_hero_state.h34C && (!g_hero_state.b49E || g_hero_state.h4AE>=16)) blocked=1;
        else if (cam_resolve_position(&temp,1)!=1) blocked=1;
        else {
            factor=FastVecDot(&temp,axis);
            if (factor<FastVecLength(state+0x10)) blocked=1;
        }
        if (blocked) {
            qcopy(out,state+0x10);
            factor=FastVecDot(&base,axis);
            FastVecScale(&temp,axis,factor);
            FastVecSub(state,&base,&temp);
        } else {
            cam_resolve_position(&temp,1);
            FastVecScale(out,axis,FastVecDot(&temp,axis));
            FastVecSub(state,&temp,out);
        }
        break;
    }
    case 3: case 5: case 6: case 7:
        lerp_vector(state+0x10,state+0x30,state+0x20,(float)H651(state,0xD4)*F651(state,0xCC));
        if (!B651(state,0xD7) && coll_test_point(obj+0x30,18,0,0.2f)) {
            qcopy(state+0x30,state+0x10); B651(state,0xD7)=1;
        }
        qcopy(out,state+0x10);
        factor=FastVecDot(&base,axis);
        FastVecScale(&temp,axis,factor);
        FastVecSub(state,&base,&temp);
        if (FastDecTimer(state+0xD4)) {
            if (B651(state,0xC4)==9) {
                B651(state,0xC4)=10; H651(state,0xD4)=((s32)(g_cam_pivot_state_half) * 5 + 2) / 6;
                qcopy(state+0x20,state+0x10);
                FastVecScale(&temp,axis,F651(state,0xD0));
                FastVecSub(state+0x30,state+0x20,&temp);
            } else if (B651(state,0xC4)==6) {
                B651(state,0xC4)=7; H651(state,0xD4)=((s32)(g_cam_pivot_state_value_b) * 5 + 2) / 6;
                qcopy(state+0x30,state+0x20); qcopy(state+0x20,state+0x10);
            } else {
                B651(state,0xC4)=4; H651(state,0xC6)=g_cam_pivot_state_value_c;
                F651(state,0xC8)=1.0f/IntToFloat(H651(state,0xC6));
            }
        }
        break;
    case 8:
        qcopy(out,state+0x10);
        factor=FastVecDot(&base,axis);
        FastVecScale(&temp,axis,factor);
        FastVecSub(state,&base,&temp);
        break;
    case 9: case 10:
        FastVecScale(out,axis,FastVecDot(&base,axis));
        FastVecSub(state,&base,out);
        lerp_vector(out,out,state+0x20,g_cam_pivot_lerp_factor);
        break;
    default:
        FastVecScale(out,axis,FastVecDot(&base,axis));
        FastVecSub(state,&base,out);
        break;
    }
}
