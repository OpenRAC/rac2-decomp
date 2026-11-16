#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char pad0[0x80]; Vec position; unsigned char pad90[0x294];
    float pitch; unsigned char pad328[0x20]; short allowed;
    unsigned char pad34a[0x1f46]; char *object;
} PlayerView;
extern PlayerView g_hero_state;
extern int g_aim_l14_blocked_flag;
extern int g_aim_extra_blocked_flag __attribute__((sda));
extern float g_aim_l14_cone_angle __attribute__((sda)),g_aim_l14_max_distance __attribute__((sda));
extern char *g_target_l14_list[];
extern Vec g_aim_ray_start;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; } Collision;
extern Collision g_projectile_l14_collision;
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern char *moby_get_private_value_0(char *);
extern float mat_fast_helper_a(float,float),FastDiffRots(float,float),math_fabs(float),math_fast_angle_helper(float),IntToFloat(int);
extern float vec_distance_xy(void *,void *),fast_vec_dist(void *,void *),FastVecDot(void *,void *),FastVecLength(void *);
extern void vec_build_spherical_offset(void *,float,float,float);

/* Target selection: the nearest visible candidate in front of the player within the aim cone. */
char *hero_l14_find_aim_target_in_cone(char *obj,Vec *origin,float *yaw,float *pitch) {
    struct { Vec origin,offset,player; char *disabled[128]; Vec target,aim,ray,axis; } frame;
    Vec *ray_start=&frame.origin;
    char *vars=*(char **)(obj+0x68),*selected,*candidate,*class_def,*hit;
    Vec *pos; int disabled_count,index,accepted,visible,tries,i;
    float best=g_aim_l14_max_distance,heading,elevation,yaw_delta,distance,dot,length,angle,radius;
    ray_start->q=origin->q;
    FastVecScale(&frame.offset,g_hero_state.object+0xE0,0.5f);
    selected=0;
    FastVecAdd(&frame.player,g_hero_state.object+0x10,&frame.offset);
    if(CollLine(&frame.player,ray_start,6,g_hero_state.object,0)) {
        qcopy(ray_start,&g_aim_ray_start);
        return 0;
    }
    disabled_count=0; index=0;
    while((candidate=g_target_l14_list[index])!=0) {
        if(*(unsigned char *)(candidate+0x20)==0xFE) goto next;
        if(*(unsigned char *)(candidate+0x20)==0xFD) goto next;
        if(*(short *)(candidate+0xAA)==MOBY_CLASS_SHEEP || *(short *)(candidate+0xAA)==MOBY_CLASS_DARK_SHEEP) goto next;
        { Vec *t=&frame.target; qcopy(t,candidate+0x10); }
        class_def=moby_get_private_value_0(candidate);
        if(!class_def || *(unsigned char *)(class_def+0xE)==3) goto next;
        FastVecScale(&frame.aim,candidate+0xE0,*(float *)(class_def+0x10));
        FastVecAdd(&frame.target,&frame.target,&frame.aim);
        if(!candidate || !*(char **)(candidate+0x24) || *(short *)(*(char **)(candidate+0x24)+0x46)!=5) goto next;
        accepted=0;
        heading=mat_fast_helper_a(frame.target.f[0]-ray_start->f[0],frame.target.f[1]-ray_start->f[1]);
        elevation=mat_fast_helper_a(vec_distance_xy(ray_start,&frame.target),frame.target.f[2]-ray_start->f[2]);
        yaw_delta=FastDiffRots(*yaw,heading);
        distance=fast_vec_dist(ray_start,&frame.target);
        if(g_aim_l14_blocked_flag || g_hero_state.allowed || g_aim_extra_blocked_flag) {
            if(distance<2.5f) {
            FastVecSub(&frame.ray,candidate+0x10,g_hero_state.object+0x10);
            dot=FastVecDot(&frame.ray,g_hero_state.object+0xE0);
            if(math_fabs(dot)<2.0f) {
                FastVecScale(&frame.axis,g_hero_state.object+0xE0,dot);
                FastVecSub(&frame.ray,&frame.ray,&frame.axis);
                dot=FastVecDot(&frame.ray,g_hero_state.object+0xC0);
                { float len=FastVecLength(&frame.ray);
                if(len!=0.0f && 1.5707964f-math_fast_angle_helper(dot/len)<1.0471977f) accepted=1; }
            }
            }
        } else {
            if(distance<2.5f) {
                char *pobj=g_hero_state.object;
                angle=mat_fast_helper_a(*(float *)(candidate+0x10)-g_hero_state.position.f[0],*(float *)(candidate+0x14)-g_hero_state.position.f[1]);
                if(FastDiffRots(*(float *)(pobj+0xF8),angle)<1.0471977f && math_fabs(ray_start->f[2]-frame.target.f[2])<2.0f) accepted=1;
            }
        }
        if(accepted && !CollLine(ray_start,&frame.target,6,g_hero_state.object,0)) { selected=candidate; *pitch=-elevation; *yaw=heading; break; }
        if((distance>best && candidate!=*(char **)(vars+0x10)) || distance>g_aim_l14_max_distance) goto next;
        vec_build_spherical_offset(&frame.aim,distance,*yaw,*pitch+g_hero_state.pitch*0.5f);
        FastVecAdd(&frame.aim,&frame.aim,ray_start);
        angle=fast_vec_dist(&frame.aim,&frame.target);
        angle=math_fast_angle_helper(angle/(distance+distance)); angle+=angle;
        if(g_aim_l14_cone_angle*0.017453294f<angle && (class_def=moby_get_private_value_0(candidate))!=0) {
            radius=IntToFloat((unsigned char)class_def[10])*0.125f;
            length=math_fast_angle_helper(radius/distance);
            if(radius<distance) { angle-=length; if(angle<0.0f) angle=0.0f; }
        }
        if(angle<g_aim_l14_cone_angle*0.017453294f) {
            visible=1;
            qcopy(&frame.ray,ray_start); tries=0;
            while(CollLine(&frame.ray,&frame.target,6,obj,0)) {
                Collision *col;
                if(++tries>6) break;
                col=&g_projectile_l14_collision;
                hit=col->hit;
                if(hit) {
                    if(*(short *)(hit+0xAA)==MOBY_CLASS_SHEEP || *(short *)(hit+0xAA)==MOBY_CLASS_DARK_SHEEP) {
                        frame.disabled[disabled_count++]=hit; *(int *)(hit+0x98)=0;
                        if(disabled_count>127) break;
                        qcopy(&frame.ray,&col->point);
                        continue;
                    }
                    if(hit==candidate) break;
                }
                visible=0; break;
            }
            if(visible) { *pitch=-elevation; best=distance; if(yaw_delta<0.17453295f) *yaw=heading; selected=candidate; if(candidate==*(char **)(vars+0x10)) return selected; }
        }
next:
        ++index;
    }
    for(i=0;i<disabled_count;++i) { char *m=frame.disabled[i]; *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10); }
    return selected;
}
