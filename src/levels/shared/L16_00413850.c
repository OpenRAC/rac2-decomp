#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Quad16 direction;
    int owner,flags;
    u8 kind,active;
    u16 oclass;
    float damage;
    int enabled;
} L16Hit;
extern float g_projectile_hit_normal[4];
extern u8 *g_aim_target_moby;
extern int coll_sweep_from_object(void *,float,float *,int,float,float,int,int,int);
extern void moby_set_state(u8 *,s32,s32);
extern void FastVecScale(void *,void *,float);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int CollLine(void *,void *,int,void *,void *);
extern void FastVecCross(void *,void *,void *);
extern float FastVecDot(void *,void *);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern void multiply_quaternions(void *,void *,void *);
extern void make_hit_descriptor(char *,int,int,float,Quad16 *);
extern int coll_test_point(void *,int,void *,float);
extern int coll_process_hit(void *,int,void *,void *,float);
extern char *SpawnExplosion(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void moby_mark_spawned(void *);
extern void ref_L16_00413850_00(void *);
extern void ref_L16_00413850_01(void (*)(void *),void *);
/* Projectile update: expires after 240 frames, rotates its velocity by a half-angle
 * quaternion built from the surface normal under it, moves and, on a hit, unless the
 * object hit is the one its state records at +0x10, sends a blast request (velocity
 * scaled 1.5, or 3 with no object hit). Both blast branches are written out in full;
 * the compiler's cross-jumping merges their common tails, as in retail. */
/* Updates a homing projectile (moby class 3962): it follows the ground, explodes on a hit and expires after a while. */
void homing_l16_projectile_update(u8 *object)
{
    float destination[4],backward[4],normal[4],quaternion[4],inverse[4],rotated[4],start[4],finish[4];
    L16Hit hit;
    float impact[4];
    L16Hit blast;
    u8 *state=*(u8 **)(object+0x68);
    float savedW,speed,angle;
    *(int *)(state+0x24) += 1;
    if (*(int *)(state+0x24)>240) {
        coll_sweep_from_object(object,0.6f,(float *)(object+0x10),0x10001,*(float *)(state+0x14),0.0f,0,1,0);
        moby_set_state(object,1,-1);
    }
    switch (object[0x20]) {
    case 0: {
        qcopy(backward,object+0xE0);
        FastVecScale(backward,backward,-1.0f);
        savedW=*(float *)(state+0xC);
        *(float *)(state+0xC)=0.0f;
        speed=FastVecLength(state);
        vec_scale_to_length(start,object+0xE0,0.1f);
        vec_scale_to_length(finish,object+0xE0,-3.0f);
        FastVecAdd(start,start,object+0x10);
        FastVecAdd(finish,finish,object+0x10);
        if (CollLine(start,finish,2,object,0)) vec_scale_to_length(normal,g_projectile_hit_normal,1.0f);
        else vec_scale_to_length(normal,object+0xE0,-1.0f);
        FastVecScale(normal,normal,-1.0f);
        vec_scale_to_length(state,state,1.0f);
        FastVecCross(normal,backward,normal);
        angle=-FastVecDot(backward,normal)*0.5f;
        FastVecScale(quaternion,normal,math_fast_sin_or_cos_b(angle));
        quaternion[3]=math_fast_sin_or_cos_a(angle);
        inverse[0]=-quaternion[0];
        inverse[1]=-quaternion[1];
        inverse[2]=-quaternion[2];
        inverse[3]=quaternion[3];
        multiply_quaternions(rotated,quaternion,state);
        multiply_quaternions(state,rotated,inverse);
        vec_scale_to_length(state,state,speed);
        *(float *)(state+0xC)=savedW;
        FastVecScale(normal,normal,-1.0f);
        qcopy(object+0xE0,normal);
        FastVecAdd(destination,object+0x10,state);
        make_hit_descriptor((char *)&hit,(int)object,1,*(float *)(state+0x14),(Quad16 *)state);
        hit.oclass=*(u16 *)(object+0xAA);
        if (CollLine(object+0x10,destination,0,object,&hit) || coll_test_point(object+0x10,0,object,0.3f)) {
            if (g_aim_target_moby) {
                if (g_aim_target_moby != *(u8 **)(state+0x10)) {
                    qcopy(impact,state);
                    FastVecScale(impact,impact,1.5f);
                    impact[2]=1.0f;
                    impact[3]=5627.9248046875f;
                    make_hit_descriptor((char *)&blast,(int)object,0x10001,*(float *)(state+0x14),(Quad16 *)impact);
                    blast.active=1;
                    blast.oclass=*(u16 *)(object+0xAA);
                    blast.kind=0;
                    coll_process_hit(object+0x10,0,object,&blast,0.6f);
                    moby_set_state(object,1,-1);
                    return;
                }
            } else {
                qcopy(impact,state);
                FastVecScale(impact,impact,3.0f);
                impact[2]=1.0f;
                impact[3]=5627.9248046875f;
                make_hit_descriptor((char *)&blast,(int)object,0x10001,*(float *)(state+0x14),(Quad16 *)impact);
                blast.active=1;
                blast.oclass=*(u16 *)(object+0xAA);
                blast.kind=0;
                coll_process_hit(object+0x10,0,object,&blast,0.6f);
                moby_set_state(object,1,-1);
                return;
            }
        }
        qcopy(object+0x10,destination);
        FastVecScale(impact,state,-0.5f);
    break;
    }
    case 1: {
        SpawnExplosion(object+0x10,0,25,20,20,20,45,0,0,0,0,0,0.25f,20.0f);
        moby_mark_spawned(object);
        return;
    }
    }
    ref_L16_00413850_01(ref_L16_00413850_00,object);
}
