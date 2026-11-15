#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    unsigned char pad0[0x80]; Vec position; unsigned char pad90[0x294];
    float pitch; unsigned char pad328[0x20]; short allowed;
    unsigned char pad34a[0x1f46]; char *object;
} PlayerView;
extern PlayerView D_00189E20;
extern int D_L24_001A8FF0;
extern int D_L24_001A8FF4 __attribute__((sda));
extern float D_L24_001AFC00 __attribute__((sda)),D_L24_001AFC04 __attribute__((sda));
extern char *D_L24_001FA5E0[];
extern Vec D_L24_001BEB20;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; } Collision;
extern Collision D_L24_001BEB00;
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern char *func_002AB1F0(char *);
extern float func_00283248(float,float),func_00283C80(float,float),func_00282C48(float),func_002831B0(float),func_00283CE0(int);
extern float func_00282E80(void *,void *),func_00282E48(void *,void *),func_00282DB0(void *,void *),func_00282DF0(void *);
extern void func_002AF000(void *,float,float,float);

/* Target selection: the nearest visible candidate in front of the player within the aim cone. */
char *func_L24_003B3C38(char *moby,Vec *origin,float *yaw,float *pitch) {
    struct { Vec origin,offset,player; char *disabled[128]; Vec target,aim,ray,axis; } frame;
    Vec *start=&frame.origin;
    char *ctx=*(char **)(moby+0x68),*selected,*candidate,*definition,*hit;
    Vec *pos; int n,index,accepted,visible,tries,i;
    float best=D_L24_001AFC04,heading,elevation,delta,distance,dot,length,angle,radius;
    start->q=origin->q;
    FastVecScale(&frame.offset,gHeroState.object+0xE0,0.5f);
    selected=0;
    FastVecAdd(&frame.player,gHeroState.object+0x10,&frame.offset);
    if(CollLine(&frame.player,start,6,gHeroState.object,0)) {
        qcopy(start,&D_L24_001BEB20);
        return 0;
    }
    n=0; index=0;
    while((candidate=D_L24_001FA5E0[index])!=0) {
        if(*(unsigned char *)(candidate+0x20)==0xFE) goto next;
        if(*(unsigned char *)(candidate+0x20)==0xFD) goto next;
        if(*(short *)(candidate+0xAA)==0xE7D /* Sheep */ || *(short *)(candidate+0xAA)==0xEB0 /* Dark Sheep */) goto next;
        { Vec *t=&frame.target; qcopy(t,candidate+0x10); }
        definition=GetMobyPrivateValue0(candidate);
        if(!definition || *(unsigned char *)(definition+0xE)==3) goto next;
        FastVecScale(&frame.aim,candidate+0xE0,*(float *)(definition+0x10));
        FastVecAdd(&frame.target,&frame.target,&frame.aim);
        if(!candidate || !*(char **)(candidate+0x24) || *(short *)(*(char **)(candidate+0x24)+0x46)!=5) goto next;
        accepted=0;
        heading=FastMatrixHelperA(frame.target.f[0]-start->f[0],frame.target.f[1]-start->f[1]);
        elevation=FastMatrixHelperA(vec_distance_xy(start,&frame.target),frame.target.f[2]-start->f[2]);
        delta=FastDiffRots(*yaw,heading);
        distance=fast_vec_dist(start,&frame.target);
        if(D_L24_001A8FF0 || gHeroState.allowed || D_L24_001A8FF4) {
            if(distance<2.5f) {
            FastVecSub(&frame.ray,candidate+0x10,gHeroState.object+0x10);
            dot=FastVecDot(&frame.ray,gHeroState.object+0xE0);
            if(FloatAbs(dot)<2.0f) {
                FastVecScale(&frame.axis,gHeroState.object+0xE0,dot);
                FastVecSub(&frame.ray,&frame.ray,&frame.axis);
                dot=FastVecDot(&frame.ray,gHeroState.object+0xC0);
                { float len=FastVecLength(&frame.ray);
                if(len!=0.0f && 1.5707964f-FastAngleHelper(dot/len)<1.0471977f) accepted=1; }
            }
            }
        } else {
            if(distance<2.5f) {
                char *pobj=gHeroState.object;
                angle=FastMatrixHelperA(*(float *)(candidate+0x10)-gHeroState.position.f[0],*(float *)(candidate+0x14)-gHeroState.position.f[1]);
                if(FastDiffRots(*(float *)(pobj+0xF8),angle)<1.0471977f && FloatAbs(start->f[2]-frame.target.f[2])<2.0f) accepted=1;
            }
        }
        if(accepted && !CollLine(start,&frame.target,6,gHeroState.object,0)) { selected=candidate; *pitch=-elevation; *yaw=heading; break; }
        if((distance>best && candidate!=*(char **)(ctx+0x10)) || distance>D_L24_001AFC04) goto next;
        BuildSphericalOffset(&frame.aim,distance,*yaw,*pitch+gHeroState.pitch*0.5f);
        FastVecAdd(&frame.aim,&frame.aim,start);
        angle=fast_vec_dist(&frame.aim,&frame.target);
        angle=FastAngleHelper(angle/(distance+distance)); angle+=angle;
        if(D_L24_001AFC00*0.017453294f<angle && (definition=GetMobyPrivateValue0(candidate))!=0) {
            radius=IntToFloat((unsigned char)definition[10])*0.125f;
            length=FastAngleHelper(radius/distance);
            if(radius<distance) { angle-=length; if(angle<0.0f) angle=0.0f; }
        }
        if(angle<D_L24_001AFC00*0.017453294f) {
            visible=1;
            qcopy(&frame.ray,start); tries=0;
            while(CollLine(&frame.ray,&frame.target,6,moby,0)) {
                Collision *col;
                if(++tries>6) break;
                col=&D_L24_001BEB00;
                hit=col->hit;
                if(hit) {
                    if(*(short *)(hit+0xAA)==0xE7D /* Sheep */ || *(short *)(hit+0xAA)==0xEB0 /* Dark Sheep */) {
                        frame.disabled[n++]=hit; *(int *)(hit+0x98)=0;
                        if(n>127) break;
                        qcopy(&frame.ray,&col->point);
                        continue;
                    }
                    if(hit==candidate) break;
                }
                visible=0; break;
            }
            if(visible) { *pitch=-elevation; best=distance; if(delta<0.17453295f) *yaw=heading; selected=candidate; if(candidate==*(char **)(ctx+0x10)) return selected; }
        }
next:
        ++index;
    }
    for(i=0;i<n;++i) { char *m=frame.disabled[i]; *(int *)(m+0x98)=*(int *)(*(char **)(m+0x24)+0x10); }
    return selected;
}
