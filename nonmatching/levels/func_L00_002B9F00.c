/* Retained complete motion/collision C: 564/564 bytes at default game -O2 -G0.
 * All three releases: 0/27 local placements; no linked credit.
 * Two aligned16-byte locals match the full quadword consumers/producers.
 * Fresh phase-local hero views recover the retail frame and GPR lifetimes.
 * Saved FP priorities, second-offset branch scheduling and the final retained
 * zero value still differ. The earlier560-byte draft had an inverted eligibility
 * comparison and is not a valid reconstruction. Reopen with real FP lifetime
 * evidence; no volatile accesses, aliases or synthetic barriers are used.
 */
#include "common.h"
extern unsigned char D_00189E20[];
extern float func_L00_002D3A58(void *);
extern void func_00282D30(void *,void *,float);
extern void func_L00_002D3BD8(void *,void *,float);
extern void func_L00_002D3798(void *,void *,float);
extern void func_L00_002D3B58(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_L00_002D38A0(void *,void *,float);
extern int func_002761F8(void *,void *,int,void *,int);
extern float func_L00_002D3EA8(void *);
extern void func_L00_002B6118(float);
struct MovementCollisionView {
    unsigned char prefix[0x1C];
    int count;
    unsigned char gap20[0x20];
    float normal[4];
};
extern struct MovementCollisionView D_L00_001BF200;

void func_L00_002B9F00(float step,float minimum,float unused)
{
    float point[4] __attribute__((aligned(16)));
    float other[4] __attribute__((aligned(16)));
    unsigned char *velocity=D_00189E20+0xF0;
    unsigned char *position;
    if(func_L00_002D3A58(velocity)==0.0f)
        return;
    {
    unsigned char *hero=velocity-0xF0;
    if(0.5f<*(float *)(hero+0x24B8) && *(int *)(hero+0x229C)!=6 &&
       *(short *)(hero+0x214)==0 && hero[0x1497]==0)
        return;
    }
    {
    unsigned char *hero=D_00189E20;
    if(*(short *)(hero+0x34E)!=0)
        return;
    if(*(int *)(hero+0x2294)==0x1F)
        step=2.0f;
    func_00282D30(point,hero+0xF0,step);
    }
    step=0.0f;
    if(step<minimum && func_L00_002D3A58(point)<minimum) {
        func_L00_002D3BD8(point,point,step);
        func_L00_002D3798(point,point,minimum);
    }
    func_L00_002D3B58(point,point,step);
    position=D_00189E20+0x80;
    func_00282CC0(point,point,position);
    qcopy(other,point);
    func_L00_002D38A0(point,point,0.3f);
    {
    unsigned char *hero=position-0x80;
    float enabled;
    func_L00_002D38A0(other,other,hero[0x22B4]==2?-0.7f:-0.35f);
    enabled=1.0f;
    if(func_002761F8(point,other,4,*(void **)(hero+0x2290),0) &&
       D_L00_001BF200.count>0 && func_L00_002D3EA8(D_L00_001BF200.normal)<=0.8726646900177002f)
        enabled=step;
    if(enabled!=0.0f)
        func_L00_002B6118(0.0f);
    }
}
