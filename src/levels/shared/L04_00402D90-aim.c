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

unsigned char *func_L04_0040EC80(unsigned char *m, AimTargetQuad *origin, AimTargetQuad *direction, float *yaw, float *pitch, float *height, float angle, float range)
{
    float start[4], dir[4], delta[4], unit[4], target[4];
    float *startp=start, *dirp=dir;
    unsigned char *found=0, *candidate;
    float distance, dot;
    *(AimTargetQuad *)startp=*origin;
    *(AimTargetQuad *)dir=*direction;
    *yaw=func_00283248(dirp[0],dirp[1]);
    *pitch=-func_00283248(vec_length_xy(dirp),dirp[2]);
    { int index;
    for(index=0;(candidate=D_L04_001FB5A0[index])!=0;index++) {
        int type;
        if((signed char)candidate[0x20]<0)continue;
        type=*(short *)(candidate+0xaa);
        if(type!=0x8ba && type!=0xb2d && type!=0xa77)continue;
        if(type==0xb2d && candidate[0x20]==3)continue;
        qcopy(target,candidate+0x10);
        target[2]+=0.5f;
        FastVecSub(delta,target,startp);
        distance=FastVecLength(delta);
        FastVecScale(unit,delta,1.0f/distance);
        if((*(short *)(candidate+0xaa)!=0xb2d || (found && *(short *)(found+0xaa)==*(short *)(candidate+0xaa))) && distance>range)continue;
        dot=FastVecDot(unit,m+0xc0);
        if(dot>0.707f || (dot>0.0f && distance<3.0f)) {
            if(CollLine(startp,target,2,m,0))continue;
            if(CollLine(target,startp,2,m,0))continue;
            range=distance;
            found=candidate;
            *yaw=func_00283248(target[0]-startp[0],target[1]-startp[1]);
            *pitch=-func_00283248(vec_distance_xy(startp,target),target[2]-startp[2]);
            *height=0.5f;
        }
    }
    }
    return found;
}
