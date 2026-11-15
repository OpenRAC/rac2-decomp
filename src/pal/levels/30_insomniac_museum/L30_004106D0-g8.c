#include "include_asm.h"

#include "common.h"
extern int D_L30_001B189C __attribute__((sda));
extern int D_L30_001B186C __attribute__((sda));
extern int D_L30_001B16C8 __attribute__((sda));
extern int D_L30_001B16C4 __attribute__((sda));
extern float D_L30_001B18A4 __attribute__((sda));
extern float D_L30_001B18A0 __attribute__((sda));
extern float D_L30_001B1898 __attribute__((sda));
extern float D_L30_001B1894 __attribute__((sda));
extern float D_L30_001B1890 __attribute__((sda));
extern float D_L30_001B1874 __attribute__((sda));
extern float D_L30_001B1870 __attribute__((sda));
extern float D_L30_001B1868 __attribute__((sda));
extern float D_L30_001B1864 __attribute__((sda));
extern float D_L30_001B1860 __attribute__((sda));
extern float D_L30_001B1804 __attribute__((sda));
extern float D_L30_001B17F8 __attribute__((sda));
extern float D_L30_001B17F4 __attribute__((sda));
extern float D_L30_001B17F0 __attribute__((sda));
extern float D_L30_001B17E4 __attribute__((sda));
extern float D_L30_001B17AC __attribute__((sda));
extern float D_L30_001B17A8 __attribute__((sda));
extern float D_L30_001B17A4 __attribute__((sda));
extern float D_L30_001B17A0 __attribute__((sda));
extern float D_L30_001B1744 __attribute__((sda));
extern float D_L30_001B1740 __attribute__((sda));
extern float D_L30_001B173C __attribute__((sda));
extern float D_L30_001B1738 __attribute__((sda));
extern float D_L30_001B1734 __attribute__((sda));
extern float D_L30_001B1730 __attribute__((sda));
extern float D_L30_001B172C __attribute__((sda));
extern float D_L30_001B1728 __attribute__((sda));
extern float D_L30_001B1724 __attribute__((sda));
extern float D_L30_001B1720 __attribute__((sda));
extern float D_L30_001B171C __attribute__((sda));
extern float D_L30_001B1718 __attribute__((sda));
extern float D_L30_001B1714 __attribute__((sda));
extern float D_L30_001B1710 __attribute__((sda));
extern float D_L30_001B170C __attribute__((sda));
extern float D_L30_001B1700 __attribute__((sda));
extern float D_L30_001B16FC __attribute__((sda));
extern float D_L30_001B16F8 __attribute__((sda));
extern float D_L30_001B16F4 __attribute__((sda));
extern float D_L30_001B16F0 __attribute__((sda));
extern float D_L30_001B16EC __attribute__((sda));
extern float D_L30_001B16E8 __attribute__((sda));
extern float D_L30_001B16E4 __attribute__((sda));
extern float D_L30_001B16C0 __attribute__((sda));
typedef struct { float x,y,z,w; } MoveVec __attribute__((aligned(16)));
extern int g_current_map_index;
extern unsigned int D_00138320 NOT_SDA;
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
extern MoveCollision D_L30_001C0200;
extern void hover_read_inputs_full(float *,float *,float *,float *,float *,float *);
extern void func_PAL_L30_004106D0(void *,void *,int,float,float,float,float,float,float);
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
extern void coll_process_hit(void *,int,void *,void *,float);

