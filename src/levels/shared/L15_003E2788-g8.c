#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char pad0[0x80]; Vec position; unsigned char pad90[0x294];
    float pitch; unsigned char pad328[0x20]; short allowed;
    unsigned char pad34a[0x1f46]; char *object;
} PlayerView;
extern PlayerView g_hero_state;
extern int D_L15_001A8FF0;
extern int D_L15_001A8FF4 __attribute__((sda));
extern float D_L15_001AFEB0 __attribute__((sda)),D_L15_001AFEB4 __attribute__((sda));
extern char *D_L15_001FB6E0[];
extern Vec D_L15_001BFC20;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; } Collision;
extern Collision D_L15_001BFC00;
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *),FastVecSub(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern char *moby_get_private_value_0(char *);
extern float mat_fast_helper_a(float,float),FastDiffRots(float,float),math_fabs(float),math_fast_angle_helper(float),IntToFloat(int);
extern float vec_distance_xy(void *,void *),fast_vec_dist(void *,void *),FastVecDot(void *,void *),FastVecLength(void *);
extern void vec_build_spherical_offset(void *,float,float,float);

/* Target selection: the nearest visible candidate in front of the player within the aim cone. */
char *target_find_nearest_in_aim_cone(char *obj,Vec *origin,float *yaw,float *pitch) {
    struct { Vec origin,offset,player; char *disabled[128]; Vec target,aim,ray,axis; } frame;
    Vec *start=&frame.origin;
    char *ctx=*(char **)(obj+0x68),*selected,*candidate,*definition,*hit;
    Vec *pos; int n,index,accepted,visible,tries,i;
    float best=D_L15_001AFEB4,heading,elevation,delta,distance,dot,length,angle,radius;
    start->q=origin->q;
    FastVecScale(&frame.offset,g_hero_state.object+0xE0,0.5f);
    selected=0;
    FastVecAdd(&frame.player,g_hero_state.object+0x10,&frame.offset);
    if(CollLine(&frame.player,start,6,g_hero_state.object,0)) {
        qcopy(start,&D_L15_001BFC20);
        return 0;
    }
    n=0; index=0;
    while((candidate=D_L15_001FB6E0[index])!=0) {
        if(*(unsigned char *)(candidate+0x20)==0xFE) goto next;
        if(*(unsigned char *)(candidate+0x20)==0xFD) goto next;
        if(*(short *)(candidate+0xAA)==0xE7D /* Sheep */ || *(short *)(candidate+0xAA)==0xEB0 /* Dark Sheep */) goto next;
        { Vec *t=&frame.target; qcopy(t,candidate+0x10); }
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
        if(D_L15_001A8FF0 || g_hero_state.allowed || D_L15_001A8FF4) {
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
                if(FastDiffRots(*(float *)(pobj+0xF8),angle)<1.0471977f && math_fabs(start->f[2]-frame.target.f[2])<2.0f) accepted=1;
            }
        }
        if(accepted && !CollLine(start,&frame.target,6,g_hero_state.object,0)) { selected=candidate; *pitch=-elevation; *yaw=heading; break; }
        if((distance>best && candidate!=*(char **)(ctx+0x10)) || distance>D_L15_001AFEB4) goto next;
        vec_build_spherical_offset(&frame.aim,distance,*yaw,*pitch+g_hero_state.pitch*0.5f);
        FastVecAdd(&frame.aim,&frame.aim,start);
        angle=fast_vec_dist(&frame.aim,&frame.target);
        angle=math_fast_angle_helper(angle/(distance+distance)); angle+=angle;
        if(D_L15_001AFEB0*0.017453294f<angle && (definition=moby_get_private_value_0(candidate))!=0) {
            radius=IntToFloat((unsigned char)definition[10])*0.125f;
            length=math_fast_angle_helper(radius/distance);
            if(radius<distance) { angle-=length; if(angle<0.0f) angle=0.0f; }
        }
        if(angle<D_L15_001AFEB0*0.017453294f) {
            visible=1;
            qcopy(&frame.ray,start); tries=0;
            while(CollLine(&frame.ray,&frame.target,6,obj,0)) {
                Collision *col;
                if(++tries>6) break;
                col=&D_L15_001BFC00;
                hit=col->hit;
                if(hit) {
                    if(*(short *)(hit+0xAA)==0xE7D /* Sheep */ || *(short *)(hit+0xAA)==0xEB0 /* Dark Sheep */) {
                        frame.disabled[n++]=hit; *(int *)(hit+0x98)=0;
                        if(n>127) break;
                        qcopy(&frame.ray,&col->point);
                        continue;
                    }
                    if(hit==candidate) break;
                }
                visible=0; break;
            }
            if(visible) { *pitch=-elevation; best=distance; if(delta<0.17453295f) *yaw=heading; selected=candidate; if(candidate==*(char **)(ctx+0x10)) return selected; }
        }
next:
        ++index;
    }
    for(i=0;i<n;++i) { char *m=frame.disabled[i]; *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10); }
    return selected;
}
