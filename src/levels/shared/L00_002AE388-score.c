#include "common.h"
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
typedef struct { char pad0[0x40]; float matrix[16]; float position[4]; char pad1[0x318-0x90]; float height; char pad2[0x2294-0x31c]; int mode; } ScorerState;
extern ScorerState D_00189E20_26;
typedef struct { char pad[0x140]; float position[4]; float pad1; float pitch; float heading; } ScorerCamera;
extern ScorerCamera D_L00_001B8C80;
extern float func_00282E48(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern int func_002ABB78(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_002830C0(void *, void *, void *);
extern float func_00282E20(void *);

/* Gives a target a score (lower is better) from how far off the aim line it is, and flags it if out of range. */
float func_L00_002AE5F0(char *object, void *axis, float range, float hlimit, float vlimit, int *blocked, void *matrix)
{
    float position[4] __attribute__((aligned(16))), delta[4] __attribute__((aligned(16))), direction[4] __attribute__((aligned(16))), cameraDelta[4] __attribute__((aligned(16)));
    float distance, horizontal, vertical, sum, score, angle;
    *blocked=0;
    qcopy_nc(position,D_00189E20_26.position);
    if(D_00189E20_26.mode==20 && D_00189E20_26.height>0.0f) qcopy_nc(position,(char *)&D_00189E20_26+0x2d0);
    distance=fast_vec_dist(position,object+0x10);
    if(range<distance) *blocked=1;
    FastVecSub(delta,object+0x10,position);
    transform_vector(delta,delta,D_00189E20_26.matrix);
    qcopy_nc(direction,axis);
    transform_vector(direction,direction,D_00189E20_26.matrix);
    angle=FastMatrixHelperA(delta[0],delta[1]);
    sum=FastDiffRots(angle,FastMatrixHelperA(direction[0],direction[1]));
    horizontal=sum;
    vertical=FastMatrixHelperA(vec_length_xy(delta),delta[2]);
    if(D_00189E20_26.mode==1 || D_00189E20_26.mode==29) {
        FastVecSub(cameraDelta,object+0x10,D_L00_001B8C80.position);
        transform_vector(cameraDelta,cameraDelta,matrix);
        horizontal=FastMatrixHelperA(cameraDelta[0],cameraDelta[1]);
        vertical=FastMatrixHelperA(vec_length_xy(cameraDelta),cameraDelta[2]);
        sum=horizontal+vertical;
        horizontal=(horizontal > vertical ? horizontal : vertical);
    }
    if(hlimit>0.0f && hlimit<horizontal) *blocked=1;
    if(vlimit>0.0f && vlimit<vertical) *blocked=1;
    score=distance+sum*distance;
    if(IsMobyInSpecialClassRange(object)) score+=range*0.8f;
    return score;
}