void func_PAL_L30_00411310(MoveObject *object,int input)
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
    lift=D_L30_001B16F8*motion->control+D_L30_001B17F0*(1.0f-motion->control);
    in.yaw*=0.017453294f;
    in.yaw*=D_L30_001B1734;
    speed=FastVecLength(motion)*motion->control;
    turnSpeed=D_L30_001B16F4*0.020000001f;
    speedLimit=D_L30_001B173C*0.020000001f;
    steeringDelta=in.steer*((speed<speedLimit?speed:speedLimit)/speedLimit*D_L30_001B1738+(1.0f-D_L30_001B1738)+D_L30_001B17F4*(1.0f-motion->control));
    steeringDelta*=0.0003490659f;
    motion->yaw=FastAddRotations(motion->yaw,D_L30_001B16E4*steeringDelta);
    steerRadians=in.steer*0.017453294f;
    rollSpeed=D_L30_001B171C*steerRadians;
    rollSpeed*=motion->control;
    targetRoll=rollSpeed*(D_L30_001B1728*in.throttle+(1.0f-D_L30_001B1728));
    motion->roll+=(targetRoll-object->basis[3].x)*D_L30_001B1718;
    frame.dir.x=math_fast_sin_or_cos_a(motion->yaw);
    frame.dir.y=math_fast_sin_or_cos_b(motion->yaw); frame.dir.z=0;
    if(in.throttle<0) in.throttle*=D_L30_001B1720;
    sign=1.0f;
    if(in.throttle<0) sign=-1.0f;
    amplitude=math_fabs(in.steer); driveRatio=IntegerPower(2,(turnSpeed-speed)/turnSpeed);
    steeringBoost=D_L30_001B1724*amplitude;
    steeringBoost*=sign;
    drive=in.throttle+steeringBoost;
    drive*=0.00040000002f;
    object->speed+=(in.throttle*D_L30_001B17E4-object->speed)*0.02f;
    drive*=D_L30_001B16F0;
    acceleration=drive*driveRatio;
    FastVecAdd(&frame.old,&object->position,motion);
    height=coll_probe_ground_height_below(&frame.old,0,0.5f);
    special=0;
    if(GetCollHitMaterial()==1 || GetCollHitMaterial()==11) special=1;
    if(object->position.z<height+lift+0.3f && special) object->state=5;
    desiredHeight=height+lift;
    if(D_L30_001B16C4-D_L30_001B16C8<motion->jumpTimer) motion->velocity.z+=D_L30_001B16C0*0.00040000002f;
    else motion->velocity.z-=D_L30_001B170C*0.00040000002f;
    if(height!=0) {
        apply=1;
        if(desiredHeight<frame.old.z) {
            angleDelta=fast_subtract_rotations(in.yaw,motion->pitch);
            motion->pitch=FastAddRotations(motion->pitch,angleDelta*D_L30_001B1730);
            if(g_current_map_index==8) apply=0;
        } else {
            if(motion->jumpTimer==0 && in.jump>0.2f) motion->jumpTimer=((s32)(D_L30_001B16C4) * 5 + 2) / 6;
            if(height>frame.old.z+0.1f || special) {
                frame.old.z=height;
                FastVecScale(motion,motion,D_L30_001B1714);
            }
            motion->velocity.z+=((desiredHeight-frame.old.z)*D_L30_001B16FC-motion->velocity.z)*D_L30_001B16FC;
            if(in.brake>0) {
                brakeScale=1.0f-D_L30_001B1740*in.brake;
                motion->velocity.x*=brakeScale; motion->velocity.y*=brakeScale;
            }
            {
                MoveVec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                vec_scale_to_length(ahead,&D_L30_001C0200.surface,1.0f);
                up=&frame.matrix[1];
                FastVecCross(up,&object->basis[0],ahead);
                FastVecCross(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            mat_get_euler_angles(&frame.matrix[0],&frame.pos);
            yawHalf=in.yaw*0.5f;
            targetAngle=FastAddRotations(-frame.pos.y,yawHalf*(D_L30_001B17F8*(motion->control+1.0f)));
            angleDelta=fast_subtract_rotations(targetAngle,motion->pitch);
            motion->pitch=FastAddRotations(motion->pitch,angleDelta*D_L30_001B172C);
            FastVecScale(motion,motion,D_L30_001B16E8);
            matrix_from_basis_rows(frame.scratch.inverse,&object->basis[0]);
            transform_vector(motion,motion,frame.scratch.inverse);
            motion->velocity.y*=D_L30_001B16EC;
            matrix_mul_vec3(motion,motion,&object->basis[0]);
        }
        if(apply) {
            vec_scale_to_length(&frame.accel,&object->basis[0],acceleration);
            strafeDelta=in.strafe*0.00040000002f;
            strafeScale=D_L30_001B1804*strafeDelta;
            vec_scale_to_length(&frame.matrix[0],&object->basis[1],strafeScale*motion->control);
            FastVecAdd(&frame.accel,&frame.accel,&frame.matrix[0]);
            FastVecAdd(motion,motion,&frame.accel);
        }
    }
    make_hit_descriptor(&frame.matrix[0],object,0x10000,motion,D_L30_001B17A0);
    qcopy(&object->position,&frame.old);
    moby_transform_joint_to_world(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=D_L30_001B1700-D_L30_001B17F0;
    FastVecSub(&frame.pos,&object->position,&frame.matrix[3]);
    if(coll_process_triangles(&frame.matrix[3],D_L30_001B1700) || coll_test_point(&frame.matrix[3],2,object,D_L30_001B1700)) {
        if(GetCollHitMaterial()==1 || GetCollHitMaterial()==11) object->state=5;
        if(D_L30_001C0200.object!=g_hero_moby) {
            D_L30_001C0200.normal.x-=frame.matrix[3].x; D_L30_001C0200.normal.y-=frame.matrix[3].y;
            D_L30_001C0200.normal.x*=motion->control; D_L30_001C0200.normal.y*=motion->control;
            D_L30_001C0200.normal.x+=frame.matrix[3].x; D_L30_001C0200.normal.y+=frame.matrix[3].y;
            FastVecAdd(&object->position,&D_L30_001C0200.normal,&frame.pos);
            FastVecCross(&frame.scratch.contact.normal,&D_L30_001C0200.surface,motion);
            FastVecCross(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&D_L30_001C0200.surface);
            vec_scale_to_length(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            projection=FastVecDot(motion,&frame.scratch.contact.delta);
            vec_scale_to_length(motion,&frame.scratch.contact.delta,projection*motion->control);
            FastVecScale(motion,motion,D_L30_001B1710);
        }
    }
    if(object->state==3) {
        if(motion->control<0.98f && (D_00138320&4))
            func_PAL_L30_004106D0(object,&D_L30_001C0200.point,D_L30_001B189C,D_L30_001B1894,D_L30_001B1898,D_L30_001B1890,D_L30_001B1890,D_L30_001B18A0,D_L30_001B18A4);
        func_PAL_L30_004106D0(object,&D_L30_001C0200.point,D_L30_001B186C,D_L30_001B1864,D_L30_001B1868,D_L30_001B1860,D_L30_001B1870,D_L30_001B1874,1.0f);
    }
    moby_transform_joint_to_world(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=D_L30_001B17A8;
    coll_process_hit(&frame.matrix[3],0,object,&frame.matrix[0],D_L30_001B1744);
    if(FastVecLength(motion)>D_L30_001B17AC*0.020000001f) {
        moby_transform_joint_to_world(object,1,&frame.scratch.contact.delta);
        coll_process_hit(&frame.scratch.contact.delta,0,object,&frame.matrix[0],D_L30_001B17A4);
    }
}
