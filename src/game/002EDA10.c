#include "common.h"
typedef int QuadEDA __attribute__((mode(TI)));
typedef union VecEDA { QuadEDA q; float f[4]; } VecEDA;
extern unsigned char *D_001B5390;
extern int func_002ED688(unsigned char *);
extern int func_002EE6A8(unsigned char *);
extern void func_002ED6B0(unsigned char *);
extern void func_002EE6E0(unsigned char *);
extern void func_002EE238(unsigned char *);
extern void func_002EE610(unsigned char *);
extern void func_002EE000(unsigned char *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern void func_002EE920(unsigned char *,void *);
extern int func_002EEB00(unsigned char *);
extern int func_002ED948(unsigned char *);
extern void func_002EE678(unsigned char *,int);
extern int func_001163B0(void);
extern float func_002A7878(float,float);
extern float func_00283198(float);
extern float func_00283180(float);
extern float func_00283B98(float,float);
extern int func_00283DB8(void *,float);
extern int func_002A7820(int,int);
extern void func_002ED9C0(unsigned char *);
extern void func_002EE7B8(unsigned char *);
extern void func_002EE8B0(unsigned char *);
#define IEDA(p,o) (*(int *)((p)+(o)))
#define FEDA(p,o) (*(float *)((p)+(o)))
#define PEDA(p,o) (*(unsigned char **)((p)+(o)))
/* Per-frame update of a follower object: runs its helper steps, then acts on its state (flying out, orbiting, waiting, riding its target, being collected or dying). */
void func_002EDA10(unsigned char *owner)
{
    VecEDA moveVec, extraVec, frame[3], zero, up, basis[3], test, rotated;
    unsigned char *vars = (unsigned char *)GetMobyMotionData(owner);
    unsigned char *cam;
    unsigned char *target;
    float spinDir;
    if (!vars) return;
    zero.q = 0;
    up.q = 0;
    zero.f[2] = 1.0f;
    up.f[0] = 1.0f;
    qcopy(vars+0xB0,owner+0x10);
    if (GetFollowerState(owner) != 8)
        FastVecAdd(owner+0x10,vars+0x90,owner+0x10);
    ClampFollowerToRangeAndSpawnSparks(owner);
    CheckFollowerHazardContact(owner);
    MoveFollowerTowardTarget(owner);
    LimitObjectSpeed(owner);
    UpdateBankedOrientation(owner);
    cam = D_001B5390;
    switch(GetFollowerState(owner)) {
    case 7:
        vec_scale_to_length(&moveVec,PEDA(vars,0x120)+0xC0,-50.0f);
        FastVecAdd(&moveVec,PEDA(vars,0x120)+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        if(HasFollowerReachedTarget(owner)) {
            SetFollowerState(owner,8);
            IEDA(vars,0x130)=900;
            spinDir = (Rand()&1) ? -1.0f : 1.0f;
            FEDA(vars,0x140)=spinDir;
            FEDA(vars,0x134)=spinDir < 0.0f ? 1.5707964f : -1.5707964f;
            FEDA(vars,0x144)=RandomFloatRange(5.0f,15.0f);
        }
        break;
    case 8:
        moveVec.f[2]=0.0f;
        moveVec.f[0]=FastSinOrCosB(FEDA(vars,0x134))*FEDA(vars,0x144);
        moveVec.f[1]=-FastSinOrCosA(FEDA(vars,0x134))*FEDA(vars,0x144);
        moveVec.f[3]=0.0f;
        FEDA(vars,0x134)=FastAddRotations(FEDA(vars,0x134),FEDA(vars,0x140)*0.013089972f);
        qcopy(&basis[2],cam+0x20);
        FastVecCross(&basis[1],&up,&basis[2]);
        vec_scale_to_length(&basis[1],&basis[1],1.0f);
        FastVecCross(&basis[0],&basis[2],&basis[1]);
        matrix_mul_vec3(&moveVec,&moveVec,&basis[0]);
        FastVecAdd(owner+0x10,PEDA(vars,0x120)+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        if(TryPlaceFollowerAtSavedSpot(owner)) SetFollowerState(owner,9);
        if(!HasFollowerReachedTarget(owner)) break;
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(FastMathHelperA(&test,256.0f)==-1) {
            ReleaseMotionSlot(owner);
            SetFollowerState(owner,1);
        }
        break;
    case 9:
        qcopy(&test,owner+0x10);
        test.f[3]=5.0f;
        if(FastMathHelperA(&test,256.0f)==-1) {
            ReleaseMotionSlot(owner);
            SetFollowerState(owner,1);
        }
        break;
    case 4:
        if (!PEDA(vars,0x120)) { ReleaseMotionSlot(owner); SetFollowerState(owner,1); break; }
        vec_scale_to_length(&moveVec,PEDA(vars,0x120)+0xC0,25.0f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&moveVec,&rotated,&moveVec);
        }
        FastVecAdd(&moveVec,PEDA(vars,0x120)+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        if (HasFollowerReachedTarget(owner)) {
            SetFollowerState(owner,5);
            IEDA(vars,0x130)=RandomIntRange(300,600);
        }
        break;
    case 5:
        if (!PEDA(vars,0x120)) { ReleaseMotionSlot(owner); SetFollowerState(owner,1); break; }
        vec_scale_to_length(&moveVec,PEDA(vars,0x120)+0xC0,5.0f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&moveVec,&rotated,&moveVec);
        }
        FastVecAdd(&moveVec,PEDA(vars,0x120)+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        if(HasFollowerReachedTarget(owner)) { ReleaseMotionSlot(owner); SetFollowerState(owner,1); }
        break;
    case 6:
        if (!PEDA(vars,0x120)) { ReleaseMotionSlot(owner); SetFollowerState(owner,1); break; }
        vec_scale_to_length(&moveVec,PEDA(vars,0x120)+0xC0,10.0f);
        vec_scale_to_length(&extraVec,PEDA(vars,0x120)+0xE0,0.05f);
        if (IEDA(vars,0xFC)) {
            matrix_mul_vec3(&rotated,vars+0x70,PEDA(vars,0x120)+0xC0);
            FastVecAdd(&moveVec,&rotated,&moveVec);
        }
        FastVecAdd(&moveVec,&extraVec,&moveVec);
        FastVecAdd(&moveVec,PEDA(vars,0x120)+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        if(HasFollowerReachedTarget(owner)) { ReleaseMotionSlot(owner); SetFollowerState(owner,1); }
        break;
    case 3:
        target=PEDA(vars,0x10);
        qcopy(&frame[0],target+0xC0);
        FastVecCross(&frame[1],&frame[0],&zero);
        vec_scale_to_length(&frame[1],&frame[1],1.0f);
        FastVecCross(&frame[2],&frame[1],&frame[0]);
        matrix_mul_vec3(&moveVec,vars,&frame[0]);
        FastVecAdd(&moveVec,target+0x10,&moveVec);
        SetFollowerPushVector(owner,&moveVec);
        break;
    case 1:
        if(HasFollowerReachedTarget(owner)) StartFollowerRandomPush(owner);
        break;
    case 13:
        if(HasFollowerReachedTarget(owner)) StartFollowerPushFromTarget(owner);
        break;
    }
}
