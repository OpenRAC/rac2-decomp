#include "common.h"
#include "include_asm.h"
typedef int Quad004475A0 __attribute__((mode(TI)));
extern void security_robot_deactivate(char *);
extern int g_hero_l11_input_blocked;
extern char g_hero_position[];
extern char *g_active_attacker_robot NOT_SDA;
extern void turret_enemy_update(char *);
extern void security_robot_play_idle(char *);
extern void security_robot_finish_frame(char *);
extern void security_robot_damage_along_arm_swing(char *);
extern void moby_start_anim_fast(char *);
extern void moby_start_anim_slow(char *);
extern int security_robot_try_start_attack(char *);
extern int AimAtGroupEntityInCone(char *);
extern void security_robot_pick_wander_point(char *,char *);
extern void security_robot_destroy_held_item(char *,void *);
extern float vec_normalized_direction_dot(char *,void *);
extern char *arena_get_center_point(int);
extern int arena_is_point_in_polygon(int,void *);
extern void moby_set_anim_type_three(char *,int,int);
extern void part_queue_moby_for_glow(char *,int,void *);
extern void FastVecSub(void *,void *,void *);
extern float vec_get_heading_angle(char *,void *,void *);
extern float mat_fast_helper_a(float,float);
extern float FastDiffRots(float,float);
extern float fast_vec_dist(void *,void *);
extern float vec_distance_squared_xy(void *,void *);
extern int flag_set_second_pending(char *);
extern int flag_set_first_pending(char *);
extern void anim_start_blended(char *,int,int,int);
extern void moby_set_state(char *,int,int);
extern int math_random_int_below(int);
extern int moby_aim_at_target_offset(char *,void *);
extern int moby_l01_turn_toward_target(char *,void *);
extern int moby_turn_toward_target_and_step(char *,void *,float);
extern int coll_check_move_to_point(char *,void *);
extern int moby_step_at_own_position_factor(char *,float);
extern int moby_dispatch_action_by_kind(char *,void *);
extern void mem_clear(void *,int,int);
extern void AttachManipulator(char *,int,void *);
extern void vec_random_direction(void *,float,float);
extern void part_spawn_masked_debris(char *,int,void *,float,float,float,float,int);
extern void moby_set_controller_speed_limits(char *,float,float,float,float);
extern float moby_get_anim_value(char *);
extern int moby_call_helper_with_blocks(char *);
extern int moby_step_at_own_position(char *);
extern float math_random_float_range(float,float);
extern void vec_scale_to_length(void *,void *,float);
extern void mat_get_euler_angles(void *,void *);
extern int hero_set_control_motion_and_step(char *,void *);
extern void FastVecScale(void *,void *,float);
extern void moby_rotate_about_point(char *,void *,float,float,float);
extern void euler_rotation_basis(void *,void *);

