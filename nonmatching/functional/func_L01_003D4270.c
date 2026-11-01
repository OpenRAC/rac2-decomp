/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* sol-high retained attempt, USA v1.01, pinned game compiler, default -G8.
 * check.py: 1424 bytes versus 1428; 0 of 3 places match.
 * Typed trigger/pool records and separate camera locals recover retail's
 * s1/s2/s0 assignments. Ordinary TI assignments recover folded quadword
 * destinations and avoid the old helper block merging. Reversing the +0x45
 * condition recovers the retail conditional store.
 * Remaining: state-test branch/likely-load layout, address-register allocation,
 * copy/scalar scheduling in the two camera paths, and reset-store scheduling.
 * Typed anchor/moby forms tie; a position union adds a saved register (1436).
 * -fno-gcse gives 1432 with the wrong 0x50 frame and does not recover the tests.
 * Next: independent original state-control-flow or vector type evidence.
 * All required declarations are below. No linked-build claim.
 */
#include "common.h"
extern char D_00189EA0[];
extern char *D_L01_001B264C NOT_SDA;
extern char *ref_L01_003D4270_00 __attribute__((sda));
extern char *D_L01_001FE180[];
extern char D_L01_001B94C0[];
extern int func_002ACBC8(void *, int);
extern int func_002A8508(int, int);
extern void func_L00_002D7140(void *);

extern void func_00282CF0(void *, void *, void *);
extern float func_00283248(float, float);
extern float func_00282E80(void *, void *);
extern void func_00335438(void *, void *, int, int, int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern int func_L01_0042A568(void);
extern void func_L01_0042A6F0(int, int);
extern void func_003355A8(int);
extern int func_00283DB8(void *, float);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct Pool {
    float f0, f4, f8, fc, f10, f14;
    unsigned char b18, b19;
    short s1a;
    unsigned char b1c, b1d, b1e, b1f;
    Quad pos;
    int pad30, f34;
} Pool;
typedef struct TriggerData {
    int conditions[4];
    int volume;
    struct Pool *pool;
    float f18, f1c, f20, f24, f28, f2c;
    unsigned char b30, b31, b32, b33;
    int anchor, target, state, f40;
    unsigned char b44, b45, b46, b47, b48, b49;
} TriggerData;
extern Pool *func_L00_002D70A0(int);
void func_L01_003D4270(char *m)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4];
    int clear = 1;
    TriggerData *d = *(TriggerData **)(m+0x68);
    int active = func_002ACBC8(D_00189EA0,d->volume);
    Pool *p;
    if (d->conditions[0]==-1 && d->conditions[1]==-1 && d->conditions[2]==-1 && d->conditions[3]==-1) clear=0;
    if (d->conditions[0]!=-1 && func_002A8508(d->conditions[0],-1)) clear=0;
    if (d->conditions[1]!=-1 && func_002A8508(d->conditions[1],-1)) clear=0;
    if (d->conditions[2]!=-1 && func_002A8508(d->conditions[2],-1)) clear=0;
    if (d->conditions[3]!=-1 && func_002A8508(d->conditions[3],-1)) clear=0;
    if (B(m,0x20)) {
        p=d->pool;
        if (p && (!active || clear)) {func_L00_002D7140(p); d->pool=0;}
        else if (!p && active && !clear && d->target==-1) {
            Pool *created;
            created=func_L00_002D70A0(d->b33);
            d->pool=created;
            if (!created) return;
            created->f0=d->f18;
            created->fc=d->f1c==-1.0f?d->f1c:d->f1c*0.01745329424738884f;
            created->f4=d->f20; created->f8=d->f24;
            if(!d->b45) created->f14=d->f28; else created->f14=-1.0f;
            created->f10=d->f2c==-1.0f?d->f2c:d->f2c*0.01745329424738884f;
            created->s1a=d->b30; created->b1e=d->b31; created->b1f=d->b32; created->b18=d->b46;
            if(d->f40!=-1) created->f34=d->f40;
            if(d->anchor!=-1) {
                if(d->b49) created->pos=*(Quad *)(ref_L01_003D4270_00+(d->anchor<<7));
                else {func_00282CF0(pos,D_L01_001B264C+(d->anchor<<7)+0x30,D_00189EA0); created->pos=*(Quad *)(pos);}
            }
        } else if(active && !d->state && d->target!=-1) {
            char *camera;
            *(Quad *)(pos)=*(Quad *)(D_00189EA0); pos[2]+=1.25f;
            camera=D_L01_001FE180[d->target];
            rot[2]=func_00283248(pos[0]-F(camera,0x10),pos[1]-F(camera,0x14));
            rot[1]=-func_00283248(func_00282E80(camera+0x10,pos),pos[2]-F(camera,0x18)); rot[0]=0;
            func_00335438(D_L01_001B94C0,D_L01_001B94C0+0x10,3,120,0);
            func_00335370(camera+0x10); func_003353C8(rot); d->state=1;
        } else if(active && d->state) {
            char *camera;
            if(d->state==1 && (func_L01_0042A568()&1)) {d->state=2;func_L01_0042A6F0(1,0);}
            *(Quad *)(pos)=*(Quad *)(D_00189EA0); pos[2]+=1.25f;
            camera=D_L01_001FE180[d->target];
            rot[2]=func_00283248(pos[0]-F(camera,0x10),pos[1]-F(camera,0x14));
            rot[1]=-func_00283248(func_00282E80(camera+0x10,pos),pos[2]-F(camera,0x18)); rot[0]=0;
            func_00335370(camera+0x10); func_003353C8(rot);
        } else if(!active && d->state) {func_003355A8(1);d->state=0;}
        else if(p && d->anchor!=-1) {
            if(d->b49) p->pos=*(Quad *)(ref_L01_003D4270_00+(d->anchor<<7));
            else {func_00282CF0(pos,D_L01_001B264C+(d->anchor<<7)+0x30,D_00189EA0);p->pos=*(Quad *)(pos);}
        }
        p=d->pool;
        if(p) {
            if(!d->b47 && d->anchor!=-1) {
                *(Quad *)(pos)=*(Quad *)(ref_L01_003D4270_00+(d->anchor<<7)+0x30);pos[3]=1;
                if(func_00283DB8(pos,255.0f)!=-1) {
                    d->b47=1;
                    if(d->b45) d->pool->f14=d->f28;
                    if(d->b44) {d->pool->b1f=0;d->pool->b1e=0;}
                    if(d->b48) d->pool->b18=1;
                }
            }
            p->f10=d->f2c*0.01745329424738884f;
        }
    } else {d->b47=0;d->pool=0;d->state=0;B(m,0x30)=255;B(m,0x20)=1;}
}
