#include "common.h"
extern int g_enemy_ai_frozen;
extern char g_hero_position[];
extern char *g_active_attacker_robot __attribute__((section(".data")));
typedef int TIAfc8 __attribute__((mode(TI)));
extern void smasher_robot_update_aim_and_init(char *);
extern void moby_set_state(char *, int, int);
extern void anim_start_blended(char *, int, int, int);
extern int math_random_int_below(int);
extern void FastVecSub(void *, void *, void *);
extern float vec_get_heading_angle(char *, void *, void *);
extern float mat_fast_helper_a(float, float);
extern float FastDiffRots(float, float);
extern float fast_vec_dist(void *, void *);
extern float vec_distance_xy(void *, void *);
extern int flag_set_second_pending(char *);
extern int flag_set_first_pending(char *);
extern void moby_set_controller_speed_limits(char *, float, float, float, float);
extern char *arena_get_center_point(int);
extern int arena_is_point_in_polygon(int, void *);
extern void smasher_robot_pick_wander_point(char *, void *);
extern void smasher_robot_start_turn_around(char *);
extern int moby_l01_turn_toward_target(char *, void *);
extern int moby_aim_at_target_offset(char *, void *);
extern int moby_step_at_own_position_factor(char *, float);
extern int moby_step_controller(char *, void *, float);
extern int enemy_aim_at_group_entity_in_cone_b(char *);
extern int moby_turn_toward_target_and_step(char *, void *, float);
extern int coll_update_controller(char *, void *, void *);
extern float moby_get_anim_value(char *);
extern int coll_test_hit_at_bone(char *, int, float, float, int, float, int, int, int);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);
extern void joba_submit_scene_effect_params(char *);
extern void smasher_robot_advance_arm_history(char *);
extern int coll_check_move_to_point(char *, void *);
extern int moby_dispatch_action_by_kind(char *, void *);
extern void moby_set_anim_type_three(char *, int, int);
extern void smasher_robot_deactivate(char *);
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_get_euler_angles(void *, void *);
extern int hero_set_control_motion_and_step(char *, void *);
extern void FastVecScale(void *, void *, float);
extern void get_moby_joint_matrices(char *, int, void *, void *);
extern void moby_rotate_about_point(char *, void *, float, float, float);
extern void euler_rotation_basis(void *, void *);
extern void smasher_robot_finish_frame(char *);

