/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Tier: sol-high, task v1032. USA v1.01, all 28 placements.
 * Best check.py: 1324 bytes / expected 1328; 0 of 28 places match.
 * Profile: -O2 -G8 -ffunction-sections -frac2-keep-block-order.
 * First mismatch +0x12C: a branch targets the redundant iterator move instead
 * of the following instruction. At +0x2CC retail has beql and a GP score load
 * into v0; this draft uses beq and v1. Retail's absolute score path loads v0
 * then copies to v1; this draft loads directly to v1, omitting four bytes.
 * That missing move accounts for the remaining size difference and shifts the
 * rest of the function. The type dispatch, particle argument setup, data
 * allocation and subsequent relative instruction sequence are now reproduced.
 * keep-block-order plus an opening switch/default goto fixes the first dispatch.
 * The inner switch needs case 3: adjacent to default:. qzero_nc fixes data to
 * s3 and scratch to s2. NOT_SDA on D_0018C0B0 fixes the hero-pointer load.
 * A truthful FP-first tail on func_002B0A68 keeps GP/FP bank order and moves 255
 * into the delay slot. Snapshotting type before updating the counter fixes the
 * load/store schedule. GP/absolute score views bind to the same canonical int.
 * gcse-unsplit-edges, strict-aliasing, -g, int/long score and assignment-in-test
 * do not close the score join. fno-gcse worsens to 1296 bytes on this new source.
 * Next: explain the score-join copy and branch-likely using allocator evidence.
 * All required declarations are below. No linked build was run.
 */
#include "common.h"
extern int D_001B1688, D_001B24AC, D_001B24B0;
extern int D_001B1A80 NOT_SDA;
extern int D_001B1A80;
#define rewardScoreGP D_001B1A80
extern int D_001AF0F8 __attribute__((sda)),D_001AF0FC __attribute__((sda));
extern char *D_0018C0B0 NOT_SDA;
extern char *D_001AD7EC;
extern int func_00282C30(int);
extern void func_002E5DA0(int,int,void *,int),func_002E5CF8(int,int,void *);
extern int func_002ABB78(void *,void *);
extern void func_00282A28(void);
extern void func_002BC768(void *,float,int,float,unsigned int,float,float,float);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AA340(int *,int,int);
extern void func_002AD330(void *,void *,void *,void *);
extern void func_002B0A68(void *,int,void *,float,float,float,float,int);
extern void func_00282F20(void *,void *,float),func_00282CC0(void *,void *,void *);
extern void func_0032C700(void *,float,int,int,int,int,int,int,int,float,int,int,int,int);
#define PTR(p,o) (*(unsigned char **)((p)+(o)))
#define INT(p,o) (*(int *)((p)+(o)))
void func_003120C8(unsigned char *self,int effect,unsigned char *source)
{
    float position[4],direction[4],velocity[4];
    unsigned char *data=PTR(self,0x68),*p;
    int i,amount,kind,score;
    if(func_00282C30(D_001B1688-D_001B24AC)>=2) {
        switch (*(short *)(self+0xAA)) {
        case 0x1FA: func_002E5DA0(0,0,self,0x1F4); break;
        case 0x1FF: func_002E5DA0(1,0,self,0x1FF); break;
        default: goto ordinary_death;
        }
        goto death_sound_done;
ordinary_death:
        func_002E5CF8(0,0,self);
death_sound_done:
        D_001B24AC=D_001B1688;
    }
    if(func_00282C30(D_001B1688-D_001B24B0)>=2) D_001B24B0=D_001B1688;
    if(PTR(data,0xA0)) {
        PTR(PTR(PTR(data,0xA0),0x68),0xA4)=PTR(data,0xA4);
        INT(PTR(PTR(data,0xA0),0x68),0xAC)|=0x24;
    }
    if(PTR(data,0xA4)) {
        if(!func_002ABB78(PTR(PTR(PTR(data,0xA4),0x68),0xA0),self)) func_00282A28();
        PTR(PTR(PTR(data,0xA4),0x68),0xA0)=PTR(data,0xA0);
        INT(PTR(PTR(data,0xA4),0x68),0xAC)|=0x24;
    }
    p=self;
    do {unsigned char *d=PTR(p,0x68);INT(d,0xAC)|=0x20;p=PTR(d,0xA0);} while(p);
    qcopy(position,self+0x10);
    position[2]+=0.3f;
    func_002BC768(position,0.3f,1,1.01f,0x40808080,1.075f,0.05f,50000);
    i=4;
    do {func_002BC768(position,0.3f,1,1.01f,0x40808080,1.07f,0.05f,50000);--i;}while(i>=0);
    if(source) qcopy(direction,source+0x10);
    else func_00282CF0(direction,self+0x10,D_0018C0B0+0x10);
    if(func_00282C30(D_001B1688-D_001AF0F8)>=241) {D_001AF0FC=0;D_001AF0F8=D_001B1688;}
    else {
        if(D_001B1688 == D_001AF0F8) {
            score = rewardScoreGP;
            goto choose_amount;
        }
        func_002AA340(&D_001AF0FC,0,func_00282C30(D_001B1688-D_001AF0F8)>>2);
        D_001AF0F8=D_001B1688;
    }
    score=D_001B1A80;
choose_amount:
    if(score>=251 && D_001AF0FC<5) amount=4;
    else if(score>=201 && D_001AF0FC<10) amount=3;
    else if(score>=151 && D_001AF0FC<15) amount=2;
    else amount=score>=101 && D_001AF0FC<20;
    if(amount) {
        int type;
        kind=0;
        type=*(short *)(self+0xAA);
        D_001AF0FC+=amount;
        switch(type) {
        case 0x1F4:case 0x1FF:
            switch(amount) {case 1:kind=1;break;case 2:kind=5;break;case 3:default:kind=37;break;}break;
        case 0x1F5:case 0x200:kind=(1<<(amount-1))-1;if(kind>15)kind=15;break;
        }
        if(kind) {
            qzero_nc(velocity);
            if(PTR(data,0xF0) && !D_001AD7EC)func_002AD330(self,PTR(data,0xF0),self+0x10,velocity);
            func_002B0A68(self,kind,velocity,3,6,3,6,255);
        }
    }
    self[0x20]=3;*(unsigned short *)(self+0x34)|=1;self[0xBC]=15;INT(self,0x98)=0;
    if(effect) {
        data[0xCA]=1;
        func_00282F20(velocity,self+0xE0,0.5f);
        func_00282CC0(velocity,velocity,self+0x10);
        func_0032C700(velocity,1,0,10,10,10,10,15,0,0,0,0,0,0);
    }
}
