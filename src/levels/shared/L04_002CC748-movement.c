#include "common.h"

extern void func_00282CC0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(float *, float *, float);
extern void func_00282CF0(float *, float *, float *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);

typedef int MovementQuadword __attribute__((mode(TI)));

/* the hero object, with the fields this function reads and writes */
typedef struct {
    u8    pad00[0x80];
    f32   position[4];
    f32   rotation[4];
    u8    padA0[0x50];
    f32   velocity[4];
    f32   surface_motion[4];
    f32   displacement[4];
    f32   resolved_velocity[4];
    f32   resolved_velocity_xy[4];
    f32   resolved_velocity_planar[4];
    f32   surface_displacement[4];
    u8    pad160[0x10];
    f32   speed;
    f32   planar_speed;
    f32   forward_speed;
    f32   slope;
    f32   vertical_speed;
    f32   surface_speed;
    u8    pad188[0x68];
    s16   air_frames;
    u8    pad1F2[0x72];
    f32   speed_limit;
    u8    pad268[4];
    s32   collision_id;
    u8    pad270[0x17];
    u8    collision_flag;
    u8    pad288[0x94];
    f32   fall_speed_limit;
    u8    pad320[0x268];
    s32   collision_mode;
    u8    pad58C[0x4D4];
    f32   move_impulse[4];
    u8    padA70[0x1824];
    s32   state;
    u8    pad2298[4];
    s32   control_mode;
} Hero;

