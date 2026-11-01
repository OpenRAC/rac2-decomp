#include "include_asm.h"

#include "common.h"
extern float func_00282E20(void *);
extern void func_002AA2E8(float *,float,float);
extern void func_00282F70(void *,void *,float);
extern void func_00282C88(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern float func_00282DF0(void *);
extern float func_002A89A8(void *,float,int);
extern int func_00278E78(void);
extern float func_002A8A20(void *);
extern float func_00282C48(float);
extern float func_0029F530(void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int func_002A88A0(float *,float *,float,float,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern float func_002AAA00(void *,void *,int,float,float,float,float);
extern int func_002A8C28(void *,float,void *,int,float,float,int,int,int);
extern int func_00277258(void *,float,int,void *);
extern char *func_002AB1F0(void *);
extern void func_002A90C8(void *,int,int,void *,float);
extern void func_002C9218(int,void *,void *,float);
extern void func_002833F0(void *,void *);
extern void func_00283738(void *,void *,void *);
extern float func_00283B98(float,float);
typedef int MotionQuad __attribute__((mode(TI)));
struct ImpactQueueState { char pad[20]; int index; int hit; int flags; MotionQuad point, offset, normal; };
extern struct ImpactQueueState D_001BAF80;
#define BF(p,n) (*(float *)((p)+(n)))
#define BU(p,n) (*(unsigned char *)((p)+(n)))
#define BH(p,n) (*(unsigned short *)((p)+(n)))
#define BI(p,n) (*(int *)((p)+(n)))

/* Steps motion, animation speed and collision response; returns motion flags. */
int func_PAL_002B2AC8(char *object,char *state)
{
    float destination[4], original[4], offset[4], start[4];
    /* Collision vectors and the later 3x4 rotation matrix share stack storage. */
    union {
        struct { float normal[4], work[4], rayStart[4]; } collision;
        float rotation[12];
    } scratch;
    float rayEnd[4], impact[4];
    float speed, root1, root2, length;
    float t, ground, accel, response, distance;
    int flags=0;
    int fallback;
    char *record;

    if (BU(state,0x1a)==0) BF(state,0x88)=BF(state,0x88)-BF(state,0x4c);
    else BF(state,0x88)=BF(state,0x88)-BF(state,0x50);

    speed=func_00282E20((state+0x80));
    { float target=0.020000001f;
      if (BU(state,0x1a)>=2) target=0.0f;
      func_002AA2E8(&speed,target,BF(state,0x2c));
    }

    func_00282F70((state+0x80),(state+0x80),speed);
    func_00282C88(offset);
    offset[2]=BF(state,0x34);
    func_00283098(offset,offset,(object+0xc0));
    func_00282CC0(original,offset,(object+0x10));
    ground=func_002A89A8(original,0.5f,0);
    if (!func_00278E78()) {
        if (!BU(state,0x1b) && ground<=original[2] && original[2]+BF(state,0x88)<ground) BU(state,0x1b)=1;
        ground=func_002A8A20((object+0x10));
    }
    if (BU(state,0x1b)) {
        if (BU(state,0x1b)<4) func_00282D30((state+0x80),(state+0x80),0.7f);
        if (BU(state,0x1b)<7) { BU(state,0x1b)++; BF(state,0x50)*=0.75f; }
    }
    if (BF(object,0x10)<2.0f || 1021.0f<BF(object,0x10) || BF(object,0x14)<2.0f || 1021.0f<BF(object,0x14) || BF(object,0x18)<2.0f || 1021.0f<BF(object,0x18)) flags=1;
    if (BU(state,0x1a) && BF(object,0x18)<BF(state,0x40)) flags|=1;
    else if (BU(object,0x43)!=BU(state,0x15) && BF(state,0x60)!=-1.0f && BF(state,0x54)!=-1.0f) {
        switch (BU(state,0x1a)) {
        case 0: {
            float flightTime, numerator;
            flightTime=func_00282C48(BF(state,0x88)/BF(state,0x4c));
            if (2.0f<flightTime) {
                distance=func_0029F530(object);
                numerator=BF(state,0x54)-distance;
                numerator=numerator+numerator;
                accel=numerator/flightTime;
                if (0.0f<accel) func_002AA2E8((float *)(object+0x48),accel,0.24000001f);
            }
            break;
        }
        case 1:
            if (BF(state,0x60)<=func_0029F530(object)) { BF(object,0x48)=0; break; }
            else if (BU(state,0x15)!=255 && (ground==0.0f || ground<BF(state,0x40) || 10.0f<BF(object,0x18)-ground)) {
                if (BU(object,0x43)!=BU(state,0x15)) func_PAL_002A7E68(object,BU(state,0x15),0,4);
                if (0.006f<BF(state,0x50)) BF(state,0x50)=0.006f;
                break;
            }
            {
                float numerator;
                float halfGravity=BF(state,0x50)*-0.5f;
                t=60.0f;
                if (func_002A88A0(&root1,&root2,halfGravity,BF(state,0x88)-halfGravity,BF(object,0x18)-ground)>0 && 0.0f<root1 && root1<t) t=root1;
                if (t<0.0001f) t=0.0001f;
                distance=func_0029F530(object);
                numerator=BF(state,0x60)-distance;
                numerator=numerator+numerator;
                accel=numerator/t;
                if (2.0f<accel) accel=2.0f;
                else if (accel<0.0f) accel=0.0f;
                func_002AA2E8((float *)(object+0x48),accel,0.24000001f);
            }
            break;
        case 2:
            BF(object,0x48)=1.0f;
            qcopy(start,(object+0x10)); start[2]+=0.2f;
            qcopy(scratch.collision.normal,(object+0x10)); scratch.collision.normal[2]-=1.0f;
            if (!func_002761F8(start,scratch.collision.normal,2,object,0)) BU(state,0x1a)=1;
            break;
        }
    }
    func_002AAA00(object+0xf8,state+0x68,0,BF(state,0x64),0.020106196f,0.005026549f,3.140000104904175f);
    func_00282CC0((object+0x10),(object+0x10),(state+0x80));
    func_00282CC0(destination,original,(state+0x80));
    func_00282D30(start,(state+0x80),3.0f);
    func_00282CC0(start,start,destination);
    func_002A8C28(object,BF(state,0x30),start,0x4000000,1.0f,1.0f,0,1,0);
    if (BF(state,0x30)<func_00282DF0((state+0x80))) {
        if (func_002761F8(original,destination,0x24,object,0)) qcopy(destination,&D_001BAF80.point);
    }
    fallback=0;
    if (!func_00277258(destination,BF(state,0x30),0x24,object)) {
        int hit=func_002761F8(destination,(object+0x10),0x24,object,0);
        fallback=1;
        if (!hit) goto finish;
    }
    flags|=4;
    if (fallback) qcopy((object+0x10),&D_001BAF80.point);
    else func_00282CF0((object+0x10),&D_001BAF80.offset,offset);
    response=1.0f;
    func_00282F20(scratch.collision.normal,&D_001BAF80.normal,response);
    if (0.7070000171661377f<=scratch.collision.normal[2]) {
        float projection=func_00282DB0((state+0x80),scratch.collision.normal);
        if (projection<0.0f) {
            if (!D_001BAF80.hit || D_001BAF80.flags>0) {
                qcopy(scratch.collision.rayStart,(object+0x10)); scratch.collision.rayStart[2]+=0.2f;
                qcopy(rayEnd,(object+0x10)); rayEnd[2]-=2.0f;
                if (func_002761F8(scratch.collision.rayStart,rayEnd,2,object,0)) {
                    BU(state,0x1a)=2;
                    if (func_00278E78()==1) {
                        record=func_002AB1F0(object);
                        if (record) {
                            func_00282CC0(impact,(object+0xc0),(object+0x10));
                            func_002A90C8(object,0,0x110000,impact,(float)*(short *)(record+4));
                        }
                    }
                }
            }
            func_00282F20(scratch.collision.work,scratch.collision.normal,projection);
            func_00282CF0((state+0x80),(state+0x80),scratch.collision.work);
            if (BU(state,0x1a)==2) {
                if (D_001BAF80.hit && D_001BAF80.flags<0) flags|=BH(state,0x38)&1;
                length=func_00282DF0((state+0x80));
                func_002AA2E8(&length,0.0f,BF(state,0x50));
                func_00282F20((state+0x80),(state+0x80),length);
            }
        }
    } else {
        float dot=func_00282DB0((state+0x80),scratch.collision.normal);
        if (dot<0.0f) {
            dot=dot*-(BF(state,0x3c)+response);
            func_00282F20(scratch.collision.work,scratch.collision.normal,dot);
            func_00282CC0((state+0x80),(state+0x80),scratch.collision.work);
        }
    }
finish:
    if (BI(state,0x7c)!=-1) func_002C9218(BI(state,0x7c),(object+0x10),(object+0x10),BF(state,0x30));
    if (!BU(state,0x1a) && BF(state,0x88)<0.0f) BU(state,0x1a)=1;
    else if (BH(state,0x38)&2) {
        if (flags&4) { if (BF(state,0x88)<=0.0f) flags|=1; }
        if (BH(object,0x34)&0x100) {
            func_002833F0(scratch.rotation,state+0x90);
            func_00283738((object+0xc0),(object+0xc0),scratch.rotation);
        } else {
            BF(object,0xf0)=func_00283B98(BF(object,0xf0),BF(state,0x90));
            BF(object,0xf4)=func_00283B98(BF(object,0xf4),BF(state,0x94));
            BF(object,0xf8)=func_00283B98(BF(object,0xf8),BF(state,0x98));
            func_002833F0((object+0xc0),object+0xf0);
        }
        func_00282C88(scratch.collision.normal); scratch.collision.normal[2]=BF(state,0x34);
        func_00283098(scratch.collision.normal,scratch.collision.normal,(object+0xc0));
        func_00282CF0(scratch.collision.work,offset,scratch.collision.normal);
        func_00282CC0((object+0x10),(object+0x10),scratch.collision.work);
    } else {
        if (((BU(object,0x60)&2) && BU(object,0x43)!=BU(state,0x15)) || (BU(state,0x1a)==2 && BU(object,0x43)==BU(state,0x15))) {
            if (BH(state,0x38)&1) flags|=3;
            else flags|=2;
        }
    }
    return flags;
}