/* Per-frame update of the Joba smasher robot (moby class 3535): it patrols, chases the hero, smashes with its arms and flies off when destroyed. */
void smasher_robot_update(char *object)
{
    float target[4], direction[4], matrix[16];
    int collision_flags;
    char *state = *(char **)(object + 0x68);
    char *position, *waypoint;
    float angle, difference, distance, frame, scale;
    int result, i;
    float *rotation;
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !g_enemy_ai_frozen &&
        *(u8 *)(object + 0x20) != 11 && *(u8 *)(object + 0x20) != 10) return;
    smasher_robot_update_aim_and_init(object);
    if (*(u8 *)(object + 0x20) == 1) return;
    if (*(short *)(state + 0x4D2) && !g_enemy_ai_frozen) return;
    if (*(short *)(state + 0x4CA) == 0) {
        *(int *)(state + 0x490) = 0;
        if (*(u8 *)(object + 0x95) == 4) {
            moby_set_state(object, 4, 2);
            if (math_random_int_below(2)) {
                if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object, 2, 0, 10);
            } else if (*(u8 *)(object + 0x43) != 3) anim_start_blended(object, 3, 0, 10);
        }
    }
    if (*(char **)(state + 0x490)) *(TIAfc8 *)target = *(TIAfc8 *)(*(char **)(state + 0x490) + 0x10);
    else *(TIAfc8 *)target = *(TIAfc8 *)g_hero_position;
    if (*(short *)(state + 0x4D2)) {
        FastVecSub(direction, target, object + 0x10);
        position = object + 0x10;
        difference = vec_get_heading_angle(object, direction, state + 0x230);
        angle = 0.0f;
    } else {
        position = object + 0x10;
        angle = mat_fast_helper_a(target[0] - *(float *)(object + 0x10), target[1] - *(float *)(object + 0x14));
        difference = FastDiffRots(angle, *(float *)(object + 0xF8));
    }
    distance = fast_vec_dist(position, target);
    if (*(u8 *)(object + 0x95) == 2) {
        if (flag_set_second_pending(object)) {
            if (*(u8 *)(object + 0x43) != 10) anim_start_blended(object, 10, 0, 10);
            *(u8 *)(object + 0xBC) = 0;
            moby_set_controller_speed_limits(object, 0.002222222276031971f, 0.06666667014360428f, 0.0011635529808700085f, 0.10471977293491364f);
            smasher_robot_pick_wander_point(object, arena_get_center_point(*(int *)(object + 0xB8)));
            *(u16 *)(object + 0x96) = 10000;
        }
        if (*(u8 *)(object + 0xBC) == 1 && *(u16 *)(object + 0x96) > 300) {
            switch (math_random_int_below(5)) {
            case 0: if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object,2,0,10); break;
            case 1: if (*(u8 *)(object + 0x43) != 3) anim_start_blended(object,3,0,10); break;
            case 2: if (*(u8 *)(object + 0x43) != 4) anim_start_blended(object,4,0,10); break;
            case 3: if (*(u8 *)(object + 0x43) != 6) anim_start_blended(object,6,0,10); break;
            case 4: if (*(u8 *)(object + 0x43) != 7) anim_start_blended(object,7,0,10); break;
            }
            *(u16 *)(object + 0x96) = math_random_int_below(100);
        }
        if (*(short *)(state + 0x4CA)) {
            moby_set_state(object,5,4);
            if (math_random_int_below(2)) {
                if (*(u8 *)(object + 0x43) != 1) anim_start_blended(object,1,0,10);
            } else if (*(u8 *)(object + 0x43) != 5) anim_start_blended(object,5,0,10);
        }
        if (difference > 2.792527198791504f) smasher_robot_start_turn_around(object);
        waypoint = state + 0x470;
        if (*(u8 *)(object + 0xBC) == 0 && vec_distance_xy(position, waypoint) < 0.5f) *(u8 *)(object + 0xBC) = 1;
        else if (*(short *)(state + 0x4D2)) moby_aim_at_target_offset(object,waypoint);
        else moby_l01_turn_toward_target(object,waypoint);
    }
    switch (*(u8 *)(object + 0x20)) {
    case 3:
        if (flag_set_first_pending(object)) {
            *(u8 *)(object + 0xBC) = 0;
            if (*(u8 *)(object + 0x43) != 2) anim_start_blended(object,2,0,0);
            *(u16 *)(object + 0x96) = 0;
        }
        if (*(u8 *)(object + 0xBC) == 0 && *(short *)(state + 0x4D0) < *(u16 *)(object + 0x96)) {
            if (*(u8 *)(object + 0x43) != 10) anim_start_blended(object,10,0,10);
            *(u8 *)(object + 0xBC) = 1;
        } else if (*(u8 *)(object + 0xBC) == 1) {
            if (arena_is_point_in_polygon(*(int *)(object+0xB8),position)) moby_set_state(object,4,2);
            moby_l01_turn_toward_target(object,arena_get_center_point(*(int *)(object+0xB8)));
        }
        break;
    case 5:
        if (*(u8 *)(object + 0x60) & 2) moby_set_state(object,7,-1);
        break;
    case 6:
        if (flag_set_first_pending(object)) {
            if (*(u8 *)(object + 0x43) != 9) anim_start_blended(object,9,0,10);
            moby_set_controller_speed_limits(object,0.004444444552063942f,0.13333334028720856f,0.006981317885220051f,0.8377581834793091f);
        }
        moby_step_at_own_position_factor(object,angle);
        if (*(u8 *)(object+0x60)&2) moby_set_state(object,*(short *)(state+0x4CC),*(short *)(state+0x4CE));
        break;
    case 7:
        if (flag_set_first_pending(object)) {
            if (*(u8 *)(object+0x43)!=10) anim_start_blended(object,10,0,15);
        }
        if (*(u8 *)(object+0x42)==8 && distance>15.0f) {
            if (*(u8 *)(object+0x43)!=10) anim_start_blended(object,10,0,4);
            moby_set_controller_speed_limits(object,0.004444444552063942f,0.13333334028720856f,0.0011635529808700085f,0.10471977293491364f);
        } else if (*(u8 *)(object+0x42)==10 && distance<7.0f) {
            if (*(u8 *)(object+0x43)!=8) anim_start_blended(object,8,0,4);
            moby_set_controller_speed_limits(object,0.004444444552063942f,0.03333333507180214f,0.0011635529808700085f,0.10471977293491364f);
        }
        if (distance<2.8f && difference<0.3839724659919739f) {
            moby_set_state(object,8,-1);
            if (*(u8 *)(object+0x43)!=11) anim_start_blended(object,11,4,3);
            *(int *)(state+0x4B0)=0;
        } else if (distance>2.8f) {
            if (*(short *)(state+0x4D2)) moby_aim_at_target_offset(object,target);
            else if (!enemy_aim_at_group_entity_in_cone_b(object)) moby_turn_toward_target_and_step(object,target,*(float *)(state+0x494));
        } else {
            if (*(short *)(state+0x4D2)) {
                FastVecSub(direction,target,position);
                coll_update_controller(object,position,direction);
            } else moby_step_controller(object,position,angle);
        }
        if (difference>2.792527198791504f) smasher_robot_start_turn_around(object);
        break;
    case 8:
        if (*(u8 *)(object+0x60)&2) {
            *(float *)(state+0x4AC)=8.0f;
            if (g_active_attacker_robot==object) {
                moby_set_state(object,9,-1);
                if (*(u8 *)(object+0x43)!=12) anim_start_blended(object,12,0,7);
            } else moby_set_state(object,7,-1);
        }
        frame=moby_get_anim_value(object);
        if (*(u8 *)(object+0x42)==11) {
            if (19.0f<=frame && frame<=25.0f) {
                coll_test_hit_at_bone(object,0,0.35f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                coll_test_hit_at_bone(object,1,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
                coll_test_hit_at_bone(object,2,0.15f,(float)*(u8 *)(state+0x34),0x10001,1.0f,0,1,0);
            }
        }
        if (*(u8 *)(object+0x42)==11 && 17.0f<=frame && frame<=25.0f) {
            gfx_add_draw_callback_first(joba_submit_scene_effect_params,object);
            smasher_robot_advance_arm_history(object);
            *(float *)(state+0x4AC)=25.0f;
        }
        if (*(short *)(state+0x4D2)) coll_check_move_to_point(object,target);
        else moby_step_controller(object,position,angle);
        break;
    case 9:
        if (*(u8 *)(object+0x60)&2) moby_set_state(object,7,-1);
        break;
    case 10:
        result=moby_dispatch_action_by_kind(object,state+0x50);
        if (*(u8 *)(object+0x42)==15) {
            if (!math_random_int_below(30) || (result&1)) {
                if (moby_get_anim_value(object)<15.0f && *(short *)(state+0x4D2) && !math_random_int_below(2)) moby_set_state(object,11,-1);
                else {moby_set_anim_type_three(object,0,-1); smasher_robot_deactivate(object);}
            }
        } else if (result&2) moby_set_state(object,7,4);
        break;
    case 11:
        if (flag_set_first_pending(object)) {
            FastVecSub(state+0x1A0,arena_get_center_point(*(int *)(object+0xB8)),position);
            *(int *)(state+0x1A8)=0;
            scale=math_random_float_range(3.0f,5.0f);
            vec_scale_to_length(state+0x1A0,state+0x1A0,scale*0.01666666753590107f);
            if (*(u8 *)(object+0x43)!=17) anim_start_blended(object,17,0,30);
            *(short *)(state+0x4D2)=0;
            rotation = (float *)(state + 0x480);
            for (i = 0; i < 3; i++) {
                rotation[i] = math_random_float_range(240.0f,720.0f)*0.0002908882452175021f;
                qcopy((char *)matrix + i * 16, object + 0xC0 + i * 16);
            }
            mat_get_euler_angles(matrix,object+0xF0);
            *(u16 *)(object+0x34)&=0xEFFF;
        }
        *(float *)(state+0x1A8)-=*(float *)(state+0x12C);
        hero_set_control_motion_and_step(object,state+0x1A0);
        FastVecScale(state+0x480,state+0x480,0.98f);
        scale=*(float *)(object+0x2C)*0.0009765625f;
        collision_flags=6;
        get_moby_joint_matrices(object,1,&collision_flags,matrix);
        FastVecScale(direction,matrix+12,scale);
        moby_rotate_about_point(object,direction,*(float *)(state+0x480),*(float *)(state+0x484),*(float *)(state+0x488));
        euler_rotation_basis(object+0xC0,object+0xF0);
        if (*(float *)(object+0x18)<*(float *)(arena_get_center_point(*(int *)(object+0xB8))+8)+5.0f ||
            !math_random_int_below(450) || *(u16 *)(object+0x96)>300) {
            moby_set_anim_type_three(object,0,-1); smasher_robot_deactivate(object);
        }
        break;
    }
    smasher_robot_finish_frame(object);
}
