#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { Vector128 difference, local, previous, velocity, lateral; } MotionWorkspace;
extern char D_00189E20[];

extern float D_L16_001AF43C __attribute__((sda));
extern void func_L00_002B39F0(int,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002AFDD8(char *,char *,char *,char *);
extern void func_00282F70(void *,void *,float);
extern void func_00283098(void *,void *,void *);
extern float func_00282DB0(void *,void *);
extern float func_002AA2E8(float *,float,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282A88(void *,int);
extern void func_002AC9F8(float *,float);
/* Moves a spinning object across the ground, pushing it along with the player's facing and tracking how much it has spun. */
void func_L16_003959B8(char *object)
{
    MotionWorkspace local;
    char *state=*(char **)(object+0x68);
    float alignment;
    ResolveStickInputToDirection(0,1.0f);
    qcopy(&local.previous,(gHeroState+0x190));
    FastVecSub(&local.difference,gHeroState+0x80,object+0x10);
    FastVecCross((gHeroState+0x190),&local.difference,object+0xe0);
    vec_scale_to_length((gHeroState+0x190),(gHeroState+0x190),1.0f);
    TransformVectorByObjectOrGiven(object,(char *)&local.local,(char *)&local.difference,0);
    FastVectorNormalizeHelper(&local.velocity,&local.local,D_L16_001AF43C);
    matrix_mul_vec3(&local.velocity,&local.velocity,object+0xc0);
    alignment=FastVecDot(&local.previous,(gHeroState+0x190));
    if (*(float *)(gHeroState+0x24b8)>0.5f && alignment>0.5f)
        ApproachValue((float *)(state+0x30),alignment*0.0833333358f,0.00138888892f);
    else ApproachValue((float *)(state+0x30),0.0f,0.00138888892f);
    if (*(float *)(state+0x30)!=0.0f) {
        vec_scale_to_length(&local.lateral,(gHeroState+0x190),*(float *)(state+0x30));
        FastVecAdd(&local.velocity,&local.velocity,&local.lateral);
        *(float *)(state+0x34)+=*(float *)(state+0x30)/(*(float *)(state+8)*6.28318548f);
        if (*(float *)(state+0x34)>1.0f) *(float *)(state+0x34)=1.0f;
    }
    FastVecAdd(&local.velocity,&local.velocity,object+0x10);
    FastMemoryHelperB(gHeroState+0xf0,0xa0);
    FastVecSub(gHeroState+0xf0,&local.velocity,gHeroState+0x80);
    ClampVectorLength((float *)(gHeroState+0xf0),0.100000009f);
}
