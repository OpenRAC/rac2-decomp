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
extern int D_001A79F0;
extern unsigned int D_00138320 NOT_SDA;
extern void *D_0018C0B0 NOT_SDA;
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
extern void func_L30_0040B4E0(float *,float *,float *,float *,float *,float *);
extern void func_PAL_L30_004106D0(void *,void *,int,float,float,float,float,float,float);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *,void *);
extern float func_00282C48(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283B98(float,float);
extern float func_00283BE0(float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00283698(void *,void *);
extern void func_0029FCC0(void *,int,void *);
extern float func_L08_003277C0(int,float);
extern float func_002A89A8(void *,int,float);
extern void func_002A8C00(void *,void *,int,void *,float);
extern void func_002AB6D8(void *,void *);
extern int func_00278E78(void);
extern int func_00278870(void *,float);
extern int func_00277258(void *,int,void *,float);
extern void func_00277F48(void *,int,void *,void *,float);

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
    if(input) func_L30_0040B4E0(&in.steer,&in.throttle,&in.yaw,&in.brake,&in.strafe,&in.jump);
    control=motion->control;
    in.throttle*=control;
    in.brake+=1.0f-motion->control;
    in.strafe*=motion->control;
    in.jump*=motion->control;
    motion->throttle=in.throttle;
    lift=D_L30_001B16F8*motion->control+D_L30_001B17F0*(1.0f-motion->control);
    in.yaw*=0.017453294f;
    in.yaw*=D_L30_001B1734;
    speed=func_00282DF0(motion)*motion->control;
    turnSpeed=D_L30_001B16F4*0.020000001f;
    speedLimit=D_L30_001B173C*0.020000001f;
    steeringDelta=in.steer*((speed<speedLimit?speed:speedLimit)/speedLimit*D_L30_001B1738+(1.0f-D_L30_001B1738)+D_L30_001B17F4*(1.0f-motion->control));
    steeringDelta*=0.0003490659f;
    motion->yaw=func_00283B98(motion->yaw,D_L30_001B16E4*steeringDelta);
    steerRadians=in.steer*0.017453294f;
    rollSpeed=D_L30_001B171C*steerRadians;
    rollSpeed*=motion->control;
    targetRoll=rollSpeed*(D_L30_001B1728*in.throttle+(1.0f-D_L30_001B1728));
    motion->roll+=(targetRoll-object->basis[3].x)*D_L30_001B1718;
    frame.dir.x=func_00283180(motion->yaw);
    frame.dir.y=func_00283198(motion->yaw); frame.dir.z=0;
    if(in.throttle<0) in.throttle*=D_L30_001B1720;
    sign=1.0f;
    if(in.throttle<0) sign=-1.0f;
    amplitude=func_00282C48(in.steer); driveRatio=func_L08_003277C0(2,(turnSpeed-speed)/turnSpeed);
    steeringBoost=D_L30_001B1724*amplitude;
    steeringBoost*=sign;
    drive=in.throttle+steeringBoost;
    drive*=0.00040000002f;
    object->speed+=(in.throttle*D_L30_001B17E4-object->speed)*0.02f;
    drive*=D_L30_001B16F0;
    acceleration=drive*driveRatio;
    func_00282CC0(&frame.old,&object->position,motion);
    height=func_002A89A8(&frame.old,0,0.5f);
    special=0;
    if(func_00278E78()==1 || func_00278E78()==11) special=1;
    if(object->position.z<height+lift+0.3f && special) object->state=5;
    desiredHeight=height+lift;
    if(D_L30_001B16C4-D_L30_001B16C8<motion->jumpTimer) motion->velocity.z+=D_L30_001B16C0*0.00040000002f;
    else motion->velocity.z-=D_L30_001B170C*0.00040000002f;
    if(height!=0) {
        apply=1;
        if(desiredHeight<frame.old.z) {
            angleDelta=func_00283BE0(in.yaw,motion->pitch);
            motion->pitch=func_00283B98(motion->pitch,angleDelta*D_L30_001B1730);
            if(D_001A79F0==8) apply=0;
        } else {
            if(motion->jumpTimer==0 && in.jump>0.2f) motion->jumpTimer=((s32)(D_L30_001B16C4) * 5 + 2) / 6;
            if(height>frame.old.z+0.1f || special) {
                frame.old.z=height;
                func_00282D30(motion,motion,D_L30_001B1714);
            }
            motion->velocity.z+=((desiredHeight-frame.old.z)*D_L30_001B16FC-motion->velocity.z)*D_L30_001B16FC;
            if(in.brake>0) {
                brakeScale=1.0f-D_L30_001B1740*in.brake;
                motion->velocity.x*=brakeScale; motion->velocity.y*=brakeScale;
            }
            {
                MoveVec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                func_00282F20(ahead,&D_L30_001C0200.surface,1.0f);
                up=&frame.matrix[1];
                func_00282DD8(up,&object->basis[0],ahead);
                func_00282DD8(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            func_002AB6D8(&frame.matrix[0],&frame.pos);
            yawHalf=in.yaw*0.5f;
            targetAngle=func_00283B98(-frame.pos.y,yawHalf*(D_L30_001B17F8*(motion->control+1.0f)));
            angleDelta=func_00283BE0(targetAngle,motion->pitch);
            motion->pitch=func_00283B98(motion->pitch,angleDelta*D_L30_001B172C);
            func_00282D30(motion,motion,D_L30_001B16E8);
            func_00283698(frame.scratch.inverse,&object->basis[0]);
            func_002830C0(motion,motion,frame.scratch.inverse);
            motion->velocity.y*=D_L30_001B16EC;
            func_00283098(motion,motion,&object->basis[0]);
        }
        if(apply) {
            func_00282F20(&frame.accel,&object->basis[0],acceleration);
            strafeDelta=in.strafe*0.00040000002f;
            strafeScale=D_L30_001B1804*strafeDelta;
            func_00282F20(&frame.matrix[0],&object->basis[1],strafeScale*motion->control);
            func_00282CC0(&frame.accel,&frame.accel,&frame.matrix[0]);
            func_00282CC0(motion,motion,&frame.accel);
        }
    }
    func_002A8C00(&frame.matrix[0],object,0x10000,motion,D_L30_001B17A0);
    qcopy(&object->position,&frame.old);
    func_0029FCC0(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=D_L30_001B1700-D_L30_001B17F0;
    func_00282CF0(&frame.pos,&object->position,&frame.matrix[3]);
    if(func_00278870(&frame.matrix[3],D_L30_001B1700) || func_00277258(&frame.matrix[3],2,object,D_L30_001B1700)) {
        if(func_00278E78()==1 || func_00278E78()==11) object->state=5;
        if(D_L30_001C0200.object!=D_0018C0B0) {
            D_L30_001C0200.normal.x-=frame.matrix[3].x; D_L30_001C0200.normal.y-=frame.matrix[3].y;
            D_L30_001C0200.normal.x*=motion->control; D_L30_001C0200.normal.y*=motion->control;
            D_L30_001C0200.normal.x+=frame.matrix[3].x; D_L30_001C0200.normal.y+=frame.matrix[3].y;
            func_00282CC0(&object->position,&D_L30_001C0200.normal,&frame.pos);
            func_00282DD8(&frame.scratch.contact.normal,&D_L30_001C0200.surface,motion);
            func_00282DD8(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&D_L30_001C0200.surface);
            func_00282F20(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            projection=func_00282DB0(motion,&frame.scratch.contact.delta);
            func_00282F20(motion,&frame.scratch.contact.delta,projection*motion->control);
            func_00282D30(motion,motion,D_L30_001B1710);
        }
    }
    if(object->state==3) {
        if(motion->control<0.98f && (D_00138320&4))
            func_PAL_L30_004106D0(object,&D_L30_001C0200.point,D_L30_001B189C,D_L30_001B1894,D_L30_001B1898,D_L30_001B1890,D_L30_001B1890,D_L30_001B18A0,D_L30_001B18A4);
        func_PAL_L30_004106D0(object,&D_L30_001C0200.point,D_L30_001B186C,D_L30_001B1864,D_L30_001B1868,D_L30_001B1860,D_L30_001B1870,D_L30_001B1874,1.0f);
    }
    func_0029FCC0(object,0,&frame.matrix[3]);
    frame.matrix[3].z+=D_L30_001B17A8;
    func_00277F48(&frame.matrix[3],0,object,&frame.matrix[0],D_L30_001B1744);
    if(func_00282DF0(motion)>D_L30_001B17AC*0.020000001f) {
        func_0029FCC0(object,1,&frame.scratch.contact.delta);
        func_00277F48(&frame.scratch.contact.delta,0,object,&frame.matrix[0],D_L30_001B17A4);
    }
}
