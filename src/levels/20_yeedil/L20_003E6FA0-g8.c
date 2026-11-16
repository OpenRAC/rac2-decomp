#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char pad0[0x80]; Vec position; unsigned char pad90[0x294];
    float pitch; unsigned char pad328[0x20]; short allowed;
    unsigned char pad34a[0x1f46]; char *object;
} PlayerView;
extern PlayerView g_hero_state;
extern int g_hero_l20_lock_flag_a;
extern int g_hero_l20_lock_flag_b __attribute__((sda));
extern float g_aim_l20_angle_limit __attribute__((sda)),g_aim_l20_max_distance __attribute__((sda));
extern char *g_moby_target_lists[];
extern Vec g_spark_position;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; } Collision;
extern Collision g_collision_contact;
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern char *moby_get_private_value_0(char *);
extern float mat_fast_helper_a(float,float),FastDiffRots(float,float),math_fabs(float),math_fast_angle_helper(float),IntToFloat(int);
extern float vec_distance_xy(void *,void *),fast_vec_dist(void *,void *),FastVecDot(void *,void *),FastVecLength(void *);
extern void vec_build_spherical_offset(void *,float,float,float);

/* Target selection: the nearest visible candidate in front of the player within the aim cone. */
char *hero_l20_find_aim_target(char *moby,Vec *origin,float *yaw,float *pitch) {
    struct { Vec origin,offset,player; char *disabled[128]; Vec target,aim,ray,axis; } frame;
    Vec *start=&frame.origin;
    char *vars=*(char **)(moby+0x68),*selected,*candidate,*definition,*hit;
    Vec *pos; int disabled_count,index,accepted,visible,tries,i;
    float best=g_aim_l20_max_distance,heading,elevation,delta,distance,dot,length,angle,radius;
    start->q=origin->q;
    FastVecScale(&frame.offset,g_hero_state.object+0xE0,0.5f);
    selected=0;
    FastVecAdd(&frame.player,g_hero_state.object+0x10,&frame.offset);
    if(CollLine(&frame.player,start,6,g_hero_state.object,0)) {
        qcopy(start,&g_spark_position);
        return 0;
    }
    disabled_count=0; index=0;
    while((candidate=g_moby_target_lists[index])!=0) {
        if(*(unsigned char *)(candidate+0x20)==0xFE) goto next;
        if(*(unsigned char *)(candidate+0x20)==0xFD) goto next;
        if(*(short *)(candidate+0xAA)==MOBY_CLASS_SHEEP || *(short *)(candidate+0xAA)==MOBY_CLASS_DARK_SHEEP) goto next;
        { Vec *aim_pos=&frame.target; qcopy(aim_pos,candidate+0x10); }
        definition=moby_get_private_value_0(candidate);
        if(!definition || *(unsigned char *)(definition+0xE)==3) goto next;
        FastVecScale(&frame.aim,candidate+0xE0,*(float *)(definition+0x10));
        FastVecAdd(&frame.target,&frame.target,&frame.aim);
        if(!candidate || !*(char **)(candidate+0x24) || *(short *)(*(char **)(candidate+0x24)+0x46)!=5) goto next;
        accepted=0;
        heading=mat_fast_helper_a(frame.target.f[0]-start->f[0],frame.target.f[1]-start->f[1]);
        elevation=mat_fast_helper_a(vec_distance_xy(start,&frame.target),frame.target.f[2]-start->f[2]);
        delta=FastDiffRots(*yaw,heading);
        distance=fast_vec_dist(start,&frame.target);
        if(g_hero_l20_lock_flag_a || g_hero_state.allowed || g_hero_l20_lock_flag_b) {
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
                char *player_moby=g_hero_state.object;
                angle=mat_fast_helper_a(*(float *)(candidate+0x10)-g_hero_state.position.f[0],*(float *)(candidate+0x14)-g_hero_state.position.f[1]);
                if(FastDiffRots(*(float *)(player_moby+0xF8),angle)<1.0471977f && math_fabs(start->f[2]-frame.target.f[2])<2.0f) accepted=1;
            }
        }
        if(accepted && !CollLine(start,&frame.target,6,g_hero_state.object,0)) { selected=candidate; *pitch=-elevation; *yaw=heading; break; }
        if((distance>best && candidate!=*(char **)(vars+0x10)) || distance>g_aim_l20_max_distance) goto next;
        vec_build_spherical_offset(&frame.aim,distance,*yaw,*pitch+g_hero_state.pitch*0.5f);
        FastVecAdd(&frame.aim,&frame.aim,start);
        angle=fast_vec_dist(&frame.aim,&frame.target);
        angle=math_fast_angle_helper(angle/(distance+distance)); angle+=angle;
        if(g_aim_l20_angle_limit*0.017453294f<angle && (definition=moby_get_private_value_0(candidate))!=0) {
            radius=IntToFloat((unsigned char)definition[10])*0.125f;
            length=math_fast_angle_helper(radius/distance);
            if(radius<distance) { angle-=length; if(angle<0.0f) angle=0.0f; }
        }
        if(angle<g_aim_l20_angle_limit*0.017453294f) {
            visible=1;
            qcopy(&frame.ray,start); tries=0;
            while(CollLine(&frame.ray,&frame.target,6,moby,0)) {
                Collision *col;
                if(++tries>6) break;
                col=&g_collision_contact;
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
            if(visible) { *pitch=-elevation; best=distance; if(delta<0.17453295f) *yaw=heading; selected=candidate; if(candidate==*(char **)(vars+0x10)) return selected; }
        }
next:
        ++index;
    }
    for(i=0;i<disabled_count;++i) { char *disabled_moby=frame.disabled[i]; *(int *)(disabled_moby+0x98)=*(int *)(*(char **)(disabled_moby+0x24)+0x10); }
    return selected;
}
