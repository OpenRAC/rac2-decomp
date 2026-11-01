/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol, high effort (v1275, 29 October 2026).
 * Best: 1820/1820 bytes, 0/2 USA v1.01 places, default -O2 -G8
 * -ffunction-sections. Final check: instruction at +0x4 differs in both places.
 * 18 check.py invocations (one C89 syntax failure), plus one regalloc run.
 * Register allocation still swaps owner/state s4/s5; the position pointer spills
 * instead of occupying fp, and nearest/random loop setup and scheduling differ.
 * Separate case-local counters reproduce retail's initialization-case allocation.
 * Preincrement search from -1 avoids the old peeled first iteration. Explicit
 * nearest-target pointer walking, split target-copy branches, separate float
 * lifetimes, and the measured 0x3DA3D70B flight constant recover retail's size.
 * The effect prototype now follows the existing mixed integer/FP declaration;
 * func_L08_003F6018 returns a pointer, as its matched implementation establishes.
 * No linked build: this is a near miss, not a match. All declarations are below.
 * Negative probes: -fno-rerun-loop-opt, -fno-thread-jumps and
 * -frac2-keep-block-order left peeling intact in the earlier for-loop body;
 * -fno-strength-reduce and -fno-expensive-optimizations did not match either.
 * With explicit pointer walking and case-local state, -fno-strength-reduce gives
 * 1816 bytes; the retained default profile gives 1820. Do not repeat these probes.
 * Next: use allocator/lifetime evidence to recover fp for the position pointer
 * without prolonging it across the guards, then revisit search-loop entry.
 * Compile this draft in its own -g8.c source unit.
 */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 D_00189EA0[] __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
