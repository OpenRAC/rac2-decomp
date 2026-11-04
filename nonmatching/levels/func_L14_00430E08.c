/* Faithful-source review, 4 November 2026; retained, not linked.
 * 912/920 bytes, 0/1 USA placement.
 * Remove i/j/color declaration values: each is overwritten by its loop or complete if/else before any read. The older header's claim that these were real-use initializers is incorrect. Keep the consumed count=32 and corners=4. Genuine cursor/spill lifetimes remain open.
 * Measured in the assigned production unit with the profile recorded below.
 * Other-release checks were not rerun for this nonmatching source.
 * Earlier diagnostic measurements below are historical where superseded.
 */
/* func_L14_00430E08: near miss, 3 November 2026 (opus-1, Claude Opus 5.5 xhigh).
   Profile: needs its own unit, -O2 -G0 -ffunction-sections -frac2-hazard-labels
   (retail branches land on the hazard nop after bc1fl at 0x430F98).
   Best check.py: 920/920 bytes, 0/1 places, 8 instructions differ: only the
   three pointer spill slots rotate (ours D4=axis, D8=object+16, DC=rotated;
   retail D4=object+16, D8=rotated, DC=axis). Prologue and loops match.
   Cause: reload numbers spill slots by pseudo order, which follows gcse PRE
   reaching-reg bucket order. Raw hashes object+16=14130, rotated=14190,
   axis=14222; table size N=(max_cuid/2)|1 is 103 here (max_cuid 206). Retail
   order needs N=107 (max_cuid 212-215) or 113/125/127. The j/color inits are
   real-use declaration inits that add cuids without changing code; a scale
   init, a loop-count variable and a ternary clamp all changed the code.
   Declarations: the extern block below (D_0018A0E0, not D_L14_0018A0E0).
*/
#include "common.h"
extern char D_L14_001B9500[];
extern char D_0018A0E0[];
extern void func_002FC560(unsigned int, unsigned long);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long long mode;
    char pad[24];
} PrisonQuad;
extern float D_L14_002602F0[32], D_L14_00260270[32];
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float);
extern void func_002ACEC0(void *, void *, void *, float);
void func_L14_00430E08(void *arg)
{
    char *object = arg;
    PrisonQuad q;
    float right[4], rotated[4], delta[4], axis[4];
    char *state=*(char **)(object+0x68);
    float scale;
    int i,j,color,count=32,corners=4;
    for(i=0;i<count;i++) {
        D_L14_002602F0[i]+=1.0f/ *(int *)(state+0xa8);
        if(D_L14_002602F0[i]>1.0f) { D_L14_002602F0[i]=0; D_L14_00260270[i]=func_002A7878(-1.57079637f,1.57079637f); }
    }
    func_00281DE8(&q,*(int *)(state+0xb0),1,128);
    q.mode=5;
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    func_00282CF0(right,D_L14_001B9500,object+16);
    func_00282F20(right,right,*(float *)(state+0x80)*0.5f);
    func_00282F20(axis,D_0018A0E0,-1.0f);
    for(i=0;i<count;i++) {
        if(*(float *)(state+0xac)<D_L14_002602F0[i]) color=*(int *)(state+0x98);
        else color=func_00283D38(*(int *)(state+0x94),*(int *)(state+0x98),D_L14_002602F0[i]/ *(float *)(state+0xac));
        q.color[0]=q.color[1]=q.color[2]=q.color[3]=color;
        func_002ACEC0(rotated,axis,right,D_L14_00260270[i]);
        func_00282DD8(delta,right,rotated);
        func_00282F20(delta,delta,*(float *)(state+0xb4)*(1.0f-D_L14_002602F0[i]));
        scale=*(float *)(state+0xa4)+D_L14_002602F0[i]*(*(float *)(state+0xa0)-*(float *)(state+0xa4));
        if(scale>1.0f) scale=1.0f;
        func_002FC560(0x47,0x53001);
        for(j=0;j<corners;j++) {
            qcopy(q.pos[j],object+16);
            if(j>=2) func_00282CC0(q.pos[j],q.pos[j],delta);
            else func_00282CF0(q.pos[j],q.pos[j],delta);
            if(!(j&1)) {
                func_00282F20(rotated,rotated,*(float *)(state+0x80)*(1.0f-scale));
                func_00282CC0(q.pos[j],q.pos[j],rotated);
            } else {
                func_00282F20(rotated,rotated,*(float *)(state+0x80));
                func_00282CC0(q.pos[j],q.pos[j],rotated);
                q.color[j]=*(int *)(state+0xc);
            }
            func_00282CC0(q.pos[j],q.pos[j],right);
        }
        func_00280B90(&q,0,0);
    }
    func_002FC560(0x47,0x5360B);
}
