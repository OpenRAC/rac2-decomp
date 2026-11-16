#include "names.h"
/* func_PAL_L00_0042B1E8, the PAL copy of func_L00_00425CD0: the same C, where func_L00_00425A98
   becomes func_PAL_L00_0042AFB0. */
#include "include_asm.h"
#include "common.h"
extern char g_camera_move_state[], g_hero_l00_position[], g_collision_position[];
extern int g_current_map_index;
extern char *g_hero_moby NOT_SDA;
extern float g_cam_eye_spring_stiffness __attribute__((sda)), g_cam_eye_spring_damping __attribute__((sda));
extern float g_cam_eye_turn_spring_stiffness __attribute__((sda)), g_cam_eye_turn_spring_damping __attribute__((sda));
extern void FastVecAdd(void *,void *,void *), FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float),FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float),math_apply_axis_rotation_to_quat(void *,void *,void *,float);
extern float FastVecLength(void *),FastVecDot(void *,void *),math_fabs(float),math_fast_angle_helper(float);
extern float math_step_spring_damper_clamped(void *,float,float,float,float,float),math_step_spring_damper_stored(void *,float,float,float,float,float);
extern int coll_test_point(void *,int,int,float);
extern void cam_follow_get_ease_speeds_pal(char *,float *,float *);
#define F(p,n) (*(float *)((char *)(p)+(n)))
#define P(p,n) (*(char **)((char *)(p)+(n)))
/* Moves the follow camera eye: springs its distance and both turn angles toward the wanted vector, then
   pushes the eye out of walls and shifts the camera blocks by the same step (PAL: 50 Hz values). */
void cam_follow_move_eye_pal(char *moby)
{
    char *base=P(moby,112), *move=base+352, *pos=base+96, *camera=g_camera_move_state;
    char along1[16],flat1[16],along2[16],flat2[16],cross[16],dir[16],height_off[16],base_pos[16],saved[16],delta[16];
    float out1,out2;
    float len1,len2,vert1,angle1,angle2,dot2,len,angle,turn;
    int changed,i;
    float ratio, sign;
    FastVecAdd(base,base+176,move);
    len1=FastVecLength(move);
    len2=FastVecLength(move+16);
    angle2=0.0f;
    cam_follow_get_ease_speeds_pal(moby,&out1,&out2);
    len2=math_step_spring_damper_clamped(move+40,len2,len1,out1,out2,angle2);
    vert1=FastVecDot(move,camera+32);
    if(math_fabs(len1)<0.0001f) angle1=0.0f;
    else {
        ratio=vert1/len1;
        if(ratio>1.0f) ratio=1.0f;
        else if(ratio< -1.0f) ratio= -1.0f;
        angle1=math_fast_angle_helper(ratio);
    }
    len1=FastVecDot(move+16,camera+32);
    if(math_fabs(len2)<0.0001f) angle2=0.0f;
    else {
        ratio=len1/len2;
        if(ratio>1.0f) ratio=1.0f;
        else if(ratio< -1.0f) ratio= -1.0f;
        angle2=math_fast_angle_helper(ratio);
    }
    turn=math_step_spring_damper_stored(move+36,angle2,angle1,g_cam_eye_turn_spring_stiffness,g_cam_eye_turn_spring_damping,0.0f);
    FastVecScale(along1,camera+32,vert1);
    FastVecSub(flat1,move,along1);
    FastVecScale(along2,camera+32,len1);
    FastVecSub(flat2,move+16,along2);
    vert1=FastVecDot(flat1,flat2);
    len=FastVecLength(flat1);
    len*=FastVecLength(flat2);
    {
        float raw;
        if(len<0.0001f) raw=0.0f;
        else raw=1.5707963705062866f-math_fast_angle_helper(vert1/len);
        angle=math_step_spring_damper_stored(move+32,0.0f,raw,g_cam_eye_spring_stiffness,g_cam_eye_spring_damping,0.0f);
    }
    FastVecCross(cross,flat2,camera+32);
    dot2=FastVecDot(cross,flat1);
    sign=-1.0f;
    if(dot2>=0.0f) sign=1.0f;
    math_apply_axis_rotation_to_quat(dir,flat2,camera+32,angle*sign);
    FastVecCross(cross,camera+32,dir);
    math_apply_axis_rotation_to_quat(dir,dir,cross,turn);
    vec_scale_to_length(move+16,dir,len2);
    FastVecScale(height_off,camera+32,F(move,48));
    FastVecAdd(base_pos,height_off,pos+96);
    FastVecAdd(moby+48,base_pos,move+16);
    qcopy(saved,moby+48);
    changed=0;
    if(g_current_map_index==13 && F(g_hero_moby,24)<120.0f) {
        int j=0;
        while(j<3) {
            if(coll_test_point(moby+48,54,0,0.3f)) {
                changed=1;
                qcopy(moby+48,g_collision_position);
                j++;
            } else break;
        }
    } else {
        i=0;
        do {
            if(!coll_test_point(moby+48,54,0,0.25f)) break;
            FastVecSub(delta,g_hero_l00_position,moby+48);
            vec_scale_to_length(delta,delta,1.0f);
            if(math_fabs(FastVecDot(moby+32,delta))<=0.5f) break;
            changed=1;
            qcopy(moby+48,g_collision_position);
        } while(++i<3);
    }
    if(changed) {
        FastVecSub(delta,moby+48,saved);
        FastVecAdd(pos,pos,delta);
        FastVecAdd(pos+96,pos+96,delta);
        FastVecAdd(pos+144,pos+144,delta);
        FastVecAdd(pos+48,pos+48,delta);
    }
}