#define E_I(p,o) (*(int *)((u8 *)(p)+(o)))
#define E_F(p,o) (*(float *)((u8 *)(p)+(o)))
extern void func_L08_003F6348(void *,void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern int D_L08_001B2508;
extern u8 D_L08_001B9B00[];
extern u8 *D_L08_001FE7C0[];
extern u8 *D_L08_001B2ACC __attribute__((sda));
extern float D_L08_001B0B5C __attribute__((sda));
extern u8 D_L08_001AC5E0[];
extern void func_0029F338(void *);
extern int func_002A8600(void **,int,int,int);
extern int func_00282978(void *);
extern int func_002A77E0(int);
extern void func_L04_003429F8(void *,void *,void *,int,void *,int,float);
extern int func_L08_003F6568(void *,void *);
extern void func_002A7470(void *,int,int,int);
extern float func_0029F530(void *);
extern float func_00282DF0(void *);
extern void func_00282FB8(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern int func_002A7820(int,int);
extern void func_L02_0031E9E8(void *,float);
extern float func_002A7878(float,float);
extern float func_002A89A8(void *,int,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_002ACB48(void *,float);
extern float func_L00_0031CDD0(void *,void *,int,float,float);
extern u8 *func_L08_003F6018(void *,void *,void *);
extern int func_L06_0035EA68(void *,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
typedef struct { u8 pad[0x120]; float speed; int path,object; u16 delay, timer; u8 limit,count,nearest,pad2; int children[2]; int pad3; int targets[4]; } FVars;
void func_L08_003F6610(u8 *m)
{
    void *found;
    struct { TI128 target, direction, velocity, step; } frame;
    u8 *p=*(u8 **)(m+0x68);
    int index;

    void *a2,*t0;
    int a3,t1;
    func_L08_003F6348(m,p);
    if(m[0x31] && func_00282E48(m+0x10,D_L08_001B9B00)<24.0f) {
        func_002A93B0(m);m[0x6f]=0x16;
    }
    switch(m[0x20]) {
    case 0:
        if(D_L08_001B2508) {
            int i;
            found=0;
            for(i=0;i<2;i++) {
                while(!func_002A8600(&found,((FVars *)p)->children[i],0,0)) func_0029F338(found);
            }
            m[0x20]=1;
        }
        p[0x29]=1;
        break;
    case 1:
        if(!func_00282978(p+0x12e)) break;
        if(!func_002A77E0(7)) {
            a2=0;a3=0;t0=0;t1=0;
            if(E_I(p,0x124)!=-1) {a2=p+0x124;a3=1;}
            if(E_I(p,0x128)!=-1) {u8 *obj=D_L08_001FE7C0[E_I(p,0x128)];t1=E_I(obj,0);t0=obj+0x10;}
            func_L04_003429F8(m,p+0xc0,a2,a3,t0,t1,E_F(p,0x120));
        } else {
            u8 *obj=*(u8 **)(p+0x100);
            if(obj && obj[0x20]!=0xfe && obj[0x20]!=0xfd) qcopy(p+0xc0,obj+0x10);
            else {E_I(p,0x100)=0;E_I(p,0x104)=2;}
        }
        if(E_I(p,0x104)==2) break;
        index=func_L08_003F6568(m,p);
        if(p[0x130]>p[0x131] && index!=-1) {
            m[0x20]=2;
            if(m[0x43]!=1) func_002A7470(m,1,0,10);
        }
        break;
    case 2: {
        u8 *chosen;
        u8 *position;
        float f;
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) func_002A7470(m,0,0,10);
            break;
        }
        if(func_0029F530(m)!=12.0f) break;
        chosen=0;
        position=m+0x10;
        if(p[0x132]) {
            int i;
            float best, d;
            int *target=((FVars *)p)->targets;
            best=100000.0f;
            for(i=3;i>=0;i--,target++) {
                int k=*target;
                if(k!=-1) {
                    u8 *obj=D_L08_001B2ACC+k*128;
                    d=func_00282E48(D_00189EA0,obj+0x30);
                    if(d<best) {chosen=obj;best=d;}
                }
            }
            if(!chosen) {
                func_00282CF0(&frame.target,p+0xc0,position);
                func_00282D30(&frame.target,&frame.target,0.5f);
                if(E_F(p,0x120)>3.0f) func_00282FB8(&frame.target,&frame.target,3.0f);
                if(func_00282DF0(&frame.target)<3.0f) func_00282F20(&frame.target,&frame.target,3.0f);
            } else qcopy(&frame.target,chosen+0x30);
        } else {
            int k=func_002A7820(0,3);
            int i;
            i=-1;
            while(++i<4) {
                int target;
                target=E_I(p,0x140+((i+k)%4)*4);
                if(target!=-1) {
                    chosen=D_L08_001B2ACC+target*128;
                    break;
                }
            }
            if(!chosen) {
                float radius=E_F(p,0x120);if(radius<3.0f) radius=3.0f;
                func_L02_0031E9E8(&frame.target,radius);
                func_00282CC0(&frame.target,&frame.target,position);
            } else qcopy(&frame.target,chosen+0x30);
        }
        if(chosen) {
            func_00282D30(&frame.direction,chosen,func_002A7878(-1.0f,1.0f));
            func_00282CC0(&frame.target,&frame.target,&frame.direction);
            func_00282D30(&frame.direction,chosen+0x10,func_002A7878(-1.0f,1.0f));
            func_00282CC0(&frame.target,&frame.target,&frame.direction);
        }
        {float height=func_002A89A8(&frame.target,0,0.5f);
        if(height!=0.0f) E_F(&frame.target,8)=height;}
        func_00282CF0(&frame.direction,&frame.target,position);
        f=func_00282DF0(&frame.direction)/D_L08_001B0B5C<0.08000000566f ? func_00282DF0(&frame.direction)/D_L08_001B0B5C : 0.08000000566f;
        func_00282F20(&frame.direction,&frame.direction,f);
        func_0029FCC0(m,0,&frame.velocity);
        func_00282F20(&frame.step,&frame.direction,0.05f);
        func_002ACB48(&frame.step,0.025f);
        func_00282CC0(&frame.velocity,&frame.velocity,&frame.step);
        E_F(&frame.direction,8)=func_L00_0031CDD0(&frame.velocity,&frame.target,0,f,-0.002722222358f);
        func_L08_003F6018(m,&frame.velocity,&frame.direction);
        ((FVars *)p)->count++;
        ((FVars *)p)->timer=((FVars *)p)->delay;
        break;
    }
    case 3:
        func_L06_0035EA68(m,p+0x60);
        if(m[0x60]&2) {
            m[0x20]=1;
            if(m[0x43]) func_002A7470(m,0,0,20);
        }
        break;
    case 4:
        if(func_L06_0035EA68(m,p+0x60)&0x40) {
            func_00282F20(&frame.target,D_L08_001AC5E0,0.1666666716f);
            func_002ABBB8(m,&frame.target,0,0.0f,0.0f,30,8,20,8.0f,4.0f,18.0f,1.0f,1,15.0f,1,1,-1,0,0x810001);
            func_0029F338(m);
        }
        break;
    }
}
