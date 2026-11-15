#include "common.h"
typedef int MotionQuad __attribute__((mode(TI)));

extern void cam_compute_view_direction(void *, void *, int);
extern void mat_align_to_down_dir(void *, void *, int);
extern float coll_get_ground_distance_below(void *, int, int);
extern float FastVecDot(void *, void *);
extern void gravity_offset_object_position(void *, void *, void *, float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern f32 ApproachValue(void *, float, float);
extern float gravity_get_center_distance(void *);
extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern int math_solve_quadratic(void *, void *, float, float, float);
extern int CollLine(void *, void *, int, void *, int);
extern int GetCollHitMaterial(void);
extern char *moby_get_private_value_0(void *);
extern void part_start_effect_default_table(void *, int, int, void *, float);
extern void vec_decode_byte_color(void *, void *);
extern float vec_get_heading_angle(void *, void *, int);
extern float math_approach_target_with_direction_mode(void *, void *, int, float, float, float, float);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern int coll_sweep_from_object(void *, float, void *, int, float, float, int, int, int);
extern int coll_test_point(void *, float, int, void *);
struct ImpactQueueState { char pad[20]; int index; int hit; int flags; MotionQuad point, offset, normal; };
extern struct ImpactQueueState g_collision_hit;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
/* Steps motion under a position-dependent gravity direction and answers collisions; returns motion flags. */
/* Steps motion under a position-dependent gravity direction and answers collisions; returns motion flags. */
int moby_update_positional_gravity_motion(char *object, char *state)
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
    MotionQuad *hitPoint=&g_collision_hit.point;
    cam_compute_view_direction(object+0x10, direction, 0);
    mat_align_to_down_dir(object+0xC0, direction, 0);
    length = coll_get_ground_distance_below(object+0x10, 0, 0);
    approach = -FastVecDot(state+0x80, direction);
    if (B(state,0x1A)==0) {
        gravity_offset_object_position(object,state+0x80,state+0x80,F(state,0x4C));
        acceleration = F(state,0x4C)*FastVecLength(direction);
    } else {
        gravity_offset_object_position(object,state+0x80,state+0x80,F(state,0x50));
        acceleration = F(state,0x50)*FastVecLength(direction);
    }
    qcopy(oldPosition,object+0x10);
    gravity_offset_object_position(object,oldPosition,oldPosition,-F(state,0x34));
    vec_scale_to_length(scaled,direction,-approach);
    FastVecSub(state+0x80,state+0x80,scaled);
    speed = FastVecLength(state+0x80);
    { float target=0.033333335f;
      if (B(state,0x1A)>=2) target=0.0f;
      ApproachValue(&speed,target,F(state,0x2C));
    }
    vec_scale_to_length(state+0x80,state+0x80,speed);
    FastVecAdd(state+0x80,state+0x80,scaled);
    if (F(object,0x10)<2.0f || F(object,0x10)>1021.0f ||
        F(object,0x14)<2.0f || F(object,0x14)>1021.0f ||
        F(object,0x18)<2.0f || F(object,0x18)>1021.0f) result=1;
    if (B(state,0x1A)!=0 && gravity_get_center_distance(object+0x10)<F(state,0x40)) result |= 1;
    if (F(state,0x60)!=-1.0f && F(state,0x54)!=-1.0f) {
        switch (B(state,0x1A)) {
        case 0:
            flightTime = math_fabs(approach / acceleration);
            if (flightTime>2.0f) {
                float numerator=(F(state,0x54)-moby_get_anim_value(object))*2.0f;
                float target = numerator / flightTime;
                if (target>0.0f) ApproachValue(object+0x48,target,0.1f);
            }
            break;
        case 1:
            if (moby_get_anim_value(object)>=F(state,0x60)) F(object,0x48)=0.0f;
            else {
                float a=acceleration*-0.5f;
                acceleration=60.0f;
                if (math_solve_quadratic(&root1,&root2,a,approach-a,length)>0 && root1>0.0f && root1<acceleration) acceleration=root1;
                if (acceleration<0.0001f) acceleration=0.0001f;
                {
                    float numerator=(F(state,0x60)-moby_get_anim_value(object))*2.0f;
                    float target = numerator / acceleration;
                    if (target>2.0f) target=2.0f;
                    else if (target<0.0f) target=0.0f;
                    ApproachValue(object+0x48,target,0.1f);
                }
            }
            break;
        case 2:
            F(object,0x48)=1.0f;
            vec_scale_to_length(start,direction,-0.2f);
            FastVecAdd(start,start,object+0x10);
            vec_scale_to_length(normal,direction,1.0f);
            FastVecAdd(normal,normal,object+0x10);
            if (!CollLine(start,normal,2,object,0)) B(state,0x1A)=1;
            else if (GetCollHitMaterial()==1) {
                hit=moby_get_private_value_0(object);
                if (hit) {
                    FastVecAdd(temp,object+0xC0,object+0x10);
                    part_start_effect_default_table(object,0,0x110000,temp,(float)*(short *)(hit+4));
                }
            }
            break;
        }
    }
    vec_decode_byte_color(start,state+0x64);
    angle=vec_get_heading_angle(object,start,0);
    damped=0.0f;
    math_approach_target_with_direction_mode(&damped,state+0x68,0,angle,0.013962636f,0.003490659f,3.14159274f);
    qzero_nc(normal);
    normal[2]=F(state,0x68);
    euler_rotation_basis(scratch.rotation,normal);
    multiply_matrix3x3(object+0xC0,object+0xC0,scratch.rotation);
    FastVecAdd(object+0x10,object+0x10,state+0x80);
    FastVecAdd(predicted,oldPosition,state+0x80);
    FastVecAdd(start,predicted,state+0x80);
    coll_sweep_from_object(object,F(state,0x30),start,0x4000000,1.0f,1.0f,0,1,0);
    if (FastVecLength(state+0x80)>F(state,0x30)) {
        if (CollLine(oldPosition,predicted,0x24,object,0)) qcopy(predicted,hitPoint);
    }
    rayHit=coll_test_point(predicted,F(state,0x30),0x24,object);
    fallback=0;
    if (!rayHit) {
        rayHit=CollLine(predicted,object+0x10,0x24,object,0);
        fallback=1;
        if (!rayHit) goto finish;
    }
    result |= 4;
    if (fallback) qcopy(object+0x10,hitPoint);
    else {
        qcopy(object+0x10,&g_collision_hit.offset);
        vec_scale_to_length(temp,direction,F(state,0x34));
        FastVecAdd(object+0x10,object+0x10,temp);
    }
    acceleration=1.0f;
    vec_scale_to_length(normal,&g_collision_hit.normal,acceleration);
    if (FastVecDot(normal,direction)<=-0.707f) {
        float projection=FastVecDot(state+0x80,normal);
        if (projection<0.0f) {
            if (g_collision_hit.hit==0 || g_collision_hit.flags>0) {
                vec_scale_to_length(scratch.collision.probeStart,object+0xE0,0.2f);
                vec_scale_to_length(scratch.collision.probeEnd,object+0xE0,-2.0f);
                FastVecAdd(scratch.collision.probeStart,scratch.collision.probeStart,object+0x10);
                FastVecAdd(scratch.collision.probeEnd,scratch.collision.probeEnd,object+0x10);
                if (CollLine(scratch.collision.probeStart,scratch.collision.probeEnd,2,object,0)) B(state,0x1A)=2;
            }
            vec_scale_to_length(scratch.collision.impulse,normal,projection);
            FastVecSub(state+0x80,state+0x80,scratch.collision.impulse);
            if (B(state,0x1A)==2) {
                float value=FastVecLength(state+0x80);
                ApproachValue(&value,0.0f,F(state,0x50));
                vec_scale_to_length(state+0x80,state+0x80,value);
            }
        }
    } else {
        float dot=FastVecDot(state+0x80,normal);
        if (dot<0.0f) {
            dot = dot*-(F(state,0x3C)+acceleration);
            vec_scale_to_length(scratch.collision.impulse,normal,dot);
            FastVecAdd(state+0x80,state+0x80,scratch.collision.impulse);
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
#undef F
#undef B
#undef H
