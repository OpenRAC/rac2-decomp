#include "include_asm.h"

#include "common.h"
typedef int MotionQuad __attribute__((mode(TI)));
extern void func_002AFFD8(void *, void *, int);
extern void func_002B03B8(void *, void *, int);
extern float func_002B0178(void *, int, int);
extern float func_00282DB0(void *, void *);
extern void func_002B0158(void *, void *, void *, float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AA2E8(void *, float, float);
extern float func_002B0360(void *);
extern float func_00282C48(float);
extern float func_0029F530(void *);
extern int func_002A88A0(void *, void *, float, float, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern char *func_002AB1F0(void *);
extern void func_002A90C8(void *, int, int, void *, float);
extern void func_002AE838(void *, void *);
extern float func_002B04E0(void *, void *, int);
extern float func_002AAA00(void *, void *, int, float, float, float, float);
extern void func_002833F0(void *, void *);
extern void func_00283738(void *, void *, void *);
extern int func_002A8C28(void *, float, void *, int, float, float, int, int, int);
extern int func_00277258(void *, float, int, void *);
struct ImpactQueueState { char pad[20]; int index; int hit; int flags; MotionQuad point, offset, normal; };
extern struct ImpactQueueState D_001BAF80;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))

/* Steps motion under a position-dependent gravity direction and answers collisions; returns motion flags. */
int func_PAL_002B35A8(char *object, char *state)
{
    float predicted[4] __attribute__((aligned(16)));
    float oldPosition[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float scaled[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    float normal[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    /* The 48-byte rotation output shares storage with later collision probes. */
    union {
        float rotation[12];
        struct { float impulse[4], probeStart[4], probeEnd[4]; } collision;
    } scratch __attribute__((aligned(16)));
    float speed, root1, root2, angle, damped, flightTime;
    int result = 0;
    float length, approach, acceleration;
    char *hit;
    int fallback, rayHit;
    MotionQuad *hitPoint=&D_001BAF80.point;
    func_002AFFD8(object+0x10, direction, 0);
    func_002B03B8(object+0xC0, direction, 0);
    length = func_002B0178(object+0x10, 0, 0);
    approach = -func_00282DB0(state+0x80, direction);
    if (B(state,0x1A)==0) {
        func_002B0158(object,state+0x80,state+0x80,F(state,0x4C));
        acceleration = F(state,0x4C)*func_00282DF0(direction);
    } else {
        func_002B0158(object,state+0x80,state+0x80,F(state,0x50));
        acceleration = F(state,0x50)*func_00282DF0(direction);
    }
    qcopy(oldPosition,object+0x10);
    func_002B0158(object,oldPosition,oldPosition,-F(state,0x34));
    func_00282F20(scaled,direction,-approach);
    func_00282CF0(state+0x80,state+0x80,scaled);
    speed = func_00282DF0(state+0x80);
    { float target=0.040000003f;
      if (B(state,0x1A)>=2) target=0.0f;
      func_002AA2E8(&speed,target,F(state,0x2C));
    }
    func_00282F20(state+0x80,state+0x80,speed);
    func_00282CC0(state+0x80,state+0x80,scaled);
    if (F(object,0x10)<2.0f || F(object,0x10)>1021.0f ||
        F(object,0x14)<2.0f || F(object,0x14)>1021.0f ||
        F(object,0x18)<2.0f || F(object,0x18)>1021.0f) result=1;
    if (B(state,0x1A)!=0 && func_002B0360(object+0x10)<F(state,0x40)) result |= 1;
    if (F(state,0x60)!=-1.0f && F(state,0x54)!=-1.0f) {
        switch (B(state,0x1A)) {
        case 0:
            flightTime = func_00282C48(approach / acceleration);
            if (flightTime>2.0f) {
                float numerator=(F(state,0x54)-func_0029F530(object))*2.0f;
                float target = numerator / flightTime;
                if (target>0.0f) func_002AA2E8(object+0x48,target,0.120000005f);
            }
            break;
        case 1:
            if (func_0029F530(object)>=F(state,0x60)) F(object,0x48)=0.0f;
            else {
                float a=acceleration*-0.5f;
                acceleration=60.0f;
                if (func_002A88A0(&root1,&root2,a,approach-a,length)>0 && root1>0.0f && root1<acceleration) acceleration=root1;
                if (acceleration<0.0001f) acceleration=0.0001f;
                {
                    float numerator=(F(state,0x60)-func_0029F530(object))*2.0f;
                    float target = numerator / acceleration;
                    if (target>2.0f) target=2.0f;
                    else if (target<0.0f) target=0.0f;
                    func_002AA2E8(object+0x48,target,0.120000005f);
                }
            }
            break;
        case 2:
            F(object,0x48)=1.0f;
            func_00282F20(start,direction,-0.2f);
            func_00282CC0(start,start,object+0x10);
            func_00282F20(normal,direction,1.0f);
            func_00282CC0(normal,normal,object+0x10);
            if (!func_002761F8(start,normal,2,object,0)) B(state,0x1A)=1;
            else if (func_00278E78()==1) {
                hit=func_002AB1F0(object);
                if (hit) {
                    func_00282CC0(temp,object+0xC0,object+0x10);
                    func_002A90C8(object,0,0x110000,temp,(float)*(short *)(hit+4));
                }
            }
            break;
        }
    }
    func_002AE838(start,state+0x64);
    angle=func_002B04E0(object,start,0);
    damped=0.0f;
    func_002AAA00(&damped,state+0x68,0,angle,0.020106196f,0.005026549f,3.14159274f);
    qzero_nc(normal);
    normal[2]=F(state,0x68);
    func_002833F0(scratch.rotation,normal);
    func_00283738(object+0xC0,object+0xC0,scratch.rotation);
    func_00282CC0(object+0x10,object+0x10,state+0x80);
    func_00282CC0(predicted,oldPosition,state+0x80);
    func_00282CC0(start,predicted,state+0x80);
    func_002A8C28(object,F(state,0x30),start,0x4000000,1.0f,1.0f,0,1,0);
    if (func_00282DF0(state+0x80)>F(state,0x30)) {
        if (func_002761F8(oldPosition,predicted,0x24,object,0)) qcopy(predicted,hitPoint);
    }
    rayHit=func_00277258(predicted,F(state,0x30),0x24,object);
    fallback=0;
    if (!rayHit) {
        rayHit=func_002761F8(predicted,object+0x10,0x24,object,0);
        fallback=1;
        if (!rayHit) goto finish;
    }
    result |= 4;
    if (fallback) qcopy(object+0x10,hitPoint);
    else {
        qcopy(object+0x10,&D_001BAF80.offset);
        func_00282F20(temp,direction,F(state,0x34));
        func_00282CC0(object+0x10,object+0x10,temp);
    }
    acceleration=1.0f;
    func_00282F20(normal,&D_001BAF80.normal,acceleration);
    if (func_00282DB0(normal,direction)<=-0.707f) {
        float projection=func_00282DB0(state+0x80,normal);
        if (projection<0.0f) {
            if (D_001BAF80.hit==0 || D_001BAF80.flags>0) {
                func_00282F20(scratch.collision.probeStart,object+0xE0,0.2f);
                func_00282F20(scratch.collision.probeEnd,object+0xE0,-2.0f);
                func_00282CC0(scratch.collision.probeStart,scratch.collision.probeStart,object+0x10);
                func_00282CC0(scratch.collision.probeEnd,scratch.collision.probeEnd,object+0x10);
                if (func_002761F8(scratch.collision.probeStart,scratch.collision.probeEnd,2,object,0)) B(state,0x1A)=2;
            }
            func_00282F20(scratch.collision.impulse,normal,projection);
            func_00282CF0(state+0x80,state+0x80,scratch.collision.impulse);
            if (B(state,0x1A)==2) {
                float value=func_00282DF0(state+0x80);
                func_002AA2E8(&value,0.0f,F(state,0x50));
                func_00282F20(state+0x80,state+0x80,value);
            }
        }
    } else {
        float dot=func_00282DB0(state+0x80,normal);
        if (dot<0.0f) {
            dot = dot*-(F(state,0x3C)+acceleration);
            func_00282F20(scratch.collision.impulse,normal,dot);
            func_00282CC0(state+0x80,state+0x80,scratch.collision.impulse);
        }
    }
finish:
    if (B(state,0x1A)==0 && approach<0.0f) B(state,0x1A)=1;
    else if (H(state,0x38)&2) {
        if ((result&4) && approach<=0.0f) result |= 1;
    } else if (B(object,0x60)&2) {
        if (H(state,0x38)&1) result |= 1;
        else result |= 2;
    }
    return result;
}
