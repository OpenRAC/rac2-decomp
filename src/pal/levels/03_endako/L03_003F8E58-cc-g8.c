#include "names.h"
/* func_PAL_L03_003F8E58, the PAL copy of func_L03_003F4638: the same C, where rename func_L03_003F5590 becomes func_PAL_L03_003F9DE0; rename func_002A7470 becomes func_PAL_002A7E68; rename func_L03_003F62C8 becomes func_PAL_L03_003FAB20; rename func_L03_003D9820 becomes func_PAL_L03_003DDB50; rename func_002AEB60 becomes func_PAL_002AF6C0; rename func_L03_003E18D8 becomes func_PAL_L03_003E5DE8; rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_0032DA58 becomes func_PAL_0032F3B8; rename func_002A6C58 becomes func_PAL_002A7650; rename func_L03_003F6080 becomes func_PAL_L03_003FA8D8; scale D_L03_001B1040; wrap H(e,0x96) (((int)({e}) * 5 + 2) / 6); .... */
/* The 15-state per-frame update of one Endako entity. -G8 for its small data;
 * -g (config/cflags.txt) gives the two nops retail has before state 12's div.s.
 *
 * func_002AA800 returns the angle still left, the result of its last call to
 * func_002AA738, as RAC1's ApproachValue returns the distance left. No caller
 * here reads it, but the call still defines $f0: that is why state 14's copy
 * right after it takes $f1.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define H(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define Q(p,o) (*(Quad *)((u8 *)(p)+(o)))
extern u8 g_hero_l03_position[], g_str_clank_scene_key[], g_camera_pose_buffer[];
typedef struct {u8 pad[0x80]; float position[4];} HeroState;
extern HeroState g_hero_l03_state_block;
extern u8 g_endako_boss_flags[2] NOT_SDA;
extern u8 *g_path_l03_entry_table[], *g_moby_record_base;
extern u8 g_sound_l03_slot_table[];
extern int g_endako_boss_zone_check_enabled __attribute__((sda)), g_endako_boss_launch_queued __attribute__((sda)), g_hero_l03_mode __attribute__((sda));
extern float g_endako_boss_blend_rate __attribute__((sda)), g_endako_boss_move_speed_a __attribute__((sda)), g_endako_boss_move_speed_b __attribute__((sda));
extern int g_endako_boss_attack_interval __attribute__((sda)), g_endako_boss_turn_count __attribute__((sda));
extern float g_endako_boss_lateral_offsets[3] SDATA(D_L03_001B1030);
extern float g_endako_boss_height_limit __attribute__((sda));
extern int g_frame_l03_counter;
extern void endako_boss_update_damage_pal(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_set_state(void *, int, int);
extern float mat_fast_helper_a(float,float);
extern int req_push_queue(void *,int);
extern s32 req_launch_queued(void *);
extern void moby_set_flag_bit(void *,int);
extern void script_queue_keyed_request(int,int);
extern int flag_set_first_pending(void *);
extern void anim_start_blended_pal(void *,int,int,int);
extern void endako_boss_pick_pose(void *,int);
extern int math_fast_float_d(void *);
extern void boss_choose_next_behaviour_pal(void *);
extern float math_fabs(float);
extern f32 ApproachValue(void *,float,float);
extern float math_random_signed_float_range(float,float);
extern void moby_transform_joint_point(void *,int,void *);
extern void transform_vector(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern int PlayMobySound(int,int,void *);
extern u8 *spark_shot_spawn_pal(void *,void *,void *,int);
extern void endako_boss_add_target(void *,int);
extern int math_random_int_range(int,int);
extern int math_is_value_within_step_pal(void *,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern u8 *object_spawn_and_init_pal(void *,void *,void *,void *,int,float,float,int,int,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern char *part_create_interpolated_emitter(void *,int,void *,void *,void *,int,int,int);
extern float math_random_float_range(float,float);
extern char *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern float StepAngleTowardTarget(void *,int,float,float);
extern char *part_spawn_blast_effect_moby_pal(void *,void *,void *,float);
extern float FastAddRotations(float,float);
extern float IntToFloat(int);
extern void SetDeathBits_pal(void *,int,int);
extern void cam_end_override(int);
extern void moby_mark_spawned(void *);
extern void moby_mark_table_entry_flagged(int);
extern void snd_stop_voice(int);
extern void endako_boss_update_helpers_pal(void *);

typedef struct {
    u8 pad[0x80];
    int paths[3], activation[2], trigger, ready[2];
    u8 padA0[0x2A0-0xA0];
    float angles[4];
    u8 pad2B0[0x2E8-0x2B0];
    float blend[4], target[2];
} AttackState;

/* Endako boss update (PAL): runs the damage update, then the 15 behaviour states (walk the path,
   attack, spit objects, die in explosions), then the helpers. */
