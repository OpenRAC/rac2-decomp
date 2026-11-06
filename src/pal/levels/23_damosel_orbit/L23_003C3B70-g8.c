#include "include_asm.h"
#include "common.h"

/* func_PAL_L23_003C3B70, the PAL copy of func_L23_003C02C8: the same C, where both 0x26E timer stores
 * take the 50 Hz scale, the speed step becomes 1/50 and the fourth argument of func_PAL_L23_003C3868
 * is 3. A unit of its own: it reads $gp data (D_L23_001AFA50, D_L23_001AFA54).
 * The probe's 0x326 store is a struct member at a varying address, which alias analysis keeps
 * apart from the fixed scalar D_L23_001AFA50, so the probe length loads straight into $f12. */

typedef int Quad __attribute__((mode(TI)));
typedef struct { u64 first,last; } L23PathLinks;
typedef struct { u8 pad[0x2B2]; s16 direction; u8 pad2B4[0x326-0x2B4]; s16 probeHit; } L23PathState;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
#define S(p,o) (*(s16 *)((u8 *)(p)+(o)))
extern float D_00189EA0[] __attribute__((aligned(16)));
extern float D_L23_001AFA50 __attribute__((sda));
extern int D_L23_001AFA54 __attribute__((sda));
extern u8 *D_L23_001C0A98 NOT_SDA;
extern int *D_L23_001B36A8;
extern u8 *D_L23_001FF300[];
extern L23PathLinks D_L23_002595C8[];
extern void func_L23_00418650(char *,float);
extern int func_L23_003C0A60(void *,void *,void *);
extern int func_PAL_L23_003C4CE8(void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,void *,void *);
extern s32 func_002A77E0(s32);
extern void func_PAL_L23_003C3868(char *,int,int,int,int,float);
extern s32 func_002A7820(s32,s32);
extern int func_00282978(s16 *);
extern float func_00282E48(void *,void *);
extern void func_L23_003C0C78(void *,int);
extern f32 func_L00_0031BDC0(f32 *,const f32 *,const f32 *,const f32 *);
extern void func_L23_003C0F88(char *,u64,int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern int func_L02_00332630(char *,void *);
extern int func_L22_003300E8(char *,Quad *);
extern void func_PAL_L23_003C3AA0(char *,int);
void func_PAL_L23_003C3B70(u8 *object)
{
    float destination[4] __attribute__((aligned(16))),reference[4] __attribute__((aligned(16))),node[4] __attribute__((aligned(16))),direction[4] __attribute__((aligned(16)));
    float *target;
    u8 *state=*(u8 **)(object+0x68),*path;
    int arrived,allow,mode,choice,index,pathIndex,next,base;
    unsigned short allowMode;
    float side,first,second;
    {
        float *copyTarget=*(float **)(state+0x320);
        qcopy(destination, copyTarget);
        qcopy(reference, copyTarget);
    }
    func_L23_00418650((char *)reference,0.0f);
    target=*(float **)(state+0x320);
    arrived=target==D_00189EA0 ? S(state,0x324) : func_L23_003C0A60(object,object+0x10,target);
    if (arrived==0 && S(state,0x2B0)==0 && S(state,0x26C)==0) S(state,0x2B0)=1;
    if (S(state,0x26C)!=0) goto timer;
    allow=1;
    allowMode=*(u16 *)(state+0x2B0);
    if (S(state,0x2B0)==2) allow=0;
    else if (S(state,0x2B0)==4) { if (arrived) allow=0; }
    else if (*(float **)(state+0x320)==D_00189EA0 && S(state,0x324)!=0) allow=0;
    else {
        if (allowMode==0 && arrived!=0) allow=0;
        else allow = S(state,0x2B0)==3 ? 0 : allow;
    }
    if (allow) {
        if (func_PAL_L23_003C4CE8(object)) {
            qcopy(destination, (state+0x2D0));
            qcopy((state+0x2E0), (object+0x10));
            S(state,0x26E)=((s32)(D_L23_001AFA54+func_002A7820(-D_L23_001AFA54/2,D_L23_001AFA54/2))*5+2)/6;
            goto follow;
        }
        goto follow;
    }
    {
        ((L23PathState *)state)->probeHit=0;
        func_00282D30(node,object+0xC0,D_L23_001AFA50);
        func_00282CC0(node,node,object+0x10);
    if (func_002761F8(object+0x10,node,17,object,0) && D_L23_001C0A98 && *(s16 *)(D_L23_001C0A98+0xAA)==0x7E5) {
        choice=func_002A77E0(3);
        switch (choice) {
        case 0: side=1.0f; S(state,0x26C)=1; break;
        case 1: side=-1.0f; S(state,0x26C)=1; break;
        case 2:
        default: {
            S(state,0x26C)=-1;
            func_PAL_L23_003C3868((char *)object,3,0,3,1,1.0f);
            side=0.0f;
        }
        }
        if (side!=0.0f) {
            func_00282D30(direction,object+0xD0,side);
            func_00282CC0(direction,direction,object+0xC0);
            func_00282D30(direction,direction,12.0f);
            func_00282CC0(state+0x2D0,object+0x10,direction);
            func_L23_00418650((char *)state+0x2D0,0.0f);
        }
        base=D_L23_001AFA54;
        S(state,0x2B0)=0;
        ((L23PathState *)state)->probeHit=1;
        S(state,0x26E)=((s32)(D_L23_001AFA54+func_002A7820(-base/2,base/2))*5+2)/6;
        goto follow;
    }
    }
    goto follow;
timer:
    if (S(state,0x26E)) func_00282978((s16 *)(state+0x26E));
    if (!S(state,0x26E)) S(state,0x26C)=0;
    if (S(state,0x26C)==-1) return;
    qcopy(destination, (state+0x2D0));
follow:
    mode=S(state,0x2B0);
    if (mode==0) goto update;
    switch (mode) {
    case 1: {
        u8 *path;
        func_L23_003C0C78(object,1);
        path=D_L23_001FF300[D_L23_001B36A8[S(state,0x2B4)]];
        {
            int initialIndex=S(state,0x2B6);
            qcopy(node, (path+0x10+initialIndex*16));
            S(state,0x2B0)=2;
            first=func_00282E48(path+0x10+initialIndex*16,reference);
        }
        index=S(state,0x2B6);
        if (index==0) {
            second=func_00282E48(path+0x20,reference);
            if (second<first) {
                ((L23PathState *)state)->direction=1;
                func_L00_0031BDC0((float *)(state+0x2C0),node,(float *)(path+0x20+S(state,0x2B6)*16),(float *)(object+0x10));
            } else { Quad savedNode=*(Quad *)node; ((L23PathState *)state)->direction=-1; *(Quad *)(state+0x2C0)=savedNode; }
        } else if (index==I(path,0)-1) {
            second=func_00282E48(path+(I(path,0)*16-4*4),reference);
            if (second<first) {
                ((L23PathState *)state)->direction=-1;
                func_L00_0031BDC0((float *)(state+0x2C0),node,(float *)(path+S(state,0x2B6)*16),(float *)(object+0x10));
            } else { Quad savedNode=*(Quad *)node; ((L23PathState *)state)->direction=1; *(Quad *)(state+0x2C0)=savedNode; }
        } else {
            direction[0]=func_00282E48(path+index*16,reference);
            direction[1]=func_00282E48(path+0x20+S(state,0x2B6)*16,reference);
            if (direction[0]<direction[1]) ((L23PathState *)state)->direction=-1; else ((L23PathState *)state)->direction=1;
            func_L00_0031BDC0((float *)(state+0x2C0),node,(float *)(path+0x10+((L23PathState *)state)->direction*16),(float *)(object+0x10));
        }
        func_L23_00418650((char *)state+0x2C0,0.0f);
        goto update;
    }
    case 2: {
        float *pathTarget=(float *)(state+0x2C0);
        if (func_00282E48(object+0x10,pathTarget)<2.0f) { S(state,0x2B0)=3; goto update; }
        qcopy(destination,pathTarget);
        goto update;
    }
    case 3: {
        if (func_00282E48(state+0x300,reference)<20.0f && arrived) { S(state,0x2B0)=4; goto update; }
        if (func_00282E48(object+0x10,state+0x2C0)<2.0f) {
            next=S(state,0x2B6)+((L23PathState *)state)->direction;
            if (next<0) func_L23_003C0F88((char *)object,D_L23_002595C8[D_L23_001B36A8[S(state,0x2B4)]].first,1,1);
            else {
                pathIndex=D_L23_001B36A8[S(state,0x2B4)];
                if (next>=I(D_L23_001FF300[pathIndex],0)) {
                    func_L23_003C0F88((char *)object,D_L23_002595C8[pathIndex].last,1,1);
                    goto loadPath;
                }
                S(state,0x2B6)=next;
            }
loadPath:
            path=D_L23_001FF300[D_L23_001B36A8[S(state,0x2B4)]];
            qcopy((state+0x2C0), (path+0x10+S(state,0x2B6)*16));
            func_L23_00418650((char *)state+0x2C0,0.0f);
        }
        qcopy(destination,state+0x2C0);
        goto update;
    }
    case 4: S(state,0x2B0)=0; goto update;
    default: goto update;
    }
update:
    func_00282CF0(node,destination,object+0x10);
    func_00282F20(node,node,F(state,0x2A8)*0.020000001f);
    func_L02_00332630((char *)object,destination);
    func_L22_003300E8((char *)object,(Quad *)node);
    func_PAL_L23_003C3AA0((char *)object,1);
}
