#include "common.h"
typedef int V4_Fbfdc087a __attribute__((mode(TI)));

typedef struct {
unsigned char pad0[464];
short cooldown;
unsigned char pad1d2[146];
float radius;
unsigned char pad268[180];
float groundHeight;
unsigned char pad320[382];
unsigned char pastApex;
unsigned char pad49f[1945];
float frame;
unsigned char padc3c[5716];
void * moby;
int state;
unsigned char pad2298[4];
int control;
unsigned char pad22a0[20];
unsigned char vehicle;
} LedgeProbeResident;
extern LedgeProbeResident D_00189E20;
/* Related ledge-probe flow: OpenRAC/rac1-decomp hero_idle_and_animation.c,
 * check_ledge_grab (GPL-3.0); this version uses oriented vector helpers. */
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283180(float);
extern float func_00283248(float, float);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern float func_L00_002D3EA8(void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern char *func_002AB1F0(void *);
extern char *func_002AD0B0(void *);
extern int func_00277258(void *, int, void *, float);
typedef struct {
    unsigned char pad0[0x18];
    void *moby;
    unsigned char pad1c[4];
    float position[4];
    unsigned char pad30[16];
    float normal[4];
} LedgeProbeHit;
extern LedgeProbeHit D_L00_001BF200;
#define FL(p,o) (*(float *)((char *)(p)+(o)))
#define IN(p,o) (*(int *)((char *)(p)+(o)))
/* Checks whether the hero can grab a ledge in front of it. Returns 1 and fills in the grab position if it can. */
int func_L00_002ACF88(void *position, void *unused, char *out)
{
    float probeBase[4], upperPoint[4], lowerPoint[4], stepOffset[4], scratchOffset[4], toLedge[4], ledgePoint[4], aboveLedge[4], behindLedge[4], probeStart[4], edgeStep[4], probeEnd[4], edgeNormal[4], sweepEndA[4], sweepEndB[4], nearOffset[4], farOffset[4], downOffset[4], sweepPoint[4], backOffset[4];
    char *mobyData, *mobyInfo;
    void *object;
    int canGrab, found, i, kind, grabbable;
    int edge, j;
    float height;
    float step, max;
    float down, fwd, up, top, drop, rise, back, sweepDistance, length;
    if (out) IN(out,0x28)=0;
    if (gHeroState.cooldown) return 0;
    canGrab=0;
    if (gHeroState.vehicle==0) {
        if ((gHeroState.control==4 && (gHeroState.pastApex || GetViewSpaceHeight((char *)&gHeroState+0xf0)<0.05833333730697632f)) || gHeroState.control==2 || gHeroState.state==8 || gHeroState.state==25 || gHeroState.state==26) canGrab=1;
        if (gHeroState.state==14 && gHeroState.frame<37.0f) canGrab=0;
    }
    if (gHeroState.vehicle==1) {
        if ((gHeroState.control==4 && gHeroState.pastApex) || gHeroState.control==2 || gHeroState.state==75 || gHeroState.state==73 || gHeroState.state==74) canGrab=1;
    }
    if (out != (char *)&gHeroState+0x550) canGrab=1;
    if (!canGrab) return 0;
    down=-0.7f; fwd=0.3f; up=1.5f; top=1.15f; drop=-1.43f; rise=1.8f; back=0.5f;
    found=0;
    if (gHeroState.vehicle==1) { down=-0.4f; fwd=0.25f; up=0.725f; top=0.7f; drop=-0.71f; rise=0.7f; back=0.32f; }
    qcopy(probeBase,position);
    vec_scale_to_length(scratchOffset,(char *)&gHeroState,gHeroState.radius);
    FastVecAdd(probeBase,probeBase,scratchOffset);
    vec_scale_to_length(scratchOffset,(char *)&gHeroState+0x20,up+0.15f);
    FastVecAdd(upperPoint,probeBase,scratchOffset);
    vec_scale_to_length(scratchOffset,(char *)&gHeroState+0x20,-top);
    FastVecAdd(lowerPoint,probeBase,scratchOffset);
    vec_scale_to_length(stepOffset,(char *)&gHeroState,fwd*0.25f);
    for(i=0; i<4; i++) {
        FastVecAdd(upperPoint,upperPoint,stepOffset);
        FastVecAdd(lowerPoint,lowerPoint,stepOffset);
        if(CollLine(upperPoint,lowerPoint,4,gHeroState.moby,0)) {
            kind=GetCollHitMaterial();
            if(kind!=9 && kind!=12 && kind!=0 && GetViewSpaceAngle(gCollisionResult.normal)<0.349065899848938f) found=1;
        }
        if(found) break;
    }
    object=0;
    if(!found) goto fail;
    if(gCollisionResult.moby) {
        grabbable=0;
        mobyData=GetMobyPrivateValue0(gCollisionResult.moby);
        mobyInfo=GetMobyPrivateValue2(gCollisionResult.moby);
        if(mobyData && (*(unsigned short *)(mobyData+0x1e)&1)) grabbable=1;
        else if(mobyInfo) grabbable=IN(mobyInfo,0x3c)&1;
        if(!grabbable) return 0;
        object=gCollisionResult.moby;
    }
    if(out) *(void **)(out+0x38)=gCollisionResult.moby;
    qcopy(ledgePoint,gCollisionResult.position);
    FastVecSub(toLedge,ledgePoint,position);
    if(up<GetViewSpaceHeight(toLedge)) return 0;
    vec_scale_to_length(aboveLedge,(char *)&gHeroState+0x20,0.005f);
    FastVecAdd(aboveLedge,aboveLedge,ledgePoint);
    vec_scale_to_length(behindLedge,(char *)&gHeroState,-1.0f);
    FastVecAdd(behindLedge,behindLedge,aboveLedge);
    if(CollLine(behindLedge,aboveLedge,2,gHeroState.moby,0)) {
        if(!gCollisionResult.moby || gCollisionResult.moby!=object) return 0;
    }
    if(out) {
        vec_scale_to_length(probeStart,(char *)&gHeroState+0x20,0.6f);
        FastVecAdd(probeStart,probeStart,ledgePoint);
        if(TestPointAgainstCollision(probeStart,4,gHeroState.moby,0.45f)) IN(out,0x34)|=1;
        else IN(out,0x34)&=~1;
    }
    height=GetViewSpaceHeight(toLedge);
    if(height+gHeroState.groundHeight<rise || height<0.5f) return 0;
    *(V4_Fbfdc087a *)probeEnd=0; FL(probeEnd,0)=1.0f; FL(probeEnd,8)=down;
    matrix_mul_vec3(probeEnd,probeEnd,(char *)&gHeroState);
    edge=0;
    FastVecAdd(probeEnd,probeEnd,ledgePoint);
    FastVecSub(probeStart,position,probeEnd);
    SetViewSpaceHeight(probeStart,probeStart,0.0f);
    FastVecAdd(probeStart,probeStart,probeEnd);
    vec_scale_to_length(edgeStep,(char *)&gHeroState+0x20,-down*0.2f);
    for(j=0;j<5;j++) {
        if(CollLine(probeStart,probeEnd,2,0,0)) {
            vec_scale_to_length(edgeNormal,gCollisionResult.normal,1.0f);
            edge=1;
            SetViewSpaceHeight(edgeNormal,edgeNormal,0.0f);
            break;
        }
        FastVecAdd(probeStart,probeStart,edgeStep);
        FastVecAdd(probeEnd,probeEnd,edgeStep);
    }
    if(!edge) return 0;
    length=FastVecDot((char *)&gHeroState,edgeNormal);
    if(!(length<FastSinOrCosA(1.134464144706726f))) return 0;
    step=0.03f;
    max=2.4f;
    qcopy(sweepPoint,ledgePoint);
    vec_scale_to_length(downOffset,(char *)&gHeroState+0x2c0,-0.05f);
    vec_scale_to_length(farOffset,edgeNormal,step);
    FastVecAdd(nearOffset,farOffset,downOffset);
    FastVecSub(farOffset,farOffset,downOffset);
    FastVecAdd(sweepEndA,sweepPoint,farOffset);
    FastVecAdd(sweepEndB,sweepPoint,nearOffset);
    for(sweepDistance=0.0f;sweepDistance<max;sweepDistance+=step) {
        if(!CollLine(sweepEndB,sweepEndA,4,gHeroState.moby,0)) {
            if(out) {
                qcopy(out+0x10,sweepPoint);
                vec_scale_to_length(backOffset,edgeNormal,back);
                vec_scale_to_length(out,(char *)&gHeroState+0x2c0,-drop);
                FastVecAdd(out,backOffset,out);
                FastVecAdd(out,out+0x10,out);
                FL(out,0x24)=FastMatrixHelperA(FL(edgeNormal,0),FL(edgeNormal,4));
                IN(out,0x28)=1;
            }
            return 1;
        }
        qcopy(sweepPoint,gCollisionResult.position);
        FastVecAdd(sweepEndB,sweepPoint,nearOffset);
        FastVecAdd(sweepEndA,sweepPoint,farOffset);
    }
fail:
    return 0;
}
#undef FL
#undef IN
