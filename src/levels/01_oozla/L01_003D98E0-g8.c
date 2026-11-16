#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
extern float level_get_water_height(void);
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
extern void platform_sink_when_hit(void *);
extern int math_fast_float_d(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern u8 *g_moby_l01_table __attribute__((sda));
typedef struct {
    u8 pad00[0x30];
    Vec position;
    u8 pad40[0x40];
} AnchorRecord;
extern AnchorRecord *g_swamp_patrol_positions;
typedef struct {
    u8 pad00[0x80];
    Vec position;
    u8 pad90[0x33C - 0x90];
    u8 *platform;
    u8 pad340[0x34E - 0x340];
    s16 mode;
} HeroView;
extern u8 g_hero_state[];
extern char g_str_swing_debug_format[];
extern float g_swing_object_scale __attribute__((sda));
extern float g_swing_tilt_accel __attribute__((sda));
extern float g_swing_tilt_max_speed __attribute__((sda));
extern float g_swing_tilt_damping __attribute__((sda));
extern float g_swing_return_accel __attribute__((sda));
extern float g_swing_return_max_speed __attribute__((sda));
extern float g_swing_return_damping __attribute__((sda));
extern float g_swing_outer_pull_radius __attribute__((sda));
extern float g_swing_inner_pull_radius __attribute__((sda));
extern float g_swing_pull_scale __attribute__((sda));
extern float g_swing_pull_time_a __attribute__((sda));
extern float g_swing_pull_time_b __attribute__((sda));
extern float g_swing_rotation_strength __attribute__((sda));
extern float g_swing_outer_push_radius __attribute__((sda));
extern float g_swing_inner_push_radius __attribute__((sda));
extern float g_swing_push_time __attribute__((sda));
extern float g_swing_min_radius __attribute__((sda));
extern float g_swing_max_radius __attribute__((sda));
extern float g_swing_sink_height_limit __attribute__((sda));
extern float g_swing_sink_speed __attribute__((sda));
extern float g_swing_rise_speed __attribute__((sda));

/* Floating platform. It bobs on the water, tilts under the hero and is pushed away from nearby platforms. */
void UpdateFloatingPlatform(u8 *moby)
{
    Vec oldPos,oldRot,anchor,target,delta,prevRot,prevPos,out;
    u8 *vars=*(u8 **)(moby+0x68);
    u8 *other;
    u8 *cursor;
    float height;
    float *fieldD0,*fieldD4,*fieldD8,*fieldDC;
    qcopy_nc(oldPos,moby+0x10);
    qcopy_nc(oldRot,moby+0xF0);
    height=level_get_water_height();
    if(moby[0x20]!=0 && *(float *)(vars+0xB8)+5.0f<height) return;
    switch(moby[0x20]) {
    case 0:
        if(0.0f<height) {
            if(*(int *)(vars+0xC0)==-1) {
                STUB_printf(g_str_swing_debug_format,*(s16 *)(moby+0xAA),*(s16 *)(moby+0xB2));
                *(int *)(vars+0xC8)=0;
                moby_mark_spawned(moby);
                return;
            }
            *(u8 **)(vars+0xC8)=g_moby_l01_table+(*(int *)(vars+0xC0)<<8);
            qcopy(vars+0x90,moby+0xF0);
            qzero(vars+0xA0);
            qcopy(vars+0xB0,moby+0x10);
            moby_set_state(moby,1,-1);
        }
        break;
    case 1: {
        float limit,secondary;
        u8 *otherState,*attached;
        attached=*(u8 **)(vars+0xC8);
        otherState=*(u8 **)(attached+0x68);
        if(attached!=0 && attached[0x95]>=7) {
            *(float *)(moby+0x10)=*(float *)(vars+0xB0);
            *(float *)(moby+0x14)=*(float *)(vars+0xB4);
            if(*(float *)(moby+0x18)<*(float *)(vars+0xB8)) *(float *)(moby+0x18)=*(float *)(vars+0xB8);
            break;
        }
        qcopy(anchor,g_swamp_patrol_positions[*(int *)(otherState+0x2CC)].position);
        anchor[2]=*(float *)(moby+0x18);
        vec_scale_to_length(target,*(u8 **)(vars+0xC8)+0xC0,5.0f);
        FastVecAdd(target,target,*(u8 **)(vars+0xC8)+0x10);
        if(((HeroView *)g_hero_state)->mode==0 && ((HeroView *)g_hero_state)->platform==moby) {
            float dotX,dotY,y,x,scale;
            FastVecSub(delta,((HeroView *)g_hero_state)->position,moby+0x10);
            dotX=FastVecDot(delta,moby+0xC0);
            dotY=FastVecDot(delta,moby+0xD0);
            scale=g_swing_object_scale;
            y=-scale*dotY;
            x=scale*dotX;
            *(Quad *)prevRot=*(Quad *)(vars+0x90);
            *(Quad *)prevPos=*(Quad *)(moby+0x10);
            math_approach_with_velocity((float *)(vars+0x90),y,(float *)(vars+0xA0),g_swing_tilt_accel*4.848137450608192e-06f,g_swing_tilt_max_speed,g_swing_tilt_damping*0.0002908882452175021f,0);
            math_approach_with_velocity((float *)(vars+0x94),x,(float *)(vars+0xA4),g_swing_tilt_accel*4.848137450608192e-06f,g_swing_tilt_max_speed,g_swing_tilt_damping*0.0002908882452175021f,0);
            mat_transform_offset_two_matrices(((HeroView *)g_hero_state)->position,out,moby+0x10,prevRot,vars+0x90);
        } else {
            math_approach_with_velocity((float *)(vars+0x90),0.0f,(float *)(vars+0xA0),g_swing_return_accel*4.848137450608192e-06f,g_swing_return_max_speed,g_swing_return_damping*0.0002908882452175021f,0);
            math_approach_with_velocity((float *)(vars+0x94),0.0f,(float *)(vars+0xA4),g_swing_return_accel*4.848137450608192e-06f,g_swing_return_max_speed,g_swing_return_damping*0.0002908882452175021f,0);
            other=*(u8 **)(vars+0xC8);
            if(other!=0 && other[0x20]!=0xFE && other[0x20]!=0xFD && other[0x95]>=2) {
                float dist,dist2;
                FastVecSub(delta,moby+0x10,other+0x10);
                dist=FastVecLength(delta);
                dist2=vec_distance_xy(moby+0x10,target);
                if(dist2<dist) { FastVecSub(delta,moby+0x10,target); dist=dist2; }
                if(dist<g_swing_outer_pull_radius) {
                    float falloff,anchorDistance,d;
                    dist=g_swing_outer_pull_radius-dist;
                    falloff=dist/(g_swing_outer_pull_radius-g_swing_inner_pull_radius);
                    if(falloff>1.0f) falloff=1.0f;
                    else if(falloff<0.0f) falloff=0.0f;
                    vec_scale_to_length(delta,delta,dist*falloff);
                    vec_fast_divide_helper(delta,delta,g_swing_pull_time_b*(1.0f/60.0f));
                    anchorDistance=vec_distance_xy(*(u8 **)(vars+0xC8)+0x10,anchor);
                    FastVecSub(prevRot,moby+0x10,anchor);
                    d=FastVecLength(prevRot)-anchorDistance;
                    d=d/math_fabs(d);
                    d*=1.0f/60.0f;
                    vec_scale_to_length(prevRot,prevRot,(g_swing_rotation_strength*d)*falloff);
                    FastVecAdd(moby+0x10,moby+0x10,prevRot);
                    FastVecAdd(moby+0x10,moby+0x10,delta);
                }
            }
        }
        FastVecSub(delta,vars+0xB0,moby+0x10);
        fieldD8=(float *)(vars+0xD8);
        FastVecScale(delta,delta,g_swing_pull_scale);
        fieldDC=(float *)(vars+0xDC); fieldD0=(float *)(vars+0xD0);
        vec_fast_divide_helper(delta,delta,g_swing_pull_time_a*(1.0f/60.0f));
        fieldD4=(float *)(vars+0xD4);
        FastVecAdd(moby+0x10,moby+0x10,delta);
        limit=vec_distance_xy(moby+0x10,*(u8 **)(vars+0xC8)+0x10);
        secondary=vec_distance_xy(moby+0x10,target);
        limit=limit<secondary?limit:secondary;
        cursor=0;
        GetFirstMobyInGroup(&cursor,moby[0x21],0,0);
        while(cursor!=0) {
            float dist,dist2,falloff;
            FastVecSub(delta,moby+0x10,cursor+0x10);
            dist=FastVecLength(delta);
            if(dist<g_swing_outer_push_radius) {
                dist2=vec_distance_xy(cursor+0x10,*(u8 **)(vars+0xC8)+0x10);
                secondary=vec_distance_xy(moby+0x10,target);
                dist2=dist2<secondary?dist2:secondary;
                dist=g_swing_outer_push_radius-dist;
                falloff=dist/(g_swing_outer_push_radius-g_swing_inner_push_radius);
                if(falloff>1.0f) falloff=1.0f;
                else if(falloff<0.0f) falloff=0.0f;
                vec_scale_to_length(delta,delta,dist*falloff);
                vec_fast_divide_helper(delta,delta,g_swing_push_time*(1.0f/60.0f));
                if(limit<dist2) {
                    float radius;
                    FastVecSub(cursor+0x10,cursor+0x10,delta);
                    FastVecSub(prevRot,cursor+0x10,anchor);
                    radius=FastVecLength(prevRot);
                    if(radius<g_swing_min_radius) {
                        vec_scale_to_length(prevRot,prevRot,g_swing_min_radius);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    } else if(g_swing_max_radius<radius) {
                        vec_scale_to_length(prevRot,prevRot,g_swing_max_radius);
                        FastVecAdd(cursor+0x10,anchor,prevRot);
                    }
                } else FastVecAdd(moby+0x10,moby+0x10,delta);
            }
            GetNextMobyInGroup(&cursor,cursor,0,0);
        }
        {
            float dist;
            FastVecSub(delta,moby+0x10,anchor);
            dist=FastVecLength(delta);
            if(dist<g_swing_min_radius) {
                vec_scale_to_length(delta,delta,g_swing_min_radius);
                FastVecAdd(moby+0x10,anchor,delta);
            } else if(g_swing_max_radius<dist) {
                vec_scale_to_length(delta,delta,g_swing_max_radius);
                FastVecAdd(moby+0x10,anchor,delta);
            }
        }
        *(float *)(moby+0x18)=height;
        math_update_wrapped_angle_offset(moby,fieldD8,fieldDC,0.08f,0.008726648055016994f,-1.0f);
        moby_scale_owner_words_by_angles(moby,fieldD0,fieldD4,0.04363323748111725f,0.007272206246852875f,0.00901753549f);
        *(float *)(moby+0xF0)=FastAddRotations(*(float *)(vars+0x90),*(float *)(moby+0xF0));
        *(float *)(moby+0xF4)=FastAddRotations(*(float *)(vars+0x94),*(float *)(moby+0xF4));
        platform_sink_when_hit(moby);
        break;
    }
    case 2:
        if(height-g_swing_sink_height_limit<*(float *)(moby+0x18)) *(float *)(moby+0x18)-=g_swing_sink_speed*(1.0f/60.0f);
        if(math_fast_float_d(vars+0xC4)) moby_set_state(moby,3,-1);
        break;
    case 3:
        if(*(float *)(moby+0x18)<height) {
            *(float *)(moby+0x18)+=g_swing_rise_speed*(1.0f/60.0f);
            if(height<*(float *)(moby+0x18)) {
                *(float *)(moby+0x18)=height;
                moby_set_state(moby,1,-1);
            }
        }
        break;
    case 4:
    case 5:
        break;
    }
    if(*(float *)(moby+0x10)<10.0f) *(float *)(moby+0x10)=10.0f;
    if(*(float *)(moby+0x10)>1013.0f) *(float *)(moby+0x10)=1013.0f;
    if(*(float *)(moby+0x14)<10.0f) *(float *)(moby+0x14)=10.0f;
    if(*(float *)(moby+0x14)>1013.0f) *(float *)(moby+0x14)=1013.0f;
    if(*(float *)(moby+0x18)<10.0f) *(float *)(moby+0x18)=10.0f;
    if(*(float *)(moby+0x18)>1013.0f) *(float *)(moby+0x18)=1013.0f;
    if(moby[0x20]!=2) {
        FastVecSub(anchor,moby+0x10,oldPos);
        mat_combine_and_store(vars+0x50,anchor,oldRot,moby+0xF0);
    }
}