extern Hero D_00189E20;
extern void func_L00_002D4140(int, void *, void *);
extern float func_L00_002D3A58(void *);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3BD8(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D3960(void *, void *);
extern void func_00282C88(void *);
extern void func_L00_002B5A88(void);
extern void func_L04_002DAD10(void);
extern void func_L00_002B5250(void);
extern float func_L00_002B5590(void *);

/* Moves the hero by its velocity, impulse and surface motion, then measures the
   resolved displacement and the speeds derived from it. */
void func_L04_002DBE70(void) {
    float old[4];
    float horizontal[4];
    float flat[4];

    qcopy(old, D_00189E20.position);
    func_L00_002D4140(D_00189E20.collision_mode, D_00189E20.surface_motion,
                      D_00189E20.rotation);
    if (D_00189E20.state == 0x14 || D_00189E20.state == 0x5B ||
        D_00189E20.state == 0x58 || D_00189E20.state == 0x81) {
        if (D_00189E20.air_frames == 0) {
            if (func_L00_002D3A58(D_00189E20.velocity) > D_00189E20.speed_limit - 0.02f) {
                func_L00_002D3BD8(D_00189E20.velocity, D_00189E20.velocity,
                                  D_00189E20.speed_limit - 0.02f);
            }
        }
        if (func_L00_002D3B00(D_00189E20.velocity) < -D_00189E20.fall_speed_limit) {
            float fall = -D_00189E20.fall_speed_limit - 0.02f;

            if (fall > 0.0f)
                fall = 0.0f;
            func_L00_002D3B58(D_00189E20.velocity, D_00189E20.velocity, fall);
        }
    } else if (D_00189E20.control_mode != 13) {
        if (D_00189E20.control_mode != 14) {
            if (D_00189E20.air_frames == 0) {
                if (func_00282DF0(D_00189E20.velocity) > D_00189E20.speed_limit - 0.02f) {
                    func_00282F20(D_00189E20.velocity, D_00189E20.velocity,
                                  D_00189E20.speed_limit - 0.02f);
                }
            }
        }
    }
    func_00282CC0(D_00189E20.position, D_00189E20.position, D_00189E20.velocity);
    func_00282CC0(D_00189E20.position, D_00189E20.position, D_00189E20.move_impulse);
    func_00282C88(D_00189E20.move_impulse);
    D_00189E20.collision_flag = 0;
    D_00189E20.collision_id = 0;
    if (func_00282DF0(D_00189E20.surface_motion) <= 0.0001f) {
        func_L00_002B5A88();
        func_L04_002DAD10();
        func_00282CF0(D_00189E20.displacement, D_00189E20.position, old);
        func_L00_002B5250();
    } else {
        func_L04_002DAD10();
    }

    /* the move actually made, projected on the velocity in three variants */
    func_00282CF0(D_00189E20.resolved_velocity, D_00189E20.position, old);
    qcopy(D_00189E20.resolved_velocity_planar, D_00189E20.resolved_velocity);
    qcopy(D_00189E20.resolved_velocity_xy, D_00189E20.resolved_velocity);
    func_00282F20(D_00189E20.resolved_velocity, D_00189E20.resolved_velocity, 1.0f);
    {
        float dot = func_00282DB0(D_00189E20.resolved_velocity, D_00189E20.velocity);

        if (dot < 0.0f)
            dot = 0.0f;
        func_00282F20(D_00189E20.resolved_velocity, D_00189E20.velocity, dot);
    }
    qcopy(horizontal, D_00189E20.velocity);
    func_L00_002D3960(horizontal, horizontal);
    func_L00_002D3960(D_00189E20.resolved_velocity_planar, D_00189E20.resolved_velocity_planar);
    func_00282F20(D_00189E20.resolved_velocity_planar, D_00189E20.resolved_velocity_planar,
                  1.0f);
    {
        float dot = func_00282DB0(D_00189E20.resolved_velocity_planar, horizontal);

        if (dot < 0.0f)
            dot = 0.0f;
        func_00282F20(D_00189E20.resolved_velocity_planar, horizontal, dot);
    }
    qcopy(flat, D_00189E20.velocity);
    func_L00_002D3BD8(flat, flat, 0.0f);
    func_L00_002D3BD8(D_00189E20.resolved_velocity_xy, D_00189E20.resolved_velocity_xy, 0.0f);
    func_00282F20(D_00189E20.resolved_velocity_xy, D_00189E20.resolved_velocity_xy, 1.0f);
    {
        float dot = func_00282DB0(D_00189E20.resolved_velocity_xy, flat);

        if (dot < 0.0f)
            dot = 0.0f;
        func_00282F20(D_00189E20.resolved_velocity_xy, flat, dot);
    }

    D_00189E20.speed = func_00282DF0(D_00189E20.resolved_velocity);
    D_00189E20.planar_speed = func_L00_002D3A58(D_00189E20.resolved_velocity);
    *(MovementQuadword *)horizontal = *(MovementQuadword *)D_00189E20.resolved_velocity;
    D_00189E20.forward_speed = func_L00_002B5590(horizontal);
    D_00189E20.vertical_speed = func_L00_002D3B00(D_00189E20.resolved_velocity);
    if (D_00189E20.forward_speed < 0.0f)
        D_00189E20.forward_speed = 0.0f;

    /* the part of the move caused by the surface the hero stands on */
    qcopy(horizontal, D_00189E20.position);
    if (func_00282DF0(D_00189E20.surface_motion) > 0.0001f) {
        float w;

        func_00282CC0(D_00189E20.position, D_00189E20.position, D_00189E20.surface_motion);
        w = D_00189E20.surface_motion[3];
        func_00282C88(D_00189E20.surface_motion);
        D_00189E20.surface_motion[3] = w;
        func_L00_002B5A88();
        func_L04_002DAD10();
        func_00282CF0(D_00189E20.displacement, D_00189E20.position, old);
        func_L00_002B5250();
    }
    func_00282CF0(D_00189E20.surface_displacement, D_00189E20.position, horizontal);
    D_00189E20.surface_speed = func_00282DF0(D_00189E20.surface_displacement);
    D_00189E20.surface_displacement[3] = D_00189E20.surface_motion[3];
    D_00189E20.surface_motion[3] = 0.0f;
    func_00282CF0(D_00189E20.displacement, D_00189E20.position, old);

    D_00189E20.slope = 0.0f;
    if (D_00189E20.planar_speed > 0.004f) {
        D_00189E20.slope = D_00189E20.displacement[2] / D_00189E20.planar_speed;
        if (D_00189E20.slope > 0.5f)
            D_00189E20.slope = 0.5f;
        else if (D_00189E20.slope < -0.5f)
            D_00189E20.slope = -0.5f;
    }
    if (D_00189E20.speed > 0.8666667342185974f) {
        func_00282D30(D_00189E20.displacement, D_00189E20.displacement,
                      0.8666667342185974f / D_00189E20.speed);
        D_00189E20.speed = 0.8666667342185974f;
    }
}

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
int func_L04_0033CC00(char *obj,MovementConfig *cfg,float *target,void *out,float scale)
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
