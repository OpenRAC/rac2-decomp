#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define V(offset) ((char *)&D_00189E20+(offset))
typedef struct {
char pad0[268];
float field10c;
char pad110[8];
float field118;
char pad11c[64];
float field15c;
char pad160[16];
float field170;
float field174;
float field178;
float field17c;
float field180;
float field184;
char pad188[104];
s16 field1f0;
char pad1f2[114];
float field264;
char pad268[4];
int field26c;
char pad270[23];
u8 field287;
char pad288[148];
float field31c;
char pad320[616];
int field588;
char pad58c[7432];
int field2294;
char pad2298[4];
int field229c;
} Resident;
extern Resident D_00189E20;
extern void func_L00_002D4140(int,void *,void *);
extern float func_L00_002D3A58(char *);
extern float func_L00_002D3B00(char *);
extern void func_L00_002D3BD8(char *,char *,float);
extern void func_L00_002D3B58(Quad *,Quad *,float);
extern float func_00282E20(void *);
extern void func_00282F70(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282C88(Quad *);
extern float func_00282DB0(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_L00_002B5A88(void);
extern void func_L09_002B7238(void);
extern void func_L00_002B5250(void);
extern void func_L00_002D3960(char *,char *);
extern float func_L00_002B5590(void *);
/* Applies the player's movement for this frame, limits the speed, and records how far the player moved. */
void func_L16_002B5EE0(void)
{
    float oldPosition[4],horizontal[4],vertical[4];
    float limit,saved;
    qcopy(oldPosition,V(0x80));
    UpdateHeroAttachment(gHeroState.field588,V(0x100),V(0x90));
    if (gHeroState.field2294==0x14 || gHeroState.field2294==0x5B || gHeroState.field2294==0x58 || gHeroState.field2294==0x81) {
        if (gHeroState.field1f0==0 && GetViewSpaceVectorLength(V(0xF0))>gHeroState.field264-0.02f)
            SetViewSpaceVectorLength(V(0xF0),V(0xF0),gHeroState.field264-0.02f);
        if (GetViewSpaceHeight(V(0xF0)) < -gHeroState.field31c) {
            limit=-gHeroState.field31c-0.02f;
            if (limit>0.0f) limit=0.0f;
            SetViewSpaceHeight((Quad *)V(0xF0),(Quad *)V(0xF0),limit);
        }
    } else if (gHeroState.field229c==15) {
        if (gHeroState.field1f0==0 && vec_length_xy(V(0xF0))>gHeroState.field264-0.02f)
            FastVectorNormalizeHelper(V(0xF0),V(0xF0),gHeroState.field264-0.02f);
    } else {
        if (gHeroState.field229c==13) goto moved;
        if (gHeroState.field229c==14) goto moved;
        if (gHeroState.field1f0==0 && FastVecLength(V(0xF0))>gHeroState.field264-0.02f)
            vec_scale_to_length(V(0xF0),V(0xF0),gHeroState.field264-0.02f);
    }
moved:
    FastVecAdd(V(0x80),V(0x80),V(0xF0));
    FastVecAdd(V(0x80),V(0x80),V(0xA60));
    ClearVector128((Quad *)V(0xA60));
    gHeroState.field287=0;
    gHeroState.field26c=0;
    if (FastVecLength(V(0x100))<=0.0001f) {
        ResolveHeroCollisionWithRewind();
        ProbeHeroGround();
        FastVecSub(V(0x110),V(0x80),oldPosition);
        EaseHeroPositionToGoal();
    } else ProbeHeroGround();
    FastVecSub(V(0x120),V(0x80),oldPosition);
    qcopy(V(0x140),V(0x120));
    qcopy(V(0x130),V(0x120));
    vec_scale_to_length(V(0x120),V(0x120),1.0f);
    { float dot;
    dot=FastVecDot(V(0x120),V(0xF0));
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x120),V(0xF0),dot);
    }
    qcopy(horizontal,V(0xF0));
    ProjectVectorOntoViewPlane((char *)horizontal,(char *)horizontal);
    ProjectVectorOntoViewPlane(V(0x140),V(0x140));
    vec_scale_to_length(V(0x140),V(0x140),1.0f);
    { float dot;
    dot=FastVecDot(V(0x140),horizontal);
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x140),horizontal,dot);
    }
    qcopy(vertical,V(0xF0));
    SetViewSpaceVectorLength((char *)vertical,(char *)vertical,0.0f);
    SetViewSpaceVectorLength(V(0x130),V(0x130),0.0f);
    vec_scale_to_length(V(0x130),V(0x130),1.0f);
    { float dot;
    dot=FastVecDot(V(0x130),vertical);
    if (dot<0.0f) dot=0.0f;
    vec_scale_to_length(V(0x130),vertical,dot);
    }
    gHeroState.field170=FastVecLength(V(0x120));
    gHeroState.field174=GetViewSpaceVectorLength(V(0x120));
    *(Quad *)horizontal=*(Quad *)V(0x120);
    gHeroState.field178=GetSpeedAlongHeroForward(horizontal);
    gHeroState.field180=GetViewSpaceHeight(V(0x120));
    if (gHeroState.field178<0.0f) gHeroState.field178=0.0f;
    qcopy(horizontal,V(0x80));
    if (FastVecLength(V(0x100))>0.0001f) {
        FastVecAdd(V(0x80),V(0x80),V(0x100));
        saved=gHeroState.field10c;
        ClearVector128((Quad *)V(0x100));
        gHeroState.field10c=saved;
        ResolveHeroCollisionWithRewind();
        ProbeHeroGround();
        FastVecSub(V(0x110),V(0x80),oldPosition);
        EaseHeroPositionToGoal();
    }
    FastVecSub(V(0x150),V(0x80),horizontal);
    gHeroState.field184=FastVecLength(V(0x150));
    gHeroState.field15c=gHeroState.field10c;
    gHeroState.field10c=0.0f;
    FastVecSub(V(0x110),V(0x80),oldPosition);
    gHeroState.field17c=0.0f;
    if (gHeroState.field174>0.004f) {
        gHeroState.field17c=gHeroState.field118/gHeroState.field174;
        if (gHeroState.field17c>0.5f) gHeroState.field17c=0.5f;
        else if (gHeroState.field17c<-0.5f) gHeroState.field17c=-0.5f;
    }
    if (gHeroState.field170>0.86666673f) {
        FastVecScale(V(0x110),V(0x110),0.86666673f/gHeroState.field170);
        gHeroState.field170=0.86666673f;
    }
}
