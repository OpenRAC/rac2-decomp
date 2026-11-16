#include "include_asm.h"

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
extern float D_L03_001B1B98_abs[] __asm__("D_L03_001B1B98") __attribute__((sda));
extern int g_bot_hit_count;
extern int g_bot_hit_flag[] __attribute__((sda));
extern u8 g_item_enabled_flags[32] __attribute__((sda));
extern u8 *g_linked_effect_records[] __attribute__((sda));
extern u8 *D_L03_001B2B0C_gp SDATA(D_L03_001B2B0C) __attribute__((sda));
extern u8 *g_collision_hit_result NOT_SDA;
extern void sweeper_bot_update_core_us2(void *);
extern int IsPointInCuboid(void *,int);
extern void moby_set_state(void *,int,int);
extern void anim_start_blended(void *,int,int,int);
extern float vec_distance_xy(void *,void *);
extern int flag_set_second_pending(void *);
extern float math_random_signed_float_range(float,float);
extern int moby_dispatch_action_by_kind(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern int PlayMobySound(int,int,void *);
extern void part_spawn_explosion_with_sparks(void *,void *,int,float,float);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void part_spawn_masked_debris(void *,int,void *,float,float,float,float,int);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_us2(int,int);
extern void func_US2_002A7AA8(void *,int,int);
extern void moby_mark_spawned(void *);
extern int math_random_int_range(int,int);
extern float math_random_float_range(float,float),math_random_angle(void),math_fast_sin_or_cos_a(float),math_fast_sin_or_cos_b(float);
extern void path_clamp_move_to_area(void *,void *,void *,int,float);
extern int flag_set_first_pending(void *),moby_l01_turn_toward_target(void *,void *);
extern float mat_fast_helper_a(float,float);
extern int moby_start_effect_from_entry(void *,float);
extern int math_fast_float_d(void *),flag_is_third_pending_set(void *);
extern int enemy_aim_toward_target(void *,void *,int,float,float,float);
extern int moby_move_to_target_temp_limits(void *,void *,int,float,float,float);
extern int coll_sweep_from_object(void *,void *,int,int,int,int,float,float,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern int coll_test_point(void *,int,void *,float);
extern void moby_set_flag_bit(void *,int),sweeper_bot_reset_delays(void *);
extern int moby_fuse_linked_objects(void *,void *,void *,int,int);
extern void transform_vector(void *,void *,void *);
extern int path_check_point_reached(void *);
extern void sweeper_bot_update_warning_light(void *);

/* Updates the actor's combat and movement states, including hiding and respawning. */
void UpdateEndakoRespawningEnemy_us2(u8 *e) {
    u8 *s=P(e,0x68);
    Vec a,b;
    float speed,scale,angle;
    int hit;
    sweeper_bot_update_core_us2(e);
    speed=I(s,0x29c) ? g_sweeper_bot_speed_fast : g_sweeper_bot_speed_slow;
    scale=I(s,0x29c) ? 1.0f : g_sweeper_bot_idle_scale;
    switch(e[0x95]) {
    case 0:
        if(I(s,0x2a8)!=-1) {
            hit=IsPointInCuboid(g_camera_pose_buffer,I(s,0x2a8));
            if(!hit) { e[0x31]=0; U(e,0x34)|=1; return; }
            e[0x31]=1; U(e,0x34)&=0xfffe;
        }
        if(I(s,0x204)!=1) {
            if(H(s,0x2d6)) {
                moby_set_state(e,3,1);
                H(s,0x2d6)=0;
                if(H(s,0x2d0)<300) H(s,0x2d0)=math_random_int_range(480,600);
            }
            break;
        }
        /* Fall through to the active-state transition. */
    case 1:
        if(I(s,0x204)==1) {
            moby_set_state(e,5,2);
            if(e[0x43]) anim_start_blended(e,0,0,10);
        } else if(vec_distance_xy(e+0x10,g_hero_state.position)>24.0f && H(s,0x2d0)==0) moby_set_state(e,1,0);
        break;
    case 2:
        if(flag_set_second_pending(e)) { float upper=D_L03_001B1B98_abs[1]; F(s,0x2e0)=math_random_signed_float_range(g_sweeper_bot_turn_range,upper)*0.017453294f; }
        if(I(s,0x204)!=1) {
            moby_set_state(e,3,1);
            if(e[0x43]) anim_start_blended(e,0,0,10);
            H(s,0x2d0)=math_random_int_range(580,600);
        }
        break;
    case 3:
        hit=moby_dispatch_action_by_kind(e,s+0x140);
        if(hit&1) {
            matrix_mul_vec3(&a,g_sweeper_bot_local_offset,e+0xc0);
            FastVecAdd(&a,&a,e+0x10);
            PlayMobySound(2,0,e);
            part_spawn_explosion_with_sparks(e,&a,-1,0.333f,0.0f);
            FastVecSub(&b,e+0x10,g_hero_state.position);
            b.f[2]=0;
            vec_scale_to_length(&b,&b,0.10000001f);
            part_spawn_masked_debris(e,31,g_effect_descriptor_default,3.0f,6.0f,3.0f,6.0f,255);
            if(g_hero_state.state==49) {
                g_bot_hit_count=g_bot_hit_count+1;
                if(g_bot_hit_count>=10 && !g_item_enabled_flags[28]) {
                    g_item_enabled_flags[28]=1; snd_play_from_global_bank(1,0,0); value_set_entry_by_index_us2(0x1233,-1); g_bot_hit_flag[0]=1;
                }
            }
            func_US2_002A7AA8(e,0,3);
            if(I(s,0x2a4)) {
                moby_set_state(e,8,4); I(e,0x98)=0; U(e,0x34)=(U(e,0x34)|0x41)&0xefff;
            } else {moby_mark_spawned(e);return;}
        } else if(hit&2) {
            if(I(s,0x204)==1) moby_set_state(e,6,2);
            else {moby_set_state(e,3,1); H(s,0x2d0)=math_random_int_range(580,600);}
        }
        break;
    }
    switch(e[0x20]) {
    case 1:
        if(e[0x31] && U(e,0x96)>10 && vec_distance_xy(e+0x10,g_camera_pose_buffer)<50.0f) {
            speed=math_random_float_range(2.0f,5.0f); angle=math_random_angle();
            F(s,0x2c0)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x2c4)=math_fast_sin_or_cos_b(angle)*speed; I(s,0x2c8)=0;
            FastVecAdd(s+0x2c0,s+0x2c0,s+0x2b0);
            a.q=*(Quad *)(s+0x2b0);
            path_clamp_move_to_area(&a,s+0x2c0,s+0x2c0,I(s,0x290),1.5f);
            moby_set_state(e,2,-1);
        }
        break;
    case 2:
        if(flag_set_first_pending(e)) I(s,0x88)&=~0x10;
        if((moby_l01_turn_toward_target(e,s+0x2c0)&0x80)||U(e,0x96)>300) moby_set_state(e,1,-1);
        break;
    case 3:
        {
            float heading;
            if(g_hero_state.state==49) {
                u8 *target=g_hero_state.target;
                heading=mat_fast_helper_a(F(target,0x10)-F(e,0x10),F(target,0x14)-F(e,0x14));
            } else {
                heading=mat_fast_helper_a(g_hero_state.position[0]-F(e,0x10),g_hero_state.position[1]-F(e,0x14));
            }
            moby_start_effect_from_entry(e,heading);
        }
        if(U(e,0x96)>10) moby_set_state(e,4,-1);
        break;
    case 4:
        if(flag_set_first_pending(e)) {
            I(s,0x88)|=0x10;
            speed=math_random_float_range(2.0f,5.0f); angle=math_random_angle();
            F(s,0x2c0)=math_fast_sin_or_cos_a(angle)*speed;
            F(s,0x2c4)=math_fast_sin_or_cos_b(angle)*speed; I(s,0x2c8)=0;
            FastVecAdd(s+0x2c0,s+0x2c0,s+0x2b0);
            a.q=*(Quad *)(s+0x2b0);
            path_clamp_move_to_area(&a,s+0x2c0,s+0x2c0,I(s,0x290),1.0f);
        }
        {
            float heading;
            if(g_hero_state.state==49) {
                u8 *target=g_hero_state.target;
                heading=mat_fast_helper_a(F(target,0x10)-F(e,0x10),F(target,0x14)-F(e,0x14));
            } else {
                heading=mat_fast_helper_a(g_hero_state.position[0]-F(e,0x10),g_hero_state.position[1]-F(e,0x14));
            }
            moby_start_effect_from_entry(e,heading);
        }
        if((moby_l01_turn_toward_target(e,s+0x2c0)&0x80)||U(e,0x96)>300) moby_set_state(e,3,-1);
        break;
    case 5:
        if(flag_set_first_pending(e)) PlayMobySound(5,0,e);
        if(math_fast_float_d(s+0x2e4) && I(s,0xd0)>60) {I(s,0x2e4)=60; F(s,0x2e0)=-F(s,0x2e0);}
        angle=mat_fast_helper_a(F(s,0x1f0)-F(e,0x10),F(s,0x1f4)-F(e,0x14));
        moby_start_effect_from_entry(e,angle);
        enemy_aim_toward_target(e,s+0x1f0,16,F(s,0x2e0),-1.0f,-1.0f);
        if(U(e,0x96)>60 && vec_distance_xy(e+0x10,g_hero_state.position)<scale*speed) {
            moby_set_state(e,6,-1);
            if(e[0x43]!=1) anim_start_blended(e,1,0,10);
        }
        break;
    case 6: {
        if(U(e,0x96)>45) {
            moby_set_state(e,5,-1); if(e[0x43]) anim_start_blended(e,0,0,10);
        } else if(U(e,0x96)>10) {
            qcopy(&a,e+0x10); a.f[2]+=0.25f;
            coll_sweep_from_object(e,&a,0x4000001,0,1,0,speed*1.25f,(float)s[0x34],1.0f);
        }
        {
            float *target=(float *)(s+0x1f0);
            angle=mat_fast_helper_a(F(s,0x1f0)-F(e,0x10),F(s,0x1f4)-F(e,0x14)); moby_start_effect_from_entry(e,angle);
            {
                float x=target[0];
                angle=mat_fast_helper_a(x-F(e,0x10),F(s,0x1f4)-F(e,0x14));
                moby_move_to_target_temp_limits(e,target,16,angle,-1.0f,-1.0f);
            }
        }
        break;
    }
    case 8:
        if(flag_is_third_pending_set(e) && math_fast_float_d(s+0x2d8)) {
            if(I(s,0x2a0)!=-1) {
                qcopy(&a,D_L03_001B2B0C_gp+I(s,0x2a0)*128+0x30);
                a.f[2]=coll_probe_ground_height_below(&a,0,0.5f); qcopy(&b,&a);
                b.f[2]+=F(s,0x50)+0.1f;
                coll_test_point(&b,0,e,F(s,0x50));
                if(!g_collision_hit_result || H(g_collision_hit_result,0xaa)!=0xff3) {
                    moby_set_flag_bit(e,0); I(s,0x8c)=-1; sweeper_bot_reset_delays(e);moby_set_state(e,9,-1);
                    U(e,0x34)=(U(e,0x34)&0xffbe)|0x1000; I(e,0x98)=I(P(e,0x24),0x10);
                    if(e[0x43])anim_start_blended(e,0,0,0);
                    H(s,0x178)=0;
                    coll_sweep_from_object(e,&b,0x10001,0,1,0,F(s,0x50),2.0f,1.0f);
                    moby_fuse_linked_objects(e,&a,g_linked_effect_records[0]+I(s,0x2a0)*128+0x70,0,0);
                } else {I(s,0x2d8)=math_random_int_range(10,20);}
            } else if(vec_distance_xy(g_hero_state.position,s+0x2b0)>5.0f) {
                moby_set_flag_bit(e,0);sweeper_bot_reset_delays(e); H(s,0x178)=0;F(s,0x20)=(float)H(s,0x24);
                moby_set_state(e,9,-1);
                U(e,0x34)=(U(e,0x34)&0xffbe)|0x1000;I(e,0x98)=I(P(e,0x24),0x10);
                if(e[0x43])anim_start_blended(e,0,0,0);
                b.q=0;b.f[2]=math_random_angle();a.q=b.q;
                moby_fuse_linked_objects(e,s+0x2b0,&a,0,0);
            }
        }
        break;
    case 9:
        if(!I(s,0x2ac)) {PlayMobySound(3,0,e);I(s,0x2ac)=1;}
        a.q=0;a.f[0]=6.0f;a.f[3]=1.0f;
        transform_vector(&a,&a,g_linked_effect_records[0]+I(s,0x2a0)*128);
        moby_l01_turn_toward_target(e,&a);
        if(path_check_point_reached(e)) {I(s,0x8c)=I(s,0x290);moby_set_state(e,5,2);}
        break;
    }
    sweeper_bot_update_warning_light(e);
}
