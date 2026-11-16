#include "names.h"
/* func_PAL_L04_0033EB40, the PAL copy of func_L04_0033CC00: the same C with the per-frame values
   scale by (60/50)^2: the fall step 0.0025 becomes 0.0036000002f (0x3B6BEDFB) and the -0.01 drop
   speed -0.012. */
#include "common.h"

extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(float *, float *, float);
extern void FastVecSub(float *, float *, float *);
extern void FastVecScale(void *, void *, float);

extern float vec_length_xy(void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float,float);
extern int coll_check_ground_below_point(void *,void *,int,float,float);
extern int math_blend_scaled_count(float,void *,void *,int,float,int);
extern float coll_probe_ground_height_below(void *,int,float);
typedef struct { float fields[16]; float normal[4]; } CollisionResult;
extern CollisionResult g_probe_hit;
typedef union { int q __attribute__((mode(TI))); float f[4]; } CollisionVec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef union { float f[20]; int i[20]; } MovementConfig;
/* Accelerates obj toward target, probes the ground ahead and returns the collision flags. */
int moby_move_toward_target_pal(char *moby,MovementConfig *config,float *target,void *out,float scale)
{
    CollisionVec old;
    float move[4] __attribute__((aligned(16)));
    float test[4] __attribute__((aligned(16)));
    float probe[4] __attribute__((aligned(16)));
    float accel=config->f[0x1C/4]*scale;
    float max_step=config->f[0x24/4]*scale;
    float distance,step,height,first,second,speed;
    int flags=0,result;
    FastVecSub(move,target,(float *)(moby+0x10));
    distance=vec_length_xy(move);
    old.q=((CollisionVec *)(moby+0x10))->q;
    step=accel*distance;
    if (accel<step) step=accel;
    config->f[0x10/4]+=step;
    if (distance<config->f[0x10/4]*10.0f) config->f[0x10/4]-=config->f[0x20/4]*config->f[0x10/4];
    if (max_step<config->f[0x10/4]) config->f[0x10/4]=max_step;
    else if (config->f[0x10/4]<-max_step) config->f[0x10/4]=-max_step;
    if (config->i[0x38/4]&4) {
        move[0]=math_fast_sin_or_cos_a(config->f[0x4C/4])*config->f[0x10/4];
        move[1]=math_fast_sin_or_cos_b(config->f[0x4C/4])*config->f[0x10/4];
    } else {
        move[0]=math_fast_sin_or_cos_a(F(moby,0xF8))*config->f[0x10/4];
        move[1]=math_fast_sin_or_cos_b(F(moby,0xF8))*config->f[0x10/4];
    }
    if (config->i[0x38/4]&1) move[2]=0;
    else { move[2]=config->f[0x18/4]; config->f[0x18/4]-=0.0036000002f; }
    height=F(moby,0x18)+0.04f;
    FastVecAdd(test,moby+0x10,move);
    test[2]=F(moby,0x18)-config->f[0x30/4];
    if (coll_check_ground_below_point(test,moby,config->i[0x38/4]&0x20,config->f[8/4],config->f[12/4])) {
        step=mat_fast_helper_a(g_probe_hit.normal[2],vec_length_xy(g_probe_hit.normal));
        first=g_probe_hit.fields[10];
        if (step>0.5f) {
            if (vec_length_xy(move)>0.1f) {
                vec_scale_to_length(probe,move,0.57f);
                FastVecAdd(probe,probe,moby+0x10);
                probe[2]=F(moby,0x18)-config->f[0x30/4];
                if (coll_check_ground_below_point(probe,moby,config->i[0x38/4]&0x20,config->f[8/4],config->f[12/4])) {
                    second=g_probe_hit.fields[10];
                    if (mat_fast_helper_a(g_probe_hit.normal[2],vec_length_xy(g_probe_hit.normal))>=0.5f) {
                        flags=0x22;
                        if ((config->i[0x38/4]&8) && second<height && first<height) flags=8;
                    }
                } else {
                    flags=0x22;
                    if ((config->i[0x38/4]&8) && first<height) flags=8;
                }
            }
        }
    } else {
        flags=0x22;
        if (config->i[0x38/4]&8) flags=8;
    }
    if (!(flags&2)) {
        speed=vec_length_xy(move);
        FastVecScale(test,move,1.0f/speed);
        result=math_blend_scaled_count(config->f[4/4],moby,move,config->i[0/4],config->f[0x30/4],config->i[0x38/4]);
        if (result&2) config->f[0x18/4]=-0.012f;
        if (result&1) {
            flags|=1;
            if (move[0]*test[0]+move[1]*test[1]<speed*0.2f) flags|=2;
            {
                float ground=coll_probe_ground_height_below(moby+0x10,0,0.5f);
                float old_height=old.f[2];
                if (config->f[8/4]<old_height-ground || config->f[12/4]<ground-old_height) {
                    flags|=0x22;
                    ((CollisionVec *)(moby+0x10))->q=old.q;
                }
            }
        }
        qcopy(out,move);
    } else if ((config->i[0x38/4]^1)&1) config->f[0x18/4]=-0.012f;
    if (distance<config->f[0x2C/4]) flags|=4;
    return flags;
}
