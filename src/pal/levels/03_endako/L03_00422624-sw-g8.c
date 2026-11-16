#include "include_asm.h"

#include "common.h"
#define WORD(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define HALF(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define UHALF(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define FLOAT(p,o) (*(float *)((u8 *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; struct { float x,y,z,w; } v; } VecE2D8;
extern VecE2D8 g_laser_bot_beam_point SDATA(D_L03_001B1C30);
extern float g_laser_bot_turn_rate __attribute__((sda));
extern u8 g_camera_pose_buffer[], g_hero_position[];
typedef struct { u8 pad[0x80]; float x,y; u8 gap[0x222C]; u8 flag; } HeroE2D8;
extern HeroE2D8 g_hero_state;
extern u8 g_effect_descriptor_default[] __attribute__((sda));
extern u8 *g_linked_effect_records;
extern u8 *g_path_l03_entry_table[];
extern void laser_bot_init_check_hit_pal(u8 *);
extern void robot_update_timers(u8 *);
extern void laser_bot_trace_beam(u8 *);
extern void DrawBeamQuadsAndRingTrail(u8 *);
extern int IsPointInCuboid(void *, int);
extern void snd_stop_voice(int);
extern int moby_dispatch_action_by_kind(void *,void *);
extern int flag_set_first_pending(void *);
extern int flag_is_third_pending_set(void *);
extern void moby_set_flag_bit(void *,int);
extern float math_fabs(float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void transform_vector(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void part_spawn_masked_debris_pal(void *,float,float,int,void *,float,float,int);
extern int PlayMobySound(int,int,void *);
extern void SetDeathBits_pal(void *,int,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern f32 ApproachValue(void *,float,float);
extern float FastAddRotations(float,float);
extern int moby_l01_turn_toward_target_pal(void *,void *);
extern void gfx_add_draw_callback_first(void *,void *);
extern void moby_transform_joint_to_world(int,int,void *);
extern int coll_test_point(void *,float,int,void *);
extern void moby_mark_spawned(void *);
extern float mat_fast_helper_a(float,float);
extern float math_fast_sin_or_cos_b(float);
extern int moby_step_at_own_position_factor_pal(void *,float);
extern int coll_sweep_from_object(void *,void *,int,float,float,float,int,int,int);
extern int moby_fuse_linked_objects(void *,void *,void *,void *,int);

/* Laser bot state machine: moves along its path, traces and draws its beam, falls and explodes when killed (PAL). */
void laser_bot_update_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    int flags;
    u8 *path;
    VecE2D8 point, delta;
    float angle;
    laser_bot_init_check_hit_pal(moby);
    switch (moby[0x95]) {
    case 0:
        if (WORD(state,0x294) != -1) {
            if (!IsPointInCuboid(g_camera_pose_buffer,WORD(state,0x294))) {
                if (WORD(state,0x340) != -1) {
                    snd_stop_voice(WORD(state,0x340));
                    WORD(state,0x340) = -1;
                }
                moby[0x31] = 0;
                UHALF(moby,0x34) |= 1;
                return;
            }
            moby[0x31] = 1;
            UHALF(moby,0x34) &= 0xFFFE;
        }
        break;
    case 3:
        flags = moby_dispatch_action_by_kind(moby,state+0x60);
        if (flag_set_first_pending(moby)) {
            if (WORD(state,0x340) != -1) {
                snd_stop_voice(WORD(state,0x340));
                WORD(state,0x340) = -1;
            }
        }
        if ((flags & 1) || math_fabs(FLOAT(moby,0xF4)) > 0.1f) {
            matrix_mul_vec3(&point,&g_laser_bot_beam_point,moby+0xC0);
            FastVecAdd(&point,&point,moby+0x10);
            SpawnExplosion_pal(&point,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
            FastVecSub(&delta,moby+0x10,g_hero_position);
            delta.v.z = 0;
            vec_scale_to_length(&delta,&delta,0.120000005f);
            part_spawn_masked_debris_pal(moby,3.0f,6.0f,31,&delta,3.0f,6.0f,255);
            PlayMobySound(3,0,moby);
            SetDeathBits_pal(moby,0,3);
            moby_mark_spawned(moby);
            return;
        }
        if (flags & 2) {
            if (WORD(state,0x288)) {
                moby_set_state(moby,4,1);
                if (moby[0x43]) anim_start_blended_pal(moby,0,0,8);
            } else {
                moby_set_state(moby,3,0);
                if (moby[0x43]) anim_start_blended_pal(moby,0,0,8);
            }
        }
        break;
    }
    switch (moby[0x20]) {
    case 3:
        path = g_path_l03_entry_table[WORD(state,0x280)];
        if (flag_set_first_pending(moby)) {
            UHALF(state,0x334)=0;
            UHALF(state,0x336)=0;
        } else if (flag_is_third_pending_set(moby)) {
            moby_set_flag_bit(moby,0);
            FLOAT(state,0x134)=0.004f;
            FLOAT(state,0x130)=0.004f;
            WORD(state,0x138)=0;
        }
        ApproachValue(state+0x33C,6.0f,0.060000002f);
        laser_bot_trace_beam(moby);
        FLOAT(moby,0xF8)=FastAddRotations(FLOAT(moby,0xF8),g_laser_bot_turn_rate*0.0003490659f);
        if (moby_l01_turn_toward_target_pal(moby,path+(HALF(state,0x32C)*16+16))&0x80)
            HALF(state,0x32C)=(HALF(state,0x32C)+1)%WORD(path,0);
        if (UHALF(moby,0x96)>=6) gfx_add_draw_callback_first(DrawBeamQuadsAndRingTrail,moby);
        break;
    case 2:
        if (!WORD(state,0x290)) {
            PlayMobySound(4,0,moby);
            WORD(state,0x290)=1;
        }
        point.q=0; point.v.x=6.0f; point.v.w=1.0f;
        transform_vector(&point,&point,g_linked_effect_records+WORD(state,0x284)*128);
        if (moby_l01_turn_toward_target_pal(moby,&point)&0x80) moby_set_state(moby,3,-1);
        break;
    case 6:
        point.q=0;point.v.z=0.5f;
        matrix_mul_vec3(&point,&point,moby+0xC0);
        moby_transform_joint_to_world(WORD(state,0x338),2,&delta);
        qcopy(moby+0x10,&delta);
        FLOAT(moby,0x18)-=0.75f;
        FastVecSub(moby+0x10,moby+0x10,&point);
        ApproachValue(moby+0xF4,1.5707964f,0.12566373f);
        ApproachValue(state+0x33C,10.0f,0.080000006f);
        laser_bot_trace_beam(moby);
        gfx_add_draw_callback_first(DrawBeamQuadsAndRingTrail,moby);
        break;
    case 7:
        FLOAT(state,0x1B8)-=0.006f;
        FastVecAdd(moby+0x10,moby+0x10,state+0x1B0);
        point.q=0;point.v.z=0.5f;
        matrix_mul_vec3(&point,&point,moby+0xC0);
        FastVecAdd(&point,&point,moby+0x10);
        laser_bot_trace_beam(moby);
        gfx_add_draw_callback_first(DrawBeamQuadsAndRingTrail,moby);
        if (coll_test_point(&point,0.5f,0,moby)) {
            matrix_mul_vec3(&delta,&g_laser_bot_beam_point,moby+0xC0);
            FastVecAdd(&delta,&delta,moby+0x10);
            SpawnExplosion_pal(&delta,0,25,20,20,20,45,0,0.5f,20.0f,1,0,0,0);
            part_spawn_masked_debris_pal(moby,3.0f,6.0f,31,g_effect_descriptor_default,3.0f,6.0f,255);
            moby_mark_spawned(moby);
            return;
        }
        break;
    case 4:
        if (g_hero_state.flag == 1) moby_set_state(moby,5,-1);
        break;
    case 5:
        FLOAT(state,0x29C)=FastAddRotations(FLOAT(state,0x29C),0.12566373f);
        angle=mat_fast_helper_a(g_hero_state.x-FLOAT(moby,0x10),g_hero_state.y-FLOAT(moby,0x14));
        moby_step_at_own_position_factor_pal(moby,FastAddRotations(angle,math_fast_sin_or_cos_b(FLOAT(state,0x29C))*0.087266475f));
        laser_bot_trace_beam(moby);
        if (UHALF(moby,0x96)>=6) gfx_add_draw_callback_first(DrawBeamQuadsAndRingTrail,moby);
        if (g_hero_state.flag!=1) moby_set_state(moby,4,-1);
        break;
    case 9:
        if (flag_set_first_pending(moby)) {
            if (WORD(state,0x340)!=-1) {
                snd_stop_voice(WORD(state,0x340));
                WORD(state,0x340)=-1;
            }
        }
        if (flag_is_third_pending_set(moby)) {
            moby_set_flag_bit(moby,0);
            moby_set_state(moby,2,0);
            UHALF(moby,0x34)=(UHALF(moby,0x34)&0xFFBE)|0x1000;
            WORD(moby,0x98)=WORD(*(u8 **)(moby+0x24),0x10);
            coll_sweep_from_object(moby,moby+0x10,0x10001,0.5f,2.0f,1.0f,0,1,0);
            { u8 *transform=g_linked_effect_records+WORD(state,0x284)*128;
            moby_fuse_linked_objects(moby,transform+0x30,transform+0x70,0,0); }
            moby[0x7F]=0;
        }
        WORD(moby,0x98)=0;
        UHALF(moby,0x34)=(UHALF(moby,0x34)|0x41)&0xEFFF;
        break;
    }
    robot_update_timers(moby);
}