/* Per-frame update of the Joba security robot (moby class 3480): it patrols, walks to the hero, attacks, gets knocked out and gets thrown away when destroyed. */
void security_robot_update(char *self)
{
    float target[4], temp[4], matrix[16];
    char *state;
    char *point, *p;
    float angle, difference, distance, time, old, turn;
    int flags = 0, i;
    state=*(char **)(self+0x68);
    if (*(u8 *)(self+0x20)==1) return;
    if (*(short *)(state+0x36E) && !g_hero_l11_input_blocked &&
        *(u8 *)(self+0x20)!=18 && *(u8 *)(self+0x20)!=17) return;
    turret_enemy_update(self);
    if (*(u8 *)(self+0x20)==1) return;
    if (*(short *)(state+0x366)==0) {
        unsigned char phase;
        *(int *)(state+0x350)=0;
        phase=*(u8 *)(self+0x95);
        if (phase!=0 && phase!=2 && phase!=1 && phase!=7 && phase!=8) security_robot_play_idle(self);
    }
    if (*(char **)(state+0x350)) *(Quad004475A0 *)target=*(Quad004475A0 *)(*(char **)(state+0x350)+0x10);
    else *(Quad004475A0 *)target=*(Quad004475A0 *)g_hero_position;
    if (*(short *)(state+0x36E)) {
        FastVecSub(temp,target,self+0x10);
        point=self+0x10;
        angle=0.0f;
        difference=vec_get_heading_angle(self,temp,state+0x2F0);
    } else {
        float x=target[0], y=target[1];
        point=self+0x10;
        x-=*(float *)(self+0x10);
        y-=*(float *)(self+0x14);
        angle=mat_fast_helper_a(x,y);
        difference=FastDiffRots(angle,*(float *)(self+0xF8));
    }
    distance=fast_vec_dist(point,target);
    switch (*(u8 *)(self+0x95)) {
    case 2:
        if (flag_set_second_pending(self)) {
            p=arena_get_center_point(*(int *)(self+0xB8));
            if (*(u8 *)(self+0x43)!=3) anim_start_blended(self,3,0,10);
            *(u8 *)(self+0xBC)=0;
            security_robot_pick_wander_point(self,p);
            *(u16 *)(self+0x96)=10000;
        }
        if (*(u8 *)(self+0xBC)==1 && *(u16 *)(self+0x96)>300) {
            int choice=math_random_int_below(2);
            switch(choice) {
            case 0: if (*(u8 *)(self+0x43)!=1) anim_start_blended(self,1,0,10); break;
            case 1: if (*(u8 *)(self+0x43)!=0) anim_start_blended(self,0,0,10); break;
            }
            *(u16 *)(self+0x96)=math_random_int_below(100);
        }
        if (*(short *)(state+0x366)) moby_start_anim_fast(self);
        if (*(u8 *)(self+0xBC)==0) {
            p=state+0x330;
            if (vec_distance_squared_xy(point,p)<4.0f) *(u8 *)(self+0xBC)=1;
            if (*(short *)(state+0x36E)) moby_aim_at_target_offset(self,p);
            else moby_l01_turn_toward_target(self,p);
        } else {
            if (*(short *)(state+0x36E)) moby_aim_at_target_offset(self,point);
            else moby_l01_turn_toward_target(self,point);
        }
        break;
    case 5:
        if (*(u8 *)(self+0x60)&2) moby_start_anim_slow(self);
        break;
    case 3:
        if (*(short *)(state+0x36E)) moby_aim_at_target_offset(self,target);
        else if (!AimAtGroupEntityInCone(self)) {
            switch(*(u8 *)(self+0x42)) {
            case 2: moby_l01_turn_toward_target(self,target); break;
            case 3: moby_turn_toward_target_and_step(self,target,*(float *)(state+0x358)); break;
            }
        }
        break;
    case 4:
        if (distance>14.0f) moby_start_anim_fast(self);
        else if (!security_robot_try_start_attack(self)) {
            if (distance<4.0f && difference<0.2617994248867035f) moby_set_state(self,11,-1);
            else if (*(u8 *)(self+0x20)==11 && distance>5.0f) moby_set_state(self,10,-1);
        }
        break;
    case 6:
        if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);
        else moby_step_at_own_position_factor(self,angle);
        break;
    case 7:
        flags=moby_dispatch_action_by_kind(self,state+0x50);
        if (*(float *)(state+0x20)<=1.0f && *(char **)(state+0x354)) {
            *(Quad004475A0 *)temp=*(Quad004475A0 *)(*(char **)(state+0x354)+0x10);
            security_robot_destroy_held_item(self,temp);
        }
        if (*(float *)(state+0x20)<=0.0f && !*(u8 *)(state+0x2B1)) {
            mem_clear(state+0x2B0,0,0x40);
            AttachManipulator(self,3,state+0x2B0);
            *(u8 *)(state+0x2B2)=1;
            *(float *)(state+0x2D8)=0.0001f;
            *(float *)(state+0x2D4)=0.0001f;
            *(float *)(state+0x2D0)=0.0001f;
            vec_random_direction(temp,0.01666666753590107f,0.05000000447034836f);
            part_spawn_masked_debris(self,0x20,temp,3.0f,6.0f,3.0f,6.0f,255);
            if (*(short *)(state+0x36E) && !math_random_int_below(2)) {
                moby_set_state(self,18,8);
                return;
            }
        }

        if ((flags&1) || (*(float *)(state+0x20)<=0.0f && *(u16 *)(self+0x96)>60)) {
            *(int *)(self+0x98)=0;
            moby_set_anim_type_three(self,0,-1);
            part_queue_moby_for_glow(self,0,security_robot_deactivate);
        }
        break;
    }
    switch (*(u8 *)(self+0x20)) {
    case 3:
        if (flag_set_first_pending(self)) {
            *(u8 *)(self+0xBC)=0;
            if (*(u8 *)(self+0x43)!=0) anim_start_blended(self,0,0,0);
            *(u16 *)(self+0x96)=0;
        }
        if (*(u8 *)(self+0xBC)==0) {
            if (*(short *)(state+0x36C)<*(u16 *)(self+0x96)) {
                if (*(u8 *)(self+0x43)!=3) anim_start_blended(self,3,0,10);
                *(u8 *)(self+0xBC)=1;
                break;
            }
        }
        if (*(u8 *)(self+0xBC)==1) {
            if (arena_is_point_in_polygon(*(int *)(self+0xB8),point)) moby_set_state(self,4,2);
            moby_l01_turn_toward_target(self,arena_get_center_point(*(int *)(self+0xB8)));
        }
        break;
    case 7:
        if (flag_set_first_pending(self)) *(u16 *)(self+0x96)=0;
        if (distance<4.0f || *(u16 *)(self+0x96)>450 || *(int *)(state+0x180)>=31) moby_start_anim_fast(self);
        break;
    case 6:
        if (distance>14.0f) {
            moby_set_controller_speed_limits(self,0.0055555556900799274f,0.10333333909511566f,0.0034906589426100254f,0.41887909173965454f);
            moby_set_state(self,7,3);
            if (*(u8 *)(self+0x43)!=3) anim_start_blended(self,3,0,10);
        } else if (distance<4.0f || *(int *)(state+0x180)>=31) moby_start_anim_slow(self);
        break;
    case 10:
        time=moby_get_anim_value(self);
        turn=vec_normalized_direction_dot(self,target);
        if (turn>0.01f) {
            moby_set_state(self,9,-1);
            if (*(u8 *)(self+0x43)!=5) anim_start_blended(self,5,0,10);
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);
            else moby_step_at_own_position_factor(self,angle);
        } else if (turn< -0.01f) {
            moby_set_state(self,8,-1);
            if (*(u8 *)(self+0x43)!=4) anim_start_blended(self,4,0,10);
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);
            else moby_step_at_own_position_factor(self,angle);
        } else if (distance<4.0f) {moby_set_state(self,11,-1);}
        else if (time<2.0f) {
            moby_set_controller_speed_limits(self,0.0055555556900799274f,0.03333333507180214f,0.0034906589426100254f,0.41887909173965454f);
            if (*(short *)(state+0x36E)) moby_aim_at_target_offset(self,target);
            else moby_l01_turn_toward_target(self,target);
        } else if (time>10.0f && moby_get_anim_value(self)<17.0f) {
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);
            else moby_step_at_own_position_factor(self,angle);
        } else if (time<20.0f) {
            if (*(short *)(state+0x36E)) moby_aim_at_target_offset(self,target);
            else moby_l01_turn_toward_target(self,target);
        } else {
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);
            else moby_step_at_own_position_factor(self,angle);
        }
        break;
    case 8:
        if (vec_normalized_direction_dot(self,target)> -0.01f) {
            moby_set_state(self,10,-1);
            if (*(u8 *)(self+0x43)!=6) anim_start_blended(self,6,0,10);
            if (*(short *)(state+0x36E)) moby_call_helper_with_blocks(self);else moby_step_at_own_position(self);
        } else if (moby_get_anim_value(self)>5.0f) {
            old=*(float *)(state+0x130);*(float *)(state+0x130)=0.01745329424738884f;
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);else moby_step_at_own_position_factor(self,angle);
            *(float *)(state+0x130)=old;
        }
        break;
    case 9:
        if (vec_normalized_direction_dot(self,target)<0.01f) {
            moby_set_state(self,10,-1);
            if (*(u8 *)(self+0x43)!=6) anim_start_blended(self,6,0,10);
            if (*(short *)(state+0x36E)) moby_call_helper_with_blocks(self);else moby_step_at_own_position(self);
        } else if (moby_get_anim_value(self)>5.0f) {
            old=*(float *)(state+0x130);*(float *)(state+0x130)=0.01745329424738884f;
            if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);else moby_step_at_own_position_factor(self,angle);
            *(float *)(state+0x130)=old;
        }
        break;
    case 11:
        if (flag_set_first_pending(self) && *(u8 *)(self+0x43)!=1) anim_start_blended(self,1,0,10);
        if (*(short *)(state+0x36E)) coll_check_move_to_point(self,target);else moby_step_at_own_position_factor(self,angle);
    case 15: case 16:
        if (flags&2) security_robot_play_idle(self);
        break;
    case 13: case 14:
        if (*(u8 *)(self+0x60)&2) {
            *(short *)(state+0x368)=0;
            if (g_active_attacker_robot==self) {
                moby_set_state(self,12,5);
                if (*(u8 *)(self+0x43)!=7) anim_start_blended(self,7,0,10);
            } else security_robot_play_idle(self);
        }
        security_robot_damage_along_arm_swing(self);
        break;
    case 18:
        if (flag_set_first_pending(self)) {
            FastVecSub(state+0x1A0,arena_get_center_point(*(int *)(self+0xB8)),point);
            *(float *)(state+0x1A8)=0;
            vec_scale_to_length(state+0x1A0,state+0x1A0,math_random_float_range(3.0f,5.0f)*0.01666666753590107f);
            *(short *)(state+0x36E)=0;
            for(i=0;i<3;i++) {
                float *spin=(float *)(state+0x340);
                spin[i]=math_random_float_range(240.0f,720.0f)*0.0002908882452175021f;
                qcopy_nc((char *)matrix+i*16,self+0xC0+i*16);
            }
            mat_get_euler_angles(matrix,self+0xF0);
            if (*(u8 *)(self+0x43)!=13) anim_start_blended(self,13,0,30);
            *(u16 *)(self+0x34)&=0xEFFF;
        }
        { float gravity=*(float *)(state+0x12C);
          *(float *)(state+0x1A8)=*(float *)(state+0x1A8)-gravity; }
        hero_set_control_motion_and_step(self,state+0x1A0);
        FastVecScale(state+0x340,state+0x340,0.98f);
        *(Quad004475A0 *)matrix=0;
        matrix[2]=*(float *)(state+0x30);
        *(Quad004475A0 *)temp=*(Quad004475A0 *)matrix;
        moby_rotate_about_point(self,temp,*(float *)(state+0x340),*(float *)(state+0x344),*(float *)(state+0x348));
        euler_rotation_basis(self+0xC0,self+0xF0);
        p=arena_get_center_point(*(int *)(self+0xB8));
        if (*(float *)(self+0x18)<*(float *)(p+8)+5.0f || !math_random_int_below(450) || *(u16 *)(self+0x96)>300) {
            *(int *)(self+0x98)=0;
            moby_set_anim_type_three(self,0,-1);
            part_queue_moby_for_glow(self,0,security_robot_deactivate);
        }
        break;
    }
    security_robot_finish_frame(self);
}
