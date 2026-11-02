/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), task v1282, 29 October 2026.
 * Game -O2 -G8 -ffunction-sections, USA v1.01: 1840/1840 bytes,
 * 0/2 places (Barlow/Notak); frame matches 0x100. All declarations below.
 * The earlier draft remeasured at 1928/1840 here. Approved qcopy_nc
 * transfers reproduce the two address-based quadword copies. Explicit
 * search backedges avoid the peeled random-search iteration and nearest
 * loop invariant hoists, but lose GCC's loop weighting: state/slot are
 * s1/s2 rather than retail s2/s1, and object/counter are s3/s4 rather than
 * s4/s3. Stack-address spill order, temporary registers, padding and
 * scheduling also differ. This is not a linked match.
 * Structured nearest loops restore object/state/counter allocation when
 * the index is scoped to case 1, but hoist -1 and the resident target base,
 * spilling two additional pointers and growing the frame to 0x110.
 * A typed state view corrects case-0 load/store scheduling (1832 bytes
 * with backedges; 1852 with the structured nearest loop), still 0/2.
 * Aggregate vector storage ties this draft. -fno-rerun-loop-opt ties the
 * structured-loop output; -fno-gcse, -fno-strength-reduce and
 * -fno-expensive-optimizations do not solve it. No volatile accesses,
 * barriers, pins, compiler changes or unavailable flags were used.
 * Next: recover loop weighting without the invariant-hoist/spill change;
 * another equivalent for/while spelling alone is not useful evidence.
 * D_L04_001B25CC requires G8. The path table is level data, so its name
 * is corrected from the old draft's D_001FE340 to D_L04_001FE340.
 */
