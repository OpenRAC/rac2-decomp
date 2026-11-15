/* func_00331800 has its own unit for its jump table and -frac2-hazard-labels,
 * without which it does not match.
 *
 * func_002A7CA0 is void (see 0032EB28-ai-g8.c). With a float declaration the
 * call sets F0, which ends the F12 copy's dependence on the later calls, and
 * sched2 issues that copy after F14/F15, A0 and A1.
 * The arguments interleave by bank; each bank keeps its order. */
#include "common.h"

extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } D_00189E20;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } D_001BAF80;
extern int D_001AD7EC;
extern int D_001A8CA0, D_001A8CA4;
extern void func_00283658(void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_002AD0E0(void *,int,void *,void *,void *,void *);
extern void func_002833F0(void *,void *);
extern int func_002A9640(void *,int,int);
extern void func_003320F0(void *);
extern float func_00283248(float,float);
extern void func_002A9288(void *,float);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern float func_002A7878(float,float);
extern float func_00282E80(void *,void *);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern float func_00283B98(float,float);
extern void func_002A7CA0(float,void *,void *,float,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002A7EA0(void *,void *,void *,float,float,float,float,int);
extern int func_00277258(void *,int,void *,float);
extern void func_002B00B0(void *,void *,int);
extern int func_002761F8(void *,void *,int,void *,int);
extern int func_00278E78(void);
extern float func_002A89A8(void *,int,float);

#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

/* Runs the brain of a simple creature that wanders around, turns toward the player when close and stays on the ground. */
void func_00331800(char *object)
{
    float dest[4] __attribute__((aligned(16)));
    float temp[4] __attribute__((aligned(16)));
    union { float matrix[16]; struct { float vector[4]; float far[4]; float near[4]; } v; } work __attribute__((aligned(16)));
    char *state = *(char **)(object+0x68);
    float r;
    float angle;
    char *position;
    float *saved;
    int hit;

    if (AI_B(object,0x20) && D_001AD7EC) {
        copy_matrix_rotation(work.matrix,object+0xc0);
        GetEulerAnglesFromMatrix(work.matrix,dest);
        TransformPointAndRotationByParent(object,D_001AD7EC,object+0x10,dest,object+0x10,temp);
        euler_rotation_basis(object+0xc0,temp);
        qcopy(object+0xf0,temp);
    }
    if (FindOwnedEffectSlot(object,0x4010000,0)) UpdateExplosionEffectMoby(object);
    FastMatrixHelperA(AI_F(object,0x10)-gHeroState.pos[0],AI_F(object,0x14)-gHeroState.pos[1]);
    QueueGroundShadow(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        SetMobyState(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            r=RandomFloatRange(0,100);
            if (r>=0 && r<20) StartAnimationBlended(object,0,0,10);
            if (r>=20 && r<50) StartAnimationBlended(object,4,0,10);
            if (r>=50 && r<100) StartAnimationBlended(object,1,0,10);
        }
        if (vec_distance_xy(object+0x10,gHeroState.pos)<2 && !D_001A8CA4 && !D_001A8CA0) {
            SetMobyState(object,2,-1);
            StartAnimationBlended(object,2,0,10);
            AI_F(object,0x48)=0.75f;
        }
        if (FastFloatHelperD(state+0x70)) {
            if (D_001A8CA4) return;
            if (!D_001A8CA0) {
                if (RandomIntBelow(2)) {
                    SetMobyState(object,5,-1);
                    AI_I(state,0x70)=RandomIntRange(400,600);
                    StartAnimationBlended(object,2,0,10);
                    AI_F(object,0x48)=0.75f;
                } else {
                    SetMobyState(object,6,-1);
                    AI_I(state,0x70)=RandomIntRange(180,360);
                    StartAnimationBlended(object,3,0,10);
                }
            }
        }
        break;
    case 6:
        if (AI_B(object,0x60)&2) StartAnimationBlended(object,3,0,10);
        if (FastFloatHelperD(state+0x70)) {
            SetMobyState(object,1,-1);
            AI_I(state,0x70)=RandomIntRange(120,600);
            StartAnimationBlended(object,RandomIntBelow(2),0,10);
        }
        break;
    case 5:
        if (AI_B(object,0x60)&2) {
            StartAnimationBlended(object,2,0,10);
            AI_F(object,0x48)=0.75f;
        }
        position=object+0x10;
        if (vec_distance_xy(position,gHeroState.pos)<2) {
            SetMobyState(object,2,-1);
            AI_F(object,0x48)=0.1f;
            StartAnimationBlended(object,2,0,10);
        }
        if (FastFloatHelperD(state+0x70)) {
            SetMobyState(object,1,-1);
            AI_I(state,0x70)=RandomIntRange(400,600);
        }
        angle=FastAddRotations(AI_F(object,0xf8),RandomFloatRange(-30,30)*0.017453294f);
        MobySpringTurn(angle,object,state+0x58,0.00014544412260875106f,0.00043633237f,0.013089972f);
        vec_scale_to_length(temp,object+0xc0,0.004166667f);
        FastVecAdd(dest,position,temp);
        saved=work.matrix;
        qcopy_nc(saved,position);
        if (MoveOverGround(object,position,dest,0.1f,0.7f,0.25f,0.52359885f,2)) {
            if (TestPointAgainstCollision(position,1,object,0.5f) && gCollisionHit.surface) qcopy(position,saved);
        } else {
            angle=FastAddRotations(AI_F(object,0xf8),RandomFloatRange(20,135)*0.017453294f);
            MobySpringTurn(angle,object,state+0x58,4.848137541557662e-05f,0.00043633237f,0.013089972f);
        }
        break;
    case 2:
        position=object+0x10;
        if (vec_distance_xy(position,gHeroState.pos)<2) {
            angle=FastAddRotations(AI_F(object,0xf8),RandomFloatRange(-30,30)*0.017453294f);
            MobySpringTurn(angle,object,state+0x58,0.00014544412260875106f,0.00043633237f,0.013089972f);
            vec_scale_to_length(temp,object+0xc0,0.004166667f);
            FastVecAdd(dest,position,temp);
            saved=work.matrix;
            qcopy_nc(saved,position);
            if (MoveOverGround(object,position,dest,0.5f,0.7f,0.25f,0.52359885f,2)) {
                if (TestPointAgainstCollision(position,1,object,0.5f) && gCollisionHit.surface) qcopy(position,saved);
            } else {
                angle=FastAddRotations(AI_F(object,0xf8),RandomFloatRange(-90,-10)*0.017453294f);
                MobySpringTurn(angle,object,state+0x58,5.81776475883089e-05f,0.00043633237f,0.013089972f);
            }
        } else {
            AI_F(object,0x48)=1;
            SetMobyState(object,1,-1);
        }
        break;
    case 4:
        GetGravityDirectionAtObject(object,work.matrix,0);
        vec_scale_to_length(work.matrix,work.matrix,4);
        FastVecAdd(work.v.far,object+0x10,work.matrix);
        vec_scale_to_length(work.matrix,work.matrix,-1);
        FastVecAdd(work.v.near,object+0x10,work.matrix);
        if (CollLine(work.v.near,work.v.far,0,object,0)) {
            if (gCollisionHit.surface!=gHeroState.surface) qcopy(object+0x10,gCollisionHit.point);
        }
        hit=GetCollHitMaterial();
        if (hit>0 && hit!=10 && !D_001A8CA4) {UpdateExplosionEffectMoby(object);return;}
        SetMobyState(object,0,-1);
        break;
    case 3:
        break;
    }
    if (!D_001A8CA4 && !D_001A8CA0) {
        qcopy(work.matrix,object+0x10);
        work.matrix[2]+=0.5f;
        AI_F(object,0x18)=ProbeGroundHeightBelow(work.matrix,0,0.5f);
    }
}
