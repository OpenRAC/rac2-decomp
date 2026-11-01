/* Tier: sol-high (task v0968).
 * Best check.py result: 1216/1216 bytes, 0/2 USA v1.01 places.
 * Required profile: -O2 -G0 -ffunction-sections -g.
 * Eight instructions differ at +0x144..+0x160: the flags load crosses the
 * horizontal-speed multiply/store, and the vertical branch lacks retail's
 * branch-likely load slot. Everything outside that region agrees after linking
 * the checker relocations. No linked program build was run.
 * A typed collision-result object fixes saved pointers; a separate late height
 * scope fixes F2/F3; -g supplies the single nop preceding div.s.
 * Corrected the old draft: an initial probe miss blocks movement, while a slope
 * at or below 0.5 does not. The low-bit complement uses (flags ^ 1) & 1.
 * Tied: union-array and direct-union field views, -fno-sched-spec and
 * -fno-sched-interblock. -fno-schedule-insns grows to 1236 bytes and is worse.
 * Next: recover a real source dependence around the vertical branch, without
 * volatile locals, fabricated field accesses, or barriers.
 * All required declarations follow; symbols remain unqualified by a full build.
 *
 * closer D, 1 November 2026: sched1 hoists the flags load into the load-delay gap after the
 * velocity load, ahead of mul.s/swc1. Retail keeps it after the store, which needs a dependence from
 * the sp+0x14 store to the cfg+0x38 load: base_alias_check sees stack against argument and answers
 * no alias, so cfg's base must be unknown to alias analysis in retail (a pseudo with two sets?).
 *
 * closer D successor, 1 November 2026: copying arguments gives cfg a known base; only a pseudo with two sets loses it.
 */
#include "common.h"
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00283248(float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern int func_L04_0033C420(void *,void *,int,float,float);
extern int func_L04_0033CB08(float,void *,void *,int,float,int);
extern float func_002A89A8(void *,int,float);
typedef struct { float fields[16]; float normal[4]; } CollisionResult;
extern CollisionResult D_L04_001BFAC0;
typedef union { int q __attribute__((mode(TI))); float f[4]; } CollisionVec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
typedef union { float f[20]; int i[20]; } MovementConfig;
int func_L04_0033CC00(char *obj,MovementConfig *cfg,float *target,void *out,float scale)
{
    CollisionVec old;
    float move[4] __attribute__((aligned(16)));
    float test[4] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float accel=cfg->f[0x1C/4]*scale;
    float max=cfg->f[0x24/4]*scale;
    float distance,step,angle,height,first,second,speed;
    int flags=0,result;
    func_00282CF0(move,target,obj+0x10);
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
        angle=cfg->f[0x4C/4];
    } else {
        move[0]=func_00283180(F(obj,0xF8))*cfg->f[0x10/4];
        angle=F(obj,0xF8);
    }
    move[1]=func_00283198(angle)*cfg->f[0x10/4];
    if (cfg->i[0x38/4]&1) move[2]=0;
    else { move[2]=cfg->f[0x18/4]; cfg->f[0x18/4]-=0.0025f; }
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
        if (result&2) cfg->f[0x18/4]=-0.01f;
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
    } else if ((cfg->i[0x38/4]^1)&1) cfg->f[0x18/4]=-0.01f;
    if (distance<cfg->f[0x2C/4]) flags|=4;
    return flags;
}
