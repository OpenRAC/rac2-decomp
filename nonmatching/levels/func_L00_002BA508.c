/* Nonmatching: US/US2 708/720 bytes, 0/27; absent from PAL.
 * Four checks. Default profile. Equivalent predicate and switch forms retain
 * the Boolean SLTU/SLT choices where retail uses shared-one MOVZ/MOVN values.
 * GCSE off yields716 bytes but loses the saved hero-base lifetime and shrinks
 * the frame to0xF0, so it is rejected. Remaining: these predicates, initial
 * hero-base ordering, matrix/predicate saved-register priorities and call
 * setup scheduling. Reopen with a measured narrow predicate/lifetime witness.
 * Independent producer/consumer proof fixes local extents at16,48,48,64 bytes:
 * C88 zeroes16; 833F0 writes48; 83738 reads/writes48; 83658 writes64;
 * AB6D8 consumes64. Angles.w remains initialized by the real C88 call.
 * Existing animation state at hero+0x1A30 is not locally allocated or bounded.
 * BA410/B3248 predicates and B9B88 sound result retain integer returns; the
 * matrix/vector and animation state setters are void update interfaces.
 */
#include "common.h"

/* Measured hero-field prefix, with no claim about its complete owner. */
extern struct {
    unsigned char reserved000[0x184];
    float speed;
    unsigned char reserved188[0x1B8-0x188];
    int frame;
    unsigned char reserved1BC[0x278-0x1BC];
    float distance,unknown27C,angle;
    unsigned char blocked;
    unsigned char reserved285[0xC04-0x285];
    float pitch,yaw;
    unsigned char reservedC0C[0x1220-0xC0C];
    unsigned char *target;
    unsigned char reserved1224[0x123A-0x1224];
    unsigned char pending;
    unsigned char reserved123B[0x1500-0x123B];
    int override;
    unsigned char reserved1504[0x2290-0x1504];
    unsigned char *object;
    int action;
} D_00189E20 NOT_SDA;
extern struct {
    unsigned char reserved000[0x150];
    float rotation[3];
} D_L00_001B8C80 NOT_SDA;
extern int func_L00_002BA410(void);
extern float func_00283B98(float,float);
extern int func_L00_002B3248(void *);
extern int func_L00_002B9B88(int,int);
extern void func_00282C88(void *);
extern void func_L00_002D3798(void *,void *,float);
extern void func_002AF000(void *,float,float,float);
extern void func_002833F0(void *,void *);
extern void func_00283738(void *,void *,void *);
extern void func_00283658(void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_L00_00322A98(void *,void *);
extern void func_L00_00322AC0(void *,int,int,float);
extern void func_002A7470(void *,int,int,int);

void func_L00_002BA508(void)
{
    float angles[4] __attribute__((aligned(16)));
    float localMatrix[12] __attribute__((aligned(16)));
    float cameraMatrix[12] __attribute__((aligned(16)));
    float expanded[16] __attribute__((aligned(16)));
    unsigned char *actor,*component;
    int facing;
    if(D_00189E20.pending) return;
    facing=1;
    if(!D_00189E20.override) facing=0;
    switch(D_00189E20.action) {
    case 1: case 29:
        facing=1;
        if(D_00189E20.frame<21) facing=0;
        break;
    }
    if(facing && !func_L00_002BA410()) {
        D_00189E20.pitch=D_L00_001B8C80.rotation[2];
        D_00189E20.yaw=func_00283B98(-D_L00_001B8C80.rotation[1],0.12217305600643158f);
    }
    actor=D_00189E20.target;
    if(!func_L00_002B3248(actor)) return;
    D_00189E20.pending=1;
    if(facing) func_L00_002B9B88(17,0);
    actor[0x20]=10;
    component=*(unsigned char **)(actor+0x68);
    if(D_00189E20.distance<1.2f && D_00189E20.angle>0.6632251739501953f && !D_00189E20.blocked)
        *(short *)(component+0x76)=1;
    func_00282C88(component+0x40);
    if(!facing)
        func_L00_002D3798(component+0x40,component+0x40,1.0f);
    else
        func_002AF000(component+0x40,1.0f,D_00189E20.pitch,D_00189E20.yaw);
    func_00282C88(angles);
    func_002833F0(localMatrix,angles);
    if(facing) {
        angles[0]=D_L00_001B8C80.rotation[0];
        angles[1]=D_L00_001B8C80.rotation[1];
        angles[2]=D_L00_001B8C80.rotation[2];
        func_002833F0(cameraMatrix,angles);
        func_00283738(localMatrix,cameraMatrix,localMatrix);
    } else
        func_00283738(localMatrix,D_00189E20.object+0xC0,localMatrix);
    func_00283658(expanded,localMatrix);
    func_002AB6D8(expanded,actor+0xF0);
    *(int *)(component+0x64)=0;
    *(float *)(component+0x60)=0.38333335518836975f;
    if(D_00189E20.speed<0.3333333432674408f) {
        void *animation=(unsigned char *)&D_00189E20+0x1A30;
        func_L00_00322A98(actor,animation);
        func_L00_00322AC0(animation,0x30,3,0.0f);
        func_L00_00322AC0(animation,0x17,5,0.0f);
    }
    func_002A7470(actor,6,0,5);
}
