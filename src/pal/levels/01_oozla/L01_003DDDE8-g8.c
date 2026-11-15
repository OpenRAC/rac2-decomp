/* func_PAL_L01_003DDDE8, the PAL copy of func_L01_003D98E0: the same C at 50 Hz, with the attached-object test moved ahead of the switch and widened. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
extern float func_PAL_L01_003BEB40(void);
extern void STUB_printf(const char *, ...);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float FastVecLength(void *);
extern float vec_distance_xy(void *, void *);
extern float math_fabs(float);
extern void vec_fast_divide_helper(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float math_approach_with_velocity(float *position, float target, float *velocity, float acceleration, float damping, float limit, int direction);
extern void mat_transform_offset_two_matrices(void *, void *, void *, void *, void *);
extern int GetFirstMobyInGroup(void *, int, int, int);
extern int GetNextMobyInGroup(void *, void *, int, int);
extern void math_update_wrapped_angle_offset(void *, void *, void *, float, float, float);
extern void moby_scale_owner_words_by_angles(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void func_PAL_L01_003DDD18(void *);
extern int math_fast_float_d(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern u8 *g_moby_l01_table __attribute__((sda));
typedef struct {
    u8 pad00[0x30];
    Vec position;
    u8 pad40[0x40];
} AnchorRecord;
extern AnchorRecord *D_L01_001B264C;
typedef struct {
    u8 pad00[0x80];
    Vec position;
    u8 pad90[0x33C - 0x90];
    u8 *platform;
    u8 pad340[0x34E - 0x340];
    s16 mode;
} HeroView;
extern u8 g_hero_state[];
extern char D_L01_001B0800[];
extern float D_L01_001B07A8 __attribute__((sda));
extern float D_L01_001B07AC __attribute__((sda));
extern float D_L01_001B07B0 __attribute__((sda));
extern float D_L01_001B07B4 __attribute__((sda));
extern float D_L01_001B07B8 __attribute__((sda));
extern float D_L01_001B07BC __attribute__((sda));
extern float D_L01_001B07C0 __attribute__((sda));
extern float D_L01_001B07C4 __attribute__((sda));
extern float D_L01_001B07C8 __attribute__((sda));
extern float D_L01_001B07CC __attribute__((sda));
extern float D_L01_001B07D0 __attribute__((sda));
extern float D_L01_001B07D4 __attribute__((sda));
extern float D_L01_001B07D8 __attribute__((sda));
extern float D_L01_001B07DC __attribute__((sda));
extern float D_L01_001B07E0 __attribute__((sda));
extern float D_L01_001B07E4 __attribute__((sda));
extern float D_L01_001B07E8 __attribute__((sda));
extern float D_L01_001B07EC __attribute__((sda));
extern float D_L01_001B07F0 __attribute__((sda));
extern float D_L01_001B07F4 __attribute__((sda));
extern float D_L01_001B07F8 __attribute__((sda));

void func_PAL_L01_003DDDE8(u8 *m)
{
    Vec oldPos,oldRot,anchor,target,delta,prevRot,prevPos,out;
    u8 *s=*(u8 **)(m+0x68);
    u8 *other;
    u8 *cursor;
    float height;
    float *fieldD0,*fieldD4,*fieldD8,*fieldDC;
    qcopy_nc(oldPos,m+0x10);
    qcopy_nc(oldRot,m+0xF0);
    height=func_PAL_L01_003BEB40();
    if(m[0x20]!=0) {
        u8 *attached;
        if(*(float *)(s+0xB8)+5.0f<height) return;
        attached=*(u8 **)(s+0xC8);
        if(attached!=0 && (attached[0x95]>=7 || *(float *)(*(u8 **)(attached+0x68)+0x20)==0.0f)) {
            *(float *)(m+0x10)=*(float *)(s+0xB0);
            *(float *)(m+0x14)=*(float *)(s+0xB4);
            if(*(float *)(m+0x18)<*(float *)(s+0xB8)-0.2f) *(float *)(m+0x18)=*(float *)(s+0xB8);
            *(int *)(s+0xC4)=0;
            moby_set_state(m,1,-1);
            return;
        }
    }
    switch(m[0x20]) {
    case 0:
        if(0.0f<height) {
            if(*(int *)(s+0xC0)==-1) {
                STUB_printf(D_L01_001B0800,*(s16 *)(m+0xAA),*(s16 *)(m+0xB2));
                *(int *)(s+0xC8)=0;
                moby_mark_spawned(m);
                return;
            }
            *(u8 **)(s+0xC8)=g_moby_l01_table+(*(int *)(s+0xC0)<<8);
            qcopy(s+0x90,m+0xF0);
            qzero(s+0xA0);
            qcopy(s+0xB0,m+0x10);
            moby_set_state(m,1,-1);
        }
        break;
    case 1: {
        float limit,secondary;
        u8 *otherState,*attached;
        attached=*(u8 **)(s+0xC8);
        otherState=*(u8 **)(attached+0x68);
        qcopy(anchor,D_L01_001B264C[*(int *)(otherState+0x2CC)].position);
        anchor[2]=*(float *)(m+0x18);
        vec_scale_to_length(target,*(u8 **)(s+0xC8)+0xC0,5.0f);
        FastVecAdd(target,target,*(u8 **)(s+0xC8)+0x10);
        if(((HeroView *)g_hero_state)->mode==0 && ((HeroView *)g_hero_state)->platform==m) {
            float dotX,dotY,y,x,scale;
            FastVecSub(delta,((HeroView *)g_hero_state)->position,m+0x10);
            dotX=FastVecDot(delta,m+0xC0);
            dotY=FastVecDot(delta,m+0xD0);
            scale=D_L01_001B07A8;
            y=-scale*dotY;
            x=scale*dotX;
            *(Quad *)prevRot=*(Quad *)(s+0x90);
            *(Quad *)prevPos=*(Quad *)(m+0x10);
            math_approach_with_velocity((float *)(s+0x90),y,(float *)(s+0xA0),D_L01_001B07AC*6.981318e-06f,D_L01_001B07B0*1.44f,D_L01_001B07B4*0.0003490659f,0);
            math_approach_with_velocity((float *)(s+0x94),x,(float *)(s+0xA4),D_L01_001B07AC*6.981318e-06f,D_L01_001B07B0*1.44f,D_L01_001B07B4*0.0003490659f,0);
            mat_transform_offset_two_matrices(((HeroView *)g_hero_state)->position,out,m+0x10,prevRot,s+0x90);
        } else {
            math_approach_with_velocity((float *)(s+0x90),0.0f,(float *)(s+0xA0),D_L01_001B07B8*6.981318e-06f,D_L01_001B07BC*1.44f,D_L01_001B07C0*0.0003490659f,0);
            math_approach_with_velocity((float *)(s+0x94),0.0f,(float *)(s+0xA4),D_L01_001B07B8*6.981318e-06f,D_L01_001B07BC*1.44f,D_L01_001B07C0*0.0003490659f,0);
            other=*(u8 **)(s+0xC8);
            if(other!=0 && other[0x20]!=0xFE && other[0x20]!=0xFD && other[0x95]>=2) {
                float dist,dist2;
                FastVecSub(delta,m+0x10,other+0x10);
                dist=FastVecLength(delta);
                dist2=vec_distance_xy(m+0x10,target);
                if(dist2<dist) { FastVecSub(delta,m+0x10,target); dist=dist2; }
                if(dist<D_L01_001B07C4) {
                    float falloff,anchorDistance,d;
                    dist=D_L01_001B07C4-dist;
                    falloff=dist/(D_L01_001B07C4-D_L01_001B07C8);
                    if(falloff>1.0f) falloff=1.0f;
                    else if(falloff<0.0f) falloff=0.0f;
                    vec_scale_to_length(delta,delta,dist*falloff);
                    vec_fast_divide_helper(delta,delta,D_L01_001B07D4*(0.020000001f));
                    anchorDistance=vec_distance_xy(*(u8 **)(s+0xC8)+0x10,anchor);
                    FastVecSub(prevRot,m+0x10,anchor);
                    d=FastVecLength(prevRot)-anchorDistance;
                    d=d/math_fabs(d);
                    d*=0.020000001f;
                    vec_scale_to_length(prevRot,prevRot,(D_L01_001B07D8*d)*falloff);
                    FastVecAdd(m+0x10,m+0x10,prevRot);
                    FastVecAdd(m+0x10,m+0x10,delta);
                }
            }
        }
        FastVecSub(delta,s+0xB0,m+0x10);
        fieldD8=(float *)(s+0xD8);
        FastVecScale(delta,delta,D_L01_001B07CC);
        fieldDC=(float *)(s+0xDC); fieldD0=(float *)(s+0xD0);
        vec_fast_divide_helper(delta,delta,D_L01_001B07D0*(0.020000001f));
        fieldD4=(float *)(s+0xD4);
        FastVecAdd(m+0x10,m+0x10,delta);
        limit=vec_distance_xy(m+0x10,*(u8 **)(s+0xC8)+0x10);
        secondary=vec_distance_xy(m+0x10,target);
        limit=limit<secondary?limit:secondary;
        cursor=0;
        GetFirstMobyInGroup(&cursor,m[0x21],0,0);
        while(cursor!=0) {
            float dist,dist2,falloff;
            FastVecSub(delta,m+0x10,cursor+0x10);
            dist=FastVecLength(delta);
            if(dist<D_L01_001B07DC) {
                dist2=vec_distance_xy(cursor+0x10,*(u8 **)(s+0xC8)+0x10);
                secondary=vec_distance_xy(m+0x10,target);
                dist2=dist2<secondary?dist2:secondary;
                dist=D_L01_001B07DC-dist;
                falloff=dist/(D_L01_001B07DC-D_L01_001B07E0);
                if(falloff>1.0f) falloff=1.0f;
                else if(falloff<0.0f) falloff=0.0f;
                vec_scale_to_length(delta,delta,dist*falloff);
                vec_fast_divide_helper(delta,delta,D_L01_001B07E4*(0.020000001f));
                if(limit<dist2) {
                    float radius;
                    FastVecSub(cursor+0x10,cursor+0x10,delta);
                    FastVecSub(prevRot,cursor+0x10,anchor);
                    radius=FastVecLength(prevRot);
                    if(radius<D_L01_001B07E8) {
                        vec_scale_to_length(prevRot,prevRot,D_L01_001B07E8);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    } else if(D_L01_001B07EC<radius) {
                        vec_scale_to_length(prevRot,prevRot,D_L01_001B07EC);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    }
                } else FastVecAdd(m+0x10,m+0x10,delta);
            }
            GetNextMobyInGroup(&cursor,cursor,0,0);
        }
        {
            float dist;
            FastVecSub(delta,m+0x10,anchor);
            dist=FastVecLength(delta);
            if(dist<D_L01_001B07E8) {
                vec_scale_to_length(delta,delta,D_L01_001B07E8);
                FastVecAdd(m+0x10,anchor,delta);
            } else if(D_L01_001B07EC<dist) {
                vec_scale_to_length(delta,delta,D_L01_001B07EC);
                FastVecAdd(m+0x10,anchor,delta);
            }
        }
        *(float *)(m+0x18)=height;
        math_update_wrapped_angle_offset(m,fieldD8,fieldDC,0.08f,0.010471977f,-1.0f);
        moby_scale_owner_words_by_angles(m,fieldD0,fieldD4,0.04363323748111725f,0.008726647f,0.010821043f);
        *(float *)(m+0xF0)=FastAddRotations(*(float *)(s+0x90),*(float *)(m+0xF0));
        *(float *)(m+0xF4)=FastAddRotations(*(float *)(s+0x94),*(float *)(m+0xF4));
        func_PAL_L01_003DDD18(m);
        break;
    }
    case 2:
        if(height-D_L01_001B07F0<*(float *)(m+0x18)) *(float *)(m+0x18)-=D_L01_001B07F4*(0.020000001f);
        if(math_fast_float_d(s+0xC4)) moby_set_state(m,3,-1);
        break;
    case 3:
        if(*(float *)(m+0x18)<height) {
            *(float *)(m+0x18)+=D_L01_001B07F8*(0.020000001f);
            if(height<*(float *)(m+0x18)) {
                *(float *)(m+0x18)=height;
                moby_set_state(m,1,-1);
            }
        }
        break;
    case 4:
    case 5:
        break;
    }
    if(*(float *)(m+0x10)<10.0f) *(float *)(m+0x10)=10.0f;
    if(*(float *)(m+0x10)>1013.0f) *(float *)(m+0x10)=1013.0f;
    if(*(float *)(m+0x14)<10.0f) *(float *)(m+0x14)=10.0f;
    if(*(float *)(m+0x14)>1013.0f) *(float *)(m+0x14)=1013.0f;
    if(*(float *)(m+0x18)<10.0f) *(float *)(m+0x18)=10.0f;
    if(*(float *)(m+0x18)>1013.0f) *(float *)(m+0x18)=1013.0f;
    if(m[0x20]!=2) {
        FastVecSub(anchor,m+0x10,oldPos);
        mat_combine_and_store(s+0x50,anchor,oldRot,m+0xF0);
    }
}
