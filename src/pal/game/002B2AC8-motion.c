#include "include_asm.h"

#include "common.h"
extern float vec_length_xy(void *);
extern void ApproachValue(float *,float,float);
extern void vec_fast_normalize_helper(void *,void *,float);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern float FastVecDot(void *,void *);
extern float FastVecLength(void *);
extern float coll_probe_ground_height_below(void *,float,int);
extern int GetCollHitMaterial(void);
extern float coll_get_ground_height_under_object(void *);
extern float math_fabs(float);
extern float moby_get_anim_value(void *);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int math_solve_quadratic(float *,float *,float,float,float);
extern int CollLine(void *,void *,int,void *,int);
extern float math_approach_target_with_direction_mode(void *,void *,int,float,float,float,float);
extern int coll_sweep_from_object(void *,float,void *,int,float,float,int,int,int);
extern int coll_test_point(void *,float,int,void *);
extern char *moby_get_private_value_0(void *);
extern void part_start_effect_default_table(void *,int,int,void *,float);
extern void path_push_point_away(int,void *,void *,float);
extern void euler_rotation_basis(void *,void *);
extern void multiply_matrix3x3(void *,void *,void *);
extern float FastAddRotations(float,float);
typedef int MotionQuad __attribute__((mode(TI)));
struct ImpactQueueState { char pad[20]; int index; int hit; int flags; MotionQuad point, offset, normal; };
extern struct ImpactQueueState g_collision_hit;
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

    speed=vec_length_xy((state+0x80));
    { float target=0.020000001f;
      if (BU(state,0x1a)>=2) target=0.0f;
      ApproachValue(&speed,target,BF(state,0x2c));
    }

    vec_fast_normalize_helper((state+0x80),(state+0x80),speed);
    vec_clear_128(offset);
    offset[2]=BF(state,0x34);
    matrix_mul_vec3(offset,offset,(object+0xc0));
    FastVecAdd(original,offset,(object+0x10));
    ground=coll_probe_ground_height_below(original,0.5f,0);
    if (!GetCollHitMaterial()) {
        if (!BU(state,0x1b) && ground<=original[2] && original[2]+BF(state,0x88)<ground) BU(state,0x1b)=1;
        ground=coll_get_ground_height_under_object((object+0x10));
    }
    if (BU(state,0x1b)) {
        if (BU(state,0x1b)<4) FastVecScale((state+0x80),(state+0x80),0.7f);
        if (BU(state,0x1b)<7) { BU(state,0x1b)++; BF(state,0x50)*=0.75f; }
    }
    if (BF(object,0x10)<2.0f || 1021.0f<BF(object,0x10) || BF(object,0x14)<2.0f || 1021.0f<BF(object,0x14) || BF(object,0x18)<2.0f || 1021.0f<BF(object,0x18)) flags=1;
    if (BU(state,0x1a) && BF(object,0x18)<BF(state,0x40)) flags|=1;
    else if (BU(object,0x43)!=BU(state,0x15) && BF(state,0x60)!=-1.0f && BF(state,0x54)!=-1.0f) {
        switch (BU(state,0x1a)) {
        case 0: {
            float flightTime, numerator;
            flightTime=math_fabs(BF(state,0x88)/BF(state,0x4c));
            if (2.0f<flightTime) {
                distance=moby_get_anim_value(object);
                numerator=BF(state,0x54)-distance;
                numerator=numerator+numerator;
                accel=numerator/flightTime;
                if (0.0f<accel) ApproachValue((float *)(object+0x48),accel,0.24000001f);
            }
            break;
        }
        case 1:
            if (BF(state,0x60)<=moby_get_anim_value(object)) { BF(object,0x48)=0; break; }
            else if (BU(state,0x15)!=255 && (ground==0.0f || ground<BF(state,0x40) || 10.0f<BF(object,0x18)-ground)) {
                if (BU(object,0x43)!=BU(state,0x15)) func_PAL_002A7E68(object,BU(state,0x15),0,4);
                if (0.006f<BF(state,0x50)) BF(state,0x50)=0.006f;
                break;
            }
            {
                float numerator;
                float halfGravity=BF(state,0x50)*-0.5f;
                t=60.0f;
                if (math_solve_quadratic(&root1,&root2,halfGravity,BF(state,0x88)-halfGravity,BF(object,0x18)-ground)>0 && 0.0f<root1 && root1<t) t=root1;
                if (t<0.0001f) t=0.0001f;
                distance=moby_get_anim_value(object);
                numerator=BF(state,0x60)-distance;
                numerator=numerator+numerator;
                accel=numerator/t;
                if (2.0f<accel) accel=2.0f;
                else if (accel<0.0f) accel=0.0f;
                ApproachValue((float *)(object+0x48),accel,0.24000001f);
            }
            break;
        case 2:
            BF(object,0x48)=1.0f;
            qcopy(start,(object+0x10)); start[2]+=0.2f;
            qcopy(scratch.collision.normal,(object+0x10)); scratch.collision.normal[2]-=1.0f;
            if (!CollLine(start,scratch.collision.normal,2,object,0)) BU(state,0x1a)=1;
            break;
        }
    }
    math_approach_target_with_direction_mode(object+0xf8,state+0x68,0,BF(state,0x64),0.020106196f,0.005026549f,3.140000104904175f);
    FastVecAdd((object+0x10),(object+0x10),(state+0x80));
    FastVecAdd(destination,original,(state+0x80));
    FastVecScale(start,(state+0x80),3.0f);
    FastVecAdd(start,start,destination);
    coll_sweep_from_object(object,BF(state,0x30),start,0x4000000,1.0f,1.0f,0,1,0);
    if (BF(state,0x30)<FastVecLength((state+0x80))) {
        if (CollLine(original,destination,0x24,object,0)) qcopy(destination,&g_collision_hit.point);
    }
    fallback=0;
    if (!coll_test_point(destination,BF(state,0x30),0x24,object)) {
        int hit=CollLine(destination,(object+0x10),0x24,object,0);
        fallback=1;
        if (!hit) goto finish;
    }
    flags|=4;
    if (fallback) qcopy((object+0x10),&g_collision_hit.point);
    else FastVecSub((object+0x10),&g_collision_hit.offset,offset);
    response=1.0f;
    vec_scale_to_length(scratch.collision.normal,&g_collision_hit.normal,response);
    if (0.7070000171661377f<=scratch.collision.normal[2]) {
        float projection=FastVecDot((state+0x80),scratch.collision.normal);
        if (projection<0.0f) {
            if (!g_collision_hit.hit || g_collision_hit.flags>0) {
                qcopy(scratch.collision.rayStart,(object+0x10)); scratch.collision.rayStart[2]+=0.2f;
                qcopy(rayEnd,(object+0x10)); rayEnd[2]-=2.0f;
                if (CollLine(scratch.collision.rayStart,rayEnd,2,object,0)) {
                    BU(state,0x1a)=2;
                    if (GetCollHitMaterial()==1) {
                        record=moby_get_private_value_0(object);
                        if (record) {
                            FastVecAdd(impact,(object+0xc0),(object+0x10));
                            part_start_effect_default_table(object,0,0x110000,impact,(float)*(short *)(record+4));
                        }
                    }
                }
            }
            vec_scale_to_length(scratch.collision.work,scratch.collision.normal,projection);
            FastVecSub((state+0x80),(state+0x80),scratch.collision.work);
            if (BU(state,0x1a)==2) {
                if (g_collision_hit.hit && g_collision_hit.flags<0) flags|=BH(state,0x38)&1;
                length=FastVecLength((state+0x80));
                ApproachValue(&length,0.0f,BF(state,0x50));
                vec_scale_to_length((state+0x80),(state+0x80),length);
            }
        }
    } else {
        float dot=FastVecDot((state+0x80),scratch.collision.normal);
        if (dot<0.0f) {
            dot=dot*-(BF(state,0x3c)+response);
            vec_scale_to_length(scratch.collision.work,scratch.collision.normal,dot);
            FastVecAdd((state+0x80),(state+0x80),scratch.collision.work);
        }
    }
