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

    qcopy(old, gHeroState.position);
    UpdateHeroAttachment(gHeroState.collision_mode, gHeroState.surface_motion,
                      gHeroState.rotation);
    if (gHeroState.state == 0x14 || gHeroState.state == 0x5B ||
        gHeroState.state == 0x58 || gHeroState.state == 0x81) {
        if (gHeroState.air_frames == 0) {
            if (GetViewSpaceVectorLength(gHeroState.velocity) > gHeroState.speed_limit - 0.02f) {
                SetViewSpaceVectorLength(gHeroState.velocity, gHeroState.velocity,
                                  gHeroState.speed_limit - 0.02f);
            }
        }
        if (GetViewSpaceHeight(gHeroState.velocity) < -gHeroState.fall_speed_limit) {
            float fall = -gHeroState.fall_speed_limit - 0.02f;

            if (fall > 0.0f)
                fall = 0.0f;
            SetViewSpaceHeight(gHeroState.velocity, gHeroState.velocity, fall);
        }
    } else if (gHeroState.control_mode != 13) {
        if (gHeroState.control_mode != 14) {
            if (gHeroState.air_frames == 0) {
                if (FastVecLength(gHeroState.velocity) > gHeroState.speed_limit - 0.02f) {
                    vec_scale_to_length(gHeroState.velocity, gHeroState.velocity,
                                  gHeroState.speed_limit - 0.02f);
                }
            }
        }
    }
    FastVecAdd(gHeroState.position, gHeroState.position, gHeroState.velocity);
    FastVecAdd(gHeroState.position, gHeroState.position, gHeroState.move_impulse);
    ClearVector128(gHeroState.move_impulse);
    gHeroState.collision_flag = 0;
    gHeroState.collision_id = 0;
    if (FastVecLength(gHeroState.surface_motion) <= 0.0001f) {
        ResolveHeroCollisionWithRewind();
        Hero_ProbeGround();
        FastVecSub(gHeroState.displacement, gHeroState.position, old);
        EaseHeroPositionToGoal();
    } else {
        Hero_ProbeGround();
    }

    /* the move actually made, projected on the velocity in three variants */
    FastVecSub(gHeroState.resolved_velocity, gHeroState.position, old);
    qcopy(gHeroState.resolved_velocity_planar, gHeroState.resolved_velocity);
    qcopy(gHeroState.resolved_velocity_xy, gHeroState.resolved_velocity);
    vec_scale_to_length(gHeroState.resolved_velocity, gHeroState.resolved_velocity, 1.0f);
    {
        float dot = FastVecDot(gHeroState.resolved_velocity, gHeroState.velocity);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(gHeroState.resolved_velocity, gHeroState.velocity, dot);
    }
    qcopy(horizontal, gHeroState.velocity);
    ProjectVectorOntoViewPlane(horizontal, horizontal);
    ProjectVectorOntoViewPlane(gHeroState.resolved_velocity_planar, gHeroState.resolved_velocity_planar);
    vec_scale_to_length(gHeroState.resolved_velocity_planar, gHeroState.resolved_velocity_planar,
                  1.0f);
    {
        float dot = FastVecDot(gHeroState.resolved_velocity_planar, horizontal);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(gHeroState.resolved_velocity_planar, horizontal, dot);
    }
    qcopy(flat, gHeroState.velocity);
    SetViewSpaceVectorLength(flat, flat, 0.0f);
    SetViewSpaceVectorLength(gHeroState.resolved_velocity_xy, gHeroState.resolved_velocity_xy, 0.0f);
    vec_scale_to_length(gHeroState.resolved_velocity_xy, gHeroState.resolved_velocity_xy, 1.0f);
    {
        float dot = FastVecDot(gHeroState.resolved_velocity_xy, flat);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(gHeroState.resolved_velocity_xy, flat, dot);
    }

    gHeroState.speed = FastVecLength(gHeroState.resolved_velocity);
    gHeroState.planar_speed = GetViewSpaceVectorLength(gHeroState.resolved_velocity);
    *(MovementQuadword *)horizontal = *(MovementQuadword *)gHeroState.resolved_velocity;
    gHeroState.forward_speed = GetSpeedAlongHeroForward(horizontal);
    gHeroState.vertical_speed = GetViewSpaceHeight(gHeroState.resolved_velocity);
    if (gHeroState.forward_speed < 0.0f)
        gHeroState.forward_speed = 0.0f;

    /* the part of the move caused by the surface the hero stands on */
    qcopy(horizontal, gHeroState.position);
    if (FastVecLength(gHeroState.surface_motion) > 0.0001f) {
        float w;

        FastVecAdd(gHeroState.position, gHeroState.position, gHeroState.surface_motion);
        w = gHeroState.surface_motion[3];
        ClearVector128(gHeroState.surface_motion);
        gHeroState.surface_motion[3] = w;
        ResolveHeroCollisionWithRewind();
        Hero_ProbeGround();
        FastVecSub(gHeroState.displacement, gHeroState.position, old);
        EaseHeroPositionToGoal();
    }
    FastVecSub(gHeroState.surface_displacement, gHeroState.position, horizontal);
    gHeroState.surface_speed = FastVecLength(gHeroState.surface_displacement);
    gHeroState.surface_displacement[3] = gHeroState.surface_motion[3];
    gHeroState.surface_motion[3] = 0.0f;
    FastVecSub(gHeroState.displacement, gHeroState.position, old);

    gHeroState.slope = 0.0f;
    if (gHeroState.planar_speed > 0.004f) {
        gHeroState.slope = gHeroState.displacement[2] / gHeroState.planar_speed;
        if (gHeroState.slope > 0.5f)
            gHeroState.slope = 0.5f;
        else if (gHeroState.slope < -0.5f)
            gHeroState.slope = -0.5f;
    }
    if (gHeroState.speed > 0.8666667342185974f) {
        FastVecScale(gHeroState.displacement, gHeroState.displacement,
                      0.8666667342185974f / gHeroState.speed);
        gHeroState.speed = 0.8666667342185974f;
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
    FastVecSub(move,target,(float *)(obj+0x10));
    distance=vec_length_xy(move);
    old.q=((CollisionVec *)(obj+0x10))->q;
    step=accel*distance;
    if (accel<step) step=accel;
    cfg->f[0x10/4]+=step;
    if (distance<cfg->f[0x10/4]*10.0f) cfg->f[0x10/4]-=cfg->f[0x20/4]*cfg->f[0x10/4];
    if (max<cfg->f[0x10/4]) cfg->f[0x10/4]=max;
    else if (cfg->f[0x10/4]<-max) cfg->f[0x10/4]=-max;
    if (cfg->i[0x38/4]&4) {
        move[0]=FastSinOrCosA(cfg->f[0x4C/4])*cfg->f[0x10/4];
        move[1]=FastSinOrCosB(cfg->f[0x4C/4])*cfg->f[0x10/4];
    } else {
        move[0]=FastSinOrCosA(F(obj,0xF8))*cfg->f[0x10/4];
        move[1]=FastSinOrCosB(F(obj,0xF8))*cfg->f[0x10/4];
    }
    if (cfg->i[0x38/4]&1) move[2]=0;
    else { move[2]=cfg->f[0x18/4]; cfg->f[0x18/4]-=0.0025f; }
    height=F(obj,0x18)+0.04f;
    FastVecAdd(test,obj+0x10,move);
    test[2]=F(obj,0x18)-cfg->f[0x30/4];
    if (CheckGroundBelowPoint(test,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
        step=FastMatrixHelperA(D_L04_001BFAC0.normal[2],vec_length_xy(D_L04_001BFAC0.normal));
        first=D_L04_001BFAC0.fields[10];
        if (step>0.5f) {
            if (vec_length_xy(move)>0.1f) {
                vec_scale_to_length(probe,move,0.57f);
                FastVecAdd(probe,probe,obj+0x10);
                probe[2]=F(obj,0x18)-cfg->f[0x30/4];
                if (CheckGroundBelowPoint(probe,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
                    second=D_L04_001BFAC0.fields[10];
                    if (FastMatrixHelperA(D_L04_001BFAC0.normal[2],vec_length_xy(D_L04_001BFAC0.normal))>=0.5f) {
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
        speed=vec_length_xy(move);
        FastVecScale(test,move,1.0f/speed);
        result=BlendWithScaledCount(cfg->f[4/4],obj,move,cfg->i[0/4],cfg->f[0x30/4],cfg->i[0x38/4]);
        if (result&2) cfg->f[0x18/4]=-0.01f;
        if (result&1) {
            flags|=1;
            if (move[0]*test[0]+move[1]*test[1]<speed*0.2f) flags|=2;
            {
                float ground=ProbeGroundHeightBelow(obj+0x10,0,0.5f);
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
