#include "common.h"

extern void FastVecAdd(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecSub(float *, float *, float *);
extern float FastVecDot(void *, void *);
extern void FastVecScale(void *, void *, float);

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

extern Hero g_hero_state;
extern void UpdateHeroAttachment(int, void *, void *);
extern float cam_get_view_space_vector_length(void *);
extern float cam_get_view_space_height(void *);
extern void cam_set_view_space_vector_length(void *, void *, float);
extern void cam_set_view_space_height(void *, void *, float);
extern void cam_project_vector_onto_view_plane(void *, void *);
extern void vec_clear_128(void *);
extern void hero_resolve_collision_with_rewind(void);
extern void Hero_ProbeGround(void);
extern void EaseHeroPositionToGoal(void);
extern float hero_get_speed_along_forward(void *);

/* Moves the hero by its velocity, impulse and surface motion, then measures the
   resolved displacement and the speeds derived from it. */
void ApplyHeroVelocityAndResolveDisplacement(void) {
    float old[4];
    float horizontal[4];
    float flat[4];

    qcopy(old, g_hero_state.position);
    UpdateHeroAttachment(g_hero_state.collision_mode, g_hero_state.surface_motion,
                      g_hero_state.rotation);
    if (g_hero_state.state == 0x14 || g_hero_state.state == 0x5B ||
        g_hero_state.state == 0x58 || g_hero_state.state == 0x81) {
        if (g_hero_state.air_frames == 0) {
            if (cam_get_view_space_vector_length(g_hero_state.velocity) > g_hero_state.speed_limit - 0.02f) {
                cam_set_view_space_vector_length(g_hero_state.velocity, g_hero_state.velocity,
                                  g_hero_state.speed_limit - 0.02f);
            }
        }
        if (cam_get_view_space_height(g_hero_state.velocity) < -g_hero_state.fall_speed_limit) {
            float fall = -g_hero_state.fall_speed_limit - 0.02f;

            if (fall > 0.0f)
                fall = 0.0f;
            cam_set_view_space_height(g_hero_state.velocity, g_hero_state.velocity, fall);
        }
    } else if (g_hero_state.control_mode != 13) {
        if (g_hero_state.control_mode != 14) {
            if (g_hero_state.air_frames == 0) {
                if (FastVecLength(g_hero_state.velocity) > g_hero_state.speed_limit - 0.02f) {
                    vec_scale_to_length(g_hero_state.velocity, g_hero_state.velocity,
                                  g_hero_state.speed_limit - 0.02f);
                }
            }
        }
    }
    FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.velocity);
    FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.move_impulse);
    vec_clear_128(g_hero_state.move_impulse);
    g_hero_state.collision_flag = 0;
    g_hero_state.collision_id = 0;
    if (FastVecLength(g_hero_state.surface_motion) <= 0.0001f) {
        hero_resolve_collision_with_rewind();
        Hero_ProbeGround();
        FastVecSub(g_hero_state.displacement, g_hero_state.position, old);
        EaseHeroPositionToGoal();
    } else {
        Hero_ProbeGround();
    }

    /* the move actually made, projected on the velocity in three variants */
    FastVecSub(g_hero_state.resolved_velocity, g_hero_state.position, old);
    qcopy(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity);
    qcopy(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity);
    vec_scale_to_length(g_hero_state.resolved_velocity, g_hero_state.resolved_velocity, 1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity, g_hero_state.velocity);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity, g_hero_state.velocity, dot);
    }
    qcopy(horizontal, g_hero_state.velocity);
    cam_project_vector_onto_view_plane(horizontal, horizontal);
    cam_project_vector_onto_view_plane(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity_planar);
    vec_scale_to_length(g_hero_state.resolved_velocity_planar, g_hero_state.resolved_velocity_planar,
                  1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity_planar, horizontal);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity_planar, horizontal, dot);
    }
    qcopy(flat, g_hero_state.velocity);
    cam_set_view_space_vector_length(flat, flat, 0.0f);
    cam_set_view_space_vector_length(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity_xy, 0.0f);
    vec_scale_to_length(g_hero_state.resolved_velocity_xy, g_hero_state.resolved_velocity_xy, 1.0f);
    {
        float dot = FastVecDot(g_hero_state.resolved_velocity_xy, flat);

        if (dot < 0.0f)
            dot = 0.0f;
        vec_scale_to_length(g_hero_state.resolved_velocity_xy, flat, dot);
    }

    g_hero_state.speed = FastVecLength(g_hero_state.resolved_velocity);
    g_hero_state.planar_speed = cam_get_view_space_vector_length(g_hero_state.resolved_velocity);
    *(MovementQuadword *)horizontal = *(MovementQuadword *)g_hero_state.resolved_velocity;
    g_hero_state.forward_speed = hero_get_speed_along_forward(horizontal);
    g_hero_state.vertical_speed = cam_get_view_space_height(g_hero_state.resolved_velocity);
    if (g_hero_state.forward_speed < 0.0f)
        g_hero_state.forward_speed = 0.0f;

    /* the part of the move caused by the surface the hero stands on */
    qcopy(horizontal, g_hero_state.position);
    if (FastVecLength(g_hero_state.surface_motion) > 0.0001f) {
        float w;

        FastVecAdd(g_hero_state.position, g_hero_state.position, g_hero_state.surface_motion);
        w = g_hero_state.surface_motion[3];
        vec_clear_128(g_hero_state.surface_motion);
        g_hero_state.surface_motion[3] = w;
        hero_resolve_collision_with_rewind();
        Hero_ProbeGround();
        FastVecSub(g_hero_state.displacement, g_hero_state.position, old);
        EaseHeroPositionToGoal();
    }
    FastVecSub(g_hero_state.surface_displacement, g_hero_state.position, horizontal);
    g_hero_state.surface_speed = FastVecLength(g_hero_state.surface_displacement);
    g_hero_state.surface_displacement[3] = g_hero_state.surface_motion[3];
    g_hero_state.surface_motion[3] = 0.0f;
    FastVecSub(g_hero_state.displacement, g_hero_state.position, old);

    g_hero_state.slope = 0.0f;
    if (g_hero_state.planar_speed > 0.004f) {
        g_hero_state.slope = g_hero_state.displacement[2] / g_hero_state.planar_speed;
        if (g_hero_state.slope > 0.5f)
            g_hero_state.slope = 0.5f;
        else if (g_hero_state.slope < -0.5f)
            g_hero_state.slope = -0.5f;
    }
    if (g_hero_state.speed > 0.8666667342185974f) {
        FastVecScale(g_hero_state.displacement, g_hero_state.displacement,
                      0.8666667342185974f / g_hero_state.speed);
        g_hero_state.speed = 0.8666667342185974f;
    }
}

