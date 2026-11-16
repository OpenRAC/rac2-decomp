#include "common.h"

extern int g_museum_dust_big_param_a __attribute__((sda));
extern int g_museum_dust_param_a __attribute__((sda));
extern int g_vehicle_jump_boost_window __attribute__((sda));
extern int g_vehicle_jump_timer_max __attribute__((sda));
extern float g_museum_dust_big_param_f __attribute__((sda));
extern float g_museum_dust_big_param_e __attribute__((sda));
extern float g_museum_dust_big_param_c __attribute__((sda));
extern float g_museum_dust_big_param_b __attribute__((sda));
extern float g_museum_dust_big_param_d __attribute__((sda));
extern float g_museum_dust_param_f __attribute__((sda));
extern float g_museum_dust_param_e __attribute__((sda));
extern float g_museum_dust_param_c __attribute__((sda));
extern float g_museum_dust_param_b __attribute__((sda));
extern float g_museum_dust_param_d __attribute__((sda));
extern float g_vehicle_strafe_scale __attribute__((sda));
extern float g_vehicle_yaw_target_scale __attribute__((sda));
extern float g_vehicle_steer_uncontrolled_bonus __attribute__((sda));
extern float g_vehicle_lift_uncontrolled __attribute__((sda));
extern float g_vehicle_throttle_speed_scale __attribute__((sda));
extern float g_vehicle_l30_min_speed_2 __attribute__((sda));
extern float g_vehicle_l30_ground_offset_2 __attribute__((sda));
extern float g_vehicle_hit_param_c __attribute__((sda));
extern float g_vehicle_hit_param_b __attribute__((sda));
extern float g_vehicle_hit_param_a __attribute__((sda));
extern float g_vehicle_brake_strength __attribute__((sda));
extern float g_vehicle_l30_speed_limit_2 __attribute__((sda));
extern float g_vehicle_steer_speed_blend __attribute__((sda));
extern float g_vehicle_input_yaw_scale __attribute__((sda));
extern float g_vehicle_pitch_follow_b __attribute__((sda));
extern float g_vehicle_pitch_follow_a __attribute__((sda));
extern float g_vehicle_roll_throttle_blend __attribute__((sda));
extern float g_vehicle_steer_boost_scale __attribute__((sda));
extern float g_vehicle_reverse_throttle_scale __attribute__((sda));
extern float g_vehicle_roll_speed_scale __attribute__((sda));
extern float g_vehicle_roll_follow __attribute__((sda));
extern float g_vehicle_drag_scale_b __attribute__((sda));
extern float g_vehicle_drag_scale_a __attribute__((sda));
extern float g_vehicle_l30_gravity_2 __attribute__((sda));
extern float g_vehicle_ground_probe_radius __attribute__((sda));
extern float g_vehicle_l30_hover_spring_2 __attribute__((sda));
extern float g_vehicle_lift_controlled __attribute__((sda));
extern float g_vehicle_turn_speed __attribute__((sda));
extern float g_vehicle_drive_scale __attribute__((sda));
extern float g_vehicle_l30_vertical_damping_2 __attribute__((sda));
extern float g_vehicle_drag_scale __attribute__((sda));
extern float g_vehicle_steer_yaw_scale __attribute__((sda));
extern float g_vehicle_jump_boost __attribute__((sda));
typedef struct { float x,y,z,w; } MoveVec __attribute__((aligned(16)));
extern int g_current_map_index;
extern unsigned int g_pad_pressed_flags NOT_SDA;
extern void *g_hero_moby NOT_SDA;
typedef struct {
    MoveVec velocity;
    char gap10[0x10];
    float roll, pitch, yaw;
    char gap2c[0x30];
    float throttle;
    char gap60[8];
    float control;
    char gap6c[0x30];
    int jumpTimer;
} Motion;
typedef struct {
    char header[0x10];
    MoveVec position;
    unsigned char state;
    char gap21[0x27];
    float speed;
    char gap4c[0x1c];
    Motion *motion;
    char gap6c[0x54];
    MoveVec basis[4];
} MoveObject;
typedef struct {
    char header[0x18];
    void *object;
    int count;
    MoveVec point, normal, surface;
} MoveCollision;
extern MoveCollision g_collision_l30_result;
extern void hover_read_inputs_full(float *,float *,float *,float *,float *,float *);
extern void part_spawn_museum_dust_burst(void *,void *,int,float,float,float,float,float,float);
extern float FastVecLength(void *);
extern float FastVecDot(void *,void *);
extern float math_fabs(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float FastAddRotations(float,float);
extern float fast_subtract_rotations(float,float);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecCross(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void matrix_mul_vec3(void *,void *,void *);
extern void transform_vector(void *,void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void moby_transform_joint_to_world(void *,int,void *);
extern float IntegerPower(int,float);
extern float coll_probe_ground_height_below(void *,int,float);
extern void make_hit_descriptor(void *,void *,int,void *,float);
extern void mat_get_euler_angles(void *,void *);
extern int GetCollHitMaterial(void);
extern int coll_process_triangles(void *,float);
extern int coll_test_point(void *,int,void *,float);
extern int coll_process_hit(void *,int,void *,void *,float);
/* Moves the hover vehicle for one frame from the player's steering, speed, height and what it bumps into. */
void UpdateHoverVehicleMotion(MoveObject *object,int input)
{
    struct {
        MoveVec dir, accel, old;
        MoveVec matrix[4];
        MoveVec pos;
        union { MoveVec inverse[4]; struct { MoveVec delta, normal; } contact; } scratch;
    } frame;
    Motion *motion=object->motion;
    struct { float steer, throttle, yaw, brake, strafe, jump; } in;
    float control, height, speed, turnSpeed, lift, sign, amplitude, desiredHeight, acceleration, brakeScale;
    float speedLimit, steeringDelta, driveRatio, drive, angleDelta, targetAngle, projection, steerRadians, rollSpeed, targetRoll, steeringBoost, strafeDelta, strafeScale, yawHalf;
    int special, apply;
    in.jump=in.strafe=in.brake=in.yaw=in.throttle=in.steer=0.0f;
    if(input) hover_read_inputs_full(&in.steer,&in.throttle,&in.yaw,&in.brake,&in.strafe,&in.jump);
    control=motion->control;
    in.throttle*=control;
    in.brake+=1.0f-motion->control;
    in.strafe*=motion->control;
    in.jump*=motion->control;
    motion->throttle=in.throttle;
    lift=g_vehicle_lift_controlled*motion->control+g_vehicle_lift_uncontrolled*(1.0f-motion->control);
    in.yaw*=0.017453294f;
    in.yaw*=g_vehicle_input_yaw_scale;
    speed=FastVecLength(motion)*motion->control;
    turnSpeed=g_vehicle_turn_speed*0.016666668f;
    speedLimit=g_vehicle_l30_speed_limit_2*0.016666668f;
    steeringDelta=in.steer*((speed<speedLimit?speed:speedLimit)/speedLimit*g_vehicle_steer_speed_blend+(1.0f-g_vehicle_steer_speed_blend)+g_vehicle_steer_uncontrolled_bonus*(1.0f-motion->control));
    steeringDelta*=0.00029088825f;
    motion->yaw=FastAddRotations(motion->yaw,g_vehicle_steer_yaw_scale*steeringDelta);
    steerRadians=in.steer*0.017453294f;
    rollSpeed=g_vehicle_roll_speed_scale*steerRadians;
    rollSpeed*=motion->control;
    targetRoll=rollSpeed*(g_vehicle_roll_throttle_blend*in.throttle+(1.0f-g_vehicle_roll_throttle_blend));
    motion->roll+=(targetRoll-object->basis[3].x)*g_vehicle_roll_follow;
    frame.dir.x=math_fast_sin_or_cos_a(motion->yaw);
    frame.dir.y=math_fast_sin_or_cos_b(motion->yaw); frame.dir.z=0;
    if(in.throttle<0) in.throttle*=g_vehicle_reverse_throttle_scale;
    sign=1.0f;
    if(in.throttle<0) sign=-1.0f;
    amplitude=math_fabs(in.steer); driveRatio=IntegerPower(2,(turnSpeed-speed)/turnSpeed);
    steeringBoost=g_vehicle_steer_boost_scale*amplitude;
    steeringBoost*=sign;
    drive=in.throttle+steeringBoost;
    drive*=0.00027777778f;
    object->speed+=(in.throttle*g_vehicle_throttle_speed_scale-object->speed)*0.02f;
    drive*=g_vehicle_drive_scale;
    acceleration=drive*driveRatio;
    FastVecAdd(&frame.old,&object->position,motion);
    height=coll_probe_ground_height_below(&frame.old,0,0.5f);
    special=0;
    if(GetCollHitMaterial()==1 || GetCollHitMaterial()==11) special=1;
    if(object->position.z<height+lift+0.3f && special) object->state=5;
    desiredHeight=height+lift;
    if(g_vehicle_jump_timer_max-g_vehicle_jump_boost_window<motion->jumpTimer) motion->velocity.z+=g_vehicle_jump_boost*0.00027777778f;
    else motion->velocity.z-=g_vehicle_l30_gravity_2*0.00027777778f;
    if(height!=0) {
        apply=1;
        if(desiredHeight<frame.old.z) {
            angleDelta=fast_subtract_rotations(in.yaw,motion->pitch);
            motion->pitch=FastAddRotations(motion->pitch,angleDelta*g_vehicle_pitch_follow_b);
            if(g_current_map_index==8) apply=0;
        } else {
            if(motion->jumpTimer==0 && in.jump>0.2f) motion->jumpTimer=g_vehicle_jump_timer_max;
            if(height>frame.old.z+0.1f || special) {
                frame.old.z=height;
                FastVecScale(motion,motion,g_vehicle_drag_scale_b);
            }
            motion->velocity.z+=((desiredHeight-frame.old.z)*g_vehicle_l30_hover_spring_2-motion->velocity.z)*g_vehicle_l30_hover_spring_2;
            if(in.brake>0) {
                brakeScale=1.0f-g_vehicle_brake_strength*in.brake;
                motion->velocity.x*=brakeScale; motion->velocity.y*=brakeScale;
            }
            {
                MoveVec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                vec_scale_to_length(ahead,&g_collision_l30_result.surface,1.0f);
                up=&frame.matrix[1];
                FastVecCross(up,&object->basis[0],ahead);
                FastVecCross(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            mat_get_euler_angles(&frame.matrix[0],&frame.pos);
            yawHalf=in.yaw*0.5f;
            targetAngle=FastAddRotations(-frame.pos.y,yawHalf*(g_vehicle_yaw_target_scale*(motion->control+1.0f)));
            angleDelta=fast_subtract_rotations(targetAngle,motion->pitch);
            motion->pitch=FastAddRotations(motion->pitch,angleDelta*g_vehicle_pitch_follow_a);
            FastVecScale(motion,motion,g_vehicle_drag_scale);
            matrix_from_basis_rows(frame.scratch.inverse,&object->basis[0]);
            transform_vector(motion,motion,frame.scratch.inverse);
            motion->velocity.y*=g_vehicle_l30_vertical_damping_2;
            matrix_mul_vec3(motion,motion,&object->basis[0]);
        }
        if(apply) {
            vec_scale_to_length(&frame.accel,&object->basis[0],acceleration);
            strafeDelta=in.strafe*0.00027777778f;
            strafeScale=g_vehicle_strafe_scale*strafeDelta;
            vec_scale_to_length(&frame.matrix[0],&object->basis[1],strafeScale*motion->control);
            FastVecAdd(&frame.accel,&frame.accel,&frame.matrix[0]);
            FastVecAdd(motion,motion,&frame.accel);
        }
    }
    make_hit_descriptor(&frame.matrix[0],object,0x10000,motion,g_vehicle_hit_param_b);
    qcopy(&object->position,&frame.old);
    moby_transform_joint_to_world(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=g_vehicle_ground_probe_radius-g_vehicle_lift_uncontrolled;
    FastVecSub(&frame.pos,&object->position,&frame.matrix[3]);
    if(coll_process_triangles(&frame.matrix[3],g_vehicle_ground_probe_radius) || coll_test_point(&frame.matrix[3],2,object,g_vehicle_ground_probe_radius)) {
        if(GetCollHitMaterial()==1 || GetCollHitMaterial()==11) object->state=5;
        if(g_collision_l30_result.object!=g_hero_moby) {
            g_collision_l30_result.normal.x-=frame.matrix[3].x; g_collision_l30_result.normal.y-=frame.matrix[3].y;
            g_collision_l30_result.normal.x*=motion->control; g_collision_l30_result.normal.y*=motion->control;
            g_collision_l30_result.normal.x+=frame.matrix[3].x; g_collision_l30_result.normal.y+=frame.matrix[3].y;
            FastVecAdd(&object->position,&g_collision_l30_result.normal,&frame.pos);
            FastVecCross(&frame.scratch.contact.normal,&g_collision_l30_result.surface,motion);
            FastVecCross(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&g_collision_l30_result.surface);
            vec_scale_to_length(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            projection=FastVecDot(motion,&frame.scratch.contact.delta);
            vec_scale_to_length(motion,&frame.scratch.contact.delta,projection*motion->control);
            FastVecScale(motion,motion,g_vehicle_drag_scale_a);
        }
    }
    if(object->state==3) {
        if(motion->control<0.98f && (g_pad_pressed_flags&4))
            part_spawn_museum_dust_burst(object,&g_collision_l30_result.point,g_museum_dust_big_param_a,g_museum_dust_big_param_b,g_museum_dust_big_param_c,g_museum_dust_big_param_d,g_museum_dust_big_param_d,g_museum_dust_big_param_e,g_museum_dust_big_param_f);
        part_spawn_museum_dust_burst(object,&g_collision_l30_result.point,g_museum_dust_param_a,g_museum_dust_param_b,g_museum_dust_param_c,g_museum_dust_param_d,g_museum_dust_param_e,g_museum_dust_param_f,1.0f);
    }
    moby_transform_joint_to_world(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=g_vehicle_l30_ground_offset_2;
    coll_process_hit(&frame.matrix[3],0,object,&frame.matrix[0],g_vehicle_hit_param_a);
    if(FastVecLength(motion)>g_vehicle_l30_min_speed_2*0.016666668f) {
        moby_transform_joint_to_world(object,1,&frame.scratch.contact.delta);
        coll_process_hit(&frame.scratch.contact.delta,0,object,&frame.matrix[0],g_vehicle_hit_param_c);
    }
}