void endako_boss_update_pal(u8 *entity) {
    u8 *state=*(u8 **)(entity+0x68);
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float work[16] __attribute__((aligned(16)));
    int i;
    endako_boss_update_damage_pal(entity);
    switch(entity[0x20]) {
    case 1:
        if (IsPointInCuboid(g_hero_l03_position,((AttackState *)state)->activation[I(state,0x2D4)])) {
            u8 *path;
            moby_set_state(entity,2,-1);
            H(entity,0x34)=(H(entity,0x34)&0xFFBE)|0x1000;
            I(entity,0x98)=I(*(u8 **)(entity+0x24),0x10);
            path=g_path_l03_entry_table[((AttackState *)state)->paths[I(state,0x2D4)]];
            I(state,0x2D8)=0; *(u8 **)(state+0x2CC)=path; I(state,0x2DC)=0;
            qcopy(state+0x290,path+0x10);
            F(state,0x298)-=7.0f;
            qcopy(entity+0x10,state+0x290); qzero(state+0x2A0);
            F(state,0x2A8)=mat_fast_helper_a(g_hero_l03_state_block.position[0]-F(entity,0x10),g_hero_l03_state_block.position[1]-F(entity,0x14));
            F(state,0x2D0)=0.20000002f;
        }
        if(IsPointInCuboid(g_hero_l03_position,I(state,0x94))) moby_set_state(entity,4,-1);
        break;
    case 2:
        if(IsPointInCuboid(g_hero_l03_position,((AttackState *)state)->ready[I(state,0x2D4)])) {
            g_endako_boss_flags[0]=1; moby_set_state(entity,3,-1);
            I(state,0x2DC)=I(*(u8 **)(state+0x2CC),0)-1;
        }
        break;
    case 3:
        if(I(state,0x2D8)==I(state,0x2DC)) {
            if(I(state,0x2D4)==0) {
                I(entity,0x98)=0; H(entity,0x34)=(H(entity,0x34)|0x41)&0xEFFF;
                moby_set_state(entity,1,-1); I(state,0x2D4)++;
            } else {
                I(entity,0x98)=0; H(entity,0x34)=(H(entity,0x34)|0x41)&0xEFFF;
                moby_set_state(entity,4,-1);
            }
        }
        break;
    case 4:
        if(g_endako_boss_zone_check_enabled && IsPointInCuboid(g_hero_l03_position,I(state,0x94))) {
            if(g_endako_boss_launch_queued) moby_set_state(entity,5,-1);
            else if(req_push_queue(g_str_clank_scene_key,0x36)) {
                g_endako_boss_launch_queued=1;req_launch_queued(g_str_clank_scene_key);moby_set_state(entity,5,-1);
            }
        }
        break;
    case 5:
        if(H(entity,0x96)>=18 && g_hero_l03_mode!=2) {
            u8 *path;
            moby_set_state(entity,6,2);
            H(entity,0x34)=(H(entity,0x34)&0xFFBE)|0x1000;
            I(entity,0x98)=I(*(u8 **)(entity+0x24),0x10);
            path=g_path_l03_entry_table[I(state,0x88)];
            I(state,0x2DC)=I(state,0x320); *(u8 **)(state+0x2CC)=path; I(state,0x2D8)=I(state,0x320);
            qcopy(state+0x290,path+I(state,0x320)*16+0x10); qcopy(entity+0x10,state+0x290);
            F(state,0x2A8)=mat_fast_helper_a(g_hero_l03_state_block.position[0]-F(entity,0x10),g_hero_l03_state_block.position[1]-F(entity,0x14));
            F(entity,0xF8)=F(state,0x2A8);
            {u8 *linked=g_moby_record_base+(I(state,0xA8)<<8);
            F(state,0x2D0)=0.20000002f; I(state,0x2E0)=50; F(state,0x298)-=7.0f;
            moby_set_flag_bit(linked,0);}
            script_queue_keyed_request(I(state,0xB0),-1);
        }
        break;
    case 6:
        if(flag_set_first_pending(entity)) {
            if(entity[0x43]!=0) anim_start_blended_pal(entity,0,0,5);
            if(entity[0x94]!=4) endako_boss_pick_pose(entity,entity[0x94]!=8);
        }
        if(I(state,0x2D8)==I(state,0x2DC) && math_fast_float_d(state+0x2E0)) boss_choose_next_behaviour_pal(entity);
        break;
    case 7: {
        int done=1;
        F(state,0x178)=F(state,0x2F8); F(state,0x1F8)=F(state,0x2FC);
        if(math_fabs(F(state,0x158)-F(state,0x2F8))>0.01f) done=0;
        else if(math_fabs(F(state,0x1D8)-F(state,0x2FC))>0.01f) done=0;
        if(done) {
            if(F(state,0x2F8)!=0 && F(state,0x2FC)!=0) {if(entity[0x43]!=3) anim_start_blended_pal(entity,3,0,4);}
            else if(F(state,0x2F8)!=0) {if(entity[0x43]!=1) anim_start_blended_pal(entity,1,0,4);}
            else {if(entity[0x43]!=2) anim_start_blended_pal(entity,2,0,4);}
            moby_set_state(entity,8,-1);
            {float first=((AttackState *)state)->target[0],second=((AttackState *)state)->target[1];
            ((AttackState *)state)->blend[2]=(((AttackState *)state)->blend[0]=first,((AttackState *)state)->blend[1]=second,((AttackState *)state)->blend[3]=0.0f);}
        }
        break;
    }
    case 8: {
        int done=1,value;
        for(i=0;i<2;i++) {
            if(((AttackState *)state)->target[i]!=0) {
                ApproachValue(&((AttackState *)state)->blend[i],-((AttackState *)state)->target[i],g_endako_boss_blend_rate*0.0003490659f);
                F(state,0x178+i*0x80)=((AttackState *)state)->blend[i];
                if(math_fabs(((AttackState *)state)->blend[i]+((AttackState *)state)->target[i])>0.01f) done=0;
                if(((g_frame_l03_counter+i*4)&7)==0) {
                    Q(vel,0)=0; vel[1]=math_random_signed_float_range(0,0.1f);vel[2]=math_random_signed_float_range(0,0.1f);vel[3]=1;
                    Q(pos,0)=Q(vel,0);moby_transform_joint_point(entity,i+2,work);transform_vector(pos,pos,work);
                    vec_scale_to_length(vel,work,g_endako_boss_move_speed_a*0.020000001f);
                    PlayMobySound(3,0,entity);value=spark_shot_spawn_pal(entity,pos,vel,state[0x34]);endako_boss_add_target(entity,value);
                }
            }
        }
        if(done) {F(state,0x2F8)=F(state,0x2FC)=0;moby_set_state(entity,6,2);}
        break;
    }
    case 9: break;
    case 10:
        if(flag_set_first_pending(entity)) {
            switch(S(state,0x3C2)) {
            case 3: I(state,0x33C)=math_random_int_range(4,6); break;
            case 2: I(state,0x33C)=math_random_int_range(3,5); break;
            case 1: default: I(state,0x33C)=math_random_int_range(2,3); break;
            }
            if(entity[0x43]!=4) anim_start_blended_pal(entity,4,0,4);
        }
        if(entity[0x60]&2) moby_set_state(entity,11,-1);
        break;
    case 11: {
        int value;
        if(flag_set_first_pending(entity) && entity[0x43]!=6) anim_start_blended_pal(entity,6,0,4);
        if(math_is_value_within_step_pal(entity,2.0f)) {
            moby_transform_joint_to_world(entity,4,pos);qcopy(vel,entity+0xC0);vel[2]=0;
            vec_scale_to_length(vel,vel,g_endako_boss_move_speed_b*0.020000001f);
            value=state[0x36];PlayMobySound(4,0,entity);
            object_spawn_and_init_pal(entity,pos,vel,vel,30,(float)value,(float)value,80,1,1.0f);
        }
        if((entity[0x60]&2) && math_fast_float_d(state+0x33C)) moby_set_state(entity,6,2);
        break;
    }
    case 12: {
        int value;
        if(math_fast_float_d(state+0x2E4)) {moby_set_state(entity,6,2);break;}
        if(H(entity,0x96) && H(entity,0x96)%(((int)(g_endako_boss_attack_interval) * 5 + 2) / 6)==0) {
            moby_transform_joint_to_world(entity,I(state,0x330)>0?6:5,pos);
            {float limit=g_endako_boss_height_limit, height, side, lateral;
            value=(((int)(g_endako_boss_turn_count) * 5 + 2) / 6); I(state,0x330)=-I(state,0x330);
            height=limit-pos[2];
            Q(work,0)=0; work[0]=0.020000001f;
            side=(float)I(state,0x330)*0.020000001f;
            lateral=g_endako_boss_lateral_offsets[S(state,0x3C2)-1]*side;
            work[2]=2*height/(float)value; work[1]=lateral;}
            Q(vel,0)=Q(work,0);matrix_mul_vec3(vel,vel,entity+0xC0);
            FastVecScale(work,vel,(float)(value>>1));FastVecAdd(work,work,pos);FastVecSub(work,state+0x50,work);work[2]=0;
            vec_scale_to_length(work,work,g_endako_boss_lateral_offsets[S(state,0x3C2)-1]*0.020000001f);
            part_create_interpolated_emitter(entity,0,pos,vel,work,value,250,state[0x35]);
        }
        break;
    }
    case 13:
        if(flag_set_first_pending(entity) && entity[0x43]!=8) anim_start_blended_pal(entity,8,0,4);
        if(entity[0x60]&2) {moby_set_state(entity,10,4);endako_boss_pick_pose(entity,1);I(state,0x2D0)=0;}
        break;
    case 14:
        if(flag_set_first_pending(entity)) {if(entity[0x43]!=8)anim_start_blended_pal(entity,8,0,5);}
        else if(entity[0x43]!=0)anim_start_blended_pal(entity,0,0,5);
        if(H(entity,0x96)%37==0) {
            Q(vel,0)=0;vel[0]=math_random_float_range(-2,2);vel[1]=math_random_float_range(-4,4);vel[2]=math_random_float_range(-1,3);
            Q(pos,0)=Q(vel,0);matrix_mul_vec3(pos,pos,entity+0xC0);FastVecAdd(pos,pos,entity+0x10);PlayMobySound(2,0,entity);
            SpawnExplosion_pal(pos,0,25,20,20,20,45,1,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(state+0x2A0,0,0.26179942f,0.0017453296f);
        ((AttackState *)state)->angles[1]=((AttackState *)state)->angles[0];I(state,0x2DC)=I(state,0x2D8);
        if(H(entity,0x96)>=150) {
            FastVecSub(pos,g_camera_pose_buffer,entity+0x10);vec_scale_to_length(pos,pos,1);part_spawn_blast_effect_moby_pal(entity,entity+0x10,pos,0);
            moby_set_state(entity,15,-1);I(state,0x2CC)=0;F(state,0x2D0)=-0.10000001f;
        } else F(state,0x2C0)=FastAddRotations(F(state,0x2C0),(float)H(entity,0x96)*0.0034906592f);
        break;
    case 15: {
        int value;
        float fall_time;
        if(H(entity,0x96)%12==0) {
            Q(vel,0)=0;vel[0]=math_random_float_range(-2,2);vel[1]=math_random_float_range(-2,2);vel[2]=math_random_float_range(0,3);
            Q(pos,0)=Q(vel,0);matrix_mul_vec3(pos,pos,entity+0xC0);FastVecAdd(pos,pos,entity+0x10);PlayMobySound(2,0,entity);
            SpawnExplosion_pal(pos,0,25,20,20,20,45,0,0,0,0,0,1,20);
        }
        StepAngleTowardTarget(state+0x2A0,0,0.78539824f,0.031415932f);StepAngleTowardTarget(state+0x2A4,0,1.5707965f,0.031415932f);
        fall_time=IntToFloat(H(entity,0x96));F(state,0x2D0)-=fall_time*0.00016000001f;F(state,0x298)+=F(state,0x2D0);
        if(!S(state,0x3C0) && F(state,0x298)<F(state,0x2B8)-1) {S(state,0x3C0)=1;SetDeathBits_pal(entity,0,3);}
        if(F(state,0x298)<F(state,0x2B8)-12) {
            cam_end_override(I(state,0x2C8));moby_set_flag_bit(g_moby_record_base+(I(state,0xA4)<<8),0);script_queue_keyed_request(I(state,0xB4),I(state,0xB8));
            if(I(state,0x2C4))moby_mark_spawned(*(void **)(state+0x2C4));
            g_endako_boss_flags[1]=1;moby_mark_table_entry_flagged(entity[0xB0]);value=I(state,0x3CC);
            if(value!=-1) {u8 *sound=g_sound_l03_slot_table+value*0x70;if(*(u8 **)(sound+0x88)==entity && sound[0x74])snd_stop_voice(value);}
            I(state,0x3CC)=-1;moby_mark_spawned(entity);return;
        }
        break;
    }
    }
    endako_boss_update_helpers_pal(entity);
}