extern float vec_length_xy(void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float,float);
extern int coll_check_ground_below_point(void *,void *,int,float,float);
extern int math_blend_scaled_count(float,void *,void *,int,float,int);
extern float coll_probe_ground_height_below(void *,int,float);
typedef struct { float fields[16]; float normal[4]; } CollisionResult;
extern CollisionResult D_L04_001BFAC0;
typedef union { int q __attribute__((mode(TI))); float f[4]; } CollisionVec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef union { float f[20]; int i[20]; } MovementConfig;
/* Accelerates obj toward target, probes the ground ahead and returns the collision flags. */
int moby_move_toward_target(char *obj,MovementConfig *cfg,float *target,void *out,float scale)
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
        move[0]=math_fast_sin_or_cos_a(cfg->f[0x4C/4])*cfg->f[0x10/4];
        move[1]=math_fast_sin_or_cos_b(cfg->f[0x4C/4])*cfg->f[0x10/4];
    } else {
        move[0]=math_fast_sin_or_cos_a(F(obj,0xF8))*cfg->f[0x10/4];
        move[1]=math_fast_sin_or_cos_b(F(obj,0xF8))*cfg->f[0x10/4];
    }
    if (cfg->i[0x38/4]&1) move[2]=0;
    else { move[2]=cfg->f[0x18/4]; cfg->f[0x18/4]-=0.0025f; }
    height=F(obj,0x18)+0.04f;
    FastVecAdd(test,obj+0x10,move);
    test[2]=F(obj,0x18)-cfg->f[0x30/4];
    if (coll_check_ground_below_point(test,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
        step=mat_fast_helper_a(D_L04_001BFAC0.normal[2],vec_length_xy(D_L04_001BFAC0.normal));
        first=D_L04_001BFAC0.fields[10];
        if (step>0.5f) {
            if (vec_length_xy(move)>0.1f) {
                vec_scale_to_length(probe,move,0.57f);
                FastVecAdd(probe,probe,obj+0x10);
                probe[2]=F(obj,0x18)-cfg->f[0x30/4];
                if (coll_check_ground_below_point(probe,obj,cfg->i[0x38/4]&0x20,cfg->f[8/4],cfg->f[12/4])) {
                    second=D_L04_001BFAC0.fields[10];
                    if (mat_fast_helper_a(D_L04_001BFAC0.normal[2],vec_length_xy(D_L04_001BFAC0.normal))>=0.5f) {
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
        result=math_blend_scaled_count(cfg->f[4/4],obj,move,cfg->i[0/4],cfg->f[0x30/4],cfg->i[0x38/4]);
        if (result&2) cfg->f[0x18/4]=-0.01f;
        if (result&1) {
            flags|=1;
            if (move[0]*test[0]+move[1]*test[1]<speed*0.2f) flags|=2;
            {
                float ground=coll_probe_ground_height_below(obj+0x10,0,0.5f);
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