finish:
    if (BI(state,0x7c)!=-1) path_push_point_away(BI(state,0x7c),(object+0x10),(object+0x10),BF(state,0x30));
    if (!BU(state,0x1a) && BF(state,0x88)<0.0f) BU(state,0x1a)=1;
    else if (BH(state,0x38)&2) {
        if (flags&4) { if (BF(state,0x88)<=0.0f) flags|=1; }
        if (BH(object,0x34)&0x100) {
            euler_rotation_basis(scratch.rotation,state+0x90);
            multiply_matrix3x3((object+0xc0),(object+0xc0),scratch.rotation);
        } else {
            BF(object,0xf0)=FastAddRotations(BF(object,0xf0),BF(state,0x90));
            BF(object,0xf4)=FastAddRotations(BF(object,0xf4),BF(state,0x94));
            BF(object,0xf8)=FastAddRotations(BF(object,0xf8),BF(state,0x98));
            euler_rotation_basis((object+0xc0),object+0xf0);
        }
        vec_clear_128(scratch.collision.normal); scratch.collision.normal[2]=BF(state,0x34);
        matrix_mul_vec3(scratch.collision.normal,scratch.collision.normal,(object+0xc0));
        FastVecSub(scratch.collision.work,offset,scratch.collision.normal);
        FastVecAdd((object+0x10),(object+0x10),scratch.collision.work);
    } else {
        if (((BU(object,0x60)&2) && BU(object,0x43)!=BU(state,0x15)) || (BU(state,0x1a)==2 && BU(object,0x43)==BU(state,0x15))) {
            if (BH(state,0x38)&1) flags|=3;
            else flags|=2;
        }
    }
    return flags;
}
