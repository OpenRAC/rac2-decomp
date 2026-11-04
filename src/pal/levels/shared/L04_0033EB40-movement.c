/* func_PAL_L04_0033EB40, the PAL copy of func_L04_0033CC00: the same C with the per-frame values
   scale by (60/50)^2: the fall step 0.0025 becomes 0.0036000002f (0x3B6BEDFB) and the -0.01 drop
   speed -0.012. */
#include "common.h"

extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CF0(float *, float *, float *);
extern void func_00282D30(void *, void *, float);

extern float func_00282E20(void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float,float);
extern int func_L04_0033C420(void *,void *,int,float,float);
extern int func_L04_0033CB08(float,void *,void *,int,float,int);
extern float func_002A89A8(void *,int,float);
typedef struct { float fields[16]; float normal[4]; } CollisionResult;
extern CollisionResult D_L04_001BFAC0;
typedef union { int q __attribute__((mode(TI))); float f[4]; } CollisionVec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef union { float f[20]; int i[20]; } MovementConfig;
/* Accelerates obj toward target, probes the ground ahead and returns the collision flags. */
int func_PAL_L04_0033EB40(char *obj,MovementConfig *cfg,float *target,void *out,float scale)
{
    CollisionVec old;
    float move[4] __attribute__((aligned(16)));
    float test[4] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float accel=cfg->f[0x1C/4]*scale;
    float max=cfg->f[0x24/4]*scale;
    float distance,step,height,first,second,speed;
    int flags=0,result;
    func_00282CF0(move,target,(float *)(obj+0x10));
    distance=func_00282E20(move);
    old.q=((CollisionVec *)(obj+0x10))->q;
    step=accel*distance;
    if (accel<step) step=accel;
    cfg->f[0x10/4]+=step;
    if (distance<cfg->f[0x10/4]*10.0f) cfg->f[0x10/4]-=cfg->f[0x20/4]*cfg->f[0x10/4];
    if (max<cfg->f[0x10/4]) cfg->f[0x10/4]=max;
    else if (cfg->f[0x10/4]<-max) cfg->f[0x10/4]=-max;
    if (cfg->i[0x38/4]&4) {
        move[0]=func_00283180(cfg->f[0x4C/4])*cfg->f[0x10/4];
        move[1]=func_00283198(cfg->f[0x4C/4])*cfg->f[0x10/4];
    } else {
        move[0]=func_00283180(F(obj,0xF8))*cfg->f[0x10/4];
        move[1]=func_00283198(F(obj,0xF8))*cfg->f[0x10/4];
    }
    if (cfg->i[0x38/4]&1) move[2]=0;
    else { move[2]=cfg->f[0x18/4]; cfg->f[0x18/4]-=0.0036000002f; }
    height=F(obj,0x18)+0.04f;
    func_00282CC0(test,obj+0x10,move);
    test[2]=F(obj,0x18)-cfg->f[0x30/4];
    if (func_L04_0033C420(test,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
        step=func_00283248(D_L04_001BFAC0.normal[2],func_00282E20(D_L04_001BFAC0.normal));
        first=D_L04_001BFAC0.fields[10];
        if (step>0.5f) {
            if (func_00282E20(move)>0.1f) {
                func_00282F20(probe,move,0.57f);
                func_00282CC0(probe,probe,obj+0x10);
                probe[2]=F(obj,0x18)-cfg->f[0x30/4];
                if (func_L04_0033C420(probe,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
                    second=D_L04_001BFAC0.fields[10];
                    if (func_00283248(D_L04_001BFAC0.normal[2],func_00282E20(D_L04_001BFAC0.normal))>=0.5f) {
                        flags=0x22;
                        if ((cfg->i[0x38/4]&8) && second<height && first<height) flags=8;
                    }
                } else {
                    flags=0x22;
                    if ((cfg->i[0x38/4]&8) && first<height) flags=8;
                }
            }
        }
    } else {
        flags=0x22;
        if (cfg->i[0x38/4]&8) flags=8;
    }
    if (!(flags&2)) {
        speed=func_00282E20(move);
        func_00282D30(test,move,1.0f/speed);
        result=func_L04_0033CB08(cfg->f[4/4],obj,move,cfg->i[0/4],cfg->f[0x30/4],cfg->i[0x38/4]);
        if (result&2) cfg->f[0x18/4]=-0.012f;
        if (result&1) {
            flags|=1;
            if (move[0]*test[0]+move[1]*test[1]<speed*0.2f) flags|=2;
            {
                float ground=func_002A89A8(obj+0x10,0,0.5f);
                float old_height=old.f[2];
                if (cfg->f[8/4]<old_height-ground || cfg->f[12/4]<ground-old_height) {
                    flags|=0x22;
                    ((CollisionVec *)(obj+0x10))->q=old.q;
                }
            }
        }
        qcopy(out,move);
    } else if ((cfg->i[0x38/4]^1)&1) cfg->f[0x18/4]=-0.012f;
    if (distance<cfg->f[0x2C/4]) flags|=4;
    return flags;
}
