#include "common.h"
typedef unsigned int AimTargetQuad __attribute__((mode(TI)));
extern unsigned char *D_L04_001FB5A0[];
extern float func_00283248(float, float);
extern float func_00282E20(void *);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
extern float func_00282DB0(void *, void *);

/* Looks through the moby list for the nearest visible enemy or bomb in front of the shooter and returns it with the angles to aim at it. */
unsigned char *func_L04_0040EC80(unsigned char *shooter, AimTargetQuad *origin, AimTargetQuad *direction, float *yaw, float *pitch, float *height, float angle, float range)
{
    float start[4], dir[4], delta[4], unit[4], target[4];
    float *startp=start, *dirp=dir;
    unsigned char *bestTarget=0, *candidate;
    float distance, dot;
    *(AimTargetQuad *)startp=*origin;
    *(AimTargetQuad *)dir=*direction;
    *yaw=FastMatrixHelperA(dirp[0],dirp[1]);
    *pitch=-FastMatrixHelperA(vec_length_xy(dirp),dirp[2]);
    { int index;
    for(index=0;(candidate=gMobyList[index])!=0;index++) {
        int type;
        if((signed char)candidate[0x20]<0)continue;
        type=*(short *)(candidate+0xaa);
        if(type!=0x8ba /* moby class 2234 */ && type!=0xb2d /* Enemy Hoverbike */ && type!=0xa77 /* Hoverbike Race Bomb */)continue;
        if(type==0xb2d /* Enemy Hoverbike */ && candidate[0x20]==3)continue;
        qcopy(target,candidate+0x10);
        target[2]+=0.5f;
        FastVecSub(delta,target,startp);
        distance=FastVecLength(delta);
        FastVecScale(unit,delta,1.0f/distance);
        if((*(short *)(candidate+0xaa)!=0xb2d /* Enemy Hoverbike */ || (bestTarget && *(short *)(bestTarget+0xaa)==*(short *)(candidate+0xaa))) && distance>range)continue;
        dot=FastVecDot(unit,shooter+0xc0);
        if(dot>0.707f || (dot>0.0f && distance<3.0f)) {
            if(CollLine(startp,target,2,shooter,0))continue;
            if(CollLine(target,startp,2,shooter,0))continue;
            range=distance;
            bestTarget=candidate;
            *yaw=FastMatrixHelperA(target[0]-startp[0],target[1]-startp[1]);
            *pitch=-FastMatrixHelperA(vec_distance_xy(startp,target),target[2]-startp[2]);
            *height=0.5f;
        }
    }
    }
    return bestTarget;
}
