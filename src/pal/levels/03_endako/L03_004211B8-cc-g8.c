/* func_PAL_L03_004211B8, the PAL copy of func_L03_0041BE50: the same C, where frame counts become 5/6 of
   their value and the 0.1 vector scale becomes 0.12 for 50 Hz. */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern float g_sweeper_bot_speed_fast SDATA(D_L03_001B1BA4) __attribute__((sda));
extern float g_sweeper_bot_speed_slow SDATA(D_L03_001B1BA0) __attribute__((sda));
extern float g_sweeper_bot_idle_scale SDATA(D_L03_001B1B90) __attribute__((sda));
extern float g_sweeper_bot_turn_range SDATA(D_L03_001B1B98) __attribute__((sda));
extern float g_sweeper_bot_local_offset[4] SDATA(D_L03_001B1BB0) __attribute__((sda));
typedef struct {
    u8 pad00[0x80]; float position[4];
    u8 pad90[0x17A0]; u8 *target;
    u8 pad1834[0xA60]; int state;
} Player;
extern Player g_hero_state;
extern u8 g_camera_pose_buffer[];
extern u8 g_effect_descriptor_default[] NOT_SDA __attribute__((sda));
/* Two bounds of the spin-angle range, with an absolute view of its upper bound. */
extern float D_L03_001B1B98_abs[] __asm__("D_L03_001B1B98") __attribute__((sda));
extern int g_bot_hit_count;
extern int g_bot_hit_flag[] __attribute__((sda));
/* The 32 skill-point flags scanned by func_002B0E90. */
extern u8 g_item_enabled_flags[32] __attribute__((sda));
/* The same path-table pointer is read absolutely and through GP. */
extern u8 *g_linked_effect_records[] __attribute__((sda));
extern u8 *D_L03_001B2B0C_gp SDATA(D_L03_001B2B0C) __attribute__((sda));
extern u8 *g_collision_hit_result NOT_SDA;
extern void sweeper_bot_update_core_pal(void *);
extern int IsPointInCuboid(void *,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended_pal(void *,int,int,int);
extern float vec_distance_xy(void *,void *);
extern int flag_set_second_pending(void *);
extern float math_random_signed_float_range(float,float);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern int PlayMobySound(int,int,void *);
extern void part_spawn_explosion_with_sparks_pal(void *,void *,int,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_masked_debris_pal(void *,int,void *,float,float,float,float,int);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_pal(int,int);
extern void SetDeathBits_pal(void *,int,int);
extern void moby_mark_spawned(void *);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float),math_random_angle(void),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void path_clamp_move_to_area(void *,void *,void *,int,float);
extern int flag_set_first_pending(void *),moby_l01_turn_toward_target_pal(void *,void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int math_fast_float_d(void *),flag_is_third_pending_set(void *);
extern int enemy_aim_toward_target_pal(void *,void *,int,float,float,float);
extern int moby_move_to_target_temp_limits_pal(void *,void *,int,float,float,float);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern int coll_test_point(void *,int,void *,float);
extern void moby_set_flag_bit(void *,int),sweeper_bot_reset_delays_pal(void *);
extern int moby_fuse_linked_objects(void *,void *,void *,int,int);
extern void transform_vector(void *,void *,void *);
extern int path_check_point_reached(void *);
extern void sweeper_bot_update_warning_light_pal(void *);
/* Updates the actor's combat and movement states, including hiding and respawning. */
void UpdateEndakoRespawningEnemy_pal(u8 *moby) {
    u8 *state=P(moby,0x68);
    Vec vec_a,vec_b;
    float speed,scale,angle;
    int hit;
    sweeper_bot_update_core_pal(moby);
    speed=I(state,0x29c) ? g_sweeper_bot_speed_fast : g_sweeper_bot_speed_slow;
    scale=I(state,0x29c) ? 1.0f : g_sweeper_bot_idle_scale;
    switch(moby[0x95]) {
    case 0:
        if(I(state,0x2a8)!=-1) {
            hit=IsPointInCuboid(g_camera_pose_buffer,I(state,0x2a8));
            if(!hit) { moby[0x31]=0; U(moby,0x34)|=1; return; }
            moby[0x31]=1; U(moby,0x34)&=0xfffe;
        }
        if(I(state,0x204)!=1) {
            if(H(state,0x2d6)) {
                moby_set_state(moby,3,1);
                H(state,0x2d6)=0;
                if(H(state,0x2d0)<250) H(state,0x2d0)=((s32)math_random_int_range(480,600)*5+2)/6;
            }
            break;
        }
        /* Fall through to the active-state transition. */
    case 1:
        if(I(state,0x204)==1) {
            moby_set_state(moby,5,2);
            if(moby[0x43]) anim_start_blended_pal(moby,0,0,8);
        } else if(vec_distance_xy(moby+0x10,g_hero_state.position)>24.0f && H(state,0x2d0)==0) moby_set_state(moby,1,0);
        break;
    case 2:
        if(flag_set_second_pending(moby)) { float upper=D_L03_001B1B98_abs[1]; F(state,0x2e0)=math_random_signed_float_range(g_sweeper_bot_turn_range,upper)*0.017453294f; }
        if(I(state,0x204)!=1) {
            moby_set_state(moby,3,1);
            if(moby[0x43]) anim_start_blended_pal(moby,0,0,8);
            H(state,0x2d0)=((s32)math_random_int_range(580,600)*5+2)/6;
        }
        break;
    case 3:
        hit=moby_dispatch_action_by_kind(moby,state+0x140);
        if(hit&1) {
            matrix_mul_vec3(&vec_a,g_sweeper_bot_local_offset,moby+0xc0);
            FastVecAdd(&vec_a,&vec_a,moby+0x10);
            PlayMobySound(2,0,moby);
            part_spawn_explosion_with_sparks_pal(moby,&vec_a,-1,0.333f,0.0f);
            FastVecSub(&vec_b,moby+0x10,g_hero_state.position);
            vec_b.f[2]=0;
            vec_scale_to_length(&vec_b,&vec_b,0.120000005f);
            part_spawn_masked_debris_pal(moby,31,g_effect_descriptor_default,3.0f,6.0f,3.0f,6.0f,255);
            if(g_hero_state.state==49) {
                g_bot_hit_count=g_bot_hit_count+1;
                if(g_bot_hit_count>=10 && !g_item_enabled_flags[28]) {
                    g_item_enabled_flags[28]=1; snd_play_from_global_bank(1,0,0); value_set_entry_by_index_pal(0x1233,-1); g_bot_hit_flag[0]=1;
                }
            }
            SetDeathBits_pal(moby,0,3);
            if(I(state,0x2a4)) {
                moby_set_state(moby,8,4); I(moby,0x98)=0; U(moby,0x34)=(U(moby,0x34)|0x41)&0xefff;
            } else {moby_mark_spawned(moby);return;}
        } else if(hit&2) {
            if(I(state,0x204)==1) moby_set_state(moby,6,2);
            else {moby_set_state(moby,3,1); H(state,0x2d0)=((s32)math_random_int_range(580,600)*5+2)/6;}
        }
        break;
    }
    switch(moby[0x20]) {
    case 1:
        if(moby[0x31] && U(moby,0x96)>8 && vec_distance_xy(moby+0x10,g_camera_pose_buffer)<50.0f) {
            speed=math_random_float_range(2.0f,5.0f); angle=math_random_angle();
            F(state,0x2c0)=math_fast_sin_or_cos_a(angle)*speed;
            F(state,0x2c4)=math_fast_sin_or_cos_b(angle)*speed; I(state,0x2c8)=0;
            FastVecAdd(state+0x2c0,state+0x2c0,state+0x2b0);
            vec_a.q=*(Quad *)(state+0x2b0);
            path_clamp_move_to_area(&vec_a,state+0x2c0,state+0x2c0,I(state,0x290),1.5f);
            moby_set_state(moby,2,-1);
        }
        break;
    case 2:
        if(flag_set_first_pending(moby)) I(state,0x88)&=~0x10;
        if((moby_l01_turn_toward_target_pal(moby,state+0x2c0)&0x80)||U(moby,0x96)>250) moby_set_state(moby,1,-1);
        break;
    case 3:
        {
            float heading;
            if(g_hero_state.state==49) {
                u8 *target=g_hero_state.target;
                heading=mat_fast_helper_a(F(target,0x10)-F(moby,0x10),F(target,0x14)-F(moby,0x14));
            } else {
                heading=mat_fast_helper_a(g_hero_state.position[0]-F(moby,0x10),g_hero_state.position[1]-F(moby,0x14));
            }
            moby_start_effect_from_entry(moby,heading);
        }
        if(U(moby,0x96)>8) moby_set_state(moby,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(moby)) {
            I(state,0x88)|=0x10;
            speed=math_random_float_range(2.0f,5.0f); angle=math_random_angle();
            F(state,0x2c0)=math_fast_sin_or_cos_a(angle)*speed;
            F(state,0x2c4)=math_fast_sin_or_cos_b(angle)*speed; I(state,0x2c8)=0;
            FastVecAdd(state+0x2c0,state+0x2c0,state+0x2b0);
            vec_a.q=*(Quad *)(state+0x2b0);
            path_clamp_move_to_area(&vec_a,state+0x2c0,state+0x2c0,I(state,0x290),1.0f);
        }
        {
            float heading;
            if(g_hero_state.state==49) {
                u8 *target=g_hero_state.target;
                heading=mat_fast_helper_a(F(target,0x10)-F(moby,0x10),F(target,0x14)-F(moby,0x14));
            } else {
                heading=mat_fast_helper_a(g_hero_state.position[0]-F(moby,0x10),g_hero_state.position[1]-F(moby,0x14));
            }
            moby_start_effect_from_entry(moby,heading);
        }
        if((moby_l01_turn_toward_target_pal(moby,state+0x2c0)&0x80)||U(moby,0x96)>250) moby_set_state(moby,3,-1);
        break;
    case 5:
        if(flag_set_first_pending(moby)) PlayMobySound(5,0,moby);
        if(math_fast_float_d(state+0x2e4) && I(state,0xd0)>50) {I(state,0x2e4)=50; F(state,0x2e0)=-F(state,0x2e0);}
        angle=mat_fast_helper_a(F(state,0x1f0)-F(moby,0x10),F(state,0x1f4)-F(moby,0x14));
        moby_start_effect_from_entry(moby,angle);
        enemy_aim_toward_target_pal(moby,state+0x1f0,16,F(state,0x2e0),-1.0f,-1.0f);
        if(U(moby,0x96)>50 && vec_distance_xy(moby+0x10,g_hero_state.position)<scale*speed) {
            moby_set_state(moby,6,-1);
            if(moby[0x43]!=1) anim_start_blended_pal(moby,1,0,8);
        }
        break;
    case 6: {
        if(U(moby,0x96)>37) {
            moby_set_state(moby,5,-1); if(moby[0x43]) anim_start_blended_pal(moby,0,0,8);
        } else if(U(moby,0x96)>8) {
            qcopy(&vec_a,moby+0x10); vec_a.f[2]+=0.25f;
            coll_sweep_from_object(moby,&vec_a,0x4000001,0,1,0,speed*1.25f,(float)state[0x34],1.0f);
        }
        {
            float *target=(float *)(state+0x1f0);
            angle=mat_fast_helper_a(F(state,0x1f0)-F(moby,0x10),F(state,0x1f4)-F(moby,0x14)); moby_start_effect_from_entry(moby,angle);
            {
                float x=target[0];
                angle=mat_fast_helper_a(x-F(moby,0x10),F(state,0x1f4)-F(moby,0x14));
                moby_move_to_target_temp_limits_pal(moby,target,16,angle,-1.0f,-1.0f);
            }
        }
        break;
    }
    case 8:
        if(flag_is_third_pending_set(moby) && math_fast_float_d(state+0x2d8)) {
            if(I(state,0x2a0)!=-1) {
                qcopy(&vec_a,D_L03_001B2B0C_gp+I(state,0x2a0)*128+0x30);
                vec_a.f[2]=coll_probe_ground_height_below(&vec_a,0,0.5f); qcopy(&vec_b,&vec_a);
                vec_b.f[2]+=F(state,0x50)+0.1f;
                coll_test_point(&vec_b,0,moby,F(state,0x50));
                if(!g_collision_hit_result || H(g_collision_hit_result,0xaa)!=MOBY_CLASS_MEGACORP_SWEEPER_BOT) {
                    moby_set_flag_bit(moby,0); I(state,0x8c)=-1; sweeper_bot_reset_delays_pal(moby);moby_set_state(moby,9,-1);
                    U(moby,0x34)=(U(moby,0x34)&0xffbe)|0x1000; I(moby,0x98)=I(P(moby,0x24),0x10);
                    if(moby[0x43])anim_start_blended_pal(moby,0,0,0);
                    H(state,0x178)=0;
                    coll_sweep_from_object(moby,&vec_b,0x10001,0,1,0,F(state,0x50),2.0f,1.0f);
                    moby_fuse_linked_objects(moby,&vec_a,g_linked_effect_records[0]+I(state,0x2a0)*128+0x70,0,0);
                } else {I(state,0x2d8)=((s32)math_random_int_range(10,20)*5+2)/6;}
            } else if(vec_distance_xy(g_hero_state.position,state+0x2b0)>5.0f) {
                moby_set_flag_bit(moby,0);sweeper_bot_reset_delays_pal(moby); H(state,0x178)=0;F(state,0x20)=(float)H(state,0x24);
                moby_set_state(moby,9,-1);
                U(moby,0x34)=(U(moby,0x34)&0xffbe)|0x1000;I(moby,0x98)=I(P(moby,0x24),0x10);
                if(moby[0x43])anim_start_blended_pal(moby,0,0,0);
                vec_b.q=0;vec_b.f[2]=math_random_angle();vec_a.q=vec_b.q;
                moby_fuse_linked_objects(moby,state+0x2b0,&vec_a,0,0);
            }
        }
        break;
    case 9:
        if(!I(state,0x2ac)) {PlayMobySound(3,0,moby);I(state,0x2ac)=1;}
        vec_a.q=0;vec_a.f[0]=6.0f;vec_a.f[3]=1.0f;
        transform_vector(&vec_a,&vec_a,g_linked_effect_records[0]+I(state,0x2a0)*128);
        moby_l01_turn_toward_target_pal(moby,&vec_a);
        if(path_check_point_reached(moby)) {I(state,0x8c)=I(state,0x290);moby_set_state(moby,5,2);}
        break;
    }
    sweeper_bot_update_warning_light_pal(moby);
}
