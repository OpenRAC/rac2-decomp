#include "names.h"
/* func_PAL_L01_003DDDE8, the PAL copy of func_L01_003D98E0: the same C at 50 Hz, with the attached-object test moved ahead of the switch and widened. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef float Vec[4] __attribute__((aligned(16)));
extern float level_get_water_height_pal(void);
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
extern void platform_sink_when_hit_pal(void *);
extern int math_fast_float_d(void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern u8 *g_moby_l01_table __attribute__((sda));
typedef struct {
    u8 pad_00[0x30];
    Vec position;
    u8 pad_40[0x40];
} AnchorRecord;
extern AnchorRecord *g_swamp_patrol_positions;
typedef struct {
    u8 pad_00[0x80];
    Vec position;
    u8 pad_90[0x33C - 0x90];
    u8 *platform;
    u8 pad_340[0x34E - 0x340];
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

/* Updates the floating platform. It tilts under the hero, is pushed around by nearby mobys, sinks and rises again, and stays inside the level bounds (PAL: 50 Hz rates). */
void floating_platform_update_pal(u8 *moby)
{
    Vec old_pos,old_rot,anchor,target,delta,prev_rot,prev_pos,out;
    u8 *vars=*(u8 **)(moby+0x68);
    u8 *linked_moby;
    u8 *cursor;
    float height;
    float *field_d0,*field_d4,*field_d8,*field_dc;
    qcopy_nc(old_pos,moby+0x10);
    qcopy_nc(old_rot,moby+0xF0);
    height=level_get_water_height_pal();
    if(moby[0x20]!=0) {
        u8 *attached;
        if(*(float *)(vars+0xB8)+5.0f<height) return;
        attached=*(u8 **)(vars+0xC8);
        if(attached!=0 && (attached[0x95]>=7 || *(float *)(*(u8 **)(attached+0x68)+0x20)==0.0f)) {
            *(float *)(moby+0x10)=*(float *)(vars+0xB0);
            *(float *)(moby+0x14)=*(float *)(vars+0xB4);
            if(*(float *)(moby+0x18)<*(float *)(vars+0xB8)-0.2f) *(float *)(moby+0x18)=*(float *)(vars+0xB8);
            *(int *)(vars+0xC4)=0;
            moby_set_state(moby,1,-1);
            return;
        }
    }
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
        u8 *linked_vars,*attached;
        attached=*(u8 **)(vars+0xC8);
        linked_vars=*(u8 **)(attached+0x68);
        qcopy(anchor,g_swamp_patrol_positions[*(int *)(linked_vars+0x2CC)].position);
        anchor[2]=*(float *)(moby+0x18);
        vec_scale_to_length(target,*(u8 **)(vars+0xC8)+0xC0,5.0f);
        FastVecAdd(target,target,*(u8 **)(vars+0xC8)+0x10);
        if(((HeroView *)g_hero_state)->mode==0 && ((HeroView *)g_hero_state)->platform==moby) {
            float dot_x,dot_y,tilt_y,tilt_x,scale;
            FastVecSub(delta,((HeroView *)g_hero_state)->position,moby+0x10);
            dot_x=FastVecDot(delta,moby+0xC0);
            dot_y=FastVecDot(delta,moby+0xD0);
            scale=g_swing_object_scale;
            tilt_y=-scale*dot_y;
            tilt_x=scale*dot_x;
            *(Quad *)prev_rot=*(Quad *)(vars+0x90);
            *(Quad *)prev_pos=*(Quad *)(moby+0x10);
            math_approach_with_velocity((float *)(vars+0x90),tilt_y,(float *)(vars+0xA0),g_swing_tilt_accel*6.981318e-06f,g_swing_tilt_max_speed*1.44f,g_swing_tilt_damping*0.0003490659f,0);
            math_approach_with_velocity((float *)(vars+0x94),tilt_x,(float *)(vars+0xA4),g_swing_tilt_accel*6.981318e-06f,g_swing_tilt_max_speed*1.44f,g_swing_tilt_damping*0.0003490659f,0);
            mat_transform_offset_two_matrices(((HeroView *)g_hero_state)->position,out,moby+0x10,prev_rot,vars+0x90);
        } else {
            math_approach_with_velocity((float *)(vars+0x90),0.0f,(float *)(vars+0xA0),g_swing_return_accel*6.981318e-06f,g_swing_return_max_speed*1.44f,g_swing_return_damping*0.0003490659f,0);
            math_approach_with_velocity((float *)(vars+0x94),0.0f,(float *)(vars+0xA4),g_swing_return_accel*6.981318e-06f,g_swing_return_max_speed*1.44f,g_swing_return_damping*0.0003490659f,0);
            linked_moby=*(u8 **)(vars+0xC8);
            if(linked_moby!=0 && linked_moby[0x20]!=0xFE && linked_moby[0x20]!=0xFD && linked_moby[0x95]>=2) {
                float dist,dist_b;
                FastVecSub(delta,moby+0x10,linked_moby+0x10);
                dist=FastVecLength(delta);
                dist_b=vec_distance_xy(moby+0x10,target);
                if(dist_b<dist) { FastVecSub(delta,moby+0x10,target); dist=dist_b; }
                if(dist<g_swing_outer_pull_radius) {
                    float falloff,anchor_distance,pull_dir;
                    dist=g_swing_outer_pull_radius-dist;
                    falloff=dist/(g_swing_outer_pull_radius-g_swing_inner_pull_radius);
                    if(falloff>1.0f) falloff=1.0f;
                    else if(falloff<0.0f) falloff=0.0f;
                    vec_scale_to_length(delta,delta,dist*falloff);
                    vec_fast_divide_helper(delta,delta,g_swing_pull_time_b*(0.020000001f));
                    anchor_distance=vec_distance_xy(*(u8 **)(vars+0xC8)+0x10,anchor);
                    FastVecSub(prev_rot,moby+0x10,anchor);
                    pull_dir=FastVecLength(prev_rot)-anchor_distance;
                    pull_dir=pull_dir/math_fabs(pull_dir);
                    pull_dir*=0.020000001f;
                    vec_scale_to_length(prev_rot,prev_rot,(g_swing_rotation_strength*pull_dir)*falloff);
                    FastVecAdd(moby+0x10,moby+0x10,prev_rot);
                    FastVecAdd(moby+0x10,moby+0x10,delta);
                }
            }
        }
        FastVecSub(delta,vars+0xB0,moby+0x10);
        field_d8=(float *)(vars+0xD8);
        FastVecScale(delta,delta,g_swing_pull_scale);
        field_dc=(float *)(vars+0xDC); field_d0=(float *)(vars+0xD0);
        vec_fast_divide_helper(delta,delta,g_swing_pull_time_a*(0.020000001f));
        field_d4=(float *)(vars+0xD4);
        FastVecAdd(moby+0x10,moby+0x10,delta);
        limit=vec_distance_xy(moby+0x10,*(u8 **)(vars+0xC8)+0x10);
        secondary=vec_distance_xy(moby+0x10,target);
        limit=limit<secondary?limit:secondary;
        cursor=0;
        GetFirstMobyInGroup(&cursor,moby[0x21],0,0);
        while(cursor!=0) {
            float dist,dist_b,falloff;
            FastVecSub(delta,moby+0x10,cursor+0x10);
            dist=FastVecLength(delta);
            if(dist<g_swing_outer_push_radius) {
                dist_b=vec_distance_xy(cursor+0x10,*(u8 **)(vars+0xC8)+0x10);
                secondary=vec_distance_xy(moby+0x10,target);
                dist_b=dist_b<secondary?dist_b:secondary;
                dist=g_swing_outer_push_radius-dist;
                falloff=dist/(g_swing_outer_push_radius-g_swing_inner_push_radius);
                if(falloff>1.0f) falloff=1.0f;
                else if(falloff<0.0f) falloff=0.0f;
                vec_scale_to_length(delta,delta,dist*falloff);
                vec_fast_divide_helper(delta,delta,g_swing_push_time*(0.020000001f));
                if(limit<dist_b) {
                    float radius;
                    FastVecSub(cursor+0x10,cursor+0x10,delta);
                    FastVecSub(prev_rot,cursor+0x10,anchor);
                    radius=FastVecLength(prev_rot);
                    if(radius<g_swing_min_radius) {
                        vec_scale_to_length(prev_rot,prev_rot,g_swing_min_radius);
                        FastVecAdd(cursor+0x10,anchor,prev_rot);
                    } else if(g_swing_max_radius<radius) {
                        vec_scale_to_length(prev_rot,prev_rot,g_swing_max_radius);
                        FastVecAdd(cursor+0x10,anchor,prev_rot);
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
        math_update_wrapped_angle_offset(moby,field_d8,field_dc,0.08f,0.010471977f,-1.0f);
        moby_scale_owner_words_by_angles(moby,field_d0,field_d4,0.04363323748111725f,0.008726647f,0.010821043f);
        *(float *)(moby+0xF0)=FastAddRotations(*(float *)(vars+0x90),*(float *)(moby+0xF0));
        *(float *)(moby+0xF4)=FastAddRotations(*(float *)(vars+0x94),*(float *)(moby+0xF4));
        platform_sink_when_hit_pal(moby);
        break;
    }
    case 2:
        if(height-g_swing_sink_height_limit<*(float *)(moby+0x18)) *(float *)(moby+0x18)-=g_swing_sink_speed*(0.020000001f);
        if(math_fast_float_d(vars+0xC4)) moby_set_state(moby,3,-1);
        break;
    case 3:
        if(*(float *)(moby+0x18)<height) {
            *(float *)(moby+0x18)+=g_swing_rise_speed*(0.020000001f);
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
        FastVecSub(anchor,moby+0x10,old_pos);
        mat_combine_and_store(vars+0x50,anchor,old_rot,moby+0xF0);
    }
}
