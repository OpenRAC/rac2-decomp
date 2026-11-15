/* func_00332658 has its own unit for -frac2-hazard-labels: three FP branches
 * target the hazard nop after their compare (+0x198, +0x1E0, +0x228).
 *
 * func_002A7CA0 is void here. Its F0 is the scratch left by its last call: no
 * direct caller, or caller of a function that returns with it live, reads F0 in
 * any retail program (334 call sites, USA), and its definition and wrapper
 * func_002A7E08 compile to the same code either way. The float declaration
 * changes this caller: the call then sets F0, which ends the F12 copy's
 * dependence on the two later calls, and sched2 issues that copy after F14/F15.
 * The arguments interleave by bank; each bank keeps its order. */
#include "common.h"

extern struct { char pad[0x80]; float pos[4]; char gap[0x2200]; int surface; } D_00189E20;
extern int D_001AD7EC;
extern int D_001A8CA0, D_001A8CA4;
extern struct { char pad[0x18]; int surface; int gap; float point[4]; } D_001BAF80;
extern void func_00283658(void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_002AD0E0(void *, int, void *, void *, void *, void *);
extern void func_002833F0(void *, void *);
extern int func_002A9640(void *, int, int);
extern void func_00333048(void *);
extern float func_00283248(float, float);
extern void func_002A9288(void *, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
extern float func_002A7878(float, float);
extern void *func_002AF460(void *, float, float, float, float);
extern float func_00282E80(void *, void *);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern int func_002A7820(int, int);
extern void func_002A7CA0(float, void *, void *, float, float, float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A7EA0(void *, void *, void *, float, float, float, float, int);
extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern void func_002B00B0(void *, void *, int);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_002A89A8(void *, int, float);

typedef int AI_Quad __attribute__((mode(TI)));

#define AI_F(p,n) (*(float *)((char *)(p)+(n)))
#define AI_I(p,n) (*(int *)((char *)(p)+(n)))
#define AI_P(p,n) (*(char **)((char *)(p)+(n)))
#define AI_B(p,n) (*(unsigned char *)((char *)(p)+(n)))

/* Runs the brain of a small creature that walks, picks a target to chase and attacks up close. It keeps the creature standing on the ground. */
void func_00332658(char *object)
{
    float end[4], offset[4], scratch[4], front[4], back[4], matrix[4];
    char *state = AI_P(object, 0x68);
    char *target;
    char *position;
    float angle, choice;
    int hit;
    if (AI_B(object,0x20) && D_001AD7EC) {
        copy_matrix_rotation(scratch,object+0xC0);
        GetEulerAnglesFromMatrix(scratch,end);
        TransformPointAndRotationByParent(object,D_001AD7EC,object+0x10,end,object+0x10,offset);
        euler_rotation_basis(object+0xC0,offset);
        qcopy(object+0xF0,offset);
    }
    if (FindOwnedEffectSlot(object,0x4010000,0)) ExplodeAndHurtNearbyMobys(object);
    AI_I(state,0x78)++;
    angle=FastMatrixHelperA(AI_F(object,0x10)-gHeroState.pos[0],AI_F(object,0x14)-gHeroState.pos[1]);
    QueueGroundShadow(object,0.5f);
    switch (AI_B(object,0x20)) {
    case 0:
        SetMobyState(object,1,-1);
        break;
    case 1:
        if (AI_B(object,0x60)&2) {
            choice=RandomFloatRange(0.0f,100.0f);
            if (choice>=0.0f && choice<25.0f) StartAnimationBlended(object,0,0,10);
            if (choice>=25.0f && choice<50.0f) StartAnimationBlended(object,4,0,10);
            if (choice>=50.0f && choice<75.0f) StartAnimationBlended(object,1,0,10);
            if (choice>=75.0f && choice<100.0f && !D_001A8CA4 && !D_001A8CA0) {
                *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
                AI_P(state,0x7C)=FindBestTargetByReach(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
                if (AI_P(state,0x7C)) {
                    SetMobyState(object,8,-1);
                    StartAnimationBlended(object,5,0,1);
                    AI_F(object,0x48)=1.7f;
                }
            }
        }
        if (vec_distance_xy(object+0x10,gHeroState.pos)<2.0f && !D_001A8CA4 && !D_001A8CA0) {
            SetMobyState(object,2,-1);
            StartAnimationBlended(object,5,0,1);
            AI_F(object,0x48)=1.7f;
        }
        if (FastFloatHelperD(state+0x70)) {
            if (D_001A8CA4) return;
            if (!D_001A8CA0) {
                if (RandomIntBelow(2)) {
                    SetMobyState(object,5,-1);
                    AI_I(state,0x70)=RandomIntRange(400,600);
                    StartAnimationBlended(object,2,0,10);
                } else {
                    SetMobyState(object,6,-1);
                    AI_I(state,0x70)=RandomIntRange(180,360);
                    StartAnimationBlended(object,3,0,10);
                }
            }
        }
        break;
    case 8:
        target=AI_P(state,0x7C);
        choice=FastMatrixHelperA(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
        MobySpringTurn(choice,object,state+0x58,0.00021816618391312659f,0.00043633236782625318f,0.017453296110033989f);
        vec_scale_to_length(offset,object+0xC0,1.0f/24.0f);
        FastVecAdd(end,object+0x10,offset);
        if (!MoveOverGround(object,object+0x10,end,0.5f,0.6f,0.25f,0.52359885f,0)) ExplodeAndHurtNearbyMobys(object);
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
        if (AI_B(object,0x60)&2) StartAnimationBlended(object,2,0,2);
        if (vec_distance_xy(object+0x10,gHeroState.pos)<2.0f) {
            SetMobyState(object,2,-1);
            StartAnimationBlended(object,5,0,1);
        }
        if (FastFloatHelperD(state+0x70)) {
            SetMobyState(object,1,-1);
            AI_I(state,0x70)=RandomIntRange(400,600);
        }
        MobySpringTurn(FastAddRotations(AI_F(object,0xF8),RandomFloatRange(-30.0f,30.0f)*0.01745329424738884f),object,state+0x58,0.00014544412260875106f,0.00043633236782625318f,0.013089972f);
        vec_scale_to_length(offset,object+0xC0,1.0f/240.0f);
        FastVecAdd(end,object+0x10,offset);
        if (!MoveOverGround(object,object+0x10,end,0.1f,0.5f,0.25f,0.52359885f,0)) {
            MobySpringTurn(FastAddRotations(AI_F(object,0xF8),RandomFloatRange(20.0f,135.0f)*0.01745329424738884f),object,state+0x58,0.000048481375415576622f,0.00043633236782625318f,0.013089972f);
        }
        break;
    case 2:
        position=object+0x10;
        *(AI_Quad *)scratch=*(AI_Quad *)(object+0x10);
        AI_P(state,0x7C)=FindBestTargetByReach(scratch,1.5707964897155762f,999.0f,-1.0f,-1.0f);
        target=AI_P(state,0x7C);
        if (target) {
            choice=FastMatrixHelperA(AI_F(target,0x10)-AI_F(object,0x10),AI_F(target,0x14)-AI_F(object,0x14));
            MobySpringTurn(choice,object,state+0x58,0.00021816618391312659f,0.00043633236782625318f,0.017453296110033989f);
            vec_scale_to_length(offset,object+0xC0,1.0f/24.0f);
            FastVecAdd(end,position,offset);
        }
        if (!MoveOverGround(object,position,end,0.5f,0.6f,0.25f,0.52359885f,0)) {
            ExplodeAndHurtNearbyMobys(object);
        } else if (FastDiffRots(angle,AI_F(object,0xF8))>0.52359885f) {
            MobySpringTurn(angle,object,state+0x58,0.00038785100332461298f,0.00043633236782625318f,0.013089972f);
        }
        break;
    case 4:
        GetGravityDirectionAtObject(object,scratch,0);
        vec_scale_to_length(scratch,scratch,4.0f);
        FastVecAdd(front,object+0x10,scratch);
        vec_scale_to_length(scratch,scratch,-1.0f);
        FastVecAdd(back,object+0x10,scratch);
        if (CollLine(back,front,0,object,0)) {
            if (gCollisionHit.surface!=gHeroState.surface) qcopy(object+0x10,gCollisionHit.point);
        }
        hit=GetCollHitMaterial();
        if (hit>0 && hit!=10 && !D_001A8CA4) {ExplodeAndHurtNearbyMobys(object);return;}
        SetMobyState(object,1,-1);
        break;
    }
    if (!D_001A8CA4 && !D_001A8CA0) {
        qcopy(scratch,object+0x10);
        scratch[2]+=0.5f;
        AI_F(object,0x18)=ProbeGroundHeightBelow(scratch,0,0.5f);
    }
}