#include "common.h"
typedef int UpdateQuad __attribute__((mode(TI)));
extern int D_L04_001B2008 __attribute__((section(".sdata")));
extern unsigned char D_L04_001B9680[], D_00189EA0[], D_L04_001A8F20[];
extern unsigned char *D_L04_001B25CC __attribute__((sda));
extern unsigned char *D_L04_001FE340[];
extern void func_L04_003EDF80(unsigned char *, unsigned char *);
extern int func_L04_003EDFF0(unsigned char *, unsigned char *);
extern void func_0029F338(void *);
extern int func_002A8600(unsigned char **,int,int,int);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern void func_002A7470(void *,int,int,int);
extern int func_00282978(short *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *,void *,void *,int,void *,int,float);
extern int func_002A7820(int,int);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282FB8(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_L02_0031E9E8(void *,float);
extern float func_002A7878(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_002ACB48(void *,float);
extern float func_L00_0031CDD0(void *,void *,int,float,float);
extern unsigned char *func_L04_003EDD40(void *,void *);
extern void func_002A7A00(void *,float,float);
extern void func_L04_0030C4C0(void *,void *,void *,void *,void *,void *,int,int,int);
extern void func_002A7750(void *,int,int);
extern int func_002E5CF8(int,int,void *);
extern void func_0032C700(void *,int,int,int,int,int,int,int,int,int,int,int,float,float);
extern void func_002A6C58(void *,int,int);
void func_L04_003EE090(unsigned char *m)
{
    float target[4], delta[4], rotation[4], axis[4], position[4], velocity[4];
    unsigned char *p=*(unsigned char **)(m+0x68), *cursor, *chosen, *child;
    int count, index;
    float scale, z;
    func_L04_003EDF80(m,p);
    if(m[0x31] && func_00282E48(m+0x10,D_L04_001B9680)<24.0f) {
        func_002A93B0(m); m[0x6f]=22;
    }
    switch(m[0x20]) {
    case 0:
        p[0x29]=1; *(float *)(p+0x20)=1.0f; *(int *)(p+0x140)=0;
        if(D_L04_001B2008) {
            cursor=0; count=0;
            while(!func_002A8600(&cursor,*(int *)(p+0x84),0,0)) {func_0029F338(cursor); count++;}
            if(count<p[0x80]) p[0x80]=count;
            m[0x20]=1;
        }
        break;
    case 1: {
        int i; float best,distance;
        func_L04_003EDF80(m,p);
        if(m[0x43]==1 && (m[0x60]&2)) func_002A7470(m,0,0,5);
        if(!func_00282978((short *)(p+0x7e))) break;
        if(!func_002A77E0(7)) {
            void *ids=0,*path=0; int n=0, pathCount=0;
            if(*(int *)(p+0x74)!=-1) {ids=p+0x74;n=1;}
            if(*(int *)(p+0x78)!=-1) {unsigned char *d=D_L04_001FE340[*(int *)(p+0x78)]; path=d+0x10;pathCount=*(int *)d;}
            func_L04_003429F8(m,p+0xf0,ids,n,path,pathCount,*(float *)(p+0x70));
        } else {
            unsigned char *q=*(unsigned char **)(p+0x130);
            if(q && q[0x20]!=0xfe && q[0x20]!=0xfd) qcopy_nc(p+0xf0,q+0x10);
            else {*(int *)(p+0x130)=0;*(int *)(p+0x134)=2;}
        }
        if(*(int *)(p+0x134)==2) break;
        index=func_L04_003EDFF0(m,p);
        if(p[0x81]>=p[0x80] || index==-1) break;
        chosen=0;
        if(p[0x82]) {
            int *slot=(int *)(p+0x90);
            best=100000.0f;
            i=3;
        nearestTarget:
            {
                int id=*slot;
                if(id!=-1) {
                    unsigned char *q=D_L04_001B25CC+id*128;
                    distance=func_00282E48(D_00189EA0,q+0x30);
                    if(distance<best) {chosen=q;best=distance;}
                }
            }
            slot++;
            if(--i>=0) goto nearestTarget;
            if(!chosen) {
                func_00282CF0(target,p+0xf0,m+0x10);
                func_00282D30(target,target,0.5f);
                if(*(float *)(p+0x70)>1.0f) func_00282FB8(target,target,1.0f);
                if(func_00282DF0(target)<1.0f) func_00282F20(target,target,1.0f);
                func_00282CC0(target,target,m+0x10);
                goto targetReady;
            }
        } else {
            int start=func_002A7820(0,3);
            i=0;
            goto testTarget;
        nextTarget:
            i++;
        testTarget:
            if(i<4) {
                int id=*(int *)(p+0x90+((i+start)%4)*4);
                if(id==-1) goto nextTarget;
                chosen=D_L04_001B25CC+id*128;
            }
            if(!chosen) {
                float radius=*(float *)(p+0x70); if(radius<1.0f) radius=1.0f;
                func_L02_0031E9E8(target,radius);
                func_00282CC0(target,target,m+0x10);
                goto targetReady;
            }
        }
        qcopy_nc(target,chosen+0x30);
    targetReady:
        if(chosen) {
            func_00282D30(delta,chosen,func_002A7878(-0.5f,0.5f));
            func_00282CC0(target,target,delta);
            func_00282D30(delta,chosen+0x10,func_002A7878(-0.5f,0.5f));
            func_00282CC0(target,target,delta);
        }
        z=func_002A89A8(target,0,3.0f); if(z!=0) target[2]=z;
        func_00282CF0(delta,target,m+0x10);
        scale=func_00282DF0(delta)*0.0100000007f;
        func_00282F20(delta,delta,scale);
        func_0029FCC0(m,0,rotation);
        func_00282F20(axis,delta,0.05f);
        func_002ACB48(axis,0.025f);
        delta[2]=func_L00_0031CDD0(rotation,target,0,scale,-0.00272222236f);
        *(UpdateQuad *)position=*(UpdateQuad *)(m+0x10);
        child=func_L04_003EDD40(m,position);
        *(float *)(child+0x2c)=*(float *)(*(unsigned char **)(child+0x24)+0x24);
        func_002A7A00(position,2.0f,3.0f);
        position[2]=0;
        func_00282CC0(position,position,target);
        rotation[2]+=1.0f;
        *(UpdateQuad *)velocity=0;
        velocity[2]=3.0f;
        func_L04_0030C4C0(child,rotation,velocity,position,velocity,D_L04_001A8F20,60,0,0);
        p[0x81]++;
        *(short *)(p+0x7e)=*(short *)(p+0x7c);
        if(++*(int *)(p+0x140)>=19) func_002A7750(m,2,-1);
        func_002E5CF8(0,0,m);
        if(m[0x43]!=1) func_002A7470(m,1,0,5);
        break;
    }
    case 2:
        func_0032C700(m+0x10,0,25,20,20,20,20,0,1,0,0,0,0.75f,20.0f);
        *(float *)(p+0x20)=0;
        func_002E5CF8(1,0,m);
        func_002A6C58(m,0,3);
        func_0029F338(m);
        break;
    }
}
